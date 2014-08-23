/* manager object */
/* vim: set sw=2 et: */

/*
 * Copyright (C) 2014 Brian Bidulock
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#undef WNCK_DISABLE_DEPRECATED

#include <config.h>

#include <glib/gi18n-lib.h>
#include "screen.h"
#include "manager.h"
#include "style.h"
#include "theme.h"
#include "xutils.h"
#include "private.h"
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <string.h>
#include <stdlib.h>

/**
 * SECTION:manager
 * @short_description: an object representing a window manager
 * @see_also: #WnckStyle, #WnckTheme
 * @stability: Unstable
 *
 * The #WnckManager represents a window manager running on a
 * #WnckScreen.
 *
 * The #WnckManager has no corresponding notion in GDK.
 *
 * The #WnckManager objects are always owned by libwnck and must not be
 * referenced or unreferenced.
 */

#define CHECK_WINS 6
#define CHECK_DIRS 5

struct _WnckManagerOperations {
  char *name;
  char *version;
  void (*get_rcfile) (void);
  char *(*find_style) (void);
  char *(*get_stlye) (void);
  void (*set_style) (void);
  void (*reload_style) (void);
  void (*list_dir) (char *, char *, WnckStyleType);
  void (*list_styles) (void);
  char *(*get_menu) (void);
  void (*gen_item) (char *, WnckStyleType, char *, char *);
  void (*gen_dir) (char *, char *, WnckStyleType);
  void (*gen_menu) (void);
  char *(*get_icon) (void);
};

struct _WnckManagerPrivate
{
  WnckScreen *screen;
  struct _WnckManagerOperations *ops;
  union {
    struct {
      gulong netwm_check;   /* NetWM/EWMH check window */
      gulong winwm_check;   /* GNOME1/WMH check window */
      gulong maker_check;   /* WindowMaker Noticeboard check window */
      gulong motif_check;   /* Motif/MWMH check window */
      gulong icccm_check;   /* ICCCM 2.0 manager window */
      gulong redir_check;   /* ICCCM root window */
    };
    gulong wins[CHECK_WINS];
  };
  gulong proxy;             /* desktop button proxy window */
  pid_t pid;                /* window manager pid */
  char *host;               /* window manager host */
  char *name;               /* window manager name */
  char **argv;              /* window manager command line argv[] */
  int argc;                 /* window manager command line argc */
  char **cargv;             /* window manager WM_COMMAND argv[] */
  int cargc;                /* window manager WM_COMMAND argc */
  XClassHint ch;            /* window manager WM_CLASS */
  char *rcfile;             /* window manager rc file */
  union {
    struct {
      char *pdir;   /* WM private directory */
      char *rdir;   /* WM run directory */
      char *udir;   /* WM user directory */
      char *sdir;   /* WM system directory */
      char *edir;   /* WM config directory */
    };
    char *dirs[CHECK_DIRS];
  };
  WnckStyle *current_style;
  WnckTheme *current_theme;
  char *menu;
  gboolean noenv;
  char *env;
  size_t nenv;
  XrmDatabase db;
  char **xdg_dirs;
  char *icon;
};

G_DEFINE_TYPE (WnckManager, wnck_manager, G_TYPE_OBJECT);
#define WNCK_MANAGER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), WNCK_TYPE_MANAGER, WnckManagerPrivate))

enum {
  STYLE_CHANGED,
  THEME_CHANGED,
  MENU_CHANGED,
  ICON_CHANGED,
  LAST_SIGNAL
};

static void wnck_manager_init               (WnckManager        *manager);
static void wnck_manager_class_init         (WnckManagerClass   *klass);
static void wnck_manager_finalize           (GObject            *object);

static void emit_style_changed              (WnckManager        *manager,
                                             WnckStyle          *previous_style);
static void emit_theme_changed              (WnckManager        *manager,
                                             WnckTheme          *previous_theme);
static void emit_menu_changed               (WnckManager        *manager,
                                             const char*        *previous_menU);
static void emit_icon_changed               (WnckManager        *manager,
                                             const char*        *previous_icon);

static guint signals[LAST_SIGNAL] = { 0 };

static void
wnck_manager_init (WnckManager *manager)
{
  manager->priv = WNCK_MANAGER_GET_PRIVATE (manager);

  manager->priv->screen = NULL;

  manager->priv->netwm_check = 0;
  manager->priv->winwm_check = 0;
  manager->priv->maker_check = 0;
  manager->priv->motif_check = 0;
  manager->priv->icccm_check = 0;
  manager->priv->redir_check = 0;

  manager->priv->proxy = 0;

  manager->priv->pid = 0;
  manager->priv->host = NULL;
  manager->priv->name = NULL;
  manager->priv->argv = NULL;
  manager->priv->argc = 0;
  manager->priv->cargv = NULL;
  manager->priv->cargc = 0;
  manager->priv->ch = { NULL, NULL };
  manager->priv->rcfile = NULL;

  manager->priv->pdir = NULL;
  manager->priv->rdir = NULL;
  manager->priv->udir = NULL;
  manager->priv->sdir = NULL;
  manager->priv->edir = NULL;

  manager->priv->current_style = NULL;
  manager->priv->current_theme = NULL;
  manager->priv->menu = NULL;
  manager->priv->noenv = TRUE;
  manager->priv->env = NULL;
  manager->priv->nenv = 0;
  manager->priv->db = NULL;
  manager->priv->xdg_dirs = NULL;
  manager->priv->icon = NULL;
}

static void
wnck_manager_class_init (WnckManagerClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  _wnck_manager_init ();

  g_type_class_add_private (klass, sizeof (WnckManagerPrivate));

  object_class->finalize = wnck_manager_finalize;

  /**
   * WnckManager::style-changed:
   * @manager: the #WnckManager that emitted the signal
   * @previous_style: the previous #WnckStyle before this change.
   *
   * Emitted when the window manager style changes.  This may be as a result
   * of the style being changed by this library or by the window manager using
   * its root menu or other facility.
   *
   * Since: libwnck+
   */
  signals[STYLE_CHANGED] =
    g_signal_new ("style_changed",
                  G_OBJECT_CLASS_TYPE (object_class),
                  G_SIGNAL_RUN_LAST,
                  G_STRUCT_OFFSET (WnckManagerClass, style_changed),
                  NULL, NULL,
                  g_cclosure_marshal_VOID__OBJECT,
                  G_TYPE_NONE, 1, WNCK_TYPE_STYLE);
  /**
   * WnckManager::theme-changed:
   * @manager: the #WnckManager that emitted the signal
   * @previous_theme: the previous #WnckTheme before this change.
   *
   * Emitted when the window manager theme changes.  This may be as a result
   * of the style beign changed by this library or by the window manager using
   * its root menu or other facility.
   *
   * Since: libwnck+
   */
  signals[THEME_CHANGED] =
    g_signal_new("theme_changed",
                 G_OBJECT_CLASS_TYPE (object_class),
                 G_SIGNAL_RUN_LAST,
                 G_STRUCT_OFFSET (WnckManagerClass, theme_changed),
                 NULL, NULL,
                 g_cclosure_marshal_VOID__OBJECT,
                 G_TYPE_NONE, 1, WNCK_TYPE_THEME);

  /**
   * WnckManager::menu-changed:
   * @manager: the #WnckManager that emitted the signal
   * @previous_menu: the previous menu path before this change.
   *
   * Emitted when the window manager root menu path changes.
   *
   * Since: libwnck+
   */
  signals[MENU_CHANGED] =
    g_signal_new("menu_changed",
                 G_OBJECT_CLASS_TYPE (object_class),
                 G_SIGNAL_RUN_LAST,
                 G_STRUCT_OFFSET (WnckManagerClass, menu_changed),
                 NULL, NULL,
                 g_cclosure_marshal_VOID__OBJECT,
                 G_TYPE_NONE, 1, G_TYPE_STRING);

  /**
   * WnckManager::icon-changed:
   * @manager: the #WnckManager that emitted the signal
   * @previous_icon: the previous icon name before this change.
   *
   * Emitted when the window manager icon changes.
   *
   * Since: libwnck+
   */
  signals[ICON_CHANGED] =
    g_signal_new("icon_changed",
                 G_OBJECT_CLASS_TYPE (object_class),
                 G_SIGNAL_RUN_LAST,
                 G_STRUCT_OFFSET (WnckManagerClass, icon_changed),
                 NULL, NULL,
                 g_cclosure_marshal_VOID__OBJECT,
                 G_TYPE_NONE, 1, G_TYPE_STRING);
}

static void
wnck_manager_finalize (GObject *object)
{
  WnckManager *manager;

  manager = WNCK_MANAGER (object);

  if (manager->priv->screen)
    g_object_unref(manager->priv->screen);
  g_free(manager->priv->host);
  g_free(manager->priv->name);
  g_strfreev(manager->priv->argv);
  g_strfreev(manager->priv->cargv);
  g_free(manager->priv->ch.res_name);
  g_free(manager->priv->ch.res_class);

  g_free(manager->priv->rcfile);
  g_free(manager->priv->pdir);
  g_free(manager->priv->rdir);
  g_free(manager->priv->udir);
  g_free(manager->priv->sdir);
  g_free(manager->priv->edir);

  if (manager->priv->current_style)
    g_object_unref(manager->priv->current_style);
  if (manager->priv->current_theme)
    g_object_unref(manager->priv->current_theme);

  g_free(manager->priv->menu);
  g_free(manager->priv->env);
  if (manager->priv->db)
    XrmDestroyDatabase(manager->priv->db);
  g_strfreev(manager->priv->xdg_dirs);
  g_free(manager->priv->icon);

  G_OBJECT_CLASS (wnck_manager_parent_class)->finalize (object);
}

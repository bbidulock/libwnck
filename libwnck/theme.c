/* theme object */
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
 * SECTION:theme
 * @short_description: an object representing a desktop theme
 * @see_also: #WnckManager, #WnckStyle
 * @stability: Unstable
 *
 * The #WnckTheme represents a theme for a window manager.
 *
 * The #WnckTheme has no corresponding notion in GDK.
 *
 * The #WnckTheme objects are always owned by libwnck and must not be
 * referenced or unreferenced.
 */

struct _WnckThemePrivate
{
	char *themename;
	char *theme;
	char *themefile;
        WnckThemeType type;
};

G_DEFINE_TYPE (WnckTheme, wnck_theme, G_TYPE_OBJECT);
#define WNCK_THEME_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), WNCK_TYPE_SYTLE, WnckThemePrivate))

enum {
  THEME_ACTIVATED,
  THEME_DEACTIVATED,
  LAST_SIGNAL
};

static void wnck_theme_init             (WnckTheme      *theme);
static void wnck_theme_class_init       (WnckThemeClass *klass);
static void wnck_theme_finalize         (GObject        *object);

static void emit_theme_activated        (WnckTheme      *theme,
					 WnckScreen	*screen);
static void emit_theme_deactivated      (WnckTheme      *theme,
					 WnckScreen	*screen);

static guint signals[LAST_SIGNAL] = { 0 };

static void
wnck_theme_init (WnckStyle *theme)
{
  theme->priv = WNCK_THEME_GET_PRIVATE (theme);

  theme->priv->themename = NULL;
  theme->priv->theme = NULL;
  theme->priv->themefile = NULL;
  theme->priv->type = 0;
}

static void
wnck_theme_class_init (WnckStyleClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  _wnck_theme_init ();

  g_type_class_add_private (klass, sizeof (WnckStylePrivate));

  object_class->finalize = wnck_theme_finalize;

  /**
   * WnckStyle::theme-activated:
   * @theme: the #WnckStyle that emitted the signal.
   * @screen: the #WnckScreen for which the theme became active.
   *
   * Emitted when the window manager theme become the active theme for
   * a #WnckScreen instance.
   *
   * Since: libwnck+
   */
  signals[THEME_ACTIVATED] =
    g_signal_new ("theme_activated",
                  G_OBJECT_CLASS_TYPE (object_class),
                  G_SIGNAL_RUN_LAST,
                  G_STRUCT_OFFSET (WnckStyleClass, theme_activated),
                  NULL, NULL,
                  g_cclosure_marshal_VOID__OBJECT,
                  G_TYPE_NONE, 1, WNCK_TYPE_SCREEN);

  /**
   * WnckStyle::theme-deactivated:
   * @theme: the #WnckStyle that emitted the signal
   * @screen: the #WnckScreen for which the theme became inactive.
   *
   * Emitted when the window manager theme becomes the active theme for
   * a #WnckScreen instance.
   *
   * Since: libwnck+
   */
  signals[THEME_DEACTIVATED] =
    g_signal_new ("theme_deactivated",
                  G_OBJECT_CLASS_TYPE (object_class),
                  G_SIGNAL_RUN_LAST,
                  G_STRUCT_OFFSET (WnckStyleClass, theme_deactivated),
                  NULL, NULL,
                  g_cclosure_marshal_VOID__OBJECT,
                  G_TYPE_NONE, 1, WNCK_TYPE_SCREEN);

}

static void
wnck_theme_finalize (GObject *object)
{
  WnckStyle *theme;

  theme = WNCK_THEME (object);

  if (theme->themename)
    g_free(theme->themename);
  if (theme->theme)
    g_free(theme->theme);
  if (theme->themefile)
    g_free(theme->themefile);

  G_OBJECT_CLASS (wnck_theme_parent_class)->finalize (object);
}



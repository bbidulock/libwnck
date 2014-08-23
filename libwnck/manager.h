/* manager object */
/* vim: set sw=2 et: */

/*
 * Copyright (c) 2014 Brian Bidulock
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

#ifndef WNCK_MANAGER_H
#define WNCK_MANAGER_H

#include <glib-object.h>

G_BEGIN_DECLS

/* forward decls */
typedef struct _WnckScreen      WnckScreen;
typedef struct _WnckStyle       WnckStyle;
typedef struct _WnckTheme       WnckTheme;

/* Manager */

#define WNCK_TYPE_MANAGER               (wnck_manager_get_type ())
#define WNCK_MANAGER(object)            (G_TYPE_CHECK_INSTANCE_CAST ((object), WNCK_TYPE_MANAGER, WnckManager))
#define WNCK_MANAGER_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST ((klass), WNCK_TYPE_MANAGER, WnckManagerClass))
#define WNCK_IS_MANAGER(object)         (G_TYPE_CHECK_INSTANCE_TYPE ((object), WNCK_TYPE_MANAGER))
#define WNCK_IS_MANAGER_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE ((klass), WNCK_TYPE_MANAGER))
#define WNCK_MANAGER_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS ((obj), WNCK_TYPE_MANAGER, WnckManagerClass))

typedef struct _WnckManager             WnckManager;
typedef struct _WnckManagerClass        WnckManagerClass;
typedef struct _WnckManagerPrivate      WnckManagerPrivate;

/**
 * WnckManager:
 *
 * The #WnckManager struct contains only private fields and should not be
 * directly accessed.
 */
struct _WnckManager
{
  GObject parent_instance;

  WnckManagerPrivate *priv;
};

struct _WnckManagerClass
{
  GObjectClass parent_class;

  void (* style_changed)        (WnckManager    *manager,
                                 WnckStyle      *previous_style);
  void (* theme_changed)        (WnckManager    *manager,
                                 WnckTheme      *previous_theme);
  void (* menu_changed)         (WnckManager    *manager,
                                 gchar          *previous_menu);
  void (* icon_changed)         (WnckManager    *manager,
                                 gchar          *previous_icon);

  /* Padding for future expansion */
  void (* pad2) (void);
  void (* pad3) (void);
  void (* pad4) (void);
  void (* pad5) (void);
  void (* pad6) (void);
};

/**
 * WnckStyleType:
 * @WNCK_STYLE_TYPE_GENERAL: the #WnckStyle is of a general type
 * that is neither a system type nor a user type.
 * @WNCK_STYLE_TYPE_SYSTEM: the #WnckStyle corresponds to a system
 * style.
 * @WNCK_STYLE_TYPE_USER: the #WnckStyle corresponds to a user style.
 *
 * The defining the origin of the #WnckStyle.  Most window managers
 * support the distinction between system defined styles and user
 * defined styles.  Some, such as IceWM, do not support the distinction
 * between system and user styles and only have a general style type.
 */
typedef enum
{
  WNCK_STYLE_TYPE_GENERAL,
  WNCK_STYLE_TYPE_USER,
  WNCK_STYLE_TYPE_SYSTEM
} WnckStyleType;

/**
 * WnckManagerSupport:
 * @WNCK_MANAGER_SUPPORT_NETWM: Support for EWMH/NetWM specifications.
 * @WNCK_MANAGER_SUPPORT_WINWM: Support for GNOME/WinWM specifications.
 * @WNCK_MANAGER_SUPPORT_MAKER: Support for WindowMaker specifications.
 * @WNCK_MANAGER_SUPPORT_MOTIF: Support for OSF/Motif specifications.
 * @WNCK_MANAGER_SUPPORT_ICCCM: Support for ICCCM 2.0 specifications.
 * @WNCK_MANAGER_SUPPORT_REDIR: Support for ICCCM reparenting specifications.
 *
 * Type defining a the specifications that a window manager may support.
 */
typedef enum {
  WNCK_MANAGER_SUPPORT_NETWM,
  WNCK_MANAGER_SUPPORT_WINWM,
  WNCK_MANAGER_SUPPORT_MAKER,
  WNCK_MANAGER_SUPPORT_MOTIF,
  WNCK_MANAGER_SUPPORT_ICCCM,
  WNCK_MANAGER_SUPPORT_REDIR
} WnckManagerSupport;

GType wnck_manager_get_type (void) G_GNUC_CONST;

WnckManager*    wnck_manager_get_default                (void);
WnckManager*    wnck_manager_get                        (int            index);
WnckManager*    wnck_manager_get_for_root               (gulong         root_window_id);
WnckManager*    wnck_manager_get_for_screen             (WnckScreen     *screen);
GList*          wnck_manager_get_screens                (WnckManager    *manager);
int             wnck_manager_get_number                 (WnckManager    *manager);
WnckScreen*     wnck_manager_get_screen                 (WnckManager    *manager);

WnckStyle*      wnck_manager_find_style                 (WnckManager    *manager,
                                                         WnckStyleType  type,
                                                         const char     *name);
WnckStyle*      wnck_manager_get_style                  (WnckManager    *manager);
GList*          wnck_manager_get_styles                 (WnckManager    *manager);
GList*          wnck_manager_get_system_styles          (WnckManager    *manager);
GList*          wnck_manager_get_user_styles            (WnckManager    *manager);
gboolean        wnck_manager_set_style                  (WnckManager    *manager,
                                                         WnckStyle      *style);
gboolean        wnck_manager_set_system_style           (WnckManager    *manager,
                                                         gchar          *style_name);
gboolean        wnck_manager_set_user_style             (WnckManager    *manager,
                                                         gchar          *style_name);
void            wnck_manager_reload_style               (WnckManager    *manager);

WnckTheme*      wnck_manager_get_theme                  (WnckManager    *manager);
GList*          wnck_manager_get_themes                 (WnckManager    *manager);
GList*          wnck_manager_get_system_themes          (WnckManager    *manager);
GList*          wnck_manager_get_user_themes            (WnckManager    *manager);
gboolean        wnck_manager_set_theme                  (WnckManager    *manager,
                                                         WnckTheme      *theme);
gboolean        wnck_manager_set_system_theme           (WnckManager    *manager,
                                                         gchar          *theme_name);
gboolean        wnck_manager_set_user_theme             (WnckManager    *manager,
                                                         gchar          *theme_name);
void            wnck_manager_reload_theme               (WnckManager    *manager);

gboolean        wnck_manager_restart                    (WnckManager    *manager);
gboolean        wnck_manager_reload                     (WnckManager    *manager);

gboolean        wnck_manager_supports                   (WnckManager    *manager,
                                                         WnckManagerSupport spec);
pid_t           wnck_manager_get_pid                    (WnckManager    *manager);
const char*     wnck_manager_get_name                   (WnckManager    *manager);
gboolean        wnck_manager_supports_feature           (WnckManager    *manager,
                                                         WnckManagerSupport spec,
                                                         const char     *atom);
GList*          wnck_manager_get_command                (WnckManager    *manager);
const char*     wnck_manager_get_res_class              (WnckManager    *manager);
const char*     wnck_manager_get_res_name               (WnckManager    *manager);

const char*     wnck_manager_get_rcfile                 (WnckManager    *manager);
const char*     wnck_manager_get_menu_file              (WnckManager    *manager);

const char*     wnck_manager_get_private_directory      (WnckManager    *manager);
const char*     wnck_manager_get_run_directory          (WnckManager    *manager);
const char*     wnck_manager_get_user_directory         (WnckManager    *manager);
const char*     wnck_manager_get_system_directory       (WnckManager    *manager);
const char*     wnck_manager_get_config_directory       (WnckManager    *manager);
const char*     wnck_manager_get_icon_name              (WnckManager    *manager);

G_END_DECLS

#endif /* WNCK_MANAGER_H */

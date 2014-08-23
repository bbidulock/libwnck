/* manager theme menu (ops on a single manager) */
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

#ifndef WNCK_MANAGER_THEME_MENU_H
#define WNCK_MANAGER_THEME_MENU_H

#include <libwnck/manager.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define WNCK_TYPE_THEME_MENU              (wnck_theme_menu_get_type ())
#define WNCK_THEME_MENU(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), WNCK_TYPE_THEME_MENU, WnckThemeMenu))
#define WNCK_THEME_MENU_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), WNCK_TYPE_THEME_MENU, WnckThemeMenuClass))
#define WNCK_IS_THEME_MENU(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), WNCK_TYPE_THEME_MENU))
#define WNCK_IS_THEME_MENU_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), WNCK_TYPE_THEME_MENU))
#define WNCK_THEME_MENU_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), WNCK_TYPE_THEME_MENU, WnckThemeMenuClass))

typedef struct _WnckThemeMenu        WnckThemeMenu;
typedef struct _WnckThemeMenuClass   WnckThemeMenuClass;
typedef struct _WnckThemeMenuPrivate WnckThemeMenuPrivate;

/**
 * WnckThemeMenu:
 *
 * The #WnckThemeMenu struct contains only private fields and should not be
 * directly accessed.
 */
struct _WnckThemeMenu
{
  GtkMenu parent_instance;

  WnckThemeMenuPrivate *priv;
};

struct _WnckThemeMenuClass
{
  GtkMenuClass parent_class;

  /* Padding for future expansion */
  void (* pad1) (void);
  void (* pad2) (void);
  void (* pad3) (void);
  void (* pad4) (void);
};

GType wnck_theme_menu_get_type (void) G_GNUC_CONST;

GtkWidget* wnck_theme_menu_new (WnckManager *manager);

G_END_DECLS

#endif /* WNCK_MANAGER_THEME_MENU_H */

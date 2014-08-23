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

#ifndef WNCK_THEME_H
#define WNCK_THEME_H

#include <glib-object.h>
#include <libwnck/screen.h>
#include <libwnck/manager.h>

G_BEGIN_DECLS

#define WNCK_TYPE_THEME                 (wnck_theme_get_type())
#define WNCK_THEME(object)              (G_TYPE_CHECK_INSTANCE_CAST ((object), WNCK_TYPE_THEME, WnckTheme))
#define WNCK_THEME_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST ((klass), WNCK_TYPE_THEME, WnckThemeClass))
#define WNCK_IS_THEME(object)           (G_TYPE_CHECK_INSTANCE_TYPE ((object), WNCK_TYPE_THEME))
#define WNCK_IS_THEME_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), WNCK_TYPE_THEME))
#define WNCK_WORKSPACE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), WNCK_TYPE_THEME, WnckThemeClass))

typedef struct _WnckThemeClass      WnckThemeClass;
typedef struct _WnckThemePrivate    WnckThemePrivate;

/**
 * WnckTheme:
 *
 * The #WnckTheme struct contains only private fields and should not be
 * directly accessed.
 */
struct _WnckTheme
{
  GObject parent_instance;

  WnckThemePrivate *priv;
};

struct _WnckThemeClass
{
  GObjectClass parent_class;

  void (* theme_activated)          (WnckTheme      *theme,
                                     WnckScreen     *screen);

  void (* theme_deactivated)        (WnckTHeme      *theme,
                                     WnckScreen     *screen);

  /* Padding for future expansion */
  void (* pad1) (void);
  void (* pad2) (void);
  void (* pad3) (void);
  void (* pad4) (void);
  void (* pad5) (void);
  void (* pad6) (void);
};

GType wnck_theme_get_type (void) G_GNUC_CONST;

const char*     wnck_theme_get_name     (WnckTheme      *theme);
const char*     wnck_theme_get_path     (WnckTheme      *theme);
const char*     wnck_theme_get_spec     (WnckTheme      *theme);
WnckThemeType   wnck_theme_get_type     (WnckTheme      *theme);
gboolean        wnck_theme_is_active    (WnckTheme      *theme);

G_END_DECLS

#endif /* WNCK_THEME_H */

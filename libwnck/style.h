/* style object */
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

#ifndef WNCK_STYLE_H
#define WNCK_STYLE_H

#include <glib-object.h>
#include <libwnck/manager.h>

G_BEGIN_DECLS

#define WNCK_TYPE_STYLE                 (wnck_style_get_type())
#define WNCK_STYLE(object)              (G_TYPE_CHECK_INSTANCE_CAST ((object), WNCK_TYPE_STYLE, WnckStyle))
#define WNCK_STYLE_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST ((klass), WNCK_TYPE_STYLE, WnckStyleClass))
#define WNCK_IS_STYLE(object)           (G_TYPE_CHECK_INSTANCE_TYPE ((object), WNCK_TYPE_STYLE))
#define WNCK_IS_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), WNCK_TYPE_STYLE))
#define WNCK_WORKSPACE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), WNCK_TYPE_STYLE, WnckStyleClass))

typedef struct _WnckStyleClass      WnckStyleClass;
typedef struct _WnckStylePrivate    WnckStylePrivate;

/**
 * WnckStyle:
 *
 * The #WnckStyle struct contains only private fields and should not be
 * directly accessed.
 */
struct _WnckStyle
{
  GObject parent_instance;

  WnckStylePrivate *priv;
};

struct _WnckStyleClass
{
  GObjectClass parent_class;

  void (* style_activated)          (WnckStyle      *style,
                                     WnckManager    *manager);

  void (* style_deactivated)        (WnckStyle      *style,
                                     WnckManager    *manager);

  /* Padding for future expansion */
  void (* pad1) (void);
  void (* pad2) (void);
  void (* pad3) (void);
  void (* pad4) (void);
  void (* pad5) (void);
  void (* pad6) (void);
};

GType wnck_style_get_type (void) G_GNUC_CONST;

const char*     wnck_style_get_name     (WnckStyle      *style);
const char*     wnck_style_get_path     (WnckStyle      *style);
const char*     wnck_style_get_spec     (WnckStyle      *style);
WnckStyleType   wnck_style_get_type     (WnckStyle      *style);
gboolean        wnck_style_is_active    (WnckStyle      *style);

G_END_DECLS

#endif /* WNCK_STYLE_H */

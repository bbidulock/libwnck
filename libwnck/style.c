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
 * SECTION:style
 * @short_description: an object representing a window manager style
 * @see_also: #WnckManager, #WnckTheme
 * @stability: Unstable
 *
 * The #WnckStyle represents a style for a window manager.
 *
 * The #WnckStyle has no corresponding notion in GDK.
 *
 * The #WnckStyle objects are always owned by libwnck and must not be
 * referenced or unreferenced.
 */

struct _WnckStylePrivate
{
	char *stylename;
	char *style;
	char *stylefile;
        WnckStyleType type;
};

G_DEFINE_TYPE (WnckStyle, wnck_style, G_TYPE_OBJECT);
#define WNCK_STYLE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), WNCK_TYPE_SYTLE, WnckStylePrivate))

enum {
  STYLE_ACTIVATED,
  STYLE_DEACTIVATED,
  LAST_SIGNAL
};

static void wnck_style_init             (WnckStyle      *style);
static void wnck_style_class_init       (WnckStyleClass *klass);
static void wnck_style_finalize         (GObject        *object);

static void emit_style_activated        (WnckStyle      *style,
                                         WnckManager    *manager);
static void emit_style_deactivated      (WnckStyle      *style,
                                         WnckManager    *manager);

static guint signals[LAST_SIGNAL] = { 0 };

static void
wnck_style_init (WnckStyle *style)
{
  style->priv = WNCK_STYLE_GET_PRIVATE (style);

  style->priv->stylename = NULL;
  style->priv->style = NULL;
  style->priv->stylefile = NULL;
  style->priv->type = 0;
}

static void
wnck_style_class_init (WnckStyleClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  _wnck_style_init ();

  g_type_class_add_private (klass, sizeof (WnckStylePrivate));

  object_class->finalize = wnck_style_finalize;

  /**
   * WnckStyle::style-activated:
   * @style: the #WnckStyle that emitted the signal.
   * @manager: the #WnckManager for which the style became active.
   *
   * Emitted when the window manager style become the active style for
   * a #WnckManager instance.
   *
   * Since: libwnck+
   */
  signals[STYLE_ACTIVATED] =
    g_signal_new ("style_activated",
                  G_OBJECT_CLASS_TYPE (object_class),
                  G_SIGNAL_RUN_LAST,
                  G_STRUCT_OFFSET (WnckStyleClass, style_activated),
                  NULL, NULL,
                  g_cclosure_marshal_VOID__OBJECT,
                  G_TYPE_NONE, 1, WNCK_TYPE_MANAGER);

  /**
   * WnckStyle::style-deactivated:
   * @style: the #WnckStyle that emitted the signal
   * @manager: the #WnckManager for which the style became inactive.
   *
   * Emitted when the window manager style becomes the active style for
   * a #WnckManager instance.
   *
   * Since: libwnck+
   */
  signals[STYLE_DEACTIVATED] =
    g_signal_new ("style_deactivated",
                  G_OBJECT_CLASS_TYPE (object_class),
                  G_SIGNAL_RUN_LAST,
                  G_STRUCT_OFFSET (WnckStyleClass, style_deactivated),
                  NULL, NULL,
                  g_cclosure_marshal_VOID__OBJECT,
                  G_TYPE_NONE, 1, WNCK_TYPE_MANAGER);

}

static void
wnck_style_finalize (GObject *object)
{
  WnckStyle *style;

  style = WNCK_STYLE (object);

  if (style->stylename)
    g_free(style->stylename);
  if (style->style)
    g_free(style->style);
  if (style->stylefile)
    g_free(style->stylefile);

  G_OBJECT_CLASS (wnck_style_parent_class)->finalize (object);
}



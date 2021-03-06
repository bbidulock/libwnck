/* Xlib utilities */
/* vim: set sw=2 et: */

/*
 * Copyright (C) 2001 Havoc Pennington
 * Copyright (C) 2005-2007 Vincent Untz
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

#ifndef WNCK_XUTILS_H
#define WNCK_XUTILS_H

#include <glib.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>

G_BEGIN_DECLS

#define WNCK_STOCK_ABOVE         "wnck-stock-above"
#define WNCK_STOCK_ARRANGED      "wnck-stock-arranged"
#define WNCK_STOCK_BELOW         "wnck-stock-below"
#define WNCK_STOCK_BORDER        "wnck-stock-border"
#define WNCK_STOCK_DELETE        "wnck-stock-delete"
#define WNCK_STOCK_COMMAND       "wnck-stock-command"
#define WNCK_STOCK_FOCUS         "wnck-stock-focus"
#define WNCK_STOCK_KILL          "wnck-stock-kill"
#define WNCK_STOCK_LOWER         "wnck-stock-lower"
#define WNCK_STOCK_MAXIMIZE_B    "wnck-stock-maximize-b"
#define WNCK_STOCK_MAXIMIZE_H    "wnck-stock-maximize-h"
#define WNCK_STOCK_MAXIMIZE_V    "wnck-stock-maximize-v"
#define WNCK_STOCK_MAXIMIZE      "wnck-stock-maximize"
#define WNCK_STOCK_MENU          "wnck-stock-menu"
#define WNCK_STOCK_MINIMIZE      "wnck-stock-minimize"
#define WNCK_STOCK_MOVE          "wnck-stock-move"
#define WNCK_STOCK_NORMAL        "wnck-stock-normal"
#define WNCK_STOCK_NOTITLEBAR    "wnck-stock-notitlebar"
#define WNCK_STOCK_RAISE         "wnck-stock-raise"
#define WNCK_STOCK_RESIZE        "wnck-stock-resize"
#define WNCK_STOCK_SENDTO_D      "wnck-stock-sendto-d"
#define WNCK_STOCK_SENDTO_L      "wnck-stock-sendto-l"
#define WNCK_STOCK_SENDTO_R      "wnck-stock-sendto-r"
#define WNCK_STOCK_SENDTO_U      "wnck-stock-sendto-u"
#define WNCK_STOCK_SENDTO        "wnck-stock-sendto"
#define WNCK_STOCK_SHADE         "wnck-stock-shade"
#define WNCK_STOCK_STICK         "wnck-stock-stick"
#define WNCK_STOCK_TITLEBAR      "wnck-stock-titlebar"
#define WNCK_STOCK_UNARRANGED    "wnck-stock-unarranged"
#define WNCK_STOCK_UNMAXIMIZE_B  "wnck-stock-unmaximize-b"
#define WNCK_STOCK_UNMAXIMIZE_H  "wnck-stock-unmaximize-h"
#define WNCK_STOCK_UNMAXIMIZE_V  "wnck-stock-unmaximize-v"
#define WNCK_STOCK_UNMAXIMIZE    "wnck-stock-unmaximize"
#define WNCK_STOCK_UNMINIMIZE    "wnck-stock-unminimize"
#define WNCK_STOCK_UNSHADE       "wnck-stock-unshade"
#define WNCK_STOCK_UNSTICK       "wnck-stock-unstick"
#define WNCK_STOCK_MAXIMIZE_L    "wnck-stock-maximize-l"
#define WNCK_STOCK_MAXIMIZE_R    "wnck-stock-maximize-r"
#define WNCK_STOCK_UNMAXIMIZE_L  "wnck-stock-unmaximize-l"
#define WNCK_STOCK_UNMAXIMIZE_R  "wnck-stock-unmaximize-r"

#define WNCK_APP_WINDOW_EVENT_MASK (PropertyChangeMask | StructureNotifyMask)

gboolean _wnck_get_cardinal      (Window  xwindow,
                                  Atom    atom,
                                  int    *val);
int      _wnck_get_wm_state      (Window  xwindow);
gboolean _wnck_get_window        (Window  xwindow,
                                  Atom    atom,
                                  Window *val);
gboolean _wnck_get_pixmap        (Window  xwindow,
                                  Atom    atom,
                                  Pixmap *val);
gboolean _wnck_get_atom          (Window  xwindow,
                                  Atom    atom,
                                  Atom   *val);
char*    _wnck_get_text_property (Window  xwindow,
                                  Atom    atom);
char*    _wnck_get_utf8_property (Window  xwindow,
                                  Atom    atom);
gboolean _wnck_get_window_list   (Window   xwindow,
                                  Atom     atom,
                                  Window **windows,
                                  int     *len);
gboolean _wnck_get_atom_list     (Window   xwindow,
                                  Atom     atom,
                                  Atom   **atoms,
                                  int     *len);
gboolean _wnck_get_cardinal_list (Window   xwindow,
                                  Atom     atom,
                                  gulong **cardinals,
                                  int     *len);
char**   _wnck_get_utf8_list     (Window   xwindow,
                                  Atom     atom);

void     _wnck_set_utf8_list     (Window   xwindow,
                                  Atom     atom,
                                  char   **list);

void _wnck_error_trap_push (void);
int  _wnck_error_trap_pop  (void);

#define _wnck_atom_get(atom_name) gdk_x11_get_xatom_by_name (atom_name)
#define _wnck_atom_name(atom)     gdk_x11_get_xatom_name (atom)

void _wnck_event_filter_init (void);

int   _wnck_xid_equal (gconstpointer v1,
                       gconstpointer v2);
guint _wnck_xid_hash  (gconstpointer v);

void _wnck_iconify   (Window xwindow);
void _wnck_deiconify (Window xwindow);

void _wnck_close     (Screen *screen,
		      Window  xwindow,
		      Time    timestamp);

void _wnck_change_state     (Screen  *screen,
			     Window   xwindow,
                             gboolean add,
                             Atom     state1,
                             Atom     state2);
void _wnck_change_workspace (Screen  *screen,
			     Window   xwindow,
                             int      new_space);
void _wnck_activate         (Screen  *screen,
                             Window   xwindow,
                             Time     timestamp);
void _wnck_activate_workspace (Screen *screen,
                               int     new_active_space,
                               Time    timestamp);
void _wnck_change_viewport (Screen *screen,
			    int     x,
			    int     y);

char*  _wnck_get_session_id     (Window xwindow);
int    _wnck_get_pid            (Window xwindow);
char*  _wnck_get_name           (Window xwindow);
char*  _wnck_get_icon_name      (Window xwindow);
char*  _wnck_get_res_class_utf8 (Window xwindow);
void   _wnck_get_wmclass        (Window xwindow,
                                 char **res_class,
                                 char **res_name);
gboolean _wnck_get_frame_extents  (Window  xwindow,
                                   int    *left_frame,
                                   int    *right_frame,
                                   int    *top_frame,
                                   int    *bottom_frame);

void   _wnck_select_input     (Window xwindow,
                               int    mask);

void   _wnck_keyboard_move    (Screen *screen,
                               Window  xwindow);

void   _wnck_keyboard_size    (Screen *screen,
                               Window  xwindow);

void _wnck_toggle_showing_desktop (Screen  *screen,
                                   gboolean show);

typedef struct _WnckIconCache WnckIconCache;

WnckIconCache *_wnck_icon_cache_new                  (void);
void           _wnck_icon_cache_free                 (WnckIconCache *icon_cache);
void           _wnck_icon_cache_property_changed     (WnckIconCache *icon_cache,
                                                      Atom           atom);
gboolean       _wnck_icon_cache_get_icon_invalidated (WnckIconCache *icon_cache);
void           _wnck_icon_cache_set_want_fallback    (WnckIconCache *icon_cache,
                                                      gboolean       setting);
gboolean       _wnck_icon_cache_get_is_fallback      (WnckIconCache *icon_cache);

gboolean _wnck_read_icons         (Window          xwindow,
                                   WnckIconCache  *icon_cache,
                                   GdkPixbuf     **iconp,
                                   int             ideal_width,
                                   int             ideal_height,
                                   GdkPixbuf     **mini_iconp,
                                   int             ideal_mini_width,
                                   int             ideal_mini_height);
void _wnck_get_fallback_icons (GdkPixbuf     **iconp,
                               int             ideal_width,
                               int             ideal_height,
                               GdkPixbuf     **mini_iconp,
                               int             ideal_mini_width,
                               int             ideal_mini_height);



void _wnck_get_window_geometry (Screen *screen,
				Window  xwindow,
                                int    *xp,
                                int    *yp,
                                int    *widthp,
                                int    *heightp);
void _wnck_set_window_geometry (Screen *screen,
                                Window  xwindow,
                                int     gravity_and_flags,
                                int     x,
                                int     y,
                                int     width,
                                int     height);

void _wnck_get_window_position (Screen *screen,
				Window  xwindow,
                                int    *xp,
                                int    *yp);

void _wnck_set_icon_geometry  (Window xwindow,
			       int    x,
			       int    y,
			       int    width,
			       int    height);

void _wnck_set_desktop_layout (Screen *xscreen,
                               int     rows,
                               int     columns);

GdkPixbuf* _wnck_gdk_pixbuf_get_from_pixmap (GdkPixbuf   *dest,
                                             Pixmap       xpixmap,
                                             int          src_x,
                                             int          src_y,
                                             int          dest_x,
                                             int          dest_y,
                                             int          width,
                                             int          height);

#define WNCK_NO_MANAGER_TOKEN 0

int      _wnck_try_desktop_layout_manager           (Screen *xscreen,
                                                     int     current_token);
void     _wnck_release_desktop_layout_manager       (Screen *xscreen,
                                                     int     current_token);
gboolean _wnck_desktop_layout_manager_process_event (XEvent *xev);

G_END_DECLS

#endif /* WNCK_XUTILS_H */

/**
 * @file buddy_list.h
 *
 * purple
 *
 * Purple is the legal property of its developers, whose names are too numerous
 * to list here.  Please refer to the COPYRIGHT file distributed with this
 * source distribution.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */

#ifndef _QQ_BUDDY_LIST_H_
#define _QQ_BUDDY_LIST_H_

#include <glib.h>
#include "connection.h"

#include "qq.h"
typedef struct _qq_buddy_status {
	guint32 uid;
	guint8 flag1;
	struct in_addr ip;
	guint16 port;
	guint8 flag2;
	guint8 status;
	guint16 version;
	guint8 key[QQ_KEY_LENGTH];
	guint16 unknown;
	guint8 ext_flag;
	guint8 comm_flag;
} qq_buddy_status;

typedef struct _qq_buddy_group {
	guint32 uid;
	guint8 group_id;
} qq_buddy_group;

typedef struct _qq_group {
	guint8 group_id;
	gchar * group_name;
} qq_group;

void qq_request_get_buddies_online(PurpleConnection *gc, guint8 position, guint32 update_class);
guint8 qq_process_get_buddies_online(guint8 *data, gint data_len, PurpleConnection *gc);

void qq_request_get_buddies_list(PurpleConnection *gc, guint16 position, guint32 update_class);
guint16 qq_process_get_buddies_list(guint8 *data, gint data_len, PurpleConnection *gc);

void qq_request_get_rooms(PurpleConnection *gc, guint32 position, guint32 update_class);
guint32 qq_process_get_buddies_and_rooms(guint8 *data, gint data_len, PurpleConnection *gc);

void qq_request_change_status(PurpleConnection *gc, guint32 update_class);
void qq_process_change_status(guint8 *data, gint data_len, PurpleConnection *gc);
void qq_process_buddy_change_status(guint8 *data, gint data_len, PurpleConnection *gc);

void qq_update_buddies_status(PurpleConnection *gc);
void qq_update_buddy_status(PurpleConnection *gc, guint32 uid, guint8 status, guint8 flag);
void qq_buddy_data_free_all(PurpleConnection *gc);
guint32 qq_process_get_group_list(guint8 *data, gint data_len, PurpleConnection *gc);
void qq_request_get_group_list(PurpleConnection *gc, guint16 position, guint32 update_class);
#endif

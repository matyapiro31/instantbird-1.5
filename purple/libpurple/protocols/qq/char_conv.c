/**
 * @file char_conv.c
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

#include "internal.h"
#include "debug.h"

#include "char_conv.h"
#include "packet_parse.h"
#include "utils.h"

#define QQ_NULL_MSG           "(NULL)"	/* return this if conversion fails */

/* convert a string from from_charset to to_charset, using g_convert */
/* Warning: do not return NULL */
static gchar *do_convert(const gchar *str, gssize len, gsize *out_len, const gchar *to_charset, const gchar *from_charset)
{
	GError *error = NULL;
	gchar *ret;
	gsize byte_read, byte_write;

	g_return_val_if_fail(str != NULL && to_charset != NULL && from_charset != NULL, g_strdup(QQ_NULL_MSG));

	ret = g_convert(str, len, to_charset, from_charset, &byte_read, &byte_write, &error);

	if (error == NULL) {
		if (out_len)
			*out_len = byte_write;
		return ret;	/* convert is OK */
	}

	/* convert error */
	purple_debug_error("QQ_CONVERT", "%s\n", error->message);
	qq_show_packet("Dump failed text", (guint8 *) str, (len == -1) ? strlen(str) : len);

	g_error_free(error);
	return g_strdup(QQ_NULL_MSG);
}

/*
 * Changed!!!! Check Every Invoke!!!!
 * take the input as a pascal string and return a converted c-string in UTF-8
 * len_size is the size of length bytes in pascal string
 * if from_charset == NULL, will not do the conversion
 * returns the number of bytes read, return -1 if fatal error
 * the converted UTF-8 will be saved in ret
 * Return: *ret != NULL
 */
gint qq_get_vstr( gchar **ret, const gchar *from_charset, gsize len_size, guint8 *data )
{
	guint32 len = 0;
	guint32 tmp = 0;
	gint i;

	g_return_val_if_fail(data != NULL, -1);

	for (i=len_size-1; i>=0; --i) {
		tmp = *((guint8 *)(data+i));
		tmp <<= (len_size-i-1) * 8;
		len ^= tmp;
	}

	if (len) {
		if (from_charset)
		{
			*ret = do_convert((gchar *) (data + len_size), len, NULL, UTF8, from_charset);
		} else {
			*ret = (gchar *)g_malloc0(len+1);
			g_memmove(*ret, data+len_size, len);
		}
	} else {	
		*ret = g_strdup("");
		return 1;
	}
	return len + len_size;
}

gint qq_put_vstr( guint8 *buf, const gchar *str_utf8, gsize len_size, const gchar *to_charset )
{
	gchar *str;
	guint32 len;
	guint i;


	if (str_utf8 == NULL)	len = 0;
	else	{
		len = strlen(str_utf8);

		if (to_charset) {
			str = do_convert(str_utf8, -1, &len, to_charset, UTF8);
			if (len > 0)	g_memmove(buf + len_size, str, len);
		}
		else	g_memmove(buf + len_size, str_utf8, len);
	}
	
	/* TODO: this part not working on BIG ENDIAN */
	for (i=0; i<len_size; ++i)
		buf[i] = *((guint8 *)(&len)+len_size-1-i);

	return len_size + len;
}

/* Warning: do not return NULL */
gchar *utf8_to_qq(const gchar *str, const gchar *to_charset)
{
	return do_convert(str, -1, NULL, to_charset, UTF8);
}

/* Warning: do not return NULL */
gchar *qq_to_utf8(const gchar *str, const gchar *from_charset)
{
	return do_convert(str, -1, NULL, UTF8, from_charset);
}


/**
 * @file prefs.h Prefs API
 * @ingroup core
 */

/* purple
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
 *
 */
#ifndef _PURPLE_PREFS_H_
#define _PURPLE_PREFS_H_

#include <glib.h>

/**
 * Preference data types.
 */
typedef enum _PurplePrefType
{
	PURPLE_PREF_NONE,        /**< No type.         */
	PURPLE_PREF_BOOLEAN,     /**< Boolean.         */
	PURPLE_PREF_INT,         /**< Integer.         */
	PURPLE_PREF_STRING,      /**< String.          */
	/* The 3 following types are unused in libpurple,
	   and not implemented in Instantbird */
	PURPLE_PREF_STRING_LIST, /**< List of strings. */
	PURPLE_PREF_PATH,        /**< Path.            */
	PURPLE_PREF_PATH_LIST    /**< List of paths.   */

} PurplePrefType;

/**
 * The type of callbacks for preference changes.
 *
 * @param name the name of the preference which has changed.
 * @param type the type of the preferenced named @a name
 * @param val  the new value of the preferencs; should be cast to the correct
 *             type.  For instance, to recover the value of a #PURPLE_PREF_INT
 *             preference, use <tt>GPOINTER_TO_INT(val)</tt>.  Alternatively,
 *             just call purple_prefs_get_int(), purple_prefs_get_string_list()
 *             etc.
 * @param data Arbitrary data specified when the callback was connected with
 *             purple_prefs_connect_callback().
 *
 * @see purple_prefs_connect_callback()
 */
typedef void (*PurplePrefCallback) (const char *name, PurplePrefType type,
		gconstpointer val, gpointer data);


/** @copydoc _PurplePrefsUiOps */
typedef struct _PurplePrefsUiOps PurplePrefsUiOps;


/**  Prefs UI operations
 */
struct _PurplePrefsUiOps
{
	void (*add_none)(const char *name);
	void (*add_bool)(const char *name, gboolean value);
	void (*add_int)(const char *name, int value);
	void (*add_string)(const char *name, const char *value);

	void (*set_bool)(const char *name, gboolean value);
	void (*set_int)(const char *name, int value);
	void (*set_string)(const char *name, const char *value);

	gboolean (*get_bool)(const char *name);
	int (*get_int)(const char *name);
	const char *(*get_string)(const char *name);

	PurplePrefType (*get_type)(const char *name);
	GList *(*get_children_names)(const char *name);

	gboolean (*exists)(const char *name);
	void (*remove)(const char *name);

	void (*save)(void);

	void *(*add_observer)(const char *name, gpointer data);
	void (*remove_observer)(const char *name, void *observer);

	void (*_purple_reserved1)(void);
	void (*_purple_reserved2)(void);
	void (*_purple_reserved3)(void);
	void (*_purple_reserved4)(void);
};


#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************/
/** @name UI Registration Functions                                       */
/**************************************************************************/
/*@{*/
/**
 * Sets the UI operations structure to be used for preferences.
 *
 * @param ops The UI operations structure.
 */
void purple_prefs_set_ui_ops(PurplePrefsUiOps *ops);

/**
 * Returns the UI operations structure used for preferences.
 *
 * @return The UI operations structure in use.
 */
PurplePrefsUiOps *purple_prefs_get_ui_ops(void);

/*@}*/

/**************************************************************************/
/** @name Prefs API
    Preferences are named according to a directory-like structure.
    Example: "/plugins/core/potato/is_from_idaho" (probably a boolean)    */
/**************************************************************************/
/*@{*/

/**
 * Returns the prefs subsystem handle.
 *
 * @return The prefs subsystem handle.
 */
void *purple_prefs_get_handle(void);

/**
 * Initialize core prefs
 */
void purple_prefs_init(void);

/**
 * Uninitializes the prefs subsystem.
 */
void purple_prefs_uninit(void);

/**
 * Add a new typeless pref.
 *
 * @param name  The name of the pref
 */
void purple_prefs_add_none(const char *name);

/**
 * Add a new boolean pref.
 *
 * @param name  The name of the pref
 * @param value The initial value to set
 */
void purple_prefs_add_bool(const char *name, gboolean value);

/**
 * Add a new integer pref.
 *
 * @param name  The name of the pref
 * @param value The initial value to set
 */
void purple_prefs_add_int(const char *name, int value);

/**
 * Add a new string pref.
 *
 * @param name  The name of the pref
 * @param value The initial value to set
 */
void purple_prefs_add_string(const char *name, const char *value);

/**
 * Remove a pref.
 *
 * @param name The name of the pref
 */
void purple_prefs_remove(const char *name);

/**
 * Set boolean pref value
 *
 * @param name  The name of the pref
 * @param value The value to set
 */
void purple_prefs_set_bool(const char *name, gboolean value);

/**
 * Set integer pref value
 *
 * @param name  The name of the pref
 * @param value The value to set
 */
void purple_prefs_set_int(const char *name, int value);

/**
 * Set string pref value
 *
 * @param name  The name of the pref
 * @param value The value to set
 */
void purple_prefs_set_string(const char *name, const char *value);


/**
 * Check if a pref exists
 *
 * @param name The name of the pref
 * @return TRUE if the pref exists.  Otherwise FALSE.
 */
gboolean purple_prefs_exists(const char *name);

/**
 * Get pref type
 *
 * @param name The name of the pref
 * @return The type of the pref
 */
PurplePrefType purple_prefs_get_type(const char *name);

/**
 * Get boolean pref value
 *
 * @param name The name of the pref
 * @return The value of the pref
 */
gboolean purple_prefs_get_bool(const char *name);

/**
 * Get integer pref value
 *
 * @param name The name of the pref
 * @return The value of the pref
 */
int purple_prefs_get_int(const char *name);

/**
 * Get string pref value
 *
 * @param name The name of the pref
 * @return The value of the pref
 */
const char *purple_prefs_get_string(const char *name);

/**
 * Returns a list of children for a pref
 *
 * @param name The parent pref
 * @return A list of newly allocated strings denoting the names of the children.
 *         Returns @c NULL if there are no children or if pref doesn't exist.
 *         The caller must free all the strings and the list.
 *
 * @since 2.1.0
 */
GList *purple_prefs_get_children_names(const char *name);

/**
 * Add a callback to a pref (and its children)
 *
 * @param handle   The handle of the receiver.
 * @param name     The name of the preference
 * @param cb       The callback function
 * @param data     The data to pass to the callback function.
 *
 * @return An id to disconnect the callback
 *
 * @see purple_prefs_disconnect_callback
 */
guint purple_prefs_connect_callback(void *handle, const char *name, PurplePrefCallback cb,
		gpointer data);

/**
 * Call the callback of the observer
 */
void purple_prefs_observe(gpointer data);

/**
 * Remove a callback to a pref
 */
void purple_prefs_disconnect_callback(guint callback_id);

/**
 * Remove all pref callbacks by handle
 */
void purple_prefs_disconnect_by_handle(void *handle);

/**
 * Trigger callbacks as if the pref changed
 */
void purple_prefs_trigger_callback(const char *name);

/**
 * Read preferences
 */
gboolean purple_prefs_load(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _PURPLE_PREFS_H_ */
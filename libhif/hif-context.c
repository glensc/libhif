/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2014 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

/**
 * SECTION:hif-context
 * @short_description: High level interface to libhif.
 * @include: libhif.h
 * @stability: Stable
 *
 * This object is a high level interface that does not allow the the user
 * to use objects from librepo, rpm or hawkey directly.
 */

#include "config.h"

#include <rpm/rpmlib.h>

#include "hif-context.h"
#include "hif-utils.h"

typedef struct _HifContextPrivate	HifContextPrivate;
struct _HifContextPrivate
{
	gchar			*repo_dir;
	gchar			*base_arch;
	gchar			*release_ver;
	gchar			*cache_dir;
	gchar			*os_info;
	gchar			*arch_info;
	gchar			*rpm_verbosity;
	gboolean		 check_disk_space;
	gboolean		 check_transaction;
	gboolean		 keep_cache;
};

G_DEFINE_TYPE_WITH_PRIVATE (HifContext, hif_context, G_TYPE_OBJECT)

#define GET_PRIVATE(o) (hif_context_get_instance_private (o))

/**
 * hif_context_finalize:
 **/
static void
hif_context_finalize (GObject *object)
{
	HifContext *context = HIF_CONTEXT (object);
	HifContextPrivate *priv = GET_PRIVATE (context);

	g_free (priv->repo_dir);
	g_free (priv->base_arch);
	g_free (priv->release_ver);
	g_free (priv->cache_dir);
	g_free (priv->rpm_verbosity);
	g_free (priv->os_info);
	g_free (priv->arch_info);

	G_OBJECT_CLASS (hif_context_parent_class)->finalize (object);
}

/**
 * hif_context_init:
 **/
static void
hif_context_init (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	priv->check_disk_space = TRUE;
	priv->check_transaction = TRUE;
}

/**
 * hif_context_class_init:
 **/
static void
hif_context_class_init (HifContextClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = hif_context_finalize;
}

/**
 * hif_context_get_repo_dir:
 * @context: a #HifContext instance.
 *
 * Gets the context ID.
 *
 * Returns: the context ID, e.g. "fedora-updates"
 *
 * Since: 0.1.0
 **/
const gchar *
hif_context_get_repo_dir (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	return priv->repo_dir;
}

/**
 * hif_context_get_base_arch:
 * @context: a #HifContext instance.
 *
 * Gets the context ID.
 *
 * Returns: the base architecture, e.g. "x86_64"
 *
 * Since: 0.1.0
 **/
const gchar *
hif_context_get_base_arch (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	return priv->base_arch;
}

/**
 * hif_context_get_os_info:
 * @context: a #HifContext instance.
 *
 * Gets the OS info.
 *
 * Returns: the OS info, e.g. "Linux"
 *
 * Since: 0.1.0
 **/
const gchar *
hif_context_get_os_info (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	return priv->os_info;
}

/**
 * hif_context_get_arch_info:
 * @context: a #HifContext instance.
 *
 * Gets the architecture info.
 *
 * Returns: the architecture info, e.g. "x86_64"
 *
 * Since: 0.1.0
 **/
const gchar *
hif_context_get_arch_info (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	return priv->arch_info;
}

/**
 * hif_context_get_release_ver:
 * @context: a #HifContext instance.
 *
 * Gets the context ID.
 *
 * Returns: the context ID, e.g. "fedora-updates"
 *
 * Since: 0.1.0
 **/
const gchar *
hif_context_get_release_ver (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	return priv->release_ver;
}

/**
 * hif_context_get_cache_dir:
 * @context: a #HifContext instance.
 *
 * Gets the context ID.
 *
 * Returns: the context ID, e.g. "fedora-updates"
 *
 * Since: 0.1.0
 **/
const gchar *
hif_context_get_cache_dir (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	return priv->cache_dir;
}

/**
 * hif_context_get_rpm_verbosity:
 * @context: a #HifContext instance.
 *
 * Gets the RPM verbosity string.
 *
 * Returns: the verbosity string, e.g. "info"
 *
 * Since: 0.1.0
 **/
const gchar *
hif_context_get_rpm_verbosity (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	return priv->rpm_verbosity;
}

/**
 * hif_context_get_check_disk_space:
 * @context: a #HifContext instance.
 *
 * Gets the diskspace check value.
 *
 * Returns: %TRUE if diskspace should be checked before the transaction
 *
 * Since: 0.1.0
 **/
gboolean
hif_context_get_check_disk_space (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	return priv->check_disk_space;
}

/**
 * hif_context_get_check_transaction:
 * @context: a #HifContext instance.
 *
 * Gets the test transaction value. A test transaction shouldn't be required
 * with hawkey and it takes extra time to complete, but bad things happen
 * if hawkey ever gets this wrong.
 *
 * Returns: %TRUE if a test transaction should be done
 *
 * Since: 0.1.0
 **/
gboolean
hif_context_get_check_transaction (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	return priv->check_transaction;
}

/**
 * hif_context_get_keep_cache:
 * @context: a #HifContext instance.
 *
 * Gets if the downloaded packages are kept.
 *
 * Returns: %TRUE if the packages will not be deleted
 *
 * Since: 0.1.0
 **/
gboolean
hif_context_get_keep_cache (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	return priv->keep_cache;
}

/**
 * hif_context_set_repo_dir:
 * @context: a #HifContext instance.
 * @repo_dir: the repodir, e.g. "/etc/yum.repos.d"
 *
 * Sets the repo directory.
 *
 * Since: 0.1.0
 **/
void
hif_context_set_repo_dir (HifContext *context, const gchar *repo_dir)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	g_free (priv->repo_dir);
	priv->repo_dir = g_strdup (repo_dir);
}

/**
 * hif_context_set_release_ver:
 * @context: a #HifContext instance.
 * @release_ver: the release version, e.g. "20"
 *
 * Sets the release version.
 *
 * Since: 0.1.0
 **/
void
hif_context_set_release_ver (HifContext *context, const gchar *release_ver)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	g_free (priv->release_ver);
	priv->release_ver = g_strdup (release_ver);
}

/**
 * hif_context_set_cache_dir:
 * @context: a #HifContext instance.
 * @cache_dir: the cachedir, e.g. "/var/cache/PackageKit"
 *
 * Sets the cache directory.
 *
 * Since: 0.1.0
 **/
void
hif_context_set_cache_dir (HifContext *context, const gchar *cache_dir)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	g_free (priv->cache_dir);
	priv->cache_dir = g_strdup (cache_dir);
}

/**
 * hif_context_set_rpm_verbosity:
 * @context: a #HifContext instance.
 * @rpm_verbosity: the verbosity string, e.g. "info"
 *
 * Sets the RPM verbosity string.
 *
 * Since: 0.1.0
 **/
void
hif_context_set_rpm_verbosity (HifContext *context, const gchar *rpm_verbosity)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	g_free (priv->rpm_verbosity);
	priv->rpm_verbosity = g_strdup (rpm_verbosity);
}

/**
 * hif_context_set_check_disk_space:
 * @context: a #HifContext instance.
 * @check_disk_space: %TRUE to check for diskspace
 *
 * Enables or disables the diskspace check.
 *
 * Since: 0.1.0
 **/
void
hif_context_set_check_disk_space (HifContext *context, gboolean check_disk_space)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	priv->check_disk_space = check_disk_space;
}

/**
 * hif_context_set_check_transaction:
 * @context: a #HifContext instance.
 * @check_transaction: %TRUE to do a test transaction
 *
 * Enables or disables the test transaction.
 *
 * Since: 0.1.0
 **/
void
hif_context_set_check_transaction (HifContext *context, gboolean check_transaction)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	priv->check_transaction = check_transaction;
}

/**
 * hif_context_set_keep_cache:
 * @context: a #HifContext instance.
 * @keep_cache: %TRUE keep the packages after installing or updating
 *
 * Enables or disables the automatic package deleting functionality.
 *
 * Since: 0.1.0
 **/
void
hif_context_set_keep_cache (HifContext *context, gboolean keep_cache)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	priv->keep_cache = keep_cache;
}

/**
 * hif_context_set_os_release:
 **/
static gboolean
hif_context_set_os_release (HifContext *context, GError **error)
{
	gboolean ret;
	gchar *contents = NULL;
	gchar *version = NULL;
	GKeyFile *key_file = NULL;
	GString *str = NULL;

	/* make a valid GKeyFile from the .ini data by prepending a header */
	ret = g_file_get_contents ("/etc/os-release", &contents, NULL, NULL);
	if (!ret)
		goto out;
	str = g_string_new (contents);
	g_string_prepend (str, "[os-release]\n");
	key_file = g_key_file_new ();
	ret = g_key_file_load_from_data (key_file,
					 str->str, -1,
					 G_KEY_FILE_NONE,
					 error);
	if (!ret)
		goto out;

	/* get keys */
	version = g_key_file_get_string (key_file,
					 "os-release",
					 "VERSION_ID",
					 error);
	if (version == NULL)
		goto out;
	hif_context_set_release_ver (context, version);
out:
	if (key_file != NULL)
		g_key_file_free (key_file);
	if (str != NULL)
		g_string_free (str, TRUE);
	g_free (version);
	g_free (contents);
	return ret;
}

/**
 * hif_context_setup:
 * @context: a #HifContext instance.
 * @error: A #GError or %NULL
 *
 * Sets up the context ready for use
 *
 * Returns: %TRUE for success, %FALSE otherwise
 *
 * Since: 0.1.0
 **/
gboolean
hif_context_setup (HifContext *context, GError **error)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	const gchar *value;
	gboolean ret = TRUE;
	gint retval;

	retval = rpmReadConfigFiles (NULL, NULL);
	if (retval != 0) {
		ret = FALSE;
		g_set_error_literal (error,
				     HIF_ERROR,
				     HIF_ERROR_INTERNAL_ERROR,
				     "failed to read rpm config files");
		goto out;
	}

	/* get info from RPM */
	rpmGetOsInfo (&value, NULL);
	priv->os_info = g_strdup (value);
	rpmGetArchInfo (&value, NULL);
	priv->arch_info = g_strdup (value);
	if (g_strcmp0 (value, "i486") == 0 ||
	    g_strcmp0 (value, "i586") == 0 ||
	    g_strcmp0 (value, "i686") == 0) {
		value = "i386";
	} else if (g_strcmp0 (value, "armv7l") == 0 ||
		   g_strcmp0 (value, "armv6l") == 0 ||
		   g_strcmp0 (value, "armv5tejl") == 0 ||
		   g_strcmp0 (value, "armv5tel") == 0) {
		value = "arm";
	} else if (g_strcmp0 (value, "armv7hnl") == 0 ||
		 g_strcmp0 (value, "armv7hl") == 0) {
		value = "armhfp";
	}
	priv->base_arch = g_strdup (value);

	/* get info from OS release file */
	ret = hif_context_set_os_release (context, error);
	if (!ret)
		goto out;
out:
	return ret;
}

/**
 * hif_context_new:
 *
 * Creates a new #HifContext.
 *
 * Returns: (transfer full): a #HifContext
 *
 * Since: 0.1.0
 **/
HifContext *
hif_context_new (void)
{
	HifContext *context;
	context = g_object_new (HIF_TYPE_CONTEXT, NULL);
	return HIF_CONTEXT (context);
}
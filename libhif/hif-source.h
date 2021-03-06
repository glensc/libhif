/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2013-2014 Richard Hughes <richard@hughsie.com>
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

#if !defined (__LIBHIF_H) && !defined (HIF_COMPILATION)
#error "Only <libhif.h> can be included directly."
#endif

#ifndef __HIF_SOURCE_H
#define __HIF_SOURCE_H

#include <glib-object.h>

#include <hawkey/repo.h>
#include <hawkey/package.h>

#include "hif-context.h"
#include "hif-state.h"

#define HIF_TYPE_SOURCE			(hif_source_get_type())
#define HIF_SOURCE(obj)			(G_TYPE_CHECK_INSTANCE_CAST((obj), HIF_TYPE_SOURCE, HifSource))
#define HIF_SOURCE_CLASS(cls)		(G_TYPE_CHECK_CLASS_CAST((cls), HIF_TYPE_SOURCE, HifSourceClass))
#define HIF_IS_SOURCE(obj)		(G_TYPE_CHECK_INSTANCE_TYPE((obj), HIF_TYPE_SOURCE))
#define HIF_IS_SOURCE_CLASS(cls)	(G_TYPE_CHECK_CLASS_TYPE((cls), HIF_TYPE_SOURCE))
#define HIF_SOURCE_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), HIF_TYPE_SOURCE, HifSourceClass))

G_BEGIN_DECLS

typedef struct _HifSource		HifSource;
typedef struct _HifSourceClass		HifSourceClass;

struct _HifSource
{
	GObject			parent;
};

struct _HifSourceClass
{
	GObjectClass		parent_class;
	/*< private >*/
	void (*_hif_reserved1)	(void);
	void (*_hif_reserved2)	(void);
	void (*_hif_reserved3)	(void);
	void (*_hif_reserved4)	(void);
	void (*_hif_reserved5)	(void);
	void (*_hif_reserved6)	(void);
	void (*_hif_reserved7)	(void);
	void (*_hif_reserved8)	(void);
};

/**
 * HifSourceUpdateFlags:
 * @HIF_SOURCE_UPDATE_FLAG_NONE:		No flags set
 * @HIF_SOURCE_UPDATE_FLAG_FORCE:		Force the source to be updated
 *
 * The update flags.
 **/
typedef enum {
	HIF_SOURCE_UPDATE_FLAG_NONE		= 0,
	HIF_SOURCE_UPDATE_FLAG_FORCE		= 1,
	/*< private >*/
	HIF_SOURCE_UPDATE_FLAG_LAST
} HifSourceUpdateFlags;

/**
 * HifSourceKind:
 * @HIF_SOURCE_KIND_REMOTE:			A remote repo
 * @HIF_SOURCE_KIND_MEDIA:			A media repo, e.g. a DVD
 *
 * The source kind.
 **/
typedef enum {
	HIF_SOURCE_KIND_REMOTE,
	HIF_SOURCE_KIND_MEDIA,
	/*< private >*/
	HIF_SOURCE_KIND_LAST
} HifSourceKind;

GType		 hif_source_get_type		(void);
HifSource	*hif_source_new			(HifContext		*context);

/* getters */
const gchar	*hif_source_get_id		(HifSource		*source);
const gchar	*hif_source_get_location	(HifSource		*source);
const gchar	*hif_source_get_filename	(HifSource		*source);
const gchar	*hif_source_get_packages	(HifSource		*source);
gboolean	 hif_source_get_enabled		(HifSource		*source);
guint		 hif_source_get_cost		(HifSource		*source);
HifSourceKind	 hif_source_get_kind		(HifSource		*source);
gboolean	 hif_source_get_gpgcheck	(HifSource		*source);
gchar		*hif_source_get_description	(HifSource		*source);
HyRepo		 hif_source_get_repo		(HifSource		*source);
gboolean	 hif_source_is_devel		(HifSource		*source);
gboolean	 hif_source_is_source		(HifSource		*source);
gboolean	 hif_source_is_supported	(HifSource		*source);

/* setters */
void		 hif_source_set_id		(HifSource		*source,
						 const gchar		*id);
void		 hif_source_set_location	(HifSource		*source,
						 const gchar		*location);
void		 hif_source_set_location_tmp	(HifSource		*source,
						 const gchar		*location_tmp);
void		 hif_source_set_filename	(HifSource		*source,
						 const gchar		*filename);
void		 hif_source_set_packages	(HifSource		*source,
						 const gchar		*packages);
void		 hif_source_set_packages_tmp	(HifSource		*source,
						 const gchar		*packages_tmp);
void		 hif_source_set_enabled		(HifSource		*source,
						 gboolean		 enabled);
void		 hif_source_set_cost		(HifSource		*source,
						 guint			 cost);
void		 hif_source_set_kind		(HifSource		*source,
						 HifSourceKind		 kind);
void		 hif_source_set_gpgcheck	(HifSource		*source,
						 gboolean		 gpgcheck);
void		 hif_source_set_keyfile		(HifSource		*source,
						 GKeyFile		*keyfile);
gboolean	 hif_source_setup		(HifSource		*source,
						 GError			**error);

/* object methods */
gboolean	 hif_source_check		(HifSource		*source,
						 guint			 permissible_cache_age,
						 HifState		*state,
						 GError			**error);
gboolean	 hif_source_update		(HifSource		*source,
						 HifSourceUpdateFlags	 flags,
						 HifState		*state,
						 GError			**error);
gboolean	 hif_source_clean		(HifSource		*source,
						 GError			**error);
gboolean	 hif_source_set_data		(HifSource		*source,
						 const gchar		*parameter,
						 const gchar		*value,
						 GError			**error);
gchar		*hif_source_download_package	(HifSource		*source,
						 HyPackage		 pkg,
						 const gchar		*directory,
						 HifState		*state,
						 GError			**error);

G_END_DECLS

#endif /* __HIF_SOURCE_H */

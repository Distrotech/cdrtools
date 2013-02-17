/* @(#)hostname.h	1.18 09/07/28 Copyright 1995-2008 J. Schilling */
/*
 *	This file has been separated from libport.h in order to avoid
 *	to include netdb.h in case gethostname() is not needed.
 *
 *	Copyright (c) 1995-2008 J. Schilling
 */
/*
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * See the file CDDL.Schily.txt in this distribution for details.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file CDDL.Schily.txt from this distribution.
 */


#ifndef _SCHILY_HOSTNAME_H
#define	_SCHILY_HOSTNAME_H

#ifndef	_SCHILY_MCONFIG_H
#include <schily/mconfig.h>
#endif
#ifndef _SCHILY_TYPES_H
#include <schily/types.h>
#endif

/*
 * Try to get HOST_NAME_MAX for gethostname() from unistd.h or limits.h
 */
#ifndef _SCHILY_UNISTD_H
#include <schily/unistd.h>
#endif
#ifndef _SCHILY_LIMITS_H
#include <schily/limits.h>
#endif

#ifndef HOST_NAME_MAX
#if	defined(HAVE_NETDB_H) && !defined(HOST_NOT_FOUND) && \
				!defined(_INCL_NETDB_H)
#include <netdb.h>		/* #defines MAXHOSTNAMELEN */
#define	_INCL_NETDB_H
#endif
#ifdef	MAXHOSTNAMELEN
#define	HOST_NAME_MAX	MAXHOSTNAMELEN
#endif
#endif

#ifndef HOST_NAME_MAX
#ifndef	_SCHILY_PARAM_H
#include <schily/param.h>	/* Include various defs needed with some OS */
#endif				/* Linux MAXHOSTNAMELEN */
#ifdef	MAXHOSTNAMELEN
#define	HOST_NAME_MAX	MAXHOSTNAMELEN
#endif
#endif

#ifndef HOST_NAME_MAX
#define	HOST_NAME_MAX	255
#endif
#ifndef	MAXHOSTNAMELEN
#define	MAXHOSTNAMELEN	HOST_NAME_MAX
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef	HAVE_GETHOSTNAME
extern	int		gethostname	__PR((char *name, int namelen));
#endif
#ifndef	HAVE_GETDOMAINNAME
extern	int		getdomainname	__PR((char *name, int namelen));
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _SCHILY_HOSTNAME_H */

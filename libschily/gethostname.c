/* @(#)gethostname.c	1.20 09/08/04 Copyright 1995-2009 J. Schilling */
#include <schily/mconfig.h>
#ifndef lint
static	UConst char sccsid[] =
	"@(#)gethostname.c	1.20 09/08/04 Copyright 1995-2009 J. Schilling";
#endif
/*
 *	Copyright (c) 1995-2009 J. Schilling
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

#include <schily/standard.h>
#include <schily/stdlib.h>
#include <schily/systeminfo.h>
#include <schily/hostname.h>

#ifndef	HAVE_GETHOSTNAME
EXPORT	int	gethostname	__PR((char *name, int namelen));


#ifdef	SI_HOSTNAME

EXPORT int
gethostname(name, namelen)
	char	*name;
	int	namelen;
{
	if (sysinfo(SI_HOSTNAME, name, namelen) < 0)
		return (-1);
	return (0);
}
#else

#ifdef	HAVE_UNAME
#include <schily/utsname.h>
#include <schily/string.h>

EXPORT int
gethostname(name, namelen)
	char	*name;
	int	namelen;
{
	struct utsname	uts;

	if (uname(&uts) < 0)
		return (-1);

	strncpy(name, uts.nodename, namelen);
	return (0);
}
#else
#include <schily/errno.h>

EXPORT int
gethostname(name, namelen)
	char	*name;
	int	namelen;
{
	if (namelen < 0) {
		seterrno(EINVAL);
		return (-1);
	}
	if (namelen > 0)
		name[0] = '\0';
	return (0);
}
#endif

#endif

#endif	/* HAVE_GETHOSTNAME */

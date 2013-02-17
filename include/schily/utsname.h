/* @(#)utsname.h	1.1 09/07/13 Copyright 2009 J. Schilling */
/*
 *	Utsname abstraction
 *
 *	Copyright (c) 2009 J. Schilling
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

#ifndef	_SCHILY_UTSNAME_H
#define	_SCHILY_UTSNAME_H

#ifndef _SCHILY_MCONFIG_H
#include <schily/mconfig.h>
#endif

/*
 * NeXT Step has sys/utsname but not uname()
 */
#ifdef	HAVE_SYS_UTSNAME_H
#ifndef	_INCL_SYS_UTSNAME_H
#define	_INCL_SYS_UTSNAME_H
#include <sys/utsname.h>
#endif
#endif

#endif	/* _SCHILY_UTSNAME_H */

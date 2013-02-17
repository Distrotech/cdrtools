/* @(#)stdio.h	1.2 09/04/08 Copyright 2009 J. Schilling */
/*
 *	Abstraction from stdio.h
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

#ifndef _SCHILY_STDIO_H
#define	_SCHILY_STDIO_H

#ifndef	_SCHILY_MCONFIG_H
#include <schily/mconfig.h>
#endif

#ifndef _INCL_STDIO_H
#include <stdio.h>
#define	_INCL_STDIO_H
#endif

#ifdef	HAVE_LARGEFILES
/*
 * If HAVE_LARGEFILES is defined, it is guaranteed that fseeko()/ftello()
 * both are available.
 */
#define	fseek	fseeko
#define	ftell	ftello
#else	/* !HAVE_LARGEFILES */

/*
 * If HAVE_LARGEFILES is not defined, we depend on specific tests for
 * fseeko()/ftello() which must have been done before the tests for
 * Large File support have been done.
 * Note that this only works if the tests used below are really done before
 * the Large File autoconf test is run. This is because autoconf does no
 * clean testing but instead cumulatively modifes the envivonment used for
 * testing.
 */
#ifdef	HAVE_FSEEKO
#	define	fseek	fseeko
#endif
#ifdef	HAVE_FTELLO
#	define	ftell	ftello
#endif
#endif

#endif	/* _SCHILY_STDIO_H */

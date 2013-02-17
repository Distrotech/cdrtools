/* @(#)align.h	1.7 09/06/06 Copyright 1995-2009 J. Schilling */
/*
 *	Platform dependent definitions for aligning data.
 *
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

/*
 *	The automatically created included file defines the following macros:
 *
 *	saligned(a)	One parameter aligned for a "short int"
 *	s2aligned(a, b)	Both parameters aligned for a "short int"
 *	ialigned(a)	One parameter aligned for a "int"
 *	i2aligned(a, b)	Both parameters aligned for a "int"
 *	laligned(a)	One parameter aligned for a "long"
 *	l2aligned(a, b)	Both parameters aligned for a "long"
 *	llaligned(a)	One parameter aligned for a "long long"
 *	ll2aligned(a, b) Both parameters aligned for a "long long"
 *	faligned(a)	One parameter aligned for a "float"
 *	f2aligned(a, b)	Both parameters aligned for a "float"
 *	daligned(a)	One parameter aligned for a "double"
 *	d2aligned(a, b)	Both parameters aligned for a "double"
 *	paligned(a)	One parameter aligned for a "pointer"
 *	p2aligned(a, b)	Both parameters aligned for a "pointe"
 *
 *	salign(x)	Align for a "short int"
 *	ialign(x)	Align for a "int"
 *	lalign(x)	Align for a "long"
 *	llalign(x)	Align for a "long long"
 *	falign(x)	Align for a "float"
 *	dalign(x)	Align for a "double"
 *	palign(x)	Align for a "pointer"
 */
#ifndef _SCHILY_ALIGN_H
#define	_SCHILY_ALIGN_H

#ifndef _SCHILY_MCONFIG_H
#include <schily/mconfig.h>
#endif

#ifndef	_SCHILY_UTYPES_H
#include <schily/utypes.h>
#endif

#ifdef	SCHILY_BUILD	/* #defined by Schily makefile system */
	/*
	 * Include $(SRCROOT)/incs/$(OARCH)/align.h via
	 * -I$(SRCROOT)/incs/$(OARCH)/
	 */
#	include <align.h>
#else	/* !SCHILY_BUILD */
/*
 * The stuff for static compilation. Include files from a previous
 * dynamic autoconfiguration.
 */
#ifdef	__SUNOS5_SPARC_CC32
#include <schily/sparc-sunos5-cc/align.h>
#define	__JS_ARCH_ALIGN_INCL
#endif
#ifdef	__SUNOS5_SPARC_CC64
#include <schily/sparc-sunos5-cc64/align.h>
#define	__JS_ARCH_ALIGN_INCL
#endif
#ifdef	__SUNOS5_SPARC_GCC32
#include <schily/sparc-sunos5-gcc/align.h>
#define	__JS_ARCH_ALIGN_INCL
#endif
#ifdef	__SUNOS5_SPARC_GCC64
#include <schily/sparc-sunos5-gcc64/align.h>
#define	__JS_ARCH_ALIGN_INCL
#endif
#ifdef	__SUNOS5_X86_CC32
#include <schily/i386-sunos5-cc/align.h>
#define	__JS_ARCH_ALIGN_INCL
#endif
#ifdef	__SUNOS5_X86_CC64
#include <schily/i386-sunos5-cc64/align.h>
#define	__JS_ARCH_ALIGN_INCL
#endif
#ifdef	__SUNOS5_X86_GCC32
#include <schily/i386-sunos5-gcc/align.h>
#define	__JS_ARCH_ALIGN_INCL
#endif
#ifdef	__SUNOS5_X86_GCC64
#include <schily/i386-sunos5-gcc64/align.h>
#define	__JS_ARCH_ALIGN_INCL
#endif

#ifdef	__HPUX_HPPA_CC32
#include <schily/hppa-hp-ux-cc/align.h>
#define	__JS_ARCH_CONF_INCL
#endif
#ifdef	__HPUX_HPPA_CC64
#include <schily/hppa-hp-ux-cc64/align.h>
#define	__JS_ARCH_CONF_INCL
#endif
#ifdef	__HPUX_HPPA_GCC32
#include <schily/hppa-hp-ux-gcc/align.h>
#define	__JS_ARCH_CONF_INCL
#endif
#ifdef	__HPUX_HPPA_GCC64
#include <schily/hppa-hp-ux-gcc64/align.h>
#define	__JS_ARCH_CONF_INCL
#endif

#ifdef	__MSWIN_X86_CL32
#include <schily/i686-cygwin32_nt-cl/align.h>
#define	__JS_ARCH_ALIGN_INCL
#endif

#ifdef	__CYGWIN_X86_GCC
#include <schily/i686-cygwin32_nt-gcc/align.h>
#define	__JS_ARCH_ALIGN_INCL
#endif

#ifndef	__JS_ARCH_ALIGN_INCL
Error unconfigured architecture
#endif

#endif	/* SCHILY_BUILD */

#endif /* _SCHILY_ALIGN_H */

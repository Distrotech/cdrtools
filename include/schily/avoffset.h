/* @(#)avoffset.h	1.7 07/12/01 Copyright 1995-2007 J. Schilling */
/*
 *	Platform dependent definitions for stack scanning.
 *
 *	Copyright (c) 1995-2007 J. Schilling
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
 *	This file includes definitions for STACK_DIRECTION,
 *	AV_OFFSET and FP_INDIR.
 *
 *	STACK_DIRECTION:
 *			+1 -> stack grows to larger addresses
 *			-1 -> stack "groes" to lower addresses
 *
 *	FP_INDIR:	the number of fp chain elements above 'main'.
 *
 *	AV_OFFSET:	the offset of &av[0] relative to the frame pointer
 *			in 'main'.
 *
 *	If getav0() does not work on a specific architecture
 *	the program which generated this automaticly generated include file
 *	may dump core. In this case, the generated include file does not include
 *	definitions for AV_OFFSET and FP_INDIR but ends after the STACK_DIRECTION
 *	definition.
 *	If AV_OFFSET or FP_INDIR are missing in the file, all code
 *	that use the definitions are automatically disabled.
 */
#ifndef _SCHILY_AVOFFSET_H
#define	_SCHILY_AVOFFSET_H

#ifndef _SCHILY_MCONFIG_H
#include <schily/mconfig.h>
#endif

#ifdef	SCHILY_BUILD	/* #defined by Schily makefile system */
	/*
	 * Include $(SRCROOT)/incs/$(OARCH)/avoffset.h via
	 * -I$(SRCROOT)/incs/$(OARCH)/
	 */
#	include <avoffset.h>
#else	/* !SCHILY_BUILD */
/*
 * The stuff for static compilation. Include files from a previous
 * dynamic autoconfiguration.
 */
#ifdef	__SUNOS5_SPARC_CC32
#include <schily/sparc-sunos5-cc/avoffset.h>
#define	__JS_ARCH_AVOFFSET_INCL
#endif
#ifdef	__SUNOS5_SPARC_CC64
#include <schily/sparc-sunos5-cc64/avoffset.h>
#define	__JS_ARCH_AVOFFSET_INCL
#endif
#ifdef	__SUNOS5_SPARC_GCC32
#include <schily/sparc-sunos5-gcc/avoffset.h>
#define	__JS_ARCH_AVOFFSET_INCL
#endif
#ifdef	__SUNOS5_SPARC_GCC64
#include <schily/sparc-sunos5-gcc64/avoffset.h>
#define	__JS_ARCH_AVOFFSET_INCL
#endif
#ifdef	__SUNOS5_X86_CC32
#include <schily/i386-sunos5-cc/avoffset.h>
#define	__JS_ARCH_AVOFFSET_INCL
#endif
#ifdef	__SUNOS5_X86_CC64
#include <schily/i386-sunos5-cc64/avoffset.h>
#define	__JS_ARCH_AVOFFSET_INCL
#endif
#ifdef	__SUNOS5_X86_GCC32
#include <schily/i386-sunos5-gcc/avoffset.h>
#define	__JS_ARCH_AVOFFSET_INCL
#endif
#ifdef	__SUNOS5_X86_GCC64
#include <schily/i386-sunos5-gcc64/avoffset.h>
#define	__JS_ARCH_AVOFFSET_INCL
#endif

#ifdef	__HPUX_HPPA_CC32
#include <schily/hppa-hp-ux-cc/avoffset.h>
#define	__JS_ARCH_CONF_INCL
#endif
#ifdef	__HPUX_HPPA_CC64
#include <schily/hppa-hp-ux-cc64/avoffset.h>
#define	__JS_ARCH_CONF_INCL
#endif
#ifdef	__HPUX_HPPA_GCC32
#include <schily/hppa-hp-ux-gcc/avoffset.h>
#define	__JS_ARCH_CONF_INCL
#endif
#ifdef	__HPUX_HPPA_GCC64
#include <schily/hppa-hp-ux-gcc64/avoffset.h>
#define	__JS_ARCH_CONF_INCL
#endif

#ifdef	__MSWIN_X86_CL32
#include <schily/i686-cygwin32_nt-cl/avoffset.h>
#define	__JS_ARCH_AVOFFSET_INCL
#endif

#ifdef	__CYGWIN_X86_GCC
#include <schily/i686-cygwin32_nt-gcc/avoffset.h>
#define	__JS_ARCH_AVOFFSET_INCL
#endif

#ifndef	__JS_ARCH_AVOFFSET_INCL
Error unconfigured architecture
#endif

#endif	/* SCHILY_BUILD */

#endif /* _SCHILY_AVOFFSET_H */

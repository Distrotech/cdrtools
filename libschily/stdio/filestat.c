/* @(#)filestat.c	1.10 06/09/13 Copyright 1985 J. Schilling */
/*
 *	Copyright (c) 1985 J. Schilling
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

#include "schilyio.h"
#include <schily/stat.h>

EXPORT int
filestat(f, stbuf)
	FILE		*f;
	struct stat	*stbuf;
{
	down(f);
	return (fstat(fileno(f), stbuf));
}

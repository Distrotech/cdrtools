/* @(#)fexec.c	1.42 09/11/15 Copyright 1985, 1995-2009 J. Schilling */
/*
 *	Execute a program with stdio redirection
 *
 *	Copyright (c) 1985, 1995-2009 J. Schilling
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

#include <schily/mconfig.h>
#include <schily/stdio.h>
#include <schily/standard.h>
#include <schily/unistd.h>
#include <schily/stdlib.h>
#include <schily/string.h>
#include <schily/varargs.h>
#include <schily/errno.h>
#include <schily/fcntl.h>
#include <schily/dirent.h>
#include <schily/maxpath.h>
#include <schily/schily.h>
#define	VMS_VFORK_OK
#include <schily/vfork.h>

/*
 * Check whether fexec may be implemented...
 */
#if	defined(HAVE_DUP) && (defined(HAVE_DUP2) || defined(F_DUPFD))


#define	MAX_F_ARGS	16

#ifdef	JOS
#define	enofile(t)			((t) == EMISSDIR || \
					(t)  == ENOFILE || \
					(t)  == EISADIR || \
					(t)  == EIOERR)
#else
#define	enofile(t)			((t) == ENOENT || \
					(t)  == ENOTDIR || \
					(t)  == EISDIR || \
					(t)  == EIO)
#endif

#if	defined(IS_MACOS_X) && defined(HAVE_CRT_EXTERNS_H)
/*
 * The MAC OS X linker does not grok "common" varaibles.
 * We need to fetch the address of "environ" using a hack.
 */
#include <crt_externs.h>
#define	environ	*_NSGetEnviron()
#else
extern	char **environ;
#endif

#ifndef	set_child_standard_fds
LOCAL void	 fdcopy __PR((int, int));
LOCAL void	 fdmove __PR((int, int));
#endif
LOCAL const char *chkname __PR((const char *, const char *));
LOCAL const char *getpath __PR((char * const *));

#ifdef	F_GETFD
#define	fd_getfd(fd)		fcntl((fd), F_GETFD, 0)
#else
#define	fd_getfd(fd)
#endif
#ifdef	F_SETFD
#define	fd_setfd(fd, val)	fcntl((fd), F_SETFD, (val));
#else
#define	fd_setfd(fd, val)
#endif

#ifdef	PROTOTYPES
EXPORT int
fexecl(const char *name, FILE *in, FILE *out, FILE *err, const char *arg0, ...)
#else
EXPORT int
fexecl(name, in, out, err, arg0, va_alist)
	char		*name;
	FILE		*in;
	FILE		*out;
	FILE		*err;
	const char	*arg0;
	va_dcl
#endif
{
	va_list	args;
	int	ac = 0;
	char	*xav[MAX_F_ARGS+1];
	char	**av;
const	char	**pav;
	char	*p;
	int	ret;

#ifdef	PROTOTYPES
	va_start(args, arg0);
#else
	va_start(args);
#endif
	if (arg0) {
		ac++;
		while (va_arg(args, char *) != NULL)
			ac++;
	}
	va_end(args);

	if (ac <= MAX_F_ARGS) {
		av = xav;
	} else {
		av = (char **)malloc((ac+1)*sizeof (char *));
		if (av == 0)
			return (-1);
	}
	pav = (const char **)av;

#ifdef	PROTOTYPES
	va_start(args, arg0);
#else
	va_start(args);
#endif
	*pav++ = arg0;
	if (arg0) do {
		p = va_arg(args, char *);
		*pav++ = p;
	} while (p != NULL);
	va_end(args);

	ret = fexecv(name, in, out, err, ac, av);
	if (av != xav)
		free(av);
	return (ret);
}

#ifdef	PROTOTYPES
EXPORT int
fexecle(const char *name, FILE *in, FILE *out, FILE *err, const char *arg0, ...)
#else
EXPORT int
fexecle(name, in, out, err, arg0, va_alist)
	char		*name;
	FILE		*in;
	FILE		*out;
	FILE		*err;
	const char	*arg0;
	va_dcl
#endif
{
	va_list	args;
	int	ac = 0;
	char	*xav[MAX_F_ARGS+1];
	char	**av;
const	char	**pav;
	char	*p;
	char	**env;
	int	ret;

#ifdef	PROTOTYPES
	va_start(args, arg0);
#else
	va_start(args);
#endif
	if (arg0) {
		ac++;
		while (va_arg(args, char *) != NULL)
			ac++;
	}
	env = va_arg(args, char **);
	va_end(args);

	if (ac <= MAX_F_ARGS) {
		av = xav;
	} else {
		av = (char **)malloc((ac+1)*sizeof (char *));
		if (av == 0)
			return (-1);
	}
	pav = (const char **)av;

#ifdef	PROTOTYPES
	va_start(args, arg0);
#else
	va_start(args);
#endif
	*pav++ = arg0;
	if (arg0) do {
		p = va_arg(args, char *);
		*pav++ = p;
	} while (p != NULL);
	va_end(args);

	ret = fexecve(name, in, out, err, av, env);
	if (av != xav)
		free(av);
	return (ret);
}

EXPORT int
fexecv(name, in, out, err, ac, av)
	const char *name;
	FILE *in, *out, *err;
	int ac;
	char *av[];
{
	av[ac] = NULL;			/*  force list to be null terminated */
	return (fexecve(name, in, out, err, av, environ));
}

EXPORT int
fexecve(name, in, out, err, av, env)
	const char *name;
	FILE *in, *out, *err;
	char * const av[], * const env[];
{
	char	nbuf[MAXPATHNAME+1];
	char	*np;
	const char *path;
#if defined(__BEOS__) || defined(__HAIKU__)
	char	*av0 = av[0];
#endif
	int	ret;
	int	fin;
	int	fout;
	int	ferr;
#ifndef	JOS
	int	o[3];		/* Old fd's for stdin/stdout/stderr */
	int	f[3];		/* Old close on exec flags for above  */
	int	errsav = 0;

	o[0] = o[1] = o[2] = -1;
	f[0] = f[1] = f[2] = 0;
#endif

	fflush(out);
	fflush(err);
	fin  = fdown(in);
	fout = fdown(out);
	ferr = fdown(err);
#ifdef JOS

	/*
	 * If name contains a pathdelimiter ('/' on unix)
	 * or name is too long ...
	 * try exec without path search.
	 */
	if (find('/', name) || strlen(name) > MAXFILENAME) {
		ret = exec_env(name, fin, fout, ferr, av, env);

	} else if ((path = getpath(env)) == NULL) {
		ret = exec_env(name, fin, fout, ferr, av, env);
		if ((ret == ENOFILE) && strlen(name) <= (sizeof (nbuf) - 6)) {
			strcatl(nbuf, "/bin/", name, (char *)NULL);
			ret = exec_env(nbuf, fin, fout, ferr, av, env);
			if (ret == EMISSDIR)
				ret = ENOFILE;
		}
	} else {
		int	nlen = strlen(name);

		for (;;) {
			np = nbuf;
			/*
			 * JOS always uses ':' as PATH Environ separator
			 */
			while (*path != ':' && *path != '\0' &&
				np < &nbuf[MAXPATHNAME-nlen-2]) {

				*np++ = *path++;
			}
			*np = '\0';
			if (*nbuf == '\0')
				strcatl(nbuf, name, (char *)NULL);
			else
				strcatl(nbuf, nbuf, "/", name, (char *)NULL);
			ret = exec_env(nbuf, fin, fout, ferr, av, env);
			if (ret == EMISSDIR)
				ret = ENOFILE;
			if (ret != ENOFILE || *path == '\0')
				break;
			path++;
		}
	}
	return (ret);

#else	/* JOS */

#ifdef	set_child_standard_fds
	set_child_standard_fds(fin, fout, ferr);
#else
	if (fin != STDIN_FILENO) {
		f[0] = fd_getfd(STDIN_FILENO);
		o[0] = dup(STDIN_FILENO);
		fd_setfd(o[0], 1);
		fdmove(fin, STDIN_FILENO);
	}
	if (fout != STDOUT_FILENO) {
		f[1] = fd_getfd(STDOUT_FILENO);
		o[1] = dup(STDOUT_FILENO);
		fd_setfd(o[1], 1);
		fdmove(fout, STDOUT_FILENO);
	}
	if (ferr != STDERR_FILENO) {
		f[2] = fd_getfd(STDERR_FILENO);
		o[2] = dup(STDERR_FILENO);
		fd_setfd(o[2], 1);
		fdmove(ferr, STDERR_FILENO);
	}
#endif

	/*
	 * If name contains a pathdelimiter ('/' on unix)
	 * or name is too long ...
	 * try exec without path search.
	 */
#ifdef	FOUND_MAXFILENAME
	if (strchr(name, '/') || strlen(name) > (unsigned)MAXFILENAME) {
#else
	if (strchr(name, '/')) {
#endif
		ret = execve(name, av, env);

	} else if ((path = getpath(env)) == NULL) {
		ret = execve(name, av, env);
		if ((geterrno() == ENOENT) && strlen(name) <= (sizeof (nbuf) - 6)) {
			strcatl(nbuf, "/bin/", name, (char *)NULL);
			ret = execve(nbuf, av, env);
#if defined(__BEOS__) || defined(__HAIKU__)
			((char **)av)[0] = av0;	/* BeOS destroys things ... */
#endif
		}
	} else {
		int	nlen = strlen(name);

		for (;;) {
			int	xerr;

			np = nbuf;
			while (*path != PATH_ENV_DELIM && *path != '\0' &&
				np < &nbuf[MAXPATHNAME-nlen-2]) {

				*np++ = *path++;
			}
			*np = '\0';
			if (*nbuf == '\0')
				strcatl(nbuf, name, (char *)NULL);
			else
				strcatl(nbuf, nbuf, "/", name, (char *)NULL);
			ret = execve(nbuf, av, env);
#if defined(__BEOS__) || defined(__HAIKU__)
			((char **)av)[0] = av0;	/* BeOS destroys things ... */
#endif
			xerr = geterrno();
			if (errsav == 0 && !enofile(xerr))
				errsav = xerr;
			if ((!enofile(xerr) && !(xerr == EACCES)) || *path == '\0')
				break;
			path++;
		}
	}
	if (errsav == 0)
		errsav = geterrno();

#ifndef	set_child_standard_fds
			/* reestablish old files */
	if (ferr != STDERR_FILENO) {
		fdmove(STDERR_FILENO, ferr);
		fdmove(o[2], STDERR_FILENO);
		if (f[2] == 0)
			fd_setfd(STDERR_FILENO, 0);
	}
	if (fout != STDOUT_FILENO) {
		fdmove(STDOUT_FILENO, fout);
		fdmove(o[1], STDOUT_FILENO);
		if (f[1] == 0)
			fd_setfd(STDOUT_FILENO, 0);
	}
	if (fin != STDIN_FILENO) {
		fdmove(STDIN_FILENO, fin);
		fdmove(o[0], STDIN_FILENO);
		if (f[0] == 0)
			fd_setfd(STDIN_FILENO, 0);
	}
#endif
	seterrno(errsav);
	return (ret);

#endif	/* JOS */
}

#ifndef	JOS
#ifndef	set_child_standard_fds

LOCAL void
fdcopy(fd1, fd2)
	int	fd1;
	int	fd2;
{
	close(fd2);
#ifdef	F_DUPFD
	fcntl(fd1, F_DUPFD, fd2);
#else
#ifdef	HAVE_DUP2
	dup2(fd1, fd2);
#endif
#endif
}

LOCAL void
fdmove(fd1, fd2)
	int	fd1;
	int	fd2;
{
	fdcopy(fd1, fd2);
	close(fd1);
}

#endif
#endif

/*----------------------------------------------------------------------------
|
|	get PATH from env
|
+----------------------------------------------------------------------------*/

LOCAL const char *
getpath(env)
	char	* const *env;
{
	char * const *p = env;
	const char *p2;

	if (p != NULL) {
		while (*p != NULL) {
			if ((p2 = chkname("PATH", *p)) != NULL)
				return (p2);
			p++;
		}
	}
	return (NULL);
}


/*----------------------------------------------------------------------------
|
| Check if name is in environment.
| Return pointer to value name is found.
|
+----------------------------------------------------------------------------*/

LOCAL const char *
chkname(name, ev)
	const char	*name;
	const char	*ev;
{
	for (;;) {
		if (*name != *ev) {
			if (*ev == '=' && *name == '\0')
				return (++ev);
			return (NULL);
		}
		name++;
		ev++;
	}
}

#endif	/* defined(HAVE_DUP) && (defined(HAVE_DUP2) || defined(F_DUPFD)) */

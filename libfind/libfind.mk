#ident @(#)libfind.mk	1.2 07/02/04 
###########################################################################
SRCROOT=	..
RULESDIR=	RULES
include		$(SRCROOT)/$(RULESDIR)/rules.top
###########################################################################

#.SEARCHLIST:	. $(ARCHDIR) stdio $(ARCHDIR)
#VPATH=		.:stdio:$(ARCHDIR)
INSDIR=		lib
TARGETLIB=	find
#CPPOPTS +=	-Istdio
#CPPOPTS +=	-DUSE_SCANSTACK

#CPPOPTS +=	-D__FIND__
CPPOPTS +=	-DUSE_LARGEFILES
CPPOPTS +=	-DUSE_ACL
CPPOPTS +=	-DUSE_XATTR
CPPOPTS +=	-DUSE_NLS
CPPOPTS +=	-DSCHILY_PRINT

include		Targets
LIBS=		

###########################################################################
include		$(SRCROOT)/$(RULESDIR)/rules.lib
###########################################################################

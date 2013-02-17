#ident @(#)shledc_dec.mk	1.3 08/12/22 
###########################################################################
SRCROOT=	..
RULESDIR=	RULES
include		$(SRCROOT)/$(RULESDIR)/rules.top
###########################################################################

SUBARCHDIR=	/pic
INSDIR=		lib
TARGETLIB=	edc_ecc_dec
#
# Selectively increase the opimisation for libedc for better performance
#
# The code has been tested for correctness with this level of optimisation
# If your GCC creates defective code, you found a GCC bug that should
# be reported to the GCC people. As a workaround, you may remove the next
# lines to fall back to the standard optimisation level.
#
_XARCH_OPT=	$(OARCH:%cc64=$(SUNPROCOPT64))
XARCH_OPT=	$(_XARCH_OPT:%cc=-xarch=generic)

SUNPROCOPTOPT=	-fast $(XARCH_OPT)
GCCOPTOPT=	-O3  -fexpensive-optimizations
#
CFILES=		edc_ecc_dec.c
HFILES=		edc.h
LIBS=		-ledc_ecc -lc
#XMK_FILE=	Makefile.man

###########################################################################
include		$(SRCROOT)/$(RULESDIR)/rules.shl
###########################################################################

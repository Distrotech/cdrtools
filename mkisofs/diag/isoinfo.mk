#ident @(#)isoinfo.mk	1.14 09/11/19 
###########################################################################
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2
# as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program; see the file COPYING.  If not, write to the Free Software
# Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
###########################################################################
SRCROOT=	../..
RULESDIR=	RULES
include		$(SRCROOT)/$(RULESDIR)/rules.top
###########################################################################

INSDIR=		bin
TARGET=		isoinfo
CPPOPTS +=	-DUSE_LIBSCHILY
CPPOPTS +=	-DUSE_LARGEFILES
CPPOPTS +=	-DUSE_SCG
CPPOPTS +=	-I..
CPPOPTS +=	-I../../libscg
CPPOPTS +=	-I../../libscgcmd
CPPOPTS +=	-I../../libcdrdeflt
CPPOPTS +=	-DSCHILY_PRINT
CPPOPTS +=	-DUSE_NLS
CPPOPTS +=	-DUSE_ICONV
CPPOPTS +=	-DINS_BASE=\"${INS_BASE}\"

CFILES=		isoinfo.c \
		scsi.c

LIBS=		-lsiconv -lscgcmd -lrscg -lscg $(LIB_VOLMGT) -lcdrdeflt -ldeflt -lschily \
			$(SCSILIB) $(LIB_SOCKET) $(LIB_ICONV) $(LIB_INTL)

XMK_FILE=	isoinfo_man.mk

###########################################################################
include		$(SRCROOT)/$(RULESDIR)/rules.cmd
###########################################################################

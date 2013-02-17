#ident @(#)isodebug.mk	1.8 08/10/26 
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
TARGET=		isodebug
CPPOPTS +=	-DUSE_LIBSCHILY
CPPOPTS +=	-DUSE_LARGEFILES
CPPOPTS +=	-DUSE_SCG
CPPOPTS +=	-I..
CPPOPTS +=	-I../../libscg
CPPOPTS +=	-I../../libscgcmd
CPPOPTS +=	-I../../libcdrdeflt
CPPOPTS +=	-DSCHILY_PRINT

CFILES=		isodebug.c \
		scsi.c

LIBS=		-lscgcmd -lrscg -lscg $(LIB_VOLMGT) -lcdrdeflt -ldeflt -lschily $(SCSILIB) $(LIB_SOCKET)
XMK_FILE=	isodebug_man.mk

###########################################################################
include		$(SRCROOT)/$(RULESDIR)/rules.cmd
###########################################################################

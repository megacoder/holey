#########################################################################
# vim: ts=8 sw=8
#########################################################################
# Author:   reynolds (Tommy Reynolds)
# Filename: Makefile
# Date:     2006-12-30 13:23:28
#########################################################################
# Note that we use '::' rules to allow multiple rule sets for the same
# target.  Read that as "modularity exemplarized".
#########################################################################

PREFIX	:=/opt/holey
BINDIR	=${PREFIX}/bin

TARGETS	=all clean distclean clobber check install uninstall tags
TARGET	=all

SUBDIRS	=

.PHONY:	${TARGETS} ${SUBDIRS}

CC	=ccache gcc -m32 -std=gnu99
OPT	=-Os
OPT	=-O0
INC	=-I.
DEFS	=
DEFS	+= `getconf LFS_CFLAGS`
CFLAGS	=${OPT} -Wall -Wextra -Werror -pedantic -g ${DEFS} ${INC}
LDFLAGS	=-g
LDFLAGS	+= `getconf LFS_LDFLAGS`
LDLIBS	=

all::	holey

${TARGETS}::

clean::
	${RM} a.out *.o core.* lint tags
	${RM} biggun

distclean clobber:: clean
	${RM} holey

check::	holey
	./holey ${ARGS}
	dumpf ./biggun

install:: holey
	install -d ${BINDIR}
	install -c -s holey ${BINDIR}/

uninstall::
	${RM} ${BINDIR}/holey

tags::
	ctags -R .

# ${TARGETS}::
# 	${MAKE} TARGET=$@ ${SUBDIRS}

# ${SUBDIRS}::
# 	${MAKE} -C $@ ${TARGET}

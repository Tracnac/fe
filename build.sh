#!/bin/sh

DEBUG=0
MODULE=0

while getopts dm opt
do	case "$opt" in
	d) DEBUG=1;;
  m) MODULE=1;;
	[?])	print >&2 "Usage: $0 [-d] debug [-m] build modules"
		exit 1;;
	esac
done

BASEDIR=`pwd`
SRCDIR="${BASEDIR}/src"
BUILDDIR="${BASEDIR}/build"
MODULESDIR="${BASEDIR}/modules"

if [ $DEBUG -eq 1 ];
then
  CC="gcc"
  CFLAGS="-g -Wall -Wextra -pedantic -std=c89 -march=native"
  LDFLAGS="-ldl"
else
  CC="gcc"
  CFLAGS="-Os -Wall -Wextra -pedantic -std=c89 -march=native"
  LDFLAGS="-ldl"
fi

export LD_LIBRARY_PATH=${MODULESDIR}

# Make directories
[ ! -d ${BUILDDIR} ] && mkdir ${BUILDDIR}
[ ! -d ${MODULESDIR} ] && mkdir ${MODULESDIR}

if [ $MODULE -eq 1 ];
then
  # Clean
  rm -rf ${BUILDDIR}/*.o ${MODULESDIR}/*.so fe

  # Make core
  ${CC} ${CFLAGS} -o ${BUILDDIR}/fe.o -c -fPIC ${SRCDIR}/fe.c
  ${CC} -o ${MODULESDIR}/fe_core.so -shared -fPIC -ldl ${BUILDDIR}/fe.o

  # Make module
  ${CC} ${CFLAGS} -o ${BUILDDIR}/fe_math.o -c -fPIC ${SRCDIR}/fe_math.c
  ${CC} -o ${MODULESDIR}/fe_math.so -shared -fPIC -lm -L${MODULESDIR} -l:fe_core.so ${BUILDDIR}/fe_math.o
  for i in ${MODULESDIR}/*.so ; do strip -s ${i}; done 
fi

# Make binaries
${CC} ${CFLAGS} -o ${BASEDIR}/fe ${SRCDIR}/fe.c ${SRCDIR}/tre/tre.c ${LDFLAGS}
strip -s ${BASEDIR}/fe

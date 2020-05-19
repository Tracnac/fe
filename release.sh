#!/bin/sh

export BASEDIR=`pwd`
export SRCDIR="${BASEDIR}/src"
export BUILDDIR="${BASEDIR}/build"
export MODULESDIR="${BASEDIR}/modules"
export CC="gcc"
export CFLAGS="-Os -Wall -Wextra -pedantic -std=c89 -march=native"
export LDFLAGS="-ldl"
export LD_LIBRARY_PATH=${MODULESDIR}

# Make directories
[ ! -d ${BUILDDIR} ] && mkdir ${BUILDDIR}
[ ! -d ${MODULESDIR} ] && mkdir ${MODULESDIR}

# Clean
rm -rf ${BUILDDIR}/*.o ${MODULESDIR}/*.so fe

# Make core
${CC} ${CFLAGS} -o ${BUILDDIR}/fe.o -c -fPIC ${SRCDIR}/fe.c
${CC} -o ${MODULESDIR}/fe_core.so -shared -fPIC -ldl ${BUILDDIR}/fe.o

# Make module
${CC} ${CFLAGS} -o ${BUILDDIR}/fe_math.o -c -fPIC ${SRCDIR}/fe_math.c
${CC} -o ${MODULESDIR}/fe_math.so -shared -fPIC -lm -L${MODULESDIR} -l:fe_core.so ${BUILDDIR}/fe_math.o
for i in ${MODULESDIR}/*.so ; do strip -s ${i}; done 

# Make binaries
${CC} ${CFLAGS} -o ${BASEDIR}/fe ${SRCDIR}/fe.c ${LDFLAGS}
strip -s ${BASEDIR}/fe

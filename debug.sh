#!/bin/sh

export BASEDIR=`pwd`
export SRCDIR="${BASEDIR}/src"
export BUILDDIR="${BASEDIR}/build"
export MODULESDIR="${BASEDIR}/modules"
export CC="gcc"
export CFLAGS="-ldl -Wall -Wextra -pedantic -std=c89 -march=native -g"
export LD_LIBRARY_PATH=${MODULESDIR}

# Make directories
[ ! -d ${BUILDDIR} ] && mkdir ${BUILDDIR}
[ ! -d ${MODULESDIR} ] && mkdir ${MODULESDIR}

# Clean
rm -rf ${BUILDDIR}/*.o ${MODULESDIR}/*.so fe

# Make core
${CC} -g -o ${BUILDDIR}/fe.o -c -fPIC ${SRCDIR}/fe.c
${CC} -g -o ${MODULESDIR}/core.so -shared -fPIC -ldl ${BUILDDIR}/fe.o

# Make module
${CC} -g -o ${BUILDDIR}/fe_math.o -c -fPIC ${SRCDIR}/fe_math.c
${CC} -g -o ${MODULESDIR}/fe_math.so -shared -fPIC -lm -L${MODULESDIR} -l:core.so ${BUILDDIR}/fe_math.o

# Make binaries
${CC} ${CFLAGS} -o ${BASEDIR}/fe ${SRCDIR}/fe.c

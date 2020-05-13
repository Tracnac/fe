#!/bin/sh

BASEDIR=`pwd`
SRCDIR="${BASEDIR}/src"
BUILDDIR="${BASEDIR}/build"
LIBDIR="${BASEDIR}/libs"
CC="g++"
FLAGS="-Os -Wall -Wextra -march=native"

# Makedir
[ ! -d ${BUILDDIR} ] && mkdir ${BUILDDIR}
[ ! -d ${LIBDIR} ] && mkdir ${LIBDIR}

# Clean
rm -rf ${BUILDDIR}/*.o

# Make lib
cd ${BUILDDIR}
export SRCFILES=`ls -1 ${SRCDIR}/*.cpp ${SRCDIR}/*.cxx`
for i in ${SRCFILES} ; do ${CC} -Os -c -fPIC ${i} ; done
export OBJFILES=`ls -1 ${BUILDDIR}/*.o`
${CC} -o ${LIBDIR}/lib_replxx.so -shared -fPIC -lstdc++ ${OBJFILES}
strip -s ${LIBDIR}/lib_replxx.so
cd ${BASEDIR}

# Check
ldd -r ${LIBDIR}/lib_replxx.so

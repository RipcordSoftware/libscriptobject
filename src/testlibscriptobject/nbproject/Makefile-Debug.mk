#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=--coverage
CXXFLAGS=--coverage

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../libscriptobject/dist/Debug/GNU-Linux-x86/libscriptobject.a ../libscriptobject_gason/dist/Debug/GNU-Linux-x86/liblibscriptobject_gason.a ../libscriptobject_msgpack/dist/Debug/GNU-Linux-x86/liblibscriptobject_msgpack.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testlibscriptobject

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testlibscriptobject: ../libscriptobject/dist/Debug/GNU-Linux-x86/libscriptobject.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testlibscriptobject: ../libscriptobject_gason/dist/Debug/GNU-Linux-x86/liblibscriptobject_gason.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testlibscriptobject: ../libscriptobject_msgpack/dist/Debug/GNU-Linux-x86/liblibscriptobject_msgpack.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testlibscriptobject: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testlibscriptobject ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../externals/gason/src -I../libscriptobject -I../libscriptobject_gason -I../libscriptobject_msgpack -I../../externals/msgpack-c/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../libscriptobject && ${MAKE}  -f Makefile CONF=Debug
	cd ../libscriptobject_gason && ${MAKE}  -f Makefile CONF=Debug
	cd ../libscriptobject_msgpack && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testlibscriptobject

# Subprojects
.clean-subprojects:
	cd ../libscriptobject && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libscriptobject_gason && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libscriptobject_msgpack && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

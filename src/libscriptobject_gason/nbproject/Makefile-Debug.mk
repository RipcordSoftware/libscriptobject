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
	${OBJECTDIR}/_ext/1762787558/gason.o \
	${OBJECTDIR}/script_array_json_source.o \
	${OBJECTDIR}/script_object_json_source.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=$(COVERAGE_FLAGS)
CXXFLAGS=$(COVERAGE_FLAGS)

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject_gason.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject_gason.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject_gason.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject_gason.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject_gason.a

${OBJECTDIR}/_ext/1762787558/gason.o: ../../externals/gason/src/gason.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1762787558
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../libscriptobject -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1762787558/gason.o ../../externals/gason/src/gason.cpp

${OBJECTDIR}/script_array_json_source.o: script_array_json_source.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../libscriptobject -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_array_json_source.o script_array_json_source.cpp

${OBJECTDIR}/script_object_json_source.o: script_object_json_source.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../libscriptobject -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_object_json_source.o script_object_json_source.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject_gason.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

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
	${OBJECTDIR}/md5.o \
	${OBJECTDIR}/script_object.o \
	${OBJECTDIR}/script_object_definition.o \
	${OBJECTDIR}/script_object_factory.o \
	${OBJECTDIR}/script_object_keys.o \
	${OBJECTDIR}/script_object_keys_factory.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f3

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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject.a

${OBJECTDIR}/md5.o: md5.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/md5.o md5.cpp

${OBJECTDIR}/script_object.o: script_object.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_object.o script_object.cpp

${OBJECTDIR}/script_object_definition.o: script_object_definition.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_object_definition.o script_object_definition.cpp

${OBJECTDIR}/script_object_factory.o: script_object_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_object_factory.o script_object_factory.cpp

${OBJECTDIR}/script_object_keys.o: script_object_keys.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_object_keys.o script_object_keys.cpp

${OBJECTDIR}/script_object_keys_factory.o: script_object_keys_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_object_keys_factory.o script_object_keys_factory.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/object_defn_hash_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libjsoncpp_debug.a --coverage  -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lpthread 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/object_keys_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libjsoncpp_debug.a --coverage  -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lpthread 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/simple_object_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a ../../externals/installed/lib/libjsoncpp_debug.a --coverage  -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lpthread 


${TESTDIR}/tests/object_defn_hash_tests.o: tests/object_defn_hash_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -I../../externals/installed/include -I. -std=c++11 --coverage -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/object_defn_hash_tests.o tests/object_defn_hash_tests.cpp


${TESTDIR}/tests/object_keys_tests.o: tests/object_keys_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -I../../externals/installed/include -I. -std=c++11 --coverage -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/object_keys_tests.o tests/object_keys_tests.cpp


${TESTDIR}/tests/simple_object_tests.o: tests/simple_object_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -I../../externals/installed/include -I. -std=c++11 --coverage -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/simple_object_tests.o tests/simple_object_tests.cpp


${OBJECTDIR}/md5_nomain.o: ${OBJECTDIR}/md5.o md5.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/md5.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/md5_nomain.o md5.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/md5.o ${OBJECTDIR}/md5_nomain.o;\
	fi

${OBJECTDIR}/script_object_nomain.o: ${OBJECTDIR}/script_object.o script_object.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/script_object.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_object_nomain.o script_object.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/script_object.o ${OBJECTDIR}/script_object_nomain.o;\
	fi

${OBJECTDIR}/script_object_definition_nomain.o: ${OBJECTDIR}/script_object_definition.o script_object_definition.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/script_object_definition.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_object_definition_nomain.o script_object_definition.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/script_object_definition.o ${OBJECTDIR}/script_object_definition_nomain.o;\
	fi

${OBJECTDIR}/script_object_factory_nomain.o: ${OBJECTDIR}/script_object_factory.o script_object_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/script_object_factory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_object_factory_nomain.o script_object_factory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/script_object_factory.o ${OBJECTDIR}/script_object_factory_nomain.o;\
	fi

${OBJECTDIR}/script_object_keys_nomain.o: ${OBJECTDIR}/script_object_keys.o script_object_keys.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/script_object_keys.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_object_keys_nomain.o script_object_keys.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/script_object_keys.o ${OBJECTDIR}/script_object_keys_nomain.o;\
	fi

${OBJECTDIR}/script_object_keys_factory_nomain.o: ${OBJECTDIR}/script_object_keys_factory.o script_object_keys_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/script_object_keys_factory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG_SCRIPT_OBJECT_KEYS=1 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/script_object_keys_factory_nomain.o script_object_keys_factory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/script_object_keys_factory.o ${OBJECTDIR}/script_object_keys_factory_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libscriptobject.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

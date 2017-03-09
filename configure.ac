# Copyright 2017 Michael Thomas (malinka) <malinka@entropy-development.com>
# Distributed under the terms of the GNU Affero General Public License v3

AC_PREREQ([2.53])
m4_pattern_forbid([^AX_])
m4_pattern_forbid([^EX_])

AC_INIT([Theia], [0.0.1], [bugs@entropy-development.com])
AC_CONFIG_SRCDIR([src/Exception.hh])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_TESTDIR([test])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects dist-xz no-dist-gzip])

AM_PROG_AR
LT_INIT
AC_PROG_CXX
AC_LANG_PUSH([C++])

AC_CHECK_HEADERS([glm/glm.hpp], [], [AC_MSG_FAILURE([glm is required])])

AX_PTHREAD
[LIBS="$PTHREAD_LIBS $LIBS"]
[CFLAGS="$PTHREAD_CFLAGS $CFLAGS"]
[CXXFLAGS="$PTHREAD_CFLAGS $CXXFLAGS"]

EX_BASE_FLAGS

EX_WITH_ENTROPY
[LIBS="$ENTROPY_LIBS $LIBS"]
[LDFLAGS="$ENTROPY_LDFLAGS $LDFLAGS"]
[CPPFLAGS="$ENTROPY_CPPFLAGS $CPPFLAGS"]

EX_WITH_GLFW
[LIBS="$GLFW_LIBS $LIBS"]
[LDFLAGS="$GLFW_LDFLAGS $LDFLAGS"]
[CPPFLAGS="$GLFW_CPPFLAGS $CPPFLAGS"]

EX_WITH_GLX
[LIBS="$GLX_LIBS $LIBS"]
[LDFLAGS="$GLX_LDFLAGS $LDFLAGS"]
[CPPFLAGS="$GLX_CPPFLAGS $CPPFLAGS"]

EX_WITH_GTEST
EX_FLAGS

AC_LANG_POP([C++])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile atlocal:test/atlocal.in])
AC_OUTPUT

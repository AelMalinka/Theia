dnl Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
dnl Distributed under the terms of the GNU Affero General Public License v3

AC_DEFUN([EX_WITH_GLFW], [
	AC_ARG_WITH([glfw],
		[AS_HELP_STRING([--with-glfw], [support for glfw])],
		[with_glfw=$withval],
		[with_glfw=check]
	)

	AS_IF([test "x$with_glfw" != xno],
		[
			test "x$with_glfw" != xyes -a "x$with_glfw" != xcheck && GLFW_LDFLAGS="-L${with_glfw}/lib" && GLFW_CPPFLAGS="-I${with_glfw}/include"
			EX_CHECK_LIBRARY([GLFW], ["GLFW/glfw3.h"], [glfw3], [], [
				AS_IF([test "x$with_glfw" != xcheck], [
					AC_MSG_FAILURE(["--with-glfw: glfw not found"])
				])
			])
		]
	)
	AC_SUBST([GLFW], [$GLFW_LIBS])
	AM_CONDITIONAL([GLFW], [test "x$GLFW_LIBS" != x])
])

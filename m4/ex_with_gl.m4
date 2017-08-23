dnl Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
dnl Distributed under the terms of the GNU Affero General Public License v3

AC_DEFUN([EX_WITH_GL_CORE], [
	AC_ARG_WITH([gl-core],
		[AS_HELP_STRING([--with-gl-core],
			[enable opengl 3.3 core profile]
		)],
		[with_gl_core=$withval],
		[with_gl_core=yes]
	)

	AS_IF([test "x$with_gl_core" != "xno"],
		[
			AC_DEFINE([HAVE_OPENGL_CORE], [1], [Define to 1 if OpenGL 3.3 Core])
		]
	)
])

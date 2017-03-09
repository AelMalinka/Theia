dnl Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
dnl Distributed under the terms of the GNU Affero General Public License v3

AC_DEFUN([EX_WITH_GLX], [
	AC_ARG_WITH([glx],
		[AS_HELP_STRING([--with-glx], [use glx, (required)])],
		[with_glx=$withval],
		[with_glx=check]
	)

	AS_IF([test "x$with_glx" == xno], [AC_MSG_FAILURE([glx is required])],
		[
			test "x$with_glx" != xyes -a "x$with_glx" != xcheck && GLX_LDFLAGS="-L$with_glx"
			EX_CHECK_LIBRARY([GL], ["GL/gl.h"], [GL], [], [AC_MSG_FAILURE(["glx: failed to find GL"])])
			EX_CHECK_LIBRARY([GLU], ["GL/glu.h"], [GLU], [], [AC_MSG_FAILURE(["glx: failed to find GLU"])])
			AC_CHECK_HEADER([GL/glx.h], [], [AC_MSG_FAILURE(["glx: failed to find GL/glx.h"])])
			EX_CHECK_LIBRARY([epoxy], ["epoxy/gl.h"], [epoxy], [], [AC_MSG_FAILURE(["glx: failed to find libepoxy"])])
			AC_CHECK_HEADER([epoxy/glx.h], [], [AC_MSG_FAILURE(["glx: failed to find epoxy/glx.h"])])
			EX_CHECK_LIBRARY([xlib], ["X11/Xlib.h"], [X11], [], [AC_MSG_FAILURE(["glx: failed to find Xlib"])])
			EX_CHECK_LIBRARY([xcb], ["xcb/xcb.h"], [X11-xcb], [], [AC_MSG_FAILURE(["glx: failed to find xcb"])])
			EX_CHECK_LIBRARY([randr], ["xcb/randr.h"], [xcb-randr], [], [AC_MSG_FAILURE(["glx: failed to find xcb-randr"])])
			EX_CHECK_LIBRARY([xrandr], ["X11/extensions/Xrandr.h"], [Xrandr], [], [AC_MSG_FAILURE(["glx: failed to find xrandr"])])
			EX_CHECK_LIBRARY([xcursor], ["X11/Xcursor/Xcursor.h"], [Xcursor], [], [AC_MSG_FAILURE(["glx: failed to find xcursor"])])
			EX_CHECK_LIBRARY([xinerama], ["X11/extensions/Xinerama.h"], [Xinerama], [], [AC_MSG_FAILURE(["glx: failed to find xinerama"])])
		]
	)

	[GLX_LIBS="$GL_LIBS $GLU_LIBS $epoxy_LIBS $xlib_LIBS $xcb_LIBS $randr_LIBS $xrandr_LIBS $xcursor_LIBS $xinerama_LIBS"]

	AC_SUBST([GLX], [$GLX_LIBS])
	AM_CONDITIONAL([GLX], [test "x$GLX_LIBS" != x])

	AC_DEFINE([HAVE_GLX], [1], [Define to 1 if GLX is found])
])

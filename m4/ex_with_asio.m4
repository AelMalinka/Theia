# Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
#
# Copying and distribution of this file, with or without modification, are
# permitted in any medium without royalty provided the copyright notice
# and this notice are preserved. This file is offered as-is, without any
# warranty.

AC_DEFUN([EX_WITH_ASIO], [
	AC_ARG_WITH([asio],
		[AS_HELP_STRING([--with-asio], [location to look for entropy-asio])],
		[with_asio=$withval],
		[with_asio=check]
	)

	ASIO_LIBS=
	LDFLAGS_save="$LDFLAGS"
	AS_IF([test "x$with_asio" != xcheck], [AS_IF([test "x$with_asio" != xyes], [
		LDFLAGS="-L${with_asio}/lib"
	])])
	AC_CHECK_LIB([entropy-asio], [main], [
			AC_SUBST([ASIO_LIBS], ["-lentropy-asio"])
			AC_SUBST([ASIO_LDFLAGS], ["$LDFLAGS"])
		],
		AC_MSG_FAILURE(["--with-asio: asio not found"])
	)
	LDFLAGS="$LDFLAGS_save"
	ASIO_CPPFLAGS=
	CPPFLAGS_save="$CPPFLAGS"
	test "x$with_entopy" != xcheck && CPPFLAGS="-I${with_asio}/include"
	AC_CHECK_HEADER([Entropy/Asio/Exception.hh], [
			AC_SUBST([ASIO_CPPFLAGS], ["$CPPFLAGS"])
		],
		AC_MSG_FAILURE(["--with-asio: asio not found"])
	)
	CPPFLAGS="$CPPFLAGS_save"
])

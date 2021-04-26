dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(PangoTest, 1.0)


AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CC
AC_PROG_CXX

LT_PREREQ([2.2])
LT_INIT(win32-dll dlopen )
AC_SUBST([LIBTOOL_DEPS])

AC_LANG([C++])

PKG_CHECK_MODULES([PANGO], [pangoft2,pangocairo])

AC_SUBST([PANGO_CFLAGS])
AC_SUBST([PANGO_LIBS])

AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT


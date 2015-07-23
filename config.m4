dnl $Id$
dnl config.m4 for extension libi2c

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(libi2c, for libi2c support,
Make sure that the comment is aligned:
[  --with-libi2c             Include libi2c support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(libi2c, whether to enable libi2c support,
dnl Make sure that the comment is aligned:
dnl [  --enable-libi2c           Enable libi2c support])

if test "$PHP_LIBI2C" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-libi2c -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/libi2c.h"  # you most likely want to change this
  dnl if test -r $PHP_LIBI2C/$SEARCH_FOR; then # path given as parameter
  dnl   LIBI2C_DIR=$PHP_LIBI2C
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for libi2c files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       LIBI2C_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$LIBI2C_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the libi2c distribution])
  dnl fi

  dnl # --with-libi2c -> add include path
  dnl PHP_ADD_INCLUDE($LIBI2C_DIR/include)

  dnl # --with-libi2c -> check for lib and symbol presence
  dnl LIBNAME=libi2c # you may want to change this
  dnl LIBSYMBOL=libi2c # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $LIBI2C_DIR/lib, LIBI2C_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_LIBI2CLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong libi2c lib version or lib not found])
  dnl ],[
  dnl   -L$LIBI2C_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(LIBI2C_SHARED_LIBADD)

  PHP_NEW_EXTENSION(libi2c, libi2c.cpp, $ext_shared)
  PHP_REQUIRE_CXX()
  PHP_ADD_LIBRARY(stdc++, "", EXTRA_LDFLAGS)
  CPPFILE="libi2c.cpp"
  PHP_NEW_EXTENSION(cpptest,$CPPFILE, $ext_shared)
fi

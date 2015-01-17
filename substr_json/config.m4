dnl $Id$
dnl config.m4 for extension substr_json

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(substr_json, for substr_json support,
Make sure that the comment is aligned:
[  --with-substr_json             Include substr_json support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(substr_json, whether to enable substr_json support,
dnl Make sure that the comment is aligned:
dnl [  --enable-substr_json           Enable substr_json support])

if test "$PHP_SUBSTR_JSON" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-substr_json -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/substr_json.h"  # you most likely want to change this
  dnl if test -r $PHP_SUBSTR_JSON/$SEARCH_FOR; then # path given as parameter
  dnl   SUBSTR_JSON_DIR=$PHP_SUBSTR_JSON
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for substr_json files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SUBSTR_JSON_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SUBSTR_JSON_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the substr_json distribution])
  dnl fi

  dnl # --with-substr_json -> add include path
  dnl PHP_ADD_INCLUDE($SUBSTR_JSON_DIR/include)

  dnl # --with-substr_json -> check for lib and symbol presence
  dnl LIBNAME=substr_json # you may want to change this
  dnl LIBSYMBOL=substr_json # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SUBSTR_JSON_DIR/lib, SUBSTR_JSON_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SUBSTR_JSONLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong substr_json lib version or lib not found])
  dnl ],[
  dnl   -L$SUBSTR_JSON_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(SUBSTR_JSON_SHARED_LIBADD)

  PHP_NEW_EXTENSION(substr_json, substr_json.c, $ext_shared)
fi

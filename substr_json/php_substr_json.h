/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_SUBSTR_JSON_H
#define PHP_SUBSTR_JSON_H

#define SUBSTR_JSON_VERSION "0.0.1"
#include "ext/standard/php_smart_str.h"

extern zend_module_entry substr_json_module_entry;
#define phpext_substr_json_ptr &substr_json_module_entry

#ifdef PHP_WIN32
#	define PHP_SUBSTR_JSON_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_SUBSTR_JSON_API __attribute__ ((visibility("default")))
#else
#	define PHP_SUBSTR_JSON_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(substr_json);
PHP_MSHUTDOWN_FUNCTION(substr_json);
PHP_RINIT_FUNCTION(substr_json);
PHP_RSHUTDOWN_FUNCTION(substr_json);
PHP_MINFO_FUNCTION(substr_json);

PHP_FUNCTION(confirm_substr_json_compiled);	/* For testing, remove later. */
PHP_FUNCTION(substr_json);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(substr_json)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(substr_json)
*/

/* In every utility function you add that needs to use variables 
   in php_substr_json_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as SUBSTR_JSON_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define SUBSTR_JSON_G(v) TSRMG(substr_json_globals_id, zend_substr_json_globals *, v)
#else
#define SUBSTR_JSON_G(v) (substr_json_globals.v)
#endif

#endif	/* PHP_SUBSTR_JSON_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

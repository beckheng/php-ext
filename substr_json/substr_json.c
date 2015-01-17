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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_substr_json.h"

/* If you declare any globals in php_substr_json.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(substr_json)
*/

/* True global resources - no need for thread safety here */
static int le_substr_json;

/* {{{ substr_json_functions[]
 *
 * Every user visible function must have an entry in substr_json_functions[].
 */
const zend_function_entry substr_json_functions[] = {
	PHP_FE(confirm_substr_json_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(substr_json,	NULL)
	PHP_FE_END	/* Must be the last line in substr_json_functions[] */
};
/* }}} */

/* {{{ substr_json_module_entry
 */
zend_module_entry substr_json_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"substr_json",
	substr_json_functions,
	PHP_MINIT(substr_json),
	PHP_MSHUTDOWN(substr_json),
	PHP_RINIT(substr_json),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(substr_json),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(substr_json),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SUBSTR_JSON
ZEND_GET_MODULE(substr_json)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("substr_json.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_substr_json_globals, substr_json_globals)
    STD_PHP_INI_ENTRY("substr_json.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_substr_json_globals, substr_json_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_substr_json_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_substr_json_init_globals(zend_substr_json_globals *substr_json_globals)
{
	substr_json_globals->global_value = 0;
	substr_json_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(substr_json)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(substr_json)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(substr_json)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(substr_json)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(substr_json)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "substr_json support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_substr_json_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_substr_json_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "substr_json", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto string substr_json(string str, int start)
    */
PHP_FUNCTION(substr_json)
{
	char *str = NULL;
	int argc = ZEND_NUM_ARGS();
	int str_len;
	long start;
	
	smart_str buf = {0};

	if (zend_parse_parameters(argc TSRMLS_CC, "sl", &str, &str_len, &start) == FAILURE) 
		return;

	if (!str_len)
	{
		RETURN_NULL();
	}
	
	long i = start;
	int match_count = 0, is_instring = 0;
	char c;
	for (i = start; i < str_len; ++i)
	{
		c = str[i];
		
		smart_str_appendc(&buf, c);
		
		switch (c)
		{
			case '{':
			case '[':
				if (!is_instring)
				{
					++match_count;
				}
				break;
			case '}':
			case ']':
				if (!is_instring)
				{
					--match_count;
					
					if (0 == match_count)
					{
						goto END;
					}
				}
				break;
			case '"':
				if(i > 0 && '\\' != str[i-1])
				{
					is_instring = !is_instring;
				}
				break;
			default:
				break;
		}
	}
	
	END:
	ZVAL_STRINGL(return_value, buf.c, buf.len, 1);
	
	smart_str_free(&buf);
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

extern "C" {
#ifdef ZTS
#include "TSRM.h"
#endif
}
#ifndef PHP_LIBI2C_H
#define PHP_LIBI2C_H

extern zend_module_entry libi2c_module_entry;
#define phpext_libi2c_ptr &libi2c_module_entry

#define PHP_LIBI2C_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_LIBI2C_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_LIBI2C_API __attribute__ ((visibility("default")))
#else
#	define PHP_LIBI2C_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(libi2c);
PHP_MSHUTDOWN_FUNCTION(libi2c);
PHP_RINIT_FUNCTION(libi2c);
PHP_RSHUTDOWN_FUNCTION(libi2c);
PHP_MINFO_FUNCTION(libi2c);

PHP_FUNCTION(confirm_libi2c_compiled);	/* For testing, remove later. */

//PHP_METHOD(i2c, __construct);
PHP_METHOD(i2c, open);
PHP_METHOD(i2c, read);
PHP_METHOD(i2c, write);
PHP_METHOD(i2c, readblock);
PHP_METHOD(i2c, writeblock);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(libi2c)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(libi2c)
*/

/* In every utility function you add that needs to use variables 
   in php_libi2c_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as LIBI2C_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define LIBI2C_G(v) TSRMG(libi2c_globals_id, zend_libi2c_globals *, v)
#else
#define LIBI2C_G(v) (libi2c_globals.v)
#endif

#endif	/* PHP_LIBI2C_H */


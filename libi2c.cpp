
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
}
#include "php_libi2c.h"

#include <cstddef>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <inttypes.h>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>

/* If you declare any globals in php_libi2c.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(libi2c)
*/

/* True global resources - no need for thread safety here */
static int le_libi2c;

/*
ZEND_BEGIN_ARG_INFO(arg_construct, 2)    //声明arg_construct为含有x,y的2个参数   
ZEND_ARG_INFO(0, adapter)   
ZEND_ARG_INFO(0, addr)   
ZEND_END_ARG_INFO()


*/
/* {{{ libi2c_functions[]
 *
 * Every user visible function must have an entry in libi2c_functions[].
 */
const zend_function_entry libi2c_functions[] = {
	PHP_FE(confirm_libi2c_compiled,	NULL)		/* For testing, remove later. */
	/* PHP_ME(i2c, __construct, arg_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)//   
 
      */
        PHP_ME(i2c, open, NULL, ZEND_ACC_PUBLIC) 
        PHP_ME(i2c, read, NULL, ZEND_ACC_PUBLIC)   
        PHP_ME(i2c, readblock, NULL, ZEND_ACC_PUBLIC)   
        PHP_ME(i2c, write, NULL, ZEND_ACC_PUBLIC)   
        PHP_ME(i2c, writeblock, NULL, ZEND_ACC_PUBLIC)  
	PHP_FE_END	/* Must be the last line in libi2c_functions[] */
};
/* }}} */

/* {{{ libi2c_module_entry
 */
zend_module_entry libi2c_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"libi2c",
	libi2c_functions,
	PHP_MINIT(libi2c),
	PHP_MSHUTDOWN(libi2c),
	PHP_RINIT(libi2c),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(libi2c),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(libi2c),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_LIBI2C_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_LIBI2C
ZEND_GET_MODULE(libi2c)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("libi2c.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_libi2c_globals, libi2c_globals)
    STD_PHP_INI_ENTRY("libi2c.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_libi2c_globals, libi2c_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_libi2c_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_libi2c_init_globals(zend_libi2c_globals *libi2c_globals)
{
	libi2c_globals->global_value = 0;
	libi2c_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
zend_class_entry *i2c_ce; //类结构变量
PHP_MINIT_FUNCTION(libi2c)
{


		zend_class_entry i2c;

		INIT_CLASS_ENTRY(i2c, "i2c", libi2c_functions);//第二个参数为类名，第三个参数为函数表
		i2c_ce = zend_register_internal_class_ex(&i2c, NULL, NULL TSRMLS_CC);//注册类

		zend_declare_property_null(i2c_ce, ZEND_STRL("_adapter"), ZEND_ACC_PRIVATE TSRMLS_CC);//初始化属性
		zend_declare_property_null(i2c_ce, ZEND_STRL("_addr"), ZEND_ACC_PRIVATE TSRMLS_CC);//初始化属性
		zend_declare_property_null(i2c_ce, ZEND_STRL("_file"), ZEND_ACC_PRIVATE TSRMLS_CC);//初始化属性

	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(libi2c)
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
PHP_RINIT_FUNCTION(libi2c)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(libi2c)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(libi2c)
{
	php_info_print_table_start();
	//php_info_print_table_header(2, "libi2c support", "enabled");
	php_info_print_table_row(2, "libi2c support", "enabled");
	php_info_print_table_row(2, "libi2c Version", "1.0");
	php_info_print_table_row(2, "Enable_Functions", "open,read,readblock,write,writeblock");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_libi2c_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_libi2c_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "libi2c", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
 
PHP_METHOD(i2c, __construct) {
           
           
           
}
PHP_METHOD(i2c, open) {
            char filename[20];
            long int adapter,addr,file;
            
             //获取参数
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &adapter, &addr) == FAILURE) {
                   // WRONG_PARAM_COUNT;
                WRONG_PARAM_COUNT;
                RETURN_FALSE;
                 
            }
 		
 		snprintf(filename, 19, "/dev/i2c-%d", adapter);

		file = open(filename, O_RDWR);

		if (file < 0) {

			RETURN_FALSE;
		}
	
		if (ioctl(file, I2C_SLAVE, addr) < 0) {
			
			RETURN_FALSE;

		}
	
            //更改_x,_y属性值
            zend_update_property_long(Z_OBJCE_P(getThis()), getThis(), ZEND_STRL("_adapter"), adapter TSRMLS_CC);
            zend_update_property_long(Z_OBJCE_P(getThis()), getThis(), ZEND_STRL("_addr"), addr TSRMLS_CC);
 	    zend_update_property_long(Z_OBJCE_P(getThis()), getThis(), ZEND_STRL("_file"), file TSRMLS_CC);
            RETURN_TRUE;
     
}
PHP_METHOD(i2c, read) {
           long int addr,file;
          zval *zfile;
            
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &addr) == FAILURE) {
                   WRONG_PARAM_COUNT;
                   RETURN_FALSE;
            }
		__s32 res;
		
		zfile = zend_read_property(Z_OBJCE_P(getThis()), getThis(), ZEND_STRL("_file"), 0 TSRMLS_CC);
		file = Z_LVAL_P(zfile);
		
		res = i2c_smbus_read_byte_data(file, addr);
		if (res < 0) {
			RETURN_FALSE;
			//RETURN_LONG(file);
		}
		
		RETURN_LONG(res);
}
PHP_METHOD(i2c, readblock) {
            RETURN_FALSE;
}
PHP_METHOD(i2c, write) {
            long int addr,file,d;
          zval *zfile;
            
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &addr,&d) == FAILURE) {
                   WRONG_PARAM_COUNT;
                   RETURN_FALSE;
            }
		__s32 res;
		
		zfile = zend_read_property(Z_OBJCE_P(getThis()), getThis(), ZEND_STRL("_file"), 0 TSRMLS_CC);
		file = Z_LVAL_P(zfile);
		
		res = i2c_smbus_write_byte_data(file,addr,d);

		if (res < 0 ) {
			RETURN_FALSE;
		}
 
            RETURN_TRUE;
}
PHP_METHOD(i2c, writeblock) {
            RETURN_FALSE;
}


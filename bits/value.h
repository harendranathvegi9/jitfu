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
  | Author: krakjoe@php.net                                              |
  +----------------------------------------------------------------------+
*/
#ifndef HAVE_BITS_VALUE_H
#define HAVE_BITS_VALUE_H

#define PHP_JIT_VALUE_FUNCTIONS \
	JIT_FE(jit_value_get_param) \
	JIT_FE(jit_value_create_long_constant) \
	JIT_FE(jit_value_create_nint_constant) \
	JIT_FE(jit_value_create_float32_constant) \
	JIT_FE(jit_value_create_float64_constant) \
	JIT_FE(jit_value_create_nfloat_constant) \
	JIT_FE(jit_value_is_temporary) \
	JIT_FE(jit_value_is_local) \
	JIT_FE(jit_value_is_constant) \
	JIT_FE(jit_value_is_parameter)

static const char *le_jit_value_name = "jit value";
static       int   le_jit_value;

ZEND_RSRC_DTOR_FUNC(php_jit_value_dtor);

static inline php_jit_minit_value(int module_number TSRMLS_DC) {
	le_jit_value = zend_register_list_destructors_ex
		(php_jit_value_dtor, NULL, le_jit_value_name, module_number);
}

ZEND_BEGIN_ARG_INFO_EX(jit_value_get_param_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, function)
	ZEND_ARG_INFO(0, param)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jit_value_create_long_constant_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, function)
	ZEND_ARG_INFO(0, long)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jit_value_create_nint_constant_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, function)
	ZEND_ARG_INFO(0, nint)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jit_value_create_float32_constant_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, function)
	ZEND_ARG_INFO(0, float32)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jit_value_create_float64_constant_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, function)
	ZEND_ARG_INFO(0, float64)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jit_value_create_nfloat_constant_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, function)
	ZEND_ARG_INFO(0, nfloat)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jit_value_is_temporary_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jit_value_is_local_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jit_value_is_constant_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jit_value_is_parameter_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

PHP_FUNCTION(jit_value_get_param);
PHP_FUNCTION(jit_value_create_long_constant);
PHP_FUNCTION(jit_value_create_nint_constant);
PHP_FUNCTION(jit_value_create_float32_constant);
PHP_FUNCTION(jit_value_create_float64_constant);
PHP_FUNCTION(jit_value_create_nfloat_constant);
PHP_FUNCTION(jit_value_is_temporary);
PHP_FUNCTION(jit_value_is_local);
PHP_FUNCTION(jit_value_is_constant);
PHP_FUNCTION(jit_value_is_parameter);
#else
#ifndef HAVE_BITS_VALUE
#define HAVE_BITS_VALUE

/* {{{ php_jit_value_dtor */
ZEND_RSRC_DTOR_FUNC(php_jit_value_dtor) {
	
} /* }}} */

/* {{{ jit_value_t jit_value_get_param(jit_function_t function, int param) */
PHP_FUNCTION(jit_value_get_param) {
	zval *resource;
	long param;
	jit_function_t function;
	jit_value_t value;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &resource, &param) != SUCCESS) {
		return;
	}

	ZEND_FETCH_RESOURCE(function, jit_function_t, &resource, -1, le_jit_function_name, le_jit_function);

	value = jit_value_get_param(function, param);

	ZEND_REGISTER_RESOURCE(return_value, value, le_jit_value);
} /* }}} */

/* {{{ jit_value_t jit_value_create_long_constant(jit_function_t function, jit_type_t type, long num) */
PHP_FUNCTION(jit_value_create_long_constant) {
	zval *zfunction;
	long num, type;
	jit_function_t function;
	jit_value_t value;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &zfunction, &type, &num) != SUCCESS) {
		return;
	}

	ZEND_FETCH_RESOURCE(function, jit_function_t, &zfunction, -1, le_jit_function_name, le_jit_function);

	value = jit_value_create_long_constant(function, (jit_type_t) type, num);

	ZEND_REGISTER_RESOURCE(return_value, value, le_jit_value);
} /* }}} */

/* {{{ jit_value_t jit_value_create_nint_constant(jit_function_t function, jit_type_t type, long num) */
PHP_FUNCTION(jit_value_create_nint_constant) {
	zval *zfunction;
	long num, type;
	jit_function_t function;
	jit_value_t value;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &zfunction, &type, &num) != SUCCESS) {
		return;
	}

	ZEND_FETCH_RESOURCE(function, jit_function_t, &zfunction, -1, le_jit_function_name, le_jit_function);

	value = jit_value_create_nint_constant(function, (jit_type_t) type, num);

	ZEND_REGISTER_RESOURCE(return_value, value, le_jit_value);
} /* }}} */

/* {{{ jit_value_t jit_value_create_float32_constant(jit_function_t function, jit_type_t type, float float32) */
PHP_FUNCTION(jit_value_create_float32_constant) {
	zval *zfunction;
	long num, type;
	jit_function_t function;
	jit_value_t value;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &zfunction, &type, &num) != SUCCESS) {
		return;
	}

	ZEND_FETCH_RESOURCE(function, jit_function_t, &zfunction, -1, le_jit_function_name, le_jit_function);

	value = jit_value_create_float32_constant(function, (jit_type_t) type, num);

	ZEND_REGISTER_RESOURCE(return_value, value, le_jit_value);
} /* }}} */

/* {{{ jit_value_t jit_value_create_float64_constant(jit_function_t function, jit_type_t type, float float64) */
PHP_FUNCTION(jit_value_create_float64_constant) {
	zval *zfunction;
	long num, type;
	jit_function_t function;
	jit_value_t value;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &zfunction, &type, &num) != SUCCESS) {
		return;
	}

	ZEND_FETCH_RESOURCE(function, jit_function_t, &zfunction, -1, le_jit_function_name, le_jit_function);

	value = jit_value_create_float64_constant(function, (jit_type_t) type, num);

	ZEND_REGISTER_RESOURCE(return_value, value, le_jit_value);
} /* }}} */

/* {{{ jit_value_t jit_value_create_nfloat_constant(jit_function_t function, jit_type_t type, float nfloat) */
PHP_FUNCTION(jit_value_create_nfloat_constant) {
	zval *zfunction;
	long num, type;
	jit_function_t function;
	jit_value_t value;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &zfunction, &type, &num) != SUCCESS) {
		return;
	}

	ZEND_FETCH_RESOURCE(function, jit_function_t, &zfunction, -1, le_jit_function_name, le_jit_function);

	value = jit_value_create_nfloat_constant(function, (jit_type_t) type, num);

	ZEND_REGISTER_RESOURCE(return_value, value, le_jit_value);
} /* }}} */

/* {{{ bool jit_value_is_temporary(jit_value_t value) */
PHP_FUNCTION(jit_value_is_temporary) {
	zval *zvalue;
	jit_value_t value;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zvalue) != SUCCESS) {
		return;
	}

	ZEND_FETCH_RESOURCE(value,    jit_value_t,    &zvalue,    -1, le_jit_value_name,    le_jit_value);
	
	RETURN_BOOL(jit_value_is_temporary(value));
} /* }}} */

/* {{{ bool jit_value_is_local(jit_value_t value) */
PHP_FUNCTION(jit_value_is_local) {
	zval *zvalue;
	jit_value_t value;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zvalue) != SUCCESS) {
		return;
	}

	ZEND_FETCH_RESOURCE(value,    jit_value_t,    &zvalue,    -1, le_jit_value_name,    le_jit_value);
	
	RETURN_BOOL(jit_value_is_local(value));
} /* }}} */

/* {{{ bool jit_value_is_constant(jit_value_t value) */
PHP_FUNCTION(jit_value_is_constant) {
	zval *zvalue;
	jit_value_t value;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zvalue) != SUCCESS) {
		return;
	}

	ZEND_FETCH_RESOURCE(value,    jit_value_t,    &zvalue,    -1, le_jit_value_name,    le_jit_value);
	
	RETURN_BOOL(jit_value_is_constant(value));
} /* }}} */

/* {{{ bool jit_value_is_parameter(jit_value_t value) */
PHP_FUNCTION(jit_value_is_parameter) {
	zval *zvalue;
	jit_value_t value;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zvalue) != SUCCESS) {
		return;
	}

	ZEND_FETCH_RESOURCE(value,    jit_value_t,    &zvalue,    -1, le_jit_value_name,    le_jit_value);
	
	RETURN_BOOL(jit_value_is_parameter(value));
} /* }}} */
#endif
#endif

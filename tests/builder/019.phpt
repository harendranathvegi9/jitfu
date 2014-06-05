--TEST--
Test builder load element strings
--SKIPIF--
<?php if (!extension_loaded("jitfu")) die("skip JITFu not loaded"); ?>
--FILE--
<?php
use JITFU\Context;
use JITFU\Type;
use JITFU\Signature;
use JITFU\Func;
use JITFu\Value;
use JITFU\Builder;

$context = new Context();

$string  = new Type(JIT_TYPE_STRING);
$strings = new Type($string, true);

/*
string function (string *n, long f) {
	return n[f];
}
*/

$function = new Func($context, new Signature($string, [$strings, $string]));

new Builder($function, function(Value $n, Value $f) {
	$this->doReturn(
		$this->doLoadElem($n, $f));
});

$strings = [
	"Hello",
	"World",
	"PHP",
	"Rocks"
];

var_dump(
	$function($strings, 0),
	$function($strings, 1),
	$function($strings, 2),
	$function($strings, 3));
?>
--EXPECT--
string(5) "Hello"
string(5) "World"
string(3) "PHP"
string(5) "Rocks"
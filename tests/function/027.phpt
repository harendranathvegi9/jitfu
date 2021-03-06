--TEST--
Test doSize on strings
--SKIPIF--
<?php if (!extension_loaded("jitfu")) die("skip JITFu not loaded"); ?>
--FILE--
<?php
use JITFU\Context;
use JITFU\Type;
use JITFU\Signature;
use JITFU\Func;
use JITFU\Value;

$context = new Context();

$string  = Type::of(Type::string);
$strings = new Type($string, true);
$sstrings = new Type($strings, true);
$int    = Type::of(Type::int);

$function = new Func($context, new Signature($int, [$string]), function($args) {
	$this->doReturn(
		$this->doSize($args[0]));
});

var_dump(
	$function("hello world"));

$function = new Func($context, new Signature($int, [$strings]), function($args) {
	$zero = new Value($this, 0, Type::of(Type::int));
	$first = $this
		->doLoadElem($args[0], $zero);
	$this->doReturn($this->doSize($first));
});

var_dump(
	$function(["hello world"]));
	
$function = new Func($context, new Signature($int, [$sstrings]), function($args) {
	$zero = new Value($this, 0, Type::of(Type::int));
	$first = $this
		->doLoadElem($args[0], $zero);
	
	$this->doReturn(
		$this->doSize(
			$this->doLoadElem($first, $zero)));
});

var_dump(
	$function([["hello world"]]));
?>
--EXPECT--
int(11)
int(11)
int(11)

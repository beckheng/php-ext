<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('substr_json')) {
	dl('substr_json.' . PHP_SHLIB_SUFFIX);
}
$module = 'substr_json';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
$function = 'confirm_' . $module . '_compiled';
if (extension_loaded($module)) {
	$str = $function($module);
} else {
	$str = "Module $module is not compiled into PHP";
}
echo "$str\n";

echo substr_json('{ "body": { "name": "beckh[eng", "age": 35, "address": "kkk\"sds\"ds看啊df" } }', 10), "$br\n";
?>

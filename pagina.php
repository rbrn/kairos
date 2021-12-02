<?php
$lifetime=mktime(12,50,30,6,20,2050);
$lingua=$_REQUEST["lingua"];
$kairos_cookie=$_REQUEST["kairos_cookie"];
$kairos_cookie_lingua=$_REQUEST["kairos_cookie_lingua"];

if (isset($lingua)) {
	$kairos_cookie_lingua=$lingua;
	setcookie("kairos_cookie_lingua",$lingua,$lifetime,"/",$dominio);
};

if (!isset($lingua)) {
	if (!isset($kairos_cookie_lingua)) {
		$lingua="it";
		$kairos_cookie_lingua=$lingua;
		setcookie("kairos_cookie_lingua",$lingua,$lifetime,"/",$dominio);
	};
};

$lingua=$kairos_cookie_lingua;
$file_lingua="./include/stringhe_".$lingua.".inc";

if (!file_exists($file_lingua)) {
	$lingua="it";
	setcookie("kairos_cookie_lingua",$lingua,$lifetime,"/",$dominio);
	$file_lingua="stringhe_it.inc";
};

require "$file_lingua";

$risorsa=$_REQUEST["risorsa"];
$msg=$_REQUEST["msg"];
require "./include/testata_neutra.inc";
require "./pagine/$risorsa.inc";
require "./include/piede.inc";
?>


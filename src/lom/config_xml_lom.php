<?php
$opera=false;
$win_ie=false;
$mozilla=false;
$firefox=false;

if (ereg('MSIE',$_SERVER["HTTP_USER_AGENT"]) and ereg('Windows',$_SERVER["HTTP_USER_AGENT"])) {
	$win_ie=true;
};

if (ereg('Opera',$_SERVER["HTTP_USER_AGENT"])) {
	$opera=true;
};

if (ereg('Gecko',$_SERVER["HTTP_USER_AGENT"]) and !ereg('Firefox',$_SERVER["HTTP_USER_AGENT"])) {
	$mozilla=true;
};

if (ereg('Gecko',$_SERVER["HTTP_USER_AGENT"]) and ereg('Firefox',$_SERVER["HTTP_USER_AGENT"])) {
	$firefox=true;
};

?>

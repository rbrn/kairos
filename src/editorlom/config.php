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

$DBHOST = "localhost";
$DBUSER = "g_user_db";
$DBPWD = "gara29mond";
$DBASE = "kairos_lom";

$colore_sfondo_menu="#281d8f";
$colore_barra_testata="#e0e4f6";
$colore_scuro_neutro="#cccccc";
$colore_sfondo_neutro="#efefef";

$colore_testo="#535190";
$colore_testonegativo="#535190";

$colore_link="#535190";

$colore_bordo="#00a799";
$colore_sfondo_testata="#3EAA8F";

$colore_sfondo="#EBFFFA";
$colore_scuro="#92D8C7";

/*
$DBHOST = "localhost";
$DBUSER = "root";
$DBPWD = "";
*/

?>

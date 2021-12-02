<?php

include_once 'include/properties.php';
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

require "./teleskill/teleskill.php";

$ts=new Teleskill();

$res=$ts->canOpenRoom('2006-10-24 12:00:00','2006-10-24 13:00:00');

echo "<br><br>errcode: $res[errorcode] errormessage: $res[errormessage]<br>br>";

$res=$ts->openRoom('fleo','prova','2006-10-25 08:53:00','2006-10-25 9:00:00');

echo "<br><br>errcode: $res[errorcode] errormessage: $res[errormessage] roomid: $res[roomid]  <br><br>";
/*
if (!$res[errorcode]) {
	$roomid=$res[roomid];

	$res=$ts->loginIntoRoom($roomid,2,"fleo","Francesco","fleo@espertoweb.it");

	echo "<br><br>errcode: $res[errorcode] errormessage: $res[errormessage] url: $res[url]  <br><br>";
};
*/
?>

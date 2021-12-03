<?php
require "./include/init_sito.inc";
$audio=$_REQUEST["audio"];
$lifetime=mktime(12,50,30,6,20,2050);
setcookie("wimba_cookie",$audio,$lifetime,"/");
$query_string=$_SERVER["QUERY_STRING"];

if ($audio=='on') {
	$query_string=str_replace("audio=on&","",$query_string);
} else {
	$query_string=str_replace("audio=off&","",$query_string);
};

$url="index.php?".$query_string;
Header("Location:$url");
?>

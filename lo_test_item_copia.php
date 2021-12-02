<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$risorsa_padre=$_REQUEST["risorsa_padre"];
$id_item=$_REQUEST["id_item"];
setcookie("kairos_cookie_copia_item",$id_item,0,"/");

$url="index.php?risorsa=repository_index&id_cartella=$risorsa_padre";

Header("Location: $url");

?>

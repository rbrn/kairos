<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

// connessione al dbatlante
$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_utente=$kairos_cookie[0];

// connessione al dbatlante
$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	


$query = "UPDATE hp_news SET posizione=0 WHERE id_news='$id_news'";
$result=$mysqli->query($query);

$url="index.php?risorsa=index";
Header("Location: $url");
?>

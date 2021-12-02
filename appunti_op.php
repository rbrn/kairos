<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente1=$kairos_cookie[0];
$testo=$_REQUEST["testo"];

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query = "REPLACE INTO appunti SET id_utente='$id_utente1', testo='$testo'";
$result = $mysqli->query($query);

Header("Location:appunti.php");
?>

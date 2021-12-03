<?php
require "./include/init_sito.inc";

$id_corso=$_REQUEST["id_corso"];
$descrizione=mysql_real_escape_string($_REQUEST["descrizione"]);
$testo=mysql_real_escape_string($_REQUEST["testo"]);

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query="UPDATE corso SET 
	descrizione='$descrizione',
	testo='$testo'
 WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=corsi_index");  
?>

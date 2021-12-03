<?php
require "./include/init_sito.inc";
 
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_utente=$_REQUEST["id_utente"];
$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];

$query = "DELETE FROM iscrizioni_corso WHERE id_utente='$id_utente' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query = "DELETE FROM iscrizioni_gruppo_pw WHERE id_utente='$id_utente' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

Header("Location:index.php?risorsa=corsi_gestione_iscrizioni_form&id_corso=$id_corso&id_edizione=$id_edizione");
?>

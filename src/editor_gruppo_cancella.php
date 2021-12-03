<?php
require "./include/init_sito.inc";

$id_editor_gruppo=$_REQUEST["id_editor_gruppo"];

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query="DELETE FROM  editor_gruppo  WHERE id_editor_gruppo='$id_editor_gruppo'";
$result = $mysqli->query($query);

$query="DELETE FROM  editor_gruppo_utenti  WHERE id_editor_gruppo='$id_editor_gruppo'";
$result = $mysqli->query($query);


header("Location:index.php?risorsa=editor_gruppi");
?>

<?php
require "./include/init_sito.inc";
$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_risorsa=$_REQUEST["id_risorsa"];
$id_commento=$_REQUEST["id_commento"];

$query = "DELETE FROM risorse_materiali_commenti WHERE id_commento='$id_commento'";
$result=$mysqli->query($query);

Header("Location:materiali_browse.php?risorsa=$id_risorsa");
?>

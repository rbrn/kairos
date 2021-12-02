<?php
require "./include/init_sito.inc";
$id_risorsa=$_REQUEST["id_risorsa"];
$id_commento=$_REQUEST["id_commento"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);		

$query = "DELETE FROM commento_lab_materiali WHERE id_commento=$id_commento";
$result=$mysqli->query($query);

Header("Location:index.php?risorsa=lab_materiali_view&id_risorsa=$id_risorsa");		
?>

<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_item_opzione=$_REQUEST["id_pezzo"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

$query="SELECT * FROM lo_test_item_opzioni WHERE id_item_opzione='$id_item_opzione'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$id_item=$riga["id_item"];
$tipo_opzione=$riga["tipo"];


$url="index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre&modifica=$id_item_opzione";

Header("Location: $url");

?>

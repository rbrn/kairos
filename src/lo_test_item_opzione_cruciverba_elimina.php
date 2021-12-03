<?php
require "./include/init_sito.inc";

$id_item_opzione=$_REQUEST["id_item_opzione"];
$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query = "DELETE FROM lo_test_item_opzioni_cruciverba WHERE id_item_opzione='$id_item_opzione'";
$result=$mysqli->query($query);

header("Location:index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre");

?>

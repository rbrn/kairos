<?php
require "./include/init_sito.inc";

$id_commento=$_REQUEST["id_commento"];
$tipo_elemento=$_REQUEST["tipo_elemento"];
$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query = "DELETE FROM lo_test_commento WHERE id_commento='$id_commento'";
$result=$mysqli->query($query);

$url="index.php?risorsa=lo_test_commento_edit&tipo_elemento=$tipo_elemento&id_item=$id_item&risorsa_padre=$risorsa_padre";

Header("Location: $url");

?>

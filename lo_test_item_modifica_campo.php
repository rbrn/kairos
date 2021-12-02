<?php
require "./include/init_sito.inc";


$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$campo=$_REQUEST["campo"];
$valore=$_REQUEST[$campo];

$id_utente=$kairos_cookie[0];

			
$query = "UPDATE lo_test_item SET  
$campo='$valore'
WHERE id_item='$id_item'
";
$result=$mysqli->query($query);

$url="index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre";
	
Header("Location: $url");

?>

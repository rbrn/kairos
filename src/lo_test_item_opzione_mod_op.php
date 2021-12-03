<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_item=$_REQUEST["id_item"];
$id_item_opzione=$_REQUEST["id_item_opzione"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$risposta_opzione=$_REQUEST["opzione"];
$punteggio=$_REQUEST["punteggio"];
$id_utente=$kairos_cookie[0];
			
$query = "UPDATE lo_test_item_opzioni SET  
risposta_opzione='$risposta_opzione',
punteggio='$punteggio'
WHERE id_item_opzione='$id_item_opzione'
";
$result=$mysqli->query($query);

$url="index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre";

Header("Location: $url");

?>

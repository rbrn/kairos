<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_item=$_REQUEST["id_item"];
$id_item_opzione=$_REQUEST["id_item_opzione"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$risposta_giusta=$_REQUEST["risposta_giusta"];
$punteggio=$_REQUEST["punteggio"];
$limite_caratteri=$_REQUEST["limite_caratteri"];
$case_sensitive=$_REQUEST["case_sensitive"];
$id_utente=$kairos_cookie[0];


if ($id_item_opzione) {
	$statement="UPDATE";
	$where="WHERE id_item_opzione='$id_item_opzione'";
} else {
	$statement="INSERT INTO";
	$where="";
};			
$query = $statement." lo_test_item_opzioni SET  
id_item='$id_item',
risposta_giusta='$risposta_giusta',
case_sensitive='$case_sensitive',
limite_caratteri='$limite_caratteri' ".$where;
$result=mysql_query($query,$db);

$url="index.php?risorsa=repository_index&id_cartella=$risorsa_padre";

Header("Location: $url");

?>

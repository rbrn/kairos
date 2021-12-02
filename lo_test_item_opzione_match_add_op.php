<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$risposta_opzione=$_REQUEST["opzione"];
$punteggio=$_REQUEST["punteggio"];
$lato=$_REQUEST["lato"];
$id_item_esatto=$_REQUEST["id_item_esatto"];
$id_utente=$kairos_cookie[0];

if ($lato=="sx") {
	$tipo_opzione="1";
} else {
	$tipo_opzione="2";
};

$query="SELECT MAX(posizione) AS max_pos FROM lo_test_item_opzioni WHERE id_item='$id_item' AND tipo_opzione='$tipo_opzione'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$posizione=$riga[max_pos]+1;
			
$query = "INSERT INTO lo_test_item_opzioni SET  
id_item='$id_item',
posizione='$posizione',
risposta_opzione='$risposta_opzione',
tipo_opzione='$tipo_opzione',
id_item_esatto='$id_item_esatto',
punteggio='$punteggio',
id_editor='$id_utente'
";
$result=$mysqli->query($query);

$url="index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre";

Header("Location: $url");

?>

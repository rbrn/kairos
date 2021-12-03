<?php
require "./include/init_sito.inc";

$id_item_opzione=$_REQUEST["id_item_opzione"];
$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	


$query = "DELETE FROM lo_test_item_opzioni WHERE id_item_opzione='$id_item_opzione'";
$result=$mysqli->query($query);

$pos=1;
$query="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
$result=$mysqli->query($query);
while ($riga=$result->fetch_array()) {
	$id_item_opzione = $riga["id_item_opzione"];
	$query2="UPDATE lo_test_item_opzioni SET posizione='$pos' WHERE id_item_opzione='$id_item_opzione'";
	$mysqli->query($query2);
	$pos++;
};

	
header("Location:index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre");

?>

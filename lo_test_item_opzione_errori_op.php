<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$risposta_giusta=$_REQUEST["risposta_giusta"];
$nerrori=$_REQUEST["nerrori"];

$id_utente=$kairos_cookie[0];

$query = "DELETE FROM lo_test_item_opzioni WHERE id_item='$id_item'";
$result=$mysqli->query($query);
	
for ($i=0;$i<$nerrori;$i++) {
	$pos=$i+1;
	$query="SELECT id_item FROM lo_test_item_opzioni WHERE id_item='$id_item' AND posizione='$pos'";
	$result=$mysqli->query($query);
	if ($result->num_rows) {
		$statement="UPDATE";
		$where="WHERE id_item='$id_item' AND posizione='$pos'";
	} else {
		$statement="INSERT INTO";
		$where="";
	};
	
	$query = "$statement lo_test_item_opzioni SET  
id_item='$id_item',
posizione='$pos',
risposta_giusta='$risposta_giusta[$i]',
id_editor='$id_utente'
$where
";
	$result=mysql_query($query,$db);
};

$query="SELECT id_item FROM lo_test_item_opzioni WHERE id_item='$id_item'";
$result=$mysqli->query($query);
if ($result->num_rows>$nspazi) {
	$inf=$nerrori+1;
	$sup=$result->num_rows+1;
	for ($i=$inf;$i<$sup;$i++) {
		$query="DELETE FROM lo_test_item_opzioni WHERE id_item='$id_item' AND posizione='$i'";
		$result=$mysqli->query($query);
	};
};

$url="index.php?risorsa=repository_index&id_cartella=$risorsa_padre";

Header("Location: $url");

?>

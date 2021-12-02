<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);			

$id_item_opzione=$_REQUEST["id_item_opzione"];
$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$azione=$_REQUEST["azione"];

$query = "SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
$result=$mysqli->query($query);

$id_prec="";
$id_succ="";
$pos_prec="";
$pos_succ="";
$continua=true;

while ($riga=$result->fetch_array() and $continua) {
	$id_att=$riga[id_item_opzione];
	$pos_att=$riga[posizione];
	if (!$pos_att) $pos_att=0;

	$query_succ = "SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND posizione>$pos_att ORDER BY posizione";
	$result_succ=$mysqli->query($query_succ);

	$riga_succ=$result_succ->fetch_array();
	if ($riga) {
		$id_succ=$riga_succ[id_item_opzione];
		$pos_succ=$riga_succ[posizione];
	};
	if ($id_att==$id_item_opzione) {
		if ($azione=="up") {
			if ($id_prec) {
				$query_s="UPDATE lo_test_item_opzioni SET posizione='$pos_att' WHERE id_item_opzione='$id_prec'";
				$mysqli->query($query_s);
				
				$query_s="UPDATE lo_test_item_opzioni SET posizione='$pos_prec' WHERE id_item_opzione='$id_att'";
				$mysqli->query($query_s);
			};
		} else {
			if ($id_succ) {
				$query_s="UPDATE lo_test_item_opzioni SET posizione='$pos_att' WHERE id_item_opzione='$id_succ'";
				$mysqli->query($query_s);
				
				$query_s="UPDATE lo_test_item_opzioni SET posizione='$pos_succ' WHERE id_item_opzione='$id_att'";
				$mysqli->query($query_s);
			};
		};	
		$continua=false;
	};
	$pos_prec=$pos_att;
	$id_prec=$id_att;		
};

Header("Location:index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre");
?>

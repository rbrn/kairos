<?php
require "./include/init_sito.inc";

function setup_posizione($id_padre) {
	global 	$DBHOST,$DBASE,$DBUSER,$DBPWD, $mysqli;

	$pos=1;
	$query="SELECT id_risorsa,tipo FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo='20' or tipo='200' or tipo='201' or tipo='202') ORDER BY posizione,id_risorsa";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_risorsa = $riga["id_risorsa"];
		$tipo = $riga["tipo"];
		$query2="UPDATE risorse_materiali SET posizione='$pos' WHERE id_risorsa='$id_risorsa'";
		$mysqli->query($query2);
		$pos++;
		if ($tipo==2) {
			setup_posizione($id_risorsa);
		};
	};	
};

$id_risorsa=$_REQUEST["id_risorsa"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$azione=$_REQUEST["azione"];

setup_posizione($risorsa_padre);

$query = "SELECT id_risorsa,posizione FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' AND (tipo='20' or tipo='200' or tipo='201' or tipo='202') ORDER BY posizione,id_risorsa";
$result=$mysqli->query($query);

$id_prec="";
$id_succ="";
$pos_prec="";
$pos_succ="";
$continua=true;

while ($riga=$result->fetch_array() and $continua) {
	$id_att=$riga[id_risorsa];
	$pos_att=$riga[posizione];
	if (!$pos_att) $pos_att=0;

	$query_succ = "SELECT id_risorsa,posizione FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' AND (tipo='20' or tipo='200' or tipo='201' or tipo='202') AND posizione>$pos_att ORDER BY posizione,id_risorsa";
	$result_succ=$mysqli->query($query_succ);

	$riga_succ=$result_succ->fetch_array();
	if ($riga) {
		$id_succ=$riga_succ[id_risorsa];
		$pos_succ=$riga_succ[posizione];
	};
	if ($id_att==$id_risorsa) {
		//echo "id_att=$id_att pos_att=$pos_att id_prec=$id_prec pos_prec=$pos_prec id_succc=$id_prec pos_succ=$pos_prec";
		if ($azione=="up") {
			if ($id_prec) {
				$query_s="UPDATE risorse_materiali SET posizione='$pos_att' WHERE id_risorsa='$id_prec'";
				$mysqli->query($query_s);
				
				$query_s="UPDATE risorse_materiali SET posizione='$pos_prec' WHERE id_risorsa='$id_att'";
				$mysqli->query($query_s);
			};
		} else {
			if ($id_succ) {
				$query_s="UPDATE risorse_materiali SET posizione='$pos_att' WHERE id_risorsa='$id_succ'";
				$mysqli->query($query_s);
				
				$query_s="UPDATE risorse_materiali SET posizione='$pos_succ' WHERE id_risorsa='$id_att'";
				$mysqli->query($query_s);
			};
		};	
		$continua=false;
	};
	$pos_prec=$pos_att;
	$id_prec=$id_att;		
};

Header("Location:index.php?risorsa=repository_index&id_cartella=$risorsa_padre");	
?>

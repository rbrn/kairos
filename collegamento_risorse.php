<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);			

$id_utente=$kairos_cookie[0];

$collega_risorse=$_REQUEST["collega_risorse"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
//echo(count($collega_risorse));
//echo "<br>";
for ($i=0;$i<count($collega_risorse);$i++) {
	$id_gruppo=$collega_risorse[$i];
	$id_risorsa=uniqid($id_gruppo);
	//echo "$id_gruppo - $id_risorsa<br>";
	
	$query="SELECT titolo,descrizione,parole_chiave FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
    $result = $mysqli->query($query);
    $riga=$result->fetch_array();
	$titolo=addslashes($riga["titolo"]);
	$descrizione=addslashes($riga["descrizione"]);
	$parole_chiave=addslashes($riga["parole_chiave"]);
	
	$query="SELECT max(posizione) AS num_pag FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre'";
    $result = $mysqli->query($query);
    $riga=$result->fetch_array();
	$posizione=$riga[num_pag]+1;
	
	$query="INSERT INTO risorse_materiali SET 
	tipo='4',
	risorsa_padre='$risorsa_padre',
	id_risorsa='$id_risorsa',
	id_gruppo='$id_gruppo',
	id_autore='$id_utente',
	descrizione='$descrizione',
	titolo='$titolo',
	parole_chiave='$parole_chiave',
	posizione='$posizione',
	id_editor='$id_utente',
	data_crea=NOW()";
    $result = $mysqli->query($query);
};

Header("Location:index.php?risorsa=materiali_index&id_cartella=$risorsa_padre");	
?>

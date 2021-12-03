<?php
require "./include/init_sito.inc";
$id_risorsa=$_REQUEST["id_risorsa"];
$ex_id_risorsa=$_REQUEST["ex_id_risorsa"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$ex_risorsa_padre=$_REQUEST["ex_risorsa_padre"];
$titolo=$_REQUEST["titolo"];
$id_autore=$_REQUEST["id_autore"];
$id_editor_gruppo=$_REQUEST["id_editor_gruppo"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

if ($ex_id_risorsa<>$id_risorsa) {

	$query="SELECT id_risorsa FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";		
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();

	$errore="";

	if ($riga) {
		$errore .= "<br>$stringa[errore_id_esiste]";
	};	

	if (!ereg("^[a-zA-Z0-9_]+$",$id_risorsa)) {
	$errore .= "<br>$stringa[errore_solo_lettere]";
	};
	
								
	if ($errore) {
		$msg=ereg_replace(" ","%20",$errore);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
	};

	
			
	$query = "UPDATE risorse_materiali 
				SET 
					risorsa_padre='$id_risorsa'
				WHERE risorsa_padre='$ex_id_risorsa'";
			
	$result=$mysqli->query($query);	
};

$id_utente = $kairos_cookie["0"];
$query = "UPDATE risorse_materiali 		
			SET 
				id_risorsa='$id_risorsa',
				risorsa_padre='$risorsa_padre',
				titolo='$titolo',
				id_autore='$id_autore',
				id_editor_gruppo='$id_editor_gruppo'
			WHERE id_risorsa='$ex_id_risorsa'";
$result=$mysqli->query($query);

$query="INSERT INTO materiale_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='modificato',"
." data_evento=NOW()";
$mysqli->query($query);

Header("Location:index.php?risorsa=materiali_index&id_cartella=$risorsa_padre");			
?>

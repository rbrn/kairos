<?php
require "./include/init_sito.inc";
$id_risorsa=$_REQUEST["id_risorsa"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$titolo=$_REQUEST["titolo"];
$id_autore=$_REQUEST["id_autore"];
$id_gruppo=$_REQUEST["id_gruppo"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$errore="";
if (!$titolo) {
	$errore .= "<br>Manca descrizione cartella";
};		

if ($errore) {
	$msg=ereg_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

$id_utente = $kairos_cookie["0"];
$query = "UPDATE materiali_gruppo 		
			SET 
				titolo='$titolo',
				id_autore='$id_autore',
				id_gruppo='$id_gruppo'
			WHERE id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);

$query="INSERT INTO materiale_gruppo_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='modificato',"
." data_evento=NOW()";
$mysqli->query($query);

Header("Location:index.php?risorsa=materiali_gruppo_index&id_cartella=$risorsa_padre");			
?>

<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$risorsa_padre=$_REQUEST["risorsa_padre"];
$titolo=$_REQUEST["titolo"];
$id_autore=$_REQUEST["id_autore"];
$id_gruppo=$_REQUEST["id_gruppo"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

// controllo se tutti i campi obbligatori sono stati compilati

$errore = ""; 
if (!$titolo) {
	$errore .= "<br>Manca descrizione cartella";
};		

if ($risorsa_padre=="root") {
	$query = "SELECT id_risorsa FROM materiali_gruppo WHERE risorsa_padre='$risorsa_padre' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo'";
	$result=$mysqli->query($query);
	if ($result->num_rows) {
		$errore="<br>Esiste giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ una cartella assegnata a questo project work";
	};
};

if ($errore) {
	$msg=ereg_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};


$id_utente = $kairos_cookie["0"];

$query="SELECT max(posizione) AS num_pag FROM materiali_gruppo WHERE risorsa_padre='$risorsa_padre' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$posizione=$riga[num_pag]+1;

$query = "INSERT INTO materiali_gruppo (tipo,id_corso,id_edizione,id_gruppo,risorsa_padre,id_autore,data_crea,titolo,posizione,id_editor) VALUES ('$tipo','$id_corso_s','$id_edizione_s','$id_gruppo','$risorsa_padre','$id_autore',NOW(),'$titolo','$posizione','$id_utente')";
$result=$mysqli->query($query);
$id_risorsa=$mysqli->insert_id;

$query = "SELECT id_risorsa FROM materiali_gruppo WHERE risorsa_padre='$risorsa_padre' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";

$result=$mysqli->query($query);
$tot_righe=$result->num_rows;
$pag_size=20;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$query="INSERT INTO materiale_gruppo_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='creato',"
." data_evento=NOW()";
$mysqli->query($query);

echo mysql_error();

Header("Location:index.php?risorsa=materiali_gruppo_index&pagina=$tot_pag&id_cartella=$risorsa_padre");		
?>

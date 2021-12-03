<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$id_risorsa=$_REQUEST["id_risorsa"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$titolo=$_REQUEST["titolo"];
$tipo=$_REQUEST["tipo"];
$id_autore=$_REQUEST["id_autore"];
$id_editor_gruppo=$_REQUEST["id_editor_gruppo"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

// controllo se tutti i campi obbligatori sono stati compilati

$id_risorsa=uniqid("folder_");

$errore = ""; 
if (!$id_risorsa) {
	$errore .= "<br>Manca ID Cartella";
};		

if (!ereg("^[a-zA-Z0-9_]+$",$id_risorsa)) {
	$errore .= "<br>$stringa[errore_solo_lettere]";
};

$query="SELECT id_risorsa FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";		
$result=$mysqli->query($query);
$riga=$result->fetch_array();

if ($riga) {
	$errore .= "<br>$stringa[errore_id_esiste]";
};	
							
if ($errore) {
	$msg=ereg_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};


$id_utente = $kairos_cookie["0"];

$query="SELECT max(posizione) AS num_pag FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' and (tipo='0' or tipo='1' or tipo='2' or tipo='3')";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$posizione=$riga[num_pag]+1;

$query = "INSERT INTO risorse_materiali (id_risorsa,tipo,risorsa_padre,id_autore,data_crea,titolo,posizione,id_editor,id_editor_gruppo) VALUES ('$id_risorsa','$tipo','$risorsa_padre','$id_autore',NOW(),'$titolo','$posizione','$id_utente','$id_editor_gruppo')";
$result=$mysqli->query($query);

$ruolo=ruolo_utente($id_utente);
if ($ruolo=='admin') {
	$query = "SELECT id_risorsa FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' and (tipo='0' or tipo='1' or tipo='2' or tipo='3')";
} else {
	$query = "SELECT id_risorsa FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' AND id_editor='$id_utente' and (tipo='0' or tipo='1' or tipo='2' or tipo='3')";
};
$result=$mysqli->query($query);
$tot_righe=$result->num_rows;
$pag_size=20;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$query="INSERT INTO materiale_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='creato',"
." data_evento=NOW()";
$mysqli->query($query);



Header("Location:index.php?risorsa=materiali_index&pagina=$tot_pag&id_cartella=$risorsa_padre");		
?>

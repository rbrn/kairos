<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$tipo=$_REQUEST["tipo"];
$id_risorsa=$_REQUEST["id_risorsa"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$descrizione=$_REQUEST["descrizione"];
$parole_chiave=$_REQUEST["parole_chiave"];
$livello=$_REQUEST["livello"];
$id_gruppo=$_REQUEST["id_gruppo"];


$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];
$titolo=$_FILES["titolo"]["tmp_name"];
$titolo_size=$_FILES["titolo"]["size"];
$titolo_name=$_FILES["titolo"]["name"];

// controllo se tutti i campi obbligatori sono stati compilati



$errore = ""; 

if (!$id_risorsa) {

	$errore .= "<br>$stringa[errore_manca_id]";

};		



if (!ereg("^[a-zA-Z0-9_]+$",$id_risorsa)) {

	$errore .= "<br>$stringa[errore_solo_lettere]";

};



$query="SELECT id_risorsa FROM risorse WHERE id_risorsa='$id_risorsa'";

$result = $mysqli->query($query);
$riga = $result->fetch_array();

if ($riga) {

$errore .= "<br>$stringa[errore_id_esiste]";

};		


if (!$titolo and $tipo<>'2') {
	$errore .= "<br>$stringa[errore_manca_file]";
};	


if ($titolo_size > $MAX_FILE_SIZE) {
	$errore .= "<br>$stringa[errore_max_file]";
};

			

if ($errore) {
	$msg=ereg_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

$id_utente = $kairos_cookie["0"];


if ($titolo_name) {

	$titolo_name = trim($titolo_name);

	$titolo_name = ereg_replace(" ","",$titolo_name);

	$titolo_name = strtolower($titolo_name);

};



$query = "INSERT INTO risorse (id_risorsa,tipo,risorsa_padre,titolo,descrizione,parole_chiave,id_autore,data_crea,livello,id_gruppo,file_size) VALUES ('$id_risorsa','$tipo','$risorsa_padre','$titolo_name','$descrizione','$parole_chiave','$id_utente',NOW(),'$livello','$id_gruppo','$titolo_size')";
$result = $mysqli->query($query);

	

if ($titolo_name) {

	if (risorsa_admin($id_risorsa)) {

		$fullpath = $PATH_ARCHIVI_ADMIN.$titolo_name;

	} else {

		$fullpath = $PATH_ARCHIVI.$titolo_name;

	};

	copy($titolo,$fullpath);	

};





Header("Location:index.php?risorsa=admin_index&id_cartella=$risorsa_padre");		

?>

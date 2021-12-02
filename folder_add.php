<?php

require "./include/init_sito.inc";

mysql_select_db($DBASE,$db);	

$id_risorsa=mysql_real_escape_string($_REQUEST["id_risorsa"]);

$risorsa_padre=mysql_real_escape_string($_REQUEST["risorsa_padre"]);

$titolo=mysql_real_escape_string($_REQUEST["titolo"]);

$tipo=mysql_real_escape_string($_REQUEST["tipo"]);



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

							

if ($errore) {

	$msg=ereg_replace(" ","%20",$errore);

	Header("Location:index.php?risorsa=msg&msg=$msg");

	exit();

};





$id_utente = $kairos_cookie["0"];



$query = "INSERT INTO risorse (id_risorsa,tipo,risorsa_padre,id_autore,data_crea,titolo) VALUES ('$id_risorsa','$tipo','$risorsa_padre','$id_utente',NOW(),'$titolo')";
$result = $mysqli->query($query);
Header("Location:index.php?risorsa=admin_index&id_cartella=$risorsa_padre");		

?>

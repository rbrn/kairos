<?php
require "./include/init_sito.inc";
$risorsa_padre=$_REQUEST["risorsa_padre"];
$titolo=$_REQUEST["titolo"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

// controllo se tutti i campi obbligatori sono stati compilati

$errore = ""; 

if (!$titolo) {
	$errore .= "<br>$stringa[errore_manca_titolo]";
};	
	
								
if ($errore) {
	$msg=ereg_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};


$id_utente = $kairos_cookie["0"];

$query = "INSERT INTO lab_materiali (id_risorsa,tipo,risorsa_padre,titolo,descrizione,parole_chiave,id_autore,data_crea,id_corso,id_edizione,id_gruppo) VALUES (NULL,'2','$risorsa_padre','$titolo','$descrizione','$parole_chiave','$id_utente',NOW(),'$id_corso_s','$id_edizione_s','$id_gruppo_s')";
$result=$mysqli->query($query);

Header("Location:index.php?risorsa=lab_materiali_index&id_cartella=$risorsa_padre");		
?>

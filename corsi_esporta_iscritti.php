<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);			

$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];

$query="SELECT * FROM corso WHERE id_corso='$id_corso'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$descrizione_corso=$riga["descrizione"];

$query = "SELECT utenti.id_utente,nome,cognome,indirizzo,cap,citta,prov,email,showme FROM utenti,iscrizioni_corso WHERE utenti.id_utente=iscrizioni_corso.id_utente AND id_corso='$id_corso' AND id_edizione='$id_edizione' ORDER BY cognome,nome";

$result=$mysqli->query($query);

if ($cod_area=="kairos_area_corsi") {
	$testo="id utente"."\t"."nome"."\t"."cognome"."\t"."indirizzo"."\t"."cap"."\t"."cittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½"."\t"."prov"."\t"."email"."\t"."eprof"."\n";
} else {
	$testo="id utente"."\t"."nome"."\t"."cognome"."\t"."indirizzo"."\t"."cap"."\t"."cittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½"."\t"."prov"."\t"."email"."\n";
};

while ($utente = $result->fetch_array()) {
	$id_utente = $utente["id_utente"];
	$nome = $utente["nome"];
	$cognome = $utente["cognome"];
	$indirizzo = $utente["indirizzo"];
	$cap = $utente["cap"];
	$citta = $utente["citta"];
	$prov = $utente["prov"];
	$email = $utente["email"];
	$eprof= $utente["showme"];
	
	if ($cod_area=="kairos_area_corsi") {
	$riga=$id_utente."\t".$nome."\t".$cognome."\t".$indirizzo."\t".$cap."\t".$citta."\t".$prov."\t".$email."\t".$eprof."\n";
	} else {
	$riga=$id_utente."\t".$nome."\t".$cognome."\t".$indirizzo."\t".$cap."\t".$citta."\t".$prov."\t".$email."\n";
	};
	
	$testo .=$riga;
	
};
$file="elenco_iscritti_".$id_corso."_".$id_edizione.".txt";
header("Content-Type: text/plain");
header( "Content-Disposition: attachment; filename=$file" ); 
echo($testo);
?>

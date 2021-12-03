<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);			

$id_gruppo=$_REQUEST["id_gruppo"];
$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];

$elenco_attesa=$_REQUEST["elenco_attesa"];
$elenco_classe=$_REQUEST["elenco_classe"];
$aggiungi=$_REQUEST["aggiungi"];
$rimuovi=$_REQUEST["rimuovi"];	
if ($aggiungi) {
	$n = count($elenco_attesa);

	for ($i=0;$i<$n;$i++) {
		$id_utente=$elenco_attesa[$i];
		$query="REPLACE INTO iscrizioni_gruppo_pw SET 
		id_corso='$id_corso',
		id_edizione='$id_edizione',
		id_utente='$id_utente',
		id_gruppo='$id_gruppo'";
        $result = $mysqli->query($query);
	};
	
} else {

	$n = count($elenco_classe);

	for ($i=0;$i<$n;$i++) {
		$id_utente=$elenco_classe[$i];
		$query="DELETE FROM iscrizioni_gruppo_pw  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_utente='$id_utente' AND id_gruppo='$id_gruppo'";
        $result = $mysqli->query($query);
	};
};		

header("Location:index.php?risorsa=corsi_iscrizioni_gruppo_pw&id_corso=$id_corso&id_edizione=$id_edizione&id_gruppo=$id_gruppo");
?>

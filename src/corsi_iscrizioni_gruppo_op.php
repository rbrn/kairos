<?php
require "./include/init_sito.inc";

$id_gruppo=mysql_real_escape_string($_REQUEST["id_gruppo"]);
$id_corso=mysql_real_escape_string($_REQUEST["id_corso"]);
$id_edizione=mysql_real_escape_string($_REQUEST["id_edizione"]);

$elenco_attesa=mysql_real_escape_string($_REQUEST["elenco_attesa"]);
$elenco_classe=mysql_real_escape_string($_REQUEST["elenco_classe"]);
$aggiungi=mysql_real_escape_string($_REQUEST["aggiungi"]);
$rimuovi=mysql_real_escape_string($_REQUEST["rimuovi"]);	
if ($aggiungi) {
	$n = count($elenco_attesa);

	for ($i=0;$i<$n;$i++) {
		$id_utente=$elenco_attesa[$i];
		$query="UPDATE iscrizioni_corso SET id_gruppo='$id_gruppo' WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_utente='$id_utente'";
        $result = $mysqli->query($query);
		
		$query="UPDATE lab_materiali SET id_gruppo='$id_gruppo' WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_autore='$id_utente'";
        $result = $mysqli->query($query);
		
	};
	
} else {

	$n = count($elenco_classe);

	for ($i=0;$i<$n;$i++) {
		$id_utente=$elenco_classe[$i];
		$query="UPDATE iscrizioni_corso SET id_gruppo='' WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_utente='$id_utente'";
        $result = $mysqli->query($query);
		
		$query="UPDATE lab_materiali SET id_gruppo='' WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_autore='$id_utente'";
        $result = $mysqli->query($query);
	};
};		

header("Location:index.php?risorsa=corsi_iscrizioni_gruppo&id_corso=$id_corso&id_edizione=$id_edizione&id_gruppo=$id_gruppo");
?>

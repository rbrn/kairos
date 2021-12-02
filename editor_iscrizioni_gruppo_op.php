<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);			

$id_editor_gruppo=$_REQUEST["id_editor_gruppo"];

$elenco_attesa=$_REQUEST["elenco_attesa"];
$elenco_classe=$_REQUEST["elenco_classe"];
$aggiungi=$_REQUEST["aggiungi"];
$rimuovi=$_REQUEST["rimuovi"];	
if ($aggiungi) {
	$n = count($elenco_attesa);

	for ($i=0;$i<$n;$i++) {
		$id_utente=$elenco_attesa[$i];
		$query="SELECT * FROM editor_gruppo_utenti WHERE id_utente='$id_utente' AND id_editor_gruppo='$id_editor_gruppo'";
        $result = $mysqli->query($query);

		if (!$result->num_rows) {
			$query="INSERT INTO editor_gruppo_utenti SET id_editor_gruppo='$id_editor_gruppo', id_utente='$id_utente'";
            $result = $mysqli->query($query);
		};
	};
	
} else {

	$n = count($elenco_classe);

	for ($i=0;$i<$n;$i++) {
		$id_utente=$elenco_classe[$i];
		$query="DELETE FROM editor_gruppo_utenti WHERE id_utente='$id_utente' AND id_editor_gruppo='$id_editor_gruppo'";
        $result = $mysqli->query($query);
	};
};		

header("Location:index.php?risorsa=editor_iscrizioni_gruppo&id_editor_gruppo=$id_editor_gruppo");
?>

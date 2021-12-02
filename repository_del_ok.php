<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
require "./include/funzioni_repository.inc";
$id_risorsa=$_REQUEST["id_risorsa"];
$tipo=$_REQUEST["tipo"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);		

$id_utente=$kairos_cookie[0];

$ruolo=ruolo_utente($id_utente);

$query="SELECT * FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$risorsa_padre=$riga["risorsa_padre"];

$editabile=true;
if ($ruolo<>"admin") {
	if ($id_utente <> $riga[id_autore] and $id_utente <> $riga[id_editor]) {
		$id_editor_gruppo=$riga[id_editor_gruppo];
		if ($id_editor_gruppo) {
			$query="SELECT * FROM editor_gruppo_utenti WHERE id_utente='$id_utente' AND id_editor_gruppo='$id_editor_gruppo'";
			$result=$mysqli->query($query);
			if (!$result->num_rows) $editabile=false;
		} else {
			$editabile=false;
		};
	}; 	
};

if (!$editabile) {
	$msg="Non puoi cancellare questo oggetto.";
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

if ($tipo==200 or $tipo==202) {
	$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/$id_risorsa.inc";
	if (file_exists($file_codice)) {
		unlink($file_codice);	
	};
};
		
if ($tipo==20) {
	cancella_contenuto($id_risorsa);
	if ($risorsa_padre=="root") {
		$query = "DELETE FROM lo WHERE id_lo='$id_risorsa'";
		$mysqli->query($query);
		
		$query = "DELETE FROM lo_metadata WHERE id_lo='$id_risorsa'";
		$mysqli->query($query);
	};
};

if ($tipo==201) {
	$id_item=$riga["id_gruppo"];
	
	$query = "DELETE FROM lo_test_item WHERE id_item='$id_item'";
	$result=$mysqli->query($query);

	$query = "DELETE FROM lo_test_item_opzioni WHERE id_item='$id_item'";
	$result=$mysqli->query($query);

	$query = "DELETE FROM lo_test_item_dragdrop WHERE id_item='$id_item'";
	$result=$mysqli->query($query);

	$query = "DELETE FROM lo_test_commento WHERE id_item='$id_item'";
	$result=$mysqli->query($query);
};

$query = "DELETE FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);

$query = "DELETE FROM materiali_storia WHERE id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);

$query = "UPDATE lo_pagina SET alternativo_di='' WHERE alternativo_di='$id_risorsa'";
$result=$mysqli->query($query);

$query = "UPDATE lo_pagina SET id_alternativo='' WHERE id_alternativo='$id_risorsa'";
$result=$mysqli->query($query);

Header("Location:index.php?risorsa=repository_index&id_cartella=$risorsa_padre");		
?>

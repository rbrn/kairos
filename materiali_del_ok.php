<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
require "./include/funzioni_materiali.inc";
$id_risorsa=$_REQUEST["id_risorsa"];
$tipo=$_REQUEST["tipo"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);		

$id_utente=$kairos_cookie[0];

$ruolo=ruolo_utente($id_utente);

$editabile=true;
if ($ruolo<>"admin") {
	$query="SELECT id_risorsa,id_autore,id_editor,id_editor_gruppo FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();	
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

if ($tipo==0 or $tipo==3) {
	$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/$id_risorsa.inc";
	if (file_exists($file_codice)) {
		unlink($file_codice);	
	};
	$query = "DELETE FROM risorse_materiali WHERE id_gruppo='$id_risorsa'";
	$mysqli->query($query);
};
		
if ($tipo==1) {
	$query = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$titolo=$riga["titolo"];
	$fullpath=$PATH_ARCHIVI_ADMIN."materiali/$cod_area/".$titolo;
	
	if (file_exists($fullpath) and !is_dir($fullpath)) {
		unlink($fullpath);	
	};
};

if ($tipo==2) {
	cancella_contenuto($id_risorsa);
};
			
$query = "DELETE FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);

$query = "DELETE FROM materiali_storia WHERE id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);

$query = "DELETE FROM materiali_sequenza WHERE id_risorsa='$id_risorsa'";
$mysqli->query($query);
	
Header("Location:index.php?risorsa=materiali_index&id_cartella=$risorsa_padre");		
?>

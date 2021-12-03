<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
require "./include/function_admin.inc";

$id_risorsa=$_REQUEST["id_risorsa"];
$tipo=$_REQUEST["tipo"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);		


if ($tipo==0) {
	if (risorsa_admin($id_risorsa)) {
		$file_codice=$PATH_ROOT_FILE."pagine/$id_risorsa.inc";
	} else {
		$file_codice=$PATH_ROOT_FILE."pagine/$cod_area/$id_risorsa.inc";
	};
	if (file_exists($file_codice)) {
		unlink($file_codice);	
	};
};

if ($tipo==1) {
	$query = "SELECT titolo FROM risorse WHERE id_risorsa='$id_risorsa'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$titolo=$riga["titolo"];

	if (risorsa_admin($id_risorsa)) {
		$file_download=$PATH_ARCHIVI_ADMIN.$titolo;
	} else {
		$file_download=$PATH_ARCHIVI.$titolo;
	};
	$fullpath = $file_download;


	if (file_exists($fullpath) and !is_dir($fullpath)) {
		unlink($fullpath);	
	};
};


if ($tipo==2) {
	cancella_contenuto($id_risorsa);
};
		

$query = "DELETE FROM risorse WHERE id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);

Header("Location:index.php?risorsa=admin_index&id_cartella=$risorsa_padre");		
?>

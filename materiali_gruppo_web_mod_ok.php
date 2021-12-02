<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$cod_area=$kairos_cookie["4"];

$id_risorsa=$_REQUEST["id_risorsa"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$titolo=$_REQUEST["titolo"];
$livello="2";
$testo=$_REQUEST["testo"];
$tipo=$_REQUEST["tipo"];
$id_autore=$_REQUEST["id_autore"];
$url=$_REQUEST["url"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$dir_gruppo=$PATH_ROOT_FILE."materiali/$cod_area/gruppo";
if (!is_dir($dir_gruppo)) {
	mkdir($dir_gruppo,0755);
};

if ($testo) {
	$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/gruppo/$id_risorsa.inc";
	if (file_exists($file_codice)) {
		unlink($file_codice);
	};
};

$id_utente = $kairos_cookie["0"];
if ($id_risorsa) {
$query = "UPDATE materiali_gruppo 		
			SET 
				tipo='$tipo',
				titolo='$titolo',
				id_autore='$id_autore',
				url='$url'
			WHERE id_risorsa='$id_risorsa'";

$result=$mysqli->query($query);
};

if ($testo) {
$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/gruppo/$id_risorsa.inc";
$fp = fopen($file_codice,"w");
fwrite($fp,stripslashes($testo));
fclose($fp);
};

$query="INSERT INTO materiale_gruppo_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='modificato',"
." data_evento=NOW()";
$mysqli->query($query);

Header("Location:index.php?risorsa=materiali_gruppo_index&id_cartella=$risorsa_padre");			
?>

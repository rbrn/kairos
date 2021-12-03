<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_risorsa=$_REQUEST["id_risorsa"];
$ex_titolo=$_REQUEST["ex_titolo"];
$ex_file_size=$_REQUEST["ex_file_size"];

$risorsa_padre=$_REQUEST["risorsa_padre"];
$descrizione=$_REQUEST["descrizione"];
$livello="2";
$id_autore=$_REQUEST["id_autore"];

$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];

$titolo=$_FILES["titolo"]["tmp_name"];
$titolo_size=$_FILES["titolo"]["size"];
$titolo_name=$_FILES["titolo"]["name"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

if ($titolo_size > $MAX_FILE_SIZE) {
	$errore .= "<br>$stringa[errore_max_file]";
};
									
if ($errore) {
	$msg=ereg_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};


$id_utente = $kairos_cookie["0"];

$dir_gruppo=$PATH_ARCHIVI_ADMIN."materiali/$cod_area/gruppo";
if (!is_dir($dir_gruppo)) {
	mkdir($dir_gruppo,0755);
};

if ($titolo_name) {
	$titolo_name = trim($titolo_name);
	$titolo_name = str_replace(" ","",$titolo_name);
	$titolo_name = str_replace("'","",$titolo_name);
	$titolo_name = str_replace("(","",$titolo_name);
	$titolo_name = str_replace(")","",$titolo_name);
	$titolo_name = stripslashes($titolo_name);
	$titolo_name = strtolower($titolo_name);
	if (file_exists($titolo)) {
		$fullpath = $PATH_ARCHIVI_ADMIN."materiali/$cod_area/gruppo/".$ex_titolo;
		if (file_exists($fullpath)) {
			unlink($fullpath);
		};
		$fullpath = $PATH_ARCHIVI_ADMIN."materiali/$cod_area/gruppo/".$titolo_name;
		copy($titolo,$fullpath);	
		$est = substr($fullpath,-3);
		if ($est<>"zip") {
		
			$cur_dir=getcwd();
			chdir($PATH_ARCHIVI_ADMIN."materiali/$cod_area/gruppo");
					
			$fullpath_zip=substr($fullpath,0,strlen($fullpath)-3)."zip";
			$nome_file_zip=substr($titolo_name,0,strlen($titolo_name)-3)."zip";
			if (file_exists($fullpath_zip)) {
				unlink($fullpath_zip);
			};
			$comando="/usr/bin/zip -D -q $nome_file_zip $titolo_name";
			exec($comando);
			chdir($cur_dir);
			
			unlink($fullpath);
			$titolo_name=$nome_file_zip;
			$titolo_size=filesize($fullpath_zip);
			$titolo_type="application/x-zip-compressed";
		};	
	} else {
		$titolo_name=$ex_titolo;
		$titolo_size=$ex_file_size;
		$titolo_type="";		
	};
} else {
	$titolo_name=$ex_titolo;
	$titolo_size=$ex_file_size;
	$titolo_type="";	
};


$query = "UPDATE materiali_gruppo 		
			SET 
				titolo='$titolo_name',
				descrizione='$descrizione',
				file_size='$titolo_size',
				id_autore='$id_autore'
			WHERE id_risorsa='$id_risorsa'";

$result=$mysqli->query($query);

$query="INSERT INTO materiale_gruppo_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='modificato',"
." data_evento=NOW()";
$mysqli->query($query);

Header("Location:index.php?risorsa=materiali_gruppo_index&id_cartella=$risorsa_padre");			
?>

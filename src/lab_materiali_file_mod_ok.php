<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_risorsa=$_REQUEST["id_risorsa"];
$ex_titolo=$_REQUEST["ex_titolo"];
$ex_file_size=$_REQUEST["ex_file_size"];

$risorsa_padre=$_REQUEST["risorsa_padre"];
$descrizione=$_REQUEST["descrizione"];
$parole_chiave=$_REQUEST["parole_chiave"];

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

if ($titolo_name) {
	$titolo_name = trim($titolo_name);
	$titolo_name = str_replace("'","",$titolo_name);
	$titolo_name = str_replace("(","",$titolo_name);
	$titolo_name = str_replace(")","",$titolo_name);
	$titolo_name = stripslashes($titolo_name);
	$titolo_name = $id_utente."_".str_replace(" ","",$titolo_name);
	$titolo_name = strtolower($titolo_name);
	$fullpath = $PATH_ARCHIVI_ADMIN."materiali/$cod_area/".$titolo_name;
	if (file_exists($titolo)) {
		copy($titolo,$fullpath);	
		$est = substr($fullpath,-3);
		if ($est<>"zip") {
		
			$cur_dir=getcwd();
			chdir($PATH_ARCHIVI_ADMIN."materiali/$cod_area");
					
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


$id_utente = $kairos_cookie["0"];

$query = "UPDATE lab_materiali 		
			SET 
				risorsa_padre='$risorsa_padre',
				titolo='$titolo_name',
				descrizione='$descrizione',
				parole_chiave='$parole_chiave',
				file_size='$titolo_size'
			WHERE id_risorsa=$id_risorsa";

$result=$mysqli->query($query);



Header("Location:index.php?risorsa=lab_materiali_index&id_cartella=$risorsa_padre");			
?>

<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$tipo=$_REQUEST["tipo"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$descrizione=$_REQUEST["descrizione"];
$livello="2";
$id_autore=$_REQUEST["id_autore"];

$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];

$titolo=$_FILES["titolo"]["tmp_name"];
$titolo_size=$_FILES["titolo"]["size"];
$titolo_name=$_FILES["titolo"]["name"];

// controllo se tutti i campi obbligatori sono stati compilati

$errore = ""; 
if (!$titolo) {
	$errore .= "<br>$stringa[errore_manca_file]";
};	

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
	$fullpath = $PATH_ARCHIVI_ADMIN."materiali/$cod_area/gruppo/".$titolo_name;
	if (file_exists($titolo)) {
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
		}	
	} else {
		$titolo_name="";	
		$titolo_size=0;
		$titolo_type="";		
	};	
};

$query="SELECT max(posizione) AS num_pag FROM materiali_gruppo WHERE risorsa_padre='$risorsa_padre' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$posizione=$riga[num_pag]+1;

$query = "INSERT INTO materiali_gruppo (tipo,id_corso,id_edizione,id_gruppo,risorsa_padre,titolo,descrizione,id_autore,data_crea,livello,file_size,posizione,id_editor) VALUES ('$tipo','$id_corso_s','$id_edizione_s','$id_gruppo','$risorsa_padre','$titolo_name','$descrizione','$id_autore',NOW(),'$livello','$titolo_size','$posizione','$id_utente')";
$result=$mysqli->query($query);

$id_risorsa=$mysqli->insert_id;

$query = "SELECT id_risorsa FROM materiali_gruppo WHERE risorsa_padre='$risorsa_padre' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";

$result=$mysqli->query($query);
$tot_righe=$result->num_rows;
$pag_size=20;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$query="INSERT INTO materiale_gruppo_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='creato',"
." data_evento=NOW()";
$mysqli->query($query);

Header("Location:index.php?risorsa=materiali_gruppo_index&pagina=$tot_pag&id_cartella=$risorsa_padre");		
?>

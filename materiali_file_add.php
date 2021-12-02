<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$tipo=$_REQUEST["tipo"];
$id_risorsa=mysql_real_escape_string($_REQUEST["id_risorsa"]);
$risorsa_padre=mysql_real_escape_string($_REQUEST["risorsa_padre"]);
$descrizione=mysql_real_escape_string($_REQUEST["descrizione"]);
$parole_chiave=mysql_real_escape_string($_REQUEST["parole_chiave"]);
$livello="2";
$id_gruppo=$_REQUEST["id_gruppo"];
$id_autore=$_REQUEST["id_autore"];

$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];

$titolo=$_FILES["titolo"]["tmp_name"];
$titolo_size=$_FILES["titolo"]["size"];
$titolo_name=$_FILES["titolo"]["name"];

// controllo se tutti i campi obbligatori sono stati compilati

$id_risorsa=uniqid("file_");

$errore = ""; 
if (!$id_risorsa) {
	$errore .= "<br>$stringa[errore_manca_id]";
};		

if (!ereg("^[a-zA-Z0-9_]+$",$id_risorsa)) {
	$errore .= "<br>$stringa[errore_solo_lettere]";
};

$query="SELECT id_risorsa FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";		
$result=$mysqli->query($query);
$riga=$result->fetch_array();

if ($riga) {
$errore .= "<br>$stringa[errore_id_esiste]";
};		
	
if (!$titolo and $tipo<>'2') {
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

if ($titolo_name) {
	$titolo_name = trim($titolo_name);
	$titolo_name = str_replace(" ","",$titolo_name);
	$titolo_name = str_replace("'","",$titolo_name);
	$titolo_name = str_replace("(","",$titolo_name);
	$titolo_name = str_replace(")","",$titolo_name);
	$titolo_name = stripslashes($titolo_name);
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
			//$comando="/usr/bin/zip -D -q $nome_file_zip $titolo_name";
			
			$zip = new ZipArchive();
			if($zip->open($fullpath_zip, ZIPARCHIVE::CREATE)){
				$zip->addFile($titolo_name, $titolo_name);
				$zip->close();	
			}
		
			//$comando="/usr/bin/zip -D -q $nome_file_zip $titolo_name";
			//exec($comando);
			$titolo_size=filesize($fullpath_zip);
			
			//exec($comando);
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

$query="SELECT max(posizione) AS num_pag FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' and (tipo='0' or tipo='1' or tipo='2' or tipo='3')";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$posizione=$riga[num_pag]+1;

$query = "INSERT INTO risorse_materiali (id_risorsa,tipo,risorsa_padre,titolo,descrizione,parole_chiave,id_autore,data_crea,livello,id_gruppo,file_size,posizione,id_editor) VALUES ('$id_risorsa','$tipo','$risorsa_padre','$titolo_name','$descrizione','$parole_chiave','$id_autore',NOW(),'$livello','$id_gruppo','$titolo_size','$posizione','$id_utente')";
$result=$mysqli->query($query);
	
$ruolo=ruolo_utente($id_utente);
if ($ruolo=='admin') {
	$query = "SELECT id_risorsa FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' and (tipo='0' or tipo='1' or tipo='2' or tipo='3')";
} else {
	$query = "SELECT id_risorsa FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' AND id_editor='$id_utente' and (tipo='0' or tipo='1' or tipo='2' or tipo='3')";
};
$result=$mysqli->query($query);
$tot_righe=$result->num_rows;
$pag_size=20;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$query="INSERT INTO materiale_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='creato',"
." data_evento=NOW()";
$mysqli->query($query);

Header("Location:index.php?risorsa=materiali_index&pagina=$tot_pag&id_cartella=$risorsa_padre");		
?>

<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$titolo=trim($_REQUEST["titolo"]);
$autori=$_REQUEST["autori"];
$nome_scuola=$_REQUEST["nome_scuola"];
$citta_scuola=$_REQUEST["citta_scuola"];
$prov_scuola=$_REQUEST["prov_scuola"];
$regione_scuola=$_REQUEST["regione_scuola"];
$classe=$_REQUEST["classe"];
$unita=$_REQUEST["unita"];
$tipo=$_REQUEST["tipo"];

$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];

$allegato=$_FILES["allegato"]["tmp_name"];
$allegato_size=$_FILES["allegato"]["size"];
$allegato_name=$_FILES["allegato"]["name"];

// controllo se tutti i campi obbligatori sono stati compilati

$errore = ""; 

if (!$titolo) {
	$errore .="<br>Manca il titolo del contributo";
};

if (!$autori) {
	$errore .="<br>Mancano gli autori del contributo";
};

if (!$nome_scuola) {
	$errore .="<br>Manca il nome della scuola";
};

if (!$citta_scuola) {
	$errore .="<br>Manca la cittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ della scuola";
};

if ($prov_scuola=="XX") {
	$errore .="<br>Manca la provincia della scuola";
};

if ($regione_scuola=="XX") {
	$errore .="<br>Manca la regione della scuola";
};

if (!$classe) {
	$errore .="<br>Manca la classe";
};

if (!$unita) {
	$errore .="<br>Manca l'indicazione dell'argomento";
};

if (!$tipo) {
	$errore .="<br>Manca l'indicazione del tipo di contributo";
};

if (!$allegato) {
	$errore .= "<br>$stringa[errore_manca_file]";
};	

if ($allegato_size > $MAX_FILE_SIZE) {
	$errore .= "<br>$stringa[errore_max_file]";
};
									
if ($errore) {
	$msg=str_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

$id_utente = $kairos_cookie["0"];

if ($allegato_name) {
	$allegato_name = trim($allegato_name);
	$allegato_name = str_replace("'","",$allegato_name);
	$allegato_name = str_replace("(","",$allegato_name);
	$allegato_name = str_replace(")","",$allegato_name);
	$allegato_name = stripslashes($allegato_name);
	$allegato_name = $id_utente."_".str_replace(" ","",$allegato_name);
	$allegato_name = strtolower($allegato_name);
	$fullpath = $PATH_ARCHIVI_ADMIN."materiali/$cod_area/".$allegato_name;
	if (file_exists($allegato)) {
		copy($allegato,$fullpath);	
		/*
		$est = substr($fullpath,-3);
		if ($est<>"zip") {
		
			$cur_dir=getcwd();
			chdir($PATH_ARCHIVI_ADMIN."materiali/$cod_area");
					
			$fullpath_zip=substr($fullpath,0,strlen($fullpath)-3)."zip";
			$nome_file_zip=substr($allegato_name,0,strlen($allegato_name)-3)."zip";
			if (file_exists($fullpath_zip)) {
				unlink($fullpath_zip);
			};
			$comando="/usr/bin/zip -D -q $nome_file_zip $allegato_name";
			exec($comando);
			chdir($cur_dir);
			
			unlink($fullpath);
			$allegato_name=$nome_file_zip;
			$allegato_size=filesize($fullpath_zip);
			$allegato_type="application/x-zip-compressed";
		}	
		*/
	} else {
		$allegato_name="";	
		$allegato_size=0;
		$allegato_type="";		
	};	
};

$query = "INSERT INTO progetti SET 
id_utente='$kairos_cookie[0]',
titolo='$titolo',
data_upload=NOW(),
autori='$autori',
nome_scuola='$nome_scuola',
citta_scuola='$citta_scuola',
prov_scuola='$prov_scuola',
regione_scuola='$regione_scuola',
classe='$classe',
unita='$unita',
allegato='$allegato_name',
allegato_size='$allegato_size',
stato='1',
tipo='$tipo'";

$result=$mysqli->query($query);
	
$msg="<b>Grazie!</b> il tuo file ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ stato caricato. Prima che gli altri utenti iscritti alla community possano vederlo dovrai attenderne la pubblicazione da parte della redazione. A presto!";
$risorsa="progetti_file_form_add";
$arg=$unita;

Header("Location:index.php?risorsa=msg&msg=$msg&risorsa_back=$risorsa&arg=$arg");		
?>

<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$cod_area=$kairos_cookie["4"];

$id_risorsa=mysql_real_escape_string($_REQUEST["id_risorsa"]);
$titolo=mysql_real_escape_string($_REQUEST["titolo"]);
$risorsa_padre=mysql_real_escape_string($_REQUEST["risorsa_padre"]);
$descrizione=mysql_real_escape_string($_REQUEST["descrizione"]);
$parole_chiave=mysql_real_escape_string($_REQUEST["parole_chiave"]);
$livello="2";
$id_gruppo=mysql_real_escape_string($_REQUEST["id_gruppo"]);
$testo=mysql_real_escape_string($_REQUEST["testo"]);
$tipo=mysql_real_escape_string($_REQUEST["tipo"]);
$id_autore=mysql_real_escape_string($_REQUEST["id_autore"]);
$url=mysql_real_escape_string($_REQUEST["url"]);

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$errore="";

if (!$id_risorsa) {
	$errore .= "<br>$stringa[manca_id]";
};	

if (!$titolo and $tipo<>'2') {
	$titolo = "$stringa[senza_titolo]";
};	
	
							
if ($errore) {
	$msg=ereg_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

if ($testo) {
	$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/$id_risorsa.inc";
	if (file_exists($file_codice)) {
		unlink($file_codice);
	};
};

$id_utente = $kairos_cookie["0"];
if ($id_risorsa) {
$query = "UPDATE risorse_materiali 		
			SET 
				risorsa_padre='$risorsa_padre',
				tipo='$tipo',
				titolo='$titolo',
				descrizione='$descrizione',
				parole_chiave='$parole_chiave',
				id_gruppo='$id_gruppo',
				livello='$livello',
				id_autore='$id_autore',
				url='$url'
			WHERE id_risorsa='$id_risorsa'";

$result=$mysqli->query($query);
};

if ($titolo and $id_risorsa) {
$query = "UPDATE risorse_materiali 		
			SET 
				titolo='$titolo',
				descrizione='$descrizione',
				parole_chiave='$parole_chiave'
			WHERE id_gruppo='$id_risorsa'";

$result=$mysqli->query($query);
};


if ($testo) {
$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/$id_risorsa.inc";
$fp = fopen($file_codice,"w");
fwrite($fp,stripslashes($testo));
fclose($fp);
};

$query="INSERT INTO materiale_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='modificato',"
." data_evento=NOW()";
$mysqli->query($query);

Header("Location:index.php?risorsa=materiali_index&id_cartella=$risorsa_padre");			
?>

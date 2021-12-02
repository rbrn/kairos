<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$cod_area=$kairos_cookie["4"];
$tipo=mysql_real_escape_string($_REQUEST["tipo"]);
$id_risorsa=trim($_REQUEST["id_risorsa"]);
$titolo=mysql_real_escape_string($_REQUEST["titolo"]);
$risorsa_padre=mysql_real_escape_string($_REQUEST["risorsa_padre"]);
$descrizione=mysql_real_escape_string($_REQUEST["descrizione"]);
$parole_chiave=mysql_real_escape_string($_REQUEST["parole_chiave"]);
$livello="2";
$id_gruppo=mysql_real_escape_string($_REQUEST["id_gruppo"]);
$testo=mysql_real_escape_string($_REQUEST["testo"]);
$id_autore=mysql_real_escape_string($_REQUEST["id_autore"]);
$url=mysql_real_escape_string($_REQUEST["url"]);

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

// controllo se tutti i campi obbligatori sono stati compilati


$errore = ""; 
if (!$id_risorsa) {
	$id_risorsa=uniqid("web_");
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
	$titolo = "$stringa[senza_titolo]";
};	
	
							
if ($errore) {
	$msg=ereg_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};


$id_utente = $kairos_cookie["0"];

$query="SELECT max(posizione) AS num_pag FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' and (tipo='0' or tipo='1' or tipo='2' or tipo='3')";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$posizione=$riga[num_pag]+1;

$query = "INSERT INTO risorse_materiali (id_risorsa,tipo,risorsa_padre,titolo,descrizione,parole_chiave,id_autore,data_crea,livello,id_gruppo,posizione,id_editor,url) VALUES ('$id_risorsa','$tipo','$risorsa_padre','$titolo','$descrizione','$parole_chiave','$id_autore',NOW(),'$livello','$id_gruppo','$posizione','$id_utente','$url')";

$result=$mysqli->query($query);

if ($testo) {
$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/$id_risorsa.inc";
$fp = fopen($file_codice,"w");
fwrite($fp,stripslashes($testo));
fclose($fp);
};

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

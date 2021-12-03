<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$cod_area=$kairos_cookie["4"];
$tipo=$_REQUEST["tipo"];
$titolo=$_REQUEST["titolo"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$livello="2";
$testo=$_REQUEST["testo"];
$id_autore=$_REQUEST["id_autore"];
$url=$_REQUEST["url"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

if (!$titolo) $titolo="senza titolo";
	
							
$id_utente = $kairos_cookie["0"];

$dir_gruppo=$PATH_ROOT_FILE."materiali/$cod_area/gruppo";
if (!is_dir($dir_gruppo)) {
	mkdir($dir_gruppo,0755);
};

$query="SELECT max(posizione) AS num_pag FROM materiali_gruppo WHERE risorsa_padre='$risorsa_padre' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$posizione=$riga[num_pag]+1;

$query = "INSERT INTO materiali_gruppo (tipo,id_corso,id_edizione,id_gruppo,risorsa_padre,titolo,id_autore,data_crea,livello,posizione,id_editor,url) VALUES ('$tipo','$id_corso_s','$id_edizione_s','$id_gruppo','$risorsa_padre','$titolo','$id_autore',NOW(),'$livello','$posizione','$id_utente','$url')";
$result=$mysqli->query($query);

$id_risorsa=$mysqli->insert_id;

if ($testo) {
$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/gruppo/$id_risorsa.inc";
$fp = fopen($file_codice,"w");
fwrite($fp,stripslashes($testo));
fclose($fp);
};

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

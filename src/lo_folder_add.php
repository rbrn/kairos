<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_risorsa=$_REQUEST["id_risorsa"];

$risorsa_padre=$_REQUEST["risorsa_padre"];
$titolo=mysql_real_escape_string($_REQUEST["titolo"]);
$id_autore=mysql_real_escape_string($_REQUEST["id_autore"]);
$id_editor_gruppo=mysql_real_escape_string($_REQUEST["id_editor_gruppo"]);

$materia=mysql_real_escape_string($_REQUEST["materia"]);
$fruitore=mysql_real_escape_string($_REQUEST["fruitore"]);
$obiettivi=mysql_real_escape_string($_REQUEST["obiettivi"]);
$argomenti=mysql_real_escape_string($_REQUEST["argomenti"]);
$profilo_ingresso=mysql_real_escape_string($_REQUEST["profilo_ingresso"]);
$lo_licenza=mysql_real_escape_string($_REQUEST["lo_licenza"]);
$lo_skin=mysql_real_escape_string($_REQUEST["lo_skin"]);
$lo_tipo_lom=mysql_real_escape_string($_REQUEST["lo_tipo_lom"]);
$file_audio=$_REQUEST["file_audio"];
$lo_modocontinua_str=$_REQUEST["lo_modocontinua"];
$lo_bloccoavanzamento_str=$_REQUEST["lo_bloccoavanzamento"];

$nome_autore_credits=trim($_REQUEST["nome_autore_credits"]);
$nome_coordinatore_credits=trim($_REQUEST["nome_coordinatore_credits"]);

$lo_modocontinua=0;
$lo_bloccoavanzamento=0;

if ($lo_modocontinua_str=="on") $lo_modocontinua=1;
if ($lo_bloccoavanzamento_str=="on") $lo_bloccoavanzamento=1;

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

// controllo se tutti i campi obbligatori sono stati compilati

if ($risorsa_padre<>"root") {
$id_risorsa=uniqid("folder_");
} else {
$id_risorsa=uniqid("lo_");
};
$errore = ""; 
if (!$id_risorsa) {
	$errore .= "<br>Manca ID Cartella";
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
							
if ($errore) {
	$msg=ereg_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};


$id_utente = $kairos_cookie["0"];

$query="SELECT max(posizione) AS num_pag FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' AND (tipo='20' or tipo='200' or tipo='201' or tipo='202')";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$posizione=$riga[num_pag]+1;

$query = "INSERT INTO risorse_materiali SET".
" id_risorsa='$id_risorsa',".
" tipo='20',".
" risorsa_padre='$risorsa_padre',".
" id_autore='$id_autore',".
" data_crea=NOW(),".
" titolo='$titolo',".
" posizione='$posizione',".
" id_editor='$id_utente',".
" id_editor_gruppo='$id_editor_gruppo'";

$result=$mysqli->query($query);

$ruolo=ruolo_utente($id_utente);
if ($ruolo=='admin') {
	$query = "SELECT id_risorsa FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' AND (tipo='20' or tipo='200' or tipo='201' or tipo='202')";
} else {
	$query = "SELECT id_risorsa FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' AND  id_editor='$id_utente' AND (tipo='20' or tipo='200' or tipo='201' or tipo='202')";
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

if ($risorsa_padre=="root") {
$query="INSERT INTO lo SET"
." id_lo='$id_risorsa',"
." id_profile='lom_garamond',"
." stato='0',"
." lo_tipo='1',"
." lo_tipo_lom='$lo_tipo_lom',"
." lo_skin='$lo_skin',"
." materia='$materia',"
." fruitore='$fruitore',"
." obiettivi='$obiettivi',"
." argomenti='$argomenti',"
." file_audio='$file_audio',"
." lo_modocontinua='$lo_modocontinua',"
." lo_bloccoavanzamento='$lo_bloccoavanzamento',"
." lo_licenza='$lo_licenza',"
." profilo_ingresso='$profilo_ingresso'";
$mysqli->query($query);

$path_file=$PATH_ROOT_FILE."materiali/$cod_area/".$id_risorsa."_credits.txt";
$fp=fopen($path_file,"w");
fwrite($fp,"$nome_autore_credits\t$nome_coordinatore_credits");
fclose($fp);
};

Header("Location:index.php?risorsa=repository_index&pagina=$tot_pag&id_cartella=$risorsa_padre");		
?>

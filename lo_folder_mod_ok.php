<?php
require "./include/init_sito.inc";
$id_risorsa=$_REQUEST["id_risorsa"];

$risorsa_padre=$_REQUEST["risorsa_padre"];
$ex_risorsa_padre=$_REQUEST["ex_risorsa_padre"];

$titolo=mysql_real_escape_string($_REQUEST["titolo"]);
$materia=mysql_real_escape_string($_REQUEST["materia"]);
$fruitore=mysql_real_escape_string($_REQUEST["fruitore"]);
$obiettivi=mysql_real_escape_string($_REQUEST["obiettivi"]);
$argomenti=mysql_real_escape_string($_REQUEST["argomenti"]);
$profilo_ingresso=mysql_real_escape_string($_REQUEST["profilo_ingresso"]);
$lo_licenza=mysql_real_escape_string($_REQUEST["lo_licenza"]);
$file_audio=$_REQUEST["file_audio"];
$elimina_audio=$_REQUEST["file_audio"];
$lo_modocontinua_str=$_REQUEST["lo_modocontinua"];
$lo_bloccoavanzamento_str=$_REQUEST["lo_bloccoavanzamento"];

$nome_autore_credits=trim($_REQUEST["nome_autore_credits"]);
$nome_coordinatore_credits=trim($_REQUEST["nome_coordinatore_credits"]);

$lo_modocontinua=0;
$lo_bloccoavanzamento=0;

if ($lo_modocontinua_str=="on") $lo_modocontinua=1;
if ($lo_bloccoavanzamento_str=="on") $lo_bloccoavanzamento=1;
if ($elimina_audio=="on") $file_audio="";

$lo_skin=$_REQUEST["lo_skin"];
$lo_tipo_lom=$_REQUEST["lo_tipo_lom"];

$id_autore=$_REQUEST["id_autore"];
$id_editor_gruppo=$_REQUEST["id_editor_gruppo"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_utente = $kairos_cookie["0"];
$query = "UPDATE risorse_materiali 		
			SET 
				risorsa_padre='$risorsa_padre',
				titolo='$titolo',
				id_autore='$id_autore',
				id_editor_gruppo='$id_editor_gruppo'
			WHERE id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);

$query="INSERT INTO materiale_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='modificato',"
." data_evento=NOW()";
$mysqli->query($query);

if ($risorsa_padre=="root") {
$query="UPDATE lo SET"
." lo_skin='$lo_skin',"
." lo_tipo_lom='$lo_tipo_lom',"
." materia='$materia',"
." fruitore='$fruitore',"
." obiettivi='$obiettivi',"
." argomenti='$argomenti',"
." file_audio='$file_audio',"
." lo_modocontinua='$lo_modocontinua',"
." lo_bloccoavanzamento='$lo_bloccoavanzamento',"
." lo_licenza='$lo_licenza',"
." profilo_ingresso='$profilo_ingresso'"
." WHERE id_lo='$id_risorsa'";

$mysqli->query($query);

$path_file=$PATH_ROOT_FILE."materiali/$cod_area/".$id_risorsa."_credits.txt";
$fp=fopen($path_file,"w");
fwrite($fp,"$nome_autore_credits\t$nome_coordinatore_credits");
fclose($fp);
};

Header("Location:index.php?risorsa=repository_index&id_cartella=$risorsa_padre");			
?>

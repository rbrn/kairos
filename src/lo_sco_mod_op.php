<?php
require "./include/init_sito.inc";
$id_risorsa=mysql_real_escape_string($_REQUEST["id_risorsa"]);
$titolo=mysql_real_escape_string($_REQUEST["titolo"]);
$width=$_REQUEST["width"];
$height=$_REQUEST["height"];
$id_autore=$_REQUEST["id_autore"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	


$id_utente = $kairos_cookie["0"];
$query = "UPDATE risorse_materiali 		
			SET 
				titolo='$titolo',
				id_autore='$id_autore'
			WHERE id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);

$query = "UPDATE lo 		
			SET 
				width='$width',
				height='$height'
			WHERE id_lo='$id_risorsa'";
$result=$mysqli->query($query);

$query="INSERT INTO materiale_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='modificato',"
." data_evento=NOW()";
$mysqli->query($query);


Header("Location:index.php?risorsa=repository_index&id_cartella=root");			
?>

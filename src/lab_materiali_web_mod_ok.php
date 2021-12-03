<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$cod_area=$kairos_cookie["4"];

$id_risorsa=$_REQUEST["id_risorsa"];
$titolo=$_REQUEST["titolo"];
$url=$_REQUEST["url"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$descrizione=$_REQUEST["descrizione"];
$parole_chiave=$_REQUEST["parole_chiave"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query = "UPDATE lab_materiali 		
			SET 
				risorsa_padre='$risorsa_padre',
				titolo='$titolo',
				descrizione='$descrizione',
				parole_chiave='$parole_chiave',
				url='$url'
			WHERE id_risorsa=$id_risorsa";

$result=$mysqli->query($query);

Header("Location:index.php?risorsa=lab_materiali_index&id_cartella=$risorsa_padre");			
?>

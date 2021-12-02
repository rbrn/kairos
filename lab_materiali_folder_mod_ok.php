<?php
require "./include/init_sito.inc";
$id_risorsa=$_REQUEST["id_risorsa"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$ex_risorsa_padre=$_REQUEST["ex_risorsa_padre"];
$titolo=$_REQUEST["titolo"];
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query = "UPDATE lab_materiali 		
			SET 
				risorsa_padre='$risorsa_padre',
				titolo='$titolo'
			WHERE id_risorsa=$id_risorsa";
$result=$mysqli->query($query);


Header("Location:index.php?risorsa=lab_materiali_index&id_cartella=$risorsa_padre");			
?>

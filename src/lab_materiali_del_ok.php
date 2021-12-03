<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
require "./include/funzioni_lab_materiali.inc";
$id_risorsa=$_REQUEST["id_risorsa"];
$tipo=$_REQUEST["tipo"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);		

if ($tipo==1) {
	$query = "SELECT titolo FROM lab_materiali WHERE id_risorsa=$id_risorsa";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$titolo=$riga["titolo"];
	$fullpath=$PATH_ARCHIVI_ADMIN."materiali/$cod_area/".$titolo;
	
	if (file_exists($fullpath) and !is_dir($fullpath)) {
		unlink($fullpath);	
	};
};

if ($tipo==2) {
	cancella_lab_cartella($id_risorsa);
};
			
$query = "DELETE FROM lab_materiali WHERE id_risorsa=$id_risorsa";
$result=$mysqli->query($query);

$query = "DELETE FROM commento_lab_materiali WHERE id_risorsa=$id_risorsa";
$result=$mysqli->query($query);

Header("Location:index.php?risorsa=lab_materiali_index&id_cartella=$risorsa_padre");		
?>

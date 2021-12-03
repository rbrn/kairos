<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_risorsa=$_REQUEST[id_risorsa];
$id_utente=$kairos_cookie[0];
$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query = "SELECT * FROM lab_materiali where id_risorsa=$id_risorsa";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$titolo=$riga["titolo"];

$file_download=$PATH_ARCHIVI_ADMIN."materiali/$cod_area/".$titolo;
if (!file_exists($file_download)) {
		$errore=$stringa[errore_file_rimosso];
		$msg=ereg_replace(" ","%20",$errore);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
};

$query="INSERT INTO log_lab_materiali SET
id_utente='$id_utente',
data_log=now(),
id_risorsa='$id_risorsa',
id_corso='$id_corso_s',
id_edizione='$id_edizione_s',
id_gruppo='$id_gruppo_s'";
$mysqli->query($query);

$doc = fopen($file_download,"rb");
$type= getmimetype($titolo);
header("Content-Type: $type");
header( "Content-Disposition: attachment; filename=$titolo" ); 
fpassthru($doc);
?>

<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_progetto=$_REQUEST[id_progetto];
$id_utente=$kairos_cookie[0];

if (!$id_utente) {
		$errore=$stringa[errore_no_login];
		$msg=ereg_replace(" ","%20",$errore);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
};

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query = "SELECT * FROM progetti where id_progetto=$id_progetto";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$allegato=$riga["allegato"];

$file_download=$PATH_ARCHIVI_ADMIN."materiali/$cod_area/".$allegato;
if (!file_exists($file_download)) {
		$errore=$stringa[errore_file_rimosso];
		$msg=ereg_replace(" ","%20",$errore);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
};

$doc = fopen($file_download,"rb");
$type= getmimetype($titolo);
header("Content-Type: $type");
header( "Content-Disposition: attachment; filename=$allegato" ); 
fpassthru($doc);
?>

<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_utente=$kairos_cookie[0];
$tipo_news=$_REQUEST["tipo_news"];
$id_news=$_REQUEST["id_news"];
$testo=mysql_real_escape_string($_REQUEST["testo"]);
$posizione=$_REQUEST["posizione"];
$ex_posizione=$_REQUEST["ex_posizione"];
$url=mysql_real_escape_string($_REQUEST["url"]);
$url_label=mysql_real_escape_string($_REQUEST["url_label"]);

$errore = ""; 
if (!$testo) {
	$errore .= "<br>$stringa[errore_manca_testo]";
};	

if (!$url_label and $url) {
	$errore .= "<br>$stringa[errore_manca_titolo]";
};	

if ($errore) {
	$errore=str_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$errore");
	exit();	
};

if ($tipo_news==0) {
$query = "DELETE FROM hp_news WHERE posizione='$ex_posizione' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);

if (!$posizione) $posizione=$ex_posizione;

$query = "DELETE FROM hp_news WHERE posizione='$posizione' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);

$query = "INSERT INTO hp_news (tipo,posizione,id_utente,data_news,url,testo,url_label,id_corso,id_edizione) VALUES ('$tipo_news','$posizione','$id_utente',NOW(),'$url','$testo','$url_label','$id_corso_s','$id_edizione_s')";
$result=$mysqli->query($query);
} else {
	$query = 
"UPDATE hp_news SET 
url='$url',
testo='$testo',
url_label='$url_label'
WHERE id_news='$id_news'";
$result=mysql_query($query,$db);

};


$url="index.php?risorsa=index";
Header("Location: $url");
?>

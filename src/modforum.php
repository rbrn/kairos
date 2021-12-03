<?php
require "./include/init_sito.inc";
$id_forum=$_REQUEST["id_forum"];
$ordine=$_REQUEST["ordine"];
$descrizione=$_REQUEST["descrizione"];
$tipo=$_REQUEST["tipo"];
$id_gruppo=$_REQUEST["id_gruppo"];
$file_allegati=$_REQUEST["file_allegati"];
$archiviato=$_REQUEST["archiviato"];
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];

// connessione al dbatlante
$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	


$errore="";

if ($tipo=='1' and !$id_corso_s) {
	$errore .= "<br>$stringa[errore_gruppo_corso_richiesto]";
};	

if ($tipo=='3' and !$id_corso_s) {
	$errore .= "<br>$stringa[errore_lab_corso_richiesto]";
};	

if ($errore) {
	$errore=ereg_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$errore");
	exit();	
};

if ($id_gruppo and $tipo==0) $tipo=1;
if ($tipo==4) $id_gruppo="";

$query="UPDATE forum SET 
tipo='$tipo',
ordine='$ordine',
id_gruppo='$id_gruppo',
id_corso='$id_corso_s',
id_edizione='$id_edizione_s',
descrizione='$descrizione',
archiviato='$archiviato',
file_allegati='$file_allegati'
WHERE id_forum='$id_forum'
";

$result=$mysqli->query($query);

header("Location:index.php?risorsa=forum_admin_index&id_corso=$id_corso_s&id_edizione=$id_edizione_s");  
?>

<?php
require "./include/init_sito.inc";

$id_forum=mysql_real_escape_string($_REQUEST["id_forum"]);
$ordine=mysql_real_escape_string($_REQUEST["ordine"]);
$descrizione=mysql_real_escape_string($_REQUEST["descrizione"]);
$tipo=mysql_real_escape_string($_REQUEST["tipo"]);
$id_gruppo=$_REQUEST["id_gruppo"];
$file_allegati=$_REQUEST["file_allegati"];
$id_corso_s=mysql_real_escape_string($_REQUEST["id_corso"]);
$id_edizione_s=mysql_real_escape_string($_REQUEST["id_edizione"]);

// connessione al dbatlante
$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	



$id_forum=uniqid("forum_");

$errore="";

$id_forum=trim($id_forum);

if (!$id_forum) {
	$errore="<p>$stringa[errore_id_forum_richiesto]</p>";
};


if (!ereg("^[a-zA-Z0-9_]+$",$id_forum)) {
	$errore .= "<br>$stringa[errore_solo_lettere]";
};

/*
if ($tipo=='1' or $tipo=='3') {
	$id_forum=$id_corso_s."_".$id_edizione_s."_".$id_forum;
};
*/

$query = "SELECT * FROM forum WHERE id_forum='$id_forum'";
$result = $myqli->query($query);
$riga = $result->fetch_array();

if ($riga) {
	$errore .= "<p>$stringa[errore_forum_esiste]: $id_forum</p>";
};


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

$query="INSERT INTO forum (id_forum,tipo,ordine,id_corso,id_edizione,id_gruppo,descrizione,data_forum,file_allegati) VALUES (
'$id_forum','$tipo','$ordine','$id_corso_s','$id_edizione_s','$id_gruppo','$descrizione',NOW(),'$file_allegati')
";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=forum_admin_index&id_corso=$id_corso_s&id_edizione=$id_edizione_s");  

?>

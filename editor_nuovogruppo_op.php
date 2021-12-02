<?php
require "./include/init_sito.inc";
$descrizione=$_REQUEST["descrizione"];

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_editor_gruppo=trim($id_editor_gruppo);

$errore="";

if (!$descrizione) {
	$errore="<p>$stringa[errore_manca_descrizione]</p>";
};

	
if ($errore) {
	$errore=ereg_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$errore");
	exit();	
};

	

$query="INSERT INTO editor_gruppo SET descrizione='$descrizione'";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=editor_gruppi");  
?>

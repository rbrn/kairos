<?php
require "./include/init_sito.inc";

$id_editor_gruppo=mysql_real_escape_string($_REQUEST["id_editor_gruppo"]);
$descrizione=mysql_real_escape_string($_REQUEST["descrizione"]);

$errore="";

if (!$descrizione) {
	$errore="<p>$stringa[errore_manca_descrizione]</p>";
};

	
if ($errore) {
	$errore=ereg_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$errore");
	exit();	
};

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query="UPDATE editor_gruppo SET
descrizione='$descrizione'
WHERE id_editor_gruppo='$id_editor_gruppo' 
";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=editor_gruppi");  
?>

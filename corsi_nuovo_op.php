<?php
require "./include/init_sito.inc";

$id_corso=mysql_real_escape_string($_REQUEST["id_corso"]);
$descrizione=mysql_real_escape_string($_REQUEST["descrizione"]);
$testo=mysql_real_escape_string($_REQUEST["testo"]);


$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_corso=trim($id_corso);

$errore="";

if (!$id_corso) {
	$errore="<p>$stringa[errore_manca_id]</p>";
};


if (!ereg("^[a-zA-Z0-9_]+$",$id_corso)) {
	$errore .= "<br>$stringa[errore_solo_lettere]";
};

if ($id_corso) {
	$query = "SELECT * FROM corso WHERE id_corso='$id_corso'";
    $result = $mysqli->query($query);
	$riga = $result->fetch_array();

	if ($riga) {
		$errore .= "<p>$stringa[errore_id_esiste]</p>";
	};
};

if ($errore) {
	$errore=ereg_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$errore");
	exit();	
};

	

$query="INSERT INTO corso (id_corso,descrizione,testo) VALUES ('$id_corso','$descrizione','$testo')
";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=corsi_index");  
?>

<?php
require "./include/init_sito.inc";

$id_corso=mysql_real_escape_string($_REQUEST["id_corso"]);
$id_edizione=mysql_real_escape_string($_REQUEST["id_edizione"]);
$id_gruppo=mysql_real_escape_string($_REQUEST["id_gruppo"]);
$tipo_gruppo=mysql_real_escape_string($_REQUEST["tipo_gruppo"]);
$descrizione=mysql_real_escape_string($_REQUEST["descrizione"]);
$id_tutor=mysql_real_escape_string($_REQUEST["id_tutor"]);

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_gruppo=trim($id_gruppo);

$errore="";

if (!$id_gruppo) {
	$errore="<p>$stringa[errore_manca_id]</p>";
};


if (!ereg("^[a-zA-Z0-9_]+$",$id_gruppo)) {
	$errore .= "<br>$stringa[errore_solo_lettere]";
};

if ($id_gruppo) {
	$query = "SELECT * FROM gruppo_utenti WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
    $result = $mysqli->query($query);
    $riga = $result->fetch_array();
	if ($riga) {
		$errore .= "<p>$stringa[errore_id_esiste]</p>";
	};
};

if ($id_tutor) {
	$id_tutor=trim($id_tutor);
	$query = "SELECT id_utente FROM utenti WHERE id_utente='$id_tutor'";
    $result = $mysqli->query($query);
    $riga = $result->fetch_array();

	if (!$riga) {
		$errore .= "<p><b>$id_tutor</b>: $stringa[non_esiste] </p>";
	};

};
	
if ($errore) {
	$errore=ereg_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$errore");
	exit();	
};

	

$query="INSERT INTO gruppo_utenti SET
id_gruppo='$id_gruppo',
id_corso='$id_corso',
id_edizione='$id_edizione',
id_tutor='$id_tutor',
descrizione='$descrizione',
tipo_gruppo='$tipo_gruppo'
";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=corsi_iscrizioni&id_corso=$id_corso&id_edizione=$id_edizione");  
?>

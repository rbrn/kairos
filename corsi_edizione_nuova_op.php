<?php
require "./include/init_sito.inc";

$id_corso=mysql_real_escape_string($_REQUEST["id_corso"]);
$id_edizione=mysql_real_escape_string($_REQUEST["id_edizione"]);
$descrizione=mysql_real_escape_string($_REQUEST["descrizione"]);
$gg=$_REQUEST["gg"];
$mm=$_REQUEST["mm"];
$aa=$_REQUEST["aa"];
$durata=mysql_real_escape_string($_REQUEST["durata"]);
$un_mis=mysql_real_escape_string($_REQUEST["un_mis"]);
$stato=mysql_real_escape_string($_REQUEST["stato"]);

$id_edizione=trim($id_edizione);

$errore="";

if (!$id_edizione) {
	$errore="<p>$stringa[errore_manca_id]</p>";
};

if (!ereg("^[a-zA-Z0-9_]+$",$id_edizione)) {
	$errore .= "<br>$stringa[errore_solo_lettere]";
};

if ($id_edizione) {
	$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
    $result = $mysqli->query($query);
    $riga=$result->fetch_array();
	if ($riga) {
		$errore .= "<p>$stringa[errore_id_esiste]</p>";
	};
};

if ($errore) {
	$errore=ereg_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$errore");
	exit();	
};

	
$data_edizione=$aa."-".$mm."-".$gg;
$query="INSERT INTO edizioni (id_corso,id_edizione,descrizione,data_edizione,durata,un_mis,stato,autoiscrizione) VALUES ('$id_corso','$id_edizione','$descrizione','$data_edizione','$durata','$un_mis','$stato','$autoiscrizione')
";
$result = $mysqli->query($query);

$id_gruppo="Generale";
$descrizione=$stringa[generale];

$query="INSERT INTO gruppo_utenti SET
id_gruppo='$id_gruppo',
id_corso='$id_corso',
id_edizione='$id_edizione',
id_tutor='$id_tutor',
descrizione='$descrizione',
tipo_gruppo='0'
";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso");  
?>

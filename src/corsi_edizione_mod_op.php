<?php
require "./include/init_sito.inc";

$id_edizioni=mysql_real_escape_string($_REQUEST["id_edizioni"]);

$query = "SELECT * FROM edizioni WHERE id_edizioni='$id_edizioni'";
$result = $mysqli->query($query);
$riga=$result->fetch_array();

$id_corso=$riga["id_corso"];
$id_edizione=$riga["id_edizione"];

$descrizione=mysql_real_escape_string($_REQUEST["descrizione"]);
$gg=$_REQUEST["gg"];
$mm=$_REQUEST["mm"];
$aa=$_REQUEST["aa"];
$durata=$_REQUEST["durata"];
$un_mis=$_REQUEST["un_mis"];
$stato=mysql_real_escape_string($_REQUEST["stato"]);
$autoiscrizione=mysql_real_escape_string($_REQUEST["autoiscrizione"]);

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	



$data_edizione=$aa."-".$mm."-".$gg;
$query="UPDATE edizioni SET 
descrizione='$descrizione',
data_edizione='$data_edizione',
durata='$durata',
un_mis='$un_mis',
stato='$stato',
autoiscrizione='$autoiscrizione'
WHERE id_edizioni='$id_edizioni'";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso");  
?>

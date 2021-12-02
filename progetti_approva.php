<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_progetto=$_REQUEST["id_progetto"];
$id_utente=$kairos_cookie[0];

$ruolo=ruolo_utente($id_utente);

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);		

$query = "SELECT id_utente FROM progetti WHERE id_progetto=$id_progetto";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$id_utente1=$riga["id_utente"];

if ($id_utente1==$id_utente or $ruolo=="admin" or $ruolo=="staff") {
	$query = "UPDATE  progetti SET stato='2' WHERE id_progetto=$id_progetto";
	$result=$mysqli->query($query);
};

Header("Location:index.php?risorsa=progetti_cerca");		
?>

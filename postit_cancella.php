<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_db=$_REQUEST["id_postit"];
$id_pagina=$_REQUEST["id_pagina"];
$id_utente=$kairos_cookie[0];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$ruolo=ruolo_utente($id_utente);

mysql_select_db($DBASE,$db);	

$query="SELECT id_utente FROM postit WHERE id_postit='$id_db'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$id_autore=$riga[id_utente];
if ($id_autore==$id_utente or $ruolo=='admin' or $ruolo=='staff') {
	$query="DELETE FROM postit WHERE id_postit='$id_db'";
	$result=$mysqli->query($query);
};



if ($id_pagina<>"bacheca") {
	$url="materiali_browse.php";
} else {
	$url="index.php";
};
Header("Location:$url?risorsa=$id_pagina");

?>


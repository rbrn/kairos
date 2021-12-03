<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_risorsa=$_REQUEST["id_risorsa"];
$id_utente=$kairos_cookie[0];
$testo=mysql_real_escape_string($_REQUEST["testo"]);

$query = "INSERT INTO risorse_materiali_commenti (id_risorsa,id_utente,testo,data_commento) VALUES ('$id_risorsa','$id_utente','$testo',now())";
$result=$mysqli->query($query);

Header("Location:materiali_browse.php?risorsa=$id_risorsa");
?>

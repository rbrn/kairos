<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$tipo_elemento=$_REQUEST["tipo_elemento"];
$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$lim_inf=$_REQUEST["lim_inf"];
$lim_sup=$_REQUEST["lim_sup"];
$commento=$_REQUEST["testo"];
$id_utente=$kairos_cookie[0];


$query = "INSERT INTO lo_test_commento SET  
id_item='$id_item',
commento='$commento',
lim_inf='$lim_inf',
lim_sup='$lim_sup',
tipo_elemento='$tipo_elemento',
id_editor='$id_utente'
";
$result=$mysqli->query($query);

$url="index.php?risorsa=lo_test_commento_edit&tipo_elemento=$tipo_elemento&id_item=$id_item&risorsa_padre=$risorsa_padre";

Header("Location: $url");

?>

<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_commento=$_REQUEST["id_commento"];
$tipo_elemento=mysql_real_escape_string($_REQUEST["tipo_elemento"]);
$id_item=mysql_real_escape_string($_REQUEST["id_item"]);
$risorsa_padre=mysql_real_escape_string($_REQUEST["risorsa_padre"]);
$lim_inf=mysql_real_escape_string($_REQUEST["lim_inf"]);
$lim_sup=mysql_real_escape_string($_REQUEST["lim_sup"]);
$commento=mysql_real_escape_string($_REQUEST["testo"]);
$id_utente=$kairos_cookie[0];

$query = "UPDATE lo_test_commento SET  
commento='$commento',
lim_inf='$lim_inf',
lim_sup='$lim_sup'
WHERE id_commento='$id_commento'
";
$result=$mysqli->query($query);

$url="index.php?risorsa=lo_test_commento_edit&tipo_elemento=$tipo_elemento&id_item=$id_item&risorsa_padre=$risorsa_padre";

Header("Location: $url");

?>

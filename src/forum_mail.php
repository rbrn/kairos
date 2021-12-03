<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

if ( !isset($kairos_cookie[0]) ){
	$query = $_SERVER["QUERY_STRING"];
	$PHP_SELF=$_SERVER["PHP_SELF"];
	if ($query) {
		$url = "$PHP_SELF?$query";
	} else {
		$url ="$PHP_SELF";
	};
	$location="Location: $PATH_ROOT"."index.php?risorsa=do_login&url=$url";
	Header($location);
	exit();
};


$id_utente=$kairos_cookie[0];

$id_forum=$_REQUEST[id_forum];
$op=$_REQUEST[op];
$vista=$_REQUEST[vista];
$modo=$_REQUEST[modo];
$pagina=$_REQUEST[pagina];

mysql_select_db($DBASE,$db);

if ($op=='on') {
	$query2="INSERT INTO forum_mail SET id_forum='$id_forum',id_utente='$id_utente'";
} else {
	$query2="DELETE FROM forum_mail WHERE id_forum='$id_forum' AND id_utente='$id_utente'";
};
$result = $mysqli->query($query2);

$url="index.php?risorsa=forum_indice&id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina";
Header("Location: $url");

?>




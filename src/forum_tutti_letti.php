<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
require "./include/funzioni_forum.inc";


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
$vista=$_REQUEST[vista];
$modo=$_REQUEST[modo];
$pagina=$_REQUEST[pagina];

mysql_select_db($DBASE,$db);

$query = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum'";
$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {
	$id_post=$riga[id_post];
	$query2="INSERT INTO forum_read SET
	id_post=$id_post,
	id_forum='$id_forum',
	id_utente='$id_utente',
	data_read=NOW(),
	azione='letto_aut',
	id_corso='$id_corso_s',
	id_edizione='$id_edizione_s',
	id_gruppo='$id_gruppo_s'";
    $result = $mysqli->query($query2);
};

$url="index.php?risorsa=forum_indice&id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina";
Header("Location: $url");



?>




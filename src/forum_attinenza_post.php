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
$valore=$_REQUEST["valore"];

if ($valore<1) $valore=1;
if ($valore>4) $valore=4;

$query="SELECT * FROM forum_posts_attinenze WHERE id_post='$id_post' AND id_utente='$id_utente'";
$result = $mysqli->query($query);

if (!$result->num_rows) {
	$query="REPLACE INTO forum_posts_attinenze SET "
	." id_post='$id_post',"
	." id_forum='$id_forum',"
	." id_utente='$id_utente',"
	." id_corso='$id_corso_s',"
	." id_edizione='$id_edizione_s',"
	." id_gruppo='$id_gruppo_s',"
	." valore='$valore'";
    $result = $mysqli->query($query);

	$query="SELECT sum(valore) AS somma_valore FROM forum_posts_attinenze WHERE id_post='$id_post'";
    $result = $mysqli->query($query);
    $riga = $result->fetch_array();

	$somma_valore=$riga[somma_valore];

	$query="SELECT count(*) AS num_valore FROM forum_posts_attinenze WHERE id_post='$id_post'";
    $result = $mysqli->query($query);
    $riga = $result->fetch_array();

	$num_valore=$riga[num_valore];

	$attinenza=0;
	if ($num_valore>2) $attinenza=round($somma_valore/$num_valore);

	$query="UPDATE forum_posts SET attinenza='$attinenza',n_attinenze='$num_valore' WHERE id_post='$id_post'";
    $result = $mysqli->query($query);
};

$url="index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_post&vista=$vista&modo=$modo&pagina=$pagina";

Header("Location: $url");



?>




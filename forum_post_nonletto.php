<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
require "./include/funzioni_forum.inc";

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

$query="DELETE FROM forum_read WHERE id_utente='$id_utente' AND id_post='$id_post'";
$result = $mysqli->query($query);
$url="index.php?risorsa=forum_indice&id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina";
Header("Location: $url");

?>


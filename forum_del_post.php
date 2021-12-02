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
$ruolo=ruolo_utente($id_utente);


$query2 = "SELECT id_autore,nome_file FROM forum_posts WHERE id_post='$id_post' AND  id_forum='$id_forum'";


$result2 = $mysqli->query($query2);
$dati_post = $result2->fetch_array();

if (!$dati_post) {

	$errore="<p>$stringa[errore_no_intervento_del]</p>";

	$msg=ereg_replace(" ","%20",$errore);

	header("Location:index.php?risorsa=msg&msg=$msg");

	exit();

};



if ($dati_post["id_autore"]<>$id_utente and $ruolo<>'admin' and $ruolo<>'staff') {

	$errore="<p>$stringa[errore_no_intervento_del_altro]</p>";

	$msg=ereg_replace(" ","%20",$errore);

	header("Location:index.php?risorsa=msg&msg=$msg");

	exit();

};



refresh_utente($id_utente);





if ($vista=='data') {

	$id_start=$id_post;

} else {

	$id_start=ascendente($id_post);

};



$query = "DELETE FROM forum_posts 

WHERE id_forum='$id_forum' AND id_post='$id_post'";
$result = $mysqli->query($query);
$query = "DELETE FROM forum_read

WHERE id_forum='$id_forum' AND id_post='$id_post'";
$result = $mysqli->query($query);
if (trim($dati_post["nome_file"])) {

	$file = $PATH_ARCHIVI."forum/".$dati_post["nome_file"];

	if (file_exists($file)) {

		unlink($file);

	};

};



$url="index.php?risorsa=forum_indice&id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina";

Header("Location: $url");



?>




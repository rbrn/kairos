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



if ($op=="mark") {

	$query="INSERT INTO forum_mark (id_utente,id_post,id_forum,id_corso,id_edizione,id_gruppo) VALUES ('$id_utente','$id_post','$id_forum','$id_corso_s','$id_edizione_s','$id_gruppo_s')";

    $result = $mysqli->query($query);


} else {

	$query="DELETE FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post'";
    $result = $mysqli->query($query);

};

$url="index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_post&vista=$vista&modo=$modo&pagina=$pagina";

Header("Location: $url");



?>




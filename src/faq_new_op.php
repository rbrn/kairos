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


$ordine=mysql_real_escape_string($_REQUEST["ordine"]);
$domanda=mysql_real_escape_string($_REQUEST["domanda"]);
$risposta=mysql_real_escape_string($_REQUEST["testo"]);
$pagina=mysql_real_escape_string($_REQUEST["pagina_r"]);

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

if ($pagina=="info") $id_corso_s="";
	
$query="INSERT INTO faq (id_corso,ordine,domanda,risposta) VALUES
('$id_corso_s','$ordine','$domanda','$risposta')";
$result = $mysqli->query($query);

if ($pagina=="info") {
	Header("Location:index.php?risorsa=info");
} else {
	Header("Location:index.php?risorsa=faq");
};

?>


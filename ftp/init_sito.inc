<?php

include_once 'properties.php';

ereg("^([aA-zZ]+)\.(.+)$",$server,$parti);
$dominio=$parti[2];
if ($dominio=='ec2-54-229-184-60.eu-west-1.compute.amazonaws.com/kairos' or $dominio=='eureka.garamond.it' or $dominio=='koine.garamond.it') $dominio='garamond.it';

$altro_utente=$_REQUEST["altro_utente"];

$cod_area=$kairos_cookie[4];
if (!$cod_area) {
	$cod_area="kairos_demo";
};

$DBASE = $cod_area;
$DBASE_UTENTI=$cod_area;

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE_UTENTI,$db);
	
$query="SELECT stato FROM utenti WHERE id_utente='$kairos_cookie[0]'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$stato=$riga["stato"];

switch ($stato) {
	case 0:
		$ruolo="attesa";
		break;
			
	case 1:
		$ruolo="utente";
		break;
			
	case 2:
		$ruolo="staff";
		break;
			
	case 3:
		$ruolo="admin";
		break;
};


if ($altro_utente) {
	$area_utente=$altro_utente;
} else {
	$area_utente=$kairos_cookie_area;
};

if (!$area_utente) $area_utente=$kairos_cookie[0];

if ($area_utente<>$kairos_cookie[0] and $ruolo<>'staff' and $ruolo<>'admin') {
	$area_utente=$kairos_cookie[0];
};

if ($area_utente<>$kairos_cookie[0]) {
	$query="SELECT id_utente FROM utenti WHERE id_utente='$area_utente' LIMIT 1";
	$result=$mysqli->query($query);
	if (!$result->num_rows) {
		$area_utente=$kairos_cookie[0];
	};
};

$kairos_cookie_area=$area_utente;
setcookie("kairos_cookie_area","$kairos_cookie_area",0,"/",$dominio);

if (!isset($kairos_cookie[0])) {
	setcookie("kairos_cookie[3]","",0,"/",$dominio);
	Header("Location:../index.php?risorsa=do_login");
	exit();
};

$lifetime=mktime(12,50,30,6,20,2050);
$lingua=$_REQUEST["lingua"];

if (isset($lingua)) {
	$kairos_cookie_lingua=$lingua;
	setcookie("kairos_cookie_lingua",$lingua,$lifetime,"/",$dominio);
};

if (!isset($lingua)) {
	if (!isset($kairos_cookie_lingua)) {
		$lingua="it";
		$kairos_cookie_lingua=$lingua;
		setcookie("kairos_cookie_lingua",$lingua,$lifetime,"/",$dominio);
	};
};

$lingua=$kairos_cookie_lingua;

$file_lingua="../translation/stringhe_".$lingua.".inc";

if (!file_exists($file_lingua)) {
	$lingua="it";
	setcookie("kairos_cookie_lingua",$lingua,$lifetime,"/",$dominio);
	$file_lingua="stringhe_it.inc";
};

require "../include/$file_lingua";
	

$id_utente=$area_utente;

$PATH_ROOT0 = "http://$server/kairos/";
$PATH_ROOT = "http://$server/kairos/utenti/$cod_area/".$id_utente."/";
$PATH_ROOT_FILE = $SERVER_ROOT."kairos/utenti/$cod_area/".$id_utente;


mysql_select_db("atlante",$db);
$query="SELECT * FROM abbonamenti_piattaforma WHERE dominio='$server'";
$result=$mysqli->query($query);

if ($result->num_rows) {
	$riga=$result->fetch_array();
	$cod_area=$riga[tipo_area]."_".$riga[cod_area];
	$PATH_ROOT0="http://".$server."/";
	$PATH_ROOT = "http://$server/utenti/$cod_area/".$id_utente."/";
	$PATH_ROOT_FILE = $SERVER_ROOT."kairos/utenti/$cod_area/".$id_utente;
};


if (!is_dir($PATH_ROOT_FILE)) {
	mkdir($PATH_ROOT_FILE,0755);
};

$PATH_ROOT_FILE .= "/";

?>

<?php
include_once '../include/properties.php';
ereg("^([aA-zZ]+)\.(.+)$",$server,$parti);
$dominio=".".$parti[2];

$id_corso_ed_s=$kairos_cookie[2];
list($id_corso_s,$id_edizione_s,$id_gruppo_s,$id_tutor_s)=split(" ",$id_corso_ed_s);

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

$file_lingua="../include/stringhe_".$lingua.".inc";

if (!file_exists($file_lingua)) {
	$lingua="it";
	setcookie("kairos_cookie_lingua",$lingua,$lifetime,"/",$dominio);
	$file_lingua="stringhe_it.inc";
};

require "../include/$file_lingua";

$cod_area=$kairos_cookie[4];

if (!$cod_area) {
	$cod_area="kairos_demo";
};


$id_utente=$cod_area."_comune";
$PATH_ROOT_FILE = $SERVER_ROOT."kairos/"."utenti/$cod_area/".$id_utente;

if (!is_dir($PATH_ROOT_FILE)) {
	mkdir($PATH_ROOT_FILE,0755);
};

$id_utente=$cod_area."_comune"."/".$id_corso_s;

$PATH_ROOT0 = "http://$server/kairos/";
$PATH_ROOT = "http://$server/kairos/utenti/$cod_area/".$id_utente."/";
$PATH_ROOT_FILE = $SERVER_ROOT."kairos/"."utenti/$cod_area/".$id_utente;

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db("atlante",$db);

$query="SELECT * FROM abbonamenti_piattaforma WHERE dominio='$server'";
$result=$mysqli->query($query);

if ($result->num_rows) {
	$riga=$result->fetch_array();
	$cod_area=$riga[tipo_area]."_".$riga[cod_area];
	$PATH_ROOT0="http://".$server."/";
	$PATH_ROOT = "http://$server/utenti/$cod_area/".$id_utente."/";
	$PATH_ROOT_FILE = "kairos/utenti/$cod_area/".$id_utente;
};

if (!is_dir($PATH_ROOT_FILE)) {
	mkdir($PATH_ROOT_FILE,0755);
};

$PATH_ROOT_FILE .= "/";

if ($cod_area=="kairos_eprof") {
	$eprof=$kairos_cookie[8];
};

?>

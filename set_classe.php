<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente=$kairos_cookie[0];
$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];

if (!$id_corso) {
	setcookie("kairos_cookie[2]","",0,"/",$dominio);
	Header("Location:index.php?risorsa=index");
	exit();
};

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);
$ruolo=ruolo_utente($id_utente);
mysql_select_db($DBASE,$db);	

$valore=$id_corso." ".$id_edizione;

if ($valore) {
	$query="SELECT id_gruppo FROM iscrizioni_corso WHERE id_utente='$id_utente' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$id_gruppo=$riga["id_gruppo"];
	
	$query="SELECT id_tutor FROM gruppo_utenti WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$id_tutor=$riga["id_tutor"];
	
	$valore .=" ".$id_gruppo." ".$id_tutor;
};

if (!$valore) {
	$msg=$stringa[errore_no_accesso_corso];
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

setcookie("kairos_cookie[2]",$valore,0,"/",$dominio);

$query="REPLACE INTO contesto SET
id_utente='$id_utente',
id_corso='$valore'";
$mysqli->query($query);

Header("Location:index.php?risorsa=index");

?>

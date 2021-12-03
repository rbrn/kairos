<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$id_messaggio=$_REQUEST["id_messaggio"];

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query = "SELECT stato,id_mittente,id_destinatario FROM messaggi WHERE id_messaggio=$id_messaggio";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$stato=$riga["stato"];
$id_mittente=$riga["id_mittente"];
$id_destinatario=$riga["id_destinatario"];

if ($stato<>0) {
	$query = "DELETE FROM messaggi WHERE id_messaggio=$id_messaggio";
	$result=$mysqli->query($query);
} else {
	if ($kairos_cookie[0]==$id_mittente) {
		$nuovo_stato=1;
	} else {
		$nuovo_stato=2;
	};
	$query = "UPDATE messaggi SET stato=$nuovo_stato WHERE id_messaggio=$id_messaggio";
	$result=$mysqli->query($query);
};

Header("Location:index.php?risorsa=messaggi");
?>

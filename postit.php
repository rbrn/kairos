<?php
require "./include/init_sito.inc";

$id_utente=$kairos_cookie[0];
$id_db=$_REQUEST["id_db"];
$id_pagina=$_REQUEST["id_pagina"];
$x_p=$_REQUEST["x_p"];
$y_p=$_REQUEST["y_p"];
$colore=$_REQUEST["colore_post"];
$messaggio=trim($_REQUEST["msg_postit"]);
$tipo=$_REQUEST["tipo_post"];

if ($y_p<190) $y_p=190;

// connessione al dbatlante
$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

if ($id_db) {
	$query="UPDATE postit SET ";
	$condizione=" WHERE id_postit='$id_db'";
} else {
	$query="INSERT INTO postit SET ";
	$condizione="";
};

//$messaggio=str_replace("\'"," ",$messaggio);
//$messaggio=str_replace("\""," ",$messaggio);
$messaggio=nl2br($messaggio);
$messaggio=str_replace("\r\n","",$messaggio);
$messaggio=str_replace("\n\r","",$messaggio);
$query .= "
id_utente='$id_utente',
data_postit=NOW(),
id_corso='$id_corso_s',
id_edizione='$id_edizione_s',
id_pagina='$id_pagina',
x_p='$x_p',
y_p='$y_p',
colore='$colore',
tipo='$tipo',
messaggio='$messaggio'";

$query .= $condizione;	

$result=$mysqli->query($query);

if ($id_pagina<>"bacheca") {
	$url="materiali_browse.php";
} else {
	$url="index.php";
};
Header("Location:$url?risorsa=$id_pagina");

?>


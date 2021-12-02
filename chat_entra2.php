<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect(C_DB_HOST,C_DB_USER,C_DB_PASS);
mysql_select_db(C_DB_NAME,$db);

$id_utente=$kairos_cookie[0];
$stanza=$_REQUEST["stanza"];

if ($stanza<>"Generale") {
	$lab=substr($stanza,0,4);
	if ($lab=='lab_') {
		$corso=substr($stanza,4,strlen($stanza)-4);
	} else {
		$corso=$stanza;
	};
	
	if ($corso<>$id_corso_s) {
		$msg=$stringa[errore_no_risorsa_accesso];
		$msg=ereg_replace(" ","%20",$msg);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
	};
};

refresh_utente($id_utente);
$query="INSERT INTO ".C_MSG_TBL." VALUES ('', '$stanza', '', '', ".time().", '', '/enter $id_utente')";

$mysqli->query($query);

$query="SELECT * FROM ".C_USR_TBL." WHERE username='$id_utente'";
$result=$mysqli->query($query);


$riga=$result->fetch_array();
if ($riga["username"]) {
	$query="UPDATE ".C_USR_TBL." SET room='$stanza',u_time='".time()."', status='' WHERE username='$id_utente'"; 
	$mysqli->query($query);
} else {
	$query="INSERT INTO ".C_USR_TBL." VALUES ('$stanza', '$id_utente', '1', ".time().", '')";
	$mysqli->query($query);
};

setcookie("chat_stanza",$stanza,0,"/",$dominio);
/* reindirizzo alla pagina di chat */

Header("Location:index_chat2.php");


?>

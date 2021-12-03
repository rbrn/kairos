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
		list($corso,$resto)=split("-",$stanza);
		if ($corso<>$id_corso_s) {
			$msg=$stringa[errore_no_risorsa_accesso];
			$msg=ereg_replace(" ","%20",$msg);
			Header("Location:index.php?risorsa=msg&msg=$msg");
			exit();
		};
	};
};

refresh_utente($id_utente);
if ($id_utente<>"garamond") {
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
};

$query="SELECT * FROM c_moderazione WHERE id_stanza='$stanza'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$id_moderatore=$riga[id_moderatore];
$id_utente_abilitato=$riga[id_utente_abilitato];
if ($id_moderatore) {
$riga_chat="Ciao $id_utente! Il chat ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ moderato da $id_moderatore. Per prendere la parola bisogna prenotarsi alzando la mano.";
if ($id_utente_abilitato) $riga_chat.="<br>Al momento la parola ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ concessa a: $id_utente_abilitato";
$M=$riga_chat;
$riga_chat=addslashes($M);
$tempo=time()+1;
$query="INSERT INTO ".C_MSG_TBL." VALUES ('', '$stanza', '', '', ".$tempo.", '', '/moderazione $riga_chat')";
$mysqli->query($query);
};

setcookie("chat_stanza",$stanza,0,"/",$dominio);
/* reindirizzo alla pagina di chat */

Header("Location:index_chat.php");


?>

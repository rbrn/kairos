<?php

require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";



$db = mysql_connect(C_DB_HOST,C_DB_USER,C_DB_PASS);

mysql_select_db(C_DB_NAME,$db);

$id_utente=$kairos_cookie[0];

refresh_utente($id_utente);

if ($id_utente<>"garamond") {
$query="INSERT INTO ".C_MSG_TBL." VALUES ('', '$chat_stanza', '', '', ".time().", '', '/exit $id_utente')";
$mysqli->query($query);
};

$query="DELETE FROM ".C_USR_TBL." WHERE username='$id_utente'";
$mysqli->query($query);

$query="DELETE FROM musica_chat_stato WHERE stanza='$chat_stanza' and id_utente='$kairos_cookie[0]'";
$mysqli->query($query);

setcookie("chat_stanza","",0,"/",$dominio);

Header("Location:index.php?risorsa=chat");

?>

<?php

require "./include/init_sito.inc";

require "./include/funzioni_sito.inc";



$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	



$id_utente=$kairos_cookie[0];



$query = "DELETE FROM inlinea WHERE id_utente='$id_utente'";

$result=$mysqli->query($query);

$query="DELETE FROM c_users WHERE username='$id_utente'";

$result=$mysqli->query($query);

$query = "INSERT INTO log_sito(id_utente,data_log,dettagli,id_corso,id_edizione,id_gruppo) VALUES ('$id_utente',NOW(),'logout','$id_corso_s','$id_edizione_s','$id_gruppo_s')";
$result=$mysqli->query($query);

deleteCookies();

header("Location:index.php?risorsa=index");



?>

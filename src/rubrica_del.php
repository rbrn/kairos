<?php

require "./include/init_sito.inc";



$id_rubrica=$_REQUEST["id_rubrica"];



$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	



$query = "DELETE FROM rubrica WHERE id_rubrica='$id_rubrica'";

$result=$mysqli->query($query);



header("Location:index.php?risorsa=gestione_rubriche");  



?>

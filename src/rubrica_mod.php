<?php

require "./include/init_sito.inc";



$id_rubrica=$_REQUEST["id_rubrica"];

$posizione=$_REQUEST["posizione"];

$titolo=$_REQUEST["titolo"];



$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	



$query = "UPDATE rubrica SET 

titolo='$titolo',

posizione='$posizione'

WHERE id_rubrica='$id_rubrica'";

$result=$mysqli->query($query);



header("Location:index.php?risorsa=gestione_rubriche");  



?>

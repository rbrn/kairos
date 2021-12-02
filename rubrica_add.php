<?php

require "./include/init_sito.inc";



$id_rubrica=$_REQUEST["id_rubrica"];

$posizione=mysql_real_escape_string($_REQUEST["posizione"]);

$titolo=mysql_real_escape_string($_REQUEST["titolo"]);



// connessione al dbatlante

$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	



$query = "SELECT * FROM rubrica WHERE id_rubrica='$id_rubrica'";

$result=$mysqli->query($query);

$riga = $result->fetch_array();



$errore="";



$id_rubrica=trim($id_rubrica);



if ($riga) {

	$errore .= "<p>Esiste giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ una rubrica con identificativo: $id_rubrica</p>";

};



if (!$id_rubrica) {

	$errore="<p>E' obbligatorio specificare un id rubrica!</p>";

};



if (!ereg("^[a-zA-Z0-9_]+$",$id_rubrica)) {

	$errore .= "<br>Sono ammessi solo lettere, numeri e _ per l'identificativo";

};





if ($errore) {

	$errore=ereg_replace(" ","%20",$errore);

	header("Location:pagina.php?risorsa=msg&msg=$errore");

	exit();	

};

	



$query="INSERT INTO rubrica (id_rubrica,titolo,posizione) VALUES (

'$id_rubrica','$titolo','$posizione')";

$result=$mysqli->query($query);



header("Location:index.php?risorsa=gestione_rubriche");  



?>




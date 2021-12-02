<?php
require "./include/init_sito.inc";

$id_corso_edizione=$_REQUEST["id_corso_edizione"];
$id_corso_edizione_copia=$_REQUEST["id_corso_edizione_copia"];

list($id_corso,$id_edizione)=split(" ",$id_corso_edizione);
list($id_corso_copia,$id_edizione_copia)=split(" ",$id_corso_edizione_copia);


$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);

$query="DELETE FROM materiali_sequenza WHERE id_corso='$id_corso_copia' AND id_edizione='$id_edizione_copia'";
$result=$mysqli->query($query);

$query="SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {
	$id_risorsa=$riga["id_risorsa"];
	$tipo_risorsa=$riga["tipo_risorsa"];
	$ordine=$riga["ordine"];
	$data_rilascio=$riga["data_rilascio"];
	$id_gruppo=$riga["id_gruppo"];
	$id_utente=$riga["id_utente"];
	
	$query1="INSERT INTO materiali_sequenza SET
	id_risorsa='$id_risorsa',
	tipo_risorsa=$tipo_risorsa,
	ordine=$ordine,
	data_rilascio='$data_rilascio',
	id_corso='$id_corso_copia',
	id_edizione='$id_edizione_copia',
	id_gruppo='$id_gruppo',
	id_utente='$id_utente'";
	
	$mysqli->query($query1);
	
};
Header("Location:index.php?risorsa=utility_index");
?>

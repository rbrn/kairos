<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
 
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$ruolo=ruolo_utente($kairos_cookie[0]);
if ($ruolo<>"admin") {
	$msg="Accesso riservato solo allo staff.";
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

$id_lo=$_REQUEST["id_lo"];
$pagina=$_REQUEST["pag"];
$pag_size=$_REQUEST["pag_size"];
$filtro=$_REQUEST["filtro"];
$titolo_cerca=$_REQUEST["titolo_cerca"];
$materia_cerca=$_REQUEST["materia_cerca"];

$query = "DELETE FROM lo_repository WHERE id_lo='$id_lo'";
$result=$mysqli->query($query);

Header("Location:index.php?risorsa=lo_repository&pagina=$pagina&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro");
?>

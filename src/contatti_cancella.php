<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente=$kairos_cookie[0];

$id_contatto =$_REQUEST[id_contatto];

$query="DELETE FROM contatti WHERE id_contatto='$id_contatto'";
$result = $mysqli->query($query);

header("Location:contatti_cerca.php");
?>

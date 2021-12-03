<?php
require "./include/init_sito.inc";


$id_articolo=$_REQUEST["id_articolo"];
$id_lettore=$_REQUEST["id_lettore"];
$testo=$_REQUEST["testo"];

$testo = htmlentities($testo);
$testo = str_replace ("\n", "<br>", $testo);
$testo = str_replace (" ", "&nbsp;",$testo);

$query = "INSERT INTO commento (id_articolo,nome_lettore,testo) VALUES ('$id_articolo','$id_lettore','$testo')";
$result = $mysqli->query($query);

Header("Location:index.php?risorsa=articolo_view&id_articolo=$id_articolo");
?>

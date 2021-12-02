<?php
$id_modulo=$_REQUEST["id_modulo"];
$gruppo=$_REQUEST["gruppo"];
require "./init_esporta.php";
require "./funzioni_esporta.php";
$xml="";
esporta_modulo();
?>

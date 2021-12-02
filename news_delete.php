<?php
require "./include/init_sito.inc";


$posizione=$_REQUEST["posizione"];
$tipo_news=$_REQUEST["tipo_news"];
$id_news=$_REQUEST["id_news"];

if ($tipo_news==0) {
	$query = "DELETE FROM hp_news WHERE posizione='$posizione' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
} else {
	$query = "DELETE FROM hp_news WHERE id_news='$id_news'";
};

$result = $mysqli->query($query);

$url="index.php?risorsa=index";
Header("Location: $url");
?>

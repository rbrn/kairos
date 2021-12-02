<?php
require "./include/init_sito.inc";

$id_articolo=$_REQUEST["id_articolo"];
$id_commento=$_REQUEST["id_commento"];

$query = "DELETE FROM commento WHERE id_commento='$id_commento'";
$result = $mysqli->query($query);

Header("Location:index.php?risorsa=articolo_view&id_articolo=$id_articolo");
?>

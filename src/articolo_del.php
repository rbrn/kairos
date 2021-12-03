<?php

require "./include/init_sito.inc";

$id_articolo=$_REQUEST["id_articolo"];

$query = "DELETE FROM articolo WHERE id_articolo='$id_articolo'";

$result = $mysqli->query($query);

header("Location:index.php?risorsa=gestione_articoli");  



?>

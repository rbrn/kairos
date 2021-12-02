<?php
require "./include/init_sito.inc";

$id_corso=$_REQUEST["id_corso"];

$query="DELETE FROM  corso  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

$query="DELETE FROM  edizioni  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

$query="DELETE FROM  iscrizioni_corso  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

$query="DELETE FROM  gruppo_utenti  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_archivio  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_posts_archivio  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_posts  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_read  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_mark  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

$query="DELETE FROM  materiali_sequenza  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

$query="DELETE FROM  hp_news  WHERE id_corso='$id_corso'";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=corsi_index");  
?>

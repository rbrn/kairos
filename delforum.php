<?php
require "./include/init_sito.inc";
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];

$query="DELETE FROM forum WHERE id_forum='$id_forum'";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=forum_admin_index&id_corso=$id_corso_s&id_edizione=$id_edizione_s");  
?>




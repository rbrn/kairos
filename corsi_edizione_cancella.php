<?php
require "./include/init_sito.inc";
$id_edizioni=$_REQUEST["id_edizioni"];

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query = "SELECT * FROM edizioni WHERE id_edizioni='$id_edizioni' ";
$result = $mysqli->query($query);
$riga=$result->fetch_array();

$id_corso=$riga["id_corso"];
$id_edizione=$riga["id_edizione"];

$query="DELETE FROM  edizioni  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  iscrizioni_corso  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  gruppo_utenti  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_archivio  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_posts_archivio  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_posts  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_read  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_mark  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  materiali_sequenza  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  hp_news  WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso");  
?>

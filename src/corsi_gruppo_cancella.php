<?php

require "./include/init_sito.inc";

$id_gruppo=$_REQUEST["id_gruppo"];
$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];

if ($id_gruppo=="generale" or $id_gruppo=="Generale") {
	$msg="Non puoi cancellare questo gruppo";
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

$query="DELETE FROM  gruppo_utenti  WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  iscrizioni_corso  WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_archivio  WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_posts_archivio WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum  WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_posts WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_read  WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  forum_mark  WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  materiali_sequenza  WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

$query="DELETE FROM  hp_news  WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);

header("Location:index.php?risorsa=corsi_iscrizioni&id_corso=$id_corso&id_edizione=$id_edizione");
?>

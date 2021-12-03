<?php
require "../config.php";

$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);

$id_profile=$_REQUEST[id_profile];

$query="DELETE FROM profile WHERE id_profile='$id_profile'";
$mysqli->query($query);

$query="DELETE FROM lo_schema WHERE id_profile='$id_profile'";
$mysqli->query($query);

$query="DELETE FROM lo_metadata WHERE id_profile='$id_profile'";
$mysqli->query($query);
/*
dovrei anche cancellare da lo_metadata_valore i corrispondenti id_rep che ho cancellato da lo_metadata
*/

Header("Location:index.php");
?>

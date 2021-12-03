<?php
require "./config.php";

$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);

$id_lom=$_REQUEST[id_lom];
$id_lom_sup=$_REQUEST[id_lom_sup];
$id_profile=$_REQUEST[id_profile];


$query="DELETE FROM lo_schema WHERE id_lom='$id_lom' AND id_profile='$id_profile'";
$mysqli->query($query);

$query="DELETE FROM lo_metadata WHERE id_lom='$id_lom' AND id_profile='$id_profile'";

/*
dovrei anche cancellare da lo_metadata_valore i corrispondenti id_rep che ho cancellato da lo_metadata
*/
$mysqli->query($query);
Header("Location:profile_index.php?id_lom=$id_lom_sup&id_profile=$id_profile");
?>

<?php
require "../include/init_sito.inc";
require "./config_xml_lom.php";
require "./variabili_xml_lom.php";
require "./funzioni_xml_lom.php";


$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);

$id_lo=$_REQUEST[id_lo];
$encode=$_REQUEST[encode];
if (!$id_lo) {
	$msg="Nessun LO";
    Header("Location:msg.php?msg=$msg");
    exit();
};

$query="SELECT * FROM lo WHERE id_lo='$id_lo'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$id_profile=$riga[id_profile];

if (!$encode) $encode="LOM";

$xml="";

xml_lo($id_lo,$id_profile);

$filename=$id_lo.".xml";
header("Content-Type: text/xml");

header( "Content-Disposition: attachment; filename=$filename" ); 	

echo($xml);
?>

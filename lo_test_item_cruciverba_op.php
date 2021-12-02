<?php
require "./include/init_sito.inc";

$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$larghezza=$_REQUEST["larghezza"];
$altezza=$_REQUEST["altezza"];

			
$query = "UPDATE lo_test_item_cruciverba SET  
larghezza='$larghezza',
altezza='$altezza' WHERE id_item='$id_item'";
$result=$mysqli->query($query);


$url="index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre";
	
Header("Location: $url");

?>

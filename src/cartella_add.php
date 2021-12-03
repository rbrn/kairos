<?php
require "./include/init_sito.inc";
$cartella=$_REQUEST["cartella"];
$id_cartella=$_REQUEST["id_cartella"];

$errore = ""; 
if (!$id_cartella) {
	$errore .= "<br>$stringa[errore_manca_id]";
};		

if (!ereg("^[a-zA-Z0-9_]+$",$id_cartella)) {
	$errore .= "<br>$stringa[errore_solo_lettere]";
};				

if ($errore) {
	$msg=ereg_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

$path_file=$PATH_ROOT_FILE."img/".$cartella."/".$id_cartella;
mkdir($path_file,0775);
Header("Location:index.php?risorsa=cartella&cartella=$cartella");		
?>

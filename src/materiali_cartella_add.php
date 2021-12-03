<?php
require "./include/init_sito.inc";
$cartella=$_REQUEST["cartella"];
$tipo_file=$_REQUEST["tipo"];
$id_cartella=$_REQUEST["id_cartella"];
$dir=$_REQUEST["dir"];
$contesto=$_REQUEST["contesto"];
$nome_campo=$_REQUEST["nome_campo"];

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

$path_file=$PATH_ROOT_FILE."materiali_img/$cod_area/$dir/".$cartella."/".$id_cartella;

mkdir($path_file,0775);

Header("Location:index.php?risorsa=materiali_cartella&tipo=$tipo_file&cartella=$cartella&dir=$dir&contesto=$contesto&nome_campo=$nome_campo");		
?>

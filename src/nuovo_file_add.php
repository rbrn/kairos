<?php

require "./include/init_sito.inc";



$cartella=$_REQUEST["cartella"];



$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];

$file=$_FILES["file"]["tmp_name"];

$file_size=$_FILES["file"]["size"];

$file_name=$_FILES["file"]["name"];



$errore = ""; 

if ($file_size > $MAX_FILE_SIZE) {

	$errore .= "<br>$stringa[errore_max_file]";

};

									

if ($errore) {

	$msg=ereg_replace(" ","%20",$errore);

	Header("Location:index.php?risorsa=msg&msg=$msg");

	exit();

};



if ($file_name) {

	$file_name = trim($file_name);

	$file_name = ereg_replace(" ","",$file_name);

	$file_name = strtolower($file_name);

	$fullpath = $PATH_ROOT_FILE."img/".$cartella."/".$file_name;

	copy($file,$fullpath);	

	};



Header("Location:index.php?risorsa=cartella&cartella=$cartella");			

?>

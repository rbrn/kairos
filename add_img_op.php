<?php
require "./include/init_sito.inc";
$errore = "";
$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];
$nome_file=$_FILES["nome_file"]["tmp_name"];
$nome_file_size=$_FILES["nome_file"]["size"];
$nome_file_name=$_FILES["nome_file"]["name"];
$nome_file_type=$_FILES["nome_file"]["type"];

if ($nome_file_name) {
	$est = strtolower(substr($nome_file_name,-3));
	if ($est != "gif" and $est != "jpg") {
		$errore .= "<br>$stringa[errore_gif_jpg]";
	};
};			

if ($nome_file_size > $MAX_FILE_SIZE) {
		$errore .= "<br>$stringa[errore_max_file]";
};		

if ($errore) {
			echo "
			<HTML>
<HEAD><TITLE>Kairos: $stringa[errore]</TITLE>
</HEAD>
<BODY bgcolor=#ffffcc>
<font face=verdana size=-1>$stringa[errore_intro]:<br><b>".$errore."</b></font>";
			echo "<p><center><a href=javascript:history.back()>$stringa[indietro]</a></center></body></html>";
		exit();
};

if ($nome_file_name) {
	$nome_file_name = trim($nome_file_name);
	$nome_file_name = ereg_replace(" ","",$nome_file_name);
	$nome_file_name = strtolower($nome_file_name);
	$fullpath = $PATH_ROOT_FILE."images/$cod_area/".$nome_file_name;
	copy($nome_file,$fullpath);	
};

Header("Location:img.php");				
?>

<?php
require "./init_sito.inc";
$cartella=$_REQUEST["cartella"];
$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];
$file=$_FILES["file"]["tmp_name"];
$file_size=$_FILES["file"]["size"];
$file_name=$_FILES["file"]["name"];
$file_type=$_FILES["file"]["type"];

$errore = ""; 
if ($file_size > $MAX_FILE_SIZE) {
		$errore .= "<br>$stringa[errore_max_file]";
		};
									
if ($errore) {
	$msg= "<b>$stringa[errore]</b>:<br><br><b>".$errore."</b>";
		echo "
	<html>
	<head><title>$stringa[errore]</title>
	<link rel=\"stylesheet\" href=\"../stili/$cod_area/stile_sito.css\">
	<script language=\"JavaScript\" src=\"../script/funzioni.js\"></script>
	</HEAD>
	<BODY bgcolor=$colore_sfondo>
	<p>
	<span class=testo>$errore</span>
	</p>
	<span class=testo>
	<a href=javascript:history.back()>[".$stringa[indietro]."]</a>
	</span>
	</body>
	</html>";
	exit();
};

if ($file_name) {
	$file_name = trim($file_name);
	$file_name = ereg_replace(" ","",$file_name);
	$file_name = strtolower($file_name);
	$fullpath = $PATH_ROOT_FILE.$cartella."/".$file_name;
	if (file_exists($file)) {
		copy($file,$fullpath);	
	};
};

Header("Location:index.php?cartella=$cartella");		
?>

<?php
require "./init_sito.inc";
$cartella=$_REQUEST["cartella"];
$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];
$file=$_FILES["file"]["tmp_name"];
$file_size=$_FILES["file"]["size"];
$file_name=$_FILES["file"]["name"];
$file_type=$_FILES["file"]["type"];

$errore = ""; 
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
	//$file_name = strtolower($file_name);
	$est = substr($file_name,-3);
	
	if ($est=="zip") {
		/*
		$nome_dir = substr(basename($file_name),0,strpos(basename($file_name),"."));
		$directory=$PATH_ROOT_FILE.$nome_dir;
		if (!file_exists($directory)) {
			mkdir($directory,0777);
		};
		*/
		$path_file=$PATH_ROOT_FILE.$cartella;
		$fullpath = $path_file."/".$file_name;
		copy($file,$fullpath);	
		$comando="/usr/bin/unzip $fullpath -d $path_file > /dev/null";
		shell_exec($comando);
		unlink($fullpath);
	};
};

Header("Location:index.php?cartella=$cartella");		
?>

<?php
require "./init_sito.inc";
$cartella=$_REQUEST["cartella"];
$id_cartella=$_REQUEST["id_cartella"];
$errore = ""; 
if (!$id_cartella) {
		$errore .= "<br>$stringa[errore_manca_id]";
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

$id_cartella = ereg_replace(" ","",$id_cartella);
$id_cartella = strtolower($id_cartella);

$path_file=$PATH_ROOT_FILE.$cartella."/".$id_cartella;

mkdir($path_file,0775);

Header("Location:index.php?cartella=$cartella");		
?>

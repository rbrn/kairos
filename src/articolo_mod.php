<?php

require "./include/init_sito.inc";

$id_articolo=mysql_real_escape_string($_REQUEST["id_articolo"]);

$id_utente=$_REQUEST["id_utente"];

$titolo=mysql_real_escape_string($_REQUEST["titolo"]);

$sommario=mysql_real_escape_string($_REQUEST["sommario"]);

$id_rubrica=$_REQUEST["id_rubrica"];

$testo=mysql_real_escape_string($_REQUEST["testo"]);

$area_link=mysql_real_escape_string($_REQUEST["area_link"]);

$area_label=mysql_real_escape_string($_REQUEST["area_label"]);

$stato=mysql_real_escape_string($_REQUEST["stato"]);

$parole_chiave=mysql_real_escape_string($_REQUEST["parole_chiave"]);



$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];

$immagine=$_FILES["immagine"]["tmp_name"];

$immagine_size=$_FILES["immagine"]["size"];

$immagine_name=$_FILES["immagine"]["name"];



if ($immagine_name) {

	$est = strtolower(substr($immagine_name,-3));

};			



if ($immagine_size > $MAX_FILE_SIZE) {

	$errore .= "<br>Il file immagine  troppo grande!";

};

									

if ($errore) {

	$msg=ereg_replace(" ","%20",$errore);

	Header("Location:pagina.php?risorsa=msg&msg=$msg");

	exit();

}; 



$query = "UPDATE articolo SET

 titolo='$titolo',

 sommario='$sommario',

 id_rubrica='$id_rubrica',

 testo='$testo',

 area_link='$area_link',

 area_label='$area_label',

 stato='$stato',

 parole_chiave='$parole_chiave' WHERE id_articolo='$id_articolo'";



$result = $mysqli->query($query);



if ($immagine_name) {

	$immagine_name = trim("im_$id_articolo.$est");

	$immagine_name = strtolower($immagine_name);

	$fullpath = $PATH_ROOT_FILE."immagini/$cod_area/".$immagine_name;

	copy($immagine,$fullpath);	

};

header("Location:index.php?risorsa=gestione_articoli");  

?>

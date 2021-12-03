<?php 
require "./include/init_sito.inc";

$testo=$_REQUEST["testo"];

$cod_area=$kairos_cookie[4];

$contenuto=$PATH_ROOT_FILE.$cod_area."_".$id_corso_s."_laboratorio.txt";

$fd=fopen ($contenuto,"w");

$testo=stripslashes($testo);

fwrite($fd,$testo);

fclose($fd);

$semaforo=$PATH_ROOT_FILE.$cod_area."_".$id_corso_s."_semaforo.txt";

$id_utente=$kairos_cookie[0];

$fd=fopen($semaforo,"w");

fwrite($fd,$id_utente);

fclose($fd);

Header("Location:atlante_editor.php");
?>

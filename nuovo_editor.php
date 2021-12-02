<?php 
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");
require "./include/init_sito.inc";

$contenuto=$PATH_ROOT_FILE.$cod_area."_".$id_corso_s."_laboratorio.txt";
$fd=fopen ($contenuto,"w");
$testo="";
fwrite($fd,$testo);
fclose($fd);
$semaforo=$PATH_ROOT_FILE.$cod_area."_".$id_corso_s."_semaforo.txt";
$id_utente=$kairos_cookie[0];
$fd=fopen($semaforo,"w");
fwrite($fd,$id_utente);
fclose($fd);
Header("Location:atlante_editor.php");
?>

<?php
require "./include/init_sito.inc";

$id_utente=$kairos_cookie[0];
$tipo_news=$_REQUEST["tipo_news"];
$testo=mysql_real_escape_string($_REQUEST["testo"]);
//$posizione=$_REQUEST["posizione"];
$url=mysql_real_escape_string($_REQUEST["url"]);
$url_label=mysql_real_escape_string($_REQUEST["url_label"]);

$errore = ""; 

if (!$testo) {
	$errore .= "<br>$stringa[errore_manca_testo]";
};	

if (!$url_label and $url) {
	$errore .= "<br>$stringa[errore_manca_titolo]";
};	

if ($errore) {
	$errore=str_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$errore");
	exit();	
};



if ($tipo_news==0) {
	for ($i=$n_news;$i>=1;$i--) {
		$old_pos="r".$i;
		$j=$i+1;
		$new_pos="r".$j;
		$query = "UPDATE hp_news SET posizione='$new_pos' WHERE posizione='$old_pos' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo='0'";
        if(!$mysqli->query($query)){
            die($mysqli->error);
        }

    };
		$posizione="r1";
};

$query = "INSERT INTO hp_news (tipo,posizione,id_utente,data_news,url,testo,url_label,id_corso,id_edizione) VALUES ('$tipo_news','$posizione','$id_utente',NOW(),'$url','$testo','$url_label','$id_corso_s','$id_edizione_s')";
if(!$mysqli->query($query)){
  die($mysqli->error);
}

$url="index.php?risorsa=index";
Header("Location: $url");
?>

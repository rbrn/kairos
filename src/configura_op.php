<?php 
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
 
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$ruolo=ruolo_utente($kairos_cookie[0]);
if ($ruolo<>"admin") {
	$msg="Accesso riservato solo allo staff.";
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

$img_sfondo_default=$_REQUEST["img_sfondo_default"];
$img_testata_default=$_REQUEST["img_testata_default"];

$val_colore_testo=$_REQUEST["val_colore_testo"];
$val_colore_sfondo=$_REQUEST["val_colore_sfondo"];
$val_colore_sfondo_testata=$_REQUEST["val_colore_sfondo_testata"];
$val_colore_bordo=$_REQUEST["val_colore_bordo"];
$val_colore_testonegativo=$_REQUEST["val_colore_testonegativo"];
$val_colore_link=$_REQUEST["val_colore_link"];
$val_nome_org=$_REQUEST["val_nome_org"];

$codice="<"."?php \r\n";
$codice .= "$"."colore_testo=\"$val_colore_testo\";\r\n";
$codice .= "$"."colore_testonegativo=\"$val_colore_testonegativo\";\r\n";
$codice .= "$"."colore_link=\"$val_colore_link\";\r\n";
$codice .= "$"."colore_sfondo=\"$val_colore_sfondo\";\r\n";
$codice .= "$"."colore_sfondo_testata=\"$val_colore_sfondo_testata\";\r\n";
$codice .= "$"."colore_bordo=\"$val_colore_bordo\";\r\n";
$codice .= "$"."colore_scuro=\"$val_colore_bordo\";\r\n";
$codice .= "$"."nome_org=\"$val_nome_org\";\r\n";
$codice .= "?".">";

$file="./pagine/$cod_area/colori.inc";

$fd=fopen($file,"w");
fwrite($fd,$codice);
fclose($fd);

$file_css_template="./stili/kairos_demo/stile_sito.css.template";
$col_neg=$val_colore_testonegativo;
$str_css=join('',file($file_css_template));
$str_css=str_replace('colore_testo',$val_colore_testo,$str_css);
$str_css=str_replace('colore_negativo',$col_neg,$str_css);
$str_css=str_replace('colore_link',$val_colore_link,$str_css);
$str_css=str_replace('colore_sfondo_testata',$val_colore_sfondo_testata,$str_css);

$file_css="./stili/$cod_area/stile_sito.css";
$fd=fopen($file_css,"w");
fwrite($fd,$str_css);
fclose($fd);


$file_css_template="./stili/kairos_demo/style.css.template";
$col_neg=$val_colore_testonegativo;
$str_css=join('',file($file_css_template));
$str_css=str_replace('colore_testo',$val_colore_testo,$str_css);
$str_css=str_replace('colore_negativo',$col_neg,$str_css);
$str_css=str_replace('colore_sfondo',$val_colore_sfondo,$str_css);
$str_css=str_replace('colore_scuro',$val_colore_scuro,$str_css);

$file_css="./stili/$cod_area/style.css";
$fd=fopen($file_css,"w");
fwrite($fd,$str_css);
fclose($fd);

$file_testata=$_FILES["file"]["tmp_name"][0];
$file_sfondo=$_FILES["file"]["tmp_name"][1];

if ($file_testata and !$img_testata_default) {
	
	
	$size=getimagesize($file_testata);
	$width=$size[0];
	$height=$size[1];
	$type=$size[2];
	$errore="";

	if ($type<>1 and $type<>2) {
		$errore.="<br>$stringa[errore_immagine_gif_testata]";
	};
/*
	if ($width>756) {
		$errore.="<br>$stringa[errore_testata_max]";
	};

	if ($height<>78) {
		$errore.="<br>$stringa[errore_testata_78]";
	};
*/	
	if ($errore) {
		$msg=ereg_replace(" ","%20",$errore);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
	};
	
	if ($type==1) $est=".gif";
	if ($type==2) $est=".jpg";
	
	$fullpath = "./img/$cod_area/testata.gif";
	if (file_exists($fullpath)) unlink($fullpath);
	
	$fullpath = "./img/$cod_area/testata.jpg";
	if (file_exists($fullpath)) unlink($fullpath);
	
	
	$fullpath = "./img/$cod_area/testata".$est;
	
	copy($file_testata,$fullpath);	
	
};

if ($file_sfondo and !$img_sfondo_default) {
	
	
	$size=getimagesize($file_sfondo);
	$width=$size[0];
	$height=$size[1];
	$type=$size[2];
	$errore="";

	if ($type<>1 and $type<>2) {
		$errore.="<br>$stringa[errore_immagine_gif_sfondo]";
	};
/*
	if ($width<>800) {
		$errore.="<br>$stringa[errore_sfondo_800]";
	};

	if ($height<>78) {
		$errore.="<br>$stringa[errore_sfondo_78]";
	};
*/	
	if ($errore) {
		$msg=ereg_replace(" ","%20",$errore);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
	};
	
	if ($type==1) $est=".gif";
	if ($type==2) $est=".jpg";
	
	$fullpath = "./img/$cod_area/up-bg.gif";
	if (file_exists($fullpath)) unlink($fullpath);
	
	$fullpath = "./img/$cod_area/up-bg.jpg";
	if (file_exists($fullpath)) unlink($fullpath);
	
	
	$fullpath = "./img/$cod_area/up-bg".$est;
	
	copy($file_sfondo,$fullpath);		
};

if ($img_testata_default) {
	$fullpath = "./img/$cod_area/testata.gif";
	copy("./img/kairos_demo/testata.gif",$fullpath);		
};

if ($img_sfondo_default) {
	$fullpath = "./img/$cod_area/up-bg.gif";
	copy("./img/kairos_demo/up-bg.gif",$fullpath);		
};

Header("Location:index.php");
?>







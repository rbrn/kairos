<?php
require "./init_sito.inc";
$cod_area=$kairos_cookie[4];
$titolo=$_REQUEST["titolo"];
$nome=$_REQUEST["nome"];
$cartella=$_REQUEST["cartella"];

$dir_path=$PATH_ROOT_FILE.$cartella;
$nome=trim($nome);

$nome_file=$dir_path."/".$nome.".htm";

$contenuto="/var/www/html/prototipo/kairos/".$cod_area."_".$id_corso_s."_laboratorio.txt";
if (file_exists($contenuto)) {
	$testo_array=file($contenuto);
	$testo=join('',$testo_array);
} else {
	$testo="";
};

$fd=fopen($nome_file,"w");
$pagina="
<HTML>
<HEAD>
<TITLE>$titolo</TITLE>
</HEAD>
<BODY>
$testo
</BODY>
</HTML>";
fwrite($fd,$pagina);
fclose($fd);
setcookie("kairos_cookie[5]",$cartella,0,"/",$dominio);
setcookie("kairos_cookie[6]",$nome,0,"/",$dominio);
setcookie("kairos_cookie[7]",$titolo,0,"/",$dominio);
?>
<html>
<head>
	<title><?php echo($stringa[editor]);?></title>
	<link rel="stylesheet" href="../stili/stile_sito.css">
</head>

<body bgcolor=white>
<span class=testo><?php echo($stringa[pagina_salvata]);?>:<br>
<?php
$url=$PATH_ROOT.$cartella."/".$nome.".htm";
echo "<a href=$url target=_blank>$url</a>";
?>
</span>
<p align=center>
<span class=testo>[<a href="../atlante_editor.php"><?php echo($stringa[indietro]);?></a>]</span>
</p>
</body>
</html>

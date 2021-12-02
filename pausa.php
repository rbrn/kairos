<?php
require "./include/init_sito.inc";
?>
<html>
<head>
<title>Pausa...</title>
<?php
echo "
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>
</head>

<body bgcolor=<?php echo($colore_sfondo);?>>
<table border=0 width=100% ALIGN=CENTER>
<tr>
<td width=5>&nbsp;</td>
<td bgcolor=white>
<!-- CONTENUTO DELLA PAGINA -->
<TABLE BORDER=0 ALIGN=CENTER width=100%>
<tr>
<td align=center>
<?php

//vedo se ci sono immagini...

$dir_path=$PATH_ROOT_FILE."materiali_img/$cod_area/dolci";
$d = dir($dir_path);
$i=0;

while ($nomefile=$d->read()) {
	if (($nomefile != '.') && ($nomefile != '..')) { 
		$file_img[$i] = strtolower($nomefile);
		$i++;
	};
}
$d->close();

if (count($file_img)) {
	srand((float)microtime() * 1000000);
	shuffle($file_img);
	$immagine="materiali_img/$cod_area/dolci/".$file_img[0];
	$size=getimagesize($immagine);
	$tag_img=$size[3];
	echo "<img src=\"$immagine\" $tag_img border=0 alt=\"PAUSA!\">";
};
?>
</td>
</tr>
</table>	
<!-- FINE CONTENUTO DELLA PAGINA -->
</td>
</tr>
</table>
</body>
</html>

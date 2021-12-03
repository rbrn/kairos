<?php
require "./include/init_sito.inc";
?>
<html>
<head>
<title><?php echo($stringa[elenco_img]);?></title>
<?php
echo "
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>

<script language=javascript>

function inserisci(nome_img) {
	
	var url='<?php echo($PATH_ROOT);?>/immagini/<?php echo($cod_area);?>/'+nome_img;
<?php if ($cod_area=="kairos_area_prove") { ?>
	opener.modulo.f_url.value=url;
<?php } else { ?>
	opener.modulo.immagine.value=url;
<?php }; ?>
	window.close();
	return false;
};



function copia_indirizzo(nome_img) {

	var url='<?php echo($PATH_ROOT);?>/immagini/<?php echo($cod_area);?>/'+nome_img;

	window.clipboardData.setData("Text",url);

	window.close();

};

</script>

</head>



<body bgcolor=<?php echo($colore_sfondo);?>>

<table border=0 width=100%>



<tr>

<td width=5>&nbsp;</td>

<td bgcolor=white>

<!-- CONTENUTO DELLA PAGINA -->



<TABLE BORDER=0 ALIGN=CENTER width=90%>

<tr>

<td>



<?php



//vedo se ci sono immagini...

$dir_path=$PATH_ROOT_FILE."immagini/$cod_area";

$d = dir($dir_path);

$i=0;

while ($nomefile=$d->read()) {

	if (($nomefile != '.') && ($nomefile != '..')) { 

		$file_img[$i] = strtolower($nomefile);

		$i++;

	};

}

$d->close();



echo "

<p>

<span class=sottotitolopagina>

$stringa[elenco_img]

</span>

</p>



<form action=add_immagini_op.php encType=multipart/form-data method=post>

<INPUT name=MAX_FILE_SIZE type=hidden value=100000>

<TABLE BORDER=0 cellspacing=0 cellpadding=3 bgcolor=#ffffcc>

<TR>

<TD align=right><span class=testo>$stringa[immagine_profilo]:</span></TD>

<TD><INPUT name=nome_file type=file></TD>

</TR>

</table>		

<input type=submit value=\"$stringa[carica]\">

</form>

";



if (count($file_img)) {
	sort($file_img);
	while (list($key, $val) = each($file_img)) {
		if (ereg("^(.+)\.(.+)$",$val,$parte)) {
		echo "<span class=testo><a href=\"immagini/$cod_area/$val\" target=_blank><img src=\"immagini/$cod_area/$val\" width=70 height=70 border=0 alt=\"$val\"></a> $val [<a href=\"javascript:;\" onclick=\"inserisci('$val');\">$stringa[inserisci]</a>] [<a href=\"javascript:;\" onclick=\"copia_indirizzo('$val');\">$stringa[copia]</a>] 

</span><br>";
		};
	};
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

<?php
header("Cache-Control: no-cache");
header("Pragma: no-cache");
?><?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$ruolo=ruolo_utente($kairos_cookie[0]);
?><html>
<head>
<title><?php echo($stringa[elenco_immagini_chat]);?></title>
<?php
echo "
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>
<SCRIPT TYPE="text/javascript" LANGUAGE="javascript1.1">
function Write_Input(img)
{
	window.focus();
	if (window.opener && !window.opener.closed) window.opener.document.Form.riga_chat.value += '*'+img+'*';
}
</SCRIPT>
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
$dir_path=$PATH_ROOT_FILE."images/".$cod_area;
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
$stringa[elenco_immagini_chat]
</span>
</p>
<p>
<span class=testo>
$stringa[elenco_immagini_chat_guida]
</span>
</p>
<p><span class=testo><b>$stringa[carica_nuova_immagine]:</b></span></p>
<form action=add_img_op.php encType=multipart/form-data method=post>
<INPUT name=MAX_FILE_SIZE type=hidden value=100000>
<TABLE BORDER=0 cellspacing=0 cellpadding=3 bgcolor=#ffffcc>
<TR>
<TD align=right><span class=testo>$stringa[immagine_profilo]:</span></TD>
<TD><INPUT name=nome_file type=file></TD>
</TR>
</table>		
<input type=submit value=\"$stringa[carica]\">
</form>
<br>
<!--
<p><span class=testo><b>Elenco immagini disponibili:</span></b></p>
-->";

if (count($file_img)) {
	sort($file_img);
	while (list($key, $val) = each($file_img)) {
		if (ereg("^(.+)\.(.+)$",$val,$parte)) {
		echo "<span class=testo><a href=\"images/$cod_area/$val\" alt=\"$stringa[clicca_vederla]\" target=_blank><img src=\"images/$cod_area/$val\" width=70 height=70 border=0></a> [<a href=\"javascript:;\" onClick=\"Write_Input('$parte[1]')\">$stringa[inserisci]</a>]</span>";
			if ($ruolo=="staff" or $ruolo=="admin") {
				$file="images/$cod_area/$val";
				echo "<span class=testo>[<a href=cancella.php?file=$file&ritorno=img.php>Cancella</a>]</span>";
			};
		echo "<br>";
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

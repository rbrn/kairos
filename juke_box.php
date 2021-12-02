<?php
header("Cache-Control: no-cache");
header("Pragma: no-cache");
?><?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$ruolo=ruolo_utente($kairos_cookie[0]);
?><html>
<head>
<title>Juke Box</title>
<?php
echo "
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>
<SCRIPT TYPE="text/javascript" LANGUAGE="javascript1.1">
function Write_Input(brano)
{
	window.focus();
	if (window.opener && !window.opener.closed) window.opener.document.Form.riga_chat.value += 'suona '+brano;
	self.close();
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
$dir_path=$PATH_ROOT_FILE."juke_box";
$d = dir($dir_path);
$i=0;
while ($nomefile=$d->read()) {
	if (($nomefile != '.') && ($nomefile != '..')) { 
		$brano[$i] = strtolower($nomefile);
		$i++;
	};
}
$d->close();

echo "
<p>
<span class=sottotitolopagina>
Brani in Playlist
</span>
</p>
";

if (count($brano)) {
	sort($brano);
	while (list($key, $val) = each($brano)) {
		if (ereg("^(.+)\.(.+)$",$val,$parte)) {
		echo "<span class=testo><a href=\"javascript:;\" onClick=\"Write_Input('$parte[1]')\">$parte[1]</a></span>";
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

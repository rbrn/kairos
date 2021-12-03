<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% colspan=3 class=titolodot>".strtoupper($stringa[info])."</td>";

echo "</tr>";


echo "<tr><td valign=top width=57%>";


if ($id_corso_s) {
	echo "
	<p>
	<span class=sottotitolopagina>$descrizione_corso</span></p>
	<p>";
	
	echo "
	<p>
	<a href=\"index.php?risorsa=staff\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_staff','','img/ico_staff_over.gif',1)\"><img src=\"img/ico_staff.gif\" width=\"20\" height=\"20\" alt=\"$stringa[staff]\" border=\"0\" name=\"img_staff\" align=\"middle\"></a>&nbsp;<span class=testo><a href=\"index.php?risorsa=staff\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_staff','','img/ico_staff_over.gif',1)\">".strtoupper($stringa[staff])."</a></span>
	</p>";
	
	$query="SELECT testo FROM corso WHERE id_corso='$id_corso_s'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$dettagli_corso=$riga["testo"];
	if ($dettagli_corso) {
	echo "
	<p>
	<table border=0 width=100% cellpadding=10 bgcolor=\"$colore_sfondo_neutro\">
	<tr><td>
	<span class=testo>$dettagli_corso</span>
	</td></tr>
	</table>
	</p>";
	};
};

echo "</td>";
	
echo "
<!--
<p>
<span class=sottotitolopagina>Manuale di Kairos:</span>
<span class=testo><a href=guida/kairos_manuale.zip>versione stampabile .zip/pdf</a> (1.5MB)</span>
</p>
-->";
echo "<td valign=top width=3%>&nbsp;</td>";
echo "<td valign=top width=40%>";

echo "
<span class=sottotitolopagina>$stringa[faq]</span>
";
if ($ruolo=='admin' or $ruolo=='staff') {
	echo "<br>
	<a href=\"index.php?risorsa=faq_new&op=nuovo&pagina=info\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('Image26','','img/ico_news_nuova_over.gif',1)\"><img name=\"Image26\" border=\"0\" src=\"img/ico_news_nuova.gif\" width=\"20\" height=\"20\" align=\"absmiddle\" alt=\"$stringa[nuova_faq]\"></a> <a href=\"index.php?risorsa=faq_new&op=nuovo&pagina=info\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('Image26','','img/ico_news_nuova_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[nuova_faq])."</span></a>
<hr size=1>";
};

$query = "SELECT * FROM faq WHERE id_corso='' ORDER BY ordine";
$result=$mysqli->query($query);

echo "<ul>";
while ($faq = $result->fetch_array()) {
	$domanda=str_replace("\n","<br>",$faq["domanda"]);
	$id_faq = $faq["id_faq"];

	echo "
	<li><span class=testo>$domanda</a><br>
	<a href=\"javascript:;\" onclick=\"faq_view('$id_faq')\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_risp_$id_faq','','img/icofaq_risposta_over.gif',1)\"><img src=\"img/icofaq_risposta.gif\" width=\"20\" height=\"20\" alt=\"$stringa[risposta_f]\" border=\"0\" name=\"img_risp_$id_faq\" vspace=\"5\"></a>&nbsp;";
	if ($ruolo=='staff' or $ruolo=='admin') {
		echo "
		<a href=index.php?risorsa=faq_edit&id_faq=$id_faq&pagina=info onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_faq','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_faq\" vspace=\"5\"></a>&nbsp;<a href=index.php?risorsa=msg&msg=conf_canc&pagina=faq_cancella.php&id_faq=$id_faq&pagina_r=info onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_faq','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_faq\" vspace=\"5\"></a>
		";
	};
	echo "<br>";
	echo "</span></li><br>";
};
echo "</ul>";

if ($cod_area=='kairos_larimart') {
echo "
<p>
<span class=testo>
$stringa[chiama_helpdesk]
</span>
</p>";
};
echo "
<br>";
?>
</td></tr></table>
<br>




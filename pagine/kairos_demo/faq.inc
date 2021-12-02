<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td class=titolodot>
$stringa[faq_corso]
</td></tr>";

echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "<tr><td>
";
if ($ruolo=='admin' or $ruolo=='staff') {
	echo "<a href=\"index.php?risorsa=faq_new&op=nuovo\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('Image26','','img/ico_news_nuova_over.gif',1)\"><img name=\"Image26\" border=\"0\" src=\"img/ico_news_nuova.gif\" width=\"20\" height=\"20\" align=\"absmiddle\" alt=\"$stringa[nuova_faq]\"></a> <a href=\"index.php?risorsa=faq_new&op=nuovo\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('Image26','','img/ico_news_nuova_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[nuova_faq])."</span></a> 
<hr size=1>";
};

$query = "SELECT * FROM faq WHERE id_corso='$id_corso_s' ORDER BY ordine";
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
		<a href=index.php?risorsa=faq_edit&id_faq=$id_faq onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_faq','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_faq\" vspace=\"5\"></a>&nbsp;<a href=index.php?risorsa=msg&msg=conf_canc&pagina=faq_cancella.php&id_faq=$id_faq onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_faq','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_faq\" vspace=\"5\"></a>
		";
	};
	echo "<br>";
	echo "</span></li><br>";
};
echo "</ul>";
?>
</td></tr>
</table>
<br>




<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[catalogo_corsi])."</td></tr>
<tr><td>";


echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";


echo "<tr><td>";


$id_corso=$_REQUEST[id_corso];
$query="SELECT * FROM corso WHERE id_corso='$id_corso'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$titolo=$riga[descrizione];
$dettagli_corso=$riga["testo"];
	

echo "
<p>
<span class=sottotitolopagina>$titolo</span>
</p>
";
	
	
if ($dettagli_corso) {
	echo "
	<p>
	<table border=0 width=70% cellpadding=10 bgcolor=\"$colore_sfondo_neutro\">
	<tr><td>
	<span class=testo>$dettagli_corso</span>
	</td></tr>
	</table>
	</p>";
};



$query="SELECT id_edizione FROM edizioni WHERE 
id_corso='$id_corso' and autoiscrizione='on' ORDER BY id_edizione DESC";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

if ($riga and $cod_area<>"kairos_area_corsi" and $cod_area<>"kairos_master" and $cod_area<>"kairos_masterunitus") {
echo "
<p>
<a href=\"catalogo_corsi_iscrizione.php?id_corso=$id_corso\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_iscriviti','','img/ico_iscrivicorso_over.gif',1)\"><img src=\"img/ico_iscrivicorso.gif\" width=\"20\" height=\"20\" alt=\"$stringa[iscriviti]\" border=\"0\" name=\"img_iscriviti\" align=\"middle\"></a>&nbsp;<span class=testo><a href=\"catalogo_corsi_iscrizione.php?id_corso=$id_corso\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_iscriviti','','img/ico_iscrivicorso_over.gif',1)\">".strtoupper($stringa[iscriviti])."</a></span>
</p>
";
};

/*

if ($riga and ($cod_area=="kairos_area_corsi" or $cod_area=="kairos_master" or $cod_area=="kairos_masterunitus")) {
echo "
<p>
<a href=\"http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com/index.php?risorsa=acquisto&cod_prodotto=$id_corso\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_iscriviti','','img/ico_iscrivicorso_over.gif',1)\"><img src=\"img/ico_iscrivicorso.gif\" width=\"20\" height=\"20\" alt=\"$stringa[iscriviti]\" border=\"0\" name=\"img_iscriviti\" align=\"middle\"></a>&nbsp;<span class=testo><a href=\"http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com/index.php?risorsa=acquisto&cod_prodotto=$id_corso\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_iscriviti','','img/ico_iscrivicorso_over.gif',1)\">".strtoupper($stringa[iscriviti])."</a></span>

</p>
";
};
*/	

echo "</td></tr></table>
<br>";

?>




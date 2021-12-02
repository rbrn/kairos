<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[editor_gruppi])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=materiali_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=materiali_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

echo "
<a href=\"index.php?risorsa=editor_nuovogruppo_form\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovogruppo','','img/ico_grupponuovo_over.gif',1)\"><img border=\"0\" src=\"img/ico_grupponuovo.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[nuovo_gruppo]\" name=\"img_nuovogruppo\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=editor_nuovogruppo_form\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovogruppo','','img/ico_grupponuovo_over.gif',1)\">".strtoupper($stringa[nuovo_gruppo])."</a></span>
<br><br>
\n";


echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

echo "
<tr bgcolor=\"$colore_scuro\">
<td><span class=testonegativo><b>$stringa[gruppo]</b></span></td>
<td><span class=testonegativo><b>$stringa[iscritti]</b></span></td>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>
\n";

$query="SELECT * FROM editor_gruppo ORDER BY id_editor_gruppo";
$result=$mysqli->query($query);
$colore=$colore_sfondo;

while ($riga=$result->fetch_array()) {
	$id_editor_gruppo=$riga["id_editor_gruppo"];
	$descrizione = $riga["descrizione"];
	
	$query_c="SELECT * FROM editor_gruppo_utenti WHERE id_editor_gruppo='$id_editor_gruppo'";
	$result_c=$mysqli->query($query_c);
	$num_iscr=$result_c->num_rows;
		
	echo "<tr bgcolor=\"$colore\">\n";

	echo "<td valign=top>
	<span class=testo>$descrizione</span><br>
	</td>";
		
	
	echo "<td align=right><span class=testo>$num_iscr</></td>";

	echo "<td align=right>
	<a href=\"index.php?risorsa=editor_iscrizioni_gruppo&id_editor_gruppo=$id_editor_gruppo\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_editor_gruppo','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_$id_editor_gruppo\" align=\"middle\"></a></td>";
	
	echo "<td><a href=\"index.php?risorsa=editor_gruppo_modifica&id_editor_gruppo=$id_editor_gruppo\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_editor_gruppo','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[edit]\" border=\"0\" name=\"img_mod_$id_editor_gruppo\"></a></td>";
	
	$query_c="SELECT id_risorsa FROM risorse_materiali WHERE id_editor_gruppo='$id_editor_gruppo'";
	$result_c=$mysqli->query($query_c);
	if (!$result_c->num_rows) { 
		echo "<td><a href=\"index.php?risorsa=msg&msg=conf_canc&pagina=editor_gruppo_cancella.php&id_editor_gruppo=$id_editor_gruppo\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_editor_gruppo','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_editor_gruppo\"></a></td>";
	} else {
		echo "<td>&nbsp;</td>";
	};
		
	echo "</tr>";
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
	
}
echo "</table>";
echo "</td></tr></table>";

echo "</td></tr></table><br>";
?>

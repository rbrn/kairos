<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];

$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione;


$query="SELECT * FROM corso WHERE id_corso='$id_corso'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$descrizione_corso=$riga["descrizione"];

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_index><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso&id_edizione=$id_edizione><span class=testo><b>$stringa[corso]:</b> $descrizione_corso: $descr_edizione</span></a>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_gruppi])."</b></span>
</td></tr>



<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso&id_edizione=$id_edizione\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso&id_edizione=$id_edizione\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

echo "
<a href=\"index.php?risorsa=corsi_nuovogruppo_form&id_corso=$id_corso&id_edizione=$id_edizione\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovogruppo','','img/ico_grupponuovo_over.gif',1)\"><img border=\"0\" src=\"img/ico_grupponuovo.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[nuovo_gruppo]\" name=\"img_nuovogruppo\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=corsi_nuovogruppo_form&id_corso=$id_corso&id_edizione=$id_edizione\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovogruppo','','img/ico_grupponuovo_over.gif',1)\">".strtoupper($stringa[nuovo_gruppo])."</a></span>
<br>
<br>
\n";



echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

echo "
<tr bgcolor=\"$colore_scuro\">
<td><span class=testonegativo><b>$stringa[gruppo]</b></span></td>
<td><span class=testonegativo><b>$stringa[tipo]</b></span></td>
<td><span class=testonegativo><b>$stringa[tutor]</b></span></td>
<td><span class=testonegativo><b>$stringa[iscritti]</b></span></td>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>
\n";

$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' ORDER BY id_gruppo";
$result=$mysqli->query($query);
$colore=$colore_sfondo;

while ($riga=$result->fetch_array()) {
	$id_gruppo=$riga["id_gruppo"];
	$descrizione = $riga["descrizione"];
	$id_tutor = $riga["id_tutor"];
	$tipo_gruppo=$riga["tipo_gruppo"];
	$indice="gruppo_".$tipo_gruppo;
	$str_tipo_gruppo=$stringa[$indice];
	
	if ($tipo_gruppo==0) {
		$query_c="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_gruppo='$id_gruppo'";
	} else {
		$query_c="SELECT * FROM iscrizioni_gruppo_pw WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_gruppo='$id_gruppo'";
	};
	
	$result_c=$mysqli->query($query_c);
	$num_iscr=$result_c->num_rows;
		
	echo "<tr bgcolor=\"$colore\">\n";

	echo "<td valign=top>
	<span class=testo><i>($id_gruppo)</i> $descrizione</span><br>
	</td>";
	
	echo "<td valign=top>
	<span class=testo>$str_tipo_gruppo</span><br>
	</td>";
	
	if ($id_tutor) {
		echo "<td valign=top>
		<span class=testo>
		<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_tutor',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_tutor</a>
		</span></td>";
	} else {
		echo "<td valign=top>&nbsp;</td>";
	};
		
	
	echo "<td align=right><span class=testo>$num_iscr</span></td>";
		$pw="";
		if ($tipo_gruppo==1) $pw="_pw";
		
		echo "<td>
		<a href=\"index.php?risorsa=corsi_iscrizioni_gruppo".$pw."&id_corso=$id_corso&id_edizione=$id_edizione&id_gruppo=$id_gruppo\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_edizione_$id_gruppo','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_$id_edizione_$id_gruppo\" align=\"middle\"></a></td>";	

		echo "<td><a href=\"index.php?risorsa=corsi_gruppo_modifica&id_corso=$id_corso&id_edizione=$id_edizione&id_gruppo=$id_gruppo\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_gruppo','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[edit]\" border=\"0\" name=\"img_mod_$id_gruppo\"></a></td>";	

		echo "<td><a href=\"index.php?risorsa=msg&msg=conf_canc&pagina=corsi_gruppo_cancella.php&id_corso=$id_corso&id_edizione=$id_edizione&id_gruppo=$id_gruppo\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_gruppo','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_gruppo\"></a></td>";	


	echo "</tr>";
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
}

echo "</table>\n";

echo "</td></tr></table>";
echo "</td></tr></table><br>";
?>

<?php
echo "                </div>
</div>
</div>
</div>
</div>";
?>

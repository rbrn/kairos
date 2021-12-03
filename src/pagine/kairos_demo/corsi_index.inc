<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=admin_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=admin_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

if ($ruolo=="admin") {
	echo "
	<a href=\"index.php?risorsa=corsi_nuovo_form\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_corsonuovo','','img/ico_corsonuovo_over.gif',1)\"><img border=\"0\" src=\"img/ico_corsonuovo.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[nuovo_corso]\" name=\"img_corsonuovo\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=corsi_nuovo_form\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_corsonuovo','','img/ico_corsonuovo_over.gif',1)\">".strtoupper($stringa[nuovo_corso])."</a></span>";
};

echo "<br><br>";

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";


echo "
<tr bgcolor=\"$colore_scuro\">
<td><span class=testonegativo><b>$stringa[corso]</b></span></td>
<td><b><span class=testonegativo>$stringa[iscritti]</span></b></td>
<td><b><span class=testonegativo>$stringa[edizioni]</span></b></td>
<td>&nbsp;</td>";

if ($ruolo=="admin") {
echo "
<td>&nbsp;</td>
<td>&nbsp;</td>";
};

echo "</tr>
\n";

$id_utente=$kairos_cookie[0];
if ($ruolo=="admin") {
	$query="SELECT * FROM corso ORDER BY id_corso";
	$result=$mysqli->query($query);
} else {
	$query="SELECT DISTINCT corso.id_corso,corso.descrizione FROM gruppo_utenti,corso WHERE corso.id_corso=gruppo_utenti.id_corso AND gruppo_utenti.id_tutor='$id_utente'";
	$result=$mysqli->query($query);
	if (!$result->num_rows) {
		$query="SELECT DISTINCT corso.id_corso,corso.descrizione FROM ruolo_utenti,corso WHERE corso.id_corso=ruolo_utenti.id_corso AND ruolo_utenti.id_utente='$id_utente'";
		$result=$mysqli->query($query);
	};
};



$colore=$colore_sfondo;

while ($riga=$result->fetch_array()) {
	$id_corso = $riga["id_corso"];
	$descrizione = $riga["descrizione"];
	
	echo "<tr bgcolor=\"$colore\">\n";

	echo "<td valign=top>
	<span class=testo><i>($id_corso)</i> $descrizione</span><br>
	</td>";

	$query_t = "SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso'";
	$result_t=$mysqli->query($query_t);
	$num_iscr=$result_t->num_rows;
	
	$query_t = "SELECT * FROM edizioni WHERE id_corso='$id_corso'";
	$result_t=$mysqli->query($query_t);
	$num_ed=$result_t->num_rows;
	
	echo "<td valign=top align=right>
	<span class=testo>$num_iscr</span><br>
	</td>";
	
	echo "<td valign=top align=right>
	<span class=testo>$num_ed</span><br>
	</td>";
	
	echo "<td valign=top>
	<a href=\"index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_corso','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_$id_corso\" align=\"middle\"></a></td>";
	
	if ($ruolo=="admin") {
	
		echo "<td><a href=\"index.php?risorsa=corsi_mod_form&id_corso=$id_corso\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_corso','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[edit]\" border=\"0\" name=\"img_mod_$id_corso\"></a></td>";

		echo "<td><a href=\"index.php?risorsa=msg&msg=conf_canc&pagina=corsi_elimina.php&id_corso=$id_corso\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_corso','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_corso\"></a></td>";
	}; 
	
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

echo "                </div>
            </div>
        </div>
    </div>
</div>";
?>

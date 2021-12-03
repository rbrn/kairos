<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[catalogo_corsi])."</td></tr>
<tr><td>";

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=0 cellspacing=0 bgcolor=\"white\" >
<tr><td>";

echo "
<table border=0 cellpadding=5 cellspacing=1>
<tr>
<td bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[corso]</b></span></td>
<td bgcolor=\"$colore_scuro\"><b><span class=testonegativo>$stringa[iscritti]</span></b></td>
<td bgcolor=\"$colore_scuro\"><b><span class=testonegativo>$stringa[edizioni]</span></b></td>
<td bgcolor=\"$colore_scuro\">&nbsp;</td>
";

echo "</tr>
\n";

$id_utente=$kairos_cookie[0];

$query="SELECT * FROM corso ORDER BY id_corso";


$result=$mysqli->query($query);

$colore=$colore_sfondo;

while ($riga=$result->fetch_array()) {
	$id_corso = $riga["id_corso"];
	$descrizione = $riga["descrizione"];
	
	if (strtolower($id_corso)<>"staff") {
	
	echo "<tr bgcolor=\"$colore\">\n";

	echo "<td valign=top>
	<span class=testo>$descrizione</span><br>
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
	<a href=\"index.php?risorsa=catalogo_view&id_corso=$id_corso\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_corso','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_$id_corso\" align=\"middle\"></a></td>";

	echo "</tr>";
	
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
	};
}

echo "</table>";

echo "</td></tr></table>"; 
echo "</td></tr></table>"; 

echo "</td></tr></table><br>";
?>

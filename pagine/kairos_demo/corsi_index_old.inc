<?php
echo "<p><span class=titolopagina>$stringa[gestione_corsi]</span></p>
<hr size=1>
<br>
<span class=testo>[<a href=index.php?risorsa=corsi_nuovo_form>$stringa[nuovo_corso]</a>]</span> | <span class=testo>[<a href=index.php?risorsa=corsi_gestione_iscrizioni_form>Gestione iscrizioni</a>]</span> | <span class=testo>[<a href=index.php?risorsa=admin_index>$stringa[admin]</a>]</span>
<br>
<hr size=1>
<br>
\n";



echo "
<table border=1>
<tr>
<td><span class=testo><b>$stringa[corso]</b></span></td>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>
\n";

$query="SELECT * FROM corso ORDER BY id_corso";
$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {
	$id_corso = $riga["id_corso"];
	$descrizione = $riga["descrizione"];
	
	echo "<tr>\n";

	echo "<td valign=top>
	<span class=testo><i>($id_corso)</i> $descrizione</span><br>
	</td>";

	$query_t = "SELECT * FROM edizioni WHERE id_corso='$id_corso' ORDER BY id_edizione DESC";
	$result_t=$mysqli->query($query_t);
	
	echo "<td valign=top>
	<table border=1 width=100%>
	<tr>
	<td><b><span class=testo>$stringa[edizione]</span></b></td>
	<td><b><span class=testo>$stringa[status]</span></b></td>
	<td><b><span class=testo>$stringa[iscritti]</span></b></td>
	<td>&nbsp;</td>
	<td>&nbsp;</td>
	<td>&nbsp;</td>
	</tr>
	";
	while ($riga_t=$result_t->fetch_array()) {
		$id_edizioni=$riga_t["id_edizioni"];
		$id_edizione=$riga_t["id_edizione"];
		$stato=$riga_t["stato"];
		$query_c="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
		$result_c=$mysqli->query($query_c);
		$num_iscr=$result_c->num_rows;
		
		echo "<tr>";
		echo "<td><span class=testo>$id_edizione</span></td>";
		echo "<td><span class=testo>$stringa[$stato]</span></td>";
		echo "<td align=right><span class=testo><a href=index.php?risorsa=corsi_iscrizioni&id_corso=$id_corso&id_edizione=$id_edizione>$num_iscr</></td>";

		echo "<td><a href=corsi_esporta_iscritti.php?id_corso=$id_corso&id_edizione=$id_edizione><span class=testo>$stringa[esporta_iscritti]</span></a></td>";	

		echo "<td><a href=index.php?risorsa=corsi_edizione_modifica&id_edizioni=$id_edizioni><span class=testo>$stringa[modifica]</span></a></td>";	

		echo "<td><a href=index.php?risorsa=msg&msg=conf_canc&pagina=corsi_edizione_cancella.php&id_edizioni=$id_edizioni><span class=testo>$stringa[cancella]</span></a></td>";	
	
		echo "</tr>";
	};
	echo "</table></td>";
	
	echo "<td valign=top><span class=testo>[<a href=index.php?risorsa=corsi_edizione_nuova_form&id_corso=$id_corso>$stringa[nuova_edizione]</a>]</span></td>";

	echo "<td valign=top><span class=testo>[<a href=index.php?risorsa=corsi_mod_form&id_corso=$id_corso>$stringa[modifica]</a>]</span></td>";

	echo "<td valign=top>
	<span class=testo>[<a href=index.php?risorsa=msg&msg=conf_canc&pagina=corsi_elimina.php&id_corso=$id_corso>$stringa[cancella]</a>]</span>
	</td>";
	
	echo "</tr>";

}

echo "</table><br><br>\n";
  

?>

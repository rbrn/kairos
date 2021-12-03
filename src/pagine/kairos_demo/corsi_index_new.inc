<?php
echo "<p><span class=titolopagina>$stringa[gestione_corsi]</span></p>
<hr size=1>
<br>
<span class=testo>[<a href=index.php?risorsa=admin_index>$stringa[admin]</a>]</span>
<span class=testo>[<a href=index.php?risorsa=corsi_nuovo_form>$stringa[nuovo_corso]</a>]</span> 
<br>
<hr size=1>
<br>
\n";


echo "
<table border=1>
<tr>
<td><span class=testo><b>$stringa[corso]</b></span></td>
<td><b><span class=testo>$stringa[iscritti]</span></b></td>
<td><b><span class=testo>$stringa[edizioni]</span></b></td>
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
} else {
	$query="SELECT DISTINCT corso.id_corso,corso.descrizione FROM gruppo_utenti,corso WHERE corso.id_corso=gruppo_utenti.id_corso AND gruppo_utenti.id_tutor='$id_utente'";
};

$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {
	$id_corso = $riga["id_corso"];
	$descrizione = $riga["descrizione"];
	
	echo "<tr>\n";

	echo "<td valign=top>
	<span class=testo><i>($id_corso)</i> $descrizione</span><br>
	</td>";

	$query_t = "SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso'";
	$result_t=$mysqli->query($query_t);
	$num_iscr=$result_t->num_rows;
	
	$query_t = "SELECT * FROM edizioni WHERE id_corso='$id_corso'";
	$result_t=$mysqli->query($query_t);
	$num_ed=$result_t->num_rows;
	
	echo "<td valign=top>
	<span class=testo>$num_iscr</span><br>
	</td>";
	
	echo "<td valign=top>
	<span class=testo>$num_ed</span><br>
	</td>";
	
	echo "<td valign=top><span class=testo>[<a href=index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso>$stringa[apri]</a>]</span></td>";
	
	if ($ruolo=="admin") {
		echo "<td valign=top><span class=testo>[<a href=index.php?risorsa=corsi_mod_form&id_corso=$id_corso>$stringa[modifica]</a>]</span></td>";

		echo "<td valign=top><span class=testo>[<a href=index.php?risorsa=msg&msg=conf_canc&pagina=corsi_elimina.php&id_corso=$id_corso>$stringa[cancella]</a>]</span>
	</td>";
	}; 
	
	echo "</tr>";

}

echo "</table><br><br>\n";
  

?>

<?php
$check="";
if ($altro=="on") $check="checked";
echo "
<form action=lo_test_item_modifica_campo.php method=post>

<input type=\"hidden\" name=\"id_item\" value=\"$id_item\">
<input type=\"hidden\" name=\"campo\" value=\"altro\">
<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">
<input type=\"checkbox\" name=\"altro\" $check> <span class=testopiccolo><b>$stringa[categorizzazione]</b>: </span>
<input type=\"submit\" value=\"Ok\">
</form>
";

echo "<table border=\"0\" cellpadding=\"10\">";
echo "<tr><td valign=\"top\">";

$query="SELECT id_item_opzione FROM lo_test_item_opzioni WHERE id_item='$id_item' AND tipo_opzione='2'";
$result=$mysqli->query($query);

if ($result->num_rows) {	
if ($ruolo=='admin' or $id_utente==$id_editor) {	
echo "<p><span class=testopiccolo><a href=\"index.php?risorsa=lo_test_item_opzione_match_add&lato=sx&id_item=$id_item&risorsa_padre=$risorsa_padre\"
>$stringa[nuovo_elemento]</a></span></p>";
};
};

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";


$query="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND tipo_opzione='1' ORDER BY posizione";
$result=$mysqli->query($query);

echo "<tr>
<td width=10 bgcolor=\"$colore_scuro\">&nbsp;</td>
<td width=400 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[voce_sx]</b></span></td>";

echo "
<td width=50 bgcolor=\"$colore_scuro\"></td>
<td width=50 bgcolor=\"$colore_scuro\"></td>
</tr>
\n";

$colore=$colore_sfondo;

while ($opzione = $result->fetch_array()) {
	$id_item_opzione=$opzione[id_item_opzione];
	$id_editor=$opzione[id_editor];
	$posizione=$opzione[posizione];
	$risposta_opzione=htmlentities($opzione[risposta_opzione]);
	$id_item_esatto=$opzione[id_item_esatto];
	$query2="SELECT posizione FROM lo_test_item_opzioni WHERE id_item_opzione='$id_item_esatto'";
	$result2=$mysqli->query($query2);
	$riga2=$result2->fetch_array();
	$pos2=$riga2[posizione];

	echo "<tr bgcolor=\"$colore\">";
	if ($ruolo=='admin' or $id_utente==$id_editor) {		
	echo "<td valign=top width=30 align=center><a href=lo_test_item_opzione_match_sposta.php?lato=sx&id_item_opzione=$id_item_opzione&id_item=$id_item&risorsa_padre=$risorsa_padre&azione=up><img src=img/up.gif width=11 height=7 border=0 alt=\"$stringa[pagina_up]\"></a><a href=lo_test_item_opzione_match_sposta.php?lato=sx&id_item_opzione=$id_item_opzione&id_item=$id_item&risorsa_padre=$risorsa_padre&azione=down><img src=img/down.gif width=11 height=7 border=0 alt=\"$stringa[pagina_down]\"></a></td>\n";
	} else {
		echo "<td valign=top width=30 align=center>&nbsp;</td>";
	};
	
	echo "<td valign=top><span class=testo>$posizione. $risposta_opzione ($pos2)</span></td>\n";
	
	if ($ruolo=='admin' or $id_utente==$id_editor) {
		echo "
		<td valign=middle align=center>
		<a href=index.php?risorsa=lo_test_item_opzione_match_mod&lato=sx&id_item_opzione=$id_item_opzione&id_item=$id_item&risorsa_padre=$risorsa_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_item','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[edit]\" border=\"0\" name=\"img_mod_$id_item\"></a></td>";
	} else {
		echo "<td>&nbsp;</td>";
	};
	
	if ($ruolo=='admin' or $id_utente==$id_editor) {
		echo "
		<td valign=middle align=center>
		<a href=index.php?risorsa=msg&msg=conf_canc&pagina=lo_test_item_opzione_match_elimina.php&lato=sx&id_item_opzione=$id_item_opzione&id_item=$id_item&risorsa_padre=$risorsa_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_item','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_item\"></a>
		</td>
		";
	} else {
		echo "<td>&nbsp;</td>";
	};
	
	
	echo "</tr>";
	
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
}; 
echo "</table>\n";

echo "		
</td></tr>
</table>";

echo "</td>";
echo "<td valign=\"top\">";
if ($ruolo=='admin' or $id_utente==$id_editor) {	
echo "<p><span class=testopiccolo><a href=\"index.php?risorsa=lo_test_item_opzione_match_add&lato=dx&id_item=$id_item&risorsa_padre=$risorsa_padre\"
>$stringa[nuovo_elemento]</a></span></p>";
};

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";


$query="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND tipo_opzione='2' ORDER BY posizione";
$result=$mysqli->query($query);

echo "<tr>
<td width=10 bgcolor=\"$colore_scuro\">&nbsp;</td>
<td width=400 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[voce_dx]</b></span></td>";

echo "
<td width=50 bgcolor=\"$colore_scuro\"></td>
<td width=50 bgcolor=\"$colore_scuro\"></td>
</tr>
\n";

$colore=$colore_sfondo;

while ($opzione = $result->fetch_array()) {
	$id_item_opzione=$opzione[id_item_opzione];
	$id_editor=$opzione[id_editor];
	$posizione=$opzione[posizione];
	$risposta_opzione=htmlentities($opzione[risposta_opzione]);

	echo "<tr bgcolor=\"$colore\">";
	if ($ruolo=='admin' or $id_utente==$id_editor) {		
	echo "<td valign=top width=30 align=center><a href=lo_test_item_opzione_match_sposta.php?lato=dx&id_item_opzione=$id_item_opzione&id_item=$id_item&risorsa_padre=$risorsa_padre&azione=up><img src=img/up.gif width=11 height=7 border=0 alt=\"$stringa[pagina_up]\"></a><a href=lo_test_item_opzione_match_sposta.php?lato=dx&id_item_opzione=$id_item_opzione&id_item=$id_item&risorsa_padre=$risorsa_padre&azione=down><img src=img/down.gif width=11 height=7 border=0 alt=\"$stringa[pagina_down]\"></a></td>\n";
	} else {
		echo "<td valign=top width=30 align=center>&nbsp;</td>";
	};
	
	echo "<td valign=top><span class=testo>$posizione. $risposta_opzione</span></td>\n";
	
	if ($ruolo=='admin' or $id_utente==$id_editor) {
		echo "
		<td valign=middle align=center>
		<a href=index.php?risorsa=lo_test_item_opzione_match_mod&lato=dx&id_item_opzione=$id_item_opzione&id_item=$id_item&risorsa_padre=$risorsa_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_item','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[edit]\" border=\"0\" name=\"img_mod_$id_item\"></a></td>";
	} else {
		echo "<td>&nbsp;</td>";
	};
	
	if ($ruolo=='admin' or $id_utente==$id_editor) {
		echo "
		<td valign=middle align=center>
		<a href=index.php?risorsa=msg&msg=conf_canc&pagina=lo_test_item_opzione_match_elimina.php&lato=dx&id_item_opzione=$id_item_opzione&id_item=$id_item&risorsa_padre=$risorsa_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_item','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_item\"></a>
		</td>
		";
	} else {
		echo "<td>&nbsp;</td>";
	};
	
	
	echo "</tr>";
	
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
}; 
echo "</table>\n";

echo "		
</td></tr>
</table>";

echo "</td></tr>
</table>";

?>

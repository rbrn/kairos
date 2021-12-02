<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=materiali_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=materiali_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";


echo "
<a href=index.php?risorsa=test_crea onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_test_nuovo','','img/ico_test_over.gif',1)\"><img src=\"img/ico_test.gif\" width=\"20\" height=\"20\" alt=\"$stringa[nuovo_test]\" border=\"0\" name=\"img_test_nuovo\" align=\"middle\"></a>
<span class=testo><a href=index.php?risorsa=test_crea onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_test_nuovo','','img/ico_test_over.gif',1)\">$stringa[nuovo_test]</a></span><br><br>";


$query = "SELECT * FROM test ORDER BY id_test";
$result=$mysqli->query($query);

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

echo "<tr>
<td width=10 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[tipo]</b></td>
<td width=400 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[titolo]</b></td>
<td width=10 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[num_comp]</b></td>
<td width=50 bgcolor=\"$colore_scuro\"></td>
<td width=50 bgcolor=\"$colore_scuro\"></td>
<td width=50 bgcolor=\"$colore_scuro\"></td>
<td width=50 bgcolor=\"$colore_scuro\"></td>
</tr>
\n";

$colore=$colore_sfondo;

while ($test = $result->fetch_array()) {
	echo "<tr bgcolor=\"$colore\">";
	$id_editor=$test[id_editor];
	
	
	
	if ($test["tipo_test"]) {
		$tipo_test=$stringa[sondaggio];
	} else {
		$tipo_test=$stringa[verifica];
	};	
	
	printf ("<td valign=top width=10><span class=testo>%s</span></td>\n",$tipo_test);

	if ($ruolo=='admin' or $id_utente==$id_editor) {
		printf ("<td valign=top><span class=testo>%s</span> <span class=testopiccolo>[<a href=index.php?risorsa=test_modifica&id_test=%s>".$stringa[modifica]."]</span></td>\n",$test["titolo"],$test["id_test"]);
	} else {
		printf ("<td valign=top><span class=testo>%s</span></td>\n",$test["titolo"]);
	};
	

	printf ("<td valign=top width=10><span class=testo>%s</span></td>\n",$test["tot_prog"]);

	printf("<td valign=top width=50><span class=testo><a href=index.php?risorsa=test_risultati&id_test=%s>%s</a</span></td>\n",$test["id_test"],$stringa[risultati]);
	$id_test=$test[id_test];
	if ($ruolo=='admin' or $id_utente==$id_editor) {
		echo "
		<td valign=middle align=center>
		<a href=index.php?risorsa=test_edit&id_test=$id_test onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_test','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[edit]\" border=\"0\" name=\"img_mod_$id_test\"></a></td>";
	} else {
		echo "<td>&nbsp;</td>";
	};
	
	if ($ruolo=='admin' or $id_utente==$id_editor) {
		echo "
		<td valign=middle align=center>
		<a href=index.php?risorsa=test_elimina_conferma&id_test=$id_test onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_test','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_test\"></a>
		</td>
		";
	} else {
		echo "<td>&nbsp;</td>";
	};
	
	echo "
		<td valign=middle align=center>
		<a href=index.php?risorsa=test_duplica&id_test=$test[id_test] onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_duplica_$id_test','','img/ico_duplicatest_over.gif',1)\"><img src=\"img/ico_duplicatest.gif\" width=\"20\" height=\"20\" alt=\"$stringa[duplica]\" border=\"0\" name=\"img_duplica_$id_test\"></a>
		</td>
		";

	echo "</tr>";
	
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
}; 
echo "</table>\n";

?>
		
</td></tr>
</table>

</td></tr></table>
<br>

<?php
$padre=$_REQUEST["padre"];

mysql_select_db($DBASE,$db);	




?>

<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_repository])."</td></tr>
";

echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>";

echo "<form action=index.php method=get name=modulo id=modulo>
  <input type=\"hidden\" name=\"risorsa\" value=\"lo_cerca_risultati\">
  <input type=\"hidden\" name=\"risorsa_padre\" value=\"$padre\">
  <input type=\"hidden\" name=\"contesto_cerca\" value=\"$contesto_cerca\">";
  
echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"450\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";

	echo "<tr>";
	echo "<td colspan=\"2\" bgcolor=\"$colore_scuro\"><span class=testonegativo><b>Ricerca LO</b></span></td></tr>";
	
	echo "<tr bgcolor=\"$colore_sfondo\">";
	echo "<TD align=right><span class=testo><STRONG>$stringa[titolo]:</STRONG></span></TD>";
	echo "<TD><INPUT type=\"text\"  name=\"titolo\" size=\"60\"></TD>";
	echo "</tr>";
	
	echo "<tr bgcolor=\"$colore_sfondo_neutro\">";
	echo "<TD align=right><span class=testo><STRONG>$stringa[autore]:</STRONG></span></TD>
        <TD><INPUT type=\"text\"  name=\"id_autore\" size=\"20\"  value=\"$id_utente\">";
	echo "&nbsp;<span class=\"testopiccolo\">
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup.php?ruolo=tutti&campo=id_autore','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup_op.php?ruolo=tutti&campo=id_autore','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["tutti"]."</a>]
</span></td>";
	echo "</tr>";

	$query="SELECT * FROM lo_schema WHERE id_lom='05.02' AND id_profile='lom_garamond' LIMIT 1";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$valuespace=$riga[valuespace];
	$opzioni="<option value=\"\">(qualunque)</option>";
	$lista=explode("\n",$valuespace);
	for ($i=0;$i<count($lista);$i++) {
		$opzioni.="<option value=\"$lista[$i]\">$lista[$i]</option>";
	};
	
	echo "<tr bgcolor=\"$colore_sfondo\">";
	echo "<TD align=right><span class=testo><STRONG>$stringa[lo_tipo_lom]:</STRONG></span></TD>
        <TD><select name=\"lo_tipo_lom\" size=\"1\">$opzioni</select></TD>";
	echo "</TR>";
	
	echo "<tr bgcolor=\"$colore_sfondo_neutro\">";
	echo "<TD align=right><span class=testo><STRONG>$stringa[materia]:</STRONG></span></TD>
        <TD><INPUT type=\"text\"  name=\"materia\" size=\"60\"></TD>";
	echo "</TR>";
	  	  

    echo "<tr bgcolor=\"$colore_sfondo\">";
    echo "<td colspan=\"2\" align=center><INPUT type=submit value=\"$stringa[cerca]\"></td>";
	echo "</tr>";
	echo "</table>";
	
	echo "</td></tr></table>";
  	echo "</FORM>";
  
?>  
  
</td></tr></table>
<br>

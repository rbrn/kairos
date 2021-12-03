<?php
$indietro="javascript:history.back();";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>Carica Ordine</td></tr>
";

echo "
<tr>
<td valign=top width=100%>
<a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>";

echo "<form action=index.php method=get name=modulo id=modulo>
  <input type=\"hidden\" name=\"risorsa\" value=\"lo_ordini_carica_seleziona_lo\">";
  
echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"450\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";

	echo "<tr>";
		
	echo "<tr bgcolor=\"$colore_sfondo\">";
	echo "<TD align=right><span class=testo><STRONG>Rif. Ordine:</STRONG></span></TD>";
	echo "<TD><input type=\"text\" name=\"rif_ordine\" size=\"50\"></TD>";
	echo "</tr>";

	echo "<tr bgcolor=\"$colore_sfondo\">";
	echo "<TD align=right><span class=testo><STRONG>Num. Codici da generare:</STRONG></span></TD>";
	echo "<TD><input type=\"text\" name=\"num_utenti\" size=\"10\"></TD>";
	echo "</tr>";

    echo "<tr bgcolor=\"$colore_sfondo\">";
    echo "<td colspan=\"2\" align=center><INPUT type=submit value=\"OK\"></td>";
	echo "</tr>";
	echo "</table>";
	
	echo "</td></tr></table>";
  	echo "</FORM>";
  
?>  
  
</td></tr></table>
<br>

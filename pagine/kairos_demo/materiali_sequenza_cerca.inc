<?php
$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];
$comuni=$_REQUEST["comuni"];

$indietro="index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso&id_edizione=$id_edizione";

if ($id_corso) {
	if ($ruolo=='admin') {
		$elenco_gruppi="<option value=\"\" selected>$stringa[qualunque]</option>";
		$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' ORDER BY id_gruppo";
	} else {
		$elenco_gruppi="<option value=\"\" selected>$stringa[qualunque]</option>";
		$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_tutor='$id_utente' ORDER BY id_gruppo";
	};
	
	$result=$mysqli->query($query);
	

	while ($riga=$result->fetch_array()) {
		$id_gruppo=$riga["id_gruppo"];
		$descr_gruppo=$riga["descrizione"];
		$elenco_gruppi .= "<option value=\"$id_gruppo\">$descr_gruppo</option>";
	};
};


echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>ASSEGNAZIONE MATERIALI DEL CORSO</td></tr>
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
  <input type=\"hidden\" name=\"risorsa\" value=\"materiali_sequenza_edit\">
   <input type=\"hidden\" name=\"comuni\" value=\"$comuni\">
  <input type=\"hidden\" name=\"id_corso\" value=\"$id_corso\">
  <input type=\"hidden\" name=\"id_edizione\" value=\"$id_edizione\">";
echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"450\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";

	echo "<tr>";
	echo "<td colspan=\"2\" bgcolor=\"$colore_scuro\"><span class=testonegativo><b>Cerca materiali da assegnare</b></span></td></tr>";
	
	echo "<tr bgcolor=\"$colore_sfondo\">";
	echo "<TD align=right><span class=testo><STRONG>$stringa[titolo]:</STRONG></span></TD>";
	echo "<TD><INPUT type=\"text\"  name=\"titolo_cerca\" size=\"60\"></TD>";
	echo "</tr>";
	
	echo "<tr bgcolor=\"$colore_sfondo_neutro\">";
	echo "<TD align=right><span class=testo><STRONG>$stringa[autore]:</STRONG></span></TD>
        <TD><INPUT type=\"text\"  name=\"id_autore_cerca\" size=\"20\">";
	echo "&nbsp;<span class=\"testopiccolo\">
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup.php?ruolo=tutti&campo=id_autore_cerca','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup_op.php?ruolo=tutti&campo=id_autore_cerca','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["tutti"]."</a>]
</span></td>";
	echo "</tr>";
	
	echo "
<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[gruppo]</b></span></p>
</td>
<td valign=top>
<select name=id_gruppo_cerca>
$elenco_gruppi
</select>
</td>
</tr>";

	
    echo "<tr bgcolor=\"$colore_sfondo\">";
	echo "<td colspan=\"2\" align=center><INPUT type=submit value=\"OK, visualizza i materiali\"></td>";
	echo "</tr>";
	echo "</table>";
	
	echo "</td></tr></table>";
  	echo "</FORM>";
  
?>  
  
</td></tr></table>
<br>

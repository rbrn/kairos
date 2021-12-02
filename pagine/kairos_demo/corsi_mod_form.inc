<?php

$id_corso=$_REQUEST["id_corso"];

$query = "SELECT * FROM corso WHERE id_corso='$id_corso'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

$descrizione=htmlentities($riga["descrizione"]);
$testo=$riga["testo"];
$testo=htmlentities($testo);

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[modifica_corso])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

echo "
<table border=0 width=500>
<tr>
<td>
<form action=corsi_mod_op.php method=post name=modulo id=modulo>
<input type=hidden name=id_corso value=\"$id_corso\">
<table border=0 wodth=100% cellspacing=2 cellpadding=2>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[id_corso]</b>:</span></p>
</td>
<td valign=top>
<span class=testo>$id_corso</span>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[titolo]</b>:</span></p>
</td>
<td valign=top>
<input type=text size=70 name=descrizione value=\"$descrizione\">
</td>
</tr>";


echo"
<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[descrizione]</b>:</span></td>
</tr>
<tr>
<td colspan=2 valign=top>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<TEXTAREA id=\"testo\" cols=80 name=\"testo\" rows=30>".$testo."</TEXTAREA>
</td></tr>
</table>
</td>
</tr>";

echo "
<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=right>";

echo "<input type=\"submit\" name=\"ok\" value=\"$stringa[ok]\" />";


echo "</td></tr>
</table>

</form>


</td>
</tr>
</table>
</td>
</tr>
</table>
<br><br>";

?>

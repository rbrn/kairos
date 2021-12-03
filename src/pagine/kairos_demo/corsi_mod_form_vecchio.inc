<?php

$id_corso=$_REQUEST["id_corso"];

$query = "SELECT * FROM corso WHERE id_corso='$id_corso'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

$descrizione=htmlentities($riga["descrizione"]);
$testo=$riga["testo"];

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
<table border=0 width=600>
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

if (!$win_ie) {
echo"
<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[descrizione]</b>:</span></td>
</tr>
<tr>
<td colspan=2 valign=top>
<TEXTAREA cols=70 name=testo rows=10 wrap=virtual>".$testo."</TEXTAREA>
</td>
</tr>";
} else {
	echo "
	<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[descrizione]</b>:</span></td>
</tr>";

	echo "<input type=\"hidden\" name=\"testo\" id=\"testo\">\n
	<tr>
	<td colspan=2 valign=top>
	";
	$modifica_testo=true;
	require "./include/editor.inc";
	echo "
	</td>
	</tr>
	";
};

echo "
<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=right>";

if (!$win_ie) {
echo "
<input type=submit value=$stringa[ok]>";
} else {
echo "<input type=submit value=$stringa[ok] onclick=\"inoltra();return true\">";
};


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

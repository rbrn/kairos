<?php
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];

if ($id_corso_s) {
$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione_s;

$query="SELECT * FROM corso WHERE id_corso='$id_corso_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$descr_corso=$riga["descrizione"];
};


if ($id_corso_s) {
	if ($ruolo=='admin') {
		$elenco_gruppi="<option value=\"\" selected>$stringa[qualunque]</option>";
		$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_gruppo";
	} else {
		$elenco_gruppi="<option value=\"\" selected>$stringa[qualunque]</option>";
		$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_tutor='$id_utente' ORDER BY id_gruppo";
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
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>";

if ($id_corso_s) {
echo "
<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_index><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso_s><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span></a>
</td></tr>
";

echo "
<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_forum])."</b></span>
</td></tr>";
} else {
echo "

<tr>
<td valign=top width=100%><span class=testo><b>".$stringa[utility]."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_forum_comuni])."</b></span>
</td></tr>";
};

if ($id_corso_s) {
echo "
<tr>
<td valign=top width=100%><span class=testo><b>$stringa[corso]:</b> $descr_corso: $descr_edizione</span>
</td></tr>";
};


echo "
<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[nuovo_forum])."</b></span>
</td></tr>";

$indietro="javascript:history.back()";

echo "
<tr>
<td valign=top width=100%>
<a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";


echo "
<table border=0 width=600>
<tr>
<td>
<form action=addforum.php method=post>
<input type=hidden name=id_corso value=\"$id_corso_s\">
<input type=hidden name=id_edizione value=\"$id_edizione_s\">

<table border=0 wodth=100% cellspacing=2 cellpadding=2>

<!--
<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[id_forum]</b></span></p>
</td>
<td valign=top>
<input type=text size=20 name=id_forum>
</td>
</tr>
-->

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[posizione]</b></span></p>
</td>
<td valign=top>
<input type=text size=10 name=ordine>
<br><span class=testopiccolo><i>$stringa[indica_posizione]</i></span>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[descrizione]</b></span></p>
</td>
<td valign=top>
<textarea name=descrizione cols=40 rows=5>
</textarea>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[tipo]</b></span></p>
</td>
<td valign=top>
<select name=tipo>";
if ($ruolo=='admin') {
	if ($id_corso_s) {
		echo "
			<option value=\"1\">$stringa[corso]</option>
			
			";
	} else {
		echo "<option value=\"0\">$stringa[generale]</option>
		      <option value=\"4\">$stringa[staff]</option>";
	}
} else {
	if ($id_corso_s) {
		echo "
			<option value=\"1\">$stringa[corso]</option>
			
			";
	};
};
echo "
</select>
</td>
</tr>
";
if ($id_corso_s) {
echo "
<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[gruppo]</b></span></p>
</td>
<td valign=top>
<select name=id_gruppo>
$elenco_gruppi
</select>
</td>
</tr>";
};

echo "

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[file_allegati]</b></p></font>
</td>
<td valign=top>
<input type=radio name=file_allegati value=1> <span class=testo>$stringa[si]</span>
<input type=radio name=file_allegati value=0 checked> <span class=testo>$stringa[no]</span>
</td>
</tr>

<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=right><input type=submit value=$stringa[crea]></td></tr>
</table>

</form>


</td>
</tr>
</table>
</td>
</tr>
</table>
<br>";

?>

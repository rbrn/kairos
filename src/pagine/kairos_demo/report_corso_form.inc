<?php
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];
$direttore=0;

$query="SELECT DISTINCT * FROM ruolo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_utente='$kairos_cookie[0]'";
$result=$mysqli->query($query);
if ($result->num_rows) $direttore=1;

$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione_s;

$query="SELECT * FROM corso WHERE id_corso='$id_corso_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$descr_corso=$riga["descrizione"];

if ($ruolo=='admin' or $direttore) {
	$elenco_gruppi="<option value=\"\" selected>$stringa[qualunque]</option>";
	$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_gruppo";
} else {
	$elenco_gruppi="";
	$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_tutor='$id_utente' ORDER BY id_gruppo";
};
$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {
	$id_gruppo=$riga["id_gruppo"];
	$descr_gruppo=$riga["descrizione"];
	$elenco_gruppi .= "<option value=\"$id_gruppo\">$descr_gruppo</option>";
};


if (!$elenco_gruppi) {
	echo "<p><span class=testo>$stringa[errore_no_tutor]</span></p>";
	exit();
};	

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_index><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso_s><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s><span class=testo><b>$stringa[corso]:</b> $descr_corso: $descr_edizione</span></a>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[report_corso])."</b></span>
</td></tr>



<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso&id_edizione=$id_edizione\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso&id_edizione=$id_edizione\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";
	
echo "

<form action=index.php method=get>
<input type=hidden name=risorsa value=\"report_corso\">
<input type=hidden name=id_corso value=\"$id_corso_s\">
<input type=hidden name=id_edizione value=\"$id_edizione_s\">
<table border=0 wodth=100% cellspacing=2 cellpadding=2>";

echo "
<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[gruppo]:</b></span></p>
</td>
<td valign=top>
<select name=id_gruppo_report>
$elenco_gruppi
</select>
</td>
</tr>
";

echo "
<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=right><input type=submit value=\"$stringa[ok]\"></td></tr>
</table>

</form>

";
echo "</td></tr></table><br>";
?>

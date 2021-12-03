<?php
$id_corso=$_REQUEST["id_corso"];
$query="SELECT * FROM corso WHERE id_corso='$id_corso'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$descrizione=$riga["descrizione"];

$data = getdate();
$gg_oggi=$data["mday"];
$mm_oggi=$data["mon"];
$aa_oggi=$data["year"];

$gg="";
for ($i=1;$i<=31;$i++) {
	$giorno = "0".$i;
	$giorno=substr($giorno,-2);
	if ($i==$gg_oggi) {
		$gg .= "<option value=$giorno selected>$giorno</option>\n";
	} else {
		$gg .= "<option value=$giorno>$giorno</option>\n";
	};
};

$mm="";
for ($i=1;$i<=12;$i++) {
	$mese = "0".$i;
	$mese=substr($mese,-2);
	if ($i==$mm_oggi) {
		$mm .= "<option value=$mese selected>$mese</option>\n";
	} else {
		$mm .= "<option value=$mese>$mese</option>\n";
	};
};

$aa="";
for ($i=0;$i<=2;$i++) {
	$anno = $aa_oggi + $i;
	if ($anno==$anno_oggi) {
		$aa .= "<option value=$anno selected>$anno</option>\n";
	} else {
		$aa .= "<option value=$anno>$anno</option>\n";
	};
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_index><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[nuova_edizione_corso])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>$descrizione ($id_corso)</b></span>
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
<form action=corsi_edizione_nuova_op.php method=post>
<input type=hidden name=\"id_corso\" value=\"$id_corso\">
<table border=0 wodth=100% cellspacing=2 cellpadding=2>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[id_edizione]</b></span></p>
</td>
<td valign=top>
<input type=\"text\" size=20 name=\"id_edizione\">
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[descrizione]</b></span></p>
</td>
<td valign=top>
<input type=\"text\" size=40 name=\"descrizione\">
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[data_inizio]</b></span></p>
</td>
<td valign=top>
<select name=gg>
$gg
</select>
/
<select name=mm>
$mm
</select>
/
<select name=aa>
$aa
</select>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[durata]</b></span></p>
</td>
<td valign=top>
<input type=\"text\" maxlength=20 size=05 name=\"durata\"> <select name=un_mis>
<option value=\"mesi\" selected>$stringa[mesi]</option>
<option value=\"giorni\">$stringa[giorni]</option>
</select>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[status]</b></span></p>
</td>
<td valign=top>
<select name=\"stato\">
<option value=\"attiva\">$stringa[attiva]</option>
<option value=\"inattiva\" selected>$stringa[inattiva]</option></select>
</td>
</tr>

<tr>
<td valign=top align=right>
<input type=checkbox name=\"autoiscrizione\">
</td>
<td>
<span class=testo>$stringa[autoiscrizione]</span>
</td>
</tr>

<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=right><input type=submit value=$stringa[ok]></td></tr>
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

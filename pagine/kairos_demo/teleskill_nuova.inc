<!-- CONTENUTO DELLA PAGINA -->
<?php
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

$aa="<option value=$aa_oggi selected>$aa_oggi</option>";

$hh="";
for ($i=0;$i<24;$i++) {
	$ora = "0".$i;
	$ora=substr($ora,-2);
	$hh .= "<option value=$ora>$ora</option>\n";
};

$ss="";
for ($i=0;$i<60;$i++) {
	$minuto = "0".$i;
	$minuto=substr($minuto,-2);
	$ss .= "<option value=$minuto>$minuto</option>\n";
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td class=titolodot>
NUOVA STANZA DI VIDEOCONFERENZA
</td></tr>

<tr><td>
<form action=index.php  method=get>
<input type=hidden name=risorsa value=teleskill_nuova_op>
<table border=0 wodth=100% cellspacing=2 cellpadding=2>

<tr>
<td  align=right valign=top>
<span class=testo><b>$stringa[giorno]:</b></span>
</td>

<td  valign=top>
<span class=testo>
<select name=dal_gg>
$gg
</select>
/
<select name=dal_mm>
$mm
</select>
/
<select name=anno>
$aa
</select>
</span>
</td>
</tr>

<tr>
<td align=right valign=top>
<span class=testo><b>$stringa[dalle_ore]:</b></span>
</td>

<td  valign=top>
<span class=testo>
<select name=dal_hh>
$hh
</select>
:
<select name=dal_ss>
$ss
</select>
</span>
</td></tr>
<tr>
<td  align=right valign=top>
<span class=testo><b>$stringa[alle_ore]:</b></span>
</td>
<td  valign=top>
<span class=testo>

<select name=al_hh>
$hh
</select>
:
<select name=al_ss>
$ss
</select>
</span>
</td>
</tr>

<tr>
<td align=right valign=top><span class=testo><b>Titolo:</b></span></td>
<td><input type=\"text\" name=\"titolo\" size=\"50\"></td>
</tr>

<tr>
<td align=right valign=top><span class=testo><b>ID Moderatore:</b></span></td>
<td><input type=\"text\" name=\"userid\" size=\"20\"></td>
</tr>

<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=center><input type=submit value=\"$stringa[ok]\"></td></tr>
</table>
</form>
</td>
</tr>
</table>
<br>
";
?>

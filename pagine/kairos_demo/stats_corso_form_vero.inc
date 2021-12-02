<?php
$dossier=$_REQUEST["dossier"];
$data = getdate();
$gg_oggi=$data["mday"];
$mm_oggi=$data["mon"];
$aa_oggi=$data["year"];
$gg="";
for ($i=1;$i<=31;$i++) {
	$giorno = "0".$i;
	$giorno=substr($giorno,-2);
	if ($i==$gg_oggi) {
		$da_gg .= "<option value=$giorno selected>$giorno</option>\n";
	} else {
		$da_gg .= "<option value=$giorno>$giorno</option>\n";
	};
};

$mm="";
for ($i=1;$i<=12;$i++) {
	$mese = "0".$i;
	$mese=substr($mese,-2);
	if ($i==$mm_oggi) {
		$da_mm .= "<option value=$mese selected>$mese</option>\n";
	} else {
		$da_mm .= "<option value=$mese>$mese</option>\n";
	};
};
$aa_prev=$aa_oggi-1;
$da_aa = "<option value=$aa_prev>$aa_prev</option>\n<option value=$aa_oggi selected>$aa_oggi</option>\n";

$a_gg=$da_gg;
$a_mm=$da_mm;
$a_aa=$da_aa;

if (!$dossier) {
if ($ruolo=='admin') {
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
};



if (!$elenco_gruppi and !$dossier) {
	echo "<p><span class=testo>$stringa[errore_no_tutor]</span></p>";
	exit();
};	
	
echo "
<p><span class=titolopagina>$stringa[statistiche_corso]</span></p>
<form action=index.php method=get>
<input type=hidden name=risorsa value=\"stats_corso\">
<input type=hidden name=dossier value=\"$dossier\">
<table border=0 wodth=100% cellspacing=2 cellpadding=2>

<tr>
<td width=50% align=right valign=top>
<span class=testo>
<b>$stringa[dal]:</b>
</span>
</td>

<td width=50% valign=top>
<select name=\"da_gg\">
$da_gg
</select>
/
<select name=\"da_mm\">
$da_mm
</select>
/
<select name=\"da_aa\">
$da_aa
</select>
</span>
</td>
</tr>

<tr>
<td width=50% align=right valign=top>
<span class=testo>
<b>$stringa[al]:</b>
</span>
</td>

<td width=50% valign=top>
<select name=\"a_gg\">
$a_gg
</select>
/
<select name=\"a_mm\">
$a_mm
</select>
/
<select name=\"a_aa\">
$a_aa
</select>
</span>
</td>
</tr>
";

if (!$dossier) {
	echo "
<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[gruppo]:</b></span></p>
</td>
<td valign=top>
<select name=id_gruppo_stat>
$elenco_gruppi
</td>
</tr>
";
};

echo "
<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=right><input type=submit value=\"$stringa[ok]\"></td></tr>
</table>

</form>";

if ($ruolo=='staff' or $ruolo=='admin') {
echo "
<hr size=1>
<span class=testo>[<a href=index.php?risorsa=report_corso_form>".$stringa[report_corso]."</a>]</span>";
};

echo "
<hr size=1>
";

?>

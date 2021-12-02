<?php
$dossier=$_REQUEST["dossier"];

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
if ($ruolo=='admin' or $direttore) {
	$elenco_gruppi="<option value=\"\" selected>$stringa[qualunque]</option>
					<option value=\"99staff\">staff tutor</option>
	";
	
	
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

$max_giorni=$stringa[max_7_giorni];
if ($ruolo=="admin" or $ruolo=="staff") {
	$max_giorni=$stringa[max_30_giorni];
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>";

if (!$dossier) {
echo "
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
";
} else {
echo "
<tr>
<td valign=top width=100%><span class=testo><b>$stringa[corso]:</b> $descr_corso: $descr_edizione</span>
</td></tr>";
};

echo "
<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[statistiche_corso])."</b></span>
</td></tr>
";

if ($ruolo=='staff' or $ruolo=='admin' or $direttore) {
echo "
<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso&id_edizione=$id_edizione\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";
};

echo"
<td><tr>
";

echo "
<form action=index.php method=get>
<input type=hidden name=risorsa value=\"stats_corso\">
<input type=hidden name=dossier value=\"$dossier\">
<input type=hidden name=id_corso value=\"$id_corso_s\">
<input type=hidden name=id_edizione value=\"$id_edizione_s\">

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
</span><br>
<span class=testopiccolo>$max_giorni</span>
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

echo "
<hr size=1>
";

mysql_select_db("atlante",$db);
$query="SELECT * FROM stat_job WHERE id_utente='$id_utente' AND id_db='$DBASE' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY data_stat DESC";
$result=$mysqli->query($query);

if ($result->num_rows) {

echo "
<p><span class=titolopagina>Statistiche richieste</span></p>";


echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

echo "
<tr bgcolor=\"$colore_scuro\">
<td valign=top>
<span class=testonegativo>
<b>Dal</b>
</span>
</td>

<td valign=top>
<span class=testonegativo>
<b>Al</b>
</span>
</td>

<td valign=top>
<span class=testonegativo>
<b>Gruppo</b>
</span>
</td>

<td valign=top>
<span class=testonegativo>
<b>Stato</b>
</span>
</td>

<td>&nbsp;</td>
</tr>
";
$colore=$colore_sfondo;

while ($riga=$result->fetch_array()) {
	$id_stat=$riga["id_stat"];
	$da_data=$riga["da_data"];
	$a_data=$riga["a_data"];
	$id_gruppo_stat=$riga["id_gruppo"];
	$descr_gruppo=$riga["descr_gruppo"];
	$stato=$riga["stato"];
	
	$label_gruppo=$stringa[qualunque];
	if ($id_gruppo_stat) $label_gruppo=$descr_gruppo;
	
	ereg("(.+)-(.+)-(.+) (.+)",$da_data,$parti);
	$da_aa=$parti[1];
	$da_mm=$parti[2];
	$da_gg=$parti[3];
	
	ereg("(.+)-(.+)-(.+) (.+)",$a_data,$parti);
	$a_aa=$parti[1];
	$a_mm=$parti[2];
	$a_gg=$parti[3];
	
	echo "
	<tr bgcolor=\"$colore\">
	<td valign=top>
	<span class=testo>
	$da_gg/$da_mm/$da_aa
	</span>
	</td>

	<td valign=top>
	<span class=testo>
	$a_gg/$a_mm/$a_aa
	</span>
	</td>
	
	<td valign=top>
	<span class=testo>
	$label_gruppo
	</span>
	</td>
	
	<td valign=top>
	<span class=testo>
	";
	$url=$stringa[$stato];
	if ($stato=='stat_ok') {
		$url="<a href=\"index.php?risorsa=stats_corso_view&id_stat=$id_stat&id_corso=$id_corso_s&id_edizione=$id_edizione_s\">$stringa[$stato]</a>"; 
	};
	echo $url;
	echo "
	</span>
	</td>";
			
	if ($stato<>'stat_processing') {
		echo "<td><a href=\"index.php?risorsa=msg&msg=conf_canc&pagina=stats_corso_del.php&id_stat=$id_stat&dossier=$dossier&id_corso=$id_corso_s&id_edizione=$id_edizione_s\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_stat','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_stat\"></a></td>";	
	} else {
		echo "<td>&nbsp;</td>";
	};
	
	echo "
	</tr>";
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
		
};

echo "</table>";
echo "</td></tr></table>";
mysql_select_db($DBASE,$db);
};

echo "</td></tr></table><br>";
?>

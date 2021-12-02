<?php
$stanza=$_REQUEST["stanza"];
$dal_gg=$_REQUEST["dal_gg"];
$dal_mm=$_REQUEST["dal_mm"];
$anno=$_REQUEST["anno"];

$dal_hh=$_REQUEST["dal_hh"];
$dal_ss=$_REQUEST["dal_ss"];
$al_hh=$_REQUEST["al_hh"];
$al_ss=$_REQUEST["al_ss"];
$al_mm = $dal_mm;
$al_gg = $dal_gg;

$query = "SELECT * FROM c_messages_archive WHERE room='$stanza' AND m_time >= UNIX_TIMESTAMP(\"$anno-$dal_mm-$dal_gg $dal_hh:$dal_ss:00\") AND m_time<=UNIX_TIMESTAMP(\"$anno-$al_mm-$al_gg $al_hh:$al_ss:00\") ORDER BY m_time";
$result=$mysqli->query($query);

$tot_righe = mysql_numrows($result);

$query1 = "SELECT username, count(*) as righe_utente FROM c_messages_archive WHERE room='$stanza' AND m_time >= UNIX_TIMESTAMP(\"$anno-$dal_mm-$dal_gg $dal_hh:$dal_ss:00\") AND m_time<=UNIX_TIMESTAMP(\"$anno-$al_mm-$al_gg $al_hh:$al_ss:00\")  GROUP BY username ORDER BY righe_utente DESC";

$result1=$mysqli->query($query1);
$tot_utenti = mysql_numrows($result1);

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td class=titolodot>
$stringa[archivio_chat]
</td></tr>

<tr><td>
<p><span class=testopiccolo>
[<a href=index.php?risorsa=form_monitor_chat>$stringa[indietro]</a>]
</span>
</p>
<span class=testo>
<p>
$stringa[stanza_di_chat]: <b>$stringa[$stanza]</b>
</p>
<p>

$stringa[dialoghi_del] <b>$dal_gg/$dal_mm/$anno</b> $stringa[dalle_ore] <b>$dal_hh:$dal_ss</b> $stringa[alle_ore] <b>$al_hh:$al_ss</b>
<br>
$stringa[totale_righe]: <b>$tot_righe</b>
<br>
$stringa[totale_utenti]: <b>$tot_utenti</b> 
</p>
</span>
<table border=1 width=150 cellspacing=0 cellpadding=3>
<tr>
<td width=30><span class=testo>$stringa[utente]</span></td>
<td  width=60 align=right><span class=testo>$stringa[righe]</span></td>
<td  width=60 align=right><span class=testo>%</span></td>
</tr>
";

while ($stat_utente = $result1->fetch_array()) {
	$id_utente=$stat_utente["username"];
	$righe_utente=$stat_utente["righe_utente"];
	$perc_utente=round(100*$righe_utente/$tot_righe);
	echo "
	<tr>
	<td width=20>";
	if ($id_utente) {
	echo "
	<span class=testopiccolo>
	<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente</a>
	</span>";
	} else {
	echo "
	<span class=testopiccolo>
	$stringa[entra_esce]
	</span>";
	};
	echo "
	</td>
	<td width=40 align=right><span class=testo>$righe_utente</span></td>
	<td width=40 align=right><span class=testo>$perc_utente</span></td>
	</tr>";
};

echo "
</table><br>

<hr size=1>

<table border=0 width=100% cellspacing=0 cellpadding=3 bgcolor=$colore_sfondo>";

while ($riga_chat = $result->fetch_array()) {
	$time = date("d/m/Y H:i:s",$riga_chat["m_time"]);
	$id_utente=$riga_chat["username"];
	$msg = $riga_chat["message"];

	echo "
	<tr>
	<td width=15%>
	<span class=testopiccolo>
	$time
	</span>
	</td>
	<td width=10%>
	<span class=testopiccolo>
	<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente</a>
	</span>
	</td>
	<td width=75%>
	<span class=testopiccolo>
	$msg
	</span>
	</td>	
	</tr>\n";
};
echo "</table>
</td></tr></table><br>
";
?>

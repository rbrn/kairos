<!-- CONTENUTO DELLA PAGINA -->
<?php
$elenco_stanze="";
for($i = 0; $i < count($DefaultChatRooms); $i++)
{
	$tmpRoom = stripslashes($DefaultChatRooms[$i]);
	$id_tmpRoom=$tmpRoom;
	//if ($id_corso_s) $id_tmpRoom =$tmpRoom."_".$id_corso_s;
	
	$elenco_stanze .= "<option value=$id_tmpRoom>$stringa[$tmpRoom]</option>\n";
};

if ($id_corso_s) {
	$query="SELECT descrizione FROM corso WHERE id_corso='$id_corso_s'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$descrizione_corso=$riga[descrizione];
	
	$elenco_stanze .= "<option value=$id_corso_s>$descrizione_corso</option>\n";
	$elenco_stanze .= "<option value=lab_$id_corso_s>Laboratorio $descrizione_corso</option>\n";

	
	if ($ruolo<>'staff' and $ruolo<>'admin' ) {
		$query_gruppo="SELECT a.id_gruppo,a.descrizione FROM gruppo_utenti as a,iscrizioni_gruppo_pw as b WHERE a.id_corso=b.id_corso AND a.id_edizione=b.id_edizione AND a.id_gruppo=b.id_gruppo AND a.tipo_gruppo=1 AND a.id_corso='$id_corso_s' AND a.id_edizione='$id_edizione_s' AND b.id_utente='$kairos_cookie[0]' ORDER BY id_gruppo";
		$result_gruppo=$mysqli->query($query_gruppo);
		while ($riga_gruppo=$result_gruppo->fetch_array()) {
			$id_gruppo_s=$riga_gruppo["id_gruppo"];
			$descr_gruppo_s=$riga_gruppo["descrizione"];
			$nome_stanza=$descr_gruppo_s;
			$id_tmpRoom=$id_corso_s."-".$id_gruppo_s;
			$elenco_stanze .= "<option value=$id_tmpRoom>$nome_stanza</option>\n";
		};
	};
	
	
	if ($ruolo=='staff' or $ruolo=='admin' ) {
		$query_gruppo="SELECT id_gruppo,descrizione FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo_gruppo=1 ORDER BY id_gruppo";
		$result_gruppo=$mysqli->query($query_gruppo);
		while ($riga_gruppo=$result_gruppo->fetch_array()) {
			$id_gruppo_s=$riga_gruppo["id_gruppo"];
			$descr_gruppo_s=$riga_gruppo["descrizione"];
			$nome_stanza=$descr_gruppo_s;
			$id_tmpRoom=$id_corso_s."-".$id_gruppo_s;
			$elenco_stanze .= "<option value=$id_tmpRoom>$nome_stanza</option>\n";
		};
	};
	
};
	
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
	$anno = $aa_oggi - $i;
	if ($anno==$anno_oggi) {
		$aa .= "<option value=$anno selected>$anno</option>\n";
	} else {
		$aa .= "<option value=$anno>$anno</option>\n";
	};
};

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
$stringa[archivio_chat]
</td></tr>

<tr><td>
<form action=index.php  method=get>
<input type=hidden name=risorsa value=monitor_chat>
<table border=0 wodth=100% cellspacing=2 cellpadding=2>
<tr>
<td align=right valign=top width=50%>
<span class=testo><b>$stringa[stanza]:</span>
</td>
<td width=50% valign=top>
<select name=stanza>
$elenco_stanze
</select>
</td>
</tr>

<tr>
<td width=50% align=right valign=top>
<span class=testo><b>$stringa[giorno]:</b></span>
</td>

<td width=50% valign=top>
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
<td width=50% align=right valign=top>
<span class=testo><b>$stringa[dalle_ore]:</b></span>
</td>

<td width=50% valign=top>
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
<td width=50% align=right valign=top>
<span class=testo><b>$stringa[alle_ore]:</b></p>
</td>
<td width=50% valign=top>
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

<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=right><input type=submit value=\"$stringa[ok]\"></td></tr>
</table>
</form>
</td>
</tr>
</table>
<br>
";
?>

<?php
$id_forum=$_REQUEST["id_forum"];
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

$query="SELECT * FROM forum WHERE id_forum='$id_forum'";
$result=$mysqli->query($query);

$dati_forum=$result->fetch_array();

$ordine=$dati_forum["ordine"];
$id_gruppo=$dati_forum["id_gruppo"];
$id_corso=$dati_forum["id_corso"];
$id_edizione=$dati_forum["id_edizione"];
$id_corso_ed=$id_corso." ".$id_edizione;
$tipo=$dati_forum["tipo"];
$descrizione=$dati_forum["descrizione"];
$file_allegati=$dati_forum["file_allegati"];
$archiviato=$dati_forum["archiviato"];

$tipo0="";
$tipo1="";
$tipo3="";
$tipo4="";

$variabile="tipo".$tipo;
$$variabile="selected";
	

$file_si="";
$file_no="";

if ($file_allegati) {
	$file_si="checked";
} else {
	$file_no="checked";
};


$archiviato_si="";
$archiviato_no="";

if ($archiviato) {
	$archiviato_si="checked";
} else {
	$archiviato_no="checked";
};

if ($id_corso_s) {
	if ($ruolo=='admin') {
		$sel="";
		if (!$id_gruppo) $sel="selected";
		$elenco_gruppi="<option value=\"\" $sel>$stringa[qualunque]</option>";
		$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_gruppo";
	} else {
		$sel="";
		if (!$id_gruppo) $sel="selected";
		$elenco_gruppi="<option value=\"\" $sel>$stringa[qualunque]</option>";
		$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_tutor='$id_utente' ORDER BY id_gruppo";
	};
	
	$result=$mysqli->query($query);

	while ($riga=$result->fetch_array()) {
		$id_gruppo_d=$riga["id_gruppo"];
		$descr_gruppo_d=$riga["descrizione"];
		$sel="";
		if ($id_gruppo==$id_gruppo_d) $sel="selected";
		$elenco_gruppi .= "<option value=\"$id_gruppo_d\" $sel>$descr_gruppo_d</option>";
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
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[modifica_forum])."</b></span>
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
<form action=modforum.php method=post>
<input type=hidden name=id_forum value=\"$id_forum\">
<input type=hidden name=id_corso value=\"$id_corso_s\">
<input type=hidden name=id_edizione value=\"$id_edizione_s\">

<table border=0 wodth=100% cellspacing=2 cellpadding=2>

<!--
<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[id_forum]</b></span></p>
</td>
<td valign=top>
<span class=testo><b>$id_forum</b></span>
</td>
</tr>
-->

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[posizione]</b></span></p>
</td>
<td valign=top>
<input type=text maxlength=03 size=10 name=ordine value=\"$ordine\">
<br><span class=testopiccolo><i>$stringa[indica_posizione]</i></span>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[descrizione]</b></span></p>
</td>
<td valign=top>
<textarea name=descrizione cols=40 rows=5>
$descrizione
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
			<option value=\"1\" $tipo1>$stringa[corso]</option>
			
			";
	} else {
		echo "<option value=\"0\" $tipo0>$stringa[generale]</option>
		      <option value=\"4\" $tipo4>$stringa[staff]</option>";
	}
} else {
	if ($id_corso_s) {
		echo "
			<option value=\"1\" $tipo1>$stringa[corso]</option>
			
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

echo "
<tr>
<td align=right valign=top>
<p><span class=testo><b>Archiviato</b></p></font>
</td>
<td>
<input type=radio name=archiviato value=1 $archiviato_si> <span class=testo>$stringa[si]</span>
<input type=radio name=archiviato value=0 $archiviato_no> <span class=testo>$stringa[no]</span>
</td>
</tr>";

};

echo "

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[file_allegati]</b></p></font>
</td>
<td>
<input type=radio name=file_allegati value=1 $file_si> <span class=testo>$stringa[si]</span>
<input type=radio name=file_allegati value=0 $file_no> <span class=testo>$stringa[no]</span>
</td>
</tr>

<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=right><input type=submit value=$stringa[modifica]></td></tr>
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

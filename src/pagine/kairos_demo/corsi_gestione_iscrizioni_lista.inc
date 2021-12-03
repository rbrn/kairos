<?php
$id_utente_cookie=$kairos_cookie[0];
$id_utente_cerca=$_REQUEST["id_utente_cerca"];
$nome=$_REQUEST["nome"];
$cognome=$_REQUEST["cognome"];
$stato=$_REQUEST["stato"];
$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];
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


$elenco_corsi="";
$query="SELECT * FROM edizioni ORDER BY id_corso,id_edizione DESC";
$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {
	$id_corso=$riga["id_corso"];
	$id_edizione=$riga["id_edizione"];
	$descr_edizione2=$riga["descrizione"];
	if (!$descr_edizione2) $descr_edizione2=$id_edizione;

	$query_c="SELECT descrizione FROM corso WHERE id_corso='$id_corso'";
	$result_c=$mysqli->query($query_c);
	$riga_c=$result_c->fetch_array();
	$descr_corso2=$riga_c["descrizione"];

	if ($id_corso<>"$id_corso_s" or $id_edizione<>"$id_edizione_s") {
		$elenco_corsi .= "<option value=\"$id_corso $id_edizione\">$descr_corso2 -  $descr_edizione2";
		};
};

if ($cerca_reg) {
	$dal=$da_reg_aa."-".$da_reg_mm."-".$da_reg_gg;
	$al=$a_reg_aa."-".$a_reg_mm."-".$a_reg_gg;
	$query1=" data_reg>='$dal' AND data_reg<='$al' ";
	if ($id_utente_cerca) {
		if ($query1) $query1 .= "AND";
		$query1 .= " (id_utente='$id_utente_cerca') ";
	};
	
	if ($nome) {
		if ($query1) $query1 .= "AND";
		$query1 .= " (nome LIKE '$nome%') ";
	};

	if ($cognome) {
		if ($query1) $query1 .= "AND";
		$query1 .= " (cognome LIKE '$cognome%') ";
	};
	
	$query = "SELECT id_utente,cognome,nome,data_reg FROM utenti WHERE $query1  ORDER BY data_reg DESC";
} else {
	$query1=" utenti.id_utente=iscrizioni_corso.id_utente AND iscrizioni_corso.id_corso='$id_corso_s' AND iscrizioni_corso.id_edizione='$id_edizione_s' ";
	if ($id_utente_cerca) {
		if ($query1) $query1 .= "AND";
		$query1 .= " (utenti.id_utente='$id_utente_cerca') ";
	};
	
	if ($nome) {
		if ($query1) $query1 .= "AND";
		$query1 .= " (utenti.nome LIKE '$nome%') ";
	};

	if ($cognome) {
		if ($query1) $query1 .= "AND";
		$query1 .= " (utenti.cognome LIKE '$cognome%') ";
	};
	
	$query = "SELECT iscrizioni_corso.id_utente,nome,cognome,iscrizioni_corso.id_corso,iscrizioni_corso.id_edizione,iscrizioni_corso.data_iscrizione FROM iscrizioni_corso,utenti WHERE $query1 ORDER BY iscrizioni_corso.id_corso,iscrizioni_corso.id_edizione,iscrizioni_corso.data_iscrizione DESC ";
};

$result=$mysqli->query($query);
if (!$result) {
	echo "<br>errore: ".mysql_error()." ".$query."<br>";
};

if (!$pag_size) $pag_size=20;
if (!$pagina) $pagina=1;

$tot_righe=$result->num_rows;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$num =$tot_righe;

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
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_iscrizioni])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=corsi_gestione_iscrizioni_form&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=corsi_gestione_iscrizioni_form&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
";

if ($cerca_reg) {
	echo "<tr><td><span class=testo>$stringa[utenti_trovati]: <b>$num</b></span></td></tr>";
} else {
	echo "<tr><td><span class=testo>$stringa[iscrizioni_trovate]: <b>$num</b></span></td></tr>";
};

echo "
<tr><td>
<form action=corsi_gestione_iscrizioni_op.php method=post name=modulo id=modulo>
<input type=hidden name=cerca_reg value=\"$cerca_reg\">
<input type=hidden name=cerca_iscr value=\"$cerca_iscr\">
<input type=hidden name=id_corso value=\"$id_corso_s\">
<input type=hidden name=id_edizione value=\"$id_edizione_s\">";

echo "<p>";
if ($cerca_reg) {
	echo "<span class=testo>$stringa[iscrivi_utenti_selezionati]:<br>
	<b>$descr_corso - $descr_edizione</b> </span>";
	/*
	echo "
	<select name=id_corso_edizione_form>
	$elenco_corsi
	</select>";
	*/
	echo "
	<input type=hidden name=id_corso_edizione_form value=\"$id_corso_s $id_edizione_s\">
	<input type=submit value=\"$stringa[ok]\">
	";
} else {
	echo "<span class=testo>$stringa[sposta_iscrizioni_selezionate]:</span>";
	echo "
	<select name=id_corso_edizione_form>
	$elenco_corsi
	</select>
	<input type=submit value=\"$stringa[ok]\">
	<br><input type=\"checkbox\" name=\"copia_iscr\"> <span class=testo>copia le iscrizioni senza eliminare quelle all'attuale edizione</span>
	";
};
echo "</p>";

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

echo "
<tr bgcolor=\"$colore_scuro\">
<td>&nbsp;</td>
<td><span class=testonegativo><b>$stringa[num]</b></span></td>
<td><span class=testonegativo><b>$stringa[id_utente]</b></span></td>
<td><span class=testonegativo><b>$stringa[cognome]</b></span></td>
<td><span class=testonegativo><b>$stringa[nome]</b></span></td>";


if ($cerca_reg) {
	echo "
	<td><span class=testonegativo><b>$stringa[data_registrazione]</b></span></td>";
} else {
	echo "
	<td><span class=testonegativo><b>$stringa[data_iscrizione]</b></span></td>
	<td></td>";
};
	
echo "
</tr>\n";

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;

$righe=1;
$continua = true;
$colore=$colore_sfondo;
while ($riga=$result->fetch_array()) {
	echo "<tr bgcolor=\"$colore\">";
	
	if ($cerca_reg) {		
		printf ("<td><input type=checkbox name=id_u[] value=\"%s\"></td>",$riga["id_utente"]);
	} else {
		printf ("<td><input type=checkbox name=id_u[] value=\"%s %s %s\"></td>",$riga["id_utente"],$riga["id_corso"],$riga["id_edizione"]);
	};
	
	printf ("<td><span class=testo>%s</span></td>",$progr);
	echo "<td><span class=testo><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$riga[id_utente]',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$riga[id_utente]</a></span></td>";
	printf ("<td><span class=testo>%s</span></td>",$riga["cognome"]);
	printf ("<td><span class=testo>%s</span></td>",$riga["nome"]);
	
	if ($cerca_reg) {
		printf ("<td><span class=testo>%s</span></td>",$riga["data_reg"]);
	} else {
		printf ("<td><span class=testo>%s</span></td>",$riga["data_iscrizione"]);
		
		echo "<td><a href=\"index.php?risorsa=msg&msg=conf_canc&pagina=corsi_cancella_iscrizione.php&id_utente=$riga[id_utente]&id_corso=$riga[id_corso]&id_edizione=$riga[id_edizione]\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$riga[id_utente]','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella_iscrizione]\" border=\"0\" name=\"img_del_$riga[id_utente]\"></a></td>";
	};
	
	echo "</tr>\n";

	$righe++;
	$progr++;
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
};


?>
		
</table>
<input type=button value="<?php echo($stringa[seleziona_tutti]);?>" onClick="SetAllCheckBoxes('modulo','id_u[]',true)"> <input type=button value="<?php echo($stringa[deseleziona]);?>" onClick="SetAllCheckBoxes('modulo','id_u[]',false)"> 
</td></tr></table>

</form>	
<br>
<?php
echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		$query=$_SERVER["QUERY_STRING"];
		$query=str_replace("&pagina=$pagina","",$query);
		$query .= "&pagina=$i";
		echo "
		[<a href=index.php?$query>$i</a>]
		";
	};
	$i++;
};
echo "</span><br>";	
?>
</td></tr></table>
<br>

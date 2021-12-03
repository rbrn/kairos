<?php
//if ($cod_area=="kairos_master" or $cod_area=="kairos_masterunitus") require "./include/master_pw.inc";

$id_gruppo_report=$_REQUEST["id_gruppo_report"];
$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];

$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];

$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione_s;

$query="SELECT * FROM corso WHERE id_corso='$id_corso_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$descr_corso=$riga["descrizione"];

$livello_gruppo="";
$note_gruppo="";

$valutazione_pw=0;
if ($cod_area=="kairos_master" or $cod_area=="kairos_masterunitus") {
	if ($id_gruppo_report) {
		$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_report' AND tipo_gruppo=1";
		$result=$mysqli->query($query);
		if ($result->num_rows) {
			$riga=$result->fetch_array();
			
			$descr_gruppo=$riga["descrizione"];
			$livello_gruppo=$riga["livello"];
			$note_gruppo=$riga["note"];
			$valutazione_pw=1;
			
			$livello_gruppo1="";
			$livello_gruppo2="";
			$livello_gruppo3="";
			$livello_gruppo4="";
			$livello_gruppo5="";
	
			if ($livello_gruppo) {
				$var=trim("livello_gruppo".$livello_gruppo);
			} else {
				$var="livello_gruppo1";
			};
	
			${$var}="checked";
			
		};
	};
};



if ($id_gruppo_report) {
	$and_gruppo=" AND id_gruppo='$id_gruppo_report'";
};

$query="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' $and_gruppo ORDER BY id_gruppo,id_utente";

$result=$mysqli->query($query);

if ($and_gruppo and !$result->num_rows) {
	$query="SELECT iscrizioni_corso.id_utente,iscrizioni_gruppo_pw.id_gruppo,iscrizioni_corso.livello,iscrizioni_corso.note,iscrizioni_corso.superato FROM iscrizioni_gruppo_pw,iscrizioni_corso WHERE iscrizioni_corso.id_utente=iscrizioni_gruppo_pw.id_utente AND iscrizioni_corso.id_corso=iscrizioni_gruppo_pw.id_corso AND iscrizioni_gruppo_pw.id_edizione=iscrizioni_corso.id_edizione AND iscrizioni_gruppo_pw.id_corso='$id_corso_s' AND iscrizioni_gruppo_pw.id_edizione='$id_edizione_s' AND iscrizioni_gruppo_pw.id_gruppo='$id_gruppo_report' ORDER BY id_gruppo,id_utente";
	$result=$mysqli->query($query);
}

if (!$pag_size) $pag_size=20;
if (!$pagina) $pagina=1;

$tot_righe=$result->num_rows;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;


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
$colore=$colore_sfondo;

echo "
<form action=report_corso_op.php method=post>
<input type=hidden name=id_gruppo_report value=\"$id_gruppo_report\">
<input type=hidden name=valutazione_pw value=\"$valutazione_pw\">
<input type=hidden name=pagina value=\"$pagina\">
<input type=hidden name=pag_size value=\"$pag_size\">
<input type=hidden name=tot_pag value=\"$tot_pag\">
<input type=hidden name=id_corso value=\"$id_corso_s\">
<input type=hidden name=id_edizione value=\"$id_edizione_s\">";

if ($valutazione_pw) {
	echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

echo "
<tr bgcolor=\"$colore_scuro\">
<td>
<span class=testonegativo>
<b>Valutazione Project Work</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>$stringa[livello_competenze]</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>$stringa[note]</b>
</span>
</td>";

echo "</tr>";

	echo "
		<tr  bgcolor=\"$colore\">
		<td valign=top>
		<span class=testopiccolo>
		$descr_gruppo
		</td>

		<td align=left valign=top>
		<span class=testopiccolo>
		1 <input type=radio name=livello_gruppo value=\"1\" $livello_gruppo1>
		2 <input type=radio name=livello_gruppo value=\"2\" $livello_gruppo2>
		3 <input type=radio name=livello_gruppo value=\"3\" $livello_gruppo3>
		4 <input type=radio name=livello_gruppo  value=\"4\" $livello_gruppo4>
		Lode <input type=radio name=livello_gruppo  value=\"5\" $livello_gruppo5>
		</span>
		</td>
		<td align=left valign=top>
		<textarea class=testopiccolo rows=10 cols=70 name=note_gruppo>$note_gruppo</textarea>
		</td>";
		
		
		echo "</tr>
		";

		echo "</table>";
		echo "</td></tr></table>";
};

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

echo "
<tr bgcolor=\"$colore_scuro\">
<td>
<span class=testonegativo>
<b>$stringa[utente]</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>$stringa[gruppo]</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>$stringa[livello_competenze]</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>$stringa[superato_corso]</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>$stringa[note]</b>
</span>
</td>";

echo "</tr>";

$righe=1;
$continua = true;
$colore=$colore_sfondo;

while ($riga=$result->fetch_array()) {

	$id_utente1 = $riga["id_utente"];
	$id_gruppo1 = $riga["id_gruppo"];
	$livello = $riga["livello"];
	$note = $riga["note"];
	$superato=$riga["superato"];
	
	$livello1="";
	$livello2="";
	$livello3="";
	$livello4="";
	$livello5="";
	
	if ($livello) {
		$var=trim("livello".$livello);
	} else {
		$var="livello1";
	};
	
	${$var}="checked";
	
	$superato1="";
	if ($superato=="on") $superato1="checked";
		
	echo "
		<tr  bgcolor=\"$colore\">
		<td valign=top>
		<span class=testopiccolo>
		<b>$progr</b> - 
		<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a></span>
		</td>
		<td valign=top>
		<span class=testopiccolo>$id_gruppo1</span>
		</td>
		<td align=left valign=top>
		<span class=testopiccolo>
		1 <input type=radio name=livello[".$id_utente1."] value=\"1\" $livello1>
		2 <input type=radio name=livello[".$id_utente1."] value=\"2\" $livello2>
		3 <input type=radio name=livello[".$id_utente1."]  value=\"3\" $livello3>
		4 <input type=radio name=livello[".$id_utente1."]  value=\"4\" $livello4>
		Lode <input type=radio name=livello[".$id_utente1."]  value=\"5\" $livello5>
		</span>
		</td>
		<td valign=top>
		<input type=checkbox name=superato[".$id_utente1."]  $superato1>
		</td>
		<td align=left valign=top>
		<textarea class=testopiccolo rows=8 cols=60 name=note[".$id_utente1."]>$note</textarea>
		</td>";
		
		
		echo "</tr>
		";
	
	$righe++;
	$progr++;
	
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};

};
echo "
</table>
</td></tr></table>
<br>
<input type=submit value=\"$stringa[salva]\">
</form>
";

echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?risorsa=report_corso&&id_corso=$id_corso_s&id_edizione=$id_edizione_s&pagina=$i&pag_size=$pag_size&id_gruppo_report=$id_gruppo_report>$i</a>]
		";
	};
	$i++;
};
echo "</span><br>";	
?>
</td></tr></table>
<br>

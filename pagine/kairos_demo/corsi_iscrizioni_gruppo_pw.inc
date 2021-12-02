<?php
$id_gruppo=$_REQUEST["id_gruppo"];
$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];
$id_gruppo=$_REQUEST["id_gruppo"];

$query="SELECT descrizione FROM corso WHERE id_corso='$id_corso' LIMIT 1";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$descrizione_corso=$riga["descrizione"];

$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione;


$n_attesa=0;
$n_classe=0;

$elenco_attesa="";
$query = "SELECT utenti.id_utente,utenti.nome,utenti.cognome FROM iscrizioni_corso,utenti WHERE iscrizioni_corso.id_utente=utenti.id_utente AND id_corso='$id_corso' AND id_edizione='$id_edizione' ORDER BY id_utente";
$result=$mysqli->query($query);

while ($utente = $result->fetch_array()) {
	$id_utente = $utente["id_utente"];
	$query_1="SELECT id_utente FROM iscrizioni_gruppo_pw WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_utente='$id_utente' AND id_gruppo='$id_gruppo'";
	$result_1=$mysqli->query($query_1);
	if (!$result_1->num_rows) {
		$nome = $utente["nome"];
		$cognome = $utente["cognome"];
	
		$n_attesa++;	
		$elenco_attesa .= "<option value=$id_utente>$nome $cognome ($id_utente) </option>\n";
	};
};
	
$elenco_classe="";
$query = "SELECT utenti.id_utente,utenti.nome,utenti.cognome FROM iscrizioni_gruppo_pw,utenti WHERE iscrizioni_gruppo_pw.id_utente=utenti.id_utente AND id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_gruppo='$id_gruppo' ORDER BY id_utente";
$result=$mysqli->query($query);

while ($utente = $result->fetch_array()) {
	$id_utente = $utente["id_utente"];
	$nome = $utente["nome"];
	$cognome = $utente["cognome"];
	
	$n_classe++;
	$elenco_classe .= "<option value=$id_utente>$nome $cognome ($id_utente) </option>\n";
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_index><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso&id_edizione=$id_edizione><span class=testo><b>$stringa[corso]:</b> $descrizione_corso: $descr_edizione</span></a>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_gruppi])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_gruppo]).": $id_gruppo</b></span>
</td></tr>



<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

echo "
<table border=0 width=90%>
";

echo "
<tr>
<td>
<form action=corsi_iscrizioni_gruppo_pw_op.php method=post>
<input type=hidden name=id_gruppo value=\"$id_gruppo\">
<input type=hidden name=id_corso value=\"$id_corso\">
<input type=hidden name=id_edizione value=\"$id_edizione\">

<table border=0>

<tr>
<td width=300 valign=top>
<span class=testopiccolo>
$stringa[utenti_attesa_pw] ($n_attesa)</span>
</td>
<td width=10>&nbsp;</td>
<td width=300 valign=top>
<span class=testopiccolo>$stringa[utenti_iscritti_pw] ($n_classe) </span>
</td>
</tr>

<tr>
<td width=300 valign=top>
<select multiple name=elenco_attesa[] size=10>
$elenco_attesa
</select>
</td>
<td valign=top width=10 valign=top>
<input type=submit name=aggiungi value=\">>\">
<br>
<input type=submit name=rimuovi value=\"<<\">
</td>
<td width=300 valign=top>
<select multiple name=elenco_classe[] size=10>
$elenco_classe
</select>
</td>
</tr>
</table>


</form>
</td>
</tr>
\n";
echo "</table>";
echo "</td></tr></table><br>";
?>

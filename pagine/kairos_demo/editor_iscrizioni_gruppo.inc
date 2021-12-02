<?php
$id_editor_gruppo=$_REQUEST["id_editor_gruppo"];
$query = "SELECT descrizione FROM editor_gruppo WHERE id_editor_gruppo='$id_editor_gruppo'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$descrizione=$riga["descrizione"];

$n_attesa=0;
$n_classe=0;

$elenco_attesa="";
/*
$query = "SELECT utenti.id_utente,utenti.nome,utenti.cognome FROM utenti LEFT JOIN editor_gruppo_utenti ON utenti.id_utente=editor_gruppo_utenti.id_utente WHERE (stato='2' or stato='3') AND (editor_gruppo_utenti.id_editor_gruppo IS NULL OR  editor_gruppo_utenti.id_editor_gruppo <> '$id_editor_gruppo' ) ORDER BY utenti.id_utente";
*/

$query = "SELECT utenti.id_utente,utenti.nome,utenti.cognome FROM utenti WHERE (stato='2' or stato='3') ORDER BY utenti.id_utente";
$result=$mysqli->query($query);


while ($utente = $result->fetch_array()) {
	$id_utente = $utente["id_utente"];
	$nome = $utente["nome"];
	$cognome = $utente["cognome"];
	
	$n_attesa++;	
	$elenco_attesa .= "<option value=$id_utente>$nome $cognome ($id_utente) </option>\n";
};
	
$elenco_classe="";
$query = "SELECT utenti.id_utente,utenti.nome,utenti.cognome FROM editor_gruppo_utenti,utenti WHERE editor_gruppo_utenti.id_utente=utenti.id_utente AND id_editor_gruppo='$id_editor_gruppo' ORDER BY id_utente";
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
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[editor_gruppi])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_gruppo]).": $descrizione</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";	


echo "<table border=0 width=90%>";
echo "
<tr>
<td>
<form action=editor_iscrizioni_gruppo_op.php method=post>
<input type=hidden name=id_editor_gruppo value=\"$id_editor_gruppo\">

<table border=0>

<tr>
<td width=300 valign=top>
<span class=testopiccolo>
$stringa[editor_attesa] ($n_attesa)</span>
</td>
<td width=10>&nbsp;</td>
<td width=300 valign=top>
<span class=testopiccolo>$stringa[editor_iscritti] ($n_classe) </span>
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

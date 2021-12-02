<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";
$id_utente_cerca=$_REQUEST["id_utente_cerca"];
$nome=$_REQUEST["nome"];
$cognome=$_REQUEST["cognome"];
$citta=$_REQUEST["citta"];
$prov=$_REQUEST["prov"];
$stato=$_REQUEST["stato"];
$gruppo=$_REQUEST["gruppo"];
$cerca_in=$_REQUEST["cerca_in"];
$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];


$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>

<tr>
<td class=titolodot>".strtoupper($stringa[cerca_utenti])."</td>
</tr>";


echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";


echo "
<tr><td>
";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query1 = " utenti.id_utente<>'garamond' ";

// creo la condizione where

$id_utente_cerca=trim($id_utente_cerca);
	
if ($id_utente_cerca) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (utenti.id_utente='$id_utente_cerca') ";
};

if ($nome) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (nome LIKE '$nome%') ";
};

if ($cognome) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (cognome LIKE '$cognome%') ";
};

if ($citta) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (citta LIKE '$citta%') ";
};

if ($prov) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (prov LIKE '$prov%') ";
};


if ($stato<>9) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (stato = $stato) ";
};

if ($cerca_in=="tutto") {
	$query = "SELECT id_utente,cognome,nome FROM utenti";
	if ($query1) $query .= " WHERE $query1 "; 
	$query .= " ORDER BY utenti.cognome";
} else {
	if ($gruppo=="qualunque") {
		$query = "SELECT utenti.id_utente,cognome,nome FROM utenti,iscrizioni_corso WHERE utenti.id_utente=iscrizioni_corso.id_utente AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
	} else {
		$query = "SELECT utenti.id_utente,cognome,nome FROM utenti,iscrizioni_corso WHERE utenti.id_utente=iscrizioni_corso.id_utente AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$gruppo'";
	}	

	if ($query1) $query .= " AND $query1 "; 
	$query .= " ORDER BY utenti.cognome";
};

$result=$mysqli->query($query);

$tot_righe=$result->num_rows;

if (!$tot_righe) {
	echo "<p><span class=testo>$stringa[non_trovato]</span></p>";
	exit();
};

$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;

echo "


<TABLE BORDER=0 cellspacing=2 cellpadding=2>
<tr>
<td><span class=testo><b>$stringa[num]</b></span></td>
<td><span class=testo><b>$stringa[utente]</b></span></td>
<td></td>
</tr>";

$righe=1;
while ($utente=$result->fetch_array()) {
	$id_utente=$utente["id_utente"];
	$nome_utente = $utente["nome"]." ".$utente["cognome"];
			
	echo "<tr>";
	printf ("<td><span class=testopiccolo>%s</span></td>",$progr);

	echo "<td>
	<span class=testopiccolo>
	<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">($id_utente) $nome_utente</a>
	</span>
	</td>";	
	
	echo "
	<td><a class=miolink href=\"javascript:;\" title=\"$stringa[manda_messaggio]\" onclick=\"javascript:apri_scheda('form_messaggio_scrivi.php?id_utente=$id_utente',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\"><img src=img/envelope.gif width=14 height=10 border=0></a>";

	echo "
	</td>
	</tr>";

	$righe++;
	$progr++;
	
};      
?>		
</td></tr>
</table><br>
<?php
echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?risorsa=cerca_utenti&pagina=$i&pag_size=$pag_size&id_utente_cerca=$id_utente_cerca&nome=$nome&cognome=$cognome&citta=$citta&prov=$prov&stato=$stato&cerca_in=$cerca_in&gruppo=$gruppo>$i</a>]
		";
	};
	$i++;
};
echo "</span><br>";	
?>
</td></tr>
</table>
<br>
<!-- FINE CONTENUTO DELLA PAGINA -->
<?php

echo "</div>
</div>
</div>
</div>
</div>";

?>
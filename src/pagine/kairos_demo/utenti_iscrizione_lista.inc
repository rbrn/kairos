<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

?>
<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_utenti])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[iscrizione_utenti])."</b></span>
</td></tr>

";


echo "
<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=utenti_iscrizione_cerca\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=utenti_iscrizione_cerca\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";


echo "<tr><td>";
?>

<?php
$id_utente_cookie=$kairos_cookie[0];
$id_utente_cerca=$_REQUEST["id_utente_cerca"];
$nome=$_REQUEST["nome"];
$cognome=$_REQUEST["cognome"];
$stato=$_REQUEST["stato"];
$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];


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

	$elenco_corsi .= "<option value=\"$id_corso $id_edizione\">$descr_corso2 -  $descr_edizione2";

};


$query = "SELECT id_utente,cognome,nome,stato FROM utenti ";
$query1 = " id_utente<>'garamond' ";

// creo la condizione where
	
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

//stato
if ($stato<>9) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (stato = $stato) ";
};
	
		
if ($query1) $query .= " WHERE ".$query1;

$query .= " ORDER BY id_utente";
	
//echo $query."<br>";

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
echo "<br><span class=testo>$stringa[utenti_trovati]: <b>$num</b></span><br>";

echo "
<form action=utente_modifica_ruolo.php method=post name=modulo id=modulo>
<span class=testo>$stringa[corso]: </span>
<select name=id_corso_edizione_form>
$elenco_corsi
</select>
<span class=testo>$stringa[iscrivi_utenti_selezionati]</span>
<input type=submit name=iscrivi_utenti value=\"$stringa[ok]\">
</p>";

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=0 cellspacing=0 bgcolor=\"white\" >
<tr><td>";

echo "
<table border=0 cellpadding=5 cellspacing=1>
<tr bgcolor=\"$colore_scuro\">
<td>&nbsp;</td>
<td bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[num]</b></span></td>
<td bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[id_utente]</b></span></td>
<td bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[cognome]</b></span></td>
<td bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[nome]</b></span></td>
<td bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[stato]</b></span></td>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>";


$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;

$righe=1;
$continua = true;
$colore=$colore_sfondo;

while ($riga=$result->fetch_array()) {
	echo "<tr  bgcolor=\"$colore\">";
	
	$stato_c=$riga["stato"];
	
	switch ($stato_c) {
		case 0:
			$ruolo=$stringa[registrato_attesa];
			break;
			
		case 1:
			$ruolo=$stringa[utente];
			break;
			
		case 2:
			$ruolo=$stringa[staff];
			break;
			
		case 3:
			$ruolo=$stringa[admin];
			break;
		
	};
	
	$dati_tutor_fortic="";
	if ($cod_area=="kairos_fortic") {
		$query_f="SELECT * FROM tutor_fortic WHERE id_utente='$riga[id_utente]'";
		$result_f=$mysqli->query($query_f);
		$riga_f=$result_f->fetch_array();
		if ($riga_f) {
			$dati_tutor_fortic="(tutor ForTIC presso: $riga_f[scuola])";
		};
	};
			
	printf ("<td><input type=checkbox name=id_u[] value=\"%s\"></td>",$riga["id_utente"]);
	printf ("<td><span class=testo>%s</span></td>",$progr);
	printf ("<td><span class=testo>%s %s</span></td>",$riga["id_utente"],$dati_tutor_fortic);
	printf ("<td><span class=testo>%s</span></td>",$riga["cognome"]);
	printf ("<td><span class=testo>%s</span></td>",$riga["nome"]);
	printf ("<td><span class=testo>%s</span></td>",$ruolo);
	if ($riga["id_utente"]<>'fleo' or $id_utente_cookie=='fleo') {
		if ($id_utente_cookie=='fleo' or $cod_area<>'kairos_demo') {
			echo "<td><a href='javascript:scheda_utente(\"$riga[id_utente]\")' onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$riga[id_utente]','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$riga[id_utente]\"></a></td>";

			echo "<td><a href=index.php?risorsa=msg&msg=conf_canc&pagina=utente_cancella.php&id_utente=$riga[id_utente] onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$riga[id_utente]','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$riga[id_utente]\"></a></td>\n";
		};
	} else {
		echo "<td></td><td></td>";
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

<?php
echo "</td></tr></table>"; 
echo "<input type=button value=\"$stringa[seleziona_tutti]\" onClick=\"SetAllCheckBoxes('modulo','id_u[]',true)\"> <input type=button value=\"$stringa[deseleziona]\" onClick=\"SetAllCheckBoxes('modulo','id_u[]',false)\">";
echo "</td></tr></table>"; 
?>

</form>	
<br>
<?php
echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?risorsa=utenti_iscrizione_lista&pagina=$i&pag_size=$pag_size&id_utente_cerca=$id_utente_cerca&nome=$nome&cognome=$cognome&stato=$stato>$i</a>]
		";
	};
	$i++;
};
echo "</span><br>";	
?>
</td></tr></table>
<br>


<?php

echo "</div>
</div>
</div>
</div>
</div>";

?>

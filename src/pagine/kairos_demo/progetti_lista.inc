<?php
$query_string=$_SERVER["QUERY_STRING"];
$query_string=ereg_replace("pagina=([0-9]+)&","",$query_string);

require "./pagine/$cod_area/argomenti.inc";
$classe_str[1]="Prima";
$classe_str[2]="Seconda";
$classe_str[3]="Terza";
$classe_str[4]="Quarta linguaggi";
$classe_str[5]="Quarta discipline";
$classe_str[6]="Quinta linguaggi";
$classe_str[7]="Quinta discipline";

if ($cod_area=="kairos_amicosole") {
	$titolo="CONTRIBUTI AMICO SOLE";
};

if ($cod_area=="kairos_oppla") {
	$titolo="CONTRIBUTI OPPLA'";
};


if ($cod_area=="kairos_bandaingamba") {
	$titolo="CONTRIBUTI BANDA IN GAMBA'";
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>

<tr>
<td valign=top width=100%><span class=titolopagina>$titolo</span>
</td></tr>";


echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>&nbsp;&nbsp;
<span class=testopiccolo><a href=\"index.php?risorsa=progetti_cerca\">Nuova ricerca</a></span>
</td></tr>";


echo "<tr><td>";
?>

<?php
$titolo=trim($_REQUEST["titolo"]);
$autori=$_REQUEST["descrizione"];
$nome_scuola=$_REQUEST["nome_scuola"];
$citta_scuola=$_REQUEST["citta_scuola"];
$prov_scuola=$_REQUEST["prov_scuola"];
$regione_scuola=$_REQUEST["regione_scuola"];
$classe=$_REQUEST["classe"];
$unita=$_REQUEST["unita"];
$stato_progetto=$_REQUEST["stato_progetto"];
$tipo=$_REQUEST["tipo"];

$query = "SELECT * FROM progetti ";
$query1 = "";

$stringa_cerca="";
// creo la condizione where


if (!$stato_progetto) $stato_progetto='2';

if ($stato_progetto) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (stato='$stato_progetto') ";
};

	
if ($titolo) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (titolo LIKE '$titolo%') ";
	$stringa_cerca .="Titolo inizia per: <b>$titolo</b><br>";
};

if ($tipo) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (tipo='$tipo') ";
	$stringa_cerca .="Tipologia di materiale: <b>$tipo</b><br>";
};

if ($autori) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (autori LIKE '%$autori%') ";
	$stringa_cerca .="Nome degli autori inizia per: <b>$autori</b><br>";
};

if ($nome_scuola) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (nome_scuola LIKE '$nome_scuola%') ";
	$stringa_cerca .="Nome della scuola inizia per: <b>$nome_scuola</b><br>";
};

if ($citta_scuola) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (citta_scuola LIKE '$citta_scuola%') ";
	$stringa_cerca .="CittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ della scuola inizia per: <b>$citta_scuola</b><br>";
};

if ($prov_scuola<>"XX") {
	if ($query1) $query1 .= "AND";
	$query1 .= " (prov_scuola = '$prov_scuola') ";
	$stringa_cerca .="Provincia della scuola: <b>$prov_scuola</b><br>";
};

if ($regione_scuola<>"XX") {
	if ($query1) $query1 .= "AND";
	$query1 .= " (regione_scuola = '$regione_scuola') ";
	$stringa_cerca .="Regione della scuola: <b>$regione_scuola</b><br>";
};


if ($classe<>"XX") {
	if ($query1) $query1 .= "AND";
	$query1 .= " (classe = '$classe') ";
	$stringa_cerca .="Materiali della classe: <b>$classe_str[$classe]</b><br>";
};

if ($unita<>"XX") {
	if ($query1) $query1 .= "AND";
	$query1 .= " (unita = '$unita') ";
	$arg_str=$argomento[$classe][$unita];
	$stringa_cerca .="Argomento: <b>$arg_str</b><br>";
};


if ($query1) $query .= " WHERE ".$query1;

$query .= " ORDER BY data_upload";
	
//echo $query."<br>";

$result=$mysqli->query($query);


if (!$pag_size) $pag_size=10;
if (!$pagina) $pagina=1;

$tot_righe=$result->num_rows;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$num =$tot_righe;
echo "<br><span class=testo>Contributi trovati: <b>$num</b></span>";

if ($stringa_cerca) {
echo "<span class=testo>,&nbsp;in base ai seguenti criteri di ricerca: <br>$stringa_cerca</span><br><br>";
} else {
	echo "<br><br>";
};

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=0 cellspacing=0 bgcolor=\"white\" >
<tr><td>";

echo "
<table border=0 cellpadding=5 cellspacing=1>";

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;

$righe=1;
$continua = true;
$colore=$colore_sfondo;

while ($riga=$result->fetch_array()) {
	$id_progetto=$riga["id_progetto"];
	$titolo1=$riga["titolo"];
	$id_utente1=$riga["id_utente"];
	$autori1=$riga["autori"];
	$nome_scuola1=$riga["nome_scuola"];
	$citta_scuola1=$riga["citta_scuola"];
	$prov_scuola1=$riga["prov_scuola"];
	$regione_scuola1=$riga["regione_scuola"];
	$classe1n=$riga["classe"];
	$classe1=$classe_str[$classe1n];
	$unita1=$riga["unita"];
	$stato1=$riga["stato"];
	$tipo1=$riga["tipo"];
	
	if ($unita1<>"lab" and $unita1<>"mat") {
		$unita1=$argomento[$classe1n][$unita1];
	} else {
		if ($unita1=="lab") $unita1="Laboratori espressivi";
		if ($unita1=="mat") $unita1="Matematica";
	};
	$allegato1=$riga["allegato"];
	$allegato_size1=$riga["allegato_size"];
	
	echo "<tr bgcolor=\"$colore\">";
	echo "
	<td><table border=0>
	<tr>
  <td><img src=\"img/kairos_amicosole/file.gif\" width=\"38\" height=\"20\" alt=\"\" border=\"0\"><span class=testo><b>File da scaricare:</b><span></td>
 <td valign=bottom><span class=testo><a href=progetti_scarica.php?id_progetto=$id_progetto>$allegato1</a> (".stringa_filesize($allegato_size1).")</span></TD>
	</TR>";
	
	if ($ruolo=="admin" or $ruolo=="staff") {
	echo "
	<tr>
	 <td align=right><span class=testo><b>Responsabile:</b><span></td>
	<td valign=bottom>
	<span class=testo>
	<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a>
	</span>
	</td>
	</tr>";
	};
	
	
	echo "
	<tr>
	<td align=right><span class=testo><b>Titolo:</b><span></td>
	<td valign=bottom><span class=testo>$titolo1</span></td>
	</tr><tr>
	<tr>
	<td align=right><span class=testo><b>Tipo:</b><span></td>
	<td valign=bottom><span class=testo>$tipo1</span></td>
	</tr><tr>
	<td align=right><span class=testo><b>Autori:</b><span></td>
	<td valign=bottom><span class=testo>$autori1</span></td>
	</tr><tr>
	<td align=right><span class=testo><b>Classe:</b><span></td>
	<td valign=bottom><span class=testo>$classe1</span></td>
	</tr><tr>
	<td align=right><span class=testo><b>Argomento:</b><span></td>
	<td valign=bottom><span class=testo>$unita1</span></td>
	</tr><tr>
	<td align=right><span class=testo><b>Scuola:</b><span></td>
	<td valign=bottom><span class=testo>$nome_scuola1</span></td>
	</tr><tr>
	<td align=right><span class=testo><b>CittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½:</b><span></td>
	<td valign=bottom><span class=testo>$citta_scuola1</span></td>
	</tr><tr>
	<td align=right><span class=testo><b>Prov.:</b><span></td>
	<td valign=bottom><span class=testo>$prov_scuola1</span></td>
	</tr><tr>
	<td align=right><span class=testo><b>Regione:</b><span></td>
	<td valign=bottom><span class=testo>$regione_scuola1</span></td>
	</tr>";
	if ($id_utente1==$id_utente or $ruolo=="admin" or $ruolo=="staff") {
		echo "
		<tr>
		<td>&nbsp;</td>
		<td align=right>
		<span class=testo>[<a href=index.php?risorsa=progetti_file_form_mod&id_progetto=$id_progetto>Modifica</a>] [<a href=index.php?risorsa=msg&msg=conf_canc&pagina=progetti_cancella.php&id_progetto=$id_progetto>Cancella</a>]";

		if (($ruolo=="admin" or $ruolo=="staff") and $stato1=="1") {
		
			echo "&nbsp;[<a href=progetti_approva.php?id_progetto=$id_progetto>Approva</a>]";
		
		};
		

		echo "</span></td></tr>";
	};
	
	echo "
	</table>";
	echo "</td></tr>\n";
	$righe++;
	$progr++;
	
	if ($colore==$colore_sfondo) {
		$colore="#ffffcc";
	} else {
		$colore=$colore_sfondo;
	};
};


?>
		
</table>

<?php
echo "</td></tr></table>"; 
echo "</td></tr></table>"; 
?>
</form>	

<?php
echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?pagina=$i&$query_string>$i</a>]
		";
	};
	$i++;
};
echo "</span><br>";	
?>
</td></tr></table>
<br>

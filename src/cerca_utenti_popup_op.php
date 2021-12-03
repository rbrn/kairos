<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente1=$kairos_cookie[0];

if (!$id_utente1) {
	echo "
	<html>
	<head><title>$stringa[errore]</title>
	<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
	<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
	</HEAD>
	<BODY bgcolor=$colore_sfondo>
	<span class=testo>$stringa[errore_no_login]</span>
	</body>
	</html>";
	exit();
};

?>


<html>
<head>
<title><?php echo($stringa[cerca]);?></title>
<?php 
echo "
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">";
echo"
<script language=\"JavaScript\">
	function assegna_id(id) {
		self.close();
		opener.document.modulo.$campo.value=id;
		opener.focus();
	};
</script>
";

?>
</head>
<BODY bgcolor=<?php echo($colore_sfondo_neutro);?> topmargin="0" leftmargin="0">
<table border=0 width=100% cellpadding=5 bgcolor=<?php echo($colore_scuro_neutro);?>>
<tr><td>
<span class=testo><b><?php echo($stringa[cerca_utenti]);?></b></span></td>
</tr>
</table>

<?php

$ruolo=$_REQUEST["ruolo"];
$campo=$_REQUEST["campo"];

$stato_q="";
switch($ruolo) {
	case 'staff':
		$stato_q="(stato='2' or stato='3')";
		break;
	
	case 'tutti':
		$stato_q="";
		break;
	
	case 'corsisti':
		$stato_q="(stato='1')";
		break;
};

$id_utente_cerca=$_REQUEST["id_utente_cerca"];
$nome=$_REQUEST["nome"];
$cognome=$_REQUEST["cognome"];
$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];

if (!$pagina) $pagina=1;
if (!$pag_size) $pag_size=20;

if ($kairos_cookie[9]) $DBASE_UTENTI="atlante";

mysql_select_db($DBASE_UTENTI,$db);		

$query1 = " utenti.id_utente<>'garamond' ";

// creo la condizione where

$id_utente_cerca=trim($id_utente_cerca);
	
if ($id_utente_cerca) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (utenti.id_utente LIKE '$id_utente_cerca%') ";
};

if ($nome) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (nome LIKE '$nome%') ";
};

if ($cognome) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (cognome LIKE '$cognome%') ";
};


if ($stato_q) {
	if ($query1) $query1 .= "AND";
	$query1 .= " $stato_q ";
};

$query = "SELECT id_utente,cognome,nome FROM utenti";
if ($query1) $query .= " WHERE $query1 "; 
$query .= " ORDER BY utenti.cognome";


$result = $mysqli->query($query);
$tot_righe=$result->num_rows;

if (!$tot_righe) {
	echo "<p><span class=testo>$stringa[non_trovato]</span></p>";
	exit();
};

$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result = $mysqli->query($query);
$progr=$inizio+1;

echo "
<TABLE BORDER=0 cellspacing=2 cellpadding=2>
<tr>
<td><span class=testo><b>$stringa[num]</b></span></td>
<td><span class=testo><b>$stringa[utente]</b></span></td>
<td></td>
</tr>";

$righe=1;
$continua = true;
while ($utente=$result->fetch_array()) {
	$id_utente=$utente["id_utente"];
	$nome_utente = $utente["nome"]." ".$utente["cognome"];
			
	echo "<tr>";
	echo "<td><span class=testopiccolo>$progr</span></td>";

	echo "<td>
	<span class=testopiccolo>
	<a href=\"javascript:;\" onclick=\"assegna_id('$id_utente')\">($id_utente) $nome_utente</a>
	</span>
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
		[<a href=cerca_utenti_popup_op.php?ruolo=$ruolo&campo=$campo&pagina=$i&pag_size=$pag_size&id_utente_cerca=$id_utente_cerca&nome=$nome&cognome=$cognome>$i</a>]
		";
	};
	$i++;
};
echo "</span><br>";	
?>
<br>
<!-- FINE CONTENUTO DELLA PAGINA -->

</body>
</html>

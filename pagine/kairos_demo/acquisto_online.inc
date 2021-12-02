<?php
$cod_prodotto=$_REQUEST["cod_prodotto"];
$prezzo=$_REQUEST["prezzo"];
$causale=$_REQUEST["causale"];

mysql_select_db($DBASE_UTENTI,$db);

//parametri di chiamata:
// cod_prodotto = codice articolo da aggiungere 
if ($cod_prodotto<>"saldo") {
	$query = "SELECT * FROM prodotto WHERE cod_prodotto='$cod_prodotto'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();

	$descrizione = $riga["descrizione"];
	$prezzo = $riga["prezzo"];
} else {
	$descrizione=$causale;
};

$prezzo=trim(ereg_replace(",",".",$prezzo));

if (!is_numeric($prezzo)) {
	$prezzo=0;
};

$prezzo=floor($prezzo);

$numero=number_format($prezzo, 2, ',','.');

if ($numero=='0,00') {
	echo "
	<p>
	<TABLE BORDER=0 ALIGN=CENTER width=80%>
	<tr>
	<td>
	<span class=testo>
	Per favore controlla l'importo, deve contenere solo cifre numeriche e deve essere diverso da zero. Grazie.
	<br>
	[<a href=javascript:history.back()>Indietro</a>]
	</span>
	</td></tr>
	</table>
	</p>";
} else {

$query = "SELECT * FROM utenti WHERE id_utente='$id_utente'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

$nome = $riga["nome"];
$cognome = $riga["cognome"];
$email = $riga["email"];
$indirizzo = $riga["indirizzo"];
$cap = $riga["cap"];
$citta = $riga["citta"];
$prov = $riga["prov"];
$telefono = $riga["telefono"];


$query = "LOCK TABLES cod_acquisto WRITE";
$result=$mysqli->query($query);
$query = "select * from cod_acquisto";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

$cod_ric = $riga["codice"];
$query = "delete from cod_acquisto where codice='$cod_ric'";
$result=$mysqli->query($query);

$query = "UNLOCK TABLES";
$result=$mysqli->query($query);

if ($cod_prodotto=="saldo") {
$msg="Notifica Pagamento online da:\n
Identificativo: $id_utente
Cognome: $cognome
Nome: $nome
Indirizzo: $indirizzo
CAP: $cap
CittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½: $citta
Prov: $prov
Telefono: $telefono
E-mail: $email
Causale: $descrizione
Importo: $numero Euro
--------------------------------------------------------------------";

//mando la mail di notifica
mail("ordini@garamond.it","Pagamento online aperto","$msg","From:$email\nReply-To:$email");
};

echo "
<p>
<TABLE BORDER=0 ALIGN=CENTER width=80%>
<tr>
<td>
<span class=testo>Pagamento Ordine OnLine di: <b>$nome $cognome (<i>$id_utente</i>)</b></span>
<p>\n";

echo "<table border=1 width=600 cellpadding=5>";
echo "<tr>\n
<td align=left width=440><b><span class=testo>Descrizione</span></b></td>\n
<td align=right width=40><b><span class=testo>Prezzo</span></b></td>\n
</tr>\n";
echo "<tr>";
echo "<td align=left width=440><span class=testo>$descrizione</span></td>\n";		
echo "<td align=right width=40><span class=testo>Euro <b>$numero</b></span></td>";
echo "</tr>\n";
echo "</table>\n";

$totale = $prezzo;
echo "
<br>
<span class=testo><b>I tuoi dati</b></span>
<br>
<br>
<table border=0>
<tr>
<td><span class=testo><b>Cognome:</b></span>
</td>
<td>\n";
echo "<span class=testo>$cognome</span>\n";
echo "</td></tr>\n";
echo "<tr>
<td><span class=testo><b>Nome:</b></span></td>
<td><span class=testo>$nome</span>\n";
echo "</td></tr>";
echo "<tr>
<td><span class=testo><b>E-Mail:</b></span></td>
<td><span class=testo>$email</span>\n";
echo "</td></tr>";
echo "<tr>
<td><span class=testo><b>Indirizzo:</b></span></td>
<td><span class=testo>$indirizzo</span>\n";
echo "</td></tr>";
echo "<tr>
<td><span class=testo><b>CAP:</b></span></td>
<td><span class=testo>$cap</span>\n";
echo "</td></tr>";
echo "<tr>
<td><span class=testo><b>CittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½:</b></span></td>
<td><span class=testo>$citta</span>\n";
echo "</td></tr>";
echo "<tr>
<td><span class=testo><b>Prov.:</b></span></td>
<td><span class=testo>$prov</span></td></tr>\n";
echo "<tr>
<td><span class=testo><b>Telefono:</b></span></td>
<td><span class=testo>$telefono</span>\n";
echo "</td></tr>";
echo "</table>";

$importo = $totale*32720951;
$operazione = $cod_prodotto."-".$id_utente; 


echo "<table border=0 cellpadding=5 cellspacing=10 align=center>\n";
echo "<tr bgcolor=#ffffcc><td align=center>
<span class=testo><b>Conferma per proseguire su Banca Sella per l'inserimento dei dati relativi alla tua Carta di Credito (VISA/MASTERCARD)</b></span>";

echo "<form action=https://ecomm.sella.it/pagam.asp method=post>";
echo "
<input type=hidden name=a value=9003775>
<input type=hidden name=b value=$importo>
<input type=hidden name=c value=$cod_ric>
<input type=hidden name=d value=$operazione>";
printf("<input type=submit value=\"%s\">","OK");
echo "</form>\n";
echo "

<span class=testo><b>Nota:</b> <i>ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ una modalitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ di pagamento rapida e sicura. E' effettuata in collaborazione con Banca Sella, garantendo massima affidabilitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ e riservatezza.</i></span></td></tr>\n";

echo "</table>
</td></tr>
</table>
\n";
};
?>

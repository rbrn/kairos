<?php


$id_lo=$_REQUEST["id_lo"];

$pag_size=$_REQUEST["pag_size"];
$pagina=$_REQUEST["pagina"];
$filtro=$_REQUEST["filtro"];
$titolo_cerca=trim($_REQUEST["titolo_cerca"]);
$materia_cerca=trim($_REQUEST["materia_cerca"]);


?>

<?php 

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>Acquista Learning Object</td></tr>";


echo "<tr><td>";



	mysql_select_db($DBASE,$db);	
	$query="SELECT * FROM lo_repository WHERE id_lo='$id_lo'";
	$result=$mysqli->query($query);
	
	$riga_lo=$result->fetch_array();
	
	$titolo=$riga_lo["titolo"];
	$materia=$riga_lo["materia"];
	
	$query="SELECT * FROM utenti WHERE id_utente='$kairos_cookie[0]'";
	$result=$mysqli->query($query);
	
	$riga_ut=$result->fetch_array();
	$nome=$riga_ut["nome"];
	$cognome=$riga_ut["cognome"];
	$email=$riga_ut["email"];
	
	$query="INSERT INTO lo_purchase SET
	id_utente='$kairos_cookie[0]',
	id_lo='$id_lo',
	data_ordine=NOW(),
	stato_ordine='1'";
	$mysqli->query($query);
	
	$msg = "
	Il seguente utente ha ordinato il Learning Object: $titolo ($materia)
	
	id_utente: $id_utente
	nome: $nome
	cognome: $cognome
	
	L'ordine e' in attesa di conferma.
	
	";
	
	$msg=stripslashes($msg);

	$id_package=uniqid("");	
	mail_job($id_package,"ordini@garamond.it","Ordine Learning Object","$msg","ordini@garamond.it","ordini@garamond.it","");

	$msg = "
	Gentile $nome $cognome,
	
	grazie per aver ordinato il Learning Object: $titolo ($materia)
	
	Riceverai al tuo email nel giro di 24 ore conferma dell'acquisto.

	L'amministrazione
	
	";
	
	$msg=stripslashes($msg);

	mail_job($id_package,"$email","Ordine Learning Object","$msg","ordini@garamond.it","ordini@garamond.it","");
	
	echo "
	<table border=0 width=500>
	<tr><td>
	<p><span class=\"testo\">Acquisto del learning object: <b>$titolo</b> ($materia)</span></p>
	
	<p><span class=\"testo\">L'ordine &egrave; stato  inoltrato all'amministrazione che provveder&agrave; nel giro di 24 ore a confermarlo, ricevendone notifica al tuo email: <b>$email</b></span></p>
	
	</td></tr>
	</table>
	
	</td></tr>";
	
	echo "
<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=lo_repository&pagina=$i&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=lo_repository&pagina=$i&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">Torna al Repository di Learning Object</a></span>";
echo "</td></tr>";
?>


</td></tr></table>
<br>



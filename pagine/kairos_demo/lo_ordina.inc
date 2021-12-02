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
<td valign=top width=100% class=titolodot>Acquista Learning Object</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=lo_repository&pagina=$i&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=lo_repository&pagina=$i&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">Indietro</a></span>";
echo "</td></tr>";


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
	
	$email=$riga_ut["email"];
	
	
	echo "
	<table border=0 width=500>
	<tr><td>
	<p><span class=\"testo\">Acquisto del learning object: <b>$titolo</b> ($materia)</span></p>
	
	<p><span class=\"testo\">L'ordine sar&agrave; immediatamente inoltrato all'amministrazione che provveder&agrave; nel giro di 24 ore a confermarlo, ricevendone notifica al tuo email: <b>$email</b></span></p>
	
	<p><span class=\"testo\"><a href=\"index.php?risorsa=lo_ordina_conferma&id_lo=$id_lo&pagina=$i&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro\"><b>Conferma l'acquisto</b></a>
	</td></tr>
	</table>";
?>


</td></tr></table>
<br>



<?php
$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];
$filtro=$_REQUEST["filtro"];
$titolo_cerca=trim($_REQUEST["titolo_cerca"]);
$materia_cerca=trim($_REQUEST["materia_cerca"]);


?>

<?php 

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>Ordini Learning Object in attesa di conferma</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=lo_repository&pagina=$i&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=lo_repository&pagina=$i&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">Indietro</a></span>";
echo "</td></tr>";


echo "<tr><td>";

mysql_select_db($DBASE,$db);	


echo "
<tr><td valign=top>";

echo "
<form action=lo_ordini_attesa_op.php method=post name=modulo id=modulo>
<input type=\"hidden\" name=\"pagina\" value=\"$pagina\">
<input type=\"hidden\" name=\"pag_size\" value=\"$pag_size\">
<input type=\"hidden\" name=\"filtro\" value=\"$filtro\">
<input type=\"hidden\" name=\"titolo_cerca\" value=\"$titolo_cerca\">
<input type=\"hidden\" name=\"materia_cerca\" value=\"$materia_cerca\">";

echo "
<table border=0 width=100%>
<tr><td width=80% valign=top>

<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"$colore_scuro\">
<tr><td>
<table border=0 cellpadding=0 cellspacing=\"0\" bgcolor=\"$colore_sfondo\" width=\"100%\">
";
?>


<tr><td>


<?php


	$query="SELECT id_purchase,lo_repository.id_lo,titolo,materia,id_utente,data_ordine FROM lo_repository,lo_purchase WHERE lo_repository.id_lo=lo_purchase.id_lo AND stato_ordine='1' ORDER BY data_ordine DESC";
	$result=$mysqli->query($query);
	
	
	
	
echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"600\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"600\">
	";

	echo "<tr bgcolor=\"$colore_scuro\">";
	echo "<td >&nbsp;</td>";
	echo "<td ><span class=testonegativo><b>Data ordine</b></span></td>";
	echo "<td ><span class=testonegativo><b>Utente</b></span></td>";
	echo "<td ><span class=testonegativo><b>LO</b></span></td>";
	echo "</tr>\n";

	$colore=$colore_sfondo;
	
	while ($riga=$result->fetch_array()) {
		
	
		echo "<tr bgcolor=\"$colore\">";
		
		$id_purchase=$riga["id_purchase"];
		$id_lo=$riga["id_lo"];
		$titolo=$riga["titolo"];
		$materia=$riga["materia"];
		$data_ordine=$riga["data_ordine"];
		$id_u=$riga["id_utente"];
		
		
		echo "<td><input type=\"checkbox\" name=\"id_purchase[]\" value=\"$id_purchase\"></td>";			
		echo "<td><span class=testopiccolo>$data_ordine</span></td>";
		echo "<td><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_u', 'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\"><span class=testopiccolo>$id_u</span></a></td>";
		echo "<td><span class=testopiccolo>$titolo ($materia)</span></td>";


			echo "</tr>";
	
}; 
	
echo "</table>\n";

echo "		
</td></tr>
</table>";

?>

<!-- fine elenco risorse -->
</td>
</tr></table>

</td>
</tr></table>


</td>
<td valign=top width="20%">




</td>

</td></tr></table>

</td> 
</tr></table>
<?php
echo "<input type=button value=\"$stringa[seleziona_tutti]\" onClick=\"SetAllCheckBoxes('modulo','id_purchase[]',true)\"> <input type=button value=\"$stringa[deseleziona]\" onClick=\"SetAllCheckBoxes('modulo','id_purchase[]',false)\"> <br><br><input type=submit value=\"Conferma gli ordini selezionati\"";
?>
</td></tr></table>
<br>



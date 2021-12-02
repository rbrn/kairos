<?php
// parametro di richiamo: id_test

$id_test=$_REQUEST["id_test"];

$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];

if (!$pag_size) $pag_size=20;
if (!$pagina) $pagina=1;


$query = "SELECT titolo FROM test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[edit_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<span class=testo><b>".$riga["titolo"]."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=test_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=test_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";
?>

<TABLE BORDER=0 width=100%>
<tr>
<td>
 
<?php

echo "<a href=\"index.php?risorsa=test_item_add&id_test=$id_test\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_aggiungidomanda','','img/ico_aggiungidomanda_over.gif',1)\"><img border=\"0\" src=\"img/ico_aggiungidomanda.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[aggiungi_domanda]\" name=\"img_aggiungidomanda\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=test_item_add&id_test=$id_test\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_aggiungidomanda','','img/ico_aggiungidomanda_over.gif',1)\">$stringa[aggiungi_domanda]</a></span>";

if ($cod_area=='kairos_larimart') {
	echo "&nbsp;<span class=testo>[<a href=index.php?risorsa=test_esporta&id_test=$id_test>Esporta test per fruizione off-line</a>]</span>";
};


// seleziono le voci del id_test

$query = "SELECT * FROM item_test WHERE id_test='$id_test' ORDER BY num_item";
$result=$mysqli->query($query);


$tot_righe=$result->num_rows;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$num =$tot_righe;
echo "<p><span class=testo>$stringa[domande]: <b>$num</b></span></p>";

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

$inizio=$pag_size*($pagina-1);
//$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;
$righe=1;
$continua = true;
$colore=$colore_sfondo;

while ($item=$result->fetch_array()) {

	echo "<tr bgcolor=\"$colore\"  valign=\"top\">";
	echo "<td><a href=test_item_sposta.php?id_item_test=$item[id_item_test]&id_test=$item[id_test]&azione=up><img src=img/up.gif width=11 height=7 border=0 alt=\"$stringa[pagina_up]\"></a><a href=test_item_sposta.php?id_item_test=$item[id_item_test]&id_test=$item[id_test]&azione=down><img src=img/down.gif width=11 height=7 border=0 alt=\"$stringa[pagina_down]\"></a></td>";

	//echo "<td><span class=testo>$item[num_item])</span></td>";
	echo "<td><span class=testo>$item[domanda]</span></td>";
	echo "<td><a href=index.php?risorsa=test_item_mod&id_item_test=$item[id_item_test] onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$item[id_item_test]','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[edit]\" border=\"0\" name=\"img_mod_$item[id_item_test]\"></a></td>";
	echo "<td><a href=index.php?risorsa=msg&msg=conf_canc&pagina=test_item_del.php&id_item_test=$item[id_item_test] onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$item[id_item_test]','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$item[id_item_test]\"></td>";
	
	echo "</tr>";
	$righe++;
	$progr++;
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
};

echo "</table>";

echo "</td></tr></table>";


?>
<?php
/*
echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?risorsa=test_edit&pagina=$i&pag_size=$pag_size&id_test=$id_test>$i</a>]
		";
	};
	$i++;
};
echo "</span><br><br>";	
*/
?>		
</td></tr>
</table>

</td></tr>
</table>
<br>

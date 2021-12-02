<?php

$id_test=$_REQUEST["id_test"];
$id_start=$_REQUEST["id_start"];

$query = "SELECT titolo,tipo_test,punteggio_soglia FROM test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$tipo_test=$riga["tipo_test"];
$punteggio_soglia=$riga["punteggio_soglia"];

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[elenco_compilazioni])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<span class=testo><b>".$riga["titolo"]." ($id_test)</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=test_risultati&id_test=$id_test\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=test_risultati&id_test=$id_test\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";


$query = "SELECT id_test_compilato,id_test,id_utente,punteggio,punteggio_max,year(data_compilazione) as yy,month(data_compilazione) as mm, dayofmonth(data_compilazione) as dd,hour(data_compilazione) as hh,minute(data_compilazione) as mi FROM test_compilato WHERE  id_test='$id_test' AND id_test_compilato >= '$id_start' ORDER BY id_test_compilato";

$result=$mysqli->query($query);

$righe = 1;

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

echo "<tr bgcolor=\"$colore_scuro\">";
echo "<td><span class=testonegativo><b>$stringa[utente]</b></span></td>
<td><span class=testonegativo><b>$stringa[data]</b></span></td>";

if ($tipo_test==0) {
	echo "<td><span class=testonegativo><b>$stringa[punteggio]</b></span></td>";
};
echo "
<td>&nbsp;</td>\n
<td>&nbsp;</td>\n";

$colore=$colore_sfondo;

while ($test = $result->fetch_array() and $righe<=50) {

	$id_autore = $test["id_utente"];
	echo "<tr bgcolor=\"$colore\">";
	echo "<td><span class=testopiccolo>
	<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_autore</a>
</span></td>";
		

	echo "<td><span class=testopiccolo>".$test["dd"]."/".$test["mm"]."/".$test["yy"]." - ".$test["hh"].":".$test["mi"]."</span></td>\n";

	if ($tipo_test==0) {
		$icona="";
		if ($punteggio_soglia>0) {
			if ($test["punteggio"]>=$punteggio_soglia) {
				$icona="<img src=img/forum/approvo.gif>";
			} else {
				$icona="<img src=img/forum/disapprovo.gif>";
			};
		};
		echo "<td><span class=testopiccolo><b>".$test["punteggio"]."/".$test["punteggio_max"]."</b></span> $icona</td>";
	};
	
	printf("<td><span class=testopiccolo><a href=index.php?risorsa=test_compilato&id_test_compilato=%s>%s</a></span></td>\n",$test["id_test_compilato"],$stringa[questionario_compilato]);

	echo "<td><a href=test_compilato_del.php?id_test_compilato=".$test["id_test_compilato"]." onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$test[id_test_compilato]','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$test[id_test_compilato]\"></a></td>";
	echo "</tr>";

	$righe++;

	
}; //fine del while delle voci
echo "</table>\n";

echo "</td></tr></table>";

echo "<hr size=1>";
	
if ($test) {
	printf( "<span class=testopiccolo>[<a href=index.php?risorsa=test_risultati_elenco&id_test=%s&id_start=%s>>></a>]</span>",$id_test,$test["id_test_compilato"]);
	};
	
echo "<br><br>";
?>
</td></tr></table>
<br>

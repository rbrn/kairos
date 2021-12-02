<?php
$id_item_test=$_REQUEST["id_item_test"];

$query = "SELECT * FROM item_test WHERE id_item_test='$id_item_test'";
$result=$mysqli->query($query);
$item = $result->fetch_array();

$id_test=$item["id_test"];

$query = "SELECT titolo,tipo_test FROM test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$tipo_test=$riga["tipo_test"];

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[modifica_domanda_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<span class=testo><b>".$riga["titolo"]." ($id_test)</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=test_edit&id_test=$id_test\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=test_edit&id_test=$id_test\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

?>
<TABLE BORDER=0 width=100%>
<tr>
<td>
 
<?php




$num_item = $item["num_item"];
$tipo_item = $item["tipo_item"];
$domanda=$item["domanda"];
$testo=$domanda;
//$domanda = htmlentities(stripslashes($item["domanda"]));
$peso = $item["peso"];
$risp1 = htmlentities(stripslashes($item["risp1"]));
$risp2 = htmlentities(stripslashes($item["risp2"]));
$risp3 = htmlentities(stripslashes($item["risp3"]));
$risp4 = htmlentities(stripslashes($item["risp4"]));
$risp5 = htmlentities(stripslashes($item["risp5"]));
$risp6 = htmlentities(stripslashes($item["risp6"]));
$risp7 = htmlentities(stripslashes($item["risp7"]));
$risp8 = htmlentities(stripslashes($item["risp8"]));
$risp_altro = $item["risp_altro"];
$punt_risp1 = $item["punt_risp1"];
$punt_risp2 = $item["punt_risp2"];
$punt_risp3 = $item["punt_risp3"];
$punt_risp4 = $item["punt_risp4"];
$punt_risp5 = $item["punt_risp5"];
$punt_risp6 = $item["punt_risp6"];
$punt_risp7 = $item["punt_risp7"];
$punt_risp8 = $item["punt_risp8"];
$note = htmlentities(stripslashes($item["note"]));

$val_tipo_item0="";
$val_tipo_item1="";
$val_tipo_item2="";

switch ($tipo_item) {
	case 0:
		$val_tipo_item0="checked";
		break;
		
	case 1:
		$val_tipo_item1="checked";
		break;
	
	case 2:
		$val_tipo_item2="checked";
		break;
};

echo "<form action=test_item_mod_op.php method=post name=modulo id=modulo>";
echo "<input type=hidden name=id_item_test value=$id_item_test>";
echo "<input type=hidden name=id_test value=$id_test>";
echo "<TABLE border=0 width=100%>";
/*
if ($tipo_test==0) {
echo "
<TR>
<TD align=right><span class=testo><b>Peso:</b></span></TD>
<TD><INPUT type=text maxLength=3 name=peso value=\"$peso\" size=05><span class=testo>%</span></TD>
</TR>";
};
*/
echo "<TR>
<TD align=right><span class=testo><b>$stringa[posizione]:</b></span></TD>
<TD><INPUT type=text maxLength=3 name=num_item value=$num_item size=05></TD>
</TR>";


echo "<TR>
<TD align=right><span class=testo><b>$stringa[tipo]:</b></span></TD>";

if ($tipo_test==0) {
	echo "
	<TD><span class=testo><INPUT type=radio name=tipo_item value=1 checked>$stringa[chiusa] ";
	if ($cod_area=='kairos_larimart') {
	echo "
<INPUT type=radio name=tipo_item value=1>$stringa[risposta_multipla] <INPUT type=radio name=tipo_item value=1>$stringa[vero_falso] <br><INPUT type=radio name=tipo_item value=1 >$stringa[inserimento] <INPUT type=radio name=tipo_item value=1 >$stringa[associazione] <INPUT type=radio name=tipo_item value=1 >$stringa[aree_immagine]</span></TD>";
	};
} else {
	echo "
<TD><span class=testo><INPUT type=radio name=tipo_item value=0 $val_tipo_item0>$stringa[aperta] <INPUT type=radio name=tipo_item value=1 $val_tipo_item1>$stringa[chiusa] <INPUT type=radio name=tipo_item value=2 $val_tipo_item2>$stringa[file_allegato]</span></TD>";
};

echo "</TR>";


if (!$win_ie) {
echo"
<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[testo]:</b></span></td>
</tr>
<tr>
<td colspan=2 valign=top align=center>
<TEXTAREA cols=70 name=testo rows=10 wrap=virtual>".$testo."</TEXTAREA>
</td>
</tr>";
} else {
	echo "<input type=\"hidden\" name=\"testo\" id=\"testo\">\n
	<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[testo]:</b></span></td>
</tr>
	<tr>
	<td colspan=2 valign=top align=center>
	";
	$modifica_testo=true;
	require "./include/editor_materiali.inc";
	echo "
	</td>
	</tr>
	";
};
/*
echo "<TR>
<TD align=right valign=top><span class=testo><b>$stringa[testo]:</b></span></TD>";
echo "<TD valign=top>
<textarea name=domanda rows=5 cols=60>$domanda</textarea></TD>
</TR>";
*/

for ($j=1; $j<=8; $j++) {
	$valore = "risp".$j;
	$punteggio="punt_risp".$j;
	echo "<TR>
<TD align=right><span class=testo><b>$stringa[scelta] $j:</b></span></TD>
<TD><INPUT type=text maxLength=250 name=risp$j size=50 value=";
	echo " \"${$valore}\">";

	if ($tipo_test==0) {
		echo " <span class=testo><b>$stringa[punteggio]:</b></span> <INPUT type=text maxLength=250 name=punt_risp$j size=05 value=";
		echo " \"${$punteggio}\">";
	};

	echo "</TD></TR>";
};

if ($tipo_test<>0) {
echo "<TR><td></td>
<TD><input type=checkbox name=risp_altro";

if ($risp_altro == 'on') {
	echo " checked";
};

echo "> <span class=testo><b>$stringa[chiedi_altro]</b></span></TD>
</TR>";
};

if ($tipo_test==0) {
echo "<TR>
<TD align=right valign=top><span class=testo><b>$stringa[commento_post]:</b></span></TD>";
echo "<TD valign=top>
<textarea name=note rows=5 cols=60>$note</textarea></TD>
</TR>";
};

echo "</TABLE>";
echo "<BR><P align=center>";

if (!$win_ie) {
echo "
<input type=submit value=$stringa[ok]>";
} else {
echo "<input type=submit value=$stringa[ok] onclick=\"inoltra();return true\">";
};	

echo "</P>";

echo "</FORM>";
?>
		
</td></tr>
</table>
</td></tr>
</table>
<br>

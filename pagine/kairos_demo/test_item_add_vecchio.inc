<?php
$id_test=$_REQUEST["id_test"];

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
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[nuova_domanda_test])."</b></span>
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

$query = "SELECT MAX(num_item) as max_num_item FROM item_test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

$max_item=$riga["max_num_item"]+1;

echo "<form action=test_item_add_op.php method=post name=modulo id=modulo>";
echo "<input type=hidden name=id_test value=$id_test>";
echo "<TABLE border=0 width=100%>";

/*
if ($tipo_test==0) {
echo "
<TR>
<TD align=right><span class=testo><b>Peso:</b></span></TD>
<TD><INPUT type=text maxLength=3 name=peso value=\"100\"  size=05><span class=testo>%</span></TD>
</TR>";
};
*/
echo "
<TR>
<TD align=right><span class=testo><b>$stringa[posizione]:</b></span></TD>
<TD><INPUT type=text maxLength=3 name=num_item value=$max_item  size=05></TD>
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
<TD><span class=testo><INPUT type=radio name=tipo_item value=0>$stringa[aperta] <INPUT type=radio name=tipo_item value=1 checked>$stringa[chiusa] <INPUT type=radio name=tipo_item value=2>$stringa[file_allegato]</span></TD>";
};

echo "</TR>";

$testo=$domanda;
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
<textarea name=domanda rows=5 cols=60></textarea></TD>
</TR>";
*/
echo "<TR>
<TD align=right><span class=testo><b>$stringa[scelta] 1:</b></span></TD>
<TD><INPUT type=text maxLength=250 name=risp1 size=50>";

if ($tipo_test==0) {
	echo " <span class=testo><b>$stringa[punteggio]:</b></span> <INPUT type=text maxLength=250 name=punt_risp1 size=05>";
};

echo "
</TD>
</TR>";

echo "<TR>
<TD align=right><span class=testo><b>$stringa[scelta] 2:</b></span></TD>
<TD><INPUT type=text maxLength=250 name=risp2 size=50>";

if ($tipo_test==0) {
	echo " <span class=testo><b>$stringa[punteggio]:</b></span> <INPUT type=text maxLength=250 name=punt_risp2 size=05>";
};

echo "
</TD>
</TR>";

echo "<TR>
<TD align=right><span class=testo><b>$stringa[scelta] 3:</b></span></TD>
<TD><INPUT type=text maxLength=250 name=risp3 size=50>";

if ($tipo_test==0) {
	echo " <span class=testo><b>$stringa[punteggio]:</b></span> <INPUT type=text maxLength=250 name=punt_risp3 size=05>";
};

echo "
</TD>
</TR>";

echo "<TR>
<TD align=right><span class=testo><b>$stringa[scelta] 4:</b></span></TD>
<TD><INPUT type=text maxLength=250 name=risp4 size=50>";

if ($tipo_test==0) {
	echo " <span class=testo><b>$stringa[punteggio]:</b></span> <INPUT type=text maxLength=250 name=punt_risp4 size=05>";
};

echo "
</TD>
</TR>";

echo "<TR>
<TD align=right><span class=testo><b>$stringa[scelta] 5:</b></span></TD>
<TD><INPUT type=text maxLength=250 name=risp5 size=50>";

if ($tipo_test==0) {
	echo " <span class=testo><b>$stringa[punteggio]:</b></span> <INPUT type=text maxLength=250 name=punt_risp5 size=05>";
};

echo "
</TD>
</TR>";

echo "<TR>
<TD align=right><span class=testo><b>$stringa[scelta] 6:</b></span></TD>
<TD><INPUT type=text maxLength=250 name=risp6 size=50>";

if ($tipo_test==0) {
	echo " <span class=testo><b>$stringa[punteggio]:</b></span> <INPUT type=text maxLength=250 name=punt_risp6 size=05>";
};

echo "
</TD>
</TR>";

echo "<TR>
<TD align=right><span class=testo><b>$stringa[scelta] 7:</b></span></TD>
<TD><INPUT type=text maxLength=250 name=risp7 size=50>";

if ($tipo_test==0) {
	echo " <span class=testo><b>$stringa[punteggio]:</b></span> <INPUT type=text maxLength=250 name=punt_risp7 size=05>";
};

echo "
</TD>
</TR>";

echo "<TR>
<TD align=right><span class=testo><b>$stringa[scelta] 8:</b></span></TD>
<TD><INPUT type=text maxLength=250 name=risp8 size=50>";

if ($tipo_test==0) {
	echo " <span class=testo><b>$stringa[punteggio]:</b></span> <INPUT type=text maxLength=250 name=punt_risp8 size=05>";
};

echo "
</TD>
</TR>";

if ($tipo_test<>0) {
echo "<TR><td></td>
<TD><span class=testo><input type=checkbox name=risp_altro> <b>$stringa[chiedi_altro]</b></span></TD>
</TR>";
};

if ($tipo_test==0) {
echo "<TR>
<TD align=right valign=top><span class=testo><b>$stringa[commento_post]:</b></span></TD>";
echo "<TD valign=top>
<textarea name=note rows=5 cols=60></textarea></TD>
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

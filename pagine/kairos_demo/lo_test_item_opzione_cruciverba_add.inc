<?php

function checkBoxPerCasellaNera($ope,$i,$j,$etichetta) {
if ($etichetta!="") {
	if ($ope==2)	{
		if ($etichetta==-1)
			$strchek="<INPUT type=\"checkbox\" name=\"O$i" ."_V$j\" checked>";
		else
			$strchek="<INPUT type=\"checkbox\" name=\"O$i" ."_V$j\">";
	}
	else {
		if ($etichetta==-1)
			$strchek="&nbsp;";
		else
			$strchek=$etichetta;
	 }
}
else {
	if ($ope==2)	
		$strchek="<INPUT type=\"checkbox\" name=\"O$i" ."_V$j\">";
	else 
		$strchek="&nbsp;";
}
return $strchek;
}
$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$ope=$_REQUEST["ope"];

$query="SELECT * FROM lo_test_item_cruciverba WHERE id_item='$id_item'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$num_orz=$riga["larghezza"];
$num_ver=$riga["altezza"];
	
$query = "SELECT * FROM lo_test_item WHERE id_item='$id_item'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$titolo=htmlentities($riga[titolo]);
$testo_domanda=$riga[domanda];
$tipo_item=$riga[tipo_item];

$tipo_item_stringa=$stringa[cruciverba];

		
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_repository])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[modifica_domanda_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[nuova_opzione_domanda_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";


?>
 
<?php
echo "<TABLE border=0 width=550>";

echo "

 <TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[titolo]:</b></span></TD>
  		<TD><span class=testo>$titolo<span></TD>
      </TR>
	  
<TR>
<TD align=\"right\" valign=\"top\"><span class=testo><b>$stringa[tipo]:</b></span></TD>";

	echo "
	<TD valign=\"top\">
	<span class=testo>$tipo_item_stringa</span>
	";
	echo "</TD>";

echo "</TR>";

if (trim($testo_domanda)) {
echo "
<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[testo_domanda_esteso]:</b></span></td>
</tr>
<tr>";

echo "
<td colspan=2 valign=top width=\"600\" >
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table width=\"600\" border=\"0\" cellspacing=\"10\" cellpadding=\"1\" bgcolor=\"#ffffff\">
<tr><td>
<span class=testo>";
echo "$testo_domanda";
echo "</span>
</td></tr>
</table>
</td></tr>
</table>
</td>
</tr>";
};

echo "</TABLE>";
?>

<?php 
echo "<form action=lo_test_item_opzione_cruciverba_add_op.php method=post name=modulo id=modulo>";
echo "<table border=1 cellspacing=0 cellpadding=0>";
echo "<tr bgcolor=\"#ffffcc\">";
echo "<td width=\"19\" height=\"21\" align=\"middle\">&nbsp;</td>";
for ($j=0;$j<$num_orz;$j++) {
	$j1=$j+1;
	echo "<td width=\"19\" height=\"21\" align=\"center\"><span class=\"testopiccolo\">$j1</span></td>";
};
echo "</tr>";
for ($i=0;$i<$num_ver;$i++) {
	echo "<tr>";
	$i1=$i+1;
	echo "<td width=\"19\" height=\"21\" align=\"center\" bgcolor=\"#ffffcc\"><span class=\"testopiccolo\">$i1</span></td>";
	for ($j=0;$j<$num_orz;$j++) {
		$pos=$i*$num_orz+$j+1;
		$query="SELECT * FROM lo_test_item_opzioni_cruciverba WHERE id_item='$id_item' AND posizione='$pos'";
		$result=$mysqli->query($query);
		if ($result->num_rows) {
			$riga=$result->fetch_array();
			$etichetta=$riga["etichetta"];
			if ($etichetta=="-1") {
					echo "<td width=\"19\" height=\"21\" bgcolor=\"black\">" .checkBoxPerCasellaNera($ope,$i,$j,$etichetta) ."</td>";
			} else {
					echo "<td width=\"19\" height=\"21\"><span class=\"testopiccolo\">" .checkBoxPerCasellaNera($ope,$i,$j,$etichetta) ."</span></td>";
			};
		
		} else {
			echo "<td width=\"19\" height=\"21\">" .checkBoxPerCasellaNera($ope,$i,$j,"") ."</td>";
		};
	};
	echo "</tr>";
};
echo "</table>";
?>

<TABLE BORDER=0 width=100%>
<tr>
<td>
 
<?php

echo "<input type=\"hidden\" name=\"id_item\" value=\"$id_item\">";
echo "<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">";
echo "<input type=\"hidden\" name=\"ope\" value=\"$ope\">";


echo "<TABLE border=0>";
if ($ope!=2) {
echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[coord_riga_casella]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"riga_casella\" size=\"05\"></TD>
      </TR>";
	  
echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[coord_col_casella]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"col_casella\" size=\"05\"></TD>
      </TR>";

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[numero_casella]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"etichetta\" size=\"05\" value=\"-1\">&nbsp;
		<span class=testopiccolo><i>$stringa[numero_casella_nera]</i></span></TD>
      </TR>";  	 

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[verso]:</b></span></TD>
  		<TD><select name=\"verso\">
		<option value=\"O\">$stringa[o]</option>
		<option value=\"V\">$stringa[v]</option>
		</select></TD>
      </TR>"; 

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[definizione]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"definizione\" size=\"50\"></TD>
      </TR>"; 	  

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[risposta_giusta]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"risposta_giusta\" size=\"50\"></TD>
      </TR>"; 	

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[msg_ko]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"msg_ko\" size=\"50\"></TD>
      </TR>"; 	
} 	  
echo "
<tr>
<td colspan=2 valign=top align=\"center\"><input type=\"submit\" name=\"ok\" value=\"$stringa[ok]\" /></td>
</tr>
";
echo "</TABLE>";

echo "</FORM>";
?>
		
</td></tr>
</table>

</td></tr>
</table>
<br>

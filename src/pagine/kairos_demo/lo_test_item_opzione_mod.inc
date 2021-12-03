<?php


$id_item_opzione=$_REQUEST["id_item_opzione"];
$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$azione=$_REQUEST["azione"];

$query = "SELECT * FROM lo_test_item WHERE id_item='$id_item'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$titolo=htmlentities($riga[titolo]);
$testo_domanda=$riga[domanda];
$tipo_item=$riga[tipo_item];

switch ($tipo_item) {
	case 1:
		$tipo_item_stringa=$stringa[sm_rs];
		break;
		
	case 2:
		$tipo_item_stringa=$stringa[sm_rm];
		break;
		
	case 3:
		$tipo_item_stringa=$stringa[vero_falso];
		break;	
	
	case 4:
		$tipo_item_stringa=$stringa[inserimento];
		break;	
	
	case 5:
		$tipo_item_stringa=$stringa[associazione];
		break;	
	
	case 6:
		$tipo_item_stringa=$stringa[aperta];
		break;	
};		

$query = "SELECT * FROM lo_test_item_opzioni WHERE id_item_opzione='$id_item_opzione'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$opzione=htmlentities($riga[risposta_opzione]);
$punteggio=htmlentities($riga[punteggio]);

$sel_si="";
$sel_no="";

if ($punteggio<>"0.00") {
	$sel_si="selected";
} else {
	$sel_no="selected";
};		

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_repository])."</td></tr>


<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[modifica_domanda_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[modifica_opzione_domanda_test])."</b></span>
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
echo "<TABLE border=0 width=600>";

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

<TABLE BORDER=0 width=100%>
<tr>
<td>
 
<?php
echo "<form action=lo_test_item_opzione_mod_op.php method=post name=modulo id=modulo>";
echo "<input type=\"hidden\" name=\"id_item_opzione\" value=\"$id_item_opzione\">";
echo "<input type=\"hidden\" name=\"id_item\" value=\"$id_item\">";
echo "<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">";

echo "<TABLE border=0 width=550>";

echo "

 	<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[opzione]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"opzione\" size=\"80\" value=\"$opzione\"></TD>
      </TR>";
	  

	  echo "
	 	<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[corretto]:</b></span></TD>
  		<TD><select name=\"punteggio\"><option value=\"1\" $sel_si>$stringa[si]</option><option value=\"0\" $sel_no>$stringa[no]</option></select></TD>
     	</TR>
	  ";

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

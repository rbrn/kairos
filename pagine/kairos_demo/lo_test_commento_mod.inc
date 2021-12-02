<?php


$id_commento=$_REQUEST["id_commento"];
$tipo_elemento=$_REQUEST["tipo_elemento"];
$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

if ($id_item) {
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
	
	case 7:
		$tipo_item_stringa=$stringa[dragdrop];
		break;	
};		
};

switch ($tipo_elemento) {
	case "id_item":
		$label=$stringa[commento_item];
		$campo=$tipo_elemento;
		$val_campo=$id_item;
		break;
};

$query="SELECT * FROM lo_test_commento WHERE id_commento='$id_commento'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$lim_inf=htmlentities($riga[lim_inf]);
$lim_sup=htmlentities($riga[lim_sup]);
$testo=htmlentities($riga[commento]);

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_repository])."</td></tr>


<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($label)."</b></span>
</td></tr>


<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=lo_test_commento_edit&tipo_elemento=id_item&id_item=$id_item&risorsa_padre=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=lo_test_commento_edit&tipo_elemento=id_item&id_item=$id_item&risorsa_padre=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

?>

<TABLE BORDER=0 width=100%>
<tr>
<td>
 
<?php

if ($tipo_elemento=="id_item") {

echo "<TABLE border=0 width=550>";

echo "

 <TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[testo_domanda]:</b></span></TD>
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

if ($tipo_item=="4") {
	$nspazio=0;
	for ($i=0;$i<strlen($testo_domanda);$i++) {
		$char=substr($testo_domanda,$i,1);
		if ($char=="[" and substr($testo_domanda,$i+1,1)=="*" and substr($testo_domanda,$i+2,1)=="]") {
			$nspazio++;
			$testo_domanda1.="[*".$nspazio."]";
			$i=$i+2;
		} else {
			$testo_domanda1.=$char;
		};
	};
};

if (trim($testo_domanda) or trim($testo_domanda1)) {
echo "
<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[testo_domanda_esteso]:</b></span></td>
</tr>
<tr>
<td colspan=2 valign=top width=500>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table width=\"100%\" border=\"0\" cellspacing=\"10\" cellpadding=\"1\" bgcolor=\"#ffffff\">
<tr><td>
<span class=testo>";
if ($tipo_item=="4") {
	echo "$testo_domanda1";
} else {
	echo "$testo_domanda";
};
echo "</span>
</td></tr>
</table>
</td></tr>
</table>
</td>
</tr>";
};

echo "</TABLE>";

};
?>

<form action=lo_test_commento_mod_op.php  method=post name=modulo id=modulo>
<?php
echo "<input type=\"hidden\" name=\"id_commento\" value=\"$id_commento\">";
echo "<input type=\"hidden\" name=\"tipo_elemento\" value=\"$tipo_elemento\">";
echo "<input type=\"hidden\" name=\"id_item\" value=\"$id_item\">";
echo "<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">";
?>
    <TABLE border=0 width=550>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
	 
	  
<?php 	  

echo "
<TR>
<TD align=right valign=top><span class=testo><b>$stringa[punteggio_inf]:</b></span></TD>
<TD><INPUT type=\"text\" name=\"lim_inf\" size=\"10\" value=\"$lim_inf\"></TD>
</TR>";

echo "
<TR>
<TD align=right valign=top><span class=testo><b>$stringa[punteggio_sup]:</b></span></TD>
<TD><INPUT type=\"text\" name=\"lim_sup\" size=\"10\"  value=\"$lim_sup\"></TD>
</TR>";

echo "
<TR>
<TD align=right valign=top><span class=testo><b>$stringa[commento]:</b></span></TD>
<TD><INPUT type=\"text\" name=\"testo\" size=\"60\" value=\"$testo\"></TD>
</TR>";
?>

    </TABLE>
    <BR>
	
    <P align=center> 
  		<?php
  			echo "<input type=\"submit\" name=\"ok\" value=\"$stringa[ok]\" />";
		?>
    </P>
 </FORM>
 
 </td></tr></table>
 <br>
 
 </td></tr>
</table>

</td></tr>
</table>
<br>
 

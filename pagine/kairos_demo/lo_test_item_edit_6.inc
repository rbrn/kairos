<?php


$query = "SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$id_item_opzione=$riga[id_item_opzione];
$risposta_giusta=htmlentities($riga[risposta_giusta]);
$punteggio=htmlentities($riga[punteggio]);
$limite_caratteri=htmlentities($riga[limite_caratteri]);
$case_sensitive=htmlentities($riga[case_sensitive]);

$sel_si="";
$sel_no="";

if ($punteggio<>"0.00") {
	$sel_si="selected";
} else {
	$sel_no="selected";
};	
		
$case_checked="";
if ($case_sensitive=="on") $case_checked="checked";
		
echo "<form action=lo_test_item_opzione_aperta_op.php method=post name=modulo id=modulo>";
echo "<input type=\"hidden\" name=\"id_item_opzione\" value=\"$id_item_opzione\">";
echo "<input type=\"hidden\" name=\"id_item\" value=\"$id_item\">";
echo "<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">";

	echo "<TABLE border=0>";

	
	echo "

 	<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[risposta_giusta]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"risposta_giusta\" size=\"80\" value=\"$risposta_giusta\"></TD>
      </TR>";
	  
	  /*
	  echo "
 		<TR> 
        <TD align=right valign=top></TD>
  		<TD><INPUT type=\"checkbox\" name=\"case_sensitive\" $case_checked> <span class=testo><b>$stringa[case_sensitive]</b></span></TD>
      </TR>";
	  */
	  		 
	 
	 	echo "
	 	<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[limite_caratteri]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"limite_caratteri\" size=\"10\" value=\"$limite_caratteri\"></TD>
     	</TR>";
	

if ($ruolo=='admin' or $id_utente==$id_editor) {	
echo "
<tr>
<td colspan=2 valign=top align=\"center\"><input type=\"submit\" name=\"ok\" value=\"$stringa[ok]\" /></td>
</tr>
";
};

echo "</TABLE>";

echo "</FORM>";

?>

<?php

//analisi $testo_domanda

$errori=multi_strpos("\[\*\]",$testo_domanda);
$nerrori=count($errori);

echo "<form action=lo_test_item_opzione_errori_op.php method=post name=modulo id=modulo>";
echo "<input type=\"hidden\" name=\"nerrori\" value=\"$nerrori\">";
echo "<input type=\"hidden\" name=\"id_item\" value=\"$id_item\">";
echo "<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">";

	echo "<TABLE border=0>";
	
	for ($i=0;$i<count($errori);$i++) {
		$pos=$i+1;
		
		$query="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND posizione='$pos'";
		$result=$mysqli->query($query);
		
		$riga=$result->fetch_array();
		$risposta_giusta=$riga[risposta_giusta];
		
		$check="";
		
		if ($risposta_giusta=="on") $check="checked";
		

		
		
		echo "
		<TR> 
        <TD align=left valign=top><span class=testo><b>$stringa[nerrore]:</b></span></TD>
  		<TD align=left valign=top><span class=testo><b>$pos</b></span> <INPUT type=\"checkbox\" name=\"risposta_giusta[$i]\" $check></TD>
      </TR>";
	  
 
	  echo "<tr><td colspan=2><hr size=1></td></tr>";

	};
	
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

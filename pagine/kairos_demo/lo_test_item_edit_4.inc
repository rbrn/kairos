<?php

//analisi $testo_domanda

$spazi=multi_strpos("\[\*\]",$testo_domanda);
$nspazi=count($spazi);

echo "<form action=lo_test_item_opzione_spazi_op.php method=post name=modulo id=modulo>";
echo "<input type=\"hidden\" name=\"nspazi\" value=\"$nspazi\">";
echo "<input type=\"hidden\" name=\"id_item\" value=\"$id_item\">";
echo "<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">";

	echo "<TABLE border=0 width=550>";
	
	for ($i=0;$i<count($spazi);$i++) {
		$pos=$i+1;
		
		$query="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND posizione='$pos'";
		$result=$mysqli->query($query);
		
		$riga=$result->fetch_array();
		$risposta_giusta=$riga[risposta_giusta];
		$risposte_lista=$riga[risposte_lista];
		$punteggio=$riga[punteggio];
		$case_sensitive=$riga[case_sensitive];
		$pull_down=$riga[pull_down];
		
		$case_checked="";
		if ($case_sensitive=="on") $case_checked="checked";
		
		$sel="selected";
		
		/*
		if ($pull_down) {
			$pull_down_opzioni="<option value=\"1\" selected>in un menÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ a tendina</option>\n
			<option value=\"0\">su una finestra pop-up</option>";
		} else {
			$pull_down_opzioni="<option value=\"1\">in un menÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ a tendina</option>\n
			<option value=\"0\" selected>su una finestra pop-up</option>";
		};
		*/
		
		echo "
		<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[spazio]:</b></span></TD>
  		<TD><span class=testo><b>$pos</b></span></TD>
      </TR>";
	  
		echo "
 		<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[risposta_giusta]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"risposta_giusta[$i]\" size=\"80\" value=\"$risposta_giusta\"></TD>
      </TR>";
	  
	  /*
	  	echo "
 		<TR> 
        <TD align=right valign=top></TD>
  		<TD><INPUT type=\"checkbox\" name=\"case_sensitive[$i]\" $case_checked> <span class=testo><b>$stringa[case_sensitive]</b></span></TD>
      </TR>";
	  */
	    /*
	  	echo "
	 	<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[punteggio]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"punteggio[$i]\" size=\"10\" value=\"$punteggio\"></TD>
     	</TR>";
		*/
		
		echo "
	 	<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[risposte_lista]:</b></span></TD>
  		<TD><TEXTAREA name=\"risposte_lista[$i]\" cols=\"80\" rows=\"10\">$risposte_lista</textarea></TD>
     	</TR>
		";
	
		/*
		echo "
	 	<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[mostra_lista]:</b></span></TD>
  		<TD><select name=\"pull_down[$i]\">$pull_down_opzioni</select></TD>
     	</TR>
		";
		*/
	  
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

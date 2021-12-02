<?php


$query = "SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$id_item_opzione=$riga[id_item_opzione];
$risposta_giusta=htmlentities($riga[risposta_giusta]);
$risposta_opzione=($riga[risposta_opzione]);
$file_audio=$risposta_opzione;

		
echo "<form action=lo_test_item_opzione_ascoltaescrivi_op.php method=post name=modulo id=modulo>";
echo "<input type=\"hidden\" name=\"id_item_opzione\" value=\"$id_item_opzione\">";
echo "<input type=\"hidden\" name=\"id_item\" value=\"$id_item\">";
echo "<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">";

	echo "<TABLE border=0>";

	
	echo "

 	<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[risposta_giusta]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"risposta_giusta\" size=\"80\" value=\"$risposta_giusta\"></TD>
      </TR>";
	  
 
echo "
<tr>
<td align=right valign=top><span class=testo><b>$stringa[audio]:</b></span></td>
<td><input type=\"text\" name=\"file_audio\" id=\"file_audio\" readonly value=\"$file_audio\" size=\"60\"><br>
<a href=\"javascript:;\" onclick=\"return lo_seleziona_media('gruppo','audio','file_audio');\"><span class=testopiccolo>$stringa[elenco_suoni]</span></a>";

echo "</td>
</tr>";
	  
	  
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

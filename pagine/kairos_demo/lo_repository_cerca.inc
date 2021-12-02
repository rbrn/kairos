<?php
$indietro="javascript:history.back();";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>Repository Learning Object</td></tr>
";



echo "
<tr><td>";

echo "<form action=index.php method=get name=modulo id=modulo>
  <input type=\"hidden\" name=\"risorsa\" value=\"lo_repository\">";
  
echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"450\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";

	echo "<tr>";
	echo "<td colspan=\"2\" bgcolor=\"$colore_scuro\"><span class=testonegativo><b>Ricerca </b></span></td></tr>";
	
	echo "<tr bgcolor=\"$colore_sfondo\">";
	echo "<TD align=right><span class=testo><STRONG>$stringa[titolo]:</STRONG></span></TD>";
	echo "<TD><INPUT type=\"text\"  name=\"titolo_cerca\" size=\"60\"></TD>";
	echo "</tr>";
	
	
	echo "<tr bgcolor=\"$colore_sfondo_neutro\">";
	echo "<TD align=right><span class=testo><STRONG>$stringa[materia]:</STRONG></span></TD>
        <TD><INPUT type=\"text\"  name=\"materia_cerca\" size=\"60\"></TD>";
	echo "</TR>";
	  	  
	echo "<tr bgcolor=\"$colore_sfondo\">";
	echo "<TD align=right></TD>";
	echo "<TD><INPUT type=\"checkbox\"  name=\"filtro\"><span class=testo>Mostra solo i miei Learning Object</span></TD>";
	echo "</tr>";
	
    echo "<tr bgcolor=\"$colore_sfondo\">";
    echo "<td colspan=\"2\" align=center><INPUT type=submit value=\"$stringa[cerca]\"></td>";
	echo "</tr>";
	echo "</table>";
	
	echo "</td></tr></table>";
  	echo "</FORM>";
  
?>  
  
</td></tr></table>
<br>

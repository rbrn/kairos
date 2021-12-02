<?php
$indietro="javascript:history.back();";

$rif_ordine=$_REQUEST["rif_ordine"];
$num_utenti=$_REQUEST["num_utenti"];

$query="SELECT titolo,id_lo,materia FROM lo_repository ORDER BY materia,titolo";

$result=$mysqli->query($query);
$elenco_lo="";
while ($riga=$result->fetch_array()) {
	$id_lo=$riga["id_lo"];
	$titolo=htmlentities($riga["titolo"]);
	$materia=htmlentities($riga["materia"]);
	
	$elenco_lo .= "<option value=\"$id_lo\">$titolo ($materia)</option>";
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>Seleziona LO inclusi nell'ordine</td></tr>
";

echo "
<tr>
<td valign=top width=100%>
<a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>";

echo "<form action=index.php method=post name=modulo id=modulo>
  <input type=\"hidden\" name=\"risorsa\" value=\"lo_ordini_carica_seleziona_lo_op\">";
echo "<input type=\"hidden\" name=\"rif_ordine\" value=\"$rif_ordine\">";
echo "<input type=\"hidden\" name=\"num_utenti\" value=\"$num_utenti\">";
 
echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"450\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";


	echo "<tr bgcolor=\"$colore_sfondo\">";
	echo "<TD align=right valign=top><span class=testo><STRONG>Seleziona gli LO per i quali far valere i codici di accesso:</STRONG></span></TD>";
	echo "<TD><select multiple name=elenco_lo[] size=20>$elenco_lo</select></TD>";
	echo "</tr>";


    echo "<tr bgcolor=\"$colore_sfondo\">";
    echo "<td colspan=\"2\" align=center><INPUT type=submit value=\"OK\"></td>";
	echo "</tr>";
	echo "</table>";
	
	echo "</td></tr></table>";
  	echo "</FORM>";
  
?>  
  
</td></tr></table>
<br>

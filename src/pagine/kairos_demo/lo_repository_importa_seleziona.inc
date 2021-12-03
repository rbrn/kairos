<?php
$indietro="javascript:history.back();";

$kairos=$_REQUEST["kairos"];

mysql_select_db($kairos,$db);	

$query="SELECT titolo,id_lo,materia from risorse_materiali,lo WHERE id_risorsa=id_lo ORDER BY materia,titolo";

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
<td valign=top width=100% class=titolodot>Importa da Repository</td></tr>
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

echo "<form action=index.php method=get name=modulo id=modulo>
  <input type=\"hidden\" name=\"risorsa\" value=\"lo_repository_importa_seleziona_op\">";
echo "<input type=\"hidden\" name=\"kairos\" value=\"$kairos\">";
 
echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"450\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";


	echo "<tr bgcolor=\"$colore_sfondo\">";
	echo "<TD align=right valign=top><span class=testo><STRONG>Seleziona gli LO del repository di <b>$kairos</b> da importare:</STRONG></span></TD>";
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

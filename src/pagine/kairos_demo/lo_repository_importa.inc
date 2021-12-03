<?php
$indietro="javascript:history.back();";

mysql_select_db("atlante",$db);	

$query="SELECT * from abbonamenti_piattaforma WHERE (stato=1 or stato=2) AND tipo_area='kairos' AND editor_lo='1' ORDER BY cod_area";

$result=$mysqli->query($query);
$elenco_aree="";
while ($riga=$result->fetch_array()) {
	$tipo_area=$riga["tipo_area"];
	$cod_area=$riga["cod_area"];
	$elenco_aree .= "<option value=\"".$tipo_area."_".$cod_area."\">".$tipo_area."_".$cod_area;
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
  <input type=\"hidden\" name=\"risorsa\" value=\"lo_repository_importa_seleziona\">";
  
echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"450\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";

	echo "<tr>";
	echo "<td colspan=\"2\" bgcolor=\"$colore_scuro\"><span class=testonegativo><b>Importa LO da Repository </b></span></td></tr>";
	
	echo "<tr bgcolor=\"$colore_sfondo\">";
	echo "<TD align=right><span class=testo><STRONG>Kairos del repository da cui importare gli LO:</STRONG></span></TD>";
	echo "<TD><select name=\"kairos\">$elenco_aree</select></TD>";
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

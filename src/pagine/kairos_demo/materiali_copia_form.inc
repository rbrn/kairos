<?php

$elenco_corsi="";
$query="SELECT * FROM edizioni WHERE stato='attiva' ORDER BY id_corso,id_edizione DESC";
$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {
$id_corso=$riga["id_corso"];
$id_edizione=$riga["id_edizione"];
$elenco_corsi .= "<option value=\"$id_corso $id_edizione\">$id_corso ($id_edizione)";
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>$stringa[utility]</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[materiali_copia])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=utility_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=utility_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

echo "
<form action=materiali_copia.php method=post>
<table border=\"0\">
 <tr>
<td align=\"right\"><span class=testo><b>$stringa[corso_da_copiare]</b></span></td>
<td>
<select name=id_corso_edizione>
$elenco_corsi
</select>
</td>
</tr>
 <tr>
<td align=\"right\"><span class=testo><b>$stringa[corso_su_copiare]</b></span></td>
<td>
<select name=id_corso_edizione_copia>
$elenco_corsi
</select>
</td>
</tr>
<tr>
<td></td>
<td align=\"right\">
<input type=\"submit\" value=\"$stringa[ok]\"></td>
</tr>
</table>
</form>
</td></tr></table>
<br>";
?>



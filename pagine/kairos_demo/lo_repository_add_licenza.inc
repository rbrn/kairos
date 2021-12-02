<?php
$indietro = "javascript:history.back();";

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>Aggiungi codice di accesso per Learning Object ordinati</td></tr>
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
  <input type=\"hidden\" name=\"risorsa\" value=\"lo_repository_add_licenza_op\">";


echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"450\">
<tr><td>";

echo "<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";


echo "<tr bgcolor=\"$colore_sfondo\"><td colspan=\"2\"><span class=\"testo\">Inserendo il codice numerico ottenuto a seguito dell'invio di un ordine di Learning Object, potrai eseguire e scaricare quante volte vorrai tutti i Learning Object inclusi nell'ordine</span></td></tr>";

echo "<tr bgcolor=\"$colore_sfondo\">";
echo "<TD align=right><span class=testo><STRONG>Codice di accesso:</STRONG></span></TD>";
echo "<TD><input type=\"text\" name=\"codice\" size=\"50\"></TD>";
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
<?php
echo "                </div>
</div>
</div>
</div>
</div>";
?>
<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

?>
<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_utenti])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[iscrizione_utenti])."</b></span>
</td></tr>

";


echo "
<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=gestione_utenti_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=gestione_utenti_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";


echo "<tr><td>";
?>

<form action="index.php" method="get">
<input type="hidden" name="risorsa" value="utenti_iscrizione_lista">
<table border="0">

    <tr>
            <td align="right"><span class=testo><b><?php echo($stringa[identificativo]);?></b></span></td>
            <td><input type="text" size="10" maxlength=100 name="id_utente_cerca"></td>
        </tr>

	<tr>
	<td colspan=2>
	</td>
	</tr>		
        <tr>
            <td align="right"><span class=testo><b><?php echo($stringa[nome]);?></b></span></td>
            <td><span class=testo><input type="text" size="35" maxlength=100 name="nome"></span></td>
        </tr>
        <tr>
            <td align="right"><span class=testo><b><?php echo($stringa[cognome]);?></b></span></td>
            <td><input type="text" size="35" maxlength=100 name="cognome"></td>
        </tr>
 	       
		<tr>
            <td align="right"><span class=testo><b><?php echo($stringa[stato]);?></b></span></td>
            <td><select name="stato">
			<option value=1><?php echo($stringa[utente]);?></option>
			<option value=2><?php echo($stringa[staff]);?></option>
			<option value=3><?php echo($stringa[admin]);?></option>
			</select>
			</td>
        </tr>
		
		<tr>
            <td></td>
            <td align="right"><input type="submit" value="<?php echo($stringa[cerca]);?>"></td>
        </tr>
    </table>
	
</form>
</td></tr></table>
<br>

<?php

echo "</div>
</div>
</div>
</div>
</div>";

?>

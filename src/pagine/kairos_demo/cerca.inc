<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";
if ($id_utente and $cod_area<>'kairos_facciamo') {
?>

<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[cerca])."</td></tr>
<tr><td>";
?>



<table border=0 cellpadding=5 cellspacing=1>
<tr><td valign=top rowspan=2>

<?php
echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<img src=\"img/ico_utenti.gif\" width=\"16\" height=\"16\" alt=\"\" border=\"0\" align=\"top\"><span class=titolo>&nbsp;<b>".strtoupper($stringa[utenti])."</b></span>
</td>
</tr>
		
<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
<tr><td>";
?>

<form action="index.php" method="get">
<input type="hidden" name="risorsa" value="cerca_utenti">
<input type="hidden" name="pagina" value="1">
<input type="hidden" name="pag_size" value="20">
<table border="0" cellpadding="5">
<?php
$scope="<option value=\"tutto\">$stringa[tutti_corsi]</option>";
if ($id_corso_s) {
	$scope .= "<option value=\"corso\" selected>$stringa[solo_corso]</option>";
};
?>

<tr>
 <td align="right"><span class=testo><?php echo($stringa[cerca_in]);?></span></td>
<td><select name="cerca_in">
<?php echo($scope);?>
</select>
</td>
</tr>
<tr>
<td align="right" valign=top>
<span class=testo><?php echo($stringa[identificativo]);?></span>
</td>
<td valign=top>
<input type="text" size="10" name="id_utente_cerca">
</td>
</tr>

<?php 
if ($id_corso_s) {
	$query="SELECT id_gruppo,descrizione FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
	$result=$mysqli->query($query);
	$elenco_gruppi="<option value=\"qualunque\">$stringa[qualunque]</option>";
	while ($riga=$result->fetch_array()) {
		$id_gr=$riga[id_gruppo];
		$descr_gr=$riga[descrizione];
		$elenco_gruppi .= "<option value=\"$id_gr\">$descr_gr</option>";
	};

?>

<tr>
 <td align="right"><span class=testo><?php echo($stringa[gruppo]);?></span></td>
<td><select name="gruppo">
<?php echo($elenco_gruppi);?>
</select>
</td>
</tr>
<?php
};
?>

<tr>
 <td align="right"><span class=testo><?php echo($stringa[stato]);?></span></td>
<td><select name="stato">
<option value=9><?php echo($stringa[qualunque]);?></option>
<option value=1><?php echo($stringa[utente]);?></option>
<option value=2><?php echo($stringa[staff]);?></option>
<option value=3><?php echo($stringa[admin]);?></option>
</select>
</td>
</tr>
 <tr>
 <td align="right" valign=top>
<span class=testo><?php echo($stringa[nome]);?></span>
 </td>
  <td valign=top>
 <input type="text" size="35"  name="nome">
 </td>
 </tr>
 
 <tr>
 <td align="right" valign=top><span class=testo><?php echo($stringa[cognome]);?></span></td>
 <td valign=top><input type="text" size="35"  name="cognome">
 </td>
 </tr>
 
<?php
if ($cod_area<>"kairos_larimart") {
?> 	
<tr>
<td align="right" valign=top><span class=testo><?php echo($stringa[citta]);?></span></td>
<td valign=top><input type="text" size="35"  name="citta"></td>
</tr>		

<tr>
<td align="right" valign=top><span class=testo><?php echo($stringa[prov]);?></span></td>
<td valign=top><input type="text" size="02"  name="prov"></td>
</tr>		
<?php
};
?> 

<tr><td colspan=2></td></tr>

<tr><td colspan=2>
<p align="center">
<input type="submit"  value="<?php echo($stringa[cerca]);?>">
</p>
	
</td>
</tr>

</table>
</form>

</td></tr></table>
</td></tr></table>
</td>




<td valign=top>

<?php
echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<img src=\"img/ico_forum_utils.gif\" width=\"20\" height=\"20\" alt=\"\" border=\"0\" align=\"top\"><span class=titolo>&nbsp;<b>".strtoupper($stringa[forum])."</b></span>
</td>
</tr>

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
<tr><td>";
?>

<?php
echo "	
<FORM METHOD=\"get\" ACTION=\"index.php\">
<input type=\"hidden\" name=\"risorsa\" value=\"cerca_forum\">
<input type=\"hidden\" name=\"pagina\" value=\"1\">
<TABLE CELLSPACING=\"0\" CELLPADDING=\"5\" BORDER=\"0\">
<TR>
<TD><span class=testo>$stringa[cerca]:</span></td>
<td><INPUT TYPE=\"text\" NAME=\"stringa_cerca\" SIZE=\"25\" TABINDEX=\"1\"></TD>
</TR>
<TR>
<td></td>
<TD><SELECT NAME=\"pag_size\" TABINDEX=\"2\">
<OPTION VALUE=\"5\">$stringa[risultati_5]</OPTION>
<OPTION SELECTED VALUE=\"10\">$stringa[risultati_10]</OPTION>
<OPTION VALUE=\"20\">$stringa[risultati_20]</OPTION>
<OPTION VALUE=\"30\">$stringa[risultati_30]</OPTION>
<OPTION VALUE=\"50\">$stringa[risultati_50]</OPTION>
</SELECT>
</TD>
</TR>
<tr>
<td></td>
<TD><INPUT TYPE=\"submit\" VALUE=\"$stringa[cerca]\" TABINDEX=\"3\"></td>
</tr>
</TABLE>
</FORM>
";
?>
</td></tr></table>
</td></tr></table>
</td>
</tr>


<tr>
<td valign=top>

<?php
echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<img src=\"img/ico_materiali_int_grigio.gif\" width=\"15\" height=\"15\" alt=\"\" border=\"0\" align=\"top\"><span class=titolo>&nbsp;<b>".strtoupper($stringa[materiali])."</b></span>
</td>
</tr>

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
<tr><td>";
?>


<?php 
$scope="<option value=\"corso\" selected>$stringa[del_corso]</option>";
if ($id_corso_s) {
	$scope .= "<option value=\"utenti\">$stringa[degli_utenti]</option>";
};

echo "
	
<FORM METHOD=\"get\" ACTION=\"index.php\">
<input type=\"hidden\" name=\"risorsa\" value=\"cerca_materiali\">
<input type=\"hidden\" name=\"pagina\" value=\"1\">
<input type=\"hidden\" name=\"pag_size\" value=\"20\">
<TABLE CELLSPACING=\"0\" CELLPADDING=\"5\" BORDER=\"0\">
<TR>
<TD align=\"right\"><span class=testo>$stringa[cerca]:</span></td>
<td><INPUT TYPE=\"text\" NAME=\"stringa_cerca\" SIZE=\"25\" TABINDEX=\"1\"></TD>
</TR>
<tr>
<td align=\"right\"><span class=testo>$stringa[cerca_in]:</span></td>
<td><select name=\"cerca_in\">
$scope
</select>
</td>
</tr>
<tr>
<td></td>
<TD><INPUT TYPE=\"submit\" VALUE=\"$stringa[cerca]\" TABINDEX=\"3\"></td>
</tr>
</TABLE>
</FORM>";
?>

</td></tr></table>
</td></tr></table>

</td>
</tr>
</table>	

</td></tr></table>
<?php };
echo "                </div>
            </div>
        </div>
    </div>
</div>";
?>
<br>

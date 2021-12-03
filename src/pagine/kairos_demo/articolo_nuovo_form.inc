<span class=titolopagina>Nuovo articolo</span>

<hr>

<span class=testo>[<a href=index.php?risorsa=gestione_articoli>Gestione Articoli</a>]</span>

<br>



<FORM action=articolo_nuovo.php encType=multipart/form-data method=post name=modulo id=modulo>

<INPUT name=MAX_FILE_SIZE type=hidden value=100000>

<input type=hidden name=id_utente value="<?php echo($id_utente)?>">

<table border=0>



<tr>

<td align=right valign=top><span class=testo><b>Redattore:</b></span></td>

<td align=left valign=top><span class=testo><?php echo($id_utente) ?></span></td>

</tr>



<?php



if ($ruolo=='admin') {

	$opzioni="<option value=\"bozza\" selected>bozza</option>

<option value=\"approvato\">approvato</option>";

} else {

	$opzioni="<option value=\"bozza\" selected>bozza</option>";

};

?>

<tr>

<td align=right valign=top><span class=testo><b>Stato:</b></span></td>

<td valign=top><select name=stato>

<?php echo($opzioni);?>

</select>

</td>

</tr>



<tr>

<td align=right valign=top><span class=testo><b>Titolo:</b></span></td>

<td align=left valign=top><input type=text name=titolo size=40 maxlength=200></td>

</tr>



<tr>

<td align=left valign=top colspan=2><span class=testo><b>Sommario:</b></span>

</td>

</tr>



<tr>

<td align=left valign=top colspan=2><textarea name=sommario cols=63 rows=05></textarea></td>

</tr>



<tr>

<td align=right valign=top><span class=testo><b>Immagine:</b> (GIF/JPG max 100KB)</span></td>

<td align=left valign=top><INPUT name=immagine type=file></td>

</tr>



<tr>

<td align=right valign=top><span class=testo><b>Rubrica:</b></span></td>

<td valign=top><select name=id_rubrica>

<?php

$elenco="";

$query="SELECT * FROM rubrica ORDER BY posizione";

$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {

	$elenco .="<option value=".$riga["id_rubrica"].">".$riga["titolo"]."</option>\n";

};

echo $elenco;

?>

</select></td>

</tr>





<?php

if (!$win_ie) {

echo"

<tr>

<td colspan=2 valign=top><span class=testo><b>Testo dell'articolo:</b></span></td>

</tr>

<tr>

<td colspan=2 valign=top>

<TEXTAREA cols=70 name=testo rows=10 wrap=virtual>".$testo."</TEXTAREA>

</td>

</tr>";

} else {

	echo "<input type=\"hidden\" name=\"testo\" id=\"testo\">\n

	<tr>

	<td colspan=2 valign=top>

	<span class=testo><b>Testo dell'articolo:</b></span>

	";

	



	

	require "./include/editor.inc";

	echo "

	</td>

	</tr>

	";

};

?>


<tr>

<td align=left valign=top colspan=2><span class=testo><b>Link:</b></span>

</td>

</tr>



<tr>

<td align=left valign=top colspan=2><textarea name=area_link cols=63 rows=05></textarea></td>

</tr>



<tr>

<td align=left valign=top colspan=2><span class=testo><b>Etichette Link:</b></span>

</td>

</tr>



<tr>

<td align=left valign=top colspan=2><textarea name=area_label cols=63 rows=05></textarea></td>

</tr>



<tr>

<td align=right valign=top><span class=testo><b>Parole chiave:</b></span></td>

<td valign=top><input type=text name=parole_chiave size=40 maxlength=200></td>

</tr>



<tr>

<td align=right valign=top colspan=2>

<?php

if (!$win_ie) {

echo "

<input type=submit value=Invia>";

} else {

echo "<input type=submit value=Invia onclick=\"inoltra();return true\">";

};

?>

</td>

</tr>



</table>

</form>

<br>				


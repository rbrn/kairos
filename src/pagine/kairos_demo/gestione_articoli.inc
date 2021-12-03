<span class=titolopagina>Gestione Articoli</span>

<hr>

<span class=testo>[<a href=index.php?risorsa=articolo_nuovo_form>Nuovo Articolo</a>]</span>

<br>

<form action="index.php"  method="post">

<input type="hidden" name="risorsa" value="articolo_cerca_elenco">

<table border=0>



<tr>

<td align=right valign=top><span class=testo><b>Cerca Articolo con titolo:</b></span></td>

<td valign=top><input type=text name=titolo size=20 maxlength=200></td>

</tr>



<tr>

<td align=right valign=top><span class=testo><b>Stato articolo:</b></span></td>

<td valign=top><select name="stato"><option>bozza<option>approvato</select></td>

</tr>





<tr>

<td align=right valign=top colspan=2><input type=submit value="cerca"></td>

</tr>

</table>

</form>

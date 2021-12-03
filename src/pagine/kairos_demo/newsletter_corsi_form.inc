<?php
$elenco_corsi="";
$query="SELECT * FROM edizioni WHERE stato='attiva' ORDER BY id_corso,id_edizione DESC";
$result=$mysqli->query($query);
	

while ($riga=$result->fetch_array()) {
$id_corso=$riga["id_corso"];
$id_edizione=$riga["id_edizione"];
$elenco_corsi .= "<option value=\"$id_corso $id_edizione\">$id_corso ($id_edizione)";
};
?>
<!-- CONTENUTO DELLA PAGINA -->
<TABLE border=0 width=100%>
<TR>
<TD>
<span class=titolopagina><b><?php echo($stringa[invio_newsletter]);?></b></span>
<br><br>
<span class=testo><b><?php echo($stringa[invio_newsletter_label]);?></b></span>
<br><br>
<FONT face=verdana size=-1>[<a href=javascript:history.back()><?php echo($stringa[indietro]);?></a>]</font><br><br>
</TD>
</tr>

<TR>
<TD>		
<form action=index.php method=post>
<input type=hidden name=risorsa value="newsletter_corsi">

<?php
	echo "
<p>
<span class=testo><b>Corso:</b></span>&nbsp;<select name=\"id_corso_edizione\">
$elenco_corsi
</select>
</p>
";
?>

<p>
<span class=testo>
<b><?php echo($stringa[oggetto]);?>:</b>
</span>
<input type=text name=oggetto size=40>
</p>

<span class=testo>
<b><?php echo($stringa[contenuto]);?>:</b><br>
</span>
<textarea name=messaggio cols=40 rows=10></textarea>

<p>
<input type=checkbox name=invia_staff>
<span class=testo>
<b><?php echo($stringa[invia_staff]);?>:</b>
</span>

</p>


<input type=submit value="<?php echo($stringa[ok]);?>">
</form>
</TD></TR>

</TABLE>
<!-- FINE CONTENUTO DELLA PAGINA -->

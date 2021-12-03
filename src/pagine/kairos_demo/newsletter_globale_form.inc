<!-- CONTENUTO DELLA PAGINA -->
<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>$stringa[utility]</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[invio_newsletter_globale])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=utility_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=utility_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";
?>

<TABLE border=0 width=100%>
<TR>
<TD>
<span class=testo><b><?php echo($stringa[invio_newsletter_globale_label]);?></b></span>
<br><br>
</TD>
</tr>

<TR>
<TD>		
<form action=index.php method=post>
<input type=hidden name=risorsa value="newsletter_globale">
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
<input type=submit value="<?php echo($stringa[ok]);?>">
</form>
</TD></TR>

</TABLE>
<!-- FINE CONTENUTO DELLA PAGINA -->
</td></tr></table><br>

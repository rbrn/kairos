<!-- CONTENUTO DELLA PAGINA -->
<?php

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[invio_newsletter])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=admin_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=admin_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";
?>

<TABLE border=0 width=100%>
<TR>
<TD>		
<form action=newsletter_unione.php method=post>

<table border=0>
<td align=right valign=top>
<span class=testo>
<b>Oggetto:</b>
</span>
</td>
<td>
<input type=text name=oggetto size=40>
</p>
</td>
</tr>

<td align=right valign=top>
<span class=testo><b>Messaggio:</b></span>
</td>
<td valign=top>
<textarea name=messaggio cols=40 rows=10></textarea>
</td>
</tr>

<tr>
<td></td>
<td>
<input type=checkbox name=noadmin>&nbsp;<span class=testo>Escludi dalla ricezione gli utenti con ruolo "admin"</span>
</td>
</tr>

<tr>
<td></td>
<td>
<input type=checkbox name=nostaff>&nbsp;<span class=testo>Escludi dalla ricezione gli utenti con ruolo "redattore"</span>
</td>
</tr>

<tr>
<td></td>
<td align=right><input type=submit value="invia newsletter">
</td></tr>
</table>

</form>


</TD></TR>

</TABLE>
<!-- FINE CONTENUTO DELLA PAGINA -->

</td></tr></table><br>

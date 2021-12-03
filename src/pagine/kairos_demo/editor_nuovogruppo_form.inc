<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[editor_gruppi])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[nuovo_gruppo])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

echo "
<table border=0 width=600>
<tr>
<td>
<form action=editor_nuovogruppo_op.php method=post name=modulo id=modulo>

<table border=0 wodth=100% cellspacing=2 cellpadding=2>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[descrizione]</b></span></p>
</td>
<td valign=top>
<input type=text size=40 name=descrizione>
</td>
</tr>

<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=right><input type=submit value=$stringa[ok]></td></tr>
</table>

</form>


</td>
</tr>
</table>

</td>
</tr>
</table><br><br>";

?>

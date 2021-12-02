<?php
$id_faq=$_REQUEST["id_faq"];
$pagina=$_REQUEST["pagina"];

$query = "SELECT * FROM faq WHERE id_faq='$id_faq'";
$result=$mysqli->query($query);
$intervento = $result->fetch_array();

$domanda=$intervento["domanda"];
$ordine = $intervento["ordine"];
$testo = $intervento["risposta"];

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td class=titolodot>$stringa[modifica_faq_corso]
</td></tr>";

echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>
";

echo "<form action=faq_edit_op.php method=post name=modulo id=modulo>\n";
echo "<input type=hidden name=id_faq value=\"$id_faq\">";
echo "<input type=hidden name=pagina_r value=\"$pagina\">";

echo "
<table border=0>";

echo "
<tr>
<td colspan=2><span class=testopiccolo><b>$stringa[posizione]</b>:</span> <input type=text name=ordine maxlength=05 size=05 value=\"$ordine\"></td>
</tr>

<tr>
<td colspan=2 valign=top><span class=testopiccolo><b>$stringa[domanda_f]:</b></span></td>
</tr>
<tr>
<td colspan=2 valign=top>
<TEXTAREA cols=70 name=domanda rows=05 wrap=virtual>".$domanda."</TEXTAREA>
</td>
</tr>
<tr>
<td colspan=2 valign=top><span class=testopiccolo><b>$stringa[risposta_f]:</b></span></td>
</tr>";

if (!$win_ie) {
echo"
<tr>
<td colspan=2 valign=top>
<TEXTAREA cols=70 name=testo rows=10 wrap=virtual>".$testo."</TEXTAREA>
</td>
</tr>";
} else {
	echo "
	<input type=\"hidden\" name=\"testo\" id=\"testo\">\n
	<tr>
	<td colspan=2 valign=top>
	";
	
	$modifica_testo=true;
	
	require "./include/editor.inc";
	echo "	
	</td>
	</tr>
	";
};

echo "
</td></tr>
</table>";


if (!$win_ie) {
echo "
<input type=submit value=$stringa[ok]>";
} else {
echo "<input type=submit value=$stringa[ok] onclick=\"inoltra();return true\">";
};

echo "
</form>
";
?>
</td></tr>
</table>




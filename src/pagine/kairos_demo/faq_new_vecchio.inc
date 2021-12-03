<?php
$id_forum=$_REQUEST["id_forum"];
$id_post=$_REQUEST["id_post"];
$op=$_REQUEST["op"];
$pagina=$_REQUEST["pagina"];

if ($pagina=="helpdesk") {
	$query="SELECT MAX(ordine) as max_ord FROM faq WHERE id_corso=''";
} else {
	$query="SELECT MAX(ordine) as max_ord FROM faq WHERE id_corso='$id_corso_s'";
};

$result=$mysqli->query($query);
$riga=$result->fetch_array();
$ordine=$riga["max_ord"]+1;

if ($op<>'nuovo') {
$query = "SELECT * FROM forum_posts WHERE id_forum='$id_forum' AND id_post='$id_post'";

$result=$mysqli->query($query);
$intervento = $result->fetch_array();

$domanda="";
$testo = $intervento["testo"];
} else {
	$domanda="";
	$testo="";
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td class=titolodot>
$stringa[ricopia_in_faq_corso]
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

echo "<form action=faq_new_op.php method=post name=modulo id=modulo>\n";
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
<TEXTAREA cols=70 name=domanda rows=05 wrap=virtual>$domanda</TEXTAREA>
</td>
</tr>
<tr>
<td colspan=2 valign=top><span class=testopiccolo><b>$stringa[risposta_f]:</b></span></td>
</tr>";

if (!$win_ie) {
echo"
<tr>
<td colspan=2 valign=top>
<TEXTAREA cols=70 name=testo rows=10 wrap=virtual>$testo</TEXTAREA>
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




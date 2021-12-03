<!-- CONTENUTO DELLA PAGINA -->
<?php
$tipo_news=$_REQUEST["tipo_news"];
$id_news=$_REQUEST["id_news"];

if ($tipo_news==0) {
	if (!$id_corso_s) {		
		$query="SELECT * FROM hp_news WHERE tipo=0 AND posizione='$posizione' AND (id_corso IS NULL OR id_corso='') AND (id_edizione IS NULL OR id_edizione='')";
	} else {
		$query="SELECT * FROM hp_news WHERE tipo=0 AND posizione='$posizione' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
	};
	
	$result=$mysqli->query($query);
	$news0=$result->fetch_array();
	$url=$news0["url"];
	$url_label=$news0["url_label"];
	$testo=$news0["testo"];
	$testo=htmlentities($testo);
	
	for ($i=1;$i<=$n_news;$i++) {
		if (!$id_corso_s) {		
			$query="SELECT * FROM hp_news WHERE tipo=0 AND posizione='r".$i."' AND (id_corso IS NULL OR id_corso='') AND (id_edizione IS NULL OR id_edizione='')";
		} else {
			$query="SELECT * FROM hp_news WHERE tipo=0 AND posizione='r".$i."' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
		};
		$result=$mysqli->query($query);
		$news[$i]=$result->fetch_array();
		$btn[$i]="";
		if ($news[$i]) $btn[$i]="disabled";
		$btnc[$i]="";
		if ($posizione=="r".$i) $btnc[$i]="checked";
		
	};
	
} else {
	$query="SELECT * FROM hp_news WHERE id_news='$id_news'";
	$result=$mysqli->query($query);
	$news0=$result->fetch_array();
	$url=$news0["url"];
	$url_label=$news0["url_label"];
	$testo=$news0["testo"];
	$testo=htmlentities($testo);
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>
$stringa[modifica_news]
</td></tr>
<tr><td>";

echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>
<form action=news_mod_go.php  method=post name=modulo id=modulo>
<input type=\"hidden\" name=\"tipo_news\" value=\"$tipo_news\">
<input type=\"hidden\" name=\"id_news\" value=\"$id_news\">
<input type=\"hidden\" name=\"ex_posizione\" value=\"$posizione\">
	
<TABLE border=0 width=500>
";

if ($tipo_news==0) {
echo "
<TR> 
<TD align=right valign=top><span class=testo><p><strong>$stringa[posizione_news]:</strong></span></p>
</TD>
<TD valign=top>
<table border=1 cellpadding=5>
";

for ($j=1;$j<=$n_news/2;$j++) {
	$i=2*($j-1)+1;
	$i2=$i+1;
	echo "
<tr>
<td valign=middle align=center><input type=radio name=posizione value=\"r".$i."\" ". $btn[$i]." ".$btnc[$i]."></td>
<td valign=middle align=center><input type=radio name=posizione value=\"r".$i2."\" ". $btn[$i2]." ".$btnc[$i2]."></td>
</tr>";
};

echo"
</table>
</TD>

</TR>

";
};


echo "
<TR> 
<TD align=right valign=top><p><span class=testo><strong>$stringa[titolo]:</strong></span></p>
</TD>
<TD>
<INPUT type=text maxLength=100 name=url_label  size=60 value=\"$url_label\">
</TD>
</TR>


<TR> 
<TD align=right valign=top><p><span class=testo><strong>$stringa[url]:</strong></span></p>
</TD>
<TD>
<INPUT type=text maxLength=200 name=url  size=60 value=\"$url\">
<span class=testopiccolo>($stringa[facoltativo])</span>
</TD>
</TR>";


echo "
<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[testo]:</b></span></td>
</tr>";


echo "
<tr>
<td colspan=2 valign=top>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<TEXTAREA id=\"testo\" cols=80 name=\"testo\" rows=30>".$testo."</TEXTAREA>
</td></tr>
</table>
</td>
</tr>";


echo "

</TABLE>

<BR>

<P> ";


echo "<input type=\"submit\" name=\"ok\" value=\"$stringa[ok]\" />";

echo "
</P>

</FORM>

</td></tr>

</table>";

echo "</td></tr>

</table><br>";



?>



<!-- FINE CONTENUTO DELLA PAGINA -->


<script language="javascript">
function seleziona_forum(targ,selObj){ 
   var id_forum=selObj.options[selObj.selectedIndex].value;
   if (id_forum)  eval(targ+".location='index.php?risorsa=forum_elenco_gruppo&id_gruppo_elenco="+id_forum+"'");
 }
</script>

<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr>
<td valign=top width=77% class=titolodot>";
echo strtoupper($stringa[web_forum])."</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=20%>&nbsp;</td>";
echo "</tr>";

echo "<tr><td valign=top width=77%>";

echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr><td>";

echo "	
<p>
<span class=testopiccolo>$stringa[forum_intro]</span>
</p>
";

if ($id_corso_s) {
$query2 = "SELECT * FROM forum WHERE (tipo=1 or tipo=3) AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='' AND (archiviato IS NULL or archiviato=0) ORDER BY ordine";

$forum_corso=get_forum($query2);

if (count($forum_corso)) {
echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"left\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<span class=titolo>&nbsp;<b>$stringa[forum_corso]</b></span>
</td>
</tr>
		
<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
\n";

for  ($i=0;$i<count($forum_corso);$i++) {
	echo "
	<tr>
	<td valign=top><img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=\"testo\">$forum_corso[$i]</span></td></tr>";	
};

$query2 = "SELECT * FROM forum WHERE (tipo=1 or tipo=3) AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='' AND archiviato=1 ORDER BY ordine";

$forum_corso_archiviato=get_forum($query2);
	if (count($forum_corso_archiviato)) {
		echo "<tr>
	<td valign=top>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"left\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<span class=titolo>&nbsp;<a href=\"javascript:void(0);\" onclick=\"toggle_forum('archiviati_corso')\"><img src=\"img/plus.gif\" name=\"img_archiviati_corso\" id=\"img_archiviati_corso\" alt=\"apri elenco\" border=\"0\"></a>&nbsp;<b>Forum Archiviati</b></span>
</td>
</tr>
		
<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\" id=\"archiviati_corso\" style=\"display:none;\">
\n";
	
		for  ($i=0;$i<count($forum_corso_archiviato);$i++) {
	echo "
	<tr>
	<td valign=top><img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=\"testo\">$forum_corso_archiviato[$i]</span></td></tr>";	
};
		echo "</table>";
		echo "</td></tr></table>";
		
		echo "</td></tr>";
		
	};

echo "
</table>
</td></tr></table><br>";
};
};

if ($ruolo<>'staff' and $ruolo<>'admin' and $id_gruppo_s and $id_corso_s) {
	$query2 = "SELECT * FROM forum WHERE tipo=1 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_s' ORDER BY ordine";
	
	$forum_gruppo=get_forum($query2);

	if (count($forum_gruppo)) {

	echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"left\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<span class=titolo>&nbsp;<b>$stringa[forum_gruppo]: $descr_gr</b></span>
</td>
</tr>
		
<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
\n";

for  ($i=0;$i<count($forum_gruppo);$i++) {
	echo "
	<tr>
	<td valign=top><img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testo>$forum_gruppo[$i]</span></td></tr>";	
};

$query2 = "SELECT * FROM forum WHERE tipo=1 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_s' AND archiviato=1 ORDER BY ordine";

$forum_gruppo_archiviato=get_forum($query2);
	if (count($forum_gruppo_archiviato)) {
		echo "<tr>
	<td valign=top>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"left\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<span class=titolo>&nbsp;<a href=\"javascript:void(0);\" onclick=\"toggle_forum('archiviati_gruppo')\"><img src=\"img/plus.gif\" name=\"img_archiviati_gruppo\" id=\"img_archiviati_corso\" alt=\"apri elenco\" border=\"0\"></a>&nbsp;<b>Forum Archiviati</b></span>
</td>
</tr>
		
<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\" id=\"archiviati_gruppo\" style=\"display:none;\">
\n";
	
		for  ($i=0;$i<count($forum_gruppo_archiviato);$i++) {
			echo "
			<tr>
				<td valign=top><img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=\"testo\">$forum_gruppo_archiviato[$i]</span></td></tr>";	
		};
		echo "</table>";
		echo "</td></tr></table>";
		
		echo "</td></tr>";
	};
	
echo "
</table>
</td></tr></table><br>";
	};
};

if (($ruolo=='staff' or $ruolo=='admin') and $id_corso_s) {

$query_gruppo="SELECT id_gruppo,descrizione FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo_gruppo=0 AND id_tutor='$kairos_cookie[0]' ORDER BY id_gruppo";
$result_gruppo=$mysqli->query($query_gruppo);

while ($riga_gruppo=$result_gruppo->fetch_array()) {
	$id_gruppo_s=$riga_gruppo["id_gruppo"];
	$descr_gruppo_s=$riga_gruppo["descrizione"];


	$query2 = "SELECT * FROM forum WHERE tipo=1 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_s' ORDER BY ordine";
	
	$forum_gruppo=get_forum($query2);

	if (count($forum_gruppo)) {
	echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"left\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<span class=titolo>&nbsp;<b>$stringa[forum_del_gruppo]: $descr_gruppo_s</b></span>
</td>
</tr>
		
<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
\n";

for  ($i=0;$i<count($forum_gruppo);$i++) {
	echo "
	<tr>
	<td valign=top><img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testo>$forum_gruppo[$i]</span></td></tr>";	
};

echo "
</table>
</td></tr></table><br>";
	};
	
};
};

if ($ruolo<>'staff' and $ruolo<>'admin' and $id_corso_s) {
$query_gruppo="SELECT a.id_gruppo,a.descrizione FROM gruppo_utenti as a,iscrizioni_gruppo_pw as b WHERE a.id_corso=b.id_corso AND a.id_edizione=b.id_edizione AND a.id_gruppo=b.id_gruppo AND a.tipo_gruppo=1 AND a.id_corso='$id_corso_s' AND a.id_edizione='$id_edizione_s' AND b.id_utente='$kairos_cookie[0]' ORDER BY id_gruppo";
$result_gruppo=$mysqli->query($query_gruppo);

while ($riga_gruppo=$result_gruppo->fetch_array()) {
	$id_gruppo_s=$riga_gruppo["id_gruppo"];
	$descr_gruppo_s=$riga_gruppo["descrizione"];


	$query2 = "SELECT * FROM forum WHERE tipo=1 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_s' ORDER BY ordine";
	
	$forum_gruppo_pw=get_forum($query2);

	if (count($forum_gruppo_pw)) {
	echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"left\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<span class=titolo>&nbsp;<b>$stringa[forum_del_gruppo_pw]: $descr_gruppo_s</b></span>
</td>
</tr>
		
<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
\n";

for  ($i=0;$i<count($forum_gruppo_pw);$i++) {
	echo "
	<tr>
	<td valign=top><img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testo>$forum_gruppo_pw[$i]</span></td></tr>";	
};

echo "
</table>
</td></tr></table><br>";
	};
	
};	
};

if (($ruolo=='staff' or $ruolo=='admin') and $id_corso_s) {

$query_gruppo="SELECT id_gruppo,descrizione FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo_gruppo=1 AND id_tutor='$kairos_cookie[0]' ORDER BY id_gruppo";
$result_gruppo=$mysqli->query($query_gruppo);

while ($riga_gruppo=$result_gruppo->fetch_array()) {
	$id_gruppo_s=$riga_gruppo["id_gruppo"];
	$descr_gruppo_s=$riga_gruppo["descrizione"];

	$query2 = "SELECT * FROM forum WHERE tipo=1 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_s' ORDER BY ordine";
	
	$forum_gruppo_pw=get_forum($query2);

	if (count($forum_gruppo_pw)) {
	echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"left\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<span class=titolo>&nbsp;<b>$stringa[forum_del_gruppo_pw]: $descr_gruppo_s</b></span>
</td>
</tr>
		
<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
\n";

for  ($i=0;$i<count($forum_gruppo_pw);$i++) {
	echo "
	<tr>
	<td valign=top><img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testo>$forum_gruppo_pw[$i]</span></td></tr>";	
};

echo "
</table>
</td></tr></table><br>";
	};
	
};
};

if ($cod_area<>"kairos_area_corsi") {
$query2 = "SELECT * FROM forum WHERE tipo=0 ORDER BY ordine";
$forum_comuni=get_forum($query2);

if (count($forum_comuni)) {
	echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"left\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<span class=titolo>&nbsp;<b>$stringa[forum_generali]</b></span>
</td>
</tr>
		
<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
\n";

for  ($i=0;$i<count($forum_comuni);$i++) {
	echo "
	<tr>
	<td valign=top><img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testo>$forum_comuni[$i]</span></td></tr>";	
};

echo "
</table>
</td></tr></table><br>";
};
};


echo "</td></tr></table>";

echo "</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=20%>";

echo "		
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr> 
<td width=\"100%\" align=\"center\" valign=\"middle\"> 
<img src=\"img/ico_forum_utils.gif\" width=\"20\" height=\"20\" alt=\"\" border=\"0\" align=\"middle\"><span class=testo>&nbsp;<b>$stringa[utilities]</b></span>
</td>
</tr>

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">
\n";

if ($id_corso_s) {
echo "<tr><td><table border=0><tr><td valign=\"middle\">
<a href=index.php?risorsa=faq onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('Image_faq','','img/ico_forum_faq_over.gif',1)\"><img src=\"img/ico_forum_faq.gif\" width=\"20\" height=\"20\" alt=\"\" border=\"0\" name=\"Image_faq\"></a></td><td valign=\"middle\"><span class=testo><b>$stringa[faq]</b>: $stringa[archivio_faq]</span></td></tr></table></td></tr>";

echo "
<tr> 
<td bgcolor=\"$colore_scuro_neutro\" height=\"1\"></td>
</tr>";

};

echo "
<tr><td>

<TABLE WIDTH=\"100%\" CELLSPACING=\"0\" CELLPADDING=\"0\" BORDER=\"0\">
		<TR>
			<TD ALIGN=\"left\">
				<FORM METHOD=\"get\" ACTION=\"index.php\">
				<input type=\"hidden\" name=\"risorsa\" value=\"cerca_forum\">
				<input type=\"hidden\" name=\"pagina\" value=\"1\">
					<TABLE CELLSPACING=\"10\" CELLPADDING=\"0\" BORDER=\"0\">
						<TR>
							<TD><img src=\"img/ico_forum_cerca.gif\" width=\"20\" height=\"20\" alt=\"\" border=\"0\">&nbsp;<span class=testo><b>$stringa[cerca_forum]</b>: </span><INPUT TYPE=\"text\" NAME=\"stringa_cerca\" SIZE=\"25\" TABINDEX=\"1\">&nbsp;</TD>
							
						</tr>
						<tr>
							<TD>
								<SELECT NAME=\"pag_size\" TABINDEX=\"2\">
									<OPTION VALUE=\"5\">$stringa[risultati_5]</OPTION>
									<OPTION SELECTED VALUE=\"10\">$stringa[risultati_10]</OPTION>
									<OPTION VALUE=\"20\">$stringa[risultati_20]</OPTION>
									<OPTION VALUE=\"30\">$stringa[risultati_30]</OPTION>
									<OPTION VALUE=\"50\">$stringa[risultati_50]</OPTION>
								</SELECT>
							</TD>
						</TR>
						<tr>
						<TD><INPUT TYPE=\"submit\" VALUE=\"$stringa[cerca]\" TABINDEX=\"3\" class=\"testo\">&nbsp;</TD>
						</tr>
					</TABLE>
				</FORM>
			</TD>
		</TR>
	</TABLE>";



echo "</td></tr>";

$elenco_gruppi="";
$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_gruppo";
$result=$mysqli->query($query);
while ($riga=$result->fetch_array()) {
	$id_gruppo=$riga["id_gruppo"];
	$descr_gruppo=$riga["descrizione"];
	$elenco_gruppi .= "<option value=\"$id_gruppo\">$descr_gruppo</option>";
};

$lista=true;
$query_g="SELECT id_forum FROM forum WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo<>'' OR id_gruppo<>NULL)";
$result_g=$mysqli->query($query_g);
if (!$result_g->num_rows) $lista=false;

if ($lista) {

$elenco_gruppi="<option value=\"\" selected>(seleziona)".$elenco_gruppi;

echo "
<tr> 
<td bgcolor=\"$colore_scuro_neutro\" height=\"1\"></td>
</tr>";

echo "
<tr><td>
<span class=testo><b>Altri forum</b> </span><br>

<span class=testo>mostra i forum del gruppo:</span>
<select name=\"id_gruppo_elenco\" class=\"testopiccolo\" onChange=\"seleziona_forum('parent',this)\">
$elenco_gruppi
</select> 
</td></tr>";
};

echo "</table>";
echo "</td></tr></table>";

echo "</td>";
echo "
</tr></table><br>";

echo "</td></tr></table>";

?>




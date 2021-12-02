<?php
$query2 = "SELECT * FROM forum WHERE id_forum='$id_forum'";
$result2=$mysqli->query($query2);
$dati_forum=$result2->fetch_array();

$descr_forum = $dati_forum["descrizione"];
// prelevo i dati dell'intervento da modificare
$query = "SELECT * FROM forum_posts WHERE id_forum='$id_forum' AND id_post='$id_post'";
$result=$mysqli->query($query);
$intervento = $result->fetch_array();
$id_autore=$intervento["id_autore"];


$titolo = $stringa[modifica_intervento];

$oggetto = htmlentities($intervento["oggetto"]);
$testo = $intervento["testo"];

$id_post_padre = $intervento["id_post_padre"];
$nome_file = $intervento["nome_file"];
$file_size = $intervento["file_size"];
$repemail = $intervento["repemail"];	
$icona_post = $intervento["icona_post"];


if (!$icona_post) {
	$icona_post = "messaggio";
};


echo "<table border=0 cellspacing=10 width=100%>";
echo "<tr><td class=titolodot>".strtoupper($stringa[web_forum])."</td></tr>";

echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>
<p>
<span class=testo><b>$titolo</b></span>
</p>
<p align=left>
<span class=testo>
<b>$descr_forum</b>
</span>
</p>
";


if ($dati_forum["file_allegati"]=='1') {
	echo "
	<FORM action=forum_update_post.php encType=multipart/form-data method=post name=modulo id=modulo>\n
	<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>\n";
} else {
	echo "<form action=forum_update_post.php method=post name=modulo id=modulo>\n";
};

echo "
<input type=hidden name=id_forum value=".$id_forum.">
<input type=hidden name=id_post value=".$id_post.">
<input type=hidden name=vista value=".$vista.">
<input type=hidden name=modo value=".$modo.">
<input type=hidden name=pagina value=".$pagina.">";

echo "<input type=hidden name=ex_nome_file value=$nome_file>";
echo "
<table border=0>";

echo "
<tr>
<td align=right valign=top><span class=testopiccolo><b>$stringa[autore]</b>:</span></td>
<td valign=top><span class=testopiccolo>$id_autore</span></td>
</tr>

<tr>
<td align=right valign=top><span class=testopiccolo><b>$stringa[oggetto]</b>:</span></td>
<td valign=top><input type=text name=oggetto maxlength=150 size=60 value=\"".$oggetto."\"></td>
</tr>
";

if ($wimba) {
if ($wimba_cookie=='on') {
	$query_audio="SELECT * FROM forum_audio WHERE id_post='$id_post'";
	$result_audio=$mysqli->query($query_audio);
	$riga_audio=$result_audio->fetch_array();
	$mid=$riga_audio["mid"];
	
	echo "
		<tr>
<td valign=top align=right>
<span class=testopiccolo><b>Registra un messaggio:</b></span>
</td>
<td>
<SCRIPT type=\"text/javascript\" SRC=\"http://cgi3.garamond.it:8080/wimba/ve/record.js\"></SCRIPT>
<SCRIPT type=\"text/javascript\">
  var w_p = new Object();
  
   w_p.mid=\"$mid\";
   w_p.rid=\"0-1074674761874\";
  w_p.play_last=\"true\";
  w_p.auto_validate=\"true\";
  w_p.max_message_length=300;
  
  
  if (window.w_ve_record_tag) w_ve_record_tag(w_p);
else document.write(\"Problemi con il server audio\");
</SCRIPT>
<input type=hidden name=mid value=\"$mid\">
<span class=testo><a href=\"audio_switch.php?audio=off&".$_SERVER["QUERY_STRING"]."\" $target>[Audio Off]</a></span>&nbsp;
</td></tr>";

} else {
echo "
<tr>
<td valign=top align=right>
<span class=testopiccolo><b>Registra un messaggio:</b></span>
</td>
<td valign=top><span class=testo>
<a href=\"audio_switch.php?audio=on&".$_SERVER["QUERY_STRING"]."\" $target>[Audio On]</a></span>&nbsp;
</td></tr>";
};
};

if (!$win_ie) {
echo"
<tr>
<td colspan=2 valign=top><span class=testopiccolo><b>$stringa[intervento]:</b></span></td>
</tr>

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

if ($dati_forum["file_allegati"]=='1') {
echo "
<tr>
<td align=right valign=top><span class=testopiccolo><b>$stringa[allega_file]</b>:</span></td>
<td valign=top><INPUT name=nome_file type=file></td>
</tr>
";
};


if ($nome_file) {
	echo "<tr>
		<td colspan=2 align=left valign=top>";
	printf("<span class=testopiccolo><b>%s:</b> <a href=scarica_forum.php?file=%s>%s</a> <i>(%s)</i></span>",$stringa[file_allegato],$nome_file,$nome_file,stringa_filesize($file_size));
	echo "</td></tr>
	<tr>
	<td>&nbsp;</td>
	<td align=left valign=top>
	<input type=checkbox name=delallegato><span class=testopiccolo>$stringa[cancella_allegato]</span>";
	echo "</td></tr>";
};


echo "
<tr>
<td valign=top align=right>
<span class=testopiccolo><b>$stringa[icona]:</b></span>
</td>

<td><input type=radio name=icona_post value=messaggio ";

if ($icona_post=="messaggio") { echo "checked"; };
echo "
> <img src=img/forum/messaggio.gif alt=$stringa[generica]> <input type=radio name=icona_post value=domanda ";
if ($icona_post=="domanda") { echo "checked"; };
echo "
> <img src=img/forum/domanda.gif alt=$stringa[domanda]> <input type=radio name=icona_post value=idea ";

if ($icona_post=="idea") { echo "checked"; };
echo "
> <img src=img/forum/idea.gif alt=$stringa[idea]> <input type=radio name=icona_post value=approvo ";

if ($icona_post=="approvo") { echo "checked"; };
echo "
> <img src=img/forum/approvo.gif alt=$stringa[approvo]> <input type=radio name=icona_post value=disapprovo ";

if ($icona_post=="disapprovo") { echo "checked"; };
echo "
> <img src=img/forum/disapprovo.gif alt=$stringa[disapprovo]> <input type=radio name=icona_post value=importante ";

if ($icona_post=="importante") { echo "checked"; };
echo "
> <img src=img/forum/importante.gif alt=$stringa[importante]>
<br> 
<input type=radio name=icona_post value=confuso ";

if ($icona_post=="confuso") { echo "checked"; };
echo "
> <img src=img/forum/confuso.gif alt=$stringa[confuso]> <input type=radio name=icona_post value=contento ";

if ($icona_post=="contento") { echo "checked"; };
echo "
> <img src=img/forum/contento.gif alt=$stringa[contento]> <input type=radio name=icona_post value=triste ";

if ($icona_post=="triste") { echo "checked"; };
echo "
> <img src=img/forum/triste.gif alt=$stringa[triste]> <input type=radio name=icona_post value=scherzo ";

if ($icona_post=="scherzo") { echo "checked"; };
echo "
> <img src=img/forum/scherzo.gif alt=$stringa[scherzo]> 
<input type=radio name=icona_post value=arrabbiato ";

if ($icona_post=="arrabbiato") { echo "checked"; };
echo "
> <img src=img/forum/arrabbiato.gif alt=$stringa[arrabbiato]> <input type=radio name=icona_post value=moltoarrabbiato ";

if ($icona_post=="moltoarrabbiato") { echo "checked"; };
echo "
> <img src=img/forum/moltoarrabbiato.gif alt=$stringa[moltoarrabbiato]> 
<br>
<input type=radio name=icona_post value=fico ";

if ($icona_post=="fico") { echo "checked"; };
echo "
> <img src=img/forum/fico.gif alt=$stringa[fico]>
</td>
</tr>
\n";

echo "
<tr>
<td>&nbsp;</td>
<td align=left valign=top>
<input type=checkbox name=repemail ";

if ($repemail) {
	echo "checked";
};

echo"> <span class=testopiccolo>$stringa[invia_repliche]</span>
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

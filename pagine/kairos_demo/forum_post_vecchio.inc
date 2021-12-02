<?php
$query2 = "SELECT * FROM forum WHERE id_forum='$id_forum'";
$result2=$mysqli->query($query2);
$dati_forum=$result2->fetch_array();
$descr_forum = $dati_forum["descrizione"];

if ($op=='replica') {
	// prelevo i dati dell'intervento padre
	$query = "SELECT * FROM forum_posts WHERE id_forum='$id_forum' AND id_post='$id_post_padre'";
	$result=$mysqli->query($query);
	$intervento_padre = $result->fetch_array();
	$id_autore=$intervento_padre["id_autore"];
	$query_u="SELECT * FROM utenti WHERE id_utente='$id_autore'";
	$result_u=$mysqli->query($query_u);
	$dati_autore = $result_u->fetch_array();
	$nome_autore=$dati_autore["nome"]." ".$dati_autore["cognome"];
	$titolo = $stringa[replica_intervento];
	$oggetto = htmlentities("Re: ".$intervento_padre["oggetto"]);
	$testo = "\n\n\n<br><br><br><b>---- ".
	"($id_autore) $nome_autore"." $stringa[ha_scritto]:</b><br><i>\n".
	$intervento_padre["testo"].
	"<br></i>\n<b>--------------------------------</b>\n<br>";
	$modifica_testo=true;
} else {
	$titolo = $stringa[nuovo_intervento];
	$oggetto = "";
	$testo = "";
	$id_post_padre="0";
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
<span class=testo><b>$descr_forum</b></span>
</p>
";

if ($dati_forum["file_allegati"]=='1') {
	echo "
	<FORM action=forum_store_post.php encType=multipart/form-data method=post name=modulo id=modulo>\n
	<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>\n";
} else {
	echo "<form action=forum_store_post.php method=post name=modulo id=modulo>\n";
};

echo "
<input type=hidden name=id_forum value=".$id_forum.">
<input type=hidden name=id_post_padre value=".$id_post_padre.">
<input type=hidden name=vista value=".$vista.">
<input type=hidden name=modo value=".$modo.">
<input type=hidden name=pagina value=".$pagina.">";

echo "
<table border=0>";
echo "
<tr>
<td align=right valign=top><span class=testopiccolo><b>$stringa[autore]</b>:</span></td>
<td valign=top><span class=testopiccolo>$id_utente</span></td>
</tr>
";

printf('
<tr>
<td align=right valign=top><span class=testopiccolo><b>%s</b>:</span></td>
<td valign=top><input type=text name=oggetto maxlength=150 size=60 value="%s"></td>
</tr>',$stringa[oggetto],$oggetto);

if ($wimba) {	
if ($wimba_cookie=='on') {
$mid = uniqid("$cod_area."); 
echo "
<tr>
<td valign=top align=right>
<span class=testopiccolo><b>Registra un messaggio:</b></span>
</td>
<td valign=top>
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
	echo "<input type=\"hidden\" name=\"testo\" id=\"testo\">\n
	<tr>
	<td colspan=2 valign=top>
	";
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

echo "
<tr>
<td valign=top align=right>
<span class=testopiccolo><b>$stringa[icona]:</b></span>
</td>

<td><input type=radio checked name=icona_post value=messaggio> <img src=img/forum/messaggio.gif alt=$stringa[generica]> <input type=radio name=icona_post value=domanda> <img src=img/forum/domanda.gif alt=$stringa[domanda]> <input type=radio name=icona_post value=idea> <img src=img/forum/idea.gif alt=$stringa[idea]> <input type=radio name=icona_post value=approvo> <img src=img/forum/approvo.gif alt=$stringa[approvo]> <input type=radio name=icona_post value=disapprovo> <img src=img/forum/disapprovo.gif alt=$stringa[disapprovo]> <input type=radio name=icona_post value=importante> <img src=img/forum/importante.gif alt=$stringa[importante]>
<br> 
<input type=radio name=icona_post value=confuso> <img src=img/forum/confuso.gif alt=$stringa[confuso]> <input type=radio name=icona_post value=contento> <img src=img/forum/contento.gif alt=$stringa[contento]> <input type=radio name=icona_post value=triste> <img src=img/forum/triste.gif alt=$stringa[triste]> <input type=radio name=icona_post value=scherzo> <img src=img/forum/scherzo.gif alt=$stringa[scherzo]> 
<input type=radio name=icona_post value=arrabbiato> <img src=img/forum/arrabbiato.gif alt=$stringa[arrabbiato]> <input type=radio name=icona_post value=moltoarrabbiato> <img src=img/forum/moltoarrabbiato.gif alt=$stringa[moltoarrabbiato]> 
<br>
<input type=radio name=icona_post value=fico> <img src=img/forum/fico.gif alt=$stringa[fico]>
</td>
</tr>
\n";

echo "
<tr>
<td>&nbsp;</td>
<td align=left valign=top>
<input type=checkbox name=repemail> <span class=testopiccolo>$stringa[invia_repliche]</span>
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
<br>

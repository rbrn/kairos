<?php
$query2 = "SELECT * FROM forum WHERE id_forum='$id_forum'";
$result2=$mysqli->query($query2);
$dati_forum=$result2->fetch_array();
$descr_forum = $dati_forum["descrizione"];
$tipo_forum=$dati_forum["tipo"];
$id_gruppo_forum=strtolower($dati_forum[id_gruppo]);
$id_gruppo_s=strtolower($id_gruppo_s);

$descr_gr_forum="";

$descr_gr_forum="";
if ($id_gruppo_forum) {
$query_gr="select * from gruppo_utenti where id_gruppo='$id_gruppo_forum' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result_r=$mysqli->query($query_gr);
$riga_gr=$result_r->fetch_array();
$tipo_gruppo_gr=$riga_gr["tipo_gruppo"];
$descr_gr=$riga_gr["descrizione"];

if ($tipo_gruppo_gr==0) {
	$pagina_g="gruppo_iscritti.php";
} else {
	$pagina_g="gruppo_pw_iscritti.php";
};

$descr_gr_forum=" ($stringa[gruppo]: <a class=miolink href=\"javascript:;\" title=\"$stringa[componenti_gruppo]\" onclick=\"javascript:apri_scheda('$pagina_g?id_gruppo=$id_gruppo_forum',                   'myRemoteGruppo',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowGruppo');\">$descr_gr</a>)";
};


$edit_forum=true;

if ($ruolo<>"staff" and $ruolo<>"admin") {
	if ($id_gruppo_forum AND !$tipo_gruppo_gr AND $id_gruppo_forum<>$id_gruppo_s) {
		$edit_forum=false;
	} else {
		if ($id_gruppo_forum AND $tipo_gruppo_gr) {
			$query_f="SELECT id_utente FROM iscrizioni_gruppo_pw WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_forum' AND id_utente='$kairos_cookie[0]'";
			$result_f=$mysqli->query($query_f);
			if (!$result_f->num_rows) $edit_forum=false;
		};
	};
};

//if ($kairos_cookie[0]=="ospite" and $cod_area=="kairos_eprof") $edit_forum=false;

//marco l'intervento come letto dall'utente
	
	if ($id_utente<>"garamond") {
	$query="SELECT id_post FROM forum_read WHERE id_post='$id_post' AND id_utente='$id_utente'";
	$result=$mysqli->query($query);
	if (!$result->num_rows) {
		$query="INSERT INTO forum_read(id_post,id_forum,id_utente,data_read,azione,id_corso,id_edizione,id_gruppo) VALUES ('$id_post','$id_forum','$id_utente',NOW(),'letto','$id_corso_s','$id_edizione_s','$id_gruppo_s')";
		$result=$mysqli->query($query);
	};
	};

// prelevo i dati dell'intervento
$query = "SELECT id_post,oggetto,id_autore,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,testo,nome_file,file_size,id_post_padre,icona_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post='$id_post'";
$result=$mysqli->query($query);
$intervento = $result->fetch_array();


//ottengo il link per il prev.
$query = "SELECT MAX(id_post) as id_prev FROM forum_posts WHERE id_forum='$id_forum' AND id_post<'$id_post'";
$result=$mysqli->query($query);
$id_prev = $result->fetch_array();

//ottengo il link per il succ.
$query = "SELECT MIN(id_post) as id_succ FROM forum_posts WHERE id_forum='$id_forum' AND id_post>'$id_post'";

$result=$mysqli->query($query);
$id_succ = $result->fetch_array();

if ($vista=='data') {
	$id_start=$id_post;
} else {
	$id_start=ascendente($id_post);
};

//vedo se l'intervento ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ marcato per l'utente
$query_mark = "SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post'";
$result_mark=$mysqli->query($query_mark);
$riga_mark = $result_mark->fetch_array();

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

echo "
<table border=0 width=100% cellspacing=0>";

echo "<tr><td width=67% class=titolodot>".strtoupper($stringa[web_forum])."</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=30%>&nbsp;</td>";
echo "</tr>";

echo "
<tr>
<td valign=top width=67%>";

echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr><td>";

echo "
<span class=testo><b>$descr_forum</b> $descr_gr_forum</span>
<br><br>
";

echo "
<table border=0>
<tr>";

echo "<td valign=middle><a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_indice','','img/ico_forum_indice_over.gif',1)\"><img src=\"img/ico_forum_indice.gif\" width=\"20\" height=\"20\" alt=\"$stringa[indice]\" border=\"0\" name=\"img_indice\"></a></td><td valign=middle><span class=testopiccolo><a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_indice','','img/ico_forum_indice_over.gif',1)\">$stringa[indice]</a></span></td>";

echo "<td width=10>&nbsp;</td>";

if ($id_prev[id_prev]) {
	echo "<td valign=middle><a href=index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_prev[id_prev]&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_prec','','img/ico_forum_prec_over.gif',1)\"><img src=\"img/ico_forum_prec.gif\" width=\"20\" height=\"20\" alt=\"$stringa[prec]\" border=\"0\" name=\"img_prec\"></a></td><td valign=middle><span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_prev[id_prev]&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_prec','','img/ico_forum_prec_over.gif',1)\">$stringa[prec]</a></span></td>";
} else {
	//echo "<td valign=middle><img src=\"img/ico_forum_prec.gif\" width=\"20\" height=\"20\" alt=\"$stringa[prec]\" border=\"0\"></a></td><td valign=middle><span class=testopiccolo>$stringa[prec]</span></td>";
};

echo "<td width=10>&nbsp;</td>";

if ($id_succ[id_succ]) {
	echo "<td valign=middle><a href=index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_succ[id_succ]&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_succ','','img/ico_forum_succ_over.gif',1)\"><img src=\"img/ico_forum_succ.gif\" width=\"20\" height=\"20\" alt=\"$stringa[prec]\" border=\"0\" name=\"img_succ\"></a></td><td valign=middle><span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_succ[id_succ]&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_succ','','img/ico_forum_succ_over.gif',1)\">$stringa[succ]</a></span></td>";
} else {
	//echo "<td valign=middle><img src=\"img/ico_forum_succ.gif\" width=\"20\" height=\"20\" alt=\"$stringa[prec]\" border=\"0\"></a></td><td valign=middle><span class=testopiccolo>$stringa[succ]</span></td>";
};

echo 
"</tr></table>
<br>\n";

$id_autore=$intervento["id_autore"];
$icona_post = $intervento["icona_post"];

$immagine=false;
$file_immagine = $PATH_ROOT_FILE."foto_utenti/$cod_area/".$id_autore.".gif";
$file_immagine = strtolower($file_immagine);

if (file_exists($file_immagine)) {
	$nome_immagine = "$id_autore.gif";
	$nome_immagine = strtolower($nome_immagine);
	$immagine = true;
};

if (!$immagine) {
	$file_immagine = $PATH_ROOT_FILE."foto_utenti/$cod_area/".$id_autore.".jpg";
	$file_immagine = strtolower($file_immagine);
	if (file_exists($file_immagine)) {
		$nome_immagine = "$id_autore.jpg";
		$nome_immagine = strtolower($nome_immagine);
		$immagine = true;
	};
};



$tag_img="";
$max_img_size=120;
if ($immagine) {
	$size=getimagesize("foto_utenti/$cod_area/$nome_immagine");
	$w=$size[0];
	$h=$size[1];
	
	while ($w>$max_img_size or $h>$max_img_size) {
	
		if ($w>$max_img_size) {
			$h=floor($h*$max_img_size/$w);
			$w=$max_img_size;
		};
		
		if ($h>$max_img_size) {
			$w=floor($w*$max_img_size/$h);
			$h=$max_img_size;
		};
		
	};
			
		
	$tag_img="<img src=\"foto_utenti/$cod_area/$nome_immagine\" ALT=\"$id_autore\" width=\"$w\" height=\"$h\">";
};


if (!$icona_post) {
	$icona_post = "messaggio";
};

if ($id_corso_s) {
	$query_m="select id_risorsa FROM lab_materiali WHERE titolo='$id_autore' and tipo=2 and id_corso='$id_corso_s' and id_edizione='$id_edizione_s'";
	$result_m=$mysqli->query($query_m);
	$riga_m=$result_m->fetch_array();
	$id_cartella=$riga_m[id_risorsa];
	$link_portfolio="";
	if ($id_cartella) {
		$link_portfolio="
		<a href=\"index.php?risorsa=lab_materiali_index&id_cartella=$id_cartella\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_pf_utente','','img/ico_portfolio_over.gif',1)\"><img border=\"0\" src=\"img/ico_portfolio.gif\" width=\"20\" height=\"20\" align=\"absmiddle\" hspace=\"5\" alt=\"$stringa[cartella_utente]\" name=\"img_pf_utente\"></a>
		";
	};
};

if ($id_autore=="fleo1") $id_autore="enza62";
if ($id_autore=="fleo2") $id_autore=="AntonioTul";
	
echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"10\" bgcolor=\"$colore_sfondo\">
<tr><td>";

//$tag_img="<img src=\"foto_utenti/$cod_area/fleo.jpg\" ALT=\"$id_autore\" width=\"120\" height=\"120\">";


	echo "<table border=0 cellspacing=5 cellpadding=0><tr><td valign=top>$tag_img</td><td valign=top align=left>";


echo "
<span class=testopiccolo><b>$stringa[autore]:</b>
<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_autore</a>&nbsp;$link_portfolio - $intervento[data_p]&nbsp;</span>";

printf("<p><span class=testopiccolo><b>%s:</b>&nbsp;<img src=img/forum/%s.gif alt=%s> %s </span></p>",$stringa[oggetto],$icona_post,$icona_post,$intervento["oggetto"]);

if ($wimba) {
if ($wimba_cookie=='on') {

	$query_audio="SELECT * FROM forum_audio WHERE id_post='$id_post'";
	$result_audio=$mysqli->query($query_audio);
	$riga_audio=$result_audio->fetch_array();
	$mid=$riga_audio["mid"];
	
	
	echo "
		<p><table border=0 cellspacing=0 cellpadding=0><tr><td valign=top><span class=testopiccolo><b>Messaggio audio:</b></span></td><td>
		<SCRIPT type=\"text/javascript\" SRC=\"http://cgi3.garamond.it:8080/wimba/ve/play.js\"></SCRIPT>
<SCRIPT type=\"text/javascript\">
  var w_p = new Object();
  
   w_p.mid=\"$mid\";
   w_p.rid=\"0-1074674761874\";
  
if (window.w_ve_play_tag) w_ve_play_tag(w_p);
  else document.write(\"Problemi con il server audio\");
</SCRIPT>
<span class=testo><a href=\"audio_switch.php?audio=off&".$_SERVER["QUERY_STRING"]."\" $target>[Audio Off]</a></span>&nbsp;
</td></tr></table></p>";

} else {
echo "
<table border=0  cellspacing=0 cellpadding=0>
<tr>
<td valign=top align=right>
<span class=testopiccolo><b>Messaggio audio:</b></span>
</td>
<td valign=top>&nbsp;<span class=testo>
<a href=\"audio_switch.php?audio=on&".$_SERVER["QUERY_STRING"]."\" $target>[Audio On]</a></span>&nbsp;
</td></tr>
</table>";
};
};

$testo = $intervento["testo"];
//$testo = parse_code($intervento["testo"]);
//if (!$win_ie) {$testo = ereg_replace("\n","<br>",$testo);};
//$testo = parse_link($testo);

$testo = parse_href($testo);
$testo = parse_quote($testo);


echo "</td></tr></table><table><tr><td valign=top>";

echo "
<table border=0 width=90% cellspacing=10 cellpadding=2>
<tr>
<td><span class=testo>$testo</span></td>
</tr></table>";

if ($intervento["nome_file"]) {
	printf("<p><span class=testopiccolo><b>%s:</b> <a href=forum_scarica.php?file=%s>%s</a> <i>(%s)</i></span></p>",$stringa[file_allegato],$intervento["nome_file"],$intervento["nome_file"],stringa_filesize($intervento["file_size"]));
};


echo "</td></tr></table>";


echo "
</td></tr></table>
</td></tr></table>";

if ($id_autore<>$kairos_cookie[0]) {
$query="SELECT * FROM forum_posts_attinenze WHERE id_post='$id_post' AND id_utente='$kairos_cookie[0]'";
$result=$mysqli->query($query);

if (!$result->num_rows) {
echo "
<br>

<span class=testopiccolo>Livello di attinenza: [<a href=forum_attinenza_post.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&id_post=$id_post&valore=1 title=\"Attribuisci a tuo giudizio il livello di attinenza di questo intervento al tema del forum o del thread in cui ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ stato scritto\">1</a>]&nbsp;[<a href=forum_attinenza_post.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&id_post=$id_post&valore=2 title=\"Attribuisci a tuo giudizio il livello di attinenza di questo intervento al tema del forum o del thread in cui ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ stato scritto\">2</a>]&nbsp;[<a href=forum_attinenza_post.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&id_post=$id_post&valore=3 title=\"Attribuisci a tuo giudizio il livello di attinenza di questo intervento al tema del forum o del thread in cui ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ stato scritto\">3</a>]&nbsp;[<a href=forum_attinenza_post.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&id_post=$id_post&valore=4 title=\"Attribuisci a tuo giudizio il livello di attinenza di questo intervento al tema del forum o del thread in cui ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ stato scritto\">4</a>]&nbsp;</span>
<br>
<br>";
};
};


echo "
<table border=0>";

echo "
<tr>";
echo "
<td valign=middle>";

if ($edit_forum) {
echo "
<a href=index.php?risorsa=forum_post&id_forum=$id_forum&op=replica&id_post_padre=$id_post&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_replica','','img/ico_forum_replica_over.gif',1)\"><img src=\"img/ico_forum_replica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[replica_intervento]\" border=\"0\" name=\"img_replica\"></a>";
};

echo "
</td>
<td valign=middle>";

if ($edit_forum) {
echo "
<span class=testopiccolo>
<a href=index.php?risorsa=forum_post&id_forum=$id_forum&op=replica&id_post_padre=$id_post&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_replica','','img/ico_forum_replica_over.gif',1)\">$stringa[replica_intervento]</a></span>";
};
echo "
</td>";

if ($id_utente == $id_autore or $ruolo=='admin' or $ruolo=='staff') {
	echo "<td width=15>&nbsp;</td>";
	echo "
	 <td valign=middle>
<a href=index.php?risorsa=forum_edit&id_forum=$id_forum&id_post=$id_post&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_modifica','','img/ico_forum_modifica_over.gif',1)\"><img src=\"img/ico_forum_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica_intervento]\" border=\"0\" name=\"img_modifica\"></a>
</td>
	 <td valign=middle><span class=testopiccolo><a href=index.php?risorsa=forum_edit&id_forum=$id_forum&id_post=$id_post&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_modifica','','img/ico_forum_modifica_over.gif',1)\">$stringa[modifica_intervento]</a></span></td>";
	
	//vedo se l'intervento e' cancellabile
	$query_t = "SELECT * FROM forum_posts WHERE id_post_padre='$id_post'";
	$result_t=$mysqli->query($query_t);
	$flag_t = $result_t->fetch_array();
	if (!$flag_t) {
		echo "<td width=15>&nbsp;</td>";
		
		echo "
		<td valign=middle>
<a href=forum_del_post.php?id_forum=$id_forum&id_post=$id_post&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_cancella','','img/ico_forum_cancella_over.gif',1)\"><img src=\"img/ico_forum_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella_intervento]\" border=\"0\" name=\"img_cancella\"></a>
</td>
	 	<td valign=middle><span class=testopiccolo><a href=forum_del_post.php?id_forum=$id_forum&id_post=$id_post&vista=$vista&modo=$modo&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_cancella','','img/ico_forum_cancella_over.gif',1)\">$stringa[cancella_intervento]</a></span></td>";
	};
};


if (!$riga_mark) {
	echo "<td width=15>&nbsp;</td>";
	echo "
	<td valign=middle>
<a href=forum_marca_post.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&id_post=$id_post&op=mark onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mark','','img/ico_forum_segnainteres_over.gif',1)\"><img src=\"img/ico_forum_segnainteres.gif\" width=\"20\" height=\"20\" alt=\"$stringa[interessante]\" border=\"0\" name=\"img_mark\"></a>
</td>
	<td valign=middle><span class=testopiccolo><a href=forum_marca_post.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&id_post=$id_post&op=mark onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mark','','img/ico_forum_segnainteres_over.gif',1)\">$stringa[interessante]</a></span></td>";
} else {
	echo "<td width=15>&nbsp;</td>";
	echo "
	<td valign=middle>
<a href=forum_marca_post.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&id_post=$id_post&op=unmark onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_unmark','','img/ico_forum_segnainteres_over.gif',1)\"><img src=\"img/ico_forum_segnainteres.gif\" width=\"20\" height=\"20\" alt=\"$stringa[non_interessante]\" border=\"0\" name=\"img_unmark\"></a>
</td>
	<td valign=middle><span class=testopiccolo><a href=forum_marca_post.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&id_post=$id_post&op=unmark onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_unmark','','img/ico_forum_segnainteres_over.gif',1)\">$stringa[non_interessante]</a></span></td>";
};

echo "</tr>";

echo "
<tr>
<td valign=middle>
<a class=miolink href=\"javascript:;\" onclick=\"javascript:apri_scheda('forum_storia_msg.php?id_post=$id_post',                   'myRemoteLetto',        'height=500,width=300,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLetto');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_chiletto','','img/ico_forum_chiletto_over.gif',1)\"><img src=\"img/ico_forum_chiletto.gif\" width=\"20\" height=\"20\" alt=\"$stringa[chi_letto]\" border=\"0\" name=\"img_chiletto\"></a>
</td>
<td valign=middle><span class=testopiccolo><a class=miolink href=\"javascript:;\" title=\"$stringa[chi_letto_alt]\" onclick=\"javascript:apri_scheda('forum_storia_msg.php?id_post=$id_post',                   'myRemoteLetto',        'height=500,width=300,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLetto');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_chiletto','','img/ico_forum_chiletto_over.gif',1)\">$stringa[chi_letto]</a></span></td>
";

echo "<td width=15>&nbsp;</td>";

echo "
<td valign=middle>
<a href=forum_post_nonletto.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&id_post=$id_post onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_daleggere','','img/ico_forum_daleggere_over.gif',1)\"><img src=\"img/ico_forum_daleggere.gif\" width=\"20\" height=\"20\" alt=\"$stringa[da_leggere]\" border=\"0\" name=\"img_daleggere\"></a>
</td>
<td valign=middle><span class=testopiccolo><a href=forum_post_nonletto.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&id_post=$id_post onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_daleggere','','img/ico_forum_daleggere_over.gif',1)\">$stringa[da_leggere]</a></span></td>";


if (($ruolo=='admin' or $ruolo=='staff') and $id_corso_s) {
	echo "<td width=15>&nbsp;</td>";
	
	echo "
	<td valign=middle>
<a href=index.php?risorsa=faq_new&id_forum=$id_forum&id_post=$id_post onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_ricopiafaq','','img/ico_forum_ricopiafaq_over.gif',1)\"><img src=\"img/ico_forum_ricopiafaq.gif\" width=\"20\" height=\"20\" alt=\"$stringa[ricopia_faq]\" border=\"0\" name=\"img_ricopiafaq\"></a>
</td>
	<td valign=middle><span class=testopiccolo><a href=index.php?risorsa=faq_new&id_forum=$id_forum&id_post=$id_post onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_ricopiafaq','','img/ico_forum_ricopiafaq_over.gif',1)\">$stringa[ricopia_faq]</a></span></td>";
};


echo "</tr></table>";

if (($ruolo=='admin' or $ruolo=='staff') and !$intervento["id_post_padre"]) {
	$lista = "";
	if ($id_corso_s) {
		$query_forum = "SELECT id_forum,descrizione FROM forum WHERE tipo=0 OR (id_corso='$id_corso_s' AND id_edizione='$id_edizione_s') ORDER BY tipo,ordine";
	} else {
		$query_forum = "SELECT id_forum,descrizione FROM forum WHERE tipo=0 ORDER BY ordine";
	};

	$result_forum=$mysqli->query($query_forum);
	while ($riga_forum = $result_forum->fetch_array()) {
		$id_f = $riga_forum["id_forum"];
		$descr_f = $riga_forum["descrizione"];
		if ($id_f != $id_forum) {
			$lista .= "<option value=\"$id_f\">$descr_f</option>";
		};
	};

	echo "<br><form action=forum_sposta_thread.php><input type=hidden name=id_post value=$id_post><input type=hidden name=id_forum value=$id_forum><span class=testo><b>$stringa[sposta_in]</b></span> <select class=\"testo\" name=nuovo_forum>$lista</select>&nbsp;<input type=submit class=\"testo\" value=$stringa[sposta]></form>";
};

echo "</td></tr></table>";

echo "</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=30%>";

$id_post_view=$intervento["id_post"];
$id_padre=thread_padre($id_post_view);

echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr> 
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\"> 
<span class=titolo><img src=\"img/ico_forum_utils.gif\" width=\"20\" height=\"20\" alt=\"\" border=\"0\" align=\"top\">&nbsp;<b>$stringa[struttura_intervento]</b></span>
</td>
</tr>

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">

<tr><td>";

/*
if ($ruolo=="staff" or $ruolo=="admin" or 1) 
echo "<div class=\"testopiccolo\" id=\"progress_msg\" style=\"height:40px;\"></div>";
*/

thread_view($id_padre);

echo "
</td></tr>
</table>

</td></tr>
</table>";

echo "
</td></tr>
</table>
";

echo "
</td></tr>
</table>
<br>";
?>

<table border=0 width=100% cellspacing=10 cellpadding=0>

<tr>
<td class=titolodot>
<?php echo(strtoupper($stringa[cerca_forum]));?>
</td>
</tr>

<?php
echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";
?>

<tr><td>


<?php
$stringa_cerca=$_REQUEST["stringa_cerca"];
$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];

if (!$stringa_cerca) {
	echo "<p><span class=testo>$stringa[inserisci_stringa]</span></p>";
	exit();
};

	
// seleziono gli interventi del forum e li visualizzo

/*
if ($ruolo<>'admin' and $ruolo<>'staff') {
	if ($id_corso_s) {
		$query = "SELECT forum_posts.id_forum,id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post FROM forum,forum_posts WHERE forum.id_forum=forum_posts.id_forum AND (oggetto like '%$stringa_cerca%' or testo like '%$stringa_cerca%' or id_autore='$stringa_cerca') and forum.tipo<>4 AND forum_posts.id_corso='$id_corso_s' AND forum_posts.id_edizione='$id_edizione_s' ORDER BY id_post DESC ";
	} else {
		$query = "SELECT forum_posts.id_forum,id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post FROM forum,forum_posts WHERE forum.id_forum=forum_posts.id_forum AND (oggetto like '%$stringa_cerca%' or testo like '%$stringa_cerca%' or id_autore='$stringa_cerca') and forum.tipo<>4 AND forum_posts.id_corso='' AND forum_posts.id_edizione='' ORDER BY id_post DESC ";
	};
} else {
	if ($id_corso_s) {
		$query = "SELECT id_forum,id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post FROM forum_posts WHERE (oggetto like '%$stringa_cerca%' or testo like '%$stringa_cerca%' or id_autore='$stringa_cerca') AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_post DESC ";
	} else {
		$query = "SELECT id_forum,id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post FROM forum_posts WHERE (oggetto like '%$stringa_cerca%' or testo like '%$stringa_cerca%' or id_autore='$stringa_cerca') AND id_corso='' AND id_edizione='' ORDER BY id_post DESC ";
	};

};
*/

$query = "SELECT id_forum,id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post FROM forum_posts WHERE (oggetto like '%$stringa_cerca%' or testo like '%$stringa_cerca%' or id_autore='$stringa_cerca') AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_post DESC ";

$result=$mysqli->query($query);

$tot_righe=$result->num_rows;

if (!$tot_righe) {
	echo "<p><span class=testo>$stringa[non_trovato]</span></p>";
	exit();
};

$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;

$righe=1;
$continua = true;
while ($intervento=$result->fetch_array()) {
	//vedo se l'utente ha letto l'intervento in questione
	$id_post = $intervento["id_post"];
	$id_forum = $intervento["id_forum"];
	$query1 = "SELECT * FROM forum_read WHERE id_post = '$id_post' AND id_utente='$id_utente'";
	$result1=$mysqli->query($query1);
	$letto = mysql_numrows($result1);
	
	$query_forum = "SELECT * FROM forum WHERE id_forum='$id_forum'";
	$result_forum=$mysqli->query($query_forum);
	$riga_forum = $result_forum->fetch_array();	
	$titolo_forum=$riga_forum["descrizione"];
	
	if ($letto) {
		$flag = "";
	} else {
		$flag = " <i><b>$sringa[nuovo]</b></i>";
	};
	
	$id_autore=$intervento["id_autore"];
	$icona_post = $intervento["icona_post"];

	if (!$icona_post) {
		$icona_post = "messaggio";
	};


	$query_mark = "SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post'";
	$result_mark=$mysqli->query($query_mark);
	$riga_mark = $result_mark->fetch_array();	
	if ($riga_mark) {
		echo "<img src=img/forum/spunta.gif border=0>";
	};
	
	if ($intervento["nome_file"]) {
		echo "<img src=img/forum/allegato.gif width=16 height=16 border=0>";
	};
		
	printf("<img src=img/forum/%s.gif alt=%s> <span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post&id_forum=%s&id_post=%s&vista=data&modo=esteso&pagina=%s>%s</a> (%s - </span>",$icona_post,$icona_post,$id_forum,$intervento["id_post"],$pagina,$intervento["oggetto"],$titolo_forum);

	echo "<span class=testopiccolo> <i><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_autore</a></i>
</span>";

		
	printf("<span class=testopiccolo><i> - %s)</i></span>\n",$intervento["data_p"]);

	echo "<span class=testopiccolo>$flag</span><br>";
	
	$righe++;
	$progr++;
};

echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?risorsa=cerca_forum&pagina=$i&pag_size=$pag_size&stringa_cerca=$stringa_cerca>$i</a>]
		";
	};
	$i++;
};
echo "</span>";	
?>

</td></tr>
</table>
<br>

<?php

$query2 = "SELECT * FROM forum WHERE tipo=3 ORDER BY ordine";
$result2=$mysqli->query($query2);
echo "
<table border=0 width=100% cellpadding=5>
<tr>
<td valign=top>";
echo "<p><span class=titolopagina>$stringa[laboratori]</span></p>
<p>
<span class=testo>
[<a href=\"ftp/\" target=\"_blank\">$stringa[spazio_web_pers]</a>]
</span>
</p>
<p>
<span class=testo>
[<a href=\"ftp_comune/\" target=\"_blank\">$stringa[cartelle_condivise]</a>]
</span>
</p>";

echo "
<p>
<span class=testo>
[<a href=\"chat_entra.php?stanza=laboratorio\">$stringa[chat_collaborativo]</a>]
</span>
</p>
";

if ($id_corso_s) {
$query2 = "SELECT * FROM forum WHERE tipo=3 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY ordine";
$result2=$mysqli->query($query2);
echo "
<table border=1 cellpadding=0 cellspacing=0 width=700 bgcolor=\"$colore_sfondo\" bordercolor=\"$colore_bordo\">

<tr><td>

<table border=0 cellpadding=5>
\n";

while ($forum=$result2->fetch_array()) {
	$id_forum = $forum["id_forum"];
	$descrizione = $forum["descrizione"];

	$query_post = "SELECT * FROM forum_posts WHERE id_forum='$id_forum'";
	$result_post=$mysqli->query($query_post);
	$n_posts = mysql_numrows($result_post);

	//vediamo se ci sono interventi nuovi per l'utente


	$da_leggere=false;
	while ($intervento = $result_post->fetch_array() and !$da_leggere) {
		$id_post = $intervento["id_post"];
		$query1 = "SELECT id_post FROM forum_read WHERE id_post='$id_post' AND id_utente='$id_utente'";

		$result1=$mysqli->query($query1);
		$num_read = mysql_numrows($result1);		
		

		if (!$num_read) {
			$da_leggere=true;
		};

	};

	if ($da_leggere) {
		$flag = "<i><b>$stringa[nuovo]</b></i>";
	} else {
		$flag = "";
	};	

	echo "
	<tr>
	<td valign=top><span class=testo><a href=index.php?risorsa=forum_indice&id_forum=$id_forum>$descrizione</a> ($n_posts) $flag</span></td></tr>";	

};

echo "
</table>
</td></tr>
</table>



<table border=0>
<tr>
<td>
<span class=testopiccolo>
<b>$stringa[corsista]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[sito]</b>
</span>
</td>
</tr>";
	
$query="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_utente";
$result=$mysqli->query($query);

$i=1;
while ($riga=$result->fetch_array()) {
	$id_utente1 = $riga["id_utente"];
		

	
	echo "
		<tr>
		<td>
		<span class=testopiccolo>
		<b>$i</b> - 
		<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a></span>
		</td>";

		$url_utente=$PATH_ROOT."utenti/$cod_area/$id_utente1";
			
	echo "
		<td>
		<span class=testopiccolo>
		<a href=\"$url_utente\" target=_blank>$url_utente</a>
		</span>
		</td>
		</tr>
		";
	$i++;

};
echo "
</table>
<br>";
};

?>


</td></tr>
</table>
<br>










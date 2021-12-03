<?php
echo "
<table border=0 width=100% cellpadding=5>
<tr>
<td valign=top>";
echo "<p><span class=titolopagina>$stringa[laboratori]</span></p>
<p>
<span class=testo>
[<a href=\"ftp/index.php?altro_utente=$id_utente\" target=\"_blank\">$stringa[spazio_web_pers]</a>]
</span>
</p>";

if ($id_corso_s) {

echo "
<p>
<span class=testo>
[<a href=\"ftp_comune/\" target=\"_blank\">$stringa[cartelle_condivise]</a>]
</span>
</p>";


$id_tmpRoom="lab_".$id_corso_s;
	
echo "
<p>
<span class=testo>
[<a href=\"chat_entra.php?stanza=$id_tmpRoom\">$stringa[chat_collaborativo]</a>]
</span>
</p>
";


echo "
<p>
<span class=testo>
[<a href=\"index.php?risorsa=lab_materiali_index&id_cartella=0\">$stringa[database_lavori]</a>]
</span>
</p>
";
};

if ($id_corso_s) {
	$query2 = "SELECT * FROM forum WHERE tipo=3 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='' OR id_gruppo=null) ORDER BY ordine";
	$result2=$mysqli->query($query2);

	if ($result2->num_rows) {

	echo "
<p><span class=testo><b>$stringa[forum_corso]</b></span></p>
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
</td></tr></table><br>";
	};
};


if ($ruolo<>'staff' and $ruolo<>'admin' and $id_gruppo_s and $id_corso_s) {
	$query2 = "SELECT * FROM forum WHERE tipo=3 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_s' ORDER BY ordine";
	$result2=$mysqli->query($query2);

	if ($result2->num_rows) {

	echo "
<p><span class=testo><b>$stringa[forum_gruppo]</b></span></p>
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
</td></tr></table><br>";
	};
};


if (($ruolo=='staff' or $ruolo=='admin') and $id_corso_s) {

$query_gruppo="SELECT id_gruppo,descrizione FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_gruppo";
$result_gruppo=$mysqli->query($query_gruppo);

while ($riga_gruppo=$result_gruppo->fetch_array()) {
	$id_gruppo_s=$riga_gruppo["id_gruppo"];
	$descr_gruppo_s=$riga_gruppo["descrizione"];


	$query2 = "SELECT * FROM forum WHERE tipo=3 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_s' ORDER BY ordine";
	$result2=$mysqli->query($query2);

	if ($result2->num_rows) {
	echo "
<p><span class=testo><b>$stringa[forum_del_gruppo]: $descr_gruppo_s</b></span></p>
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
</td></tr></table><br>";
	};
	
};
};

?>


</td></tr>
</table>
<br>










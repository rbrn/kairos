<?php

$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	



$query2 = "SELECT * FROM forum WHERE tipo=3 ORDER BY ordine";

$result2=$mysqli->query($query2);

echo "

<table border=0 width=100% cellpadding=5>

<tr>

<td valign=top>";

echo "<p><span class=titolopagina>Laboratori</span></p>

<p>

<span class=testo>

[<a href=\"ftp/\" target=\"_blank\">Spazio Web personale</a>]

</span>

</p>

<p>

<span class=testo>

[<a href=\"ftp_comune/\" target=\"_blank\">Cartelle Web Condivise</a>]

</span>

</p>



";



echo "

<table border=1 cellpadding=0 cellspacing=0 width=700 bgcolor=\"$colore_sfondo\" bordercolor=\"#706EA0\">



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

		$flag = "<i><b>NovitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½!</b></i>";

	} else {

		$flag = "";

	};	



	echo "

	<tr>

	<td valign=top><span class=testo><a href=index.php?risorsa=forum_indice&id_forum=$id_forum>$descrizione</a> ($n_posts) $flag</span></td></tr>";	



};



echo "

</table>



";





echo "</td></tr></table></td></tr></table><br>";

?>







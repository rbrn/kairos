<?php

if ($db_edizione=='dbatlante' or $db_edizione=='dbcorso' or $db_edizione=='dbcorso3') {

	$db = mysql_connect("cgi.garamond.it","root","garamond");

	mysql_select_db($db_edizione,$db);	

} else {

	$db = mysql_connect("localhost",$DBUSER,$DBPWD);

	mysql_select_db($db_edizione,$db);	

};



if ($db_edizione=='espertoweb_corsi') {

	switch ($cod_area) {

		case "corso_dhtml": 

			$classe="DHTML";

			break;

			

		case "corso_flash":

			$classe="Flash";

			break;

			

		case "corso_dw":

			$classe="WebDesign-DreamWeaver";

			break;

	};

};





if ($db_edizione=='dbatlante' or $db_edizione=='dbcorso' or $db_edizione=='dbcorso3') {

	 	$query2 = "SELECT * FROM forum_corso WHERE classe='generale' ORDER BY ordine";

} else {

		$query2 = "SELECT * FROM forum WHERE tipo=0 ORDER BY ordine";

};



if ($db_edizione=='espertoweb_corsi') {

	$query2 = "SELECT * FROM forum WHERE tipo=1 AND classe='$classe' ORDER BY ordine";

};

$result2=$mysqli->query($query2);

echo "

<table border=0 width=100% cellpadding=5>

<tr>

<td valign=top>";

echo "<p><span class=titolopagina>Archivio Web Forum di Corso</span></p>

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



		

	$flag = "";

		



	echo "

	<tr>

	<td valign=top><span class=testo><a href=index.php?risorsa=forum_indice_archivio&id_forum=$id_forum&db_edizione=$db_edizione>$descrizione</a> ($n_posts) $flag</span></td></tr>";	



};



echo "

</table>



";





echo "</td></tr></table></td></tr></table><br>";

?>







<?php

require "./include/funzioni_archivio.inc";

if ($db_edizione=='dbatlante' or $db_edizione=='dbcorso' or $db_edizione=='dbcorso3') {

	$db = mysql_connect("cgi.garamond.it","root","garamond");

	mysql_select_db($db_edizione,$db);	

} else {

	$db = mysql_connect("localhost",$DBUSER,$DBPWD);

	mysql_select_db($db_edizione,$db);	

};



if ($db_edizione=='dbatlante' or $db_edizione=='dbcorso' or $db_edizione=='dbcorso3') {

 	$query2 = "SELECT * FROM forum_corso WHERE id_forum='$id_forum'";

} else {

	$query2 = "SELECT * FROM forum WHERE id_forum='$id_forum'";

};



$result2=$mysqli->query($query2);

$dati_forum=$result2->fetch_array();

?>



<br><br>

<table border=0 width=80%>

<tr><td>

<?php

$descr_forum = $dati_forum["descrizione"];

echo "

<span class=sottotitolopagina>Archivio Web Forum</span>

<hr size=1>

<span class=testo>

<b>$descr_forum</b>

</span>

<hr size=1>

";

	

echo "

<span class=testo>

[<a href=index.php?risorsa=forum_elenco_archivio&db_edizione=$db_edizione>Indice</a>]

</span> ";

echo "<hr size=1>";



thread_archivio('0');		



echo "<hr size=1>";	

echo "

<span class=testo>

[<a href=index.php?risorsa=forum_elenco_archivio&db_edizione=$db_edizione>Indice</a>]

</span> ";





	

?>

</td></tr>

</table>







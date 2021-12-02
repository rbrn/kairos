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

//marco l'intervento come letto dall'utente



// prelevo i dati dell'intervento

$query = "SELECT id_post,oggetto,id_autore,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,testo,nome_file,file_size,id_post_padre,icona_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post='$id_post'";

$result=$mysqli->query($query);

$intervento = $result->fetch_array();







echo "

<p>

<span class=testo><b>$descr_forum</b></span>

</p>

<hr size=1>

";

echo "<span class=testopiccolo>";



if ($intervento["id_post_padre"]) {

	printf(" | [<a href=index.php?risorsa=forum_mostra_post_archivio&id_forum=%s&id_post=%s&db_edizione%s>Intervento Sup.</a>]",$id_forum,$intervento["id_post_padre"],$db_edizione);

} else {

	echo " | [Intervento Sup.]";

};







printf(" | [<a href=index.php?risorsa=forum_indice_archivio&id_forum=%s&db_edizione=%s>Indice</a>]",$id_forum,$db_edizione);



echo 

"</span><br>

<hr size=1>

<br>\n";





$id_autore=$intervento["id_autore"];

$icona_post = $intervento["icona_post"];



if (!$icona_post) {

	$icona_post = "messaggio";

};





echo "

<p>

<span class=testopiccolo><b>Autore:</b>

$id_autore

</span>

";



printf("<span class=testopiccolo> - %s</span></p>",$intervento["data_p"]);

printf("<p><span class=testopiccolo><b>Oggetto:</b><img src=img/forum/%s.gif alt=%s> %s </span></p>",$icona_post,$icona_post,$intervento["oggetto"]);

$testo = parse_code($intervento["testo"]);

$testo = ereg_replace("\n","<br>",$testo);

$testo = parse_link($testo);

printf("<p><span class=testopiccolo><b>Intervento:</b></span></p><table border=0 width=90%% cellspacing=2 cellpadding=2 bgcolor=%s><tr><td><span class=testo>%s</span></td></tr></table>",$colore_sfondo,$testo);



if ($intervento["nome_file"]) {

	printf("<p><span class=testopiccolo><b>File allegato:</b> <a href=forum_scarica.php?file=%s>%s</a> <i>(%s Byte)</i></span></p>",$intervento["nome_file"],$intervento["nome_file"],$intervento["file_size"]);

};



echo "

<br>

<hr size=1>";



echo "<span class=testopiccolo>";





if ($intervento["id_post_padre"]) {

	printf(" | [<a href=index.php?risorsa=forum_mostra_post_archivio&id_forum=%s&id_post=%s&db_edizione%s>Intervento Sup.</a>]",$id_forum,$intervento["id_post_padre"],$db_edizione);

} else {

	echo " | [Intervento Sup.]";

};







printf(" | [<a href=index.php?risorsa=forum_indice_archivio&id_forum=%s&db_edizione=%s>Indice</a>]",$id_forum,$db_edizione);



echo 

"</span><br>

<hr size=1>

<br>\n";



thread_archivio($intervento["id_post"]);

?>

</td></tr>

</table>

<br>






<?php



function thread_archivio($id_padre) {

	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT,$db_edizione,

			$id_forum,$id_utente;

	

	if ($db_edizione=='dbatlante' or $db_edizione=='dbcorso' or $db_edizione=='dbcorso3') {

		$db = mysql_connect("cgi.garamond.it","root","garamond");

		mysql_select_db($db_edizione,$db);	

	} else {

		$db = mysql_connect("localhost",$DBUSER,$DBPWD);

		mysql_select_db($db_edizione,$db);	

	};	



// seleziono gli interventi del forum e li visualizzo



$query = "SELECT id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre='$id_padre' ORDER BY data_last_mod DESC";



$result=$mysqli->query($query);



echo "<ul>\n";



while ($intervento = $result->fetch_array()) {



	$id_post = $intervento["id_post"];

	$id_autore=$intervento["id_autore"];

	$icona_post = $intervento["icona_post"];



	if (!$icona_post) {

		$icona_post = "messaggio";

	};	

	

		

	echo "<li>\n";

	

		

	if ($intervento["nome_file"]) {

		echo "<img src=img/forum/allegato.gif width=16 height=16 border=0>";

	};

		

	printf("<img src=img/forum/%s.gif alt=%s> <span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post_archivio&id_forum=%s&id_post=%s&db_edizione=%s>%s</a></span>",$icona_post,$icona_post,$id_forum,$intervento["id_post"],$db_edizione,$intervento["oggetto"]);

	

	echo "<span class=testopiccolo> (<i>$id_autore</i>

</span>";

		

	printf("<span class=testopiccolo><i> - %s)</i></span>\n",$intervento["data_p"]);





	$id_post = $intervento["id_post"];

	$query = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre='$id_post'";

	$result0=$mysqli->query($query);

	$nrep = $result0->num_rows;



	



	if ($nrep) { thread_archivio($id_post); };

	

	echo "</li>\n";

	

};

	

	

echo "</ul>";



};





	

?>

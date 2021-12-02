<?php



$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	



$query2 = "SELECT * FROM forum WHERE id_forum='$id_forum'";

$result2=$mysqli->query($query2);

$dati_forum=$result2->fetch_array();

?>



<br><br>

<table border=0 width=80%>

<tr><td>

<?php

$descr_forum = $dati_forum["descrizione"];



if (!$vista) {

	$vista = 'thread';

	$modo = 'esteso';

};

	



echo "

<span class=sottotitolopagina>Web Forum</span>

<hr size=1>

<span class=testo>

<b>$descr_forum</b>

</span>

<hr size=1>

<span class=testopiccolo>

[<a href=index.php?risorsa=forum_post&id_forum=".$id_forum."&op=nuovo&vista=".$vista."&modo=".$modo.">Nuovo Intervento</a>] |";



if ($vista == 'thread') {

	if ($modo == 'esteso') {

 	echo " [<a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=thread&modo=sintetico&id_start=$id_start>Comprimi struttura</a>]";

	} else {

		echo " [<a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=thread&modo=esteso&id_start=$id_start>Espandi struttura</a>]";

	};



	echo " | [<a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=data&modo=esteso&id_start=$id_start>Vista cronologica</a>]";



} else	{

	echo " [<a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=thread&modo=esteso&id_start=$id_start>Vista per struttura</a>]";	


};






};


if ($vista <> "mark") {

	echo " | [<a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=mark&modo=esteso&id_start=0>Interessanti</a>]";		

};





if ($vista == "mark") {

	echo " | [<a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=data&modo=esteso&id_start=$id_start>Vista cronologica</a>]";

}; 





echo "

</span>

<br>

<hr>";



if ($vista=='data') {

	$pag_size=100;

} else {

	$pag_size=50;

};





switch($vista) {

	case "data":

		$query = "SELECT max(id_post) as max_id_post FROM forum_posts WHERE id_forum='$id_forum'";

		break;



	case "thread":

		$query = "SELECT max(id_post) as max_id_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre='0'";

		break;



	case "mark":

		$query = "SELECT max(id_post) as max_id_post FROM forum_mark WHERE id_forum='$id_forum' AND id_utente='$id_utente'";	

		break;

};







$result=$mysqli->query($query);

$tot_r = $result->fetch_array();

$tot_righe=$tot_r["max_id_post"];;



	



if (!$id_start or $id_start >= $tot_righe) {

	$id_start = $tot_righe;

	$id_prec=0;

};





if ($id_start != $tot_righe) {

	//re-imposto id_start in un suo intorno

	switch($vista) { 

		case "data":

			$query = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post > '$id_start' ORDER BY id_post";

		break;



		case "thread":

			$query = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post > '$id_start' and id_post_padre='0' ORDER BY id_post";	

			break;



		case "mark":

			$query = "SELECT id_post FROM forum_mark WHERE id_forum='$id_forum' AND id_utente='$id_utente' AND id_post > '$id_start' ORDER BY id_post";

			break;		

	};



	$result=$mysqli->query($query);	

	$i = $pag_size/2;

	while ($id_start_r = $result->fetch_array() and $i<$pag_size-1) {

		$id_start=$id_start_r["id_post"];

		$i++;

	};	





	if ($id_start >= $tot_righe) {

		$id_start = $tot_righe;

		$id_prec=0;

	} else {

		switch($vista) {

			case "data":

				$query = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post > '$id_start' ORDER BY id_post";

				break;



			case "thread":

				$query = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post > '$id_start' and id_post_padre='0' ORDER BY id_post";	

				break;



			case "mark":

				$query = "SELECT id_post FROM forum_mark WHERE id_forum='$id_forum' AND id_post > '$id_start' AND id_utente='$id_utente' ORDER BY id_post";

				break;			

		};



		$result=$mysqli->query($query);

		$i = 0;

		while ($id_prec_r = $result->fetch_array() and $i<$pag_size-1) {

			$i++;

		};





		if ($id_prec_r) {

			$id_prec = $id_prec_r["id_post"];

		} else {

			$id_prec = $tot_righe;

		};

	};



};



	

switch($vista) {

	case "data":

		bydate();	

		break;



	case "thread":

		thread('0',$modo);		

		break;



	case "mark":

		bymark();	

		break;	

};







echo "<hr>";	

if ($id_prec) {

	echo "

	<span class=piccolo>

	[<a href=index.php?risorsa=forum_indice&id_forum=$id_forum&id_start=$id_prec&modo=$modo&vista=$vista><<</a>]

	</span> ";

};



if ($id_succ) {

	echo " 

	<span class=piccolo>

	[<a href=index.php?risorsa=forum_indice&id_forum=$id_forum&id_start=$id_succ&modo=$modo&vista=$vista>>></a>]

	</span> ";

};	

?>

</td></tr>

</table>







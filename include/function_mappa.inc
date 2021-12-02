<?php



function thread($id_padre,$sonoqui,$espanso) {

	global 	$DBHOST, $DBASE,$DBUSER,$DBPWD;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);



$query = "SELECT id_risorsa,id_autore,titolo,tipo,sottotipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM risorse WHERE risorsa_padre='$id_padre' ORDER BY tipo DESC,id_risorsa";

$result=$mysqli->query($query);



echo "<ul>\n";

while ($risorsa = $result->fetch_array() ) {



	$id_risorsa = $risorsa["id_risorsa"];

	$id_autore=$risorsa["id_autore"];

	$titolo=$risorsa["titolo"];

	$file_size=$risorsa["file_size"];

	$tipo = $risorsa["tipo"];

	$sottotipo = $risorsa["sottotipo"];

	$data_m = $risorsa["data_m"];

	if ($id_risorsa<>'admin' and $id_risorsa<>'sezioni_home_page' and $id_risorsa<>'area_forum') {

	echo "<li>\n";



	switch ($tipo) {

		case 0:

			echo "

			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"pagina web\"> <a href=index.php?risorsa=$id_risorsa title=\"$titolo\"><span class=testo>$titolo</span></a>\n";	

			if ($id_risorsa==$sonoqui) {

				echo "<span class=testo> <img src=img/sonoqui.gif width=17 height=17 border=0> <b>Tu eri qui!</b></span>";

			};

				

			break;

		

		case 1:

			$icona="file.gif";			

			$est = substr($titolo,-3);

			

			$tipi_file = array ("zip","exe","xls","doc","pdf","rtf","jpg","gif","mid","mp3",

							"wav","avi","htm","txt","mpg","bmp","ppt");

			

			if (in_array($est,$tipi_file)) {

				$icona=$est.".gif";

			}; 

			

			echo "

			<img src=img/".$icona." width=16 height=16 border=0 alt=\"file da scaricare\"> <a href=../index.php?risorsa=$id_risorsa title=\"$titolo\"><span class=testo>$titolo - $file_size Byte</span></a>  \n";	

			break;



		case 2:

			if ($id_padre=='root') {

				if ($espanso<>$id_risorsa) {

					echo "

					<span id=menu1 onClick=\"toggleMenu(this)\">\n

					<img src=img/folder_apri.gif width=16 height=15 alt=\"\" border=0>&nbsp;<span class=testo>$titolo</span><br>\n

					<span id=menu2 style=\"display:None\" onClick=\"window.event.cancelBubble=true\">\n";

					thread($id_risorsa,$sonoqui,$toggle);

					echo "</span></span>\n";

				} else {

					echo "

					<span id=menu1 onClick=\"toggleMenu(this)\">\n

					<img src=img/folder_chiudi.gif width=16 height=15 alt=\"\" border=0>&nbsp;<span class=testo>$titolo</span><br>\n

					<span id=menu2 style=\"display:Yes\" onClick=\"window.event.cancelBubble=true\">\n";

					thread($id_risorsa,$sonoqui,$toggle);

					echo "</span></span>\n";						

				};	

			} else {

				echo "

				<img src=img/folder.gif width=16 height=15 alt=\"\" border=0>&nbsp;<span class=testo>$titolo</span>\n";

				thread($id_risorsa,$sonoqui,$toggle);			

			};

			break;



	};

	echo "</li>\n";

	};

	};

echo "</ul>\n";

};



function get_padre($id_risorsa) {
	global 	$DBHOST, $DBASE,$DBUSER,$DBPWD;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$query = "SELECT risorsa_padre FROM risorse WHERE id_risorsa='$id_risorsa'";

	$result=$mysqli->query($query);



	$riga=$result->fetch_array();

	$padre = $riga["risorsa_padre"];

	if ($padre=='root') {

		return $id_risorsa;

	} else {

		return get_padre($padre);

	};	



};

	

?>

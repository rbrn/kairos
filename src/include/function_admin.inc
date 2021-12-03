<?php
function thread_risorse($id_padre) {
	global $DBHOST,$DBASE,$DBUSER,$DBPWD,$kairos_cookie,$stringa;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$id_utente=$kairos_cookie["0"];



$query = "SELECT id_risorsa,id_autore,titolo,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM risorse WHERE risorsa_padre='$id_padre' ORDER BY tipo DESC,id_risorsa";

$result=$mysqli->query($query);



echo "<ul>\n";

while ($risorsa = $result->fetch_array() ) {



	$id_risorsa = $risorsa["id_risorsa"];

	$id_autore=$risorsa["id_autore"];

	$titolo=$risorsa["titolo"];

	$file_size=$risorsa["file_size"];

	$tipo = $risorsa["tipo"];

	$data_m = $risorsa["data_m"];

	

	$ruolo=ruolo_utente($id_utente);

	if (($id_risorsa<>'admin') or ($id_risorsa=='admin' and $ruolo=='admin')) { 

	

		echo "<li>\n";



		switch ($tipo) {

			case 0:

				echo "

			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"$stringa[pagina_web]\"> <a href=risorsa_browse.php?id_risorsa=$id_risorsa&id_cartella=$id_padre title=\"$titolo\">$id_risorsa</a> ($id_autore - $data_m)  <a href=risorsa_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo><img src=img/modify.gif width=25 height=24 alt=\"$stringa[modifica]\" border=0></a><a href=index.php?risorsa=risorsa_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre><img src=img/delete.gif width=25 height=24 alt=\"$stringa[cancella]\" border=0></a>\n";	

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

			<img src=img/".$icona." width=16 height=16 border=0 alt=\"$stringa[file]\"> <a href=index.php?risorsa=$id_risorsa title=\"$titolo\">$id_risorsa - ".stringa_filesize($file_size)."</a> ($id_autore - $data_m)  <a href=risorsa_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo><img src=img/modify.gif width=25 height=24 alt=\"$stringa[modifica]\" border=0></a><a href=index.php?risorsa=risorsa_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre><img src=img/delete.gif width=25 height=24 alt=\"$stringa[cancella]\" border=0></a>\n";	

				break;



			case 2:

				echo "

			<a href=index.php?risorsa=admin_index&id_cartella=$id_risorsa><img src=img/folder.gif width=18 height=16 alt=\"$stringa[apri_cartella]\" border=0> $id_risorsa</a> ($id_autore - $data_m) <a href=risorsa_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo><img src=img/modify.gif width=25 height=24 alt=\"$stringa[modifica]\" border=0></a><a href=index.php?risorsa=risorsa_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre><img src=img/delete.gif width=25 height=24 alt=\"$stringa[cancella]\" border=0></a><br>\n";

				break;



		};

		echo "</li>\n";

	};

};

echo "</ul>\n";

};



function cancella_contenuto($id_padre) {

	global 	$DBHOST, $DBASE,$DBUSER,$DBPWD,$PATH_ARCHIVI,$PATH_ROOT_FILE,$PATH_ARCHIVI_ADMIN,$stringa,$cod_area;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$query="SELECT * FROM risorse WHERE risorsa_padre='$id_padre'";

	$result=$mysqli->query($query);

	while ($riga=$result->fetch_array()) {

		$id_figlio = $riga["id_risorsa"];

		$tipo_figlio = $riga["tipo"];



		if ($tipo_figlio==0) {

			

			if (risorsa_admin($id_figlio)) {

				$file_codice=$PATH_ROOT_FILE."pagine/$id_figlio.inc";

			} else {

				$file_codice=$PATH_ROOT_FILE."pagine/$cod_area/$id_figlio.inc";

			};

			

			if (file_exists($file_codice)) {

				unlink($file_codice);	

			};

		};

		

		if ($tipo_figlio==1) {

			$query1 = "SELECT titolo FROM risorse WHERE id_risorsa='$id_figlio'";

			$result1=$mysqli->query($query1);

			$riga1=$result1->fetch_array();

			$titolo=$riga1["titolo"];

			if (risorsa_admin($id_figlio)) {

				$fullpath=$PATH_ARCHIVI_ADMIN.$titolo;

			} else {

				$fullpath=$PATH_ARCHIVI.$titolo;

			};

			if (file_exists($fullpath)) {

				unlink($fullpath);	

			};

		};



		if ($tipo_figlio==2) {

			cancella_contenuto($id_figlio);

		};

			

		$query2 = "DELETE FROM risorse WHERE id_risorsa='$id_figlio'";

		$result2=$mysqli->query($query2);		

	};



};



function browse_folder($cartella) {

	global $PATH_ROOT,$PATH_ROOT_FILE;

	

	if (!$cartella or $cartella=="/" or trim($cartella)=="" or ereg("^\\.(.+)$",$cartella)) {

		$cartella="";

	};



	

	$dir_path=$PATH_ROOT_FILE."img/".$cartella;

	

	if (!is_dir($dir_path)) {

		$cartella="";

		$dir_path=$PATH_ROOT_FILE."img/".$cartella;

	};

	

	

	

	if ($cartella<>"") {

		$padre=dirname($cartella);

		echo "

		[<a href=index.php?risorsa=cartella&cartella=$padre>$stringa[dir_superiore]</a>]<br><hr>";

	};



	echo "<h1>".$cartella."</h1>";

	$i=0;

	$d = dir($dir_path);

	while ($filename=$d->read()) {

		if (($filename != '.') && ($filename != '..')) { 

			$entry[$i]=$filename;

			$i++;

		};



	};

	$d->close();

	if ($i) {

		sort($entry);

	};

	for ($j=0;$j<$i;$j++){ 

		$filename=$entry[$j];

		$path_file=$PATH_ROOT_FILE."img/".$cartella."/".$filename;

		echo "

		<input type=checkbox name=$filename> ";

		if (is_dir($path_file)) {

			echo "

				<img src=img/folder.gif width=18 height=16 border=0> <a href=index.php?risorsa=cartella&cartella=$cartella"."/".$filename.">$filename</a><br>";

		} else {

				echo "<a href=".$PATH_ROOT."img/".$cartella."/"."$filename>$filename</a><br>\n";

		};

	

	};

}





?>

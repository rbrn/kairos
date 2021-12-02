<HTML>

<HEAD>

	<TITLE>Atlante Corsi: RIFERIMENTI A RISORSA ATLANTE</TITLE>

	

</HEAD>



<BODY bgcolor="white">



<b>RIFERIMENTI RISORSA Atlante Corsi</b>

<p>

[<a href=cerca_riferimenti.htm>Nuova Ricerca</a>]

</p>

<?php

require "../include/init_sito.inc";



echo "<p>Elenco Pagine che linkano la risorsa: <b>$id_risorsa</b></p>";





function elenco_file($dir_path, $filetype) {

	$i=0;

	$d = dir($dir_path);

	while ($filename=$d->read()) {

		if (($filename != '.') && ($filename != '..')) { 

			$est = substr($filename,-3);

			if ($est==$filetype) {

				$entry[$i]=$filename;

				$i++;

			};

		};



	};

	$d->close();

	if ($i) {

		sort($entry);

	};

	

	return $entry;

};







$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	

	

$dir_path=$PATH_ROOT_FILE."pagine";

$files = elenco_file($dir_path,"inc");

reset($files);



echo "<ul>\n";

$q="risorsa=$id_risorsa";

while(list(, $file) = each($files)) {

	$content = @file($dir_path."/".$file);

	$content = implode(" ",$content);

	

	if (stristr($content, $q) == false)

		continue;

	

	$riferimento = substr($file,0,strlen($file)-4);



	$query = "SELECT * FROM risorse WHERE id_risorsa='$riferimento'";

	$result=$mysqli->query($query);

	$risorsa = $result->fetch_array();

	

	$id_r = $riferimento;

	$id_autore=$risorsa["id_autore"];

	$titolo=$risorsa["titolo"];

	$tipo = $risorsa["tipo"];

	$sottotipo = $risorsa["sottotipo"];

	$id_padre= $risorsa["risorsa_padre"];

	

	echo "<li>\n";



	echo "

			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"pagina web\"> <a href=risorsa_browse.php?id_risorsa=$id_r title=\"$titolo\">$id_r</a> ($id_autore)  <a href=risorsa_form_mod.php?id_risorsa=$id_r&tipo=$tipo&sottotipo=$sottotipo><img src=img/modify.gif width=25 height=24 alt=\"Modifica\" border=0></a>\n";	

		

		

	echo "</li>\n";	

};

echo "</ul>";

		



?>

		

</table>		



</BODY>

</HTML>

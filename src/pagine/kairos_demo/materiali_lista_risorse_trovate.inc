<b>RISORSA Atlante Corsi</b>
<p>
[<a href=index.php?risorsa=materiali_cerca_risorsa>Nuova Ricerca</a>]
</p>

<?php
$id_risorsa_cerca=$_REQUEST["id_risorsa_cerca"];

mysql_select_db($DBASE,$db);	
echo "<p>Risorsa con identificativo: <b>$id_risorsa_cerca</b></p>";
	
$query = "SELECT id_autore,titolo,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM risorse_materiali WHERE id_risorsa='$id_risorsa_cerca'";
$result=$mysqli->query($query);
$risorsa = $result->fetch_array();

if (!$risorsa) {
	echo "Nessuna risorsa trovata.";
} else {
	$id_risorsa=$id_risorsa_cerca;
	$id_autore=$risorsa["id_autore"];
	$titolo=$risorsa["titolo"];
	$file_size=$risorsa["file_size"];
	$tipo = $risorsa["tipo"];
	$data_m = $risorsa["data_m"];
	
	echo "<li>\n";

	switch ($tipo) {
			case 0:
				echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"pagina web\"> <a href=materiali_browse.php?risorsa=$id_risorsa target=_blank title=\"$titolo\">$id_risorsa - $titolo</a> ($id_autore - $data_m)  <a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo><img src=img/modify.gif width=25 height=24 alt=\"Modifica\" border=0></a><a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre><img src=img/delete.gif width=25 height=24 alt=\"Cancella\" border=0></a>\n";	
				break;
				
			case 3:
				echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"pagina web\">(*) <a href=materiali_browse.php?risorsa=$id_risorsa target=_blank title=\"$titolo\">$id_risorsa - $titolo</a> ($id_autore - $data_m)  <a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo><img src=img/modify.gif width=25 height=24 alt=\"Modifica\" border=0></a><a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre><img src=img/delete.gif width=25 height=24 alt=\"Cancella\" border=0></a>\n";	
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
			<img src=img/".$icona." width=16 height=16 border=0 alt=\"file da scaricare\"> <a href=materiali_browse.php?risorsa=$id_risorsa title=\"$titolo\">$id_risorsa - $titolo - $file_size Byte</a> ($id_autore - $data_m)  <a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo><img src=img/modify.gif width=25 height=24 alt=\"Modifica\" border=0></a><a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre><img src=img/delete.gif width=25 height=24 alt=\"Cancella\" border=0></a>\n";	
				break;

			case 2:
				echo "
			<a href=index.php?risorsa=materiali_index&id_cartella=$id_risorsa><img src=img/folder.gif width=16 height=15 alt=\"apri cartella\" border=0>$id_risorsa - $titolo</a>  ($id_autore - $data_m) <a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo><img src=img/modify.gif width=25 height=24 alt=\"Modifica\" border=0></a><a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre><img src=img/delete.gif width=25 height=24 alt=\"Cancella\" border=0></a><br>\n";
				break;

		};
	
	echo "</li>\n";	
};
echo "<br>";
?>

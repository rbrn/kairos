<?php
function thread_lab_cartella($id_padre) {
	global $DBHOST,$DBASE,$DBUSER,$DBPWD,$kairos_cookie,$stringa;
	global $id_corso_s,$id_edizione_s,$id_gruppo_lab;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$id_utente=$kairos_cookie["0"];
	$ruolo=ruolo_utente($id_utente);

if ($id_gruppo_lab and $id_gruppo_lab<>"qualunque") {	
$query = "SELECT id_risorsa,risorsa_padre,id_autore,titolo,descrizione,url,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM lab_materiali WHERE risorsa_padre=$id_padre AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_lab' ORDER BY titolo,id_risorsa";
} else {
$query = "SELECT id_risorsa,risorsa_padre,id_autore,titolo,descrizione,url,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM lab_materiali WHERE risorsa_padre=$id_padre AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY titolo,id_risorsa";
};
$result=$mysqli->query($query);

echo mysql_error();

echo "
<ul>\n";
while ($risorsa = $result->fetch_array() ) {
	$id_risorsa = $risorsa["id_risorsa"];
	$risorsa_padre = $risorsa["risorsa_padre"];
	$id_autore=$risorsa["id_autore"];
	$titolo=htmlentities($risorsa["titolo"]);
	$descrizione=htmlentities($risorsa["descrizione"]);
	if (strlen($descrizione)>150) {
		$descrizione=substr($descrizione,0,150)."...";
	};
	$file_size=$risorsa["file_size"];
	$tipo = $risorsa["tipo"];
	$data_m = $risorsa["data_m"];

 	echo "<li style=\"list-style-type:none\">\n";
	echo "<span class=testo>";
	
	switch ($tipo) {
			case 0://pagina web
				echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"$stringa[sito_web]\"> <a href=index.php?risorsa=lab_materiali_view&id_risorsa=$id_risorsa title=\"$descrizione\">$titolo</a> ($id_autore - $data_m)  ";
				if ($id_autore==$id_utente or $ruolo=='admin' or $ruolo=='staff') {
					echo "<a href=lab_materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>&nbsp;<a href=index.php?risorsa=lab_materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";	
				}
				break;
								
			case 1://file
				$icona="file.gif";			
				$est = substr($titolo,-3);
				$tipi_file = array ("zip","exe","xls","doc","pdf","rtf","jpg","gif","mid","mp3",
							"wav","avi","htm","txt","mpg","bmp","ppt");

				if (in_array($est,$tipi_file)) {
					$icona=$est.".gif";
				}; 

				echo "
			<img src=img/".$icona." width=16 height=16 border=0 alt=\"$stringa[file]\"> <a href=index.php?risorsa=lab_materiali_view&id_risorsa=$id_risorsa title=\"$descrizione\">$titolo - ".stringa_filesize($file_size)."</a> ($id_autore - $data_m)  ";
				if ($id_autore==$id_utente or $ruolo=='admin' or $ruolo=='staff') {
					echo "<a href=lab_materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>&nbsp;<a href=index.php?risorsa=lab_materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";	
				};
				break;

			case 2://cartella
				echo "
			<img src=img/folder.gif width=18 height=16 alt=\"$stringa[cartella]\" border=0> <a href=index.php?risorsa=lab_materiali_index&id_cartella=$id_risorsa title=\"$stringa[apri_cartella] $id_risorsa\">$titolo</a>  ($id_autore - $data_m) ";
				if (($ruolo=='admin' or $ruolo=='staff') or ($risorsa_padre<>0 and $id_autore==$id_utente)) {
					echo "<a href=lab_materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>&nbsp;<a href=index.php?risorsa=lab_materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";	
				};
				break;
		};
	echo "</span>";
	echo "</li>\n";
};

echo "</ul>\n";
};


function cancella_lab_cartella($id_padre) {
	global 	$DBHOST, $DBASE,$DBUSER,$DBPWD,$PATH_ARCHIVI_ADMIN,$PATH_ROOT_FILE;
	global $kairos_cookie;
	
	$cod_area=$kairos_cookie[4];

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

	$query="SELECT * FROM lab_materiali WHERE risorsa_padre=$id_padre";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_figlio = $riga["id_risorsa"];
		$tipo_figlio = $riga["tipo"];


		if ($tipo_figlio==1) {
			$query1 = "SELECT titolo FROM lab_materiali WHERE id_risorsa=$id_figlio";
			$result1=$mysqli->query($query1);
			$riga1=$result1->fetch_array();
			$titolo=$riga1["titolo"];
			$fullpath=$PATH_ARCHIVI_ADMIN."materiali/$cod_area/".$titolo;

			if (file_exists($fullpath)) {
				unlink($fullpath);	
			};
		};

		if ($tipo_figlio==2) {
			cancella_lab_cartella($id_figlio);
		};
		
		$query2 = "DELETE FROM lab_materiali WHERE id_risorsa=$id_figlio";
		$result2=$mysqli->query($query2);		
	};
};


function path_cartella_materiali($id_cartella) {
	global 	$DBHOST, $DBASE,$DBUSER,$DBPWD;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
	if ($id_cartella==0) {
		return "";
	} else {
		
		$query="select titolo,risorsa_padre FROM lab_materiali WHERE id_risorsa=$id_cartella";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$titolo=$riga[titolo];
		$id_cartella_sup=$riga["risorsa_padre"];
		return path_cartella_materiali($id_cartella_sup)."/"."<a href=index.php?risorsa=lab_materiali_index&id_cartella=$id_cartella>$titolo</a>";
	};
};


?>

<?php
function thread_risorse($id_padre,$pagina) {
	global $DBHOST,$DBASE,$DBUSER,$DBPWD,$kairos_cookie,$stringa;
	global $ruolo;
	global $pag_size;
	global $repertorio;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$id_utente=$kairos_cookie["0"];
	$cod_area=$kairos_cookie["4"];


$query = "SELECT id_risorsa,risorsa_padre,id_autore,id_editor,id_editor_gruppo,titolo,tipo,file_size,DATE_FORMAT(data_crea,'%d/%m/%Y %H:%i') as data_m,id_gruppo FROM risorse_materiali WHERE risorsa_padre='$id_padre' and (tipo='0' or tipo='1' or tipo='2' or tipo='3') ORDER BY posizione";
$result=$mysqli->query($query);

if (!$pag_size) $pag_size=20;
if (!$pagina) $pagina=1;

$tot_righe=$result->num_rows;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$num =$tot_righe;

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;
$righe=1;
$continua = true;

echo "
<ul>\n";

while ($risorsa=$result->fetch_array()) {
	$id_risorsa = $risorsa["id_risorsa"];
	$id_gruppo = $risorsa["id_gruppo"];
	$id_autore=$risorsa["id_autore"];
	$id_editor=$risorsa["id_editor"];
	$id_editor_gruppo=$risorsa["id_editor_gruppo"];
	$id_cartella_sup=$risorsa["risorsa_padre"];
	
	$titolo=$risorsa["titolo"];
	$file_size=$risorsa["file_size"];
	$tipo = $risorsa["tipo"];
	$data_m = $risorsa["data_m"];
	
	$editabile=false;
	if ($id_utente==$id_autore or $id_utente==$id_editor or $ruolo=='admin') {
		$editabile=true;
	};
	
	if (!$editabile) {
		$query_g="SELECT * FROM editor_gruppo_utenti WHERE id_utente='$id_utente' AND id_editor_gruppo='$id_editor_gruppo'";
		$result_g=$mysqli->query($query_g);
		$in_gruppo=$result_g->num_rows;
		if ($tipo==2 and $in_gruppo) $editabile=true;
		if ($tipo<>2) {
			$query_g="SELECT id_editor_gruppo FROM risorse_materiali WHERE id_risorsa='$id_cartella_sup'";
			$result_g=$mysqli->query($query_g);
			$riga_g=$result_g->fetch_array();
			$id_editor_gruppo=$riga_g[id_editor_gruppo];
			$query_g="SELECT * FROM editor_gruppo_utenti WHERE id_utente='$id_utente' AND id_editor_gruppo='$id_editor_gruppo'";
			$result_g=$mysqli->query($query_g);
			$in_gruppo=$result_g->num_rows;
			if ($in_gruppo) $editabile=true;
		};
	};
		
	if ($id_editor) $id_autore=$id_autore."/".$id_editor;
	
	

 	echo "<li style=\"list-style-type:none\">\n";
	echo "<span class=testo>";
		if ($editabile) {
		echo "<a href=materiali_sposta.php?id_risorsa=$id_risorsa&risorsa_padre=$id_padre&azione=up><img src=img/up.gif width=11 height=7 border=0 alt=\"$stringa[pagina_up]\"></a><a href=materiali_sposta.php?id_risorsa=$id_risorsa&risorsa_padre=$id_padre&azione=down><img src=img/down.gif width=11 height=7 border=0 alt=\"$stringa[pagina_down]\"></a>";
		};
		
		switch ($tipo) {
			case 0://pagina web
				echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"$stringa[pagina_web]\"> <a href=materiali_browse.php?risorsa=$id_risorsa target=_blank title=\"$id_risorsa\">$titolo</a> ($id_autore - $data_m)";
		
				if ($editabile) {
					echo "<a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>&nbsp;<a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";
				};
				
				break;
				
			case 4://collegamento a pagina web
				$query_r = "SELECT titolo,id_editor,id_autore FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
				$result_r=$mysqli->query($query_r);
				$risorsa_r = $result_r->fetch_array();
				
				$titolo=$risorsa_r["titolo"];
				$id_editor_r=$risorsa_r["id_editor"];
				$id_autore_r=$risorsa_r["id_autore"];
				
				$id_autore=$id_autore_r;
				if ($id_editor_r) $id_autore=$id_autore_r."/".$id_editor_r;
				
				echo "
			<img src=img/pagina_web_link.gif width=16 height=16 border=0 alt=\"$stringa[pagina_web]\"> <a href=materiali_browse.php?risorsa=$id_risorsa target=_blank title=\"$id_gruppo\">$titolo</a> ($id_autore - $data_m)";
				
				if ($editabile) {
					if ($ruolo=='admin' or $id_editor_r==$id_utente) {
				   		echo "<a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>";
					}; 
					echo "&nbsp;<a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";	
				};
				
				break;
					

			case 3://nota
				echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"$stringa[nota]\">(*) <a href=materiali_browse.php?risorsa=$id_risorsa target=_blank title=\"$id_risorsa\">$titolo</a> ($id_autore - $data_m)";

				if ($editabile) {
					echo "<a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>&nbsp;<a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";
				};
				
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
			<img src=img/".$icona." width=16 height=16 border=0 alt=\"$stringa[file]\"> <a href=materiali_browse.php?risorsa=$id_risorsa title=\"$id_risorsa\">$titolo -  ".stringa_filesize($file_size)."</a> ($id_autore - $data_m)";
				if ($editabile) {	
					echo "<a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>&nbsp;<a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";
				};
				
				break;

			case 2://cartella
			
			$evidenzia_gruppo=true;
			$descr_gruppo="";
			
			if ($id_editor_gruppo) {
				$query_g="SELECT * FROM editor_gruppo_utenti WHERE id_utente='$id_utente' AND id_editor_gruppo='$id_editor_gruppo'";
				$result_g=$mysqli->query($query_g);
				if (!$result_g->num_rows) {
					$evidenzia_gruppo=false;
				} else {
					$query_g="SELECT descrizione FROM editor_gruppo WHERE id_editor_gruppo='$id_editor_gruppo'";
					$result_g=$mysqli->query($query_g);
					$riga_g=$result_g->fetch_array();
					$descr_gruppo=$riga_g["descrizione"];
				};
			} else {
				$evidenzia_gruppo=false;
			};
			
				echo "
			<img src=img/folder.gif width=18 height=16 alt=\"$stringa[cartella]\" border=0> <a href=index.php?risorsa=materiali_index&id_cartella=$id_risorsa title=\"$stringa[apri_cartella] $id_risorsa\">$titolo</a>  ($id_autore - $data_m)";
				if ($evidenzia_gruppo) {
					echo " $descr_gruppo ";
				};
				
				if ($editabile) {
					echo "<a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>&nbsp;<a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";
				};
				break;
		};
	
	if ($editabile) {
	echo "<a href=\"javascript:;\" title=\"$stringa[materiale_storia]\" onclick=\"javascript:apri_scheda('materiali_storia.php?id_risorsa=$id_risorsa',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_chiletto_$id_risorsa','','img/ico_forum_chiletto_over.gif',1)\"><img src=\"img/ico_forum_chiletto.gif\" width=\"20\" height=\"20\" alt=\"$stringa[materiale_storia]\" border=\"0\" name=\"img_chiletto_$id_risorsa\"></a>";
		
		if ($id_padre=="root") {
			/*
			echo "<a href=\"javascript:;\" title=\"edit metadata\" onclick=\"javascript:apri_scheda('lom/index.php?id_lo=$id_risorsa',                   'myRemoteUtente',        'height=550,width=800,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_editlom_$id_risorsa','','img/ico_lom_over.gif',1)\"><img src=\"img/ico_lom.gif\" width=\"20\" height=\"20\" alt=\"edit metadata\" border=\"0\" name=\"img_editlom_$id_risorsa\"></a>";
			*/
			/*
			echo "&nbsp;<a href=\"scorm/esporta_modulo.php?id_modulo=$id_risorsa\" title=\"esporta LO\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_esportalo_$id_risorsa','','img/ico_lo_export_over.gif',1)\"><img src=\"img/ico_lo_export.gif\" width=\"20\" height=\"20\" alt=\"esporta\" border=\"0\" name=\"img_esportalo_$id_risorsa\"></a>";
			*/
			/*
			if ($cod_area=="kairos_area_corsi") {
			echo "&nbsp;[<a href=slideshow.php?risorsa=$id_risorsa target=_blank>SlideShow</a>]";
			}
			
			if ($cod_area=="kairos_itc_scuola") {
			echo "&nbsp;[<a href=\"javascript:;\" onclick=\"javascript:apri_scheda('lo_viewer.php?risorsa=$id_risorsa','myRemoteLO',        'height=620,width=800,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=auto,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLO');\">Lancia LO</a>] [<a href=\"javascript:;\" onclick=\"javascript:apri_scheda('lo_view_tracking.php?id_lo=$id_risorsa','myRemoteTLO',        'height=500,width=700,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=auto,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLO');\">Traccia LO</a>]";
			};
			*/
			
		};
	};
	
	echo "</span>";
	echo "</li>\n";
	
	$righe++;
	$progr++;
	
};

echo "</ul>\n";

echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?risorsa=materiali_index&pagina=$i&pag_size=$pag_size&id_cartella=$id_padre>$i</a>]
		";
	};
	$i++;
};
echo "</span><br>";	
/*

echo "
<hr size=1>";

echo "
<span class=testo><b>$stringa[repertorio_pagine]</b>: ";

if ($repertorio=='mostra') {
	echo "[<a href=index.php?risorsa=materiali_index&pagina=$pagina&pag_size=$pag_size&id_cartella=$id_padre&repertorio=nascondi>".$stringa[nascondi]."</a>]";
} else {
	echo "[<a href=index.php?risorsa=materiali_index&pagina=$pagina&pag_size=$pag_size&id_cartella=$id_padre&repertorio=mostra>".$stringa[mostra]."</a>]";
};

echo "</span><br><br>";

if ($repertorio=='mostra') {
echo "
<form action=collegamento_risorse.php method=post>
<input type=hidden name=risorsa_padre value=\"$id_padre\">
";
$query="SELECT * FROM risorse_materiali WHERE tipo='0' AND risorsa_padre<>'$id_padre' ORDER BY id_risorsa";
$result=$mysqli->query($query);
$elenco="";
while ($riga=$result->fetch_array()) {
	$id_risorsa=$riga[id_risorsa];
	$titolo=$riga[titolo];
	$elenco .= "<option value=\"$id_risorsa\">$titolo</option>";
};
echo "
<select multiple name=collega_risorse[] size=20>
$elenco
</select><br>
<input type=submit value=\"$stringa[collega_pagine]\">
</form>";
};
*/


};


function cancella_contenuto($id_padre) {
	global 	$DBHOST, $DBASE,$DBUSER,$DBPWD,$PATH_ARCHIVI_ADMIN,$PATH_ROOT_FILE;
	global $kairos_cookie;
	
	$cod_area=$kairos_cookie[4];

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

	$query="SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_padre'";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_figlio = $riga["id_risorsa"];
		$tipo_figlio = $riga["tipo"];

		if ($tipo_figlio==0) {
			$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/$id_figlio.inc";
			if (file_exists($file_codice)) {
				unlink($file_codice);	
			};
			$query_t = "DELETE FROM risorse_materiali WHERE id_gruppo='$id_figlio'";
			$mysqli->query($query_t);
		};


		if ($tipo_figlio==1) {
			$query1 = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_figlio'";
			$result1=$mysqli->query($query1);
			$riga1=$result1->fetch_array();
			$titolo=$riga1["titolo"];
			$fullpath=$PATH_ARCHIVI_ADMIN."materiali/$cod_area/".$titolo;

			if (file_exists($fullpath)) {
				unlink($fullpath);	
			};
		};

		if ($tipo_figlio==2) {
			cancella_contenuto($id_figlio);
		};
		$query2 = "DELETE FROM risorse_materiali WHERE id_risorsa='$id_figlio'";
		$result2=$mysqli->query($query2);		
		
		$query2 = "DELETE FROM materiali_storia WHERE id_risorsa='$id_figlio'";
		$result2=$mysqli->query($query2);
	};
};



function browse_folder($cartella,$tipo_file='',$contesto='',$nome_campo='') {
	global $PATH_ROOT,$PATH_ROOT_FILE,$cod_area,$stringa;
	global $dir;
	global $usanuovoeditor;

	if (!$cartella or $cartella=="/" or trim($cartella)=="" or ereg("^\\.(.+)$",$cartella)) {
		$cartella="";
	};

	if ($dir) {
		$dir_path=$PATH_ROOT_FILE."materiali_img/$cod_area/$dir/".$cartella;
	} else {
		$dir_path=$PATH_ROOT_FILE."materiali_img/$cod_area/".$cartella;
	};
	
	if (!is_dir($dir_path)) {
	
		@mkdir($dir_path,0755);
		/*
		$cartella="";
		if ($dir) {
			$dir_path=$PATH_ROOT_FILE."materiali_img/$cod_area/$dir/".$cartella;
		} else {
			$dir_path=$PATH_ROOT_FILE."materiali_img/$cod_area/".$cartella;
		};
		*/
	};

	if ($cartella<>"") {
		$padre=dirname($cartella);
		echo "
		[<a href=index.php?risorsa=materiali_cartella&tipo=$tipo_file&cartella=$padre&dir=$dir&contesto=$contesto&nome_campo=$nome_campo>$stringa[dir_superiore]</a>]<br><hr>";
	};

	echo "<h1>".$cartella."</h1>";
	$i=0;
	$d = dir($dir_path);
	while ($filename=$d->read()) {
		if (($filename != '.') && ($filename != '..')) { 
			$prendi=true;
			$path_file=$PATH_ROOT_FILE."materiali_img/$cod_area/$dir/".$cartella."/".$filename;
			if ($tipo_file and !is_dir($path_file)) {
				ereg("^(.+)\.(.+)$",$filename,$parti);
				$est=$parti[2];
				
				switch ($tipo_file) {
					case "audio":
						if ($est<>'mp3') {
							$prendi=false;
						};
						break;
						
					case "video":
						if ($est<>'wmv' and $est<>'mov' and $est<>'rpm' and $est<>'mp4' and $est<>'ogg' and $est <> 'webm') {
							$prendi=false;
						};
						break;
				
					case "flash":
						if ($est<>'swf') {
							$prendi=false;
						};
						break;	
					
					case "ggb":
						if ($est<>'ggb') {
							$prendi=false;
						};
						break;	
						
					case "img":
						if ($est<>'gif' and $est<>'jpg' and $est<>'png') {
							$prendi=false;
						};
						break;
				};
			};
			
			if ($prendi) {
				$entry[$i]=$filename;
				$i++;
			};
		};
	};
	$d->close();
	if ($i) {
		sort($entry);
	};

	for ($j=0;$j<$i;$j++){ 
		$filename=$entry[$j];
	$path_file=$PATH_ROOT_FILE."materiali_img/$cod_area/$dir/".$cartella."/".$filename;
		//echo "<input type=checkbox name=$filename> ";
		if (is_dir($path_file)) {
			echo "
				<img src=img/folder.gif width=18 height=16 border=0> <a href=index.php?risorsa=materiali_cartella&tipo=$tipo_file&dir=$dir&contesto=$contesto&nome_campo=$nome_campo&cartella=$cartella"."/".$filename.">$filename</a><br>";
		} else {
			    if ($cartella) {
					if ($dir) {
			$val=$PATH_ROOT."materiali_img/$cod_area/$dir/".$cartella."/".$filename;
					} else {
					$val=$PATH_ROOT."materiali_img/$cod_area/".$cartella."/".$filename;
					}
				} else { 
					if ($dir) {
					$val=$PATH_ROOT."materiali_img/$cod_area/$dir/$filename";
					} else {
					$val=$PATH_ROOT."materiali_img/$cod_area/$filename";
					}
				};	
				$fun="";
				if ($usanuovoeditor) $fun="_n";
				if ($tipo_file=="flash") {
					$size=getimagesize($path_file);
					$w=$size[0];
					$h=$size[1];
					if ($contesto=="lo") {	
						$comando="inserisci_indirizzo_wh_lo".$fun."('$val','$w','$h','$nome_campo');";
					} else {
						$comando="inserisci_indirizzo_wh".$fun."('$val','$w','$h');";
					}
				} else {
					if ($contesto=="lo") {	
						$comando="inserisci_indirizzo_lo".$fun."('$val','$nome_campo');";
					} else {	
						$comando="inserisci_indirizzo".$fun."('$val');";
					};
				};
				echo "<a href=$val target=_blank>$filename</a> [<a href=\"javascript:;\" onclick=\"$comando\">$stringa[inserisci]</a>] <br>\n";
		};
	};
};

function setup_posizione($id_padre) {
	global 	$DBHOST,$DBASE,$DBUSER,$DBPWD;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$pos=1;
	$query="SELECT id_risorsa,tipo FROM risorse_materiali WHERE risorsa_padre='$id_padre' ORDER BY posizione,id_risorsa";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_risorsa = $riga["id_risorsa"];
		$tipo = $riga["tipo"];
		$query2="UPDATE risorse_materiali SET posizione='$pos' WHERE id_risorsa='$id_risorsa'";
		$mysqli->query($query2);
		$pos++;
		if ($tipo==2) {
			setup_posizione($id_risorsa);
		};
	};	
};

function contiene_pagina($id_cartella) {
	global 	$DBHOST,$DBASE,$DBUSER,$DBPWD;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$risultato=false;
	$query="SELECT tipo FROM risorse_materiali WHERE risorsa_padre='$id_cartella' ORDER BY posizione,id_risorsa";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array() and !$risultato) {
		$tipo = $riga["tipo"];
		if ($tipo==0 or $tipo==4) {
			$risultato=true;
		};
	};
	return $risultato;	
};

function path_cartella($id_cartella) {
	global 	$DBHOST, $DBASE,$DBUSER,$DBPWD;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	if ($id_cartella=="root") {
		return "";
	} else {
		
		$query="select titolo,risorsa_padre FROM risorse_materiali WHERE id_risorsa='$id_cartella'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$titolo=$riga[titolo];
		$id_cartella_sup=$riga["risorsa_padre"];
		return path_cartella($id_cartella_sup)."/"."<a href=index.php?risorsa=materiali_index&id_cartella=$id_cartella>$titolo</a>";
	};
};

?>

<?php
function thread_risorse($id_padre,$pagina) {
	global $DBHOST,$DBASE,$DBUSER,$DBPWD,$kairos_cookie,$stringa;
	global $ruolo;
	global $pag_size;
	global $id_corso_s,$id_edizione_s;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$id_utente=$kairos_cookie["0"];

$query = "SELECT id_risorsa,risorsa_padre,id_autore,id_editor,titolo,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m,id_gruppo FROM materiali_gruppo WHERE risorsa_padre='$id_padre' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'  ORDER BY posizione";
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

echo "
<ul>\n";

while ($risorsa=$result->fetch_array()) {
	$id_risorsa = $risorsa["id_risorsa"];
	$id_gruppo = $risorsa["id_gruppo"];
	$id_autore=$risorsa["id_autore"];
	$id_editor=$risorsa["id_editor"];
	$id_cartella_sup=$risorsa["risorsa_padre"];
	
	$titolo=$risorsa["titolo"];
	$file_size=$risorsa["file_size"];
	$tipo = $risorsa["tipo"];
	$data_m = $risorsa["data_m"];
	
	$editabile=false;
	if ($id_utente==$id_autore or $id_utente==$id_editor or $ruolo=='admin' or $ruolo=="staff") {
		$editabile=true;
	};
	
	//if (!$editabile) {
		$id_gruppo=gruppo_nodo($id_risorsa);
		$query_g="SELECT * FROM iscrizioni_gruppo_pw WHERE id_utente='$id_utente' AND id_gruppo='$id_gruppo' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
		$result_g=$mysqli->query($query_g);
		$in_gruppo=$result_g->num_rows;
		if ($in_gruppo) $editabile=true;
	//};
		
	if ($id_editor) $id_autore=$id_autore."/".$id_editor;
	
	if ($id_padre=="root" and $kairos_cookie[4]=="kairos_eprof" and $ruolo<>"admin" and $ruolo<>"staff") $editabile=false;

 	echo "<li style=\"list-style-type:none\">\n";
	echo "<span class=testo>";
		echo "<a href=materiali_gruppo_sposta.php?id_risorsa=$id_risorsa&risorsa_padre=$id_padre&azione=up><img src=img/up.gif width=11 height=7 border=0 alt=\"$stringa[pagina_up]\"></a><a href=materiali_gruppo_sposta.php?id_risorsa=$id_risorsa&risorsa_padre=$id_padre&azione=down><img src=img/down.gif width=11 height=7 border=0 alt=\"$stringa[pagina_down]\"></a>";
		
		switch ($tipo) {
			case 0://pagina web
				echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"$stringa[pagina_web]\"> <a href=materiali_gruppo_browse.php?risorsa=$id_risorsa target=_blank title=\"$stringa[anteprima_altra_finestra]\">$titolo</a> ($id_autore - $data_m)";
		
				if ($editabile) {
					echo "<a href=materiali_gruppo_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>&nbsp;<a href=index.php?risorsa=materiali_gruppo_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";
				};
				
				break;
			
					

			case 3://nota
				echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"$stringa[nota]\">(*) <a href=materiali_gruppo_browse.php?risorsa=$id_risorsa target=_blank title=\"$stringa[anteprima_altra_finestra]\">$titolo</a> ($id_autore - $data_m)";

				if ($editabile) {
					echo "<a href=materiali_gruppo_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>&nbsp;<a href=index.php?risorsa=materiali_gruppo_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";
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
			<img src=img/".$icona." width=16 height=16 border=0 alt=\"$stringa[file]\"> <a href=materiali_gruppo_browse.php?risorsa=$id_risorsa title=\"$stringa[anteprima_altra_finestra]\">$titolo -  ".stringa_filesize($file_size)."</a> ($id_autore - $data_m)";
				if ($editabile) {	
					echo "<a href=materiali_gruppo_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>&nbsp;<a href=index.php?risorsa=materiali_gruppo_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";
				};
				
				break;

			case 2://cartella
			
			$evidenzia_gruppo=false;
			$descr_gruppo="";
			
			if ($id_cartella_sup=="root") {
				$query_g="SELECT descrizione FROM gruppo_utenti WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
				$result_g=$mysqli->query($query_g);
				$riga_g=$result_g->fetch_array();
				$descr_gruppo=$riga_g["descrizione"];
				$evidenzia_gruppo=true;
			};
			
				echo "
			<img src=img/folder.gif width=18 height=16 alt=\"$stringa[cartella]\" border=0> ";
				if ($evidenzia_gruppo) {
					$b1="";
					$b2="";
					if ($in_gruppo) {
						$b1="<b>";
						$b2="</b>";
					};
					echo " [<a class=miolink href=\"javascript:;\" title=\"$stringa[componenti_gruppo]\" onclick=\"javascript:apri_scheda('gruppo_pw_iscritti.php?id_gruppo=$id_gruppo',                   'myRemoteGruppo',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowGruppo');\">$b1".$descr_gruppo."$b2</a>] ";
				};
				
				echo "<a href=index.php?risorsa=materiali_gruppo_index&id_cartella=$id_risorsa title=\"$stringa[apri_cartella]\">$titolo</a>  ($id_autore - $data_m)";
				
				
				if ($editabile) {
					echo "<a href=materiali_gruppo_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a>&nbsp;<a href=index.php?risorsa=materiali_gruppo_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a>\n";
				};
				break;
		};
	if ($editabile) {
	echo "<a href=\"javascript:;\" title=\"$stringa[materiale_storia]\" onclick=\"javascript:apri_scheda('materiali_gruppo_storia.php?id_risorsa=$id_risorsa',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_chiletto_$id_risorsa','','img/ico_forum_chiletto_over.gif',1)\"><img src=\"img/ico_forum_chiletto.gif\" width=\"20\" height=\"20\" alt=\"$stringa[materiale_storia]\" border=\"0\" name=\"img_chiletto_$id_risorsa\"></a>";
		$query_n="SELECT risorsa_padre FROM materiali_gruppo WHERE id_risorsa='$id_cartella_sup'";
		$result_n=$mysqli->query($query_n);
		$riga_n=$result_n->fetch_array();
		$id_nonno=$riga_n[risorsa_padre];
		
		if ($id_nonno=="root") {
			/*
			echo "<a href=\"javascript:;\" title=\"edit metadata\" onclick=\"javascript:apri_scheda('lom/index.php?id_lo=gruppo_$id_risorsa',                   'myRemoteUtente',        'height=550,width=800,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_editlom_$id_risorsa','','img/ico_lom_over.gif',1)\"><img src=\"img/ico_lom.gif\" width=\"20\" height=\"20\" alt=\"edit metadata\" border=\"0\" name=\"img_editlom_$id_risorsa\"></a>";

			echo "&nbsp;<a href=\"scorm/esporta_modulo.php?id_modulo=$id_risorsa&gruppo=1\" title=\"esporta LO\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_esportalo_$id_risorsa','','img/ico_lo_export_over.gif',1)\"><img src=\"img/ico_lo_export.gif\" width=\"20\" height=\"20\" alt=\"esporta LO\" border=\"0\" name=\"img_esportalo_$id_risorsa\"></a>";
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
		[<a href=index.php?risorsa=materiali_gruppo_index&pagina=$i&pag_size=$pag_size&id_cartella=$id_padre>$i</a>]
		";
	};
	$i++;
};
echo "</span><br>";	

};


function cancella_contenuto($id_padre) {
	global 	$DBHOST, $DBASE,$DBUSER,$DBPWD,$PATH_ARCHIVI_ADMIN,$PATH_ROOT_FILE;
	global $kairos_cookie;
	
	$cod_area=$kairos_cookie[4];

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

	$query="SELECT * FROM materiali_gruppo WHERE risorsa_padre='$id_padre'";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_figlio = $riga["id_risorsa"];
		$tipo_figlio = $riga["tipo"];

		if ($tipo_figlio==0) {
			$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/gruppo/$id_figlio.inc";
			if (file_exists($file_codice)) {
				unlink($file_codice);	
			};
			//mysql_query($query_t,$db);
		};


		if ($tipo_figlio==1) {
			$query1 = "SELECT titolo FROM materiali_gruppo WHERE id_risorsa='$id_figlio'";
			$result1=$mysqli->query($query1);
			$riga1=$result1->fetch_array();
			$titolo=$riga1["titolo"];
			$fullpath=$PATH_ARCHIVI_ADMIN."materiali/$cod_area/gruppo/".$titolo;

			if (file_exists($fullpath)) {
				unlink($fullpath);	
			};
		};

		if ($tipo_figlio==2) {
			cancella_contenuto($id_figlio);
		};
		$query2 = "DELETE FROM materiali_gruppo WHERE id_risorsa='$id_figlio'";
		$result2=$mysqli->query($query2);		
		
		$query2 = "DELETE FROM materiali_gruppo_storia WHERE id_risorsa='$id_figlio'";
		$mysqli->query($query2);
	};
};



function browse_folder($cartella,$tipo_file='') {
	global $PATH_ROOT,$PATH_ROOT_FILE,$cod_area,$stringa;

	if (!$cartella or $cartella=="/" or trim($cartella)=="" or ereg("^\\.(.+)$",$cartella)) {
		$cartella="";
	};

	$dir_path=$PATH_ROOT_FILE."materiali_img/$cod_area/".$cartella;

	if (!is_dir($dir_path)) {
		$cartella="";
		$dir_path=$PATH_ROOT_FILE."materiali_img/$cod_area/".$cartella;
	};

	if ($cartella<>"") {
		$padre=dirname($cartella);
		echo "
		[<a href=index.php?risorsa=materiali_cartella&tipo=$tipo_file&cartella=$padre>$stringa[dir_superiore]</a>]<br><hr>";
	};

	echo "<h1>".$cartella."</h1>";
	$i=0;
	$d = dir($dir_path);
	while ($filename=$d->read()) {
		if (($filename != '.') && ($filename != '..')) { 
			$prendi=true;
			$path_file=$PATH_ROOT_FILE."materiali_img/$cod_area/".$cartella."/".$filename;
			if ($tipo_file and !is_dir($path_file)) {
				ereg("^(.+)\.(.+)$",$filename,$parti);
				$est=$parti[2];
				
				switch ($tipo_file) {
					case "audio":
						if ($est<>'wav' and $est<>'au' and $est<>'asf' 
							and $est<>'mid') {
							$prendi=false;
						};
						break;
						
					case "video":
						if ($est<>'avi' and $est<>'mov' and $est<>'mpg') {
							$prendi=false;
						};
						break;
				
					case "flash":
						if ($est<>'swf') {
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
	$path_file=$PATH_ROOT_FILE."materiali_img/$cod_area/".$cartella."/".$filename;
		echo "
		<input type=checkbox name=$filename> ";
		if (is_dir($path_file)) {
			echo "
				<img src=img/folder.gif width=18 height=16 border=0> <a href=index.php?risorsa=materiali_cartella&tipo=$tipo_file&cartella=$cartella"."/".$filename.">$filename</a><br>";
		} else {
			    if ($cartella) {
			$val=$PATH_ROOT."materiali_img/$cod_area/".$cartella."/".$filename;
				} else { 
					$val=$PATH_ROOT."materiali_img/$cod_area/$filename";
				};	
				if ($tipo_file=="flash") {
					$size=getimagesize($path_file);
					$w=$size[0];
					$h=$size[1];	
					$comando="inserisci_indirizzo_wh('$val','$w','$h');";
				} else {
					$comando="inserisci_indirizzo('$val');";
				};
				echo "<a href=$val target=_blank>$filename</a> [<a href=\"javascript:;\" onclick=\"$comando\">$stringa[inserisci]</a>] [<a href=\"javascript:;\" onclick=\"copia_indirizzo('$val');\">$stringa[copia_indirizzo]</a>] <br>\n";
		};
	};
};

function setup_posizione($id_padre) {
	global 	$DBHOST,$DBASE,$DBUSER,$DBPWD;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$pos=1;
	$query="SELECT id_risorsa,tipo FROM materiali_gruppo WHERE risorsa_padre='$id_padre' ORDER BY posizione,id_risorsa";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_risorsa = $riga["id_risorsa"];
		$tipo = $riga["tipo"];
		$query2="UPDATE materiali_gruppo SET posizione='$pos' WHERE id_risorsa='$id_risorsa'";
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
	$query="SELECT tipo FROM materiali_gruppo WHERE risorsa_padre='$id_cartella' ORDER BY posizione,id_risorsa";
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
		
		$query="select titolo,risorsa_padre FROM materiali_gruppo WHERE id_risorsa='$id_cartella'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$titolo=$riga[titolo];
		$id_cartella_sup=$riga["risorsa_padre"];
		return path_cartella($id_cartella_sup)."/"."<a href=index.php?risorsa=materiali_gruppo_index&id_cartella=$id_cartella>$titolo</a>";
	};
};

?>

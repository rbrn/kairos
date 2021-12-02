<?php
function thread_risorse($id_padre,$pagina) {
	global $DBHOST,$DBASE,$DBUSER,$DBPWD,$kairos_cookie,$stringa;
	global $ruolo;
	global $pag_size;
	global $colore_scuro,$colore_sfondo;
	global $editor_lo;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$id_utente=$kairos_cookie["0"];
	$cod_area=$kairos_cookie["4"];

	if ($editor_lo) {
		if ($ruolo=="admin" or $ruolo=="staff") {
			$query = "SELECT id_risorsa,risorsa_padre,id_autore,id_editor,id_editor_gruppo,titolo,tipo,file_size,DATE_FORMAT(data_crea,'%d/%m/%Y %H:%i') as data_m,id_gruppo,url FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo='20' or tipo='200' or tipo='200' or tipo='201' or tipo='202') ORDER BY posizione";

		} else {
			$query = "SELECT id_risorsa,risorsa_padre,id_autore,id_editor,id_editor_gruppo,titolo,tipo,file_size,DATE_FORMAT(data_crea,'%d/%m/%Y %H:%i') as data_m,id_gruppo,url FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (id_autore='$id_utente' OR id_editor='$id_utente' OR titolo='lo esempio') AND (tipo='20' or tipo='200' or tipo='200' or tipo='201' or tipo='202') ORDER BY posizione";
		};
		
		if ($id_padre<>"root") {
			$query = "SELECT id_risorsa,risorsa_padre,id_autore,id_editor,id_editor_gruppo,titolo,tipo,file_size,DATE_FORMAT(data_crea,'%d/%m/%Y %H:%i') as data_m,id_gruppo,url FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo='20' or tipo='200' or tipo='200' or tipo='201' or tipo='202') ORDER BY posizione";
		
		};
	};
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

	if ($id_padre<>"root") {
		$path_cartella=path_cartella($id_padre);
		$id_lo_padre=id_corso($id_padre);
		
		$query_lo="SELECT * FROM lo WHERE id_lo='$id_lo_padre'";
		$result_lo=$mysqli->query($query_lo);
		$riga_lo=$result_lo->fetch_array();
					
		$lo_tipo=$riga_lo["lo_tipo"];
		$lo_url=$riga_lo["lo_url"];
		$width=$riga_lo["width"];
		$height=$riga_lo["height"];
		
		if ($lo_tipo=='1') { 
			$tipo_lancio="lo";
		} else {
			$tipo_lancio="url";
		};
	};

	echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"100%\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";

	echo "<tr>";

	echo "<td width=10 align=center bgcolor=\"$colore_scuro\">";
	if ($id_padre<>"root") {
		echo "&nbsp;";
	} else {
		echo "<img src=img/ico_materiali_int.gif width=15 height=16 alt=\"$stringa[lo]\" border=0>";
	};
	echo "</td>";

	if ($id_padre<>"root") {
		echo "
<td colspan=4 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[contenuto_cartella]: $path_cartella</b></span></td>";
		echo "
<td colspan=4 bgcolor=\"$colore_scuro\" align=center><span class=testonegativo><b>$stringa[azioni]</b></span></td>";
	} else {
		echo "
<td colspan=5 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[titolo_lo_autore]</b></span></td>";
echo "
<td colspan=4 bgcolor=\"$colore_scuro\" align=center><span class=testonegativo><b>$stringa[azioni]</b></span></td>";
	};


echo "</tr>\n";

	$colore=$colore_sfondo;
	
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
		$url = $risorsa["url"];
	
		$editabile=false;
		if ($id_utente==$id_autore or $id_utente==$id_editor or $ruolo=='admin') {
			$editabile=true;
		};
	
		if (!$editabile) {
			$query_g="SELECT * FROM editor_gruppo_utenti WHERE id_utente='$id_utente' AND id_editor_gruppo='$id_editor_gruppo'";
			$result_g=$mysqli->query($query_g);
			$in_gruppo=$result_g->num_rows;
			if ($tipo==20 and $in_gruppo) $editabile=true;
			if ($tipo<>20) {
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
	
		echo "<tr bgcolor=\"$colore\">";
		
		echo "<td width=30>";
		if ($editabile) {
		echo "<a href=repository_sposta.php?id_risorsa=$id_risorsa&risorsa_padre=$id_padre&azione=up><img src=img/up.gif width=11 height=7 border=0 alt=\"$stringa[pagina_up]\"></a><a href=repository_sposta.php?id_risorsa=$id_risorsa&risorsa_padre=$id_padre&azione=down><img src=img/down.gif width=11 height=7 border=0 alt=\"$stringa[pagina_down]\"></a>";
		};
		echo "</td>";
		
		switch ($tipo) {
			case 20: //cartella - LO
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
			
				if ($id_padre=="root") {
					$query_lo="SELECT * FROM lo WHERE id_lo='$id_risorsa'";
					$result_lo=$mysqli->query($query_lo);
					$riga_lo=$result_lo->fetch_array();
					
					$lo_tipo=$riga_lo["lo_tipo"];
					$lo_url=$riga_lo["lo_url"];
					$width=$riga_lo["width"];
					$height=$riga_lo["height"];
					$tipo_shell=$riga_lo["lo_shell"];
					switch  ($tipo_shell) {
						case 0:
							$lo_viewer_script="lo_viewer.php";
							break;
						case 1:
							$lo_viewer_script="lo_viewer_new.php";
							break;
						
					}
					echo "<td><span class=testopiccolo><b>$titolo</b>  ($id_autore - $data_m) $descr_gruppo</span></td>";

					if ($lo_tipo=='1') {
						echo "<td align=center><a href=index.php?risorsa=repository_index&id_cartella=$id_risorsa title=\"$stringa[apri_cartella] $id_risorsa\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_risorsa','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" 			name=\"img_apri_$id_risorsa\"></a></td>";
				
						$nomarchio="";		

						echo "<td align=center><a href=\"$lo_viewer_script?risorsa=$id_risorsa&esporta=1&nomarchio=$nomarchio\" title=\"esporta LO\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_esportalo_$id_risorsa','','img/ico_lo_export_over.gif',1)\"><img src=\"img/ico_lo_export.gif\" width=\"20\" height=\"20\" alt=\"esporta\" border=\"0\" name=\"img_esportalo_$id_risorsa\"></a></td>";

					} else {
						echo "<td>&nbsp;</td><td>&nbsp;</td>";
					};
					if ($lo_tipo=='1') { 
						$tipo_lancio="lo";
					} else {
						$tipo_lancio="url";
						$tipo=22;
					};
					
					echo "<td align=center><a href=\"javascript:;\" onclick=\"javascript:apri_scheda('sco_viewer.php?id_risorsa=$id_risorsa&tipo=$tipo_lancio&url=$lo_url','myRemoteLO',        'height=$height,width=$width,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=0,scrollbars=0,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLO');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_lo_lancia_$id_risorsa','','img/ico_lo_lancia_over.gif',1)\"><img src=\"img/ico_lo_lancia.gif\" width=\"20\" height=\"20\" alt=\"$stringa[lancia_lo]\" border=\"0\" name=\"img_lo_lancia_$id_risorsa\"></a></td>";
					if ($editabile) {
					echo "<td align=center><a href=\"javascript:;\" title=\"edit metadata\" onclick=\"javascript:apri_scheda('lom/index.php?id_lo=$id_risorsa',                   'myRemoteUtente',        'height=550,width=800,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_editlom_$id_risorsa','','img/ico_lom_over.gif',1)\"><img src=\"img/ico_lom.gif\" width=\"20\" height=\"20\" alt=\"edit metadata\" border=\"0\" name=\"img_editlom_$id_risorsa\"></a></td>";
					} else {
						echo "<td></td>";
					};
					echo "<td align=center><a href=\"javascript:;\" onclick=\"javascript:apri_scheda('lo_view_tracking.php?id_lo=$id_risorsa','myRemoteTLO',        'height=500,width=700,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLO');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_lo_traccia_$id_risorsa','','img/ico_lo_traccia_over.gif',1)\"><img src=\"img/ico_lo_traccia.gif\" width=\"20\" height=\"20\" alt=\"$stringa[traccia_lo]\" border=\"0\" name=\"img_lo_traccia_$id_risorsa\"></a></td>";

					

				} else {
					echo "<td align=center><img src=img/folder.gif width=18 height=16 alt=\"$stringa[cartella]\" border=0></td>";
					echo "<td><span class=testopiccolo><b>$titolo</b>  ($id_autore - $data_m) $descr_gruppo</span></td>";
					
					echo "<td align=center><a href=index.php?risorsa=repository_index&id_cartella=$id_risorsa title=\"$stringa[apri_cartella] $id_risorsa\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_risorsa','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" 			name=\"img_apri_$id_risorsa\"></a></td>";
					echo "<td>&nbsp;</td>";

				};
				break;
				
			case 201:
				$id_item=$id_gruppo;
				$query_p="SELECT * FROM lo_test_item WHERE id_item='$id_item'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$alternativo=$riga_p["alternativo"];
				
				$appr="";
				if ($alternativo=="on") $appr="&nbsp;<span class=testopiccolo>(a)</span>";	
				echo "<td align=center><img src=img/ico_test.gif width=20 height=20 border=0 alt=\"$stringa[verifica]\">$appr</td>";
				echo "<td><span class=testopiccolo><b>$titolo</b>  ($id_autore - $data_m)</span></td>";
				echo "<td align=center><a href=index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$id_padre title=\"$stringa[apri]\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_risorsa','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" 			name=\"img_apri_$id_risorsa\"></a></td>";
				echo "<td align=center><a href=\"javascript:;\" onclick=\"javascript:apri_scheda('sco_viewer.php?id_risorsa=$id_lo_padre&tipo=$tipo_lancio&url=$lo_url&launch_data=$id_risorsa','myRemoteLO',        'height=$height,width=$width,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=0,scrollbars=0,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLO');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_lo_lancia_$id_risorsa','','img/ico_lo_lancia_over.gif',1)\"><img src=\"img/ico_lo_lancia.gif\" width=\"20\" height=\"20\" alt=\"$stringa[lancia_lo]\" border=\"0\" name=\"img_lo_lancia_$id_risorsa\"></a></td>";
				break;

			case 200:
				$id_pagina=$id_gruppo;
				$query_p="SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$approfondimento=$riga_p["approfondimento"];
				$glossario=$riga_p["glossario"];
				$riepilogo=$riga_p["riepilogo"];
				$tipo_pagina=$riga_p["tipo_pagina"];
				$appr="";
				if ($approfondimento=="on") $appr="&nbsp;<span class=testopiccolo>(a)</span>";	
				if ($glossario=="on") $appr="&nbsp;<span class=testopiccolo>(g)</span>";	
				if ($riepilogo=="on") $appr="&nbsp;<span class=testopiccolo>(r)</span>";	
				
				
				echo "<td align=center><img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"$stringa[pagina_web]\">$appr</td>";
				echo "<td><span class=testopiccolo><b>$titolo</b>  ($id_autore - $data_m)</span></td>";
				if ($tipo_pagina<>"5") {
				echo "<td align=center><a href=index.php?risorsa=lo_pagina_asset_edit&id_pagina=$id_pagina&risorsa_padre=$id_padre title=\"$stringa[apri]\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_risorsa','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" 			name=\"img_apri_$id_risorsa\"></a></td>";
				} else {
				echo "<td align=center>&nbsp;</td>";
				};
				if ($approfondimento<>"on" and $glossario<>"on") {
				echo "<td align=center><a href=\"javascript:;\" onclick=\"javascript:apri_scheda('sco_viewer.php?id_risorsa=$id_lo_padre&tipo=$tipo_lancio&url=$lo_url&launch_data=$id_risorsa','myRemoteLO',        'height=$height,width=$width,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=0,scrollbars=0,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLO');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_lo_lancia_$id_risorsa','','img/ico_lo_lancia_over.gif',1)\"><img src=\"img/ico_lo_lancia.gif\" width=\"20\" height=\"20\" alt=\"$stringa[lancia_lo]\" border=\"0\" name=\"img_lo_lancia_$id_risorsa\"></a></td>";
				} else {
					echo "<td>&nbsp;</td>";
				}
				break;
					
		};
			echo "</td>";
		
			if ($editabile) {
				echo "<td align=center><a href=repository_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo&padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a></td>";
				
				echo "<td align=center><a href=index.php?risorsa=repository_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a></td>";

				echo "<td align=center><a href=\"javascript:;\" title=\"$stringa[materiale_storia]\" onclick=\"javascript:apri_scheda('materiali_storia.php?id_risorsa=$id_risorsa',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_chiletto_$id_risorsa','','img/ico_forum_chiletto_over.gif',1)\"><img src=\"img/ico_forum_chiletto.gif\" width=\"20\" height=\"20\" alt=\"$stringa[materiale_storia]\" border=\"0\" name=\"img_chiletto_$id_risorsa\"></a></td>";
				
				if ($tipo=='201') {
					echo "<td align=center><a href=lo_test_item_copia.php?id_item=$id_item&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_duplica_$id_item','','img/ico_duplicatest_over.gif',1)\"><img src=\"img/ico_duplicatest.gif\" width=\"20\" height=\"20\" alt=\"$stringa[aggiungi_feedback]\" border=\"0\" name=\"img_duplica_$id_item\"></a></td>";
				} else {
					if ($id_padre<>"root") 
						echo "<td></td>";
				};
				
			} else {
				echo "<td></td><td></td><td></td>";
			}
		
		
			echo "</tr>";
	
		
	
	
	}; 
	
echo "</table>\n";

echo "		
</td></tr>
</table>";

echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?risorsa=repository_index&pagina=$i&pag_size=$pag_size&id_cartella=$id_padre>$i</a>]
		";
	};
	$i++;
};
echo "</span><br>";	

};


function thread_risorse_filtro() {
	global $mysqli,$kairos_cookie,$stringa;
	global $titolo_cerca,$id_autore_cerca,$lo_tipo_lom_cerca,$materia_cerca;
	global $ruolo;
	global $colore_scuro,$colore_sfondo;
	global $editor_lo;
	
	$id_padre="root";
	$id_utente=$kairos_cookie["0"];
	$cod_area=$kairos_cookie["4"];
	
	$where_s="";
	if ($titolo_cerca) {
		$titolo_cerca = mysql_real_escape_string($titolo_cerca);
		$where_s.=" AND titolo like '$titolo_cerca%' ";
	};
	
	if ($id_autore_cerca) {
		$id_autore_cerca = mysql_real_escape_string($id_autore_cerca);
		$where_s.=" AND id_autore = '$id_autore_cerca'";
	};

	if ($editor_lo) {
		if ($ruolo=="admin" or $ruolo=="staff") {
			$query = "SELECT id_risorsa,risorsa_padre,id_autore,id_editor,id_editor_gruppo,titolo,tipo,file_size,DATE_FORMAT(data_crea,'%d/%m/%Y %H:%i') as data_m,id_gruppo,url FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo='20') $where_s ORDER BY posizione";

		} else {
			$query = "SELECT id_risorsa,risorsa_padre,id_autore,id_editor,id_editor_gruppo,titolo,tipo,file_size,DATE_FORMAT(data_crea,'%d/%m/%Y %H:%i') as data_m,id_gruppo,url FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (id_autore='$id_utente' OR id_editor='$id_utente' OR titolo='lo esempio') AND (tipo='20') $where_s ORDER BY posizione";
		};
		
		if ($id_padre<>"root") {
			$query = "SELECT id_risorsa,risorsa_padre,id_autore,id_editor,id_editor_gruppo,titolo,tipo,file_size,DATE_FORMAT(data_crea,'%d/%m/%Y %H:%i') as data_m,id_gruppo,url FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo='20') $where_s ORDER BY posizione";
		
		};
	};
	$result=$mysqli->query($query);
	//echo mysql_error()." ".$query;

	
	$righe=1;
	$continua = true;


	echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"100%\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";

	echo "<tr>";

	echo "<td width=10 align=center bgcolor=\"$colore_scuro\">";

	echo "<img src=img/ico_materiali_int.gif width=15 height=16 alt=\"$stringa[lo]\" border=0>";
	
	echo "</td>";


	echo "
<td colspan=5 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[titolo_lo_autore]</b></span></td>";
echo "
<td colspan=4 bgcolor=\"$colore_scuro\" align=center><span class=testonegativo><b>$stringa[azioni]</b></span></td>";
	


echo "</tr>\n";

	$colore=$colore_sfondo;
	
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
		$url = $risorsa["url"];
	
		$prendi=true;
	
		$where_s="id_lo='$id_risorsa'";
		if ($lo_tipo_lom_cerca) {
			if ($where_s) $where_s.=" AND ";
			$where_s.="lo_tipo_lom like '$lo_tipo_lom_cerca%'";
		};
	
		if ($materia_cerca) {
			if ($where_s) $where_s.=" AND ";
			$where_s.="materia like '$materia_cerca%'";
		};
	
		if ($where_s) {
			$query2="SELECT id_lo FROM lo WHERE $where_s LIMIT 1";
			$result2=$mysqli->query($query2);
			if (!$result2->num_rows) $prendi=false;
		};
	
		if ($prendi) {
		$editabile=false;
		if ($id_utente==$id_autore or $id_utente==$id_editor or $ruolo=='admin') {
			$editabile=true;
		};
	
		if (!$editabile) {
			$query_g="SELECT * FROM editor_gruppo_utenti WHERE id_utente='$id_utente' AND id_editor_gruppo='$id_editor_gruppo'";
			$result_g=$mysqli->query($query_g);
			$in_gruppo=$result_g->num_rows;
			if ($tipo==20 and $in_gruppo) $editabile=true;
			if ($tipo<>20) {
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
	
		echo "<tr bgcolor=\"$colore\">";
		
		echo "<td width=30>";
		if ($editabile) {
		echo "<a href=repository_sposta.php?id_risorsa=$id_risorsa&risorsa_padre=$id_padre&azione=up><img src=img/up.gif width=11 height=7 border=0 alt=\"$stringa[pagina_up]\"></a><a href=repository_sposta.php?id_risorsa=$id_risorsa&risorsa_padre=$id_padre&azione=down><img src=img/down.gif width=11 height=7 border=0 alt=\"$stringa[pagina_down]\"></a>";
		};
		echo "</td>";
		
		switch ($tipo) {
			case 20: //cartella - LO
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
			
				if ($id_padre=="root") {
					$query_lo="SELECT * FROM lo WHERE id_lo='$id_risorsa'";
					$result_lo=$mysqli->query($query_lo);
					$riga_lo=$result_lo->fetch_array();
					
					$lo_tipo=$riga_lo["lo_tipo"];
					$lo_url=$riga_lo["lo_url"];
					$width=$riga_lo["width"];
					$height=$riga_lo["height"];
						
					echo "<td><span class=testopiccolo><b>$titolo</b>  ($id_autore - $data_m) $descr_gruppo</span></td>";

					if ($lo_tipo=='1') {
						echo "<td align=center><a href=index.php?risorsa=repository_index&id_cartella=$id_risorsa title=\"$stringa[apri_cartella] $id_risorsa\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_risorsa','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" 			name=\"img_apri_$id_risorsa\"></a></td>";
						$nomarchio="";
						echo "<td align=center><a href=\"$lo_viewer_script?risorsa=$id_risorsa&esporta=1&nomarchio=$nomarchio\" title=\"esporta LO\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_esportalo_$id_risorsa','','img/ico_lo_export_over.gif',1)\"><img src=\"img/ico_lo_export.gif\" width=\"20\" height=\"20\" alt=\"esporta\" border=\"0\" name=\"img_esportalo_$id_risorsa\"></a></td>";

					} else {
						echo "<td>&nbsp;</td><td>&nbsp;</td>";
					};
					if ($lo_tipo=='1') { 
						$tipo_lancio="lo";
					} else {
						$tipo_lancio="url";
						$tipo=22;
					};
					
					echo "<td align=center><a href=\"javascript:;\" onclick=\"javascript:apri_scheda('sco_viewer.php?id_risorsa=$id_risorsa&tipo=$tipo_lancio&url=$lo_url','myRemoteLO',        'height=$height,width=$width,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=0,scrollbars=0,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLO');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_lo_lancia_$id_risorsa','','img/ico_lo_lancia_over.gif',1)\"><img src=\"img/ico_lo_lancia.gif\" width=\"20\" height=\"20\" alt=\"$stringa[lancia_lo]\" border=\"0\" name=\"img_lo_lancia_$id_risorsa\"></a></td>";
					if ($editabile) {
					echo "<td align=center><a href=\"javascript:;\" title=\"edit metadata\" onclick=\"javascript:apri_scheda('lom/index.php?id_lo=$id_risorsa',                   'myRemoteUtente',        'height=550,width=800,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_editlom_$id_risorsa','','img/ico_lom_over.gif',1)\"><img src=\"img/ico_lom.gif\" width=\"20\" height=\"20\" alt=\"edit metadata\" border=\"0\" name=\"img_editlom_$id_risorsa\"></a></td>";
					} else {
						echo "<td></td>";
					};
					echo "<td align=center><a href=\"javascript:;\" onclick=\"javascript:apri_scheda('lo_view_tracking.php?id_lo=$id_risorsa','myRemoteTLO',        'height=500,width=700,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLO');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_lo_traccia_$id_risorsa','','img/ico_lo_traccia_over.gif',1)\"><img src=\"img/ico_lo_traccia.gif\" width=\"20\" height=\"20\" alt=\"$stringa[traccia_lo]\" border=\"0\" name=\"img_lo_traccia_$id_risorsa\"></a></td>";

					

				} else {
					echo "<td align=center><img src=img/folder.gif width=18 height=16 alt=\"$stringa[cartella]\" border=0></td>";
					echo "<td><span class=testopiccolo><b>$titolo</b>  ($id_autore - $data_m) $descr_gruppo</span></td>";
					
					echo "<td align=center><a href=index.php?risorsa=repository_index&id_cartella=$id_risorsa title=\"$stringa[apri_cartella] $id_risorsa\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_risorsa','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" 			name=\"img_apri_$id_risorsa\"></a></td>";
					echo "<td>&nbsp;</td>";

				};
				break;
				
			
					
		};
			echo "</td>";
		
			if ($editabile) {
				echo "<td align=center><a href=repository_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo&padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_risorsa','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_risorsa\"></a></td>";
				
				echo "<td align=center><a href=index.php?risorsa=repository_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_risorsa','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_risorsa\"></a></td>";

				echo "<td align=center><a href=\"javascript:;\" title=\"$stringa[materiale_storia]\" onclick=\"javascript:apri_scheda('materiali_storia.php?id_risorsa=$id_risorsa',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_chiletto_$id_risorsa','','img/ico_forum_chiletto_over.gif',1)\"><img src=\"img/ico_forum_chiletto.gif\" width=\"20\" height=\"20\" alt=\"$stringa[materiale_storia]\" border=\"0\" name=\"img_chiletto_$id_risorsa\"></a></td>";
				if ($tipo=='201') {
					echo "<td align=center><a href=lo_test_item_copia.php?id_item=$id_item&risorsa_padre=$id_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_duplica_$id_item','','img/ico_duplicatest_over.gif',1)\"><img src=\"img/ico_duplicatest.gif\" width=\"20\" height=\"20\" alt=\"$stringa[aggiungi_feedback]\" border=\"0\" name=\"img_duplica_$id_item\"></a></td>";
				} else {
					if ($id_padre<>"root") 
						echo "<td></td>";
				};
			} else {
				echo "<td></td><td></td><td></td>";
			}
		
		
			echo "</tr>";
	
		
			};
	
	}; 
	
echo "</table>\n";

echo "		
</td></tr>
</table>";

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
		
		if ($tipo_figlio==200) {
			$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/$id_figlio.inc";
			if (file_exists($file_codice)) {
				unlink($file_codice);	
			};
		};

		if ($tipo_figlio==201) {
			$id_item=$riga["id_gruppo"];
			
			$query2 = "DELETE FROM lo_test_item WHERE id_item='$id_item'";
			$result2=$mysqli->query($query2);

			$query2 = "DELETE FROM lo_test_item_opzioni WHERE id_item='$id_item'";
			$result2=$mysqli->query($query2);

			$query2 = "DELETE FROM lo_test_item_dragdrop WHERE id_item='$id_item'";
			$result2=$mysqli->query($query2);

			$query2 = "DELETE FROM lo_test_commento WHERE id_item='$id_item'";
			$result2=$mysqli->query($query2);
		};

		if ($tipo_figlio==20) {
			cancella_contenuto($id_figlio);
		};
		
		$query2 = "DELETE FROM risorse_materiali WHERE id_risorsa='$id_figlio'";
		$result2=$mysqli->query($query2);		
		
		$query2 = "DELETE FROM materiali_storia WHERE id_risorsa='$id_figlio'";
		$result2=$mysqli->query($query2);
		
		
		$query2 = "UPDATE lo_pagina SET alternativo_di='' WHERE alternativo_di='$id_figlio'";
		$result2=$mysqli->query($query2);

		$query2 = "UPDATE lo_pagina SET id_alternativo='' WHERE id_alternativo='$id_figlio'";
		$result2=$mysqli->query($query2);
		
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
		return path_cartella($id_cartella_sup)."/"."<a href=index.php?risorsa=repository_index&id_cartella=$id_cartella>$titolo</a>";
	};
};

function path_cartella_link($id_cartella) {
	global 	$DBHOST, $DBASE,$DBUSER,$DBPWD;
	global $tipo_browse;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
	if ($id_cartella=="root") {
		return "";
	} else {
		$query="select titolo,risorsa_padre FROM risorse_materiali WHERE id_risorsa='$id_cartella'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$titolo=$riga[titolo];
		$id_cartella_sup=$riga["risorsa_padre"];
		return path_cartella_link($id_cartella_sup)."/"."<a href=index.php?risorsa=repository_cartella&id_cartella=$id_cartella&tipo_browse=$tipo_browse>$titolo</a>";
	};
};

function browse_folder($id_padre) {
	global $DBHOST,$DBASE,$DBUSER,$DBPWD,$kairos_cookie,$stringa;
	global $colore_scuro,$colore_sfondo;
	global $tipo_browse;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$id_utente=$kairos_cookie["0"];
	$cod_area=$kairos_cookie["4"];
	
	if ($tipo_browse<>"link_test") {
		$query = "SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo='20' or tipo='200' or tipo='201') ORDER BY posizione";
	} else {
		$query = "SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo='201') ORDER BY posizione";
	};
	$result=$mysqli->query($query);


	$result=$mysqli->query($query);

	$path_cartella=path_cartella_link($id_padre);
	

	echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"100%\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";

	echo "<tr>";

	echo "
<td colspan=3 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[contenuto_cartella]: $path_cartella</b></span></td>";

echo "</tr>\n";

	$colore=$colore_sfondo;
	
	while ($risorsa=$result->fetch_array()) {
		$id_risorsa = $risorsa["id_risorsa"];
		$id_gruppo = $risorsa["id_gruppo"];
		$id_cartella_sup=$risorsa["risorsa_padre"];
		$tipo=$risorsa["tipo"];
		$titolo=$risorsa["titolo"];
		$url = $risorsa["url"];
	
			
				
		switch ($tipo) {
			case 20: //cartella - LO
				$evidenzia_gruppo=true;
				$descr_gruppo="";
				echo "<tr bgcolor=\"$colore\">";
				echo "<td align=center><img src=img/folder.gif width=18 height=16 alt=\"$stringa[cartella]\" border=0></td>";
				echo "<td><span class=testopiccolo><b>$titolo</b></span></td>";
					
				echo "<td align=center><a href=index.php?risorsa=repository_cartella&id_cartella=$id_risorsa&tipo_browse=$tipo_browse title=\"$stringa[apri_cartella]\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_risorsa','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" 			name=\"img_apri_$id_risorsa\"></a></td>";
				
				echo "</tr>";
				break;
				
			
			case 200:
				$id_pagina=$id_gruppo;
				$query_p="SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$approfondimento=$riga_p["approfondimento"];
				$riepilogo=$riga_p["riepilogo"];
				$glossario=$riga_p["glossario"];
				
				$tipo_link="interno";
				$appr="";
				if ($approfondimento=="on") {
					$appr="&nbsp;<span class=testopiccolo>(a)</span>";	
					$tipo_link="approfondimento";
				};
				
				if ($glossario=="on") {
					$appr="&nbsp;<span class=testopiccolo>(g)</span>";	
					$tipo_link="glossario";
				};
				
				$str_titolo=addslashes($titolo);
				if (($tipo_browse<>"link_tutoriale" and $tipo_browse<>"link_tutoriale_post" and $tipo_browse<>"link_tutoriale_ref") or (!$approfondimento and !$glossario and !$riepilogo)) {
				echo "<tr bgcolor=\"$colore\">";
				echo "<td align=center><img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"$stringa[pagina_web]\">$appr</td>";
				echo "<td><span class=testopiccolo><b>$titolo</b></span></td>";
				if ($tipo_browse<>"link_tutoriale" and $tipo_browse<>"link_tutoriale_post" and $tipo_browse<>"link_tutoriale_ref") {
					echo "<td align=center><span class=testopiccolo>[<a href=\"javascript:;\" onclick=\"assegna_id_lo('$id_risorsa','$tipo_link','$str_titolo')\">$stringa[inserisci]</a>]</a></td>";
				} else {
					switch ($tipo_browse) {
					case "link_tutoriale":
						echo "<td align=center><span class=testopiccolo>[<a href=\"javascript:;\" onclick=\"assegna_id_lo_lnktut('$id_risorsa','$str_titolo')\">$stringa[inserisci]</a>]</a></td>";
						break;
					case "link_tutoriale_post": 
						echo "<td align=center><span class=testopiccolo>[<a href=\"javascript:;\" onclick=\"assegna_id_lo_lnktutpost('$id_risorsa','$str_titolo')\">$stringa[inserisci]</a>]</a></td>";
						break;
					case "link_tutoriale_ref": 
						echo "<td align=center><span class=testopiccolo>[<a href=\"javascript:;\" onclick=\"assegna_id_lo_lnktutref('$id_risorsa','$str_titolo')\">$stringa[inserisci]</a>]</a></td>";
						break;
					};
				};
				echo "</tr>";
				};
				break;
			
			case 201:
				$id_item=$id_gruppo;
				$query_p="SELECT * FROM lo_test_item WHERE id_item='$id_item'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$alternativo=$riga_p["alternativo"];
				$titolo=$riga_p["titolo"];
				$str_titolo=addslashes($titolo);
				if (!$tipo_browse) {
					if (!$alternativo) {
						echo "<tr bgcolor=\"$colore\">";
						echo "<td align=center><img src=img/ico_test.gif width=20 height=20 border=0 alt=\"$stringa[pagina_web]\"></td>";
						echo "<td><span class=testopiccolo><b>$titolo</b></span></td>";
						echo "<td align=center><span class=testopiccolo>[<a href=\"javascript:;\" onclick=\"assegna_id_lo('$id_risorsa','$tipo_link','$str_titolo')\">$stringa[inserisci]</a>]</a></td>";
						echo "</tr>";
					};
				};
				
				if ($tipo_browse=="link_test") {
				if ($alternativo) {
				echo "<tr bgcolor=\"$colore\">";
				echo "<td align=center><img src=img/ico_test.gif width=20 height=20 border=0 alt=\"$stringa[pagina_web]\"></td>";
				echo "<td><span class=testopiccolo><b>$titolo</b></span></td>";
				echo "<td align=center><span class=testopiccolo>[<a href=\"javascript:;\" onclick=\"assegna_id_lo_lnktest('$id_risorsa','$str_titolo')\">$stringa[inserisci]</a>]</a></td>";
				echo "</tr>";
				};
				};
				break;
					
		};
		
			
	
	
	}; 
	
echo "</table>\n";

echo "		
</td></tr>
</table>";

};


?>

<?php
echo "<ul style=\"list-style-type:none;margin-left:5px\">\n";
while ($risorsa = $result->fetch_array()) {
	$id_risorsa = $risorsa["id_risorsa"];
	$tipo_risorsa=$risorsa["tipo_risorsa"];

 	switch ($tipo_risorsa) {
	
	/*
			case 0://pagina web
				$query2 = "SELECT id_risorsa,id_autore,titolo,descrizione,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
				$result2=$mysqli->query($query2);
				$risorsa2=$result2->fetch_array();
				$id_autore=$risorsa2["id_autore"];
				$titolo=$risorsa2["titolo"];
				$descrizione=$risorsa2["descrizione"];
				$file_size=$risorsa2["file_size"];
				$tipo = $risorsa2["tipo"];
				$data_m = $risorsa2["data_m"];
	
				echo "<li>\n";
				echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0> <span class=testo><a href=materiali_browse.php?risorsa=$id_risorsa  title=\"$titolo\">$titolo</a></span><br>\n";	
				echo "</li><br>\n";
				break;
			
			case 4://alias pagina web
				$query2 = "SELECT id_risorsa,id_autore,descrizione,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m,id_gruppo FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
				$result2=$mysqli->query($query2);
				$risorsa2=$result2->fetch_array();
				
				$id_autore=$risorsa2["id_autore"];
				$id_gruppo=$risorsa2["id_gruppo"];
				$descrizione=$risorsa2["descrizione"];
				$file_size=$risorsa2["file_size"];
				$tipo = $risorsa2["tipo"];
				$data_m = $risorsa2["data_m"];
				
				$query2 = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
				$result2=$mysqli->query($query2);
				$risorsa2=$result2->fetch_array();
				$titolo=$risorsa2["titolo"];
				
				echo "<li>\n";
				echo "
			<img src=img/pagina_web_link.gif width=16 height=16 border=0> <span class=testo><a href=materiali_browse.php?risorsa=$id_risorsa  title=\"$titolo\">$titolo</a></span><br>\n";	
				echo "</li><br>\n";
				break;	

			case 1://file
				$query2 = "SELECT id_risorsa,id_autore,titolo,descrizione,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
				$result2=$mysqli->query($query2);
				$risorsa2=$result2->fetch_array();
				$id_autore=$risorsa2["id_autore"];
				$titolo=$risorsa2["titolo"];
				$descrizione=$risorsa2["descrizione"];
				$file_size=$risorsa2["file_size"];
				$tipo = $risorsa2["tipo"];
				$data_m = $risorsa2["data_m"];
				
				$icona="file.gif";			
				$est = substr($titolo,-3);
				$tipi_file = array ("zip","exe","xls","doc","pdf","rtf","jpg","gif","mid","mp3",
							"wav","avi","htm","txt","mpg","bmp","ppt");
				if (in_array($est,$tipi_file)) {
					$icona=$est.".gif";
				}; 
				
				echo "<li>\n";
				echo "
			<img src=img/".$icona." width=16 height=16 border=0> <span class=testo> <a href=materiali_browse.php?risorsa=$id_risorsa title=\"$titolo\">$titolo -  ".stringa_filesize($file_size)."</a><br>
$descrizione</span><br>\n";	
				echo "</li><br>\n";
				break;
*/

			case 2://cartella
				$query2 = "SELECT id_risorsa,id_autore,titolo,descrizione,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
				$result2=$mysqli->query($query2);
				$risorsa2=$result2->fetch_array();
				$id_autore=$risorsa2["id_autore"];
				$titolo=$risorsa2["titolo"];
				$descrizione=$risorsa2["descrizione"];
				$file_size=$risorsa2["file_size"];
				$tipo = $risorsa2["tipo"];
				$data_m = $risorsa2["data_m"];
				$cap0="cap0_".$id_risorsa;
				$cap1="cap1_".$id_risorsa;
				$immagine="img/forum/piu.gif";
				
				if (!$win_ie and !$opera) {
					$id_risorsa0=foglia($id_risorsa);
					if (!$id_risorsa0) $id_risorsa0=$id_risorsa;
				};
					
				echo "<li>\n";
				if ($win_ie or $opera) {
				echo "
				<div id=$cap0 onClick=\"mostra_capitolo(this,'$cap1')\" style=\"cursor:hand\"><img src=\"img/ico_materiali.gif\" width=\"24\" height=\"19\" alt=\"\" border=\"0\" align=middle>";
				} else {
				echo "
				<div id=$cap0><img src=\"img/ico_materiali.gif\" width=\"24\" height=\"19\" alt=\"\" border=\"0\" align=middle>";
				};
				
				if ($win_ie or $opera) {
				echo "<img name=img_".$cap1." src=\"$immagine\" width=\"11\" height=\"11\" alt=\"\" border=\"0\">\n";
				} else {
					echo "&nbsp;";
				};
				
				if ($win_ie or $opera) {
					echo "<span class=testo><a href=\"javascript:;\" >$titolo</a></span>";
 				} else {
					echo "<span class=testo><a href=materiali_browse.php?risorsa=$id_risorsa0 title=\"$titolo\">$titolo</a></span>";
				};
				
				if ($win_ie or $opera) {
					$display="None";
				} else {
					$display="Visible";
				};
				
				if ($win_ie or $opera) {
	 				echo "<div id=$cap1 style=\"Display:$display\" onClick=\"window.event.cancelBubble=true\">\n";
				} else {
					echo "<div id=$cap1 style=\"Display:$display\">\n";
				}
	 			
				if ($win_ie or $opera) {
				capitolo($id_risorsa,"");
				}; 
	 			echo "</div></div>\n";
		
				echo "</li><br>\n";
				//};
				break;
				
			case 3://test
				$query2 = "SELECT id_test,titolo FROM test WHERE id_test='$id_risorsa'";
				$result2=$mysqli->query($query2);
				$risorsa2=$result2->fetch_array();
				$id_test=$risorsa2["id_test"];
				$titolo=$risorsa2["titolo"];
				$punteggio_soglia=$risorsa2["punteggio_soglia"];
				echo "<li>\n";
				
				$tag_icona="";
				if ($ruolo<>'staff' and $ruolo<>'admin') {
					$icona=verifica_test($id_utente,$id_test,$id_corso_s,$id_edizione_s);
					if ($icona) {
						$tag_icona="<img src=\"img/forum/$icona.gif\" width=15 height=15>";
					};
				};
				
				echo "
			<img src=\"img/ico_questionario.gif\" width=\"19\" height=\"18\" alt=\"\" border=\"0\" align=middle>&nbsp;&nbsp;<span class=testo><a href=index.php?risorsa=test_compila_form&id_test=$id_test title=\"$titolo\">$titolo</a></span> $tag_icona";
				if ($ruolo=="staff" or $ruolo=="admin") {
					echo "&nbsp;<span class=testo>[<a href=index.php?risorsa=test_risultati&id_test=$id_test>Risultati</a>]</span><br>\n";
				} else {
					echo "<br>";
				};
				echo "</li><br>\n";
				break;
				
				case 20://LO
				$query2 = "SELECT id_risorsa,id_autore,titolo,descrizione,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
				$result2=$mysqli->query($query2);
				$risorsa2=$result2->fetch_array();
				$id_autore=$risorsa2["id_autore"];
				$titolo=$risorsa2["titolo"];
				$descrizione=$risorsa2["descrizione"];
				
				$query_lo="SELECT * FROM lo WHERE id_lo='$id_risorsa'";
				$result_lo=$mysqli->query($query_lo);
				$riga_lo=$result_lo->fetch_array();
					
				$lo_tipo=$riga_lo["lo_tipo"];
				$lo_url=$riga_lo["lo_url"];
				$width=$riga_lo["width"];
				$height=$riga_lo["height"];
				
				$query_lo="SELECT * FROM scorm_scoes_track WHERE scoid='$id_risorsa' AND userid='$kairos_cookie[0]' AND element='cmi.core.lesson_status'";
				$result_lo=$mysqli->query($query_lo);
				$riga_lo=$result_lo->fetch_array();
				$stato_lo=$riga_lo["value"];
				$icona_stato="ico_lo_dacompletare.gif";
				if (!$riga_lo or $stato_lo=='not attempted') $icona_stato="ico_lo_maiaperto.gif";
				if ($stato_lo=='incomplete') $icona_stato="ico_lo_dacompletare.gif";
				if ($stato_lo=='completed' or $stato_lo=='passed' or $stato_lo=='failed') $icona_stato="ico_lo_completato.gif";

				echo "<li>\n";
				echo "<img src=\"img/ico_materiali.gif\" width=\"24\" height=\"19\" alt=\"\" border=\"0\" align=middle>";
								
				echo "&nbsp;";
				
				echo "<img src=\"img/$icona_stato\" width=\"17\" height=\"15\" alt=\"$stato_lo\" border=\"0\" align=middle>";
								
				echo "&nbsp;";
				
				if ($lo_tipo=='1') { 
					$tipo_lancio="lo";
				} else {
					$tipo_lancio="url";
					$tipo=22;
				};
					
				echo "<a href=\"javascript:;\" onclick=\"javascript:apri_scheda('sco_viewer.php?id_risorsa=$id_risorsa&tipo=$tipo_lancio&url=$lo_url','myRemoteLO',        'height=$height,width=$width,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=0,scrollbars=0,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLO');\"><span class=testo>$titolo</span></a>";

				echo "</li><br>\n";
				
				break;
				
				
				
		};
	
};
echo "</ul>\n";
?>

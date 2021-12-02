<?php
include_once 'init_sito.inc';

function max_score($id_risorsa) {
	global $db,$DBASE;
	global $max_score;
	
	mysql_select_db($DBASE,$db);	
	$query="SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_risorsa' AND (tipo='201' or tipo='20') ORDER BY posizione";
	$result=$mysqli->query($query);
	
	while ($riga=$result->fetch_array()) {
		$id_risorsa=$riga["id_risorsa"];
		$titolo=$riga["titolo"];
		$tipo_risorsa=$riga["tipo"];

		switch ($tipo_risorsa) {
			case '20':
				max_score($id_risorsa);
				break;
			
			case '201':
				$id_item=$riga["id_gruppo"];
				$query_o="SELECT * FROM lo_test_item WHERE id_item='$id_item'";
				$result_o=$mysqli->query($query_o);
				$item=$result_o->fetch_array();
				$alternativo=$item[alternativo];
				if (!$alternativo) $max_score += $item["peso"];
				break;
				
		};
	};
}

function tipo_pagina($id_padre) {
	global $i_pag,$i_appr;
	global $db;
	global $DBASE;
	global $pagina_finale;
	global $tipotutoriale;
	global $nometutoriale;
	
	mysql_select_db($DBASE,$db);	
	$query="SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo='200' or tipo='201' or tipo='20') ORDER BY posizione";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_risorsa=$riga["id_risorsa"];
		$titolo=$riga["titolo"];
		$tipo_risorsa=$riga["tipo"];
		$id_pagina=$riga["id_gruppo"];
		
		switch ($tipo_risorsa) {
			case '20':
				tipo_pagina($id_risorsa);
				break;
			
			case '200':
				$id_pagina=$riga["id_gruppo"];
				$query_p="SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$approfondimento=$riga_p["approfondimento"];
				if ($approfondimento<>"on") {
					$tipotutoriale[$i_pag]=1;
					$nometutoriale[$i_pag]=$id_risorsa;
					$i_pag++;
				} else {
					//echo "appr_id[$i_appr]='$id_pagina';\n";
					$i_appr++;
				};
				break;
				
			case '201':
				$nometutoriale[$i_pag]=$id_risorsa;
				$tipotutoriale[$i_pag]=2;
				$i_pag++;
				break;
		};
		
	};	
};

function array_lo($id_padre) {
	global $i_pag,$i_appr;
	global $db;
	global $DBASE;
	global $pagina_finale;
	
	mysql_select_db($DBASE,$db);	
	$query="SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo='200' or tipo='201' or tipo='20') ORDER BY posizione";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_risorsa=$riga["id_risorsa"];
		$titolo=$riga["titolo"];
		$tipo_risorsa=$riga["tipo"];
		$id_pagina=$riga["id_gruppo"];
		
		switch ($tipo_risorsa) {
			case '20':
				tipo_pagina($id_risorsa);
				break;
			
			case '200':
				$id_pagina=$riga["id_gruppo"];
				$query_p="SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$approfondimento=$riga_p["approfondimento"];
				if ($approfondimento<>"on") {
					$tipotutoriale[$i_pag]=1;
					echo "nometutoriale[$i_pag]='$id_risorsa';\n";
					echo "numerotutoriale[\"$id_risorsa\"]=$i_pag;\n";
					if ($i_pag==1) {
						echo "tipotutoriale[\"$id_risorsa\"]=3;\n";
					} else {
						if ($i_pag<>$pagina_finale) {
							echo "tipotutoriale[\"$id_risorsa\"]=1;\n";
						} else {
							echo "tipotutoriale[\"$id_risorsa\"]=4;\n"; 
						};
					};
					$i_pag++;
				} else {
					echo "nomeapprofondimento[$i_appr]='$id_risorsa';\n";
					$i_appr++;
				};
				break;
				
			case '201':
				echo "nometutoriale[$i_pag]='$id_risorsa';\n";
				echo "numerotutoriale[\"$id_risorsa\"]=$i_pag;\n";
				echo "tipotutoriale[\"$id_risorsa\"]=2;\n";
				$id_item=$riga["id_gruppo"];
				$query_p="SELECT * FROM lo_test_item WHERE id_item='$id_item'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$alternativo=$riga_p["alternativo"];
				$punteggio=$riga_p["peso"];
				if (!$alternativo) {
					echo "puntitutoriale[\"$id_risorsa\"]=$punteggio;\n";
				};
				
				$id_alternativo=$riga_p["id_alternativo"];
				if ($id_alternativo) {
					echo "tutorialealternativo[\"$id_risorsa\"] = \"$id_alternativo\";\n";
					echo "tutorialeprincipale[\"$id_alternativo\"] = \"$id_risorsa\";\n";
				};
				
				$i_pag++;
				break;
		};
		
	};	
};

function tot_pagine($cartella) {
	global $db;
	global $cod_area,$DBASE;
	global $tot_pagine;
	global $pagina_finale;
	
	mysql_select_db($DBASE,$db);
	$query_r="SELECT * FROM risorse_materiali WHERE (tipo='200' or tipo='201') AND risorsa_padre='$cartella' ORDER BY posizione";
	$result_r=$mysqli->query($query_r);
	while ($riga_r=$result_r->fetch_array()) {
		if ($riga_r["tipo"]=='200') {
			$id_pagina=$riga_r["id_gruppo"];
			$query_p="SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
			$result_p=$mysqli->query($query_p);
			$riga_p=$result_p->fetch_array();
			$approfondimento=$riga_p["approfondimento"];
			$riepilogo=$riga_p["riepilogo"];
			if ($approfondimento<>"on") $tot_pagine++;
			if ($riepilogo=="on" and !$pagina_finale) $pagina_finale=$tot_pagine;
		} else {
			$tot_pagine++;
		};
	};
	
	$query="SELECT * FROM risorse_materiali WHERE risorsa_padre='$cartella' AND tipo='20' ORDER BY posizione";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_risorsa=$riga["id_risorsa"];
		tot_pagine($id_risorsa);
	};
			
	
};

function get_tutoriale_id($id_pagina,$tipopagina=1) {
	global $blocco_id;
	global $tipotutoriale;
	
	$blocco_link=0;
	for ($i=1;$i<=count($blocco_id);$i++) {
		if ($blocco_id[$i]==$id_pagina) {
			if ($tipotutoriale[$i]==$tipopagina) $blocco_link=$i;
		};
	};
	
	return $blocco_link;

};


/* ------------------------------------------------------------------------------------------------------ */
function genera_pagina($id_cartella) {
	global $db;
	global $cod_area,$DBASE;
	global $n_pagina,$n_item,$n_appr,$tot_pagine;
	global $path_img;
	global $drag_item;
	global $colore_scuro;
	global $d,$p;
	global $PATH_ROOT_FILE;
	global $pagina_finale;
	global $nometutoriale;
	
	mysql_select_db($DBASE,$db);	
	$query="SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_cartella' AND (tipo='200' or tipo='201' or tipo='20') ORDER BY posizione";
	$result=$mysqli->query($query);
	
	while ($riga=$result->fetch_array()) {
		
		$id_risorsa=$riga["id_risorsa"];
		$titolo=$riga["titolo"];
		$tipo_risorsa=$riga["tipo"];
		$id_pagina=$riga["id_gruppo"];
		$pos_pagina=$riga["posizione"];
		$approfondimento="";
		
		switch ($tipo_risorsa) {
			case '20':
				genera_pagina($id_risorsa);
				break;
			
			/***********  GENERA PAGINA TUTORIALE / APPROFONDIMENTO  *******************/	
			case '200':
				$contenuto="";
				$audio=false;
				$query_p="SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				
				$tipo_pagina=$riga_p["tipo_pagina"];
				$approfondimento=$riga_p["approfondimento"];
				
				switch ($tipo_pagina) {
					case "1": //solo testo (con audio opzionale)
						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='1' AND id_pagina='$id_pagina'";
						$result_p=$mysqli->query($query_p);

						$riga_p=$result_p->fetch_array();
						$id_pagina_asset=$riga_p["id_pagina_asset"];
						
			$file_asset=$PATH_ROOT_FILE."materiali/$cod_area/asset_".$id_pagina."_".$id_pagina_asset.".inc";
						if (file_exists($file_asset)) {
							$testo = implode('',file($file_asset));
						} else {
							$testo ="";
						};
						$testo=brhtml(parse_kairos($testo));
						
						$contenuto=$testo;
						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='5' AND id_pagina='$id_pagina'";
						$result_p=$mysqli->query($query_p);
						$riga_p=$result_p->fetch_array();
						if ($riga_p) {
							 $file_audio=$riga_p["file_asset"];
							 $audio=true;
						};
						break;
					
					case "2": //solo immagine (con audio opzionale)
						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='2' AND id_pagina='$id_pagina' ORDER BY posizione_int LIMIT 1";
						$result_p=$mysqli->query($query_p);
						$riga_p=$result_p->fetch_array();
					
						$file_immagine=$riga_p["file_asset"];
						$alt_text=htmlentities($riga_p["alt_text"]);
						list($width, $height, $type, $attr) = getimagesize($file_immagine);
						
						if ($width>550) {
							$height=floor(($height)*550/$width);
							$width=550;
						};
									
						if ($height>350) {
							$width=floor(($width)*350/$height);
							$height=350;
						};
								
												
						$contenuto="<img class=\"immaginesx\" src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\">\n";

						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='5' AND id_pagina='$id_pagina'";
						$result_p=$mysqli->query($query_p);
						$riga_p=$result_p->fetch_array();
						if ($riga_p) {
							 $file_audio=$riga_p["file_asset"];
							 $audio=true;
						};
						
						break;
						
					case "3": //solo video 
						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='3' AND id_pagina='$id_pagina' ORDER BY posizione_int LIMIT 1";
						$result_p=$mysqli->query($query_p);
						$riga_p=$result_p->fetch_array();
					
						$file_video=$riga_p["file_asset"];
						$alt_text=htmlentities($riga_p["alt_text"]);
						$alt_img=htmlentities($riga_p["alt_img"]);
						list($width, $height, $type, $attr) = getimagesize($alt_img);
						if ($width>250) {
							$height=floor(($height)*250/$width);
							$width=250;
						};
									
						if ($height>300) {
							$width=floor(($width)*300/$height);
							$height=300;
						};
						$est = strtolower(substr($file_video,-3));
						$videot="video";
						switch($est) {
							case "wmv": 
								$videot="videowm";
								break;
								
							case "mov":
								$videot="videoqt";
								break;
							
							case "rpm":	
								$videot="videorp";
								break;
									
						};
						$n_p=$n_pagina+1;
						$contenuto="<p class=\"nascosto\">$alt_text\n
						<p>
						<script type=\"text/javascript\">\n";
						$contenuto.="caricamedia(\"$file_video\",\"$id_risorsa\",\"sx\",\"$alt_img\",\"$alt_text\");\n";

						$contenuto.= "</script><p>\n";					 
						
						break;
					
					case "4": //solo flash 
						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='4' AND id_pagina='$id_pagina' ORDER BY posizione_int LIMIT 1";
						$result_p=$mysqli->query($query_p);
						$riga_p=$result_p->fetch_array();
					
						$file_flash=$riga_p["file_asset"];
						$alt_text=htmlentities($riga_p["alt_text"]);
						$alt_img=htmlentities($riga_p["alt_img"]);
						list($width, $height, $type, $attr) = getimagesize($alt_img);
						if ($width>650) {
							$height=floor(($height)*650/$width);
							$width=650;
						};
									
						if ($height>380) {
							$width=floor(($width)*380/$height);
							$height=380;
						};
						
						$n_p=$n_pagina+1;
						$contenuto="<p class=\"nascosto\">$alt_text
						<p>
						<script type=\"text/javascript\">";
						$contenuto.="caricamedia(\"$file_flash\",\"$id_risorsa\",\"2\",\"$alt_img\",\"$alt_text\");";

						$contenuto.= "</script><p>";					 
						
						break;
						
					case "12": //testo e immagine (con audio opzionale)
						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='1' AND id_pagina='$id_pagina'";
						$result_p=$mysqli->query($query_p);

						$riga_p=$result_p->fetch_array();
						$id_pagina_asset=$riga_p["id_pagina_asset"];
			$file_asset=$PATH_ROOT_FILE."materiali/$cod_area/asset_".$id_pagina."_".$id_pagina_asset.".inc";
						if (file_exists($file_asset)) {
							$testo = implode('',file($file_asset));
						} else {
							$testo ="";
						};
						$testo=brhtml(parse_kairos($testo));
						
						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='2' AND id_pagina='$id_pagina' ORDER BY posizione_int LIMIT 1";
						$result_p=$mysqli->query($query_p);
						$riga_p=$result_p->fetch_array();
						$posizione_base=$riga_p["posizione"];
						
						switch ($posizione_base) {
								case "1"://colonna a destra multiplo
									$colonna="";
									$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='2' AND id_pagina='$id_pagina' ORDER BY posizione_int";
									$result_p=$mysqli->query($query_p);
									while ($riga_p=$result_p->fetch_array()) {
										$file_immagine=$riga_p["file_asset"];
										$alt_text=htmlentities($riga_p["alt_text"]);
										list($width, $height, $type, $attr) = getimagesize($file_immagine);
										if ($width>200) {
											$height=floor(($height)*200/$width);
											$width=200;
										};
										
										if ($height>320) {
											$width=floor(($width)*320/$height);
											$height=320;
										};
										$colonna.="<img src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\"><br><br>\n";
									};
									$contenuto="
									<div class=\"tutorialecolonna1sx\">\n
									$testo\n
									</div>\n
									<div class=\"tutorialecolonna2dx\">\n
									$colonna\n
									</div>\n";
									
									break;
							
								case "2"://colonna a sinistra multiplo
									$colonna="";
									$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='2' AND id_pagina='$id_pagina' ORDER BY posizione_int";
									$result_p=$mysqli->query($query_p);
									while ($riga_p=$result_p->fetch_array()) {
										$file_immagine=$riga_p["file_asset"];
										$alt_text=htmlentities($riga_p["alt_text"]);
										list($width, $height, $type, $attr) = getimagesize($file_immagine);
										if ($width>250) {
											$height=floor(($height)*250/$width);
											$width=250;
										};
										
										if ($height>320) {
											$width=floor(($width)*320/$height);
											$height=320;
										};
										
										$colonna.="<img src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\"><br><br>\n";
									};
									$contenuto="
									<div class=\"tutorialecolonna1dx\">\n
									$testo\n
									</div>\n
									<div class=\"tutorialecolonna2sx\">\n
									$colonna\n
									</div>\n";
									
									break;
								
								case "3"://img a destra
									$file_immagine=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									list($width, $height, $type, $attr) = getimagesize($file_immagine);
									if ($width>350) {
										$height=floor(($height)*350/$width);
										$width=350;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
															
									//$contenuto="<img src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\" align=\"right\" hspace=\"10\" vspace=\"10\">&nbsp;$testo";
									
									$contenuto="<img class=\"immaginedx\" src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\">&nbsp;$testo\n";

									break;
									
								case "4"://img a sinistra
									$file_immagine=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									list($width, $height, $type, $attr) = getimagesize($file_immagine);
									if ($width>350) {
										$height=floor(($height)*350/$width);
										$width=350;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
													
									$contenuto="<img class=\"immaginesx\" src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\">&nbsp;$testo\n";
									
									break;
									
								case "5"://img colonna a destra
									$file_immagine=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									list($width, $height, $type, $attr) = getimagesize($file_immagine);
									if ($width>200) {
										$height=floor(($height)*200/$width);
										$width=200;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
																		
									$colonna="<img src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\">\n";
									$contenuto="
									<div class=\"tutorialecolonna1sx\">\n
									$testo\n
									</div>\n
									<div class=\"tutorialecolonna2dx\">\n
									$colonna\n
									</div>\n";
									
							
									
									
									break;
									
								case "6"://img colonna a sinistra
									$file_immagine=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									list($width, $height, $type, $attr) = getimagesize($file_immagine);
									if ($width>250) {
										$height=floor(($height)*250/$width);
										$width=250;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
																		
									$colonna="<img src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\">\n";
									$contenuto="
									<div class=\"tutorialecolonna1dx\">\n
									$testo\n
									</div>\n
									<div class=\"tutorialecolonna2sx\">\n
									$colonna\n
									</div>\n";
									
									break;
								
								case "7"://img colonna grande a destra
									$file_immagine=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									list($width, $height, $type, $attr) = getimagesize($file_immagine);
									if ($width>200) {
										$height=floor(($height)*200/$width);
										$width=200;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
																		
									$colonna="<img src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\">\n";
									$contenuto="
									<div class=\"tutorialecolonna1sx\">\n
									$testo\n
									</div>\n
									<div class=\"tutorialecolonna2dx\">\n
									$colonna\n
									</div>\n";
									
									break;
									
								case "8"://img colonna grande a sinistra
									$file_immagine=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									list($width, $height, $type, $attr) = getimagesize($file_immagine);
									if ($width>250) {
										$height=floor(($height)*250/$width);
										$width=250;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
																		
									$colonna="<img src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\">\n";
									$contenuto="
									<div class=\"tutorialecolonna1dx\">\n
									$testo\n
									</div>\n
									<div class=\"tutorialecolonna2sx\">\n
									$colonna\n
									</div>\n";
									
									break;
								
								case "9"://img sopra
									$file_immagine=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									list($width, $height, $type, $attr) = getimagesize($file_immagine);
									if ($width>450) {
										$height=floor(($height)*450/$width);
										$width=450;
									};
									
									if ($height>200) {
										$width=floor(($width)*200/$height);
										$height=200;
									};
									
									$contenuto="
									<div class=\"tutorialeblocco1su\">\n
									<img src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\">\n
									</div>\n
									<div class=\"tutorialeblocco2giu\">\n
									$testo\n
									</div>\n";
															
									
									
									break;
									
								case "10"://img sotto
									$file_immagine=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									list($width, $height, $type, $attr) = getimagesize($file_immagine);
									if ($width>450) {
										$height=floor(($height)*450/$width);
										$width=450;
									};
									
									if ($height>200) {
										$width=floor(($width)*200/$height);
										$height=200;
									};
													
									$contenuto="
									<div class=\"tutorialeblocco1giu\">\n
									<img src=\"$file_immagine\" width=\"$width\" height=\"$height\" alt=\"$alt_text\">\n
									</div>\n
									<div class=\"tutorialeblocco2su\">\n
									$testo\n
									</div>\n";
									
									break;
						};
						
						
						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='5' AND id_pagina='$id_pagina'";
						$result_p=$mysqli->query($query_p);
						$riga_p=$result_p->fetch_array();
						if ($riga_p) {
							 $file_audio=$riga_p["file_asset"];
							 $audio=true;
						};
						break;
				
					case "13": //testo e video 
						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='1' AND id_pagina='$id_pagina'";
						$result_p=$mysqli->query($query_p);

						$riga_p=$result_p->fetch_array();
						$id_pagina_asset=$riga_p["id_pagina_asset"];
			$file_asset=$PATH_ROOT_FILE."materiali/$cod_area/asset_".$id_pagina."_".$id_pagina_asset.".inc";
						if (file_exists($file_asset)) {
							$testo = implode('',file($file_asset));
						} else {
							$testo ="";
						};
						$testo=brhtml(parse_kairos($testo));
						
						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='3' AND id_pagina='$id_pagina' ORDER BY posizione_int LIMIT 1";
						$result_p=$mysqli->query($query_p);
						$riga_p=$result_p->fetch_array();
						$posizione_base=$riga_p["posizione"];
						
						switch ($posizione_base) {
								case "3"://video a destra
									$file_video=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									$alt_img=htmlentities($riga_p["alt_img"]);
									list($width, $height, $type, $attr) = getimagesize($alt_img);
									if ($width>250) {
										$height=floor(($height)*250/$width);
										$width=250;
									};
									
									if ($height>300) {
										$width=floor(($width)*300/$height);
										$height=300;
									};
									$est = strtolower(substr($file_video,-3));
									$videot="video";
									switch($est) {
										case "wmv": 
											$videot="videowm";
											break;
								
										case "mov":
											$videot="videoqt";
											break;
							
										case "rpm":	
											$videot="videorp";
											break;
									
									};
									$n_p=$n_pagina+1;
									$contenuto="<p class=\"nascosto\">$alt_text\n
									<p>
						<script type=\"text/javascript\">\n";
									$contenuto.="caricamedia(\"$file_video\",\"$id_risorsa\",\"dx\",\"$alt_img\",\"$alt_text\");\n";

									$contenuto.= "</script>\n<p>$testo\n";	
									break;
									
								case "4"://video a sinistra
									$file_video=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									$alt_img=htmlentities($riga_p["alt_img"]);
									list($width, $height, $type, $attr) = getimagesize($alt_img);
									if ($width>250) {
										$height=floor(($height)*250/$width);
										$width=250;
									};
									
									if ($height>300) {
										$width=floor(($width)*300/$height);
										$height=300;
									};
									$est = strtolower(substr($file_video,-3));
									$videot="video";
									switch($est) {
										case "wmv": 
											$videot="videowm";
											break;
								
										case "mov":
											$videot="videoqt";
											break;
							
										case "rpm":	
											$videot="videorp";
											break;
									
									};
									$n_p=$n_pagina+1;
									$contenuto="<p class=\"nascosto\">$alt_text
									<p>
						<script type=\"text/javascript\">";
									$contenuto.="caricamedia(\"$file_video\",\"$id_risorsa\",\"sx\",\"$alt_img\",\"$alt_text\");\n";

									$contenuto.= "</script>\n<p>$testo\n";	
									break;
						};
						break;
								
					case "14": //testo e flash 
							$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='1' AND id_pagina='$id_pagina'";
							$result_p=$mysqli->query($query_p);

							$riga_p=$result_p->fetch_array();
							$id_pagina_asset=$riga_p["id_pagina_asset"];
			$file_asset=$PATH_ROOT_FILE."materiali/$cod_area/asset_".$id_pagina."_".$id_pagina_asset.".inc";
							if (file_exists($file_asset)) {
								$testo = implode('',file($file_asset));
							} else {
								$testo ="";
							};
							$testo=brhtml(parse_kairos($testo));
						
							$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='4' AND id_pagina='$id_pagina' ORDER BY posizione_int LIMIT 1";
							$result_p=$mysqli->query($query_p);
							$riga_p=$result_p->fetch_array();
							$posizione_base=$riga_p["posizione"];
						
							switch ($posizione_base) {
								case "3"://flash a destra
									$file_flash=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									$alt_img=htmlentities($riga_p["alt_img"]);
									list($width, $height, $type, $attr) = getimagesize($alt_img);
									if ($width>350) {
										$height=floor(($height)*350/$width);
										$width=350;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
						
									$n_p=$n_pagina+1;
									$contenuto="<p class=\"nascosto\">$alt_text\n
									<p>
									<script type=\"text/javascript\">\n";
						$contenuto.="caricamedia(\"$file_flash\",\"$id_risorsa\",\"2dx\",\"$alt_img\",\"$alt_text\");\n";

									$contenuto.= "</script>\n<p>$testo\n";	
									break;
							
								case "4"://flash a sinistra
									$file_flash=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									$alt_img=htmlentities($riga_p["alt_img"]);
									list($width, $height, $type, $attr) = getimagesize($alt_img);
									if ($width>350) {
										$height=floor(($height)*350/$width);
										$width=350;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
						
									$n_p=$n_pagina+1;
									$contenuto="<p class=\"nascosto\">$alt_text
									<p>
									<script type=\"text/javascript\">";
						$contenuto.="caricamedia(\"$file_flash\",\"$id_risorsa\",\"2sx\",\"$alt_img\",\"$alt_text\");\n";

									$contenuto.= "</script>\n<p>$testo\n";	
									break;
						};
							
						
						break;
						
				};
				
				if ($approfondimento<>"on") {
				
					$n_pag_prev=$n_pagina;
					$n_pagina++;
					$n_pag_next=$n_pagina+1;
					$id_pag_prev=$nometutoriale[$n_pag_prev];
					$id_pag_next=$nometutoriale[$n_pag_next];
					
					echo "<div id=\"".$id_risorsa."\" class=\"contenutotutoriale\">\n
<p><a name=\"".$id_risorsa."_a\"></a>\n
<h1>$titolo</h1>\n
<script type=\"text/javascript\">\n
   visualizzapagina('$id_risorsa');\n
";

					if ($audio) {
						echo "caricamedia(\"$file_audio\",\"$id_risorsa\");\n";
					};
				
					echo "
</script>\n
<div class=\"testotutoriale\">\n
$contenuto\n
<p>\n
</div>\n
<p>\n
<script type=\"text/javascript\">
	comandi(\"$id_risorsa\");\n
</script>";
					if ($n_pag_prev and $n_pagina<=$pagina_finale) {
						echo "<a href=\"#".$id_pag_prev."_a\" accesskey=\"i\" tabindex=\"20\"  onClick=\"tutoriale('$id_pag_prev');return false;\">\n
   <img class=\"pulsanteindietro\" onMouseOver=\"roll(this,'indietro')\" onMouseOut=\"noroll(this,'indietro')\" src=\"shell/$path_img/pulsante_indietro.gif\" alt=\"Indietro\">\n
</a>\n";
					};

					if ($n_pagina<$tot_pagine and $n_pagina<$pagina_finale) {
						echo "<a href=\"#".$id_pag_next."\" accesskey=\"a\" tabindex=\"30\"  onClick=\"tutoriale('$id_pag_next');return false;\">\n
   <img class=\"pulsanteavanti\" onMouseOver=\"roll(this,'avanti')\" onMouseOut=\"noroll(this,'avanti')\" src=\"shell/$path_img/pulsante_avanti.gif\" alt=\"Avanti\">\n
</a>\n";
					};

					echo "</div>\n";
				
				} else {
					$n_appr++;
					
					echo "<div id=\"".$id_risorsa."\" class=\"contenutoapprofondimento\">\n
<p><a name=\"".$id_risorsa."_a\"></a>\n
<div class=\"logoapprofondimentogenerico\"></div>\n
<div class=\"testoapprofondimentogenerico\">\n
<h1>$titolo</h1>\n
<div class=\"testoapprofondimento\">\n
$contenuto\n
</div>\n
</div>\n
<p>
   <span class=\"nascosto\">Principali funzioni:</span>
   <a href=\"#\" accesskey=\"t\" tabindex=\"100\" onClick=\"ritorna();return false;\" onKeyPress=\"ritorna();return false;\">
      <img class=\"pulsantetorna\" onMouseOver=\"roll(this,'torna')\" onMouseOut=\"noroll(this,'torna')\" 
 src=\"shell/$path_img/pulsante_torna.gif\" alt=\"Torna dall'approfondimento\">
   </a>
   <span class=\"nascosto\">Fine dell'approfondimento. Per riascoltarlo torna al titolo.</span>
</div>
					";
					
				};
	
				break;
			/* -------------------------------------------------------------------------- */
			
			/***********  GENERA PAGINA TEST *******************/	
			case '201': 
				$n_p=$n_pagina+1;
				
				$contenuto_form="";
				$contenuto_script="<script type=\"text/javascript\">\n
   visualizzapagina(\"$id_risorsa\");\n";
				
				
				$id_item=$riga["id_gruppo"];
				$query_i = "SELECT * FROM lo_test_item WHERE id_item='$id_item'";
				$result_i=$mysqli->query($query_i);
				
				$item=$result_i->fetch_array();
				
				$tipo_item = $item["tipo_item"];
				$max_risposte = $item["max_risposte"];
				$titolo_item = parse_kairos($item["titolo"]);
				$mostra_titolo_item=($item[mostra_titolo]);
				$domanda_item = trim(parse_kairos($item["domanda"]));
				$peso=$item[peso];
				$msg_ok=$item[msg_ok];
				$msg_ko=$item[msg_ko];
				$link_tutoriale=$item[link_tutoriale];
				$link_tutoriale_post=$item[link_tutoriale_post];
				$alternativo=$item[alternativo];
				
				$tuttest0=($link_tutoriale);
				$tuttest1=($link_tutoriale_post);
				
				switch($tipo_item) {
					case "1":
					$test_tipo="1";
					// scelta multipla risposta singola
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n
					var risposta".$n_p." = new Array;\n";
					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">\n
        			<fieldset>\n
					<legend class=\"domanda\">\n";
					if ($mostra_titolo_item) 
						$contenuto_form.= "$titolo_item";
					
					if ($domanda_item)
						$contenuto_form.= "<br><br>$domanda_item\n";
				
					$contenuto_form.="</legend>\n";
					
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$n_opzione=1;
					$rispostagiusta=0;
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					while($opzione=$result2->fetch_array()) {
						$risposta_opzione=(htmlentities($opzione[risposta_opzione]));
						$risposta_opzione_p=parse_kairos($opzione[risposta_opzione]);
						$punt_opzione=$opzione[punteggio];
						if ($punt_opzione<>"0.00" and !$rispostagiusta) {
							$contenuto_script.="risposta".$n_p."[$n_opzione] = 1;\n";
						} else {
							$contenuto_script.="tutorialetest".$n_p."[$n_opzione] = \"$tuttest1\";\n";
						};
						$contenuto_form.= "<input type=\"radio\" tabindex=\"$n_opzione\" name=\"test_".$id_risorsa."\" id=\"test".$n_opzione."_".$id_risorsa."\"><label for=\"test".$n_opzione."_".$id_risorsa."\">$risposta_opzione_p</label><br>\n";
						$n_opzione++;
					};
					$contenuto_form.="</fieldset>\n</form>\n";
					$contenuto_script.="</script>\n";					
					
					break;
			
					case "2":
					// scelta multipla risposta multipla
					$test_tipo="2";
				
					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";
					if ($max_risposte>0) {
						$contenuto_form.= "<span id=\"item_".$n_p."\">\n";
					};
					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">
        			<fieldset>
					<legend class=\"domanda\">";
					if ($mostra_titolo_item) 
						$contenuto_form.= "$titolo_item";
					
					if ($domanda_item)
						$contenuto_form.= "<br><br>$domanda_item\n";
				
					$contenuto_form.="</legend>\n";
					
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$n_opzione=1;
					$rispostagiusta=0;
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					while($opzione=$result2->fetch_array()) {
						$risposta_opzione=(htmlentities($opzione[risposta_opzione]));
						$risposta_opzione_p=parse_kairos($opzione[risposta_opzione]);
						$punt_opzione=$opzione[punteggio];
						$punti=0;
						if ($punt_opzione<>"0.00") $punti=1;
						$contenuto_script.="risposta".$n_p."[$n_opzione] = $punti;\n";
						$contenuto_script.="tutorialetest".$n_p."[$n_opzione] = \"$tuttest1\";\n";
						
						if ($max_risposte>0) {
							$contenuto_form.= "<input type=\"checkbox\" tabindex=\"$n_opzione\" d=\"test".$n_opzione."_".$id_risorsa."\" onclick=\"update_check('item_".$n_p."','$id_risorsa','$max_risposte')\"><label for=\"test".$n_opzione."_".$id_risorsa."\">$risposta_opzione_p</label><br>\n";
						} else {
							$contenuto_form.= "<input type=\"checkbox\" tabindex=\"$n_opzione\" d=\"test".$n_opzione."_".$id_risorsa."\"><label for=\"test".$n_opzione."_".$id_risorsa."\">$risposta_opzione_p</label><br>\n";
						};					
						$n_opzione++;
					};
					$contenuto_form.="</fieldset></form>\n";
					$contenuto_script.="</script>\n";	
					if ($max_risposte>0) {
						$contenuto_form.= "</span>\n";
					};
					break;
				
					case "3":
					// vero/falso
					$test_tipo="1";
				
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n
					var risposta".$n_p." = new Array;\n";
					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">\n
        			<fieldset>
					<legend class=\"domanda\">\n";
					if ($mostra_titolo_item) 
						$contenuto_form.= "$titolo_item\n";
					
					if ($domanda_item)
						$contenuto_form.= "<br><br>$domanda_item\n";
				
					$contenuto_form.="</legend>\n";
					
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$n_opzione=1;
					$rispostagiusta=0;
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					while($opzione=$result2->fetch_array()) {
						$risposta_opzione=(htmlentities($opzione[risposta_opzione]));
						$risposta_opzione_p=parse_kairos($opzione[risposta_opzione]);
						$punt_opzione=$opzione[punteggio];
						if ($punt_opzione<>"0.00" and !$rispostagiusta) {
							$contenuto_script.="risposta".$n_p."[$n_opzione] = 1;\n";
						} else {
							$contenuto_script.="tutorialetest".$n_p."[$n_opzione] = \"$tuttest1\";\n";
						};
						$contenuto_form.= "<input type=\"radio\" tabindex=\"$n_opzione\" name=\"test_".$id_risorsa."\" id=\"test".$n_opzione."_".$id_risorsa."\"><label for=\"test".$n_opzione."_".$id_risorsa."\">$risposta_opzione_p</label><br>\n";
						$n_opzione++;
					};
					$contenuto_form.="</fieldset></form>";
					$contenuto_script.="</script>";		
					break;
					
					
					case "4":
					// fill-in
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item'";
					$result2=$mysqli->query($query2);
					$num_spazi=$result2->num_rows;
					
					$test_tipo="3";

					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";

					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">\n
        			<fieldset>
					<legend class=\"domanda\">";
					if ($mostra_titolo_item) 
						$contenuto_form.= "$titolo_item\n";
				
					$contenuto_form.="</legend>\n";
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$nspazio=0;
					$domanda_item1="<label for=\"test".$nspazio."_".$id_risorsa."\">";
					for ($i=0;$i<strlen($domanda_item);$i++) {
						$char=substr($domanda_item,$i,1);
						if ($char=="[" and substr($domanda_item,$i+1,1)=="*" and substr($domanda_item,$i+2,1)=="]") {
							$nspazio++;
							$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND posizione='$nspazio'";
							$result2=$mysqli->query($query2);
							$opzione=$result2->fetch_array();
							$risposte_lista=($opzione[risposte_lista]);
							$risposta_giusta=($opzione[risposta_giusta]);
							$case_sensitive=($opzione[case_sensitive]);
							$lc=strlen($risposta_giusta)+5;
							$contenuto_script.="risposta".$n_p."[$nspazio] = \"$risposta_giusta\";\n";
							$contenuto_script.="tutorialetest".$n_p."[$nspazio] = \"$tuttest1\";\n";
							
							if (!$risposte_lista) {
								$domanda_item1.="<input type=\"text\" tabindex=\"$nspazio\" size=\"$lc\" id=\"test".$nspazio."_".$id_risorsa."\"></label>";
							} else {
								$opt="<option value=\"0\" selected></option>";
								$opt_list=split("\n",$risposte_lista);
								for ($k=0;$k<count($opt_list);$k++) {
									if (trim($opt_list[$k])) {
										$opt_list[$k]=trim((($opt_list[$k])));
										$opt.="<option value=\"$opt_list[$k]\">$opt_list[$k]";
								 	};
								};
							
								$domanda_item1.="<select tabindex=\"$nspazio\"  size=\"1\" id=\"test".$nspazio."_".$id_risorsa."\">$opt</select></label>";
							};
							$i=$i+2;
							if ($nspazio<$num_spazi) $domanda_item1.="<label>";
						} else {
							$domanda_item1.=$char;
						};
					};	
					$contenuto_form.=$domanda_item1;
					$contenuto_form.="</fieldset></form>";
					$contenuto_script.="</script>";	
	
					break;
			
					case "5":
					// match
					
					$test_tipo="5";

					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";

					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">\n
        			<fieldset>
					<legend class=\"domanda\">";
					if ($mostra_titolo_item) 
						$contenuto_form.= "$titolo_item";
				
					$contenuto_form.="</legend>";
					
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND tipo_opzione='2' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					$opt_dx="<option value=\"0\" selected>(seleziona)</option>";
					while ($opzione=$result2->fetch_array()) {
						$risposta_opzione=($opzione[risposta_opzione]);
						$id_opz=$opzione[id_item_opzione];
						$opt_dx.="<option value=\"$id_opz\">$risposta_opzione";
					};
					
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND tipo_opzione='1' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$p=1;
					while ($opzione=$result2->fetch_array()) {
						$risposta_opzione=($opzione[risposta_opzione]);
						$risposta_opzione_p=parse_kairos($opzione[risposta_opzione]);
						$id_item_esatto=$opzione[id_item_esatto];
						$contenuto_script.="risposta".$n_p."[$p] = $id_item_esatto;\n";
						$contenuto_script.="tutorialetest".$n_p."[$p] = \"$tuttest1\";\n";
							
						$contenuto_form.= "<label for=\"test".$p."_".$id_risorsa."\">$risposta_opzione_p &nbsp;<select tabindex=\"$p\" size=\"1\" id=\"test".$p."_".$id_risorsa."\">$opt_dx</select></label><p>";
						$p++;
					};
					
					$contenuto_form.="</fieldset></form>";
					$contenuto_script.="</script>";		
					break;
				
					case "6":
					// domanda aperta
					
					$test_tipo="3";

					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";

					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">\n
        			<fieldset>
					<legend class=\"domanda\">";
					if ($mostra_titolo_item) 
						$contenuto_form.= "$titolo_item";
				
					$contenuto_form.="</legend>";
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item'";
					$result2=$mysqli->query($query2);
					$opzione=$result2->fetch_array();
					$nome_aperta = "aperta_".$n_p;
					$limite_caratteri=$opzione[limite_caratteri];
					$risposta_giusta=$opzione[risposta_giusta];
					$contenuto_script.="risposta".$n_p."[1] = \"$risposta_giusta\";\n";
					$contenuto_script.="tutorialetest".$n_p."[1] = \"$tuttest1\";\n";

					if ($limite_caratteri>0) {
						$pbar="progressbar_".$n_p;
						$contenuto_form.= "<label for=\"test1_".$id_risorsa."\"><textarea id=\"test1_".$id_risorsa."\" name=\"test1_".$id_risorsa."\"  tabindex=\"1\" rows=\"3\" cols=\"50\" onKeyDown=\"textCounter(this,'$pbar',$limite_caratteri)\" 
onKeyUp=\"textCounter(this,'$pbar',$limite_caratteri)\" 
onFocus=\"textCounter(this,'$pbar',$limite_caratteri)\" ></textarea></label>\n<br />

<div id=\"$pbar\" class=\"progress\"></div>

<script>textCounter(document.getElementById(\"test1_".$id_risorsa."\"),\"$pbar\",$limite_caratteri)</script>

";
					} else {
						$contenuto_form.= "<label for=\"test1_".$id_risorsa."\"><textarea id=\"test1_".$id_risorsa."\" tabindex=\"1\" rows=\"3\" cols=\"50\"></textarea></label>\n";
					};
					$contenuto_form.="</fieldset></form>\n";
					$contenuto_script.="</script>\n";		
					break;
				
					case "7":
					//dragdrop
					$test_tipo=6;
					$id_pagina=1000+$id_item;
					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="risposta".$n_p."[1] = 0;\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest1\";\n";
					$contenuto_script.="tutorialetest".$n_p."[1] = \"$tuttest1\";\n";
					$contenuto_script.="</script>";	
					
					$query2="SELECT * FROM lo_pagina_asset WHERE id_pagina='$id_pagina'";
					$result2=$mysqli->query($query2);

					$riga2=$result2->fetch_array();

					$file_flash="";
					$alt_text="";
					$alt_img="";
					if ($riga2) {
						$file_flash=$riga2["file_asset"];
						$alt_text=htmlentities($riga2["alt_text"]);
						$alt_img=$riga2["alt_img"];
					};
					list($width, $height, $type, $attr) = getimagesize($alt_img);
					$contenuto_script.="<p class=\"nascosto\">
         L'animazione prevede un test da effettuare trascinando gli oggetti sullo schermo. Per accedere automaticamente alla pagina alternativa, ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ necessario disabilitare in precedenza i componenti multimediali.";
					$contenuto_form.="<script type=\"text/javascript\">
     caricamedia(\"".$file_flash."\",\"".$id_risorsa."\",\"2\",\"$alt_img\",\"$alt_text\");\n
      </script><p class=\"domandadd\">$titolo_item\n";
					break;
					
				
		};

$n_pag_prev=$n_pagina;
$n_pagina++;
$n_pag_next=$n_pagina+1;
$id_pag_prev=$nometutoriale[$n_pag_prev];
$id_pag_next=$nometutoriale[$n_pag_next];
					

/*
if ($alternativo) {
	$query2="SELECT * FROM lo_test_item WHERE id_alternativo='$id_item'";
	$result2=$mysqli->query($query2);
	$riga2=$result2->fetch_array();
	$id_item0=$riga2["id_item"];
	
	$query2="SELECT * FROM risorse_materiali WHERE id_gruppo='$id_item0'";
	$result2=$mysqli->query($query2);
	$riga2=$result2->fetch_array();
	$id_risorsa=$riga2["id_risorsa"];
	$pos_risorsa=$riga2["posizione"];
	
	$query2="SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_cartella' AND (tipo='200' or tipo='201') AND 		posizione>'$pos_risorsa' ORDER BY posizione";
	$result2=$mysqli->query($query2);
	$riga2=$result2->fetch_array();
	if ($riga2) {
		if ($riga2["tipo"]=="200") {
			$n_pag_next=get_tutoriale_id($riga2["id_gruppo"],1);	
		} else {
			$n_pag_next=get_tutoriale_id($riga2["id_gruppo"],2);	
		};
	};
};
*/				
echo "
<div id=\"$id_risorsa\" class=\"contenutotutoriale\">\n
<p><a name=\"".$id_risorsa."_a\"></a>\n
<div class=\"testata_v\"></div>\n
<h1>Test</h1>\n
$contenuto_script\n";

if ($tipo_item<>"7") {
	echo "<div class=\"testotest\">\n";
} else {
	echo "<div class=\"testotestdd\">\n";
};
if ($tipo_item<>"7") {
	echo"<div class=\"risposta\">\n";
};
echo "$contenuto_form";
if ($tipo_item<>"7") {
	echo"</div>\n";
};
echo "</div>\n
<p>\n";



echo "<script type=\"text/javascript\">\n";
if (trim($msg_ok)) {
	echo "messaggiotest[0]=\"$msg_ok\";\n";
} else {
	echo "messaggiotest[0]=\"messaggiotest_default[0]\";\n";
};

if (trim($msg_ko)) {
	echo "messaggiotest[1]=\"$msg_ko\";\n";
} else {
	echo "messaggiotest[1]=\"messaggiotest_default[0]\";\n";
};
echo " comandi(\"$id_risorsa\",$test_tipo,\"risposta".$n_p."\",\"tutorialetest".$n_p."\",\"$id_pag_next\",\"messaggiotest\");\n
   </script>\n
   <noscript>\n
      <p>\n
      <a href=\"#".$id_pag_next."_a\" accesskey=\"a\" tabindex=\"210\">\n
         <img class=\"pulsanteavanti\" src=\"shell/$path_img/pulsante_avanti.gif\" alt=\"Avanti\">\n
      </a>\n
   </noscript>\n
 ";

/*
if ($tipo_item<>"7" ){
echo "<a href=\"#\" accesskey=\"v\" tabindex=\"10\"  onClick=\"verificatest($test_tipo,$n_pagina,risposta".$n_pagina.",$peso);return false\" onKeyPress=\"verificatest($test_tipo,$n_pagina,risposta".$n_pagina.",$peso);return false\">
      <img class=\"pulsanteverifica\" id=\"verifica".$n_pagina."\" onMouseOver=\"roll(this,'verifica')\" onMouseOut=\"noroll(this,'verifica')\" src=\"shell/$path_img/pulsante_verifica.gif\" alt=\"Verifica la risposta\">
   </a>";
};
echo "
   <a href=\"#tutoriale".$n_pagina."_a\" accesskey=\"s\" tabindex=\"20\" onClick=\"studio($n_pagina,$tuttest0,tutorialetest".$n_pagina.");return false\" onKeyPress=\"studio($n_pagina,$tuttest0,tutorialetest".$n_pagina.");return false\">
      <img class=\"pulsantestudio\" id=\"studio".$n_pagina."\" onMouseOver=\"roll(this,'studio')\" onMouseOut=\"noroll(this,'studio')\"  src=\"shell/$path_img/pulsante_studio.gif\" alt=\"Studia\">
   </a>

";
		
if ($n_pagina<=$tot_pagine) {
	if ($tipo_item<>"7") {
		$id_alt=0;
		$query2="SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_cartella' AND (tipo='200' or tipo='201') AND 		posizione>'$pos_pagina' ORDER BY posizione";
		$result2=$mysqli->query($query2);
		if ($result2->num_rows) {
			$riga2=$result2->fetch_array();
			$tipo_risorsa=$riga2["tipo"];
			if ($tipo_risorsa=="201") {
				$id_item=$riga2["id_gruppo"];
				$query_i = "SELECT * FROM lo_test_item WHERE id_item='$id_item'";
				$result_i=$mysqli->query($query_i);
				
				$item=$result_i->fetch_array();
				$id_alternativo=$item[id_alternativo];
				if ($id_alternativo) $id_alt=get_tutoriale_id($id_alternativo,2);
			};
		};	
		if (!$id_alt) {
			echo "
<p>
   <a href=\"#tutoriale".$n_pag_next."_a\" accesskey=\"a\" tabindex=\"30\"  onClick=\"avantitest($n_pagina,$n_pag_next);return false;\" onKeyPress=\"avantitest($n_pagina,$n_pag_next);return false;\">
      <img class=\"pulsanteavanti\" id=\"avanti".$n_pagina."\" onMouseOver=\"roll(this,'avanti')\" onMouseOut=\"this,noroll('avanti')\" src=\"shell/$path_img/pulsante_avanti.gif\" alt=\"Avanti\">
   </a>";
		} else {
			echo "
<p>
   <a href=\"#tutoriale".$n_pag_next."_a\" accesskey=\"a\" tabindex=\"30\" onClick=\"avantitest($n_pagina,$n_pag_next,$id_alt);return false;\" onKeyPress=\"avantitest($n_pagina,$n_pag_next,$id_alt);return false;\">
      <img class=\"pulsanteavanti\" id=\"avanti".$n_pagina."\" onMouseOver=\"roll(this,'avanti')\" onMouseOut=\"noroll(this,'avanti')\" src=\"shell/$path_img/pulsante_avanti.gif\" alt=\"Avanti\">
   </a>";
		};
   
	} else {
		echo "
<p>
   <a href=\"#tutoriale".$n_pag_next."_a\" accesskey=\"a\" tabindex=\"30\"  onClick=\"tutoriale($n_pag_next);return false;\" onKeyPress=\"tutoriale($n_pag_next);return false;\">
      <img class=\"pulsanteavanti\" id=\"avanti".$n_pagina."\" onMouseOver=\"roll(this,'avanti')\" onMouseOut=\"noroll(this,'avanti')\" src=\"shell/$path_img/pulsante_avanti.gif\" alt=\"Avanti\">
   </a>";
	}; 
} 
*/

echo "
</div>\n";
				
			
				break;
		};
	};

};


function indice($cartella) {
	global $db;
	global $cod_area,$DBASE;
	global $i_pag;
	global $path_img;
	global $format;
	
	mysql_select_db($DBASE,$db);
	$query_r="SELECT * FROM risorse_materiali WHERE (tipo='200' or tipo='201' or tipo='20') AND risorsa_padre='$cartella' ORDER BY posizione";
	$result_r=$mysqli->query($query_r);
	while ($riga_r=$result_r->fetch_array()) {
		$tipo=$riga_r["tipo"];
		$id_risorsa=$riga_r["id_risorsa"];
		$titolo_pag=trim($riga_r["titolo"]);
		if (!$titolo_pag) $titolo_pag="senza titolo";
		
		if ($tipo=="20") {
			indice($id_risorsa);
		} else {
			if ($tipo=="200") {
				$id_pagina=$riga_r["id_gruppo"];
				$query_p="SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$approfondimento=$riga_p["approfondimento"];
			
				if ($approfondimento<>"on") {
					$i_pag++;
					if ($format=="a") { 
						echo "<div id=\"sommarioriga_".$id_risorsa."\" class=\"rigabox\">
      				<a href=\"#".$id_risorsa."_a\" class=\"sommario1\" onClick=\"ritornatutoriale('$id_risorsa');return false\" onKeyPress=\"ritornatutoriale('$id_risorsa');return false\">$i_pag $titolo_pag</a>
      				<img id=\"sommarioimm_".$id_risorsa."\" class=\"sommarioimm\" src=\"shell/$path_img/vuoto.gif\" alt=\"\">
  					 </div>";
					} else {
						echo "<div id=\"sommarioriga_".$id_risorsa."\" class=\"rigabox\">
     				 <span class=\"sommario1\">$i_pag $titolo_pag</span>
      				<img id=\"sommarioimm_".$id_risorsa."\" class=\"sommarioimm\" src=\"shell/$path_img/vuoto.gif\" alt=\"\">
  					 </div>";
					};
				};
			} else {
				$i_pag++;
				echo "<div id=\"sommarioriga_".$id_risorsa."\" class=\"rigabox\">
     				 <span class=\"sommario1\">$i_pag $titolo_pag</span>
      				<img id=\"sommarioimm_".$id_risorsa."\" class=\"sommarioimm\" src=\"shell/$path_img/vuoto.gif\" alt=\"\">
  					 </div>";
					 
			};
		};
	};
	
};

function visualizza_home($id_risorsa) {
	global $db;
	global $cod_area,$DBASE;
	global $path_img;
	global $titolo_corso;
	
	mysql_select_db($DBASE,$db);
	$query="SELECT * FROM lo WHERE id_lo='$id_risorsa'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();

	$materia=brhtml(nl2br(htmlentities($riga["materia"])));
	$lo_tipo_lom=brhtml(nl2br(htmlentities($riga["lo_tipo_lom"])));
	$fruitore=brhtml(nl2br(htmlentities($riga["fruitore"])));
	$obiettivi=brhtml(nl2br(htmlentities($riga["obiettivi"])));
	$argomenti=brhtml(nl2br(htmlentities($riga["argomenti"])));
	$profilo_ingresso=brhtml(nl2br(htmlentities($riga["profilo_ingresso"])));
	$file_audio=$riga["file_audio"];
	
	echo "<h1>$titolo_corso</h1>
<script type=\"text/javascript\">
   comunicaplugin();";
   if ($file_audio) {
   		echo "caricamedia(\"$file_audio\",\"homepage\");";
	};
	echo "
</script>
<noscript>
   <p class=\"comunicazioni\">
      Attenzione: per sfruttare le funzioni avanzate del corso ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ necessario abilitare Javascript sul browser.
</noscript>
<div class=\"testohome\">
<p>
<hr class=\"linea\">
<img class=\"immaginepresentazione\" src=\"shell/$path_img/icona_tipolo.gif\" alt=\"\">
<div class=\"presentazione\">
<strong>Tipo Learning Object</strong><br>
$lo_tipo_lom<br>
</div>
<hr class=\"linea\">
<img class=\"immaginepresentazione\" src=\"shell/$path_img/icona_materie.gif\" alt=\"\">
<div class=\"presentazione\">
<strong>Materia</strong><br>
$materia
</div>
<hr class=\"linea\">
<img class=\"immaginepresentazione\" src=\"shell/$path_img/icona_argomenti.gif\" alt=\"\">
<div class=\"presentazione\">
<strong>Argomenti</strong><br>
$argomenti
</div>
<hr class=\"linea\">
<img class=\"immaginepresentazione\" src=\"shell/$path_img/icona_obiettivi.gif\" alt=\"\">
<div class=\"presentazione\">
<strong>Obiettivi</strong><br>
$obiettivi
</div>
<hr class=\"linea\">
<img class=\"immaginepresentazione\" src=\"shell/$path_img/icona_prerequisiti.gif\" alt=\"\">
<div class=\"presentazione\">
<strong>Prerequisiti</strong><br>
$profilo_ingresso
</div>";

};

function brhtml($stringa) {
	return str_replace("<br />","<br>",$stringa);
};

?>

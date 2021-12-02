<?php

include_once 'init_sito.inc';

function parse_img($testo) {
//isolo il tag img e lo restituisco

$tag_img="";
$pos=strpos($testo,"<img");
if (!($pos===false)) {
	if (!strpos($testo,".png")) {
		$tag_img="";
		$i=0;
		$char=substr($testo,$pos+$i,1);
		while ($char<>">") {
			$i++;
			$tag_img.=$char;
			$char=substr($testo,$pos+$i,1);
		};
		$tag_img.=$char;
	};
};

return $tag_img;

}

function pulisci_img($testo) {

$testo=str_replace("<p>","",$testo);
$testo=str_replace("</p>","",$testo);
$testo=str_replace("<P>","",$testo);
$testo=str_replace("</P>","",$testo);

$tag_img=parse_img($testo);
$testo=str_replace($tag_img,"",$testo);

return $testo;

}

function marchio($nome,$lo_skin) {
$nome=trim($nome);

$im = imagecreatefrompng("shell/marchiatura/fondino.png");

$fontsize=11;
$fontangle=90;


$text_nome=$nome;

//$font = "FreeSerifBoldItalic.ttf";
$font = "shell/marchiatura//TSCu_Comic.ttf";

$imgcoord=imagettfbbox ( $fontsize, $fontangle, $font, $text_nome );
$dimX=abs($imgcoord[4]-$imgcoord[2]);
$dimY=abs($imgcoord[7]-$imgcoord[5]);
$partdaX=15+$dimX+intval((20.5-$dimX)/2);
$partdaY=$dimY+intval((238-$dimY)/2);

$text_lic = "LEARNING OBJECT DI";
$imgcoord_lic=imagettfbbox ($fontsize, $fontangle, $font, $text_lic );
$dim_lic_X=abs($imgcoord_lic[4]-$imgcoord_lic[2]);
$dim_lic_Y=abs($imgcoord_lic[7]-$imgcoord_lic[5]);
$partda_lic_X=$dim_lic_X+intval((20.5-$dim_lic_X)/2);
$partda_lic_Y=$dim_lic_Y+intval((238-$dim_lic_Y)/2);

$black = imagecolorallocate($im, 0, 0, 0);

imagettftext($im, $fontsize, $fontangle, $partda_lic_X, $partda_lic_Y, $black, $font, $text_lic);
imagettftext($im, $fontsize, $fontangle, $partdaX, $partdaY, $black, $font, $text_nome);


imagepng($im,"shell/skins/$lo_skin/marchio.png");
imagedestroy($im);

}


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

function get_next_alt($id_risorsa) {
	global $nometutoriale;

	$i=1;
	while ($nometutoriale[$i]<>$id_risorsa and $i<=count($nometutoriale)) {
		$i++;
	};
	$next_alt=$nometutoriale[$i+1];
	return $next_alt;
	
};

function get_prev_alt($id_risorsa) {
	global $nometutoriale;

	$i=1;
	while ($nometutoriale[$i]<>$id_risorsa and $i<=count($nometutoriale)) {
		$i++;
	};
	$prev_alt=$nometutoriale[$i-1];
	return $prev_alt;
	
};

function tipo_pagina($id_padre) {
	global $i_pag,$i_appr;
	global $db;
	global $DBASE;
	global $pagina_finale;
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
				$glossario=$riga_p["glossario"];
				if ($approfondimento<>"on" and $glossario<>"on") {
					$nometutoriale[$i_pag]=$id_risorsa;
					$i_pag++;
				} else {
					$i_appr++;
				};
				break;
				
			case '201':
				$nometutoriale[$i_pag]=$id_risorsa;
				$i_pag++;
				break;
		};
		
	};	
};

function array_lo($id_padre) {
	global $i_pag,$i_appr;
	global $db;
	global $cod_area,$DBASE;
	global $pagina_finale;
	global $PATH_ROOT,$PATH_ROOT_FILE;
	global $risorsa;
	global $esporta;
	global $codice_array,$codice_array_nav;
	global $padre_alternativo,$risorsa_principale;
	global $tut_att,$tut_alt,$num_tut;
	global $id_ultimo_alt,$id_ultimo_pr;
		
	mysql_select_db($DBASE,$db);	
	$query="SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo='200' or tipo='201' or tipo='20') ORDER BY posizione";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_risorsa=$riga["id_risorsa"];
		$titolo=$riga["titolo"];
		$tipo_risorsa=$riga["tipo"];
		$id_pagina=$riga["id_gruppo"];
		$risorsa_padre=$riga["risorsa_padre"];
		
		switch ($tipo_risorsa) {
			case '20':
				array_lo($id_risorsa);
				break;
			
			case '200':
				$id_pagina=$riga["id_gruppo"];
				$query_p="SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$approfondimento=$riga_p["approfondimento"];
				$id_alternativo=$riga_p["id_alternativo"];
				$alternativo_di=$riga_p["alternativo_di"];
				$glossario=$riga_p["glossario"];
				$riepilogo=$riga_p["riepilogo"];
				$tipo_pagina=$riga_p["tipo_pagina"];
				
				if ($id_alternativo) $alternativo_di="";
				if ($alternativo_di) $id_alternativo="";
				
				if ($approfondimento<>"on" and $glossario<>"on") {
					$codice_array.= "nometutoriale[$i_pag]='$id_risorsa';\n";

					if ($i_pag==1) {
						$codice_array.= "tipotutoriale[\"$id_risorsa\"]=3;\n";
						$codice_array.= "numerotutoriale[\"$id_risorsa\"]=$num_tut;\n";
						$num_tut++;
						$codice_array.= "precedente['$id_risorsa']='';\n";
						$codice_array.= "successivo['$tut_att']='$id_risorsa';\n";
						$tut_att=$id_risorsa;
					} else {
						if (!$riepilogo) {
							if ($tipo_pagina<>"5") {
								$codice_array.= "tipotutoriale[\"$id_risorsa\"]=1;\n";
								if ($padre_alternativo) {
									if ($risorsa_padre==$padre_alternativo) {
										$codice_array.= "tutorialeprincipale[\"$id_risorsa\"] = \"$risorsa_principale\";\n";
										$id_ultimo_alt=$id_risorsa;
										$id_ultimo_pr=$risorsa_principale;
							
									} else {
										if ($id_ultimo_alt) {
										$codice_array_nav.= "successivo['$id_ultimo_alt']=successivo['$id_ultimo_pr'];\n";
											$id_ultimo_alt="";
											$id_ultimo_pr="";
											$tut_alt="";
										};
										$padre_alternativo="";
										$risorsa_principale="";
									};
								} else {
									$codice_array.= "numerotutoriale[\"$id_risorsa\"]=$num_tut;\n";
									$num_tut++;		
								};
								
							} else {
								$codice_array.= "tipotutoriale[\"$id_risorsa\"]=5;\n";
								$codice_array.= "numerotutoriale[\"$id_risorsa\"]=$num_tut;\n";
								$num_tut++;
							};
						} else {
							$codice_array.= "tipotutoriale[\"$id_risorsa\"]=4;\n"; 
							$codice_array.= "numerotutoriale[\"$id_risorsa\"]=$num_tut;\n";
							$num_tut++;
						};
					};
					$i_pag++;
				} else {
					$codice_array.= "nomeapprofondimento[$i_appr]='$id_risorsa';\n";
					$i_appr++;
				};
				
				if (!$padre_alternativo and !$alternativo_di and $approfondimento<>"on" and $glossario<>"on" and $i_pag<>2) {
					$codice_array.= "precedente['$id_risorsa']='$tut_att';\n";
					$codice_array.= "successivo['$tut_att']='$id_risorsa';\n";
					$tut_att=$id_risorsa;
				};
				
				
				if ($padre_alternativo and !$alternativo_di and $approfondimento<>"on" and $glossario<>"on" and $i_pag<>2) {
					$codice_array.= "precedente['$id_risorsa']='$tut_alt';\n";
					$codice_array.= "successivo['$tut_alt']='$id_risorsa';\n";
					$tut_alt=$id_risorsa;
				};
				
				if ($id_alternativo) {
					$codice_array.= "tutorialealternativo[\"$id_risorsa\"] = \"$id_alternativo\";\n";	
					$codice_array_nav.= "precedente['$id_alternativo']=precedente['$id_risorsa'];\n";		
				};
				
				if ($alternativo_di) {
					$queryp="SELECT risorsa_padre FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
					$resultp=$mysqli->query($queryp);
					$rigap=$resultp->fetch_array();
					$rp=$rigap[risorsa_padre];
					
					if ($risorsa_padre<>$risorsa) {
						$padre_alternativo=$rp;
						$risorsa_principale=$alternativo_di;
						$codice_array_nav.= "precedente['$id_risorsa']=precedente['$risorsa_principale'];\n";
						$tut_alt=$id_risorsa;
					} else {
						$padre_alternativo="";
						$risorsa_principale="";
						$codice_array_nav.= "successivo['$id_risorsa']=successivo['$alternativo_di'];\n";
					};
					$codice_array.= "tutorialeprincipale[\"$id_risorsa\"] = \"$alternativo_di\";\n";
				};
				
				break;
				
			case '201':
				$id_item=$riga["id_gruppo"];
				$query_p="SELECT * FROM lo_test_item WHERE id_item='$id_item'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$alternativo=$riga_p["alternativo"];
				$punteggio=$riga_p["peso"];
				if (!$punteggio) $punteggio=0;
	
				$id_alternativo=$riga_p["id_alternativo"];
			
				$codice_array.= "nometutoriale[$i_pag]='$id_risorsa';\n";
	
				$codice_array.= "tipotutoriale[\"$id_risorsa\"]=2;\n";

				if ($alternativo) $id_alternativo="";
				if ($id_alternativo) $alternativo="";
				
				if (!$alternativo) {
					$codice_array.= "puntitutoriale[\"$id_risorsa\"]=$punteggio;\n";
					$codice_array.= "numerotutoriale[\"$id_risorsa\"]=$num_tut;\n";
					$num_tut++;
					if ($tut_att<>"homepage") {
						$codice_array.= "precedente['$id_risorsa']='$tut_att';\n";
					} else {
						$codice_array.= "precedente['$id_risorsa']='';\n";
					};
					
					$codice_array.= "successivo['$tut_att']='$id_risorsa';\n";
					$tut_att=$id_risorsa;
				};
				
				
				if ($id_alternativo) {
					$codice_array.= "tutorialealternativo[\"$id_risorsa\"] = \"$id_alternativo\";\n";
					$codice_array.= "tutorialeprincipale[\"$id_alternativo\"] = \"$id_risorsa\";\n";
					$codice_array_nav.= "precedente['$id_alternativo']=precedente['$id_risorsa'];\n";
					$codice_array_nav.= "successivo['$id_alternativo']=successivo['$id_risorsa'];\n";
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
			$glossario=$riga_p["glossario"];
			$tipo_pagina=$riga_p["tipo_pagina"];
			if ($approfondimento<>"on" and $glossario<>"on") $tot_pagine++;
			if ($riepilogo=="on") $pagina_finale=$tot_pagine;
			if ($tipo_pagina=="5") $pagina_finale=$tot_pagine;
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


/* ------------------------------------------------------------------------------------------------------ */
function genera_pagina($id_cartella) {
	global $db;
	global $cod_area,$DBASE;
	global $n_pagina,$n_item,$n_appr,$tot_pagine;
	global $path_img;
	global $drag_item;
	global $colore_scuro;
	global $d,$p;
	global $PATH_ROOT,$PATH_ROOT_FILE;
	global $pagina_finale;
	global $nometutoriale;
	global $codice;
	global $risorsa;
	global $esporta;
	global $padre_alternativo,$risorsa_principale;
	global $geogebra;
	
	mysql_select_db($DBASE,$db);	
	$query="SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_cartella' AND (tipo='200' or tipo='201' or tipo='20') ORDER BY posizione";
	$result=$mysqli->query($query);
	
	while ($riga=$result->fetch_array()) {
		
		$id_risorsa=$riga["id_risorsa"];
		$titolo=$riga["titolo"];
		$tipo_risorsa=$riga["tipo"];
		$id_pagina=$riga["id_gruppo"];
		$pos_pagina=$riga["posizione"];
		$risorsa_padre=$riga["risorsa_padre"];
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
				$glossario=$riga_p["glossario"];
				$id_alternativo=$riga_p["id_alternativo"];
				$alternativo_di=$riga_p["alternativo_di"];
				
				$inapp="";
				if ($approfondimento=="on") 
					$inapp="2";
			
				switch ($tipo_pagina) {
					case "5": //commento
					
						$contenuto=" <form action=\"\">
      <p>
      <label for=\"commento_".$id_risorsa."\" class=\"domanda\">Invia i tuoi commenti al docente.</label>
      <textarea class=\"areacommento\" tabindex=\"1\" id=\"commento_".$id_risorsa."\" rows=\"10\" cols=\"40\" onKeyUp=\"contacaratteri(this,4000)\" onFocus=\"contacaratteri(this,4000)\">
      </textarea>
   </form>";
   						$audio=false;
						break;
						
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
						
						$testo = ereg_replace("(href=\"javascript:approfondimento\(\'([_|[:alnum:]]+)\'\);\")",
                     "href=\"#\\2_a\" onClick=\"approfondimento".$inapp."('\\2')\" onKeyPress=\"approfondimento".$inapp."('\\2')\"", $testo);

						$testo = ereg_replace("(href=\"javascript:tutoriale\(\'([_|[:alnum:]]+)\'\);\")",
                     "href=\"#\\2_a\" onClick=\"tutoriale('\\2')\" onKeyPress=\"tutoriale('\\2')\"", $testo);	
					 
					 	$testo=str_replace("/>",">",$testo);
						
						if ($esporta) {
						copia_oggetti($testo,"src");
						$path_img0=$PATH_ROOT."/immagini/$cod_area";
						$path_img1="shell/img";
						$testo=str_replace($path_img0,$path_img1,$testo);
						
						$path_img0=$PATH_ROOT."//immagini/$cod_area";
						$path_img1="shell/img";
						$testo=str_replace($path_img0,$path_img1,$testo);
						
						$path_img0=$PATH_ROOT."/materiali_img/$cod_area";
						$path_img1="shell/img";
						$testo=str_replace($path_img0,$path_img1,$testo);
						
						};
						
						$contenuto=$testo;
						$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='5' AND id_pagina='$id_pagina'";
						$result_p=$mysqli->query($query_p);
						$riga_p=$result_p->fetch_array();
						if ($riga_p) {
							 $file_audio=$riga_p["file_asset"];
							 if ($esporta) {
							 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_audio);
							 $nomefile=basename($path0);
							 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 @copy($path0,$path1);
							 $file_audio="shell/img/$nomefile";
							 };
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
						
						if ($file_immagine and $esporta) {
							 	$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_immagine);
								$nomefile=basename($path0);
								$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 	@copy($path0,$path1);
							 	$file_immagine="shell/img/$nomefile";
						};
						
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
							 if ($esporta) {
							 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_audio);
							 $nomefile=basename($path0);
							 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 @copy($path0,$path1);
							 $file_audio="shell/img/$nomefile";
							 };
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
						
						if ($file_video and $esporta) {
							 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_video);
							 $nomefile=basename($path0);
							 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 @copy($path0,$path1);
							 $file_video="shell/img/$nomefile";
						};
						
						if ($alt_img and $esporta) {
							 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$alt_img);
							 $nomefile=basename($path0);
							 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 @copy($path0,$path1);
							 $alt_img="shell/img/$nomefile";
						};
						
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
						
						$contenuto="<script type=\"text/javascript\">\n";
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
						
						if ($file_flash and $esporta) {
							 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_flash);
							 $nomefile=basename($path0);
							 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 @copy($path0,$path1);
							 $file_flash="shell/img/$nomefile";
						};
						
						if ($alt_img and $esporta) {
							 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$alt_img);
							 $nomefile=basename($path0);
							 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 @copy($path0,$path1);
							 $alt_img="shell/img/$nomefile";
						};
						
						if ($width>650) {
							$height=floor(($height)*650/$width);
							$width=650;
						};
									
						if ($height>380) {
							$width=floor(($width)*380/$height);
							$height=380;
						};
						
						$n_p=$n_pagina+1;
						$contenuto="<script type=\"text/javascript\">";
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
						$testo = ereg_replace("(href=\"javascript:approfondimento\(\'([_|[:alnum:]]+)\'\);\")",
                     "href=\"#\\2_a\" onClick=\"approfondimento".$inapp."('\\2')\" onKeyPress=\"approfondimento".$inapp."('\\2')\"", $testo);

						$testo = ereg_replace("(href=\"javascript:tutoriale\(\'([_|[:alnum:]]+)\'\);\")",
                     "href=\"#\\2_a\" onClick=\"tutoriale('\\2')\" onKeyPress=\"tutoriale('\\2')\"", $testo);	
						
						$testo=str_replace("/>",">",$testo);
						
						if ($esporta) {
						copia_oggetti($testo,"src");
						$path_img0=$PATH_ROOT."/immagini/$cod_area";
						$path_img1="shell/img";
						$testo=str_replace($path_img0,$path_img1,$testo);
						
						$path_img0=$PATH_ROOT."//immagini/$cod_area";
						$path_img1="shell/img";
						$testo=str_replace($path_img0,$path_img1,$testo);
						};
						
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
										
										if ($file_immagine and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_immagine);
										$nomefile=basename($path0);
										$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$file_immagine="shell/img/$nomefile";
							 			};
										
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
										
										if ($file_immagine and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_immagine);
										$nomefile=basename($path0);
										$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$file_immagine="shell/img/$nomefile";
							 			};
										
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
									
									if ($file_immagine and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_immagine);
										$nomefile=basename($path0);
										$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$file_immagine="shell/img/$nomefile";
							 		};
										
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
									
									if ($file_immagine and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_immagine);
										$nomefile=basename($path0);
										$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$file_immagine="shell/img/$nomefile";
							 		};
									
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
									
									if ($file_immagine and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_immagine);
										$nomefile=basename($path0);
										$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$file_immagine="shell/img/$nomefile";
							 		};
									
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
									
									if ($file_immagine and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_immagine);
										$nomefile=basename($path0);
										$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$file_immagine="shell/img/$nomefile";
							 		};
									
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
									
									if ($file_immagine and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_immagine);
										$nomefile=basename($path0);
										$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$file_immagine="shell/img/$nomefile";
							 		};
									
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
									
									if ($file_immagine and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_immagine);
										$nomefile=basename($path0);
										$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$file_immagine="shell/img/$nomefile";
							 		};
									
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
									
									if ($file_immagine and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_immagine);
										$nomefile=basename($path0);
										$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$file_immagine="shell/img/$nomefile";
							 		};
									
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
									
									if ($file_immagine and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_immagine);
										$nomefile=basename($path0);
										$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$file_immagine="shell/img/$nomefile";
							 		};
									
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
							 if ($esporta) {
								$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_audio);
								$nomefile=basename($path0);
								$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
								@copy($path0,$path1);
								$file_audio="shell/img/$nomefile";
							 };
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
						$testo = ereg_replace("(href=\"javascript:approfondimento\(\'([_|[:alnum:]]+)\'\);\")",
                     "href=\"#\\2_a\" onClick=\"approfondimento".$inapp."('\\2')\" onKeyPress=\"approfondimento".$inapp."('\\2')\"", $testo);

						$testo = ereg_replace("(href=\"javascript:tutoriale\(\'([_|[:alnum:]]+)\'\);\")",
                     "href=\"#\\2_a\" onClick=\"tutoriale('\\2')\" onKeyPress=\"tutoriale('\\2')\"", $testo);	
					 
					 	$testo=str_replace("/>",">",$testo);
						
						if ($esporta) {
						copia_oggetti($testo,"src");
						$path_img0=$PATH_ROOT."/immagini/$cod_area";
						$path_img1="shell/img";
						$testo=str_replace($path_img0,$path_img1,$testo);
						
						$path_img0=$PATH_ROOT."//immagini/$cod_area";
						$path_img1="shell/img";
						$testo=str_replace($path_img0,$path_img1,$testo);
						};
						
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
									
									if ($file_video and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_video);
										 $nomefile=basename($path0);
										 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
										 @copy($path0,$path1);
										 $file_video="shell/img/$nomefile";
									};
									
									if ($alt_img and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$alt_img);
							 			$nomefile=basename($path0);
							 			$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$alt_img="shell/img/$nomefile";
									};
							
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
									$contenuto="
						<script type=\"text/javascript\">\n";
									$contenuto.="caricamedia(\"$file_video\",\"$id_risorsa\",\"dx\",\"$alt_img\",\"$alt_text\");\n";

									$contenuto.= "</script>\n<p>$testo\n";	
									break;
									
								case "4"://video a sinistra
									$file_video=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									$alt_img=htmlentities($riga_p["alt_img"]);
									list($width, $height, $type, $attr) = getimagesize($alt_img);
									
									if ($file_video and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_video);
										 $nomefile=basename($path0);
										 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
										 @copy($path0,$path1);
										 $file_video="shell/img/$nomefile";
									};
									
									if ($alt_img and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$alt_img);
							 			$nomefile=basename($path0);
							 			$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$alt_img="shell/img/$nomefile";
									};
									
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
									$contenuto="
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
							$testo = ereg_replace("(href=\"javascript:approfondimento\(\'([_|[:alnum:]]+)\'\);\")",
                     "href=\"#\\2_a\" onClick=\"approfondimento".$inapp."('\\2')\" onKeyPress=\"approfondimento".$inapp."('\\2')\"", $testo);

						$testo = ereg_replace("(href=\"javascript:tutoriale\(\'([_|[:alnum:]]+)\'\);\")",
                     "href=\"#\\2_a\" onClick=\"tutoriale('\\2')\" onKeyPress=\"tutoriale('\\2')\"", $testo);	
					 
					 		$testo=str_replace("/>",">",$testo);
							
							if ($esporta) {
							copia_oggetti($testo,"src");
							$path_img0=$PATH_ROOT."/immagini/$cod_area";
							$path_img1="shell/img";
							$testo=str_replace($path_img0,$path_img1,$testo);
							
							$path_img0=$PATH_ROOT."//immagini/$cod_area";
						   $path_img1="shell/img";
						   $testo=str_replace($path_img0,$path_img1,$testo);
							};
							
							$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='4' AND id_pagina='$id_pagina' ORDER BY posizione_int LIMIT 1";
							$result_p=$mysqli->query($query_p);
							$riga_p=$result_p->fetch_array();
							$posizione_base=$riga_p["posizione"];
						
							switch ($posizione_base) {
								case "3"://flash a destra
									$file_flash=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									$alt_img=htmlentities($riga_p["alt_img"]);
									list($width, $height, $type, $attr) = @getimagesize($alt_img);
									
									if ($file_flash and $esporta) {
										 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_flash);
										 $nomefile=basename($path0);
										 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
										 @copy($path0,$path1);
							 			$file_flash="shell/img/$nomefile";
									};
									
									if ($alt_img and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$alt_img);
							 			$nomefile=basename($path0);
							 			$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$alt_img="shell/img/$nomefile";
									};
									
									if ($width>350) {
										$height=floor(($height)*350/$width);
										$width=350;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
						
									$n_p=$n_pagina+1;
									$contenuto="
									<script type=\"text/javascript\">\n";
						$contenuto.="caricamedia(\"$file_flash\",\"$id_risorsa\",\"2dx\",\"$alt_img\",\"$alt_text\");\n";

									$contenuto.= "</script>\n<p>$testo\n";	
									break;
							
								case "4"://flash a sinistra
									$file_flash=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									$alt_img=htmlentities($riga_p["alt_img"]);
									list($width, $height, $type, $attr) = @getimagesize($alt_img);
									
									if ($file_flash and $esporta) {
										 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_flash);
										 $nomefile=basename($path0);
										 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
										 @copy($path0,$path1);
							 			$file_flash="shell/img/$nomefile";
									};
									
									if ($alt_img and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$alt_img);
							 			$nomefile=basename($path0);
							 			$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$alt_img="shell/img/$nomefile";
									};
									
									if ($width>350) {
										$height=floor(($height)*350/$width);
										$width=350;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
						
									$n_p=$n_pagina+1;
									$contenuto="
									<script type=\"text/javascript\">";
						$contenuto.="caricamedia(\"$file_flash\",\"$id_risorsa\",\"2sx\",\"$alt_img\",\"$alt_text\");\n";
									$contenuto.= "</script>\n<p>$testo\n";	
									break;
								case 9: //flash sopra
									$file_flash=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									$alt_img=htmlentities($riga_p["alt_img"]);
									list($width, $height, $type, $attr) = @getimagesize($alt_img);
									
									if ($file_flash and $esporta) {
										 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_flash);
										 $nomefile=basename($path0);
										 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
										 @copy($path0,$path1);
							 			$file_flash="shell/img/$nomefile";
									};
									
									if ($alt_img and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$alt_img);
							 			$nomefile=basename($path0);
							 			$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$alt_img="shell/img/$nomefile";
									};
									
									if ($width>350) {
										$height=floor(($height)*350/$width);
										$width=350;
									};
									
									if ($height>300) {
										$width=floor(($width)*300/$height);
										$height=300;
									};
						
									$n_p=$n_pagina+1;
									$contenuto="
									<script type=\"text/javascript\">";
						$contenuto.="caricamedia(\"$file_flash\",\"$id_risorsa\",\"1\",\"$alt_img\",\"$alt_text\");\n";
									$contenuto.= "</script>\n<p>$testo\n";	
									break;
						};
							
						
						break;
						
					case "15": //testo e geogebra
 							$geogebra=true;
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
							$testo = ereg_replace("(href=\"javascript:approfondimento\(\'([_|[:alnum:]]+)\'\);\")",
                     "href=\"#\\2_a\" onClick=\"approfondimento".$inapp."('\\2')\" onKeyPress=\"approfondimento".$inapp."('\\2')\"", $testo);

						$testo = ereg_replace("(href=\"javascript:tutoriale\(\'([_|[:alnum:]]+)\'\);\")",
                     "href=\"#\\2_a\" onClick=\"tutoriale('\\2')\" onKeyPress=\"tutoriale('\\2')\"", $testo);	
					 
					 		$testo=str_replace("/>",">",$testo);
							
							if ($esporta) {
							copia_oggetti($testo,"src");
							$path_img0=$PATH_ROOT."/immagini/$cod_area";
							$path_img1="shell/img";
							$testo=str_replace($path_img0,$path_img1,$testo);
							
							$path_img0=$PATH_ROOT."//immagini/$cod_area";
						   $path_img1="shell/img";
						   $testo=str_replace($path_img0,$path_img1,$testo);
							};
							
							$query_p="SELECT * FROM lo_pagina_asset WHERE tipo_asset='5' AND id_pagina='$id_pagina' ORDER BY posizione_int LIMIT 1";
							$result_p=$mysqli->query($query_p);
							$riga_p=$result_p->fetch_array();
							$posizione_base=$riga_p["posizione"];
						
							switch ($posizione_base) {
								case "3"://ggb a destra
									$file_geogebra=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									$alt_img=htmlentities($riga_p["alt_img"]);
									list($width, $height, $type, $attr) = getimagesize($alt_img);
									
									if ($file_geogebra and $esporta) {
										 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_geogebra);
										 $nomefile=basename($path0);
										 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
										 @copy($path0,$path1);
							 			$file_geogebra="shell/img/$nomefile";
									};
									
									if ($alt_img and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$alt_img);
							 			$nomefile=basename($path0);
							 			$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$alt_img="shell/img/$nomefile";
									};
									
									if ($width>350) {
										$height=floor(($height)*350/$width);
										$width=350;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
						
									$n_p=$n_pagina+1;
									$contenuto="
									<script type=\"text/javascript\">\n";
						$contenuto.="caricamedia(\"$file_geogebra\",\"$id_risorsa\",\"2dx\",\"$alt_img\",\"$alt_text\");\n";

									$contenuto.= "</script>\n<p>$testo\n";	
									break;
							
								case "4"://ggb a sinistra
									$file_geogebra=$riga_p["file_asset"];
									$alt_text=htmlentities($riga_p["alt_text"]);
									$alt_img=htmlentities($riga_p["alt_img"]);
									list($width, $height, $type, $attr) = getimagesize($alt_img);
									
									if ($file_geogebra and $esporta) {
										 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_flash);
										 $nomefile=basename($path0);
										 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
										 @copy($path0,$path1);
							 			$file_flash="shell/img/$nomefile";
									};
									
									if ($alt_img and $esporta) {
							 			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$alt_img);
							 			$nomefile=basename($path0);
							 			$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
							 			@copy($path0,$path1);
							 			$alt_img="shell/img/$nomefile";
									};
									
									if ($width>350) {
										$height=floor(($height)*350/$width);
										$width=350;
									};
									
									if ($height>320) {
										$width=floor(($width)*320/$height);
										$height=320;
									};
						
									$n_p=$n_pagina+1;
									$contenuto="
									<script type=\"text/javascript\">";
						$contenuto.="caricamedia(\"$file_geogebra\",\"$id_risorsa\",\"2sx\",\"$alt_img\",\"$alt_text\");\n";

									$contenuto.= "</script>\n<p>$testo\n";	
									break;
						};
							
						
						break;
						
				};
				
				if ($approfondimento<>"on" and $glossario<>"on") {
				
					$n_pag_prev=$n_pagina;
					$n_pagina++;
					$n_pag_next=$n_pagina+1;
					$id_pag_prev=$nometutoriale[$n_pag_prev];
					$id_pag_next=$nometutoriale[$n_pag_next];
					
					if ($alternativo_di) {
						$id_pag_prev=get_prev_alt($alternativo_di);
						if ($risorsa_padre<>$risorsa) {
							$padre_alternativo=$risorsa_padre;
							$risorsa_principale=$alternativo_di;
						} else {
							$padre_alternativo="";
							$risorsa_principale="";
						};
					};
					
					if (!$alternativo_di and $padre_alternativo and $risorsa_padre==$padre_alternativo) {
						$query_p="SELECT * FROM risorse_materiali WHERE risorsa_padre='$padre_alternativo' ORDER BY posizione DESC LIMIT 1";
						$result_p=$mysqli->query($query_p);
						$riga_p=$result_p->fetch_array();
						$id_p=$riga_p["id_risorsa"];
						
						if ($id_p==$id_risorsa) {
							$id_pag_next=get_next_alt($risorsa_principale);
							$padre_alternativo="";
							$risorsa_principale="";
						};
					
					};
					
					if ($alternativo_di and $risorsa_padre==$risorsa) {
						$id_pag_next=get_next_alt($alternativo_di);
					};
					
					$codice.= "<div id=\"".$id_risorsa."\" class=\"contenutotutoriale\">\n
<p><a name=\"".$id_risorsa."_a\"></a>\n
<h1>$titolo</h1>\n
<script type=\"text/javascript\">\n
   visualizzapagina('$id_risorsa');\n
";

					if ($audio) {
						$codice.= "caricamedia(\"$file_audio\",\"$id_risorsa\");\n";
					};
				
					$codice.= "
</script>\n";
if ($tipo_pagina<>"5") {
	$codice.="<p class=\"nascosto\">$alt_text\n<div class=\"testotutoriale\">\n";
} else {
	$codice.="<p class=\"nascosto\">$alt_text\n<div class=\"testotest\">\n";
};
$codice.="$contenuto\n
<p>\n
</div>\n
<p>\n
<script type=\"text/javascript\">";
	
$codice.= "comandi(\"$id_risorsa\");\n";
	
$codice.= "</script>";
$codice.="<noscript>
		<p>";

					if ($id_pag_prev) {
						$codice.= "<a href=\"#".$id_pag_prev."_a\" accesskey=\"i\" tabindex=\"20\">\n
   <img class=\"pulsanteindietro\" src=\"shell/$path_img/pulsante_indietro.gif\" alt=\"Indietro\">\n
</a>\n";
					};

					if ($n_pagina<>$pagina_finale) {
						$codice.= "<a href=\"#".$id_pag_next."\" accesskey=\"a\" tabindex=\"30\">\n
   <img class=\"pulsanteavanti\" src=\"shell/$path_img/pulsante_avanti.gif\" alt=\"Avanti\">\n
</a>\n";
					};
 					
					if ($tipo_pagina=="5") {
					$codice.="<p class=\"comunicazioni\">
         Attenzione: per inviare commenti &egrave; necessario abilitare Javascript sul browser.";
		 			};
   					$codice.="</noscript>";
					$codice.= "</div>\n";
				
				} else {
					$n_appr++;
					
					$codice.= "<div id=\"".$id_risorsa."\" class=\"contenutoapprofondimento\">\n
<p><a name=\"".$id_risorsa."_a\"></a>\n";
if ($approfondimento=="on") {
	$codice.="<div class=\"logoapprofondimentogenerico\"></div>\n";
} else {
	$codice.="<div class=\"logoglossario\"></div>";
};
$codice.="<div class=\"testoapprofondimentogenerico\">\n
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
				$altro = $item["altro"];
				$titolo_item = parse_kairos($item["titolo"]);
				$consegna_item = parse_kairos($item["legend"]);
				$mostra_titolo_item=($item[mostra_titolo]);
				$domanda_item = trim(parse_kairos($item["domanda"]));
				$img_domanda=parse_img($domanda_item);
				if ($img_domanda) {
					$img_domanda=str_replace("/>",">",$img_domanda);
					$img_domanda="<p>".$img_domanda."</p>";
				};
								
				$domanda_item=pulisci_img($domanda_item);
				
				
				
				if ($esporta) {
				copia_oggetti($consegna_item,"src");
				
				copia_oggetti($domanda_item,"src");
				
				$path_img0=$PATH_ROOT."/immagini/$cod_area";
				$path_img1="shell/img";
				$domanda_item=str_replace($path_img0,$path_img1,$domanda_item);
				
				$path_img0=$PATH_ROOT."//immagini/$cod_area";
				$path_img1="shell/img";
				$domanda_item=str_replace($path_img0,$path_img1,$domanda_item);
				
				
				copia_oggetti($titolo_item,"src");
				$path_img0=$PATH_ROOT."/immagini/$cod_area";
				$path_img1="shell/img";
				$titolo_item=str_replace($path_img0,$path_img1,$titolo_item);
				
				$path_img0=$PATH_ROOT."//immagini/$cod_area";
				$path_img1="shell/img";
				$titolo_item=str_replace($path_img0,$path_img1,$titolo_item);
				
				copia_oggetti($img_domanda,"src");
				$path_img0=$PATH_ROOT."/immagini/$cod_area";
				$path_img1="shell/img";
				$img_domanda=str_replace($path_img0,$path_img1,$img_domanda);
				
				$path_img0=$PATH_ROOT."//immagini/$cod_area";
				$path_img1="shell/img";
				$img_domanda=str_replace($path_img0,$path_img1,$img_domanda);
				};
				
				
				$peso=$item[peso];
				$msg_ok=$item[msg_ok];
				$msg_ko=$item[msg_ko];
				$link_tutoriale=$item[link_tutoriale];
				$link_tutoriale_post=$item[link_tutoriale_post];
				$link_tutoriale_ref=$item[link_tutoriale_ref];
				$alternativo=$item[alternativo];
				$id_alternativo=$item[id_alternativo];
				$alternativo_di=$item[alternativo_di];
				
				$tuttest0=($link_tutoriale);
				$tuttest1=($link_tutoriale_post);
				
				if ($esporta) {
					$pimg="shell/img";
				} else {
					$pimg="shell/$path_img";
				};
						
				switch($tipo_item) {
					case "1":
					$test_tipo="1";
					// scelta multipla risposta singola
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n
					var risposta".$n_p." = new Array;\n";
					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">\n
        			<fieldset>\n
					<legend class=\"domanda\">\n";
				
						$contenuto_form.= "$consegna_item";
					
					if ($domanda_item)
						$contenuto_form.= "<br><br>$domanda_item\n";
				
					$contenuto_form.="</legend>$img_domanda\n";
					
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$n_opzione=1;
					$rispostagiusta=0;
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					while($opzione=$result2->fetch_array()) {
						$risposta_opzione=(htmlentities($opzione[risposta_opzione]));
						$risposta_opzione_p=parse_kairos($opzione[risposta_opzione]);
						
						if ($esporta) {
						copia_oggetti($risposta_opzione_p,"src");
						$path_img0=$PATH_ROOT."/immagini/$cod_area";
						$path_img1="shell/img";
						$risposta_opzione_p=str_replace($path_img0,$path_img1,$risposta_opzione_p);
						
						$path_img0=$PATH_ROOT."//immagini/$cod_area";
						$path_img1="shell/img";
						$risposta_opzione_p=str_replace($path_img0,$path_img1,$risposta_opzione_p);
						};
						
						$punt_opzione=$opzione[punteggio];
						if ($punt_opzione<>"0.00" and !$rispostagiusta) {
							$contenuto_script.="risposta".$n_p."[1] = $n_opzione;\n";
						} else {
							$contenuto_script.="tutorialetest".$n_p."[$n_opzione] = \"$tuttest1\";\n";
						};
						
						$contenuto_form.= "<input type=\"radio\" tabindex=\"$n_opzione\" name=\"test_".$id_risorsa."\" id=\"test".$n_opzione."_".$id_risorsa."\"><label for=\"test".$n_opzione."_".$id_risorsa."\">$risposta_opzione_p <img id=\"testimm".$n_opzione."_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"></label><br>\n";
						$n_opzione++;
					};
					$contenuto_form.="</fieldset>\n</form>\n";
					$contenuto_script.="</script>\n";					
					
					break;
			
					case "2":
					// scelta multipla risposta multipla
					$test_tipo="2";
					$max_risposte=0;
					
					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";
					if ($max_risposte>0) {
						$contenuto_form.= "<span id=\"item_".$n_p."\">\n";
					};
					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">
        			<fieldset>
					<legend class=\"domanda\">";
					
						$contenuto_form.= "$consegna_item";
					
					if ($domanda_item)
						$contenuto_form.= "<br><br>$domanda_item\n";
				
					$contenuto_form.="</legend>$img_domanda\n";
					
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$n_opzione=1;
					$rispostagiusta=0;
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					while($opzione=$result2->fetch_array()) {
						$risposta_opzione=(htmlentities($opzione[risposta_opzione]));
						$risposta_opzione_p=parse_kairos($opzione[risposta_opzione]);
						
						if ($esporta) {
						copia_oggetti($risposta_opzione_p,"src");
						$path_img0=$PATH_ROOT."/immagini/$cod_area";
						$path_img1="shell/img";
						$risposta_opzione_p=str_replace($path_img0,$path_img1,$risposta_opzione_p);
						
						$path_img0=$PATH_ROOT."//immagini/$cod_area";
						$path_img1="shell/img";
						$risposta_opzione_p=str_replace($path_img0,$path_img1,$risposta_opzione_p);
						};
						
						$punt_opzione=$opzione[punteggio];
						$punti=0;
						if ($punt_opzione<>"0.00") $punti=1;
						$contenuto_script.="risposta".$n_p."[$n_opzione] = $punti;\n";
						$contenuto_script.="tutorialetest".$n_p."[$n_opzione] = \"$tuttest1\";\n";
						
						if ($max_risposte>0) {
							$contenuto_form.= "<input type=\"checkbox\" tabindex=\"$n_opzione\" id=\"test".$n_opzione."_".$id_risorsa."\" onclick=\"update_check('item_".$n_p."','$id_risorsa','$max_risposte')\"><label for=\"test".$n_opzione."_".$id_risorsa."\">$risposta_opzione_p <img id=\"testimm".$n_opzione."_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"></label><br>\n";
						} else {
							$contenuto_form.= "<input type=\"checkbox\" tabindex=\"$n_opzione\" id=\"test".$n_opzione."_".$id_risorsa."\"><label for=\"test".$n_opzione."_".$id_risorsa."\">$risposta_opzione_p <img id=\"testimm".$n_opzione."_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"></label><br>\n";
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
					
						$contenuto_form.= "$consegna_item\n";
					
					if ($domanda_item)
						$contenuto_form.= "<br><br>$domanda_item\n";
				
					$contenuto_form.="</legend>$img_domanda\n";
					
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$n_opzione=1;
					$rispostagiusta=0;
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					while($opzione=$result2->fetch_array()) {
						$risposta_opzione=(htmlentities($opzione[risposta_opzione]));
						$risposta_opzione_p=parse_kairos($opzione[risposta_opzione]);
						
						if ($esporta) {
						copia_oggetti($risposta_opzione_p,"src");
						$path_img0=$PATH_ROOT."/immagini/$cod_area";
						$path_img1="shell/img";
						$risposta_opzione_p=str_replace($path_img0,$path_img1,$risposta_opzione_p);
						
						$path_img0=$PATH_ROOT."//immagini/$cod_area";
						$path_img1="shell/img";
						$risposta_opzione_p=str_replace($path_img0,$path_img1,$risposta_opzione_p);
						};
						
						$punt_opzione=$opzione[punteggio];
						if ($punt_opzione<>"0.00" and !$rispostagiusta) {
							$contenuto_script.="risposta".$n_p."[1] = $n_opzione;\n";
						} else {
							$contenuto_script.="tutorialetest".$n_p."[$n_opzione] = \"$tuttest1\";\n";
						};
						$contenuto_form.= "<input type=\"radio\" tabindex=\"$n_opzione\" name=\"test_".$id_risorsa."\" id=\"test".$n_opzione."_".$id_risorsa."\"><label for=\"test".$n_opzione."_".$id_risorsa."\">$risposta_opzione_p <img id=\"testimm".$n_opzione."_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"></label><br>\n";
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
					
						$contenuto_form.= "$consegna_item\n";
				
					$contenuto_form.="</legend>$img_domanda\n";
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$nspazio=0;
					$domanda_item1="<label for=\"test1_".$id_risorsa."\">";
					for ($i=0;$i<strlen($domanda_item);$i++) {
						$char=substr($domanda_item,$i,1);
						if ($char=="[" and substr($domanda_item,$i+1,1)=="*" and substr($domanda_item,$i+2,1)=="]") {
							$nspazio++;
							$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND posizione='$nspazio'";
							$result2=$mysqli->query($query2);
							$opzione=$result2->fetch_array();
							$risposte_lista=htmlentities($opzione[risposte_lista]);
							$risposta_giusta=addslashes($opzione[risposta_giusta]);
							$case_sensitive=($opzione[case_sensitive]);
							$lc=strlen($risposta_giusta)+5;
							$contenuto_script.="risposta".$n_p."[$nspazio] = \"$risposta_giusta\";\n";
							$contenuto_script.="tutorialetest".$n_p."[$nspazio] = \"$tuttest1\";\n";
							
							if (!$risposte_lista) {
								$domanda_item1.="<img id=\"testimm".$nspazio."_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"></label><input type=\"text\" tabindex=\"$nspazio\" size=\"$lc\" id=\"test".$nspazio."_".$id_risorsa."\">";
							} else {
								$opt="<option value=\"0\" selected></option>";
								$opt_list=split("\n",$risposte_lista);
								for ($k=0;$k<count($opt_list);$k++) {
									if (trim($opt_list[$k])) {
										$opt_list[$k]=trim((($opt_list[$k])));
										$opt.="<option value=\"$opt_list[$k]\">$opt_list[$k]";
								 	};
								};
							
								$domanda_item1.="<img id=\"testimm".$nspazio."_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"></label><select tabindex=\"$nspazio\"  size=\"1\" id=\"test".$nspazio."_".$id_risorsa."\">$opt</select>";
							};
							$i=$i+2;
							$next_spazio=$nspazio+1;
							if ($nspazio<$num_spazi) $domanda_item1.="<label for=\"test".$next_spazio."_".$id_risorsa."\">";
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
	
					if ($altro<>"on") { //associazione
					$test_tipo="5";
					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";

					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">\n
        			<fieldset>
					<legend class=\"domanda\">";
					
						$contenuto_form.= "$consegna_item";
					
					if ($domanda_item)
						$contenuto_form.= "<br><br>$domanda_item\n";
						
					$contenuto_form.="</legend>$img_domanda\n";
					
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND tipo_opzione='2' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					$opt_dx="<option value=\"\" selected>(seleziona)</option>";
					
					while ($opzione=$result2->fetch_array()) {
						$risposta_opzione=($opzione[risposta_opzione]);
						$id_opz=$opzione[id_item_opzione];
						$opt_dx.="<option value=\"$risposta_opzione\">$risposta_opzione";
						$value_opz[$id_opz]=addslashes($risposta_opzione);
					};
					
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND tipo_opzione='1' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$p=1;
					while ($opzione=$result2->fetch_array()) {
						$risposta_opzione=($opzione[risposta_opzione]);
						$risposta_opzione_p=parse_kairos($opzione[risposta_opzione]);
						
						if ($esporta) {
						copia_oggetti($risposta_opzione_p,"src");
						$path_img0=$PATH_ROOT."/immagini/$cod_area";
						$path_img1="shell/img";
						$risposta_opzione_p=str_replace($path_img0,$path_img1,$risposta_opzione_p);
						
						$path_img0=$PATH_ROOT."//immagini/$cod_area";
						$path_img1="shell/img";
						$risposta_opzione_p=str_replace($path_img0,$path_img1,$risposta_opzione_p);
						};
						
						$id_item_esatto=$opzione[id_item_esatto];
						$contenuto_script.="risposta".$n_p."[$p] = \"$value_opz[$id_item_esatto]\";\n";
						$contenuto_script.="tutorialetest".$n_p."[$p] = \"$tuttest1\";\n";
							
						$contenuto_form.= "<label for=\"test".$p."_".$id_risorsa."\">$risposta_opzione_p &nbsp;<select tabindex=\"$p\" size=\"1\" id=\"test".$p."_".$id_risorsa."\">$opt_dx</select> <img id=\"testimm".$p."_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"></label><p>";
						$p++;
					};
					
					$contenuto_form.="</fieldset></form>";
					$contenuto_script.="</script>";		
					} else { //categorizzazione
					$test_tipo="4";
					$abc[1]="a";
					$abc[2]="b";
					$abc[3]="c";
					
					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					
					$contenuto_form.="<div class=\"bloccoform\"><p class=\"domanda\">";
					
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND tipo_opzione='2' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					$num_categorie=$result2->num_rows;
					
					if ($num_categorie>3) $num_categorie=3;
					$p=1;
					while ($opzione=$result2->fetch_array()) {
						$risposta_opzione=($opzione[risposta_opzione]);
						$id_opz=$opzione[id_item_opzione];
						$pos_risposta_opzione[$id_opz]=$p;
						$opzione_dx[$p]=$risposta_opzione;
						$p++;
					};
					
					
						$contenuto_form.= "$consegna_item"."";
					
					if ($domanda_item)
						$contenuto_form.= "$domanda_item\n";
						
					for ($i=1;$i<=$num_categorie;$i++) {
						$contenuto_form.="<span class=\"colonnatestint_".$abc[$i]."\">".$opzione_dx[$i]."</span>\n";
					};
					$contenuto_form.="</div>\n";
					
					
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND tipo_opzione='1' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					$p=1;$k=1;
					while ($opzione=$result2->fetch_array()) {
						$risposta_opzione=($opzione[risposta_opzione]);
						$risposta_opzione_p=parse_kairos($opzione[risposta_opzione]);
						
						if ($esporta) {
						copia_oggetti($risposta_opzione_p,"src");
						$path_img0=$PATH_ROOT."/immagini/$cod_area";
						$path_img1="shell/img";
						$risposta_opzione_p=str_replace($path_img0,$path_img1,$risposta_opzione_p);
						
						$path_img0=$PATH_ROOT."//immagini/$cod_area";
						$path_img1="shell/img";
						$risposta_opzione_p=str_replace($path_img0,$path_img1,$risposta_opzione_p);
						};
						
						$id_item_esatto=$opzione[id_item_esatto];
						
						$risposta_esatta=$pos_risposta_opzione[$id_item_esatto];
						$contenuto_script.="risposta".$n_p."[$p] = $risposta_esatta;\n";
						$contenuto_script.="tutorialetest".$n_p."[$p] = \"$tuttest1\";\n";
						
						$contenuto_form.="<div class=\"bloccoform\"><form id=\"test".$p."_".$id_risorsa."\" action=\"\">
						<fieldset>
						<legend><span class=\"domandalegend\">$risposta_opzione_p</span> <img id=\"testimm".$p."_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"></legend>
						";
						for ($i=1;$i<=$num_categorie;$i++) {
							$contenuto_form.="<label class=\"nascosto\" for=\"test".$p.$abc[$i]."_".$id_risorsa."\">".$opzione_dx[$i]."</label><input class=\"colonnatest_".$abc[$i]."\" type=\"radio\" tabindex=\"$k\" name=\"test".$p."_".$id_risorsa."\" id=\"test".$p.$abc[$i]."_".$id_risorsa."\">"."\n";
						};
						$contenuto_form.="
						</fieldset>
						</form>
						</div>
						";
						$p++;
						$k++;
					};
					$contenuto_script.="</script>";		
					};
					break;
				
					case "6":
					// domanda aperta
					
					$test_tipo="3";

					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";

					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">\n
        			<fieldset>
					<legend class=\"domanda\">";
					
						$contenuto_form.= "$consegna_item";
					
					if ($domanda_item)
						$contenuto_form.= "<br><br>$domanda_item\n";
						
					$contenuto_form.="</legend>$img_domanda\n";
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item'";
					$result2=$mysqli->query($query2);
					$opzione=$result2->fetch_array();
					$nome_aperta = "aperta_".$n_p;
					$limite_caratteri=$opzione[limite_caratteri];
					$risposta_giusta=addslashes($opzione[risposta_giusta]);
					$contenuto_script.="risposta".$n_p."[1] = \"$risposta_giusta\";\n";
					$contenuto_script.="tutorialetest".$n_p."[1] = \"$tuttest1\";\n";

					if ($limite_caratteri>0) {
						$pbar="progressbar_".$n_p;
						$contenuto_form.= "<label for=\"test1_".$id_risorsa."\"><textarea id=\"test1_".$id_risorsa."\" name=\"test1_".$id_risorsa."\"  tabindex=\"1\" rows=\"3\" cols=\"50\" onKeyDown=\"textCounter(this,'$pbar',$limite_caratteri)\" 
onKeyUp=\"textCounter(this,'$pbar',$limite_caratteri)\" 
onFocus=\"textCounter(this,'$pbar',$limite_caratteri)\" ></textarea> </label>\n<br />

<div id=\"$pbar\" class=\"progress\"></div>

<script>textCounter(document.getElementById(\"test1_".$id_risorsa."\"),\"$pbar\",$limite_caratteri)</script>

";
					} else {
						$contenuto_form.= "<label for=\"test1_".$id_risorsa."\"><textarea id=\"test1_".$id_risorsa."\" tabindex=\"1\" rows=\"3\" cols=\"50\"></textarea> <img id=\"testimm1_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"></label>\n";
					};
					$contenuto_form.="</fieldset></form>\n";
					$contenuto_script.="</script>\n";		
					break;
				
					case "7":
					//dragdrop
					$test_tipo=6;
					$id_pagina=1000+$id_item;
					
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
						$soluzione=addslashes($riga2["soluzione"]);
					};
					
					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="risposta".$n_p."[1] = \"$soluzione\";\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest1\";\n";
					$contenuto_script.="tutorialetest".$n_p."[1] = \"$tuttest1\";\n";
					$contenuto_script.="</script>";	
					
					
					list($width, $height, $type, $attr) = getimagesize($alt_img);
					
					if ($file_flash and $esporta) {
						 $path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_flash);
						 $nomefile=basename($path0);
						 $path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
						 @copy($path0,$path1);
						$file_flash="shell/img/$nomefile";
					};
					
					if ($alt_img and $esporta) {
						$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$alt_img);
						$nomefile=basename($path0);
						$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
						@copy($path0,$path1);
						$alt_img="shell/img/$nomefile";
					};
									
					$contenuto_script.="<p class=\"nascosto\">
         L'animazione prevede un test da effettuare trascinando gli oggetti sullo schermo. Per accedere automaticamente alla pagina alternativa, ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ necessario disabilitare in precedenza i componenti multimediali.";
					$contenuto_form.="<script type=\"text/javascript\">
     caricamedia(\"".$file_flash."\",\"".$id_risorsa."\",\"2\",\"$alt_img\",\"$alt_text\");\n
      </script><p class=\"domandadd\"><img id=\"testimm1_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"> $consegna_item $domanda_item\n";
					break;
					
					case "8":
					// caccia all'errore

					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item'";
					$result2=$mysqli->query($query2);
					$num_errori=$result2->num_rows;
					
					$test_tipo="2";

					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";

					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">\n
        			<fieldset>
					<legend class=\"domanda\">";
					
						$contenuto_form.= "$consegna_item\n";
				
					$contenuto_form.="</legend>$img_domanda\n";
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$nerrore=0;
					$domanda_item1="<label for=\"test1_".$id_risorsa."\">";
					for ($i=0;$i<strlen($domanda_item);$i++) {
						$char=substr($domanda_item,$i,1);
						if ($char=="[" and substr($domanda_item,$i+1,1)=="*" and substr($domanda_item,$i+2,1)=="]") {
							$nerrore++;
							$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND posizione='$nerrore'";
							$result2=$mysqli->query($query2);
							$opzione=$result2->fetch_array();
							$risposta_giusta=($opzione[risposta_giusta]);
							$rg="0";
							if ($risposta_giusta=="on") $rg="1";
							
							$contenuto_script.="risposta".$n_p."[$nerrore] = $rg;\n";
							$contenuto_script.="tutorialetest".$n_p."[$nerrore] = \"$tuttest1\";\n";
							
							
							$domanda_item1.=" <img id=\"testimm".$nerrore."_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"></label><input type=\"checkbox\" tabindex=\"$nerrore\" id=\"test".$nerrore."_".$id_risorsa."\">";
							
							
							$i=$i+2;
							$next_errore=$nerrore+1;
							if ($nerrore<$num_errori) $domanda_item1.="<label for=\"test".$next_errore."_".$id_risorsa."\">";
						} else {
							$domanda_item1.=$char;
						};
					};	
					$contenuto_form.=$domanda_item1;
					$contenuto_form.="</fieldset></form>";
					$contenuto_script.="</script>";	
					break;
					
					
					case "9":
					// ascolta e scrivi
					
					$test_tipo="3";

					$contenuto_script.="var risposta".$n_p." = new Array;\n";
					$contenuto_script.="var tutorialetest".$n_p." = new Array;\n";

					$contenuto_form.="<form id=\"test_".$id_risorsa."\" action=\"\">\n
        			<fieldset>
					<legend class=\"domanda\">";
					
						$contenuto_form.= "$consegna_item";
					
						
					$contenuto_form.="</legend>$img_domanda\n";
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item'";
					$result2=$mysqli->query($query2);
					$opzione=$result2->fetch_array();
					$nome_aperta = "aperta_".$n_p;
				
					$risposta_giusta=$opzione[risposta_giusta];
					$file_audio=$opzione[risposta_opzione];
					
					$contenuto_script.="risposta".$n_p."[1] = \"$risposta_giusta\";\n";
					$contenuto_script.="tutorialetest".$n_p."[1] = \"$tuttest1\";\n";
					$contenuto_script.="caricamedia(\"".$file_audio."\",\"".$id_risorsa."\");\n";
					
					$contenuto_form.=" <a href=\"#\" accesskey=\"x\" tabindex=\"1\" onClick=\"avviamedium();return false\" onKeyPress=\"avviamedium();return false\"><img onMouseOver=\"roll(this,'audio')\" onMouseOut=\"noroll(this,'audio')\" src=\"shell/$path_img/pulsante_audio.gif\" alt=\"Ascolta l'audio\"></a>";
					$contenuto_form.= "<label for=\"test1_".$id_risorsa."\">";
					if (!$domanda_item) $domanda_item="Scrivi qui";
					if ($domanda_item)
						$contenuto_form.= "$domanda_item"."<br>";
						
					$contenuto_form.=" <img id=\"testimm1_".$id_risorsa."\"  class=\"immagineinlinea\" src=\"$pimg/vuoto.gif\" alt=\"\"></label>&nbsp;<input type=\"text\" id=\"test1_".$id_risorsa."\" tabindex=\"2\" size=\"40\">\n";
					
					$contenuto_form.="
					</fieldset>
					</form>\n";
					$contenuto_script.="</script>\n";		
					break;
					
					case "10":
					//cruciverba;
	
					$test_tipo=7;
					
					$contenuto_script.="
					var caselle".$n_p." = new Array;
					var flagrisposte".$n_p." = new Array;
  				    var definizione".$n_p." = new Array;
					var tutorialetest".$n_p." = new Array;
					var messaggiotest".$n_p."= new Array;\n";
					$contenuto_script.="tutorialetest".$n_p."[0] = \"$tuttest0\";\n";
					$contenuto_script.="messaggiotest".$n_p."[0] = \"$msg_ok\";\n";
					
					$query2="SELECT * FROM lo_test_item_cruciverba WHERE id_item='$id_item'";
					$result2=$mysqli->query($query2);
					$riga2=$result2->fetch_array();
					$num_orz=$riga2["larghezza"];
					$num_ver=$riga2["altezza"];
					
					$contenuto_script.="definizione".$n_p."[0] = new Array($num_orz,$num_ver);\n";
					$query2="SELECT * FROM lo_test_item_opzioni_cruciverba WHERE id_item='$id_item' ORDER BY posizione";
					$result2=$mysqli->query($query2);
					$p=1;
					while ($opzione2 = $result2->fetch_array()) {
						$posizione=$opzione2[posizione];
						$etichetta=$opzione2[etichetta];
						$contenuto_script.="caselle".$n_p."[$posizione] = $etichetta;\n";
						$p++;
					};
					
	
					$query2="SELECT * FROM lo_test_item_opzioni_cruciverba WHERE id_item='$id_item' and etichetta<>-1 ORDER BY verso,posizione";
					$result2=$mysqli->query($query2);
					$p=1;
					while ($opzione2 = $result2->fetch_array()) {
						$posizione=$opzione2[posizione];
						$etichetta=$opzione2[etichetta];
						$verso=strtolower($opzione2[verso]);
						$definizione=addslashes($opzione2[definizione]);
						$risposta_giusta=($opzione2[risposta_giusta]);
						$msg_ko=($opzione2[msg_ko]);
						
						$contenuto_script.="definizione".$n_p."[$p] = new Array($etichetta,\"$verso\",\"$definizione\",\"$risposta_giusta\");\n";
						$contenuto_script.="tutorialetest".$n_p."[$p] = \"$tuttest1\";\n";
						$contenuto_script.="messaggiotest".$n_p."[$p] = \"$msg_ko\";\n";
						$p++;
					};
					$contenuto_form.="
					<script type=\"text/javascript\">
   visualizzacruciverba(\"$id_risorsa\",caselle".$n_p.",definizione".$n_p.");
</script>";
					$contenuto_script.="</script>";
					break;
		};

$n_pag_prev=$n_pagina;
$n_pagina++;
$n_pag_next=$n_pagina+1;
$id_pag_prev=$nometutoriale[$n_pag_prev];
$id_pag_next=$nometutoriale[$n_pag_next];

if ($alternativo) {
	$id_pag_next=get_next_alt($alternativo_di);
};
			
$codice.= "
<div id=\"$id_risorsa\" class=\"contenutotutoriale\">\n
<p><a name=\"".$id_risorsa."_a\"></a>\n
<div class=\"testata_v\"></div>\n";

if ($mostra_titolo_item) {
 	$codice.="<h1>$titolo_item</h1>\n";
} else {
	$codice.="<h1 class=\"nascosto\">$titolo_item</h1>\n";
};
$codice.="$contenuto_script\n";

if ($tipo_item<>"7") {
	$codice.= "<div class=\"testotest\">\n";
} else {
	$codice.= "<div class=\"testotestdd\">\n";
};
if ($tipo_item<>"7" and $tipo_item<>"10") {
	$codice.="<div class=\"risposta\">\n";
};
$codice.= "$contenuto_form";
if ($tipo_item<>"7" and $tipo_item<>"10") {
	$codice.="</div>\n";
};
$codice.= "</div>\n
<p>\n";


$codice.= "<script type=\"text/javascript\">";


$codice.="var messaggiotest_".$id_risorsa."= new Array();\n";

if (trim($msg_ok)) {
	$codice.= "messaggiotest_".$id_risorsa."[0]=\"$msg_ok\";\n";
} else {
	$codice.= "messaggiotest_".$id_risorsa."[0]=\"messaggiotest[0]\";\n";
};

if (trim($msg_ko)) {
	$codice.= "messaggiotest_".$id_risorsa."[1]=\"$msg_ko\";\n";
} else {
	$codice.= "messaggiotest_".$id_risorsa."[1]=\"messaggiotest_default[0]\";\n";
};

$risposta="risposta";
if ($tipo_item=="10") $risposta="definizione";

$codice.= " comandi(\"$id_risorsa\",$test_tipo,\"$risposta".$n_p."\",\"tutorialetest".$n_p."\",\"messaggiotest_".$id_risorsa."\",\"$link_tutoriale_ref\");\n
   </script>\n
   <noscript>\n
      <p>\n
      <a href=\"#".$id_pag_next."_a\" accesskey=\"a\" tabindex=\"210\">\n
         <img class=\"pulsanteavanti\" src=\"shell/$path_img/pulsante_avanti.gif\" alt=\"Avanti\">\n
      </a>\n
	  ";
	  
if ($tipo_item=="10") {
	$codice.=" <p class=\"comunicazioni\">
      Attenzione: per visualizzare il cruciverba ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ necessario abilitare Javascript sul browser.\n";
};	  
   $codice.="</noscript>\n
 ";

$codice.= "
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
	global $PATH_ROOT,$PATH_ROOT_FILE;
	global $codice;
	global $risorsa;
	global $pagina_finale;
	
	mysql_select_db($DBASE,$db);
	$query_r="SELECT * FROM risorse_materiali WHERE (tipo='200' or tipo='201' or tipo='20') AND risorsa_padre='$cartella' ORDER BY posizione";
	$result_r=$mysqli->query($query_r);
	while ($riga_r=$result_r->fetch_array() and $i_pag<$pagina_finale) {
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
				$glossario=$riga_p["glossario"];
				if ($approfondimento<>"on" and $glossario<>"on") {
					$i_pag++;
					if ($format=="a") { 
						$codice.= "<div id=\"sommarioriga_".$id_risorsa."\" class=\"rigabox\">
      				<a href=\"#".$id_risorsa."_a\" class=\"sommario1\" onClick=\"ritornatutoriale('$id_risorsa');return false\" onKeyPress=\"ritornatutoriale('$id_risorsa');return false\">$i_pag $titolo_pag</a>
      				<img id=\"sommarioimm_".$id_risorsa."\" class=\"sommarioimm\" src=\"shell/$path_img/vuoto.gif\" alt=\"\">
  					 </div>";
					} else {
						$codice.= "<div id=\"sommarioriga_".$id_risorsa."\" class=\"rigabox\">
     				 <span class=\"sommario1\">$i_pag $titolo_pag</span>
      				<img id=\"sommarioimm_".$id_risorsa."\" class=\"sommarioimm\" src=\"shell/$path_img/vuoto.gif\" alt=\"\">
  					 </div>";
					};
				};
			} else {
				$id_item=$riga_r["id_gruppo"];
				$query_p="SELECT * FROM lo_test_item WHERE id_item='$id_item'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$alternativo=$riga_p["alternativo"];
				if (!$alternativo) {
				$i_pag++;
				$codice.= "<div id=\"sommarioriga_".$id_risorsa."\" class=\"rigabox\">
     				 <span class=\"sommario1\">$i_pag $titolo_pag</span>
      				<img id=\"sommarioimm_".$id_risorsa."\" class=\"sommarioimm\" src=\"shell/$path_img/vuoto.gif\" alt=\"\">
  					 </div>";
				};	 
			};
		};
	};
	
};

function visualizza_home($id_risorsa) {
	global $db;
	global $cod_area,$DBASE;
	global $path_img;
	global $titolo_corso;
	global $PATH_ROOT,$PATH_ROOT_FILE;
	global $codice;
	global $risorsa;
	global $esporta;
	
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
	
	$codice.= "<h1>$titolo_corso</h1>
<script type=\"text/javascript\">
   comunicaplugin();";
   if ($file_audio) {
   		if ($esporta) {
   			$path0=str_replace($PATH_ROOT,$PATH_ROOT_FILE,$file_audio);
		 	$nomefile=basename($path0);
		 	$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/$nomefile";
		 	@copy($path0,$path1);
		 	$file_audio="shell/img/$nomefile";
		 };
   		$codice.= "caricamedia(\"$file_audio\",\"homepage\");";
	};
	$codice.= "
</script>
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


function copyr($source, $dest)
{
    
    if (is_file($source)) {
        return @copy($source, $dest);
    }

  
    if (!is_dir($dest)) {
        mkdir($dest,0777);
    }

    
    $dir = dir($source);
    while (false !== $entry = $dir->read()) {
        
        if ($entry == '.' || $entry == '..') {
            continue;
        }

        
        if ($dest !== "$source/$entry") {
            copyr("$source/$entry", "$dest/$entry");
        }
    }

    
    $dir->close();
    return true;
}

function copia_oggetti($contenuto,$pattern) {
	global $PATH_ROOT,$PATH_ROOT_FILE;
	global $cod_area;
	global $risorsa;
	
	$position = multi_strpos($pattern, $contenuto);
	
	if ($position) {
  		while (list($index, $pos) = each($position)) {
			$i=0;
			$carattere=substr($contenuto,$pos+$i,1);
			
			$j=$pos+$i;
			
			if ($pattern<>"nota") {
			while ($carattere<>'=' and $j<strlen($contenuto)) {
				$i++;
				$j=$pos+$i;
				$carattere=substr($contenuto,$pos+$i,1);
				
			};	
			};
			
			if ($carattere=='=' ) {
				$i++;
				$carattere=substr($contenuto,$pos+$i,1);

				if ($carattere=='"' or $carattere=="'") {  
					$i++;
					$carattere=substr($contenuto,$pos+$i,1);
				};
			
				$link="";
				$j=$pos+$i;
				while ($carattere<>'"' and $carattere<>"'" and $carattere<>'>' and $carattere<>' ' and $j<strlen($contenuto)) {
					$link .= $carattere;
					$i++;
					$j=$pos+$i;
					$carattere=substr($contenuto,$pos+$i,1);
				
				};
					
				if (ereg("materiali_img",$link)) {
					$nome_file=basename($link);
					$path_originale=str_replace($PATH_ROOT_FILE,$PATH_ROOT,$link);
					@copy ($path_originale,$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/".$nome_file);
				};
				
				if (ereg("immagini",$link)) {
					$nome_file=basename($link);
					$path_originale=str_replace($PATH_ROOT_FILE,$PATH_ROOT,$link);
					@copy ($path_originale,$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img/".$nome_file);
				};
				
				if (ereg("formule",$link)) {
					$nome_file=basename($link);
					//$path_originale=str_replace($PATH_ROOT_FILE,$PATH_ROOT,$link);
					@copy ($link,$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/formule/".$nome_file);
				};
				
			};
		};
	};

};


?>

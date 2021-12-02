<?php
function stringa_filesize($filesize) {
	$type = Array ('Bytes', 'KB', 'MB', 'GB');

    for ($i = 0; $filesize > 1024; $i++)
        $filesize /= 1024;

    return round ($filesize, 2)." $type[$i]"; 
};

function multi_strpos($pattern, $sequence) {
  $n = -1;
  while (eregi($pattern, $sequence)) {
    $n++;
    $fragment = split($pattern, $sequence);
    $trimsize = (strlen($fragment[0]))+1;
    $sequence = "*".substr($sequence, $trimsize);
    $position[$n] = (strlen($fragment[0]) + $position[($n-1)]);
   };

  return $position;

};

function copia_oggetti($contenuto,$pattern) {
	global $DBASE,$DBUSER,$DBPWD;
	global $PATH_PAGINE,$PATH_MEDIA,$PATH_ROOT,$PATH_ARCHIVI,$PATH_MODULO;
	global $URL_IMG;
	global $cod_area;
	global $id_modulo;
	global $oggetto_img;
	global $oggetto_link;
	global $gruppo,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
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
			
			if ($pattern=="nota") {
			while ($carattere<>'(' and $j<strlen($contenuto)) {
				$i++;
				$j=$pos+$i;
				$carattere=substr($contenuto,$pos+$i,1);
				
			};	
			};
			
			if ($carattere=='=' or ($pattern=="nota" and $carattere=="(")) {
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
					$path_originale=str_replace($URL_IMG,$PATH_MEDIA,$link);
					copy ($path_originale,$PATH_MODULO.$id_modulo."/img/".$nome_file);
					$oggetto_img.=$link.",";
				};
				
				if ($gruppo) {
					if (ereg("materiali_gruppo_browse\.php\?risorsa",$link)) {
						$oggetto_link.=$link.",";
					};
				} else {
					if (ereg("materiali_browse\.php\?risorsa",$link)) {
						$oggetto_link.=$link.",";
					};
				};
			};
		};
	};

};

function id_corso($id_risorsa) {
	global 	$DBASE,$DBUSER,$DBPWD;
	global $gruppo,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
	if ($gruppo) {
		$query = "SELECT risorsa_padre FROM materiali_gruppo WHERE id_risorsa='$id_risorsa'";
	} else {
		$query = "SELECT risorsa_padre FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
	};
	
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	$id_padre = $riga["risorsa_padre"];
	
	if ($id_padre == 'root') {
		mysql_select_db($DBASE,$db);
		return $id_risorsa;
	} else {
		mysql_select_db($DBASE,$db);
		return id_corso($id_padre);
	};

}; 

function materiali_pag_prec($id_risorsa,$risorsa_superiore) {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT;
	global $id_corso;
	global $gruppo,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
	if ($gruppo) {
		$query = "SELECT id_risorsa FROM materiali_gruppo WHERE  (tipo=0 OR tipo=4) and risorsa_padre='$risorsa_superiore' ORDER BY posizione,id_risorsa";
	} else {
		$query = "SELECT id_risorsa FROM risorse_materiali WHERE  (tipo=0 OR tipo=4) and risorsa_padre='$risorsa_superiore' ORDER BY posizione,id_risorsa";
	};
	
	$result=$mysqli->query($query);
	$pag_prec="";
	$continua=true;
	while (($riga = $result->fetch_array()) and $continua) {
		$pag_att = $riga["id_risorsa"];
		if ($pag_att==$id_risorsa) {
			$continua=false;
		} else {
			$pag_prec=$pag_att.".htm";
		};
		
	};
	return $pag_prec;
}; 

function materiali_pag_succ($id_risorsa,$risorsa_superiore) {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT;
	global $id_corso;
	global $gruppo,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
	if ($gruppo) {
		$query = "SELECT id_risorsa FROM materiali_gruppo WHERE  (tipo=0 OR tipo=4) and risorsa_padre='$risorsa_superiore' ORDER BY posizione DESC";
	} else {
		$query = "SELECT id_risorsa FROM risorse_materiali WHERE  (tipo=0 OR tipo=4) and risorsa_padre='$risorsa_superiore' ORDER BY posizione DESC";
	};
	
	$result=$mysqli->query($query);
	$pag_succ="";
	$continua=true;
	while (($riga = $result->fetch_array()) and $continua) {
		$pag_att = $riga["id_risorsa"];
		if ($pag_att==$id_risorsa) {
			$continua=false;
		} else {
			$pag_succ=$pag_att.".htm";
		};
	};
	return $pag_succ;
}; 

function foglia($id_risorsa) {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT;
	global $gruppo,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
	if ($gruppo) {
		$query = "SELECT id_risorsa,tipo FROM materiali_gruppo WHERE risorsa_padre='$id_risorsa' AND (tipo=0 OR tipo=4 OR tipo=2) ORDER BY posizione,id_risorsa LIMIT 1";
	} else {
		$query = "SELECT id_risorsa,tipo FROM risorse_materiali WHERE risorsa_padre='$id_risorsa' AND (tipo=0 OR tipo=4 OR tipo=2) ORDER BY posizione,id_risorsa LIMIT 1";
	};
	
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	$id_risorsa = $riga["id_risorsa"];
	$tipo=$riga["tipo"];
	
	if ($id_risorsa) {
		if ($tipo<>2) {
			mysql_select_db($DBASE,$db);
			return $id_risorsa;
		 } else {
		 	mysql_select_db($DBASE,$db);
		 	return foglia($id_risorsa);
		};
	} else {
		mysql_select_db($DBASE,$db);
		return $id_risorsa;
	};
};

function padre($id_risorsa,$id_nodo) {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT;
	global $id_modulo;
	global $gruppo,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	if ($gruppo) {
		$query = "SELECT risorsa_padre FROM materiali_gruppo WHERE id_risorsa='$id_nodo'";
	} else {
		$query = "SELECT risorsa_padre FROM risorse_materiali WHERE id_risorsa='$id_nodo'";
	};
	
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	$id_padre = $riga["risorsa_padre"];
	
	if ($id_padre==$id_risorsa) {
		mysql_select_db($DBASE,$db);
		return true;
	} else {
		if ($id_padre==$id_modulo) {
			mysql_select_db($DBASE,$db);
			return false;
		 } else {
		 	mysql_select_db($DBASE,$db);
		 	return padre($id_risorsa,$id_padre);
		};
	};
	
};

function capitolo($id_padre,$id_nodo) {
	global 	$DBASE,$DBUSER,$DBPWD;
	global $gruppo,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
	if (!ereg('MSIE',$_SERVER["HTTP_USER_AGENT"]) or !ereg('Windows',$_SERVER["HTTP_USER_AGENT"])) {
		$win_ie=false;
	} else {	
		$win_ie=true;
	};

	
	if ($gruppo) {
		$query = "SELECT * FROM materiali_gruppo WHERE risorsa_padre='$id_padre' AND (tipo=0 OR tipo=2 OR tipo=4) ORDER BY posizione";
	} else {
		$query = "SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo=0 OR tipo=2 OR tipo=4) ORDER BY posizione";
	};
	
	$result=$mysqli->query($query);
	
	$cod_cap="";
	
$cod_cap.= "<ul style=\"list-style-type:none\">\n";

while ($risorsa = $result->fetch_array()) {
	
	$cod_cap.=  "<li>\n";
	$id_risorsa=$risorsa["id_risorsa"];
	$tipo=$risorsa["tipo"];
	$titolo=$risorsa["titolo"];
	
	if ($tipo==4) {
		$id_gruppo=$risorsa[id_gruppo];
		$query_t="SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
		$result_t=$mysqli->query($query_t);
		$riga_t=$result_t->fetch_array();
		$titolo=$riga_t[titolo];
	};
	
	
	
	if ($tipo==2) {
		$cap0="cap0_".$id_risorsa;
		$cap1="cap1_".$id_risorsa;
		$aperto=padre($id_risorsa,$id_nodo);
		if (!$win_ie) $aperto=true;
		
		
		if ($aperto) {
			$immagine="img/meno.gif";
		} else {
			$immagine="img/piu.gif";
		};
		$cod_cap.=  "<div id=$cap0 onClick=\"mostra_capitolo_cd(this,'$cap1')\" style=\"cursor:hand\"><img name=img_".$cap1." src=\"$immagine\" width=\"11\" height=\"11\" alt=\"\" border=\"0\">\n";
	};
	
	if ($tipo==2) {
		if ($win_ie) {
			$cod_cap.=  "<span class=testopiccolo><a href=\"javascript:;\" onClick=\"window.event.cancelBubble=true\">$titolo</a></span>";
 		} else {
			$cod_cap.=  "<span class=testopiccolo><a href=\"javascript:;\">$titolo</a></span>";
		};
	} else {
		if ($id_risorsa==$id_nodo) { 
			$cod_cap.=  "<span class=testopiccolo><b>$titolo</b></span>";
		} else {
			if ($tipo<>1) {
				if ($win_ie) {
					$cod_cap.=  "<span class=testopiccolo><a href=\"$id_risorsa".".htm\" onClick=\"window.event.cancelBubble=true\">$titolo</a></span>";
				} else {
					$cod_cap.=  "<span class=testopiccolo><a href=\"$id_risorsa".".htm\">$titolo</a></span>";
				}
			}; 
		};
	};
	
	
	
	if ($tipo==2) {
		if ($aperto) {
	 		$display="Visible";
		} else {
			$display="None";
		};
		if ($win_ie) {
	 		$cod_cap.=  "<div id=$cap1 style=\"Display:$display\" onClick=\"window.event.cancelBubble=true\">\n";
		} else {
			$cod_cap.=  "<div id=$cap1 style=\"Display:$display\">\n";
		}
	 	$cod_cap.= capitolo($id_risorsa,$id_nodo); 
	 	$cod_cap.=  "</div></div>\n";
	} 
	
	$cod_cap.=  "</li>";
	
	
};
	
$cod_cap.=  "</ul>";

return $cod_cap;

};


function esporta_pagina($id_risorsa) {
	global $DBASE,$DBUSER,$DBPWD;
	global $PATH_PAGINE,$PATH_MEDIA,$PATH_ROOT,$PATH_ARCHIVI,$PATH_MODULO;
	global $URL_IMG;
	global $cod_area;
	global $id_modulo;
	global $id_corso_esporta;
	global $oggetto_img;
	global $oggetto_link;
	global $gruppo,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
	if ($gruppo) {
		$query = "SELECT * FROM materiali_gruppo WHERE id_risorsa='$id_risorsa'";
	} else {
		$query = "SELECT * FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
	};
	
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$tipo_risorsa=$riga["tipo"];
	$id_gr=$riga["id_gruppo"];
	$titolo=$riga["titolo"];
	
	switch ($tipo_risorsa) {
		case 1:
			$file_download=$PATH_ARCHIVI.$titolo;
			copy($file_download,$PATH_MODULO.$id_modulo."/"."risorse/".$titolo);
			break;
			
		case 0:
			$codice="";
			$id_pagina=$id_risorsa;
			require "./layout_pagina.php";
			$fp=fopen($PATH_MODULO.$id_modulo."/".$id_risorsa.".htm","w");
			fwrite($fp,$codice);
			fclose($fp);
			break;		
			
		case 4:
			$codice="";
			$id_pagina=$id_gr;
			require "./layout_pagina.php";
			$fp=fopen($PATH_MODULO.$id_modulo."/".$id_risorsa.".htm","w");
			fwrite($fp,$codice);
			fclose($fp);
			break;	
	
		case 3:
			$id_pagina=$id_risorsa;
			if (file_exists($PATH_ROOT."pagine/$cod_area/colori.inc")) 
			require $PATH_ROOT."pagine/$cod_area/colori.inc";
	
			$codice .= "
			<html>
			<head>
			<title>$titolo</title>
			<link rel=\"stylesheet\" href=\"stili/stile_sito.css\">
			</head>
				<body topmargin=\"0\" leftmargin=\"15\" bgcolor=\"#FFFFFF\" link=\"$colore_link\">";
			$codice .= "
			<table width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=\"left\">
			<tr><td>";
			$codice .= "<span class=testo>";
		
			if (file_exists($PATH_ROOT."materiali/$cod_area/$id_pagina.inc")) {
			$pagina=join('',file($PATH_ROOT."materiali/$cod_area/$id_pagina.inc"));
			
			
			require "./copia_oggetti.php";
			
			$codice .= $pagina;
		};
		
			$codice .= "</span>";
			
			
			$fp=fopen($PATH_MODULO.$id_modulo."/".$id_risorsa.".htm","w");
			fwrite($fp,$codice);
			fclose($fp);
			break;	
			
	};
	
};


function esporta_cartella($id_cartella) {
	global $DBASE,$DBUSER,$DBPWD;
	global $PATH_PAGINE,$PATH_MEDIA,$PATH_ROOT,$PATH_ARCHIVI;
	global $id_corso_esporta;
	global $gruppo,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
	if ($gruppo) {
		$query = "SELECT * FROM materiali_gruppo WHERE risorsa_padre='$id_cartella'";
	} else {
		$query = "SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_cartella'";
	};
	$result=$mysqli->query($query);

	
	
	while ($riga=$result->fetch_array()) {
		$id_risorsa=$riga["id_risorsa"];
		$tipo_risorsa=$riga["tipo"];
	
		if ($tipo_risorsa==2) {
			//echo "esporto cartella: $id_risorsa<br>";
			esporta_cartella($id_risorsa);
		} else {
			//echo "esporto pagina: $id_risorsa<br>";
			esporta_pagina($id_risorsa);
		};
	};
};	


function esporta_modulo() {	
	global $DBASE,$DBUSER,$DBPWD;
	global $PATH_PAGINE,$PATH_MEDIA,$PATH_ROOT,$PATH_ARCHIVI,$PATH_MODULO;
	global $URL_IMG;
	global $cod_area;
	global $id_modulo;
	global $id_corso_esporta;
	global $oggetto_img;
	global $oggetto_link;
	global $xml;
	global $gruppo,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	if ($gruppo) {
		$query = "SELECT * FROM materiali_gruppo WHERE id_risorsa='$id_modulo'";
	} else {
		$query = "SELECT * FROM risorse_materiali WHERE id_risorsa='$id_modulo'";
	};
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();

if ($riga) {
	
	if (!is_dir($PATH_MODULO."$id_modulo")) {
		@mkdir($PATH_MODULO."$id_modulo",0755);
	};

	if (!is_dir($PATH_MODULO."$id_modulo/img")) {
		@mkdir($PATH_MODULO."$id_modulo/img",0755);
	};

	if (!is_dir($PATH_MODULO."$id_modulo/risorse")) {
		@mkdir($PATH_MODULO."$id_modulo/risorse",0755);
	};

	if (!is_dir($PATH_MODULO."$id_modulo/stili")) {
		@mkdir($PATH_MODULO."$id_modulo/stili",0755);
	};

	if (!is_dir($PATH_MODULO."$id_modulo/script")) {
	@mkdir($PATH_MODULO."$id_modulo/script",0755);
	};

	copy($PATH_ROOT."stili/$cod_area/stile_sito.css",$PATH_MODULO."$id_modulo/stili/stile_sito.css");
	copy($PATH_ROOT."script/funzioni.js",$PATH_MODULO."$id_modulo/script/funzioni.js");

	if (file_exists($PATH_ROOT."img/$cod_area/testata.gif")) {
		copy($PATH_ROOT."img/$cod_area/testata.gif",$PATH_MODULO."$id_modulo/img/testata.gif");
	};

	if (file_exists($PATH_ROOT."img/$cod_area/testata.jpg")) {
		copy($PATH_ROOT."img/$cod_area/testata.jpg",$PATH_MODULO."$id_modulo/img/testata.jpg");
	};

	if (file_exists($PATH_ROOT."img/$cod_area/up-bg.gif")) {
		copy($PATH_ROOT."img/$cod_area/up-bg.gif",$PATH_MODULO."$id_modulo/img/up-bg.gif");
	};

	if (file_exists($PATH_ROOT."img/$cod_area/up-bg.jpg")) {
		copy($PATH_ROOT."img/$cod_area/up-bg.jpg",$PATH_MODULO."$id_modulo/img/up-bg.jpg");
	};

	copy($PATH_ROOT."img/forum/piu.gif",$PATH_MODULO."$id_modulo/img/piu.gif");
	copy($PATH_ROOT."img/forum/meno.gif",$PATH_MODULO."$id_modulo/img/meno.gif");


	esporta_cartella($id_modulo);
	
	if ($gruppo) {
		$query="SELECT * FROM lo WHERE id_lo='gruppo_$id_modulo'";
	} else {
		$query="SELECT * FROM lo WHERE id_lo='$id_modulo'";
	};
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	
	
	if ($riga) {
		$xml="";
		if ($gruppo) {
			$id_lo="gruppo_".$id_modulo;
		} else {
			$id_lo=$id_modulo;
		};
		$id_profile=$riga[id_profile];
		xml_lo($id_lo,$id_profile);
		
		if ($xml) {
			$filexml=$PATH_MODULO.$id_modulo."/LOM.xml";
			$fd=fopen($filexml,"w");
			fwrite($fd,$xml);
			fclose($fd);
		};
	};
	
	$filename=$id_modulo.".zip";
	$cur_dir=getcwd();
	chdir($PATH_MODULO);
	$comando="/usr/bin/zip -r $filename $id_modulo";
	exec($comando);
	$comando="rm -rf $id_modulo";
	exec($comando);
	chdir($cur_dir);
	
	$file_download=$PATH_MODULO.$filename;
	if (file_exists($file_download)) {
		$doc = fopen($file_download,"rb");
		header("Content-Type: application/zip");
		header( "Content-Disposition: attachment; filename=$filename" ); 
		fpassthru($doc);	
	} else {
		echo "Problemi nell'esportazione del modulo: <b>$id_modulo</b><br>";
	}
	
} else {
	echo "Non trovo il modulo: <b>$id_modulo</b><br>";
};
};

function xml_lom($id_lo,$id_profile,$id_lom_sup=0,$id_rep_sup=0) {
	global $db,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	global $xml;
	
	$encode="IMS";
	
	$opt_lang=array("x-none","ab","aa","af","sq","am","ar","hy","as","ay","az","ba","eu","bn","dz","bh","bi","br","bg","my","be","km","ca","zh","kw","co","hr","cs","da","nl","en","eo","et","fo","fj","fi","fr","fy","gl","ka","de","el","kl","gn","gu","ha","he","hi","hu","id","ia","ie","iu","ik","ga","is","it","ja","jw","kn","ks","kk","rw","ky","rn","ko","ku","lo","la","lv","ln","lt","lb","mk","mg","ms","ml","mt","gv","mi","mr","mo","mn","na","ne","i-sami-no","no","no-nyn","no-bok","oc","or","om","ps","fa","pl","pt","pa","qu","rm","ro","ru","sm","sg","sa","gd","sr","sh","st","tn","sn","sd","si","ss","sk","sl","so","es","su","sv","sw","tl","tg","ta","tt","te","th","bo","ti","to","ts","tr","tk","tw","ug","uk","ur","uz","vi","vo","cy","wo","xh","yi","yo","za","zu");
	
	$query="SELECT * FROM lo_schema WHERE id_lom_sup='$id_lom_sup' AND id_profile='$id_profile' ORDER BY id_lom";
	$result=$mysqli->query($query);
	
		while ($riga=$result->fetch_array()) {
			$id_lom=$riga[id_lom];
			$nome=htmlentities(trim($riga[nome]));
			$nome=str_replace(" ","",$nome);
			
			switch ($encode) {
				case "LOM":
					break;
				case "IMS":
					$nome=strtolower($nome);
					break;
			};
			
			
			$size=$riga[size];
			$tipocampo=$riga[tipocampo];
			$valuespace=$riga[valuespace];
			$langstring=$riga[langstring];
			$datetype=$riga[datetype];
			$valdefault=$riga[valdefault];
            $obbligatorio=$riga[obbligatorio];
            $commento=$riga[commento];
						
			$query1="SELECT * FROM lo_metadata WHERE id_lom='$id_lom' AND id_lo='$id_lo' AND id_rep_sup='$id_rep_sup' ORDER BY id_rep";
			$result1=$mysqli->query($query1);
	
			if ($result1->num_rows) {
				while ($riga1=$result1->fetch_array()) {
					$id_rep=$riga1[id_rep];
					$lang=trim($riga1[lang]);
					$valore=trim($riga1[valore]);
					
					if ($nome=="identifier") {
						switch ($encode) {
							case "LOM":
								break;
						
							case "IMS":
								$nome="catalogentry";
								break;
						};
					};
					
					$xml.="<$nome>\n";
	
					$query2="SELECT * FROM lo_schema WHERE id_lom_sup='$id_lom'  AND id_profile='$id_profile' ORDER BY id_lom";
					$result2=$mysqli->query($query2);
					if ($result2->num_rows) {
						xml_lom($id_lo,$id_profile,$id_lom,$id_rep);
					} else {
						if ($langstring) {
							switch ($encode) {
								case "LOM":
									$xml.="<string language=\"$lang\">$valore</string>\n";
									break;
								case "IMS":
									$xml.="<langstring xml:lang=\"$lang\">$valore</langstring>\n";
									break;
							};
							
							$query_l="SELECT * FROM lo_metadata_valore WHERE id_rep='$id_rep' ORDER BY n";
							$result_l=$mysqli->query($query_l);
							$k=1;
							while ($riga_l=$result_l->fetch_array()) {
								$lang=trim($riga_l[lang]);
								$valore=trim($riga_l[valore]);
								
								switch ($encode) {
									case "LOM":							
										$xml.="<string language=\"$lang\">$valore</string>\n";
									break;
									case "IMS":
										$xml.="<langstring xml:lang=\"$lang\">$valore</langstring>\n";
									break;
								};
								$k++;
							};
							
						} else {
							switch ($tipocampo) {
							case "text":
								switch ($encode) {
									case "LOM":							
										$xml.="$valore\n";
										break;
										
									case "IMS":
										if ($nome=="entry") {
											$xml.="<langstring xml:lang=\"en\">$valore</langstring>\n";
										} else {
											$xml.="$valore\n";
										};
										break;
								};
								
								break;
							
							case "textarea":
								switch ($encode) {
									case "LOM":							
										$xml.="$valore\n";
									break;
									case "IMS":
										if ($nome=="entry") {
											$xml.="<langstring xml:lang=\"en\">$valore</langstring>\n";
										} else {
											$xml.="$valore\n";
										};
									break;
								};
								break;
								
							case "select":
								if (strtolower($nome)<>"language") {
									switch($encode) {
										case "IMS":	$valore=strtoupper(substr($valore,0,1)).substr($valore,1,strlen($valore));
											$xml.="<source>\n<langstring xml:lang=\"en\">LOMv1.0</langstring>\n</source>\n<value>\n<langstring xml:lang=\"x-none\">$valore</langstring>\n</value>\n";
											break;
										case "LOM":
											$xml.="<source>LOMv1.0</source>\n<value>$valore</value>";
											break;
									};
								} else {
									$xml.="$valore\n";
								};
								break;
							};
						};	
						
						
					}
					$xml.="</$nome>\n";
				
				};
			}; 
		};

};

function xml_lo($id_lo,$id_profile) {
	global $xml;
	
	$encode="IMS";
	
	switch ($encode) {
	case "LOM":
	
		$xml="<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?> 
<lom xmlns=\"http://ltsc.ieee.org/xsd/LOM\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchemainstance\" xsi:schemaLocation=\"http://ltsc.ieee.org/xsd/LOM http://ltsc.ieee.org/xsd/lomv1.0/lom.xsd\">\n";
		break;

	case "IMS":
		$xml="<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>
<lom xmlns=\"http://www.imsglobal.org/xsd/imsmd_v1p2\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.imsglobal.org/xsd/imsmd_v1p2 imsmd_v1p2p2.xsd\">\n";
		break;
	};

	xml_lom($id_lo,$id_profile);

	$xml.="</lom>";

};
?>

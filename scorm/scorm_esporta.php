<html>
<head><title>prova esporta corso scorm</title>
</head>
<body>
<?php
$DBHOST = "localhost";
$DBUSER = "g_user_db";
$DBPWD = "gara29mond";

if (!$cod_area) $cod_area="kairos_area_corsi";

$DBASE = $cod_area;
$PATH_ROOT="/var/www/html/prototipo/";
$PATH_PAGINE = "/var/www/html/prototipo/kairos/materiali/$cod_area/";
$PATH_MEDIA = "/var/www/html/prototipo/kairos/materiali_img/$cod_area/";
$PATH_ARCHIVI = "/var/www/archivi/kairos/materiali/cod_area";
//require "../include/funzioni_sito.inc";

/*******************************/
// FUNZIONI
/*******************************/
function getmimetype( $file_name )
{
	$est = substr($file_name,-3);

	switch (strtolower($est)) {
		case "zip":
			return "application/zip";
			break;

		case "exe":
			return "application/octet-stream";
			break;

		case "xls":
			return "application/excel";
			break;

		case "doc":
			return "application/msword";
			break;		

		case "pdf":
			return "application/pdf";
			break;					

		case "rtf":
			return "application/rtf";
			break;		

		case "jpg":
			return "image/jpeg";
			break;

		case "gif":
			return "image/gif";
			break;

		case "mid":
			return "audio/midi";
			break;	

		case "mp3":
			return "audio/mpeg";
			break;						

		case "ra":
			return "audio/x-realaudio";
			break;	

		case "ram":
			return "audio/x-pn-realaudio";
			break;	

		case "wav":
			return "audio/x-wav";
			break;	

		case "avi":
			return "audio/x-msvideo";
			break;
			
		case "htm":
			return "text/html";			
			break;

		case "txt":
			return "text/plain";			
			break;			

		case "mpg":
			return "video/mpeg";			
			break;

		case "mov":
			return "video/quicktime";			
			break;

		default:
			return "application/octet-stream";
	};
};

function log_errore($errore) {
	$fp=fopen("/var/www/html/prototipo/kairos_error.log","a");
	fwrite($fp,$errore."\r\n");
	fclose($fp);
};

function vocali_accentate_off($stringa) {
	$stringa=str_replace("ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½","a'",$stringa);
	$stringa=str_replace("ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½","e'",$stringa);
	$stringa=str_replace("ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½","i'",$stringa);
	$stringa=str_replace("ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½","o'",$stringa);
	$stringa=str_replace("ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½","u'",$stringa);
	return $stringa;
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

function aggiungi_asset($id_asset,$tipo,$path_originale,$path_sco) {
	global $lista_asset,$stringa_asset;
	
	if (!in_array($id_asset,$lista_asset)) {
		$lista_asset[]=$id_asset;
		$lista_asset_tipo[]=$tipo;
		$lista_asset_path0[]=$path_originale;
		$lista_asset_path1[]=$path_sco;
		$stringa_asset .= "
		<resource identifier=\"$id_asset\" type=\"webcontent\"
          adlcp:scormtype=\"asset\" href=\"$path_sco\">
		  <file href=\"$path_sco\" />
		</resource>
		";
	};
};
	
	
function elenco_asset($id_la) {
	global $DBASE,$DBUSER,$DBPWD;
	global $PATH_PAGINE,$PATH_MEDIA,$PATH_ROOT,$PATH_ARCHIVI;
	global $sco_asset,$id_sco;
	
	$db = mysql_connect("localhost",$DBUSER,$DBPWD);
	mysql_select_db($DBASE,$db);	

	$query = "SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_la' ORDER BY posizione";
	$result=$mysqli->query($query);
	$stringa = "";
	while ($risorsa = $result->fetch_array()) {
		$id_asset=$risorsa["id_risorsa"];
		$tipo=$risorsa["tipo"];
		$titolo=$risorsa["titolo"];
		
		if ($tipo==4) {
			$id_asset=$risorsa[id_gruppo];
		};
		
	
		if ($tipo==1) {
			if (!in_array($id_asset,$sco_asset[$id_sco])) {
				$stringa .= "
		<dependency identifierref=\"$id_asset\" />
			";
				$sco_asset[$id_sco][]=$id_asset;
				$path_sco="risorse/media/$titolo";
				$path_originale=$PATH_ARCHIVI.$titolo;
				echo "$path_originale - $path_sco<br>";
				aggiungi_asset($id_asset,"media",$path_originale,$path_sco);
					
			};
		};

		if ($tipo==2) {
	 		$stringa .= "		".elenco_asset($id_asset)."\n"; 
	 	}
		
		if ($tipo==4 or $tipo==0 or $tipo==3) {
			if (!in_array($id_asset,$sco_asset[$id_sco])) {
				$stringa .= "
		<dependency identifierref=\"$id_asset\" />
			";
				$sco_asset[$id_sco][]=$id_asset;
				$path_sco="risorse/$id_asset".".htm";
				$path_originale=$PATH_PAGINE.$id_asset.".inc";
				echo "$path_originale - $path_sco<br>";
				aggiungi_asset($id_asset,"html",$PATH_PAGINE,$path_sco);
			};
			$stringa .= "		".asset_linkati($id_asset)."\n"; 
		}; 	
	};
	
	return $stringa;
};
	
function asset_linkati($id_risorsa) {
	global $PATH_PAGINE,$PATH_MEDIA,$PATH_ROOT,$PATH_ARCHIVI;
	global $sco_asset,$id_sco;
	
	$pagina=$PATH_PAGINE.$id_risorsa.".inc";
	$contenuto="";
	$stringa="";
	if (file_exists($pagina)) {
		$contenuto = join('',file($pagina));
		$stringa .= parse($contenuto,"href");
		$stringa .= parse($contenuto,"src");
	};
	
	return $stringa;
};


function parse($contenuto,$pattern) {
	global $PATH_PAGINE,$PATH_MEDIA,$PATH_ROOT;
	global $sco_asset,$id_sco;
	$stringa="";
	$position = multi_strpos($pattern, $contenuto);
	
	if ($position) {
  		while (list($index, $pos) = each($position)) {
			$i=0;
			$carattere=substr($contenuto,$pos+$i,1);
			
			$j=$pos+$i;
			
			while ($carattere<>'=' and $j<strlen($contenuto)) {
				$i++;
				$j=$pos+$i;
				$carattere=substr($contenuto,$pos+$i,1);
				
			};	
			if ($carattere=='=') {
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
	
				if (eregi("http:\/\/www.garamond.it",$link) or ereg("materiali_browse\.php\?risorsa",$link) or ereg("materiali_img",$link) or ereg("http:\/\/www.garamond.it\/(.+)\/img",$link)) {
					$id_asset_base=basename($link);
					$id_asset=basename($link);
					
					$path_sco="";
					if (ereg("materiali_browse\.php\?risorsa\=(.+)$",$id_asset,$parti)) {
						$id_asset=$parti[1];
						//devo controllare il tipo risorsa
						$path_sco="risorse/$id_asset".".htm";
					};
				
					$id_asset=str_replace(".","_",$id_asset);
				
					
				
					if (!in_array($id_asset,$sco_asset[$id_sco])) {
						$sco_asset[$id_sco][]=$id_asset;
						if (!$path_sco) {
							if (getmimetype($id_asset_base)=="text/html") {
								$path_sco="risorse/$id_asset_base";
								$tipo="html";
							} else {
								$path_sco="risorse/media/$id_asset_base";
								$tipo="media";
							};
						};	
						$prendi=true;
						$path_originale=str_replace("http://www.garamond.it/",$PATH_ROOT,$link);
						if (($link=="http://www.garamond.it") or  ($link=="http://www.garamond.it/") or ($pattern=='href' and !eregi("/var/www/html/prototipo/kairos",$link))) $prendi=false;

				
						if ($prendi) {
							echo "$path_originale - $path_sco<br>";
							$stringa .= "
		<dependency identifierref=\"$id_asset\" />
			";
							aggiungi_asset($id_asset,$tipo,$path_originale,$path_sco);
						};
					};
				};
			};
		};
	};
	return $stringa;
};


/*******************************/
// INIZIO PROCEDURA 
/*******************************/
$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);			

$id_cartella=$_REQUEST["id_cartella"];
$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];

$query="SELECT descrizione FROM corso WHERE id_corso='$id_corso' LIMIT 1";
$result=$mysqli->query($query);

//echo $DBASE." ".$cod_area." ".mysql_error();

$riga=$result->fetch_array();
$titolo_corso=vocali_accentate_off($riga["descrizione"]);

$id_manifest=$id_corso."_".$id_edizione."_Manifest";

$preambolo="<?xml version=\"1.0\"?>
<manifest identifier=\"$id_manifest\" version=\"1.0\"
          xmlns=\"http://www.imsproject.org/xsd/imscp_rootv1p1p2\"
          xmlns:adlcp=\"http://www.adlnet.org/xsd/adlcp_rootv1p2\"
          xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
          xsi:schemaLocation=\"http://www.imsproject.org/xsd/imscp_rootv1p1p2 imscp_rootv1p1p2.xsd
                              http://www.imsglobal.org/xsd/imsmd_rootv1p2p1 imsmd_rootv1p2p1.xsd
                              http://www.adlnet.org/xsd/adlcp_rootv1p2 adlcp_rootv1p2.xsd\">
   
   <metadata/>
";
   
$manifest=$preambolo;

$id_org=$id_corso."_".$id_edizione."_1";

$manifest .= "
<!-- ***************************** -->
<!-- STRUTTURA DEL LEARNING OBJECT -->
<!-- ***************************** -->
<organizations default=\"$id_org\">
	<organization identifier=\"$id_org\">
		<title>$titolo_corso</title>
";


if ($id_cartella) {
	$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_risorsa='$id_cartella' ORDER BY ordine";
} else {
	$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' ORDER BY ordine";
};
   
$result=$mysqli->query($query);

while ($la = $result->fetch_array() ) {
	$id_la=$la["id_risorsa"];
	$tipo=$la["tipo_risorsa"];
	if ($tipo==2) {
		$id_sco_default="sco_".$id_la;
	 	
		$elenco_sco[]=$id_sco_default;
		
		$query_t="SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_la' LIMIT 1";
		$result_t=$mysqli->query($query_t);
		$riga_t=$result_t->fetch_array();
		$titolo_la=$riga_t["titolo"];
		$titolo_la=vocali_accentate_off($titolo_la);
		$manifest .= "<item identifier=\"$id_la\" identifierref=\"$id_sco_default\" isvisible=\"true\">
            <title>$titolo_la</title> 
	 		</item>
		";
	};
};
$manifest .= "
	</organization>
</organizations>
";

if (count($elenco_sco)) {
	$manifest .= "
<!-- ********************* -->
<!-- DEFINIZIONE DEGLI SCO -->	
<!-- ********************* -->
<resources>
	";
};

$lista_asset=array();
$stringa_asset="";

for ($i=0;$i<count($elenco_sco);$i++) {
	$id_sco=$elenco_sco[$i];
	$sco_asset[$id_sco]=array();
	$id_la=substr($id_sco,4,strlen($id_sco)-1);
	$id_asset_default=$id_sco.".htm";
	$manifest .= "
	<resource identifier=\"$id_sco\" type=\"webcontent\"
          adlcp:scormtype=\"sco\" href=\"risorse/$id_asset_default\">
	";
	$manifest .= "
		<file href=\"risorse/$id_asset_default\" />
		";
		
	$manifest .= "
		<dependency identifierref=\"SCOnav_js\" />
		<dependency identifierref=\"SCOAPI_js\" />
		";	
		
	$manifest .= elenco_asset($id_la);
	$manifest .= "
	</resource>
		";			
};	
$manifest .=" 
<!-- ******************** -->
<!-- DETTAGLI DEGLI ASSET -->
<!-- ******************** -->
";

$stringa_asset .= "
		<resource identifier=\"SCOnav_js\" type=\"webcontent\"
          adlcp:scormtype=\"asset\" href=\"risorse/SCOnav.js\">
		  <file href=\"risorse/SCOnav.js\" />
		</resource>
		<resource identifier=\"SCOAPI_js\" type=\"webcontent\"
          adlcp:scormtype=\"asset\" href=\"risorse/SCOAPI.js\">
		  <file href=\"risorse/SCOAPI.js\" />
		</resource>
		";
		
$manifest .= $stringa_asset;

if (count($elenco_sco)) {
	$manifest .= "
</resources>
	";
};

$manifest .= "
</manifest>";

$fp=fopen("./imsmanifest.xml","w");
fwrite($fp,$manifest);
fclose($fp);

?>
Manifest esportato: <a href=imsmanifest.xml>imsmanifest.xml</a>
<?php 
/*
echo "<br><br>";
for ($i=0;$i<count($lista_asset);$i++) {
	echo $lista_asset[$i]." ".$lista_asset_tipo[$i]." ".$lista_asset_path0[$i]." ".$lista_asset_path1[$i]."<br>";
};
*/
?>
</body>
</html>

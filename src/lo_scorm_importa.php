<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_risorsa=uniqid("lo_");
$id_autore=$_REQUEST["id_autore"];
$url0=trim($_REQUEST["url"]);
$titolo0=trim($_REQUEST["titolo"]);

$width=$_REQUEST["width"];
$height=$_REQUEST["height"];

$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];
$file=$_FILES["file"]["tmp_name"];
$file_size=$_FILES["file"]["size"];
$file_name=$_FILES["file"]["name"];
$file_type=$_FILES["file"]["type"];

$errore="";
if ($file_size > $MAX_FILE_SIZE) {
	$errore .= "<br>il file eccede la dimensione massima";
};
									
if ($errore) {
	$msg=str_replace(" ","%20",$errore);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

if ($file_name) {
	$file_name = trim($file_name);
	$file_name = str_replace(" ","",$file_name);
	//$file_name = strtolower($file_name);
	$est = substr($file_name,-3);
	$nome_base=substr($file_name,0,-4);
	if ($est=="zip") {

		$path_file=$PATH_ROOT_FILE."materiali/$cod_area/$id_risorsa";
		if (!file_exists($path_file)) {
			mkdir($path_file,0777);
		};
		
		$fullpath = $path_file."/".$file_name;
		if(!file_exists($file)) die("file does not exist");
		copy($file,$fullpath);	
		//$comando="/usr/bin/unzip $fullpath -d $path_file > /dev/null";

		
			$zip = new ZipArchive();
			if($zip->open($fullpath)=== true){
				 $zip->extractTo($path_file);
    			 $zip->close();
			}
		//shell_exec($comando);
		unlink($fullpath);
		
	};
}else {
    echo "The file has not been loader for some reason i cannot indentify";
    echo $_FILES['file']['error'];
    exit();
}

if ($file_name) {

//$id_risorsa="lo_43fed7ab4f289";
//$id_risorsa="lo_43fee79adfa42";
$manifest_file="";

$path_inizio=$PATH_ROOT_FILE."materiali/$cod_area/$id_risorsa/";

//$manifest_file=$PATH_ROOT_FILE."materiali/$cod_area/$id_risorsa/$nome_base/imsmanifest.xml";
$path0=$path_inizio;
$path_file=$path0."imsmanifest.xml";
$trovato=true;
if (!file_exists($path_file)) {
	$trovato=false;
	$d = dir($path0);
	while ($filename=$d->read() and !$trovato) {
		if (($filename != '.') && ($filename != '..')) { 
			$path0=$path0.$filename;
			if (is_dir($path0)) {
				$path_file=$path0."/imsmanifest.xml";
				if (file_exists($path_file)) {
					$trovato=true;
				};
			};
		};
	};
	$d->close();
};

if ($trovato) {
	$manifest_file=$path_file;
} else {
	$msg="Non riesco ad aprire il file imsmanifest.xml $path_file";
	$msg=str_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};


$tabledraw=false;  
$wrap=true; 
$tablewidth=255;  

$items = array();
$resources = array();
$defaultorgref='';
$defaultorgtitle='';
$version='0.0';
$inorg=false; 
$intitle=$inmeta=$ingeneral=$inresource=false;
$inversion=false;
$prereq=false;
$initem=0; 
$itemindex=0;
$resourceindex=0;
$previouslevel=1;
$clusterinfo=0;

};


function put_it_to_items($ident,$href) { 
	global $items;
	$i=1;
	while ($items[$i]) {
		if ($items[$i]['identifierref']==$ident) { $items[$i]['href']=$href; }
		$i++;
	}
}

function startElement($parser, $name, $attribs)
{
   global $xml_parser, $defaultorgref, $defaultorgtitle, $inorg, $initem, $intitle, $inmeta, $inresource, $items, $itemindex, $resources, $resourceindex, $tabledraw, $inversion, $prereq, $previouslevel, $clusterinfo, $ingeneral;

   if ($tabledraw) {
     echo "<tr><td>";
     echo xml_get_current_line_number($xml_parser);
     echo "</td><td>$inorg</td><td>$initem</td>";
   }

   if ($name=='ORGANIZATIONS') {
    list($key, $value) = each($attribs);
    $defaultorgref=$value;
   }
   if (($name=='ORGANIZATION') or ($name=='tableofcontents')) {
    $inorg=true;
   }
   if ($name=='SCHEMAVERSION') {
    $inversion=true;
   }
   if ($name=='ADLCP:PREREQUISITES') {
    $prereq=true;
   }
   if ($name=='METADATA') {
    $inmeta=true;
   }
   if ($name=='GENERAL') {
    $ingeneral=true;
   }


   if ($name=='ITEM') {
	  $initem++;
	  $itemindex++;
      while (list($key, $value) = each($attribs)) {
		if ($key=='IDENTIFIERREF') { $items[$itemindex]['identifierref']=$value;  }
		if ($key=='IDENTIFIER') { $items[$itemindex]['identifier']=$value;  }
		if ($key=='PARAMETERS') { $items[$itemindex]['parameters']=$value;  }
		if ($key=='TITLE') { $items[$itemindex]['title']=$value; }
	  }
 	  $items[$itemindex]['index']=$itemindex;
 	  $items[$itemindex]['level']=$initem;

	  if ($initem==$previouslevel) { $clusterinfo++; }
	  if ($initem>$previouslevel) { $clusterinfo=$clusterinfo*10+1; $previouslevel=$initem; }
	  if ($initem<$previouslevel) { $clusterinfo=floor($clusterinfo/10)+1; $previouslevel=$initem; }
	  $items[$itemindex]['clusterinfo']=$clusterinfo;
   }
   if ($name=='TITLE') {
	$intitle=true;
   }
   if ($name=='RESOURCE') {  
   	  $resourceindex++;
      while (list($key, $value) = each($attribs)) {
		if ($key=='HREF') { $href=$value;  }
		if ($key=='IDENTIFIER') { $ident=$value;  }
	  }
	  put_it_to_items($ident,$href);
	  $resources[$resourceindex]['identifier']=$ident;
	  $resources[$resourceindex]['href']=$href;
	  $inresource=true;
   }

   reset($attribs); 
   if ($tabledraw) {
     echo "<td><font color='#0000cc'>$name</font></td>";
     if (sizeof($attribs)) {
         while (list($k, $v) = each($attribs)) {
             echo "<td><font color='#009900'>$k</font>=<font color='#990000'>$v</font></td>";
         }
     }
   }

}

function endElement($parser, $name)
{
   global $inorg,$initem,$inmeta,$ingeneral,$intitle,$inversion,$inresource,$prereq;

   if (($name=='ORGANIZATION') or ($name=='tableofcontents')) {
	$inorg=false;
   }
   if ($name=='ITEM') {
	$initem--;
   }
   if ($name=='RESOURCE') {
	$inresource==false;
   }
   if ($name=='METADATA') {
	$inmeta==false;
   }
   if ($name=='GENERAL') {
	$ingeneral==false;
   }
   if ($name=='TITLE') {
	$intitle=false;
   }
   if ($name=='SCHEMAVERSION') {
	$inversion=false;
   }
   if ($name=='ADLCP:PREREQUISITES') {  //this is only good for scorm 1.2
		$prereq=false;
   }

}

function characterData($parser, $data)

{
   global $defaultorgtitle, $initem, $intitle, $inmeta, $inorg, $items, $itemindex, $resource,$resourceindex,$inversion, $version, $prereq, $ingeneral,$inresource;
   if (($intitle==true) and ($inorg==true) and ($initem==false) and ($ingeneral==false)) {
	    $defaultorgtitle.=$data;
        return;
   }
   if (($intitle==true) and ($initem==true)) {
		$items[$itemindex]['title'].=$data;
		return;
 	}
   if ($inversion==true) {
		$version=$data; 
		return;
 	}
   if ($prereq==true) {
		$items[$itemindex]['prereq']=$data;
	}

}

function new_xml_parser($request_file)
{
   global $parser_file;

   $xml_parser = xml_parser_create();
   xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, 1);
   xml_set_element_handler($xml_parser, "startElement", "endElement");  
   xml_set_character_data_handler($xml_parser, "characterData");

   if (!($fp = @fopen($request_file, "r"))) {
       return false;
   }
   if (!is_array($parser_file)) {
       settype($parser_file, "array");
   }
   $parser_file[$xml_parser] = $request_file;
   return array($xml_parser, $fp);
}

//INIZIO PARSING

if ($file_name) {

if (!(list($xml_parser, $fp) = new_xml_parser($manifest_file))) {
	$msg="Non riesco ad aprire il file imsmanifest.xml $manifest_file";
	$msg=str_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
}


if ($tabledraw) {
  echo "<table border='1'>"
		."<tr>"
			."<td>Row</td>"
			."<td>Inorg</td>"
			."<td>Initem</td>"
			."<td>Tag name</td>"
			."<td>Attributes</td>"
		."</tr>";
}


while ($data = fread($fp, 4096)) {  
   if (!xml_parse($xml_parser, $data, feof($fp))) {
       echo "Most likely the zip contains invalid characters, please check to content and manually remove them";
       die(sprintf("XML error: %s at line %d\n",
                   xml_error_string(xml_get_error_code($xml_parser)),
                   xml_get_current_line_number($xml_parser)));

   }
}

if ($tabledraw) {
  echo "</table>";  
  echo "parse complete<br /><hr />";  
  echo "<br />Total lines in xml file : ";
  echo xml_get_current_line_number($xml_parser);  
  echo " (xml_get_current_line_number)";  
  echo "<br /><br />";
}

if ($tabledraw) {
    echo "<br /><br /><hr /><br />";
    $i=1;
    while ($resources[$i]) {
        echo "Identifier : {$resources[$i]['identifier']} "
            ."Href : {$resources[$i]['href']}<br />\n";
        $i++;
    }
    echo "<br />\n";  
};

}; //FINE PARSING


//$url=$PATH_ROOT."materiali/$cod_area/$id_risorsa/$nome_base/".urlencode($items[1]['href']);
//$url=$PATH_ROOT."materiali/$cod_area/$id_risorsa/".urlencode($items[1]['href']);


if ($file_name) {

$url=dirname($manifest_file)."/".urlencode($items[1]['href']);
$url=str_replace($PATH_ROOT_FILE,$PATH_ROOT,$url);
$titolo= $mysqli->real_escape_string($items[1]['title']);

//echo "$url - $titolo - ".$items[1]['href'];
xml_parser_free($xml_parser);
fclose($fp);
} else {
	if (!$url) {
		$msg="Non hai specificato l'url dello SCO";
		$msg=str_replace(" ","%20",$msg);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
	} else {
		$url=$url0;
		$titolo= $mysqli->real_escape_string($titolo0);
	};
};

$id_utente = $kairos_cookie["0"];


$query="SELECT max(posizione) AS num_pag FROM risorse_materiali WHERE risorsa_padre='root'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$posizione=$riga[num_pag]+1;

$query = "INSERT INTO risorse_materiali 		
			SET 
				id_risorsa='$id_risorsa',
				posizione='$posizione',
				titolo='$titolo',
				data_crea=now(),
				id_editor='$id_utente',
				id_autore='$id_autore',
				tipo='20',
				risorsa_padre='root',
				url='$url'";
if(!$result=$mysqli->query($query)) die($mysqli->error);

$ruolo=ruolo_utente($id_utente);
if ($ruolo=='admin') {
	$query = "SELECT id_risorsa FROM risorse_materiali WHERE risorsa_padre='root'";
} else {
	$query = "SELECT id_risorsa FROM risorse_materiali WHERE risorsa_padre='root' AND id_editor='$id_utente'";
};
$result=$mysqli->query($query);
$tot_righe=$result->num_rows;
$pag_size=20;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) == 0) $tot_pag++;

$query="INSERT INTO materiale_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='creato',"
." data_evento=NOW()";
$mysqli->query($query);

$query="INSERT INTO lo SET"
." id_lo='$id_risorsa',"
." id_profile='lom_garamond',"
." stato='0',"
." width='$width',"
." height='$height',"
." lo_url='$url',"
." lo_tipo='2'";
if(!$result=$mysqli->query($query)) die($mysqli->error);

Header("Location:index.php?risorsa=repository_index&pagina=$tot_pag&id_cartella=root");
?>

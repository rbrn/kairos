<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
require "./include/funzioni_forum.inc";



$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	



if ( !isset($kairos_cookie[0]) ){
	$query = $_SERVER["QUERY_STRING"];
	$PHP_SELF=$_SERVER["PHP_SELF"];
	if ($query) {
		$url = "$PHP_SELF?$query";
	} else {
		$url ="$PHP_SELF";
	};
	$location="Location: $PATH_ROOT"."index.php?risorsa=do_login&url=$url";
	Header($location);
	exit();
};


$id_utente=$kairos_cookie[0];
$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];
$oggetto=$_REQUEST["oggetto"];
$testo=$_REQUEST["testo"];
$icona_post=$_REQUEST["icona_post"];
$repemail=$_REQUEST["repemail"];
$delallegato=$_REQUEST["delallegato"];
$ex_nome_file=$_REQUEST["ex_nome_file"];
$nome_file=$_FILES["nome_file"]["tmp_name"];
$nome_file_size=$_FILES["nome_file"]["size"];
$nome_file_name=$_FILES["nome_file"]["name"];
$nome_file_type=$_FILES["nome_file"]["type"];


$query2 = "SELECT * FROM forum WHERE id_forum='$id_forum'";
$result2=$mysqli->query($query2);
$dati_forum=$result2->fetch_array();


if (!$dati_forum) {
	$errore="<p>$stringa[errore_no_forum]: <b>$id_forum</b></p>";
	$msg=ereg_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

refresh_utente($id_utente);


if (!$oggetto) {
	$oggetto=$stringa[senza_oggetto];
	};


if ($nome_file_name) {
	if ($ex_nome_file) {
		$file = $PATH_ARCHIVI."forum/".$ex_nome_file;
		if (file_exists($file)) unlink($file);
	};

	$nome_file_name = trim($nome_file_name);
	$nome_file_name = str_replace(" ","",$nome_file_name);
	$nome_file_name = strtolower($id_utente)."_".$nome_file_name;
	$fullpath = $PATH_ARCHIVI."forum/".$nome_file_name;

	if (file_exists($nome_file)) {
		copy($nome_file,$fullpath);	
		$est = substr($fullpath,-3);
		if ($est<>"zip") {
		
			$cur_dir=getcwd();
			chdir($PATH_ARCHIVI."/forum");
					
			$fullpath_zip=substr($fullpath,0,strlen($fullpath)-3)."zip";
			$nome_file_zip=substr($nome_file_name,0,strlen($nome_file_name)-3)."zip";
			
			if (file_exists($fullpath_zip)) {
				unlink($fullpath_zip);
			};
			
			$zip = new ZipArchive();
			if($zip->open($nome_file_zip, ZIPARCHIVE::CREATE)){
				$zip->addFile($nome_file_name, $nome_file_name);
				$zip->close();	
				 
			}
						
			//$comando="/usr/bin/zip -D -q $nome_file_zip $nome_file_name";
			//exec($comando);
			chdir($cur_dir);
			
		
			unlink($fullpath);
			$nome_file_name=$nome_file_zip;
			$nome_file_size=filesize($fullpath_zip);
			$nome_file_type="application/x-zip-compressed";
		}	
	} else {
		$nome_file_name="";	
		$nome_file_size=0;
		$nome_file_type="";		
	};	
};


if ($delallegato) {
	$query = "UPDATE forum_posts SET
nome_file=NULL,
file_size=0,
file_type=NULL
WHERE id_forum='$id_forum' AND id_post='$id_post'";	
	$result=$mysqli->query($query);
	$file = $PATH_ARCHIVI."forum/".$ex_nome_file;
	if (file_exists($ile)) unlink($file);
};

if ($nome_file_name) {
	$query = "UPDATE forum_posts SET
oggetto='$oggetto',
testo='$testo',
data_last_mod=NOW(),
repemail='$repemail',
icona_post='$icona_post',
nome_file='$nome_file_name',
file_size='$nome_file_size',
file_type='$nome_file_type'
WHERE id_forum='$id_forum' AND id_post='$id_post'";	
} else {
	$query = "UPDATE forum_posts SET
oggetto='$oggetto',
testo='$testo',
data_last_mod=NOW(),
repemail='$repemail',
icona_post='$icona_post'
WHERE id_forum='$id_forum' AND id_post='$id_post'";	
};
$result = $mysqli->query($query);


if ($vista=='data') {
	$id_start=$id_post;
} else {
	$id_start=ascendente($id_post);
};

$url="index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_post&vista=$vista&modo=$modo&pagina=$pagina";
Header("Location: $url");
?>

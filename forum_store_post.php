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
$oggetto=mysql_real_escape_string($_REQUEST["oggetto"]);
$testo=mysql_real_escape_string($_REQUEST["testo"]);
$icona_post=mysql_real_escape_string($_REQUEST["icona_post"]);
$repemail=mysql_real_escape_string($_REQUEST["repemail"]);
$mid=mysql_real_escape_string($_REQUEST["mid"]);
$nome_file=$_FILES["nome_file"]["tmp_name"];
$nome_file_size=$_FILES["nome_file"]["size"];
$nome_file_name=$_FILES["nome_file"]["name"];
$nome_file_type=$_FILES["nome_file"]["type"];

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query2 = "SELECT * FROM forum WHERE id_forum='$id_forum'";
$result2=$mysqli->query($query2);
$dati_forum=$result2->fetch_array();
$descr_forum=$dati_forum[descrizione];

if (!$dati_forum) {
	$errore="<p>$stringa[errore_no_forum]: <b>$id_forum</b></p>";
	$msg=ereg_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

refresh_utente($id_utente);
$errore = ""; 

		
if ($nome_file_size > $MAX_FILE_SIZE) {
		$errore .= "<br>$stringa[errore_max_file]";
};

if (!$oggetto) {
	$oggetto=$stringa[senza_oggetto];
};


if ($errore) {
	$msg=ereg_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$msg");
	exit();	
};

if ($nome_file_name) {
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
			//$comando="/usr/bin/zip -D -q $nome_file_zip $nome_file_name";
			//exec($comando);
			
			
			
			$zip = new ZipArchive();
			if($zip->open($nome_file_zip, ZIPARCHIVE::CREATE)){
				$zip->addFile($nome_file_name, $nome_file_name);
				$zip->close();	
			}
			
			chdir($cur_dir);
			unlink($fullpath);
			$nome_file_name=$nome_file_zip;
			//$nome_file_size=filesize($nome_file_zip);
			$nome_file_type="application/x-zip-compressed";
		}	
	}





	else {
		$nome_file_name="";	
		$nome_file_size=0;
		$nome_file_type="";		
	};	
};

if ($opera) {
	//$testo=parse_code($testo);
	$testo=parse_link($testo);
	$testo=nl2br($testo);
};

$query="INSERT INTO forum_posts (id_forum,id_post_padre,data_post,id_autore,oggetto,testo,nome_file,file_size,file_type,repemail,icona_post,id_corso,id_edizione,id_gruppo,data_last_mod) VALUES ('$id_forum','$id_post_padre',NOW(),'$id_utente','$oggetto','$testo','$nome_file_name','$nome_file_size','$nome_file_type','$repemail','$icona_post','$id_corso_s','$id_edizione_s','$id_gruppo_s',NOW())";
$result = $mysqli->query($query);

if (!$result) {
	$errore="<p>".mysql_error()."</p>";
	$msg=ereg_replace(" ","%20",$errore);
	header("Location:index.php?risorsa=msg&msg=$msg");
	exit();	
};

$query = "SELECT max(id_post) as max_id FROM forum_posts WHERE id_forum='$id_forum'";
$result=$mysqli->query($query);
$max_id = $result->fetch_array();
$id_post=$max_id["max_id"];

if ($id_post_padre <> '0') {
	$id_0 = ascendente($id_post_padre);
	$query="UPDATE forum_posts SET data_last_mod=NOW() WHERE id_post='$id_0'";
	$result=$mysqli->query($query);

	$query = "SELECT id_autore,repemail FROM forum_posts WHERE id_forum='$id_forum' AND id_post='$id_post_padre'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	$id_autore = $riga["id_autore"];

	if ($riga["repemail"]) {
			mysql_select_db($DBASE_UTENTI,$db);	
			$query_u="SELECT email FROM utenti WHERE id_utente='$id_autore'";
			$result_u=$mysqli->query($query_u);
			$dati_autore = $result_u->fetch_array();
			mysql_select_db($DBASE,$db);	
			$email_padre = $dati_autore["email"];
			$email_autore=$dati_autore["email"];	
			$oggetto = "Kairos notifica replica forum: $oggetto";	
			$oggetto = stripslashes($oggetto);

			$testo = "$stringa[ricevuto_replica]: $descr_forum ($id_forum)

			$stringa[leggi_replica]: ".$PATH_ROOT."index.php?cod_area=$cod_area&risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_post";
			$testo = stripslashes($testo);
			$id_package=uniqid("");			mail_job($id_package,"$email_padre","$oggetto","$testo","$email_autore","$email_autore","");

	//mail("$email_padre","$oggetto","$testo","From:$email_autore\nReply-To:$email_autore");
	};
};

/*
if ($id_autore=='iuli') {
	mysql_select_db($DBASE_UTENTI,$db);	
			$query_u="SELECT email FROM utenti WHERE id_utente='$id_autore'";
			$result_u=$mysqli->query($query_u);
			$dati_autore = $result_u->fetch_array();
			mysql_select_db($DBASE,$db);	
			$email_padre = $dati_autore["email"];
			$email_autore=$dati_autore["email"];	
			$oggetto = "Kairos notifica replica forum: $oggetto";	
			$oggetto = stripslashes($oggetto);

			$testo = "$stringa[ricevuto_replica]: $descr_forum ($id_forum)

			$stringa[leggi_replica]: ".$PATH_ROOT."index.php?cod_area=$cod_area&risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_post";
			$testo = stripslashes($testo);
	mail("fleo@espertoweb.it","$oggetto","$testo","From:$email_autore\nReply-To:$email_autore");
}
*/
//marco l'intervento come letto dall'utente
mysql_select_db($DBASE,$db);	

$query="INSERT INTO forum_read(id_post,id_forum,id_utente,data_read,azione,id_corso,id_edizione,id_gruppo) VALUES ('$id_post','$id_forum','$id_utente',NOW(),'creato','$id_corso_s','$id_edizione_s','$id_gruppo_s')";
/*
$query="INSERT INTO forum_read(id_post,id_forum,id_corso,id_edizione,id_gruppo,id_utente,data_read,azione) VALUES ('$id_post','$id_forum','$id_corso_s','$id_edizione_s','$id_gruppo_s','$id_utente',NOW(),'creato')";
*/
$result = $mysqli->query($query);

if ($vista=='data') {
	$id_start=$id_post;
} else {
	$id_start=ascendente($id_post);
};

if ($wimba_cookie=='on') {
	$query="INSERT INTO forum_audio(id_post,id_forum,mid) VALUES ('$id_post','$id_forum','$mid')";
    $result = $mysqli->query($query);
};


$query="SELECT utenti.email,utenti.id_utente FROM forum_mail,utenti WHERE forum_mail.id_utente=utenti.id_utente AND forum_mail.id_forum='$id_forum'";
$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {
	$email=$riga[email];
	$utente=$riga[id_utente];
	
	if ($utente<>$kairos_cookie[0]) {
		$oggetto = "Kairos notifica forum: $descr_forum";	
		$oggetto = stripslashes($oggetto);
		$testo = "$stringa[forum_scritto_post]: $descr_forum ($id_forum)
	$stringa[leggi_replica]: ".$PATH_ROOT."index.php?cod_area=$cod_area&risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_post";
		$testo = stripslashes($testo);
		$id_package=uniqid("");			mail_job($id_package,"$email","$oggetto","$testo","notifica@garamond.it","notifica@garamond.it","");
	};
};


//aggiorno il feed rss
mysql_select_db($DBASE);

if ($server_base) {
	$url="http://".$server_base;
} else {
	$url="http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com/kairos/".$cod_area_base;
};

$data = getdate();
$oggi=$data["year"]."-".$data["mon"]."-".$data["mday"];

$dforum=vocali_accentate_off($descr_forum);

$testo_rss="<?xml version=\"1.0\" encoding=\"UTF-8\" ?> 
<rss version=\"2.0\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:sy=\"http://purl.org/rss/1.0/modules/syndication/\" xmlns:admin=\"http://webns.net/mvcb/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:content=\"http://purl.org/rss/1.0/modules/content/\">
<channel>
<title>Corsi Garamond</title>
<link>$url</link>
<description>Forum: $dforum</description>
<copyright>Copyright 2005 - Garamond</copyright>
<language>it-IT</language> 
";
$query="SELECT * FROM forum_posts WHERE id_forum='$id_forum' and data_post>='$oggi' ORDER BY data_post DESC";
$result=$mysqli->query($query);
while ($riga=$result->fetch_array()) {
	$id_p=$riga[id_post];
	$id_autore=$riga[id_autore];
	$oggetto=htmlentities($riga[oggetto]);
	$data_post=$riga[data_post];
	
	$testo_msg=vocali_accentate_off(stripslashes($riga["testo"]));
	for ($i=0;$i<strlen($testo_msg);$i++) {
		$c=substr($testo_msg,$i,1);
		if (ord($c)<32 or ord($c)>125) 
			$testo_msg=str_replace($c,"",$testo_msg);
	};
	
	ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_post,$parti);
	$data_pub=date("r",mktime($parti[4],$parti[5],$parti[6],$parti[2],$parti[3],$parti[1]));
	
	$testo_rss.="
<item>
<title><![CDATA[$oggetto ($id_autore)]]></title>
<description><![CDATA[intervento scritto da: $id_autore]]></description>
<link>".$url."/index.php?risorsa=forum_mostra_post&amp;id_forum=$id_forum&amp;id_post=$id_p</link>
<content:encoded><![CDATA[$testo_msg]]></content:encoded>
<pubDate>$data_pub</pubDate>
</item>";
};

$testo_rss.= "</channel>
</rss>";

$feed_rss="./materiali/$cod_area/$id_forum".".xml";
$fd=fopen($feed_rss,"w");
fwrite($fd,$testo_rss);
fclose($fd);


$url="index.php?risorsa=forum_mostra_post&id_post=$id_post&&id_forum=".$id_forum."&vista=".$vista."&modo=".$modo."&pagina=$pagina";

Header("Location: $url");
?>

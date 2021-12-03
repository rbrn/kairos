<?php
if (!ereg('MSIE',$_SERVER["HTTP_USER_AGENT"]) or !ereg('Windows',$_SERVER["HTTP_USER_AGENT"])) {
	$win_ie=false;
} else {	
	$win_ie=true;
};

$opera=false;
if (ereg('Opera',$_SERVER["HTTP_USER_AGENT"])) {
	$win_ie=false;
	$opera=true;
};

if (isset($cod_area)) {
	$kairos_cookie[4]=$cod_area;
	setcookie("kairos_cookie[4]",$kairos_cookie[4],0,"/",$dominio);
};

require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_utente="";

mysql_select_db($DBASE,$db);	
$query="SELECT * FROM materiali_gruppo WHERE id_risorsa='$risorsa'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
mysql_select_db($DBASE,$db);	

if (!$riga) {
	$msg=$stringa[errore_no_pagina];
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

$titolo=$riga["titolo"];
$livello=$riga["livello"];
$tipo_risorsa=$riga["tipo"];
$risorsa_superiore=$riga["risorsa_padre"];
$url=$riga["url"];

if (isset($kairos_cookie[0])) {
	$id_utente=$kairos_cookie[0];
	$pwd_utente=$kairos_cookie[1];
	
	refresh_utente($id_utente);
	//log_utente($id_utente,$risorsa);
	log_materiali($id_utente,$risorsa);
};

$ruolo=ruolo_utente($id_utente);
mysql_select_db($DBASE,$db);	

if (!$id_utente) {
	$query = $_SERVER["QUERY_STRING"];
	if (!$query) {
		$query = "risorsa=$risorsa"; 
	};
	$kairos_cookie[3]=$query;
	setcookie("kairos_cookie[3]",$kairos_cookie[3],0,"/",$dominio);
	Header("Location:index.php?risorsa=do_login&dir=materiali");
	exit();
};


if ($id_corso_s) {
	$query="SELECT descrizione FROM corso WHERE id_corso='$id_corso_s'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$descrizione_corso=$riga["descrizione"];
};

			
switch ($tipo_risorsa) {
	case '2': //cartella
		require "./include/testata.inc";
		echo "
		<br>
		<table border=0 width=100%>
		<tr><td>";
		
		echo "<span class=sottotitolopagina>$stringa[contenuto_cartella]: $titolo </b></a><br><br></span>";
		if ($risorsa_superiore<>"root") {
			echo "<span class=testo>[<a href=materiali_gruppo_browse.php?risorsa=$risorsa_superiore>$stringa[dir_superiore]</a>]</span><hr size=1>";
		};
		browse_cartella($risorsa);

		echo "</td></tr></table";
		require "./include/piede.inc";
		break;

	case '1': //file da scaricare 
		$file_download=$PATH_ARCHIVI_ADMIN."materiali/$cod_area/gruppo/".$titolo;
	
		if (!file_exists($file_download)) {
			$errore=$stringa[errore_file_rimosso];
			$msg=ereg_replace(" ","%20",$errore);
			Header("Location:index.php?risorsa=msg&msg=$msg");
			exit();
		};

		$doc = fopen($file_download,"rb");
		
		$type= getmimetype($titolo);
		header("Content-Type: $type");
		header( "Content-Disposition: attachment; filename=$titolo" ); 
		fpassthru($doc);
		//readfile($file_download);
		break;
	
	case '0':  //pagina web
		if ($url) {
			header("Location:materiali_gruppo_view.php?id_risorsa=$risorsa");
			exit();
			break;
		};
		$id_pagina=$risorsa;
		$titolo_pagina=$titolo;
		require "./include/layout_pagina_gruppo.inc";
		
		break;
		
	case '3': //nota
		//header("Cache-Control: no-cache");
		//header("Pragma: no-cache");
		require "./include/testata_nota.inc";
		echo "<span class=testo>";
		
		if (file_exists("./materiali/$cod_area/gruppo/$risorsa.inc")) {
			require "./materiali/$cod_area/gruppo/$risorsa.inc";
		};
		
		echo "</span>";
		require "./include/piede_nota.inc";
		break;

};
?>

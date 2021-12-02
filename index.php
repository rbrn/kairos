<?php

require_once("./include/init_sito.inc");
require "./include/funzioni_sito.inc";
require "./include/funzioni_forum.inc";

if (!isset($risorsa)) {
	$risorsa='index';
};



setcookie("kairos_cookie[7]","1",0,"/",$dominio); //mostra postit

if ($id_corso_s) {
	$query="SELECT descrizione FROM corso WHERE id_corso='$id_corso_s'";
	if(!$result=$mysqli->query($query)) die($mysqli->error);
	$riga=$result->fetch_array();

	$descrizione_corso=$riga["descrizione"];
};

$id_utente="";
if (($kairos_cookie[0])) {
	$id_utente=$kairos_cookie[0];
	$pwd_utente=$kairos_cookie[1];
	refresh_utente($id_utente);
	log_utente($id_utente,$risorsa);
};


$query="SELECT * FROM risorse WHERE id_risorsa='$risorsa'";
$result = $mysqli->query($query);
$riga=$result->fetch_array();



if (!$riga and file_exists("./pagine/kairos_demo/$risorsa.inc")) {
	$riga["titolo"]="in sviluppo";
	$riga["livello"]="2";
	$riga["tipo"]="0";
	$riga["risorsa_padre"]="editor_lo";

};	

if (!$riga) {
	$ip_utente=$_SERVER["REMOTE_ADDR"];
	$id_package=uniqid("");
	$msg=$stringa[errore_no_pagina];
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};


$titolo=$riga["titolo"];
$livello=$riga["livello"];
$tipo_risorsa=$riga["tipo"];
$id_gr=$riga["id_gruppo"];
$risorsa_superiore=$riga["risorsa_padre"];

$ruolo=ruolo_utente($id_utente);



if ($livello<>'1' and !$id_utente) {
	$query = $_SERVER["QUERY_STRING"];
	if (!$query) {
		$query = "risorsa=$risorsa"; 
	};

	$kairos_cookie[3]=$query;
	setcookie("kairos_cookie[3]",$kairos_cookie[3],0,"/",$dominio);
	Header("Location:pagina.php?risorsa=do_login");
	exit();
};


if ($livello=='4' and $ruolo<>'staff' and $ruolo<>'admin') {
	$msg=$stringa[errore_solo_staff];
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

if ($livello=='5' and $ruolo<>'admin') {
	$msg=$stringa[errore_solo_admin];
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};



if (($risorsa=='forum_indice' or $risorsa=='forum_mostra_post' or $risorsa=='forum_post' or $risorsa=='forum_edit') and $ruolo<>'admin' and $ruolo<>'staff') {
	$query="SELECT * FROM forum WHERE id_forum='$id_forum'";
	if(!$result=$mysqli->query($query)) die($mysqli->error);;
	$dati_forum=$result->fetch_array();
	if (!$dati_forum) {
		$msg=$stringa[errore_no_forum_disp];
		$msg=ereg_replace(" ","%20",$msg);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
	};
	$tipo=$dati_forum["tipo"];
	$id_corso=$dati_forum["id_corso"];
	$id_edizione=$dati_forum["id_edizione"];
	$id_gruppo=$dati_forum["id_gruppo"];
	
	
	if ($id_corso and $tipo<>"0" and $ruolo<>"admin" and $ruolo<>"staff") {
		if ($id_corso<>$id_corso_s and $id_edizione<>$id_edizione_s) {
			$msg=$stringa[errore_no_forum_accesso];
			$msg=ereg_replace(" ","%20",$msg);
			Header("Location:index.php?risorsa=msg&msg=$msg");
			exit();
		};
	};
	
	if ($id_gruppo and $tipo<>"0" and $ruolo<>"admin" and $ruolo<>"staff") {
		if ($id_corso<>$id_corso_s and $id_edizione<>$id_edizione_s and $id_gruppo<>$id_gruppo_s) {
			$msg=$stringa[errore_no_forum_accesso];
			$msg=ereg_replace(" ","%20",$msg);
			Header("Location:index.php?risorsa=msg&msg=$msg");
			exit();
		};
	};
	
	
	if ($tipo==4) {
		$msg=$stringa[errore_solo_staff];
		$msg=ereg_replace(" ","%20",$msg);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
	};
};	

	
if (($risorsa=='test_compila_form') and $ruolo<>'admin' and $ruolo<>'staff') {

	$id_test=$_REQUEST["id_test"];
	
	$query="SELECT * FROM materiali_sequenza WHERE id_risorsa='$id_test' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
	$result = $mysqli->query($query);
	$riga=$result->fetch_array();

	if (!$riga) {
		$query="SELECT * FROM materiali_sequenza WHERE id_risorsa='$id_test' AND (id_corso='' or id_corso = NULL)";
		$result = $mysqli->query($query);
        $riga=$result->fetch_array();
	}
	if (!$riga) {
		$msg=$stringa[errore_no_risorsa_accesso];
		$msg=ereg_replace(" ","%20",$msg);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
	};
};

switch ($tipo_risorsa) {

	case '2': //cartella
		Header("Location:index.php?risorsa=errore");
		exit();
		break;

	case '1': //file da scaricare 
		$file_download=$PATH_ARCHIVI.$titolo;
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
		break;

	case '0': //pagina web
		
		$target="";
		if ($risorsa=='index') {
			header("Cache-Control: no-cache");
			header("Pragma: no-cache");
		}
		
		if ($risorsa=='materiali_cartella' OR $risorsa=='materiali_nuovo_file' OR $risorsa=='materiali_nuova_cartella' OR $risorsa=='repository_cartella') {
			require "include/testata_vuota.inc";
		} else {
            require "include/testata.inc";
		};
		
	
		if (file_exists("./pagine/$cod_area/$risorsa.inc")) {
				require "./pagine/$cod_area/$risorsa.inc";
		};
		
		
		if ($risorsa=='materiali_cartella' OR $risorsa=='materiali_nuovo_file' OR $risorsa=='materiali_nuova_cartella' OR $risorsa=='repository_cartella') {
			require "./include/piede_vuota.inc";
		} else {
			require "./include/piede.inc";
		};
		
		break;

};

?>

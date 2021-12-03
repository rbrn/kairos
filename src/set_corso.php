<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente=$kairos_cookie[0];
$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];

if (!$id_corso) {
	setcookie("kairos_cookie[2]","",0,"/",$dominio);
	Header("Location:index.php?risorsa=index");
	exit();
};

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);
$ruolo=ruolo_utente($id_utente);
mysql_select_db($DBASE,$db);	


$eprof="1";
/*
if ($ruolo<>'staff' and $ruolo<>'admin' and $cod_area=='kairos_area_corsi') {
	$query_p="SELECT showme AS eprof FROM utenti WHERE id_utente='$id_utente'";
	$result_p=$mysqli->query($query_p);
	$riga=$result_p->fetch_array();
	$eprof=$riga["eprof"];
};
*/
$valore=$id_corso." ".$id_edizione;
if ($ruolo<>'staff' and $ruolo<>'admin' and (!$eprof or $cod_area<>'kairos_area_corsi')) {
	$query="SELECT iscrizioni_corso.id_corso,iscrizioni_corso.id_edizione FROM iscrizioni_corso,edizioni WHERE 
iscrizioni_corso.id_corso='$id_corso' AND
iscrizioni_corso.id_edizione='$id_edizione' AND
iscrizioni_corso.id_corso=edizioni.id_corso AND iscrizioni_corso.id_edizione=edizioni.id_edizione AND 
edizioni.stato='attiva' AND 
iscrizioni_corso.id_utente='$id_utente'";
	$result=$mysqli->query($query);

	if (!$result->num_rows) {
		$valore="";
	};
};


if ($ruolo<>'staff' and $ruolo<>'admin' and ($eprof and $cod_area=='kairos_area_corsi')) {
	$query="SELECT corso.descrizione,corso.id_corso,edizioni.id_edizione FROM corso,edizioni WHERE 
corso.id_corso=edizioni.id_corso AND corso.id_corso='$id_corso' AND
edizioni.stato='attiva'  ORDER BY corso.id_corso,edizioni.id_edizione DESC";	
	$result=$mysqli->query($query);

	$riga=$result->fetch_array();
	$ultima_edizione=$riga["id_edizione"];
	
	$query_i="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso'  AND id_utente='$id_utente'";
	$result_i=$mysqli->query($query_i);
	$iscritto_corso=$result_i->num_rows;
		
	$query_i="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_utente='$id_utente'";
	$result_i=$mysqli->query($query_i);
	$iscritto_edizione=$result_i->num_rows;
	
	if ($ultima_edizione==$id_edizione and !$iscritto_edizione) $valore="";
	
	if (!$iscritto_corso) $valore="";
};
	
			
if ($valore) {
	$query="SELECT id_gruppo FROM iscrizioni_corso WHERE id_utente='$id_utente' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$id_gruppo=$riga["id_gruppo"];
	
	$query="SELECT id_tutor FROM gruppo_utenti WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$id_tutor=$riga["id_tutor"];
	
	$valore .=" ".$id_gruppo." ".$id_tutor;
};

if (!$valore) {
	$msg=$stringa[errore_no_accesso_corso];
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

setcookie("kairos_cookie[2]",$valore,0,"/",$dominio);

$query="REPLACE INTO contesto SET
id_utente='$id_utente',
id_corso='$valore'";
$mysqli->query($query);

if ($cod_area=='kairos_larimart') {
	Header("Location:index.php?risorsa=materiali");
} else {
	Header("Location:index.php?risorsa=index");
};
?>

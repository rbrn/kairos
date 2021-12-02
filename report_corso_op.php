<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);			

$id_gruppo_report=$_REQUEST["id_gruppo_report"];
$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];
$tot_pag=$_REQUEST["tot_pag"];
$livello=$_REQUEST["livello"];
$superato=$_REQUEST["superato"];
$note=$_REQUEST["note"];
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];


$valutazione_pw=$_REQUEST["valutazione_pw"];
$livello_gruppo=$_REQUEST["livello_gruppo"];
$note_gruppo=$_REQUEST["note_gruppo"];

if ($valutazione_pw) {
	$query="UPDATE gruppo_utenti SET 
	livello='$livello_gruppo',
	note='$note_gruppo'
	WHERE id_gruppo='$id_gruppo_report' AND tipo_gruppo=1 AND id_edizione='$id_edizione_s' AND id_corso='$id_corso_s'";
	$result=$mysqli->query($query);
};

while(list($id_u,$livello_u)=each($livello)) {
	$superato_u=$superato[$id_u];
	$note_u=$note[$id_u];
	 
	$query="UPDATE iscrizioni_corso SET 
	livello='$livello_u',
	superato='$superato_u',
	note='$note_u'
	WHERE id_utente='$id_u' AND id_edizione='$id_edizione_s' AND id_corso='$id_corso_s'";
	$result=$mysqli->query($query);
		
};

/*
$msg=addslashes("
Ciao Tere', 
guarda che $kairos_cookie[0] ha aggiornato il report finale

corso: $id_corso_s 
edizione: $id_edizione_s 
gruppo: $id_gruppo_report

vedi tu che c'e' da fare. 

Grazie, ciao.

Fleoautomatico");

$id_package=uniqid("");	
mail_job($id_package,"spedizioni@garamond.it","Report finale: $id_corso_s ($id_edizione_s)","$msg","fleo@garamond.it","fleo@garamond.it","");
*/

$pagina++;	
if ($pagina>$tot_pag) $pagina=1;
header("Location:index.php?risorsa=report_corso&pagina=$pagina&pag_size=$pag_size&id_gruppo_report=$id_gruppo_report&id_corso=$id_corso_s&id_edizione=$id_edizione_s");
?>

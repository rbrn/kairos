<?php
require "../include/init_sito.inc";
$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBNAME);

$parametri=$_SERVER["QUERY_STRING"];

$azione=$_REQUEST["azione"];

if ($azione<>"null") {
	$action=$_REQUEST["action"];
	$id_utente=$_REQUEST["cmi_core_student_id"];
	$id_sco=$_REQUEST["cmi_core_lesson_location"];
	$stato=$_REQUEST["cmi_core_lesson_status"];
	$durata=$_REQUEST["cmi_core_session_time"];
	$punteggio=$_REQUEST["cmi_core_score_raw"];
	$punteggio_max=$_REQUEST["cmi_core_score_max"];
	$commenti_utente=$_REQUEST["cmi_comments"];
	
	$query="INSERT INTO lo_tracking SET 
	id_utente='$id_utente',
	azione='$action',
	data_sessione=NOW(),
	id_lo='$id_sco',
	stato_sessione='$stato',
	durata_sessione='$durata',
	punteggio='$punteggio',
	punteggio_max='$punteggio_max',
	commenti_utente='$commenti_utente'
	";
	
	$mysqli->query($query);
	echo htmlentities($parametri)."<br>";
	echo mysql_error();
};
?>

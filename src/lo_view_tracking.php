<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

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
refresh_utente($id_utente);

?><?php
header("Cache-Control: no-cache");
header("Pragma: no-cache");
?>
<html>
<head>
<title>Tracciamento LO</title>

<?php
echo "
<link rel=\"stylesheet\" href=stili/$cod_area/stile_sito.css>
<script language=\"JavaScript\" src=script/funzioni.js></script>
";
?>
</head>
<body bgcolor=<?php echo($colore_sfondo_neutro);?>>

<?php

$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);			



$query = "SELECT * FROM scorm_scoes_track WHERE scoid='$id_lo' AND element='cmi.core.lesson_status' ORDER BY timemodified DESC";
$result=$mysqli->query($query);



echo "

<span class=testo><b>Tracciamento LO</b></span>

<br><br>

<TABLE BORDER=0 cellspacing=0 cellpadding=3>
<tr>
<td><span class=testopiccolo><b>Utente</b></span></td>
<td><span class=testopiccolo><b>Data</b></span></td>
<td><span class=testopiccolo><b>Stato</b></span></td>
<td><span class=testopiccolo><b>Durata</b></span></td>
<td><span class=testopiccolo><b>Punteggio</b></span></td>
";

while ($riga = $result->fetch_array()) {

	$id_utente=$riga["userid"];
	$data_sessione = $riga["timemodified"];
	$stato_sessione=$riga["value"];
	
	$query1 = "SELECT * FROM scorm_scoes_track WHERE scoid='$id_lo' AND userid='$id_utente' AND element='cmi.core.session_time'";
	$result1=$mysqli->query($query1);
	$riga1 = $result1->fetch_array();
	$durata_sessione=$riga1["value"];
	
	$query1 = "SELECT * FROM scorm_scoes_track WHERE scoid='$id_lo' AND userid='$id_utente' AND element='cmi.core.score.raw'";
	$result1=$mysqli->query($query1);
	$riga1 = $result1->fetch_array();
	$punteggio=$riga1["value"];
	
	$query1 = "SELECT * FROM scorm_scoes_track WHERE scoid='$id_lo' AND userid='$id_utente' AND element='cmi.core.score.max'";
	$result1=$mysqli->query($query1);
	$riga1 = $result1->fetch_array();
	$punteggio_max=$riga1["value"];
	
	echo "<tr>";

	echo "<td>
	<span class=testopiccolo>
	<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente</a>
	</span>
	</td>";

	echo "
	<td><span class=testopiccolo>$data_sessione</span></td>
	<td><span class=testopiccolo>$stato_sessione</span></td>
	<td><span class=testopiccolo>$durata_sessione</span></td>
	<td><span class=testopiccolo>$punteggio/$punteggio_max</span></td>";
	
echo "</tr>";

};



echo "

</table>";

?>

</body>

</html>


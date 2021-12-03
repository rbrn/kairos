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
$id_gruppo=$_REQUEST[id_gruppo];
$id_utente=$kairos_cookie[0];
refresh_utente($id_utente);

?><?php
header("Cache-Control: no-cache");
header("Pragma: no-cache");
?>
<html>
<head>
<title><?php echo($stringa[componenti_gruppo]);?>:</title>

<?php
echo "
<link rel=\"stylesheet\" href=stili/$cod_area/stile_sito.css>
<script language=\"JavaScript\" src=script/funzioni.js></script>
";
?>
</head>
<body bgcolor=<?php echo($colore_sfondo_neutro);?>>

<?php

// connessione al dbatlante

//parametro: id_post



$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);			



$query = "SELECT id_utente FROM iscrizioni_corso WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_utente";

$result=$mysqli->query($query);



echo "

<span class=testo><b>$stringa[componenti_gruppo]</b></span>

<br><br>

<TABLE BORDER=0 cellspacing=0 cellpadding=3>

";



while ($riga = $result->fetch_array()) {

	$id_utente=$riga["id_utente"];
	
	echo "<tr>";

	echo "<td>

	<span class=testopiccolo>
	<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente</a>

	</span>

	</td>";

	

echo "</tr>";

};



echo "

</table>";

?>

</body>

</html>


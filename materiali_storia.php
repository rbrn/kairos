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
$id_risorsa=$_REQUEST[id_risorsa];
$id_utente=$kairos_cookie[0];
refresh_utente($id_utente);

?><?php
header("Cache-Control: no-cache");
header("Pragma: no-cache");
?>
<html>
<head>
<title><?php echo($stringa[materiale_storia]);?>:</title>

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



$query = "SELECT id_utente,DATE_FORMAT(data_evento,'%d/%m/%Y %H:%i') as data_r,evento FROM materiale_storia WHERE id_risorsa='$id_risorsa' ORDER BY data_evento DESC";

$result=$mysqli->query($query);





echo "

<span class=testo><b>$stringa[materiale_storia]</b></span>

<br><br>

<TABLE BORDER=0 cellspacing=0 cellpadding=3>

";



while ($riga = $result->fetch_array()) {

	$id_utente=$riga["id_utente"];

	$data = $riga["data_r"];
	$evento = $riga["evento"];
	$evento=$stringa[$evento];
	
	echo "<tr>";

	echo "<td>

	<span class=testopiccolo>
	$data - $evento ".strtolower($stringa[da])." 
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


<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$id_risorsa=$_REQUEST[id_risorsa];
$tipo=$_REQUEST[tipo];

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
if ($tipo==1) {
	$chi=$stringa[chi_scaricato];
} else {
	$chi=$stringa[chi_visto];
};

?><?php
header("Cache-Control: no-cache");
header("Pragma: no-cache");
?>
<html>
<head>
<title><?php echo($chi);?>:</title>

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

$query = "SELECT id_utente,DATE_FORMAT(data_log,'%d/%m/%Y %H:%i') as data_r FROM log_lab_materiali WHERE id_risorsa=$id_risorsa ORDER BY data_log DESC";
$result=$mysqli->query($query);


echo "
<span class=testo><b>$chi</b></span>
<br><br>
<TABLE BORDER=0 cellspacing=0 cellpadding=3>
";

while ($riga = $result->fetch_array()) {
	$id_utente=$riga["id_utente"];
	$data = $riga["data_r"];
	echo "<tr>";
	echo "<td>
	<span class=testopiccolo>
	<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente ($data)</a>
	</span>
	</td>";
echo "</tr>";
};
echo "
</table>";
?>
</body>
</html>

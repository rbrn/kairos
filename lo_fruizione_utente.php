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

$id_u=$_REQUEST["id_u"];
$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];

?><?php
header("Cache-Control: no-cache");
header("Pragma: no-cache");
?>
<html>
<head>
<title><?php echo($stringa[lo_fruizione]);?>:</title>

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

echo "<span class=testo><b>$stringa[lo_fruizione]</b></span>";

lo_mostra($id_u,$id_corso,$id_edizione,0);
?>
</body>
</html>


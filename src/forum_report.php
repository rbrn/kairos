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

?><?php
header("Cache-Control: no-cache");
header("Pragma: no-cache");
?>
<html>
<head>
<title>Report interventi del forum</title>

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

//parametro: id_forum


$id_forum=$_REQUEST["id_forum"];

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);			


$query = "SELECT DISTINCT id_utente FROM forum_read WHERE id_forum='$id_forum'";
$result=$mysqli->query($query);
$num_lettori=$result->num_rows;


$query = "SELECT DISTINCT id_autore FROM forum_posts WHERE id_forum='$id_forum'";
$result=$mysqli->query($query);
$num_scrittori=$result->num_rows;

echo "

<span class=testo><b>Report interventi del forum</b></span>

<br><br>

<span class=testo>Numero utenti singoli che hanno letto almeno un intervento: <b>$num_lettori</b></span>
<br><br>
<span class=testo>Numero utenti singoli che hanno scritto almeno un intervento: <b>$num_scrittori</b></span>
<br><br>
<span class=testo>In particolare:</span>
<br><br>
";

$utenti=array();
while ($riga=$result->fetch_array()) {
	$id_autore=$riga["id_autore"];
	
	$query2 = "SELECT id_autore FROM forum_posts WHERE id_forum='$id_forum' AND id_autore='$id_autore'";
	$result2=$mysqli->query($query2);
	$num_posts=$result2->num_rows;
	
	$utenti["$id_autore"]=$num_posts;
};



echo "

<TABLE BORDER=0 cellspacing=0 cellpadding=3>

";
arsort($utenti);
reset($utenti);
while (list($id_utente, $num_posts) = each($utenti)) {
	
	echo "<tr>";

	echo "<td>

	<span class=testopiccolo>

	<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente ($num_posts)</a>

	</span>

	</td>";

	

echo "</tr>";

};



echo "

</table>";

?>

</body>

</html>


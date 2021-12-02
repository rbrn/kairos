<?php
require "./include/init_sito.inc";
?>
<html>
<head><title>Non iscritti</title>
</head>
<body bgcolor=white>
<p><b>Utenti non iscritti</b></p>
<hr size=1>
<?php
$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db("kairos_fortic",$db);	

$query="SELECT utenti.id_utente FROM utenti LEFT JOIN iscrizioni_corso ON (utenti.id_utente=iscrizioni_corso.id_utente) WHERE iscrizioni_corso.id_utente IS NULL";
$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {
	$id_u=$riga[id_utente];
	echo "$id_u <br>";
};
?>

<hr size=1>
</body>
</html>

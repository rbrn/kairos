<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
$id_utente_mitt=$kairos_cookie[0];
$id_utente=$_REQUEST["id_utente"];
$oggetto=$_REQUEST["oggetto"];
$testo=$_REQUEST["testo"];

if ($kairos_cookie[9]) $DBASE_UTENTI="atlante";

mysql_select_db($DBASE_UTENTI,$db);	
$query = "SELECT id_utente FROM utenti WHERE id_utente='$id_utente'";
$result=$mysqli->query($query);


$esiste = $result->fetch_array();

if (!trim($oggetto)) {
	$oggetto=$stringa[senza_oggetto];

};



mysql_select_db($DBASE,$db);	

if ($esiste) {

	$query = "INSERT INTO messaggi (id_mittente,id_destinatario,oggetto,testo,data_invio,data_lettura,stato) VALUES ('$id_utente_mitt','$id_utente','$oggetto','$testo',now(),'',0)";

	$mysqli->query($query);

	$msg="Messaggio inviato.<br>Aggiorna la pagina della posta interna per vederlo in elenco.";

} else {

	$msg="$stringa[utente]: <b>$id_utente</b> $stringa[non_esiste]";

};



?>

<html>

<head>

<title><?php echo($stringa[messaggio_inviato_fb]);?></title>
<?php
echo"
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>
</head>

<BODY bgcolor=<?php echo($colore_sfondo_neutro);?>>

<p><span class=testo><?php echo ($msg);?></span></p> 

<p align=center><span class=testo>[<a href="javascript:self.close()"><?php echo($stringa[chiudi]);?></a>]</span>  



<!-- FINE CONTENUTO DELLA PAGINA -->

</body>

</html>


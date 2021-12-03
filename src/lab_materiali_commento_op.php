<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$id_risorsa=$_REQUEST["id_risorsa"];
$commento=$_REQUEST["commento"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query = "SELECT utenti.email,lab_materiali.titolo FROM lab_materiali,utenti where lab_materiali.id_autore=utenti.id_utente AND lab_materiali.id_risorsa=$id_risorsa";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$email=$riga[email];
$titolo=$riga[titolo];

$id_utente = $kairos_cookie["0"];

$query="SELECT email FROM utenti WHERE id_utente='$id_utente'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();		
	
$email_mittente=$riga["email"];

if (!$email) {
	$email_mittente="fleo@garamond.it";
};

if ($commento) {
$query = "INSERT INTO commento_lab_materiali SET
id_risorsa=$id_risorsa,
id_utente='$id_utente',
id_corso='$id_corso_s',
id_edizione='$id_edizione_s',
id_gruppo='$id_gruppo_s',
data_commento=now(),
commento='$commento'";
$result=$mysqli->query($query);
};

$oggetto = "$cod_area: commento tuo materiale";	
$oggetto = stripslashes($oggetto);
			
$testo="Hai ricevuto un commento alla tua risorsa: $titolo\n nell'area $PATH_ROOT";
$testo = stripslashes($testo);

//@mail("$email","$oggetto","$testo","From:$email_mittente\nReply-To:$email_mittente");
 
$id_package=uniqid("");	
mail_job($id_package,"$email","$oggetto","$testo","$email_mittente","$email_mittente","");
 
mysql_select_db($DBASE,$db);	

Header("Location:index.php?risorsa=lab_materiali_view&id_risorsa=$id_risorsa");		
?>

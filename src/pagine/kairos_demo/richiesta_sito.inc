<!-- CONTENUTO DELLA PAGINA -->

<p>

<span class=titolopagina>

Laboratori: Richiesta Sito Web Utente E-prof

</span>

</p>



<?php

// connessione al dbatlante

$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	

$query="SELECT sitoweb FROM profilo_utente WHERE id_utente='$id_utente'";

$result=$mysqli->query($query);

$riga=$result->fetch_array();

$sitoweb = $riga["sitoweb"];

echo "<table border=0 width=70%><tr><td>";

if ($sitoweb) {

	echo "

	<p>

	<span class=testo>

	Risulti giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ titolare di uno spazio web: <a href=\"http://utenti.garamond.it/$sitoweb\" title=\"Apri il sito dell'utente\">http://utenti.garamond.it/$sitoweb</a>

	</span></p>";

} else {

	$query="SELECT email,pwd_utente FROM utenti WHERE id_utente='$id_utente'";

	$result=$mysqli->query($query);

	$riga=$result->fetch_array();

	$email = $riga["email"];

	$pwd_utente = $riga["pwd_utente"];

	echo "

	<p>

	<span class=testo>

	E' stata inviata la richiesta di attivazione di uno spazio web gratuito su<br> <b>utenti.garamond.it/$id_utente</b>. <br>

	Ti preghiamo di attendere massimo due giorni lavorativi nell'arco dei quali riceverai al tuo email <b>$email</b> conferma dell'attivazione e istruzioni per la gestione. <br>

	Grazie! 

	</span></p>";

	$msg="

	Attivare spazio web su utenti.garamond.it al seguente utente di E-Prof:

	

	id_utente:$id_utente

	password:$pwd_utente\n	

	e-mail: $email";

	

	mail("staff_p.quadrino@garamond.it,fleo@garamond.it",

		"SitoWebEProf per $id_utente","$msg",

		"From:$email\nReply-To:$email");

};	

echo "</td></tr></table>";



?>

<!-- FINE CONTENUTO DELLA PAGINA -->

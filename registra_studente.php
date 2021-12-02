<?php

require "./include/init_sito.inc";

require "./include/funzioni_sito.inc";



$id_eprof=$kairos_cookie[0];



$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);

mysql_select_db($DBASE_UTENTI,$db);	



// controllo se tutti i campi obbligatori sono stati compilati

$id_studente=$_REQUEST["id_studente"];

$pwd_studente=$_REQUEST["pwd_studente"];

$nome=$_REQUEST["nome"];

$cognome=$_REQUEST["cognome"];

$email=$_REQUEST["email"];

$sesso=$_REQUEST["sesso"];

$eta=$_REQUEST["eta"];



$errore = "";

$id_studente=trim($id_studente);

$pwd_studente=trim($pwd_studente);



if (!$id_studente) {

	$errore .= "<br>Manca l'identificativo";

} else { //rimuovo eventuali spazi nell'identificativo

	$id_studente = ereg_replace(" ","",$id_studente);

	$id_studente=strtolower($id_studente);

}

		 

if (eregi("[^a-z0-9]{1,30}",$id_studente)) {

	$errore .= "<br>Caratteri non validi nell'identificativo";

};



if (!$pwd_studente) {

	$errore .= "<br>Manca la password";

} 

		 

if (eregi("[^a-z0-9]{1,30}",$pwd_studente)) {

	$errore .= "<br>Caratteri non validi nella password";

};

		

if (!$nome) {

		$errore .= "<br>Manca Nome";

	};	



if (!$cognome) {

	$errore .= "<br>Manca Cognome";

	};	

	



if ($email) {

	if (!ereg("^.+@.+\\..+$",$email)){

		$errore .= "<br>E-Mail non valido";

	};

};









// controllo se esiste giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ l'ID utente



if (!$errore) {

	$query = "SELECT id_utente FROM utenti where id_utente='$id_studente'";

	$result=$mysqli->query($query);

	$riga = $result->fetch_array();

	if ($riga) {

		$errore = "<br>Identificativo utente non valido perchÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ esistente, prova a definirne un altro";

	};

};



if ($errore) {

			echo "

			<HTML>

<HEAD><TITLE>Atlante Ragazzi: Esito Registrazione</TITLE>

</HEAD>

<BODY bgcolor=$colore_sfondo>

<font face=verdana size=-1><b>ERRORE NEL MODULO!</b><br>Sono stati riscontrati i seguenti errori nella compilazione del modulo:<br><b>".$errore."</b></font>";

			echo "<p><center><a href=javascript:history.back()>Torna Indietro</a></center></body></html>";

		exit();

};


// tutto OK inserisco i dati dell'utente nella tabella

			


// tutto OK inserisco i dati dell'utente nella tabella


// prendo i dati dell'utente eprof		

$query="SELECT * FROM utenti WHERE id_utente='$id_eprof'";

$result=$mysqli->query($query);

$riga = $result->fetch_array();



$ordinescuola=addslashes($riga["ordinescuola"]);

$nomescuola=addslashes($riga["nomescuola"]);

$indirizzoscuola=addslashes($riga["indirizzoscuola"]);

$capscuola=addslashes($riga["capscuola"]);

$cittascuola=addslashes($riga["cittascuola"]);

$provscuola=addslashes($riga["provscuola"]);

$emailscuola=addslashes($riga["emailscuola"]);

$sitoscuola=addslashes($riga["sitoscuola"]);



if (!$email) {

	$email=$riga["email"];

};





$query = "INSERT INTO utenti (

	id_utente,pwd_utente,data_reg,nome,cognome,indirizzo,cap,citta,prov,telefono,fax,email,sitoweb,sesso,eta,studio,ruolo,famiglia,lettura,sport,musica,cinema,viaggi,ordinescuola,nomescuola,indirizzoscuola,capscuola,cittascuola,provscuola,emailscuola,sitoscuola,materia,privacy,newsatlante,newssophia,showme,parole_chiave) VALUES (

 '$id_studente',

'$pwd_studente',NOW(), '$nome','$cognome','', '', '',

'', '', '', '$email','', '$sesso', '$eta','', 'Studente',

'', '', '', '', '', '',

'$ordinescuola', '$nomescuola', '$indirizzoscuola', '$capscuola',

'$cittascuola', '$provscuola', '$emailscuola', '$sitoscuola', '.','','','','on',NULL)";

$result=$mysqli->query($query);



$query="INSERT INTO ragazzi_eprof (id_utente,id_eprof) VALUES ('$id_studente','$id_eprof')";

$result=$mysqli->query($query);



echo "

<HTML>

<HEAD><TITLE>Atlante Ragazzi: Esito Registrazione</TITLE>

</HEAD>

<BODY bgcolor=$colore_sfondo>

<font face=verdana size=-1>Ok <b>$id_eprof</b>, la registrazione dell'alunno <b>$id_studente</b> ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ attiva. Grazie.</font>

</body>

</html>";					 	



?>

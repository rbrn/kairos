<?php

switch ($operazione) {
	case "insert":
	mysql_select_db('kairos_ipsiaeascione');
	$query = "INSERT INTO utenti (
id_utente,pwd_utente,data_reg,nome,cognome,indirizzo,cap,citta,prov,telefono,email,sitoweb,sesso,eta,professione,interesse,newsletter,privacy,showme,scuola,stato,ruolo_scuola,materia) VALUES (
 '$id_utente',
'$pwd_utente',NOW(), '$nome','$cognome','$indirizzo', '$cap', '$citta',
'$prov', '$telefono','$email','$sitoweb', '$sesso', '$eta','$professione', '$interesse','$newsletter','$privacy','on','$scuola','$stato','$ruolo_scuola','$materia')";
	@$mysqli->query($query);
	
	mysql_select_db('eureka_ipsiaeascione');
	$query = "INSERT INTO utenti (
id_utente,pwd_utente,data_reg,nome,cognome,indirizzo,cap,citta,prov,telefono,email,sitoweb,sesso,eta,professione,interesse,newsletter,privacy,showme,scuola,stato,ruolo,id_genitore,id_classe) VALUES (
 '$id_utente',
'$pwd_utente',NOW(), '$nome','$cognome','$indirizzo', '$cap', '$citta',
'$prov', '$telefono','$email','$sitoweb', '$sesso', '$eta','$professione', '$interesse','$newsletter','$privacy','on','$scuola','$stato','$ruolo','$id_genitore','$id_classe')";
	@$mysqli->query($query);
	
	mysql_select_db('koine_ipsiaeascione');
	$query = "INSERT INTO utenti (
id_utente,pwd_utente,data_reg,nome,cognome,indirizzo,cap,citta,prov,telefono,email,sitoweb,sesso,eta,professione,interesse,newsletter,privacy,showme,scuola,stato) VALUES (
 '$id_utente',
'$pwd_utente',NOW(), '$nome','$cognome','$indirizzo', '$cap', '$citta',
'$prov', '$telefono','$email','$sitoweb', '$sesso', '$eta','$professione', '$interesse','$newsletter','$privacy','on','$scuola','$stato')";
	@$mysqli->query($query);
	break;
	
	case "update":
	mysql_select_db('kairos_ipsiaeascione');
	$query = "UPDATE utenti SET
			pwd_utente='$pwd_utente',
			nome='$nome',
			cognome='$cognome',
			indirizzo='$indirizzo',
			cap='$cap',
			citta='$citta',
			prov='$prov',
			telefono='$telefono',
			email='$email',
			sitoweb='$sitoweb',
			sesso='$sesso',
			eta='$eta',
			professione='$professione',
			interesse='$interesse',
			newsletter='$newsletter',
			biografia='$biografia',
			scuola='$scuola',
			stato='$stato',
			ruolo_scuola='$ruolo_scuola',
			materia='$materia'
			WHERE id_utente='$id_utente'";
	@$mysqli->query($query);
	
	mysql_select_db('eureka_ipsiaeascione');
	$query = "UPDATE utenti SET
			pwd_utente='$pwd_utente',
			nome='$nome',
			cognome='$cognome',
			indirizzo='$indirizzo',
			cap='$cap',
			citta='$citta',
			prov='$prov',
			telefono='$telefono',
			email='$email',
			sitoweb='$sitoweb',
			sesso='$sesso',
			eta='$eta',
			professione='$professione',
			interesse='$interesse',
			newsletter='$newsletter',
			biografia='$biografia',
			scuola='$scuola',
			stato='$stato',
			ruolo='$ruolo_utente',
			id_genitore='$id_genitore',
			id_classe='$id_classe'
			WHERE id_utente='$id_utente'";
	@$mysqli->query($query);
	
	mysql_select_db('koine_ipsiaeascione');
	$query = "UPDATE utenti SET
			pwd_utente='$pwd_utente',
			nome='$nome',
			cognome='$cognome',
			indirizzo='$indirizzo',
			cap='$cap',
			citta='$citta',
			prov='$prov',
			telefono='$telefono',
			email='$email',
			sitoweb='$sitoweb',
			sesso='$sesso',
			eta='$eta',
			professione='$professione',
			interesse='$interesse',
			newsletter='$newsletter',
			biografia='$biografia',
			scuola='$scuola',
			stato='$stato'
			WHERE id_utente='$id_utente'";
	@$mysqli->query($query);
	break;
	
	case "modifica":
	mysql_select_db('kairos_ipsiaeascione');
	$query = "UPDATE utenti SET
			pwd_utente='$pwd_utente',
			nome='$nome',
			cognome='$cognome',
			indirizzo='$indirizzo',
			cap='$cap',
			citta='$citta',
			prov='$prov',
			telefono='$telefono',
			email='$email',
			sitoweb='$sitoweb',
			sesso='$sesso',
			eta='$eta',
			professione='$professione',
			interesse='$interesse',
			newsletter='$newsletter',
			biografia='$biografia',
			scuola='$scuola',
			ruolo_scuola='$ruolo_scuola',
			materia='$materia'
			WHERE id_utente='$id_utente'";
	@$mysqli->query($query);
	
	mysql_select_db('eureka_ipsiaeascione');
	$query = "UPDATE utenti SET
			pwd_utente='$pwd_utente',
			nome='$nome',
			cognome='$cognome',
			indirizzo='$indirizzo',
			cap='$cap',
			citta='$citta',
			prov='$prov',
			telefono='$telefono',
			email='$email',
			sitoweb='$sitoweb',
			sesso='$sesso',
			eta='$eta',
			professione='$professione',
			interesse='$interesse',
			newsletter='$newsletter',
			biografia='$biografia',
			scuola='$scuola'
			WHERE id_utente='$id_utente'";
	@$mysqli->query($query);
	
	mysql_select_db('koine_ipsiaeascione');
	$query = "UPDATE utenti SET
			pwd_utente='$pwd_utente',
			nome='$nome',
			cognome='$cognome',
			indirizzo='$indirizzo',
			cap='$cap',
			citta='$citta',
			prov='$prov',
			telefono='$telefono',
			email='$email',
			sitoweb='$sitoweb',
			sesso='$sesso',
			eta='$eta',
			professione='$professione',
			interesse='$interesse',
			newsletter='$newsletter',
			biografia='$biografia',
			scuola='$scuola'
			WHERE id_utente='$id_utente'";
	@$mysqli->query($query);
	break;	
	
};

?>

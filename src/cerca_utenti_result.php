<?php

require "init_sito_corso.inc";

require "functions_corso.inc";



if ( !$id_utente_corso_cookie ){

	$query = $_SERVER["QUERY_STRING"];

	if ($query) {

		$url = "$PHP_SELF?$query";

	} else {

		$url ="$PHP_SELF";

	};

	Header("Location: $PATH_ROOT/do_login.php?url=$url");

	exit();

};

refresh_utente($id_utente_corso_cookie);

?>

<?php

header("Cache-Control: no-cache");

header("Pragma: no-cache");

?>

<html>



<head>

<title>Garamond-Atlante Corso OnLine: Cerca Utenti </title>



<?php

require "menu_corso.inc";

?>





<tr>

<td width=5>&nbsp;</td>

<td bgcolor=white>

<p>

&nbsp;

</p>

<!-- CONTENUTO DELLA PAGINA -->



<?php

// connessione al dbatlante

$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	



$query1 = "";



// creo la condizione where

$privacy = false;

	

if ($id_utente) {

	if ($query1) {

		$query1 .= "AND";

		};

	$query1 .= " (iscrizione_corso.id_utente='$id_utente') ";

	}



if ($nome) {

	if ($query1) {

		$query1 .= "AND";

		};

	$query1 .= " (utenti.nome LIKE '$nome%') ";

	}



if ($cognome) {

	if ($query1) {

		$query1 .= "AND";

		};

	$query1 .= " (utenti.cognome LIKE '$cognome%') ";

	}



if ($citta) {

	$privacy = true;

	if ($query1) {

		$query1 .= "AND";

		};

	$query1 .= " (utenti.citta LIKE '$citta%') ";

	}



if ($prov) {

	$privacy = true;

	if ($query1) {

		$query1 .= "AND";

		};

	$query1 .= " (utenti.prov LIKE '$prov%') ";

	}





if ($ordinescuola<>"all") {

	$privacy = true;

	if ($query1) {

		$query1 .= "AND";

		};

	$query1 .= " (utenti.ordinescuola LIKE '$ordinescuola%') ";

};	

		



if ($materia) {

	$privacy = true;

	if ($query1) {

		$query1 .= "AND";

		};

	$query1 .= " (utenti.materia LIKE '%$materia%') ";

};			





$operatore = "";

if ($query1) {

	$operatore = " AND ";

};



if ($privacy) {

	$query = "SELECT DISTINCT iscrizione_corso.id_utente,utenti.cognome,utenti.nome,iscrizione_corso.id_gruppo,profilo_utente.privacy FROM iscrizione_corso,utenti,profilo_utente";

	$query .= " WHERE $query1 $operatore iscrizione_corso.id_utente=utenti.id_utente AND iscrizione_corso.id_utente=profilo_utente.id_utente";

} else {

	$query = "SELECT DISTINCT iscrizione_corso.id_utente,utenti.cognome,utenti.nome,iscrizione_corso.id_gruppo FROM iscrizione_corso,utenti";

	$query .= " WHERE $query1 $operatore iscrizione_corso.id_utente=utenti.id_utente";	

};


$query .= " ORDER BY iscrizione_corso.id_gruppo,utenti.cognome,utenti.nome";

$result = $mysqli->query($query);

$num = $result->num_rows;

echo "<p>Utenti trovati: <b>$num</b></p>";

echo "

<hr size=1>

<span class=piccolo>[<a href=form_cerca_utenti.php>Nuova ricerca</a>]</span>

<br>

<hr size=1>

";



echo "

<TABLE BORDER=1 cellspacing=2 cellpadding=2>

<tr>

<td><p><b>N.</b></p></td>

<td><p><b>Utente</b></p></td>

<td><p><b>Classe</b></p></td>

<td><p><b>Ultima attivitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ rilevata</b></p></td>

</tr>";



$i=1;

while ($riga = $result->fetch_array()) {

	$id_utente=$riga["id_utente"];

	$nome_utente = $riga["nome"]." ".$riga["cognome"];

	$classe = $riga["id_gruppo"];

	$query_time = "SELECT max(data_log) as last_alive FROM log_corso WHERE id_utente='$id_utente'";

	$result_time = $mysqli->query($query_time);

	$riga_time = $result_time->fetch_array();

	$time=$riga_time["last_alive"];

		

	echo "<tr>";

	printf ("<td><p>%s</p></td>",$i);



	echo "<td>

	<span class=piccolo>

	<a class=miolink href=\"#\" title=\"Clicca per sapere chi ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½...\" onclick=\"javascript:apri_scheda('$PATH_ROOT/utility/scheda_utente.php?id_utente=$id_utente',                   'myRemote',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindow');\">($id_utente) $nome_utente</a>

	</span>

	</td>";	

	

	echo "

	<td><p>$classe</p></td>

	<td><p>$time</p></td>

	</tr>";



	$i++;

};





?>

		

</table>		



<!-- FINE CONTENUTO DELLA PAGINA -->

</td>

</tr>





<?php

require "piede_corso.inc";

?>

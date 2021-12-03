<?php 

header("Cache-Control: no-cache");

header("Pragma: no-cache");



require "./include/init_sito.inc";



$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	



?>

<html>

<head>elenco iscritti</head>

<body bgcolor=white>



<table border=1>

	<tr>

	<td>

	<span class=testopiccolo>

	<b>Nome</b>

	</span>

	</td>

	<td>

	<span class=testopiccolo>

	<b>Cognome</b>

	</span>

	</td>

	<td>

	<span class=testopiccolo>

	<b>Indirizzo</b>

	</span>

	</td>

	<td>

	<span class=testopiccolo>

	<b>CAP</b>

	</span>

	</td>

	<td>

	<span class=testopiccolo>

	<b>CittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½</b>

	</span>

	</td>

	<td>

	<span class=testopiccolo>

	<b>Prov.</b>

	</span>

	</td>

	<td>

	<span class=testopiccolo>

	<b>ID - email</b>

	</span>

	</td>

	</tr>

	

    <?php

	

	$cod_area=$kairos_cookie[4];

	

	mysql_select_db($DBASE_UTENTI,$db);

	

	$query="SELECT * FROM sessioni_corso WHERE cod_area='$cod_area'";

	$result=$mysqli->query($query);

	$riga = $result->fetch_array();

	$data_inizio=$riga["data_inizio"];

	$data_fine=$riga["data_fine"];

	

	$query = "SELECT spesa.id_utente,data_spesa,nome,cognome,indirizzo,cap,citta,prov,email FROM spesa,utenti WHERE spesa.

id_utente=utenti.id_utente AND spesa.cod_prodotto='$cod_area' ORDER BY cognome,nome,data_spesa DESC";



	$result=$mysqli->query($query);

	$i=1;

	$elenco_utenti = array();

	$tot_nuovi=0;

	

	while ($riga=$result->fetch_array()) {

		$id_utente1 = $riga["id_utente"];

		$data_spesa=$riga["data_spesa"];

		$nome=strtoupper($riga["nome"]);

		$cognome=strtoupper($riga["cognome"]);

		$indirizzo=strtoupper($riga["indirizzo"]);

		$cap=strtoupper($riga["cap"]);

		$citta=strtoupper($riga["citta"]);

		$prov=strtoupper($riga["prov"]);

		$email=$riga["email"];

				

		$prendi=true;

		$nuovo=true;

		if ($data_spesa < $data_inizio or $data_spesa > $data_fine) {

			$nuovo=false;

			$prendi=false;

		};

		

		if ($prendi) {

			if (!in_array($id_utente1,$elenco_utenti)) { 

				echo "

		<tr>

		<td>

		<span class=testopiccolo>

		$nome

		</span>

		</td>

		

		<td>

		<span class=testopiccolo>

		$cognome

		</span>

		</td>

		

		<td>

		<span class=testopiccolo>

		$indirizzo

		</span>

		</td>

		

		<td>

		<span class=testopiccolo>

		$cap

		</span>

		</td>

		

		<td>

		<span class=testopiccolo>

		$citta

		</span>

		</td>

		

		

		

		<td>

		<span class=testopiccolo>

		$prov

		</span>

		</td>

		

		<td>

		<span class=testopiccolo>

		($id_utente1) $email

		</span>

		</td>

		";



		

		echo "</tr>";

			$elenco_utenti[]=$id_utente1;

						};

		};

	};

	?>

</table>

</body>

</html>

<p>
<span class=titolopagina>
Registrazione iscrizioni corso
</span>
</p>
<span class=testo>

<?php
$id_corso_edizione=$_REQUEST["id_corso_edizione"];

list($id_corso,$id_edizione)=split(" ",$id_corso_edizione);

$query="SELECT * FROM sessioni_corso WHERE cod_area='$id_corso'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$data_inizio=$riga["data_inizio"];
$data_fine=$riga["data_fine"];

$query="SELECT 
utenti.id_utente,
utenti.pwd_utente,
utenti.nome,
utenti.cognome,
utenti.indirizzo,
utenti.cap,
utenti.citta,
utenti.prov,
utenti.telefono,
utenti.fax,
utenti.email,
utenti.sitoweb,
utenti.sesso,
utenti.eta,
utenti.nomescuola,
spesa.cod_prodotto,
spesa.data_spesa
FROM spesa,utenti WHERE 
(cod_prodotto='$id_corso' AND data_spesa>='$data_inizio' AND data_spesa<='$data_fine') AND 
(spesa.id_utente=utenti.id_utente)";	

$result=$mysqli->query($query);
//echo mysql_error();
$i=1;
while ($riga=$result->fetch_array()) {
	$id_utente=addslashes($riga["id_utente"]);
	$pwd_utente=addslashes($riga["pwd_utente"]);
	$nome=addslashes($riga["nome"]);
	$cognome=addslashes($riga["cognome"]);
	$indirizzo=addslashes($riga["indirizzo"]);
	$cap=addslashes($riga["cap"]);
	$citta=addslashes($riga["citta"]);
	$prov=addslashes($riga["prov"]);
	$telefono=addslashes($riga["telefono"]);
	$email=addslashes($riga["email"]);
	$sitoweb=addslashes($riga["sitoweb"]);
	$sesso=addslashes($riga["sesso"]);
	$eta=addslashes($riga["eta"]);
	$scuola=addslashes($riga["nomescuola"]);
	$interesse="";
	$biografia="";
	
	
	$query1="SELECT * FROM abbonamenti_utente WHERE id_utente='$id_utente' AND date_add(data_prodotto,interval 1 year) >= now()";
	$result1=$mysqli->query($query1);
	echo mysql_error();
	$riga1 = $result1->fetch_array();	
	if ($riga1["cod_prodotto"]=='eprof') {
		$eprof="1";
	} else {
		$eprof="";
	};
	
	mysql_select_db($DBASE,$db);
	
	$query2="SELECT id_utente FROM utenti WHERE id_utente='$id_utente' LIMIT 1";
	$result2=$mysqli->query($query2);
	
	if (!$result2->num_rows) {
		$query2 = "INSERT INTO utenti (
id_utente,pwd_utente,data_reg,nome,cognome,indirizzo,cap,citta,prov,telefono,email,sitoweb,sesso,eta,professione,interesse,newsletter,privacy,showme,scuola,stato) VALUES (
 '$id_utente',
'$pwd_utente',NOW(), '$nome','$cognome','$indirizzo', '$cap', '$citta',
'$prov', '$telefono','$email','$sitoweb', '$sesso', '$eta','$professione', '$interesse','','','$eprof','$scuola','1')";
		$result2=$mysqli->query($query2);
	};
	
	$query2="SELECT * FROM iscrizioni_corso WHERE 
	id_gruppo='generale' AND
	id_corso='$id_corso' AND
	id_edizione='$id_edizione' AND
	id_utente='$id_utente'";
	$result2=$mysqli->query($query2);
	if (!$result2->num_rows) {
		$query2="INSERT INTO iscrizioni_corso SET 
		id_gruppo='generale',
		id_corso='$id_corso',
		id_edizione='$id_edizione',
		id_utente='$id_utente'";
		$result2=$mysqli->query($query2);
		echo "$i.$id_utente <br>";
		$i++;
	};
	
	mysql_select_db("atlante",$db);
};
?>
</span>
<hr size=1>
<span class=testo>
<b>Registrazione effettuata.</b>
</span>
<br><br>


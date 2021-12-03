<?php
echo "
<span class=titolopagina>
$stringa[invio_newsletter]
</span>
<hr size=1>";

$id_utente=$kairos_cookie[0];
$oggetto=$_REQUEST["oggetto"];
$invia_staff=$_REQUEST["invia_staff"];
$messaggio=$_REQUEST["messaggio"];
$id_corso_edizione=$_REQUEST["id_corso_edizione"];

list($id_corso_s,$id_edizione_s)=split(" ",$id_corso_edizione);
$errore="";
if (!$oggetto) {
	$errore.="<br>$stringa[errore_manca_oggetto_newsl]";
};

if (!$messaggio) {
	$errore.="<br>$stringa[errore_manca_testo_newsl]";
};

if ($errore) {
	echo "
	<span class=testo>
	<p>$errore</p>
	<a href=javascript:history.back()>[".$stringa[indietro]."]</a>
	</span>";
	exit();
};

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE_UTENTI,$db);

$query = "SELECT email FROM utenti WHERE id_utente='$id_utente'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$email_mittente=$riga["email"];

$query="SELECT email FROM iscrizioni_corso,utenti WHERE utenti.id_utente=iscrizioni_corso.id_utente AND iscrizioni_corso.id_corso='$id_corso_s' AND iscrizioni_corso.id_edizione='$id_edizione_s'";

$result_iscritti=$mysqli->query($query);


$indice=0;
$conta_email=0;

while ($utente = $result_iscritti->fetch_array()) {
	$email = $utente["email"];
	if ($email) {
		$elenco[$indice] .= "$email,";
		$conta_email++;
	};
	
	if ($conta_email==50) {
		$elenco[$indice] = substr($elenco[$indice],0,-1);
		$indice++;
		$conta_email=0;
	};

};


if ($conta_email<>0) {	
	$elenco[$indice] .= $email_mittente;
};


$query="SELECT email FROM utenti,gruppo_utenti WHERE utenti.id_utente=gruppo_utenti.id_tutor AND gruppo_utenti.id_corso='$id_corso_s' AND gruppo_utenti.id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);

$indice=0;
$conta_email=0;

while ($utente = $result->fetch_array()) {
	$email = $utente["email"];
	if ($email) {
		$elenco_staff[$indice] .= "$email,";
		$conta_email++;
	};
	
	if ($conta_email==50) {
		$elenco_staff[$indice] = substr($elenco_staff[$indice],0,-1);
		$indice++;
		$conta_email=0;
	};

};

if ($conta_email<>0) {	
	$elenco_staff[$indice] .= $email_mittente;
};


$messaggio = stripslashes($messaggio);
$oggetto = stripslashes($oggetto);
$id_package=uniqid("");
if ($cod_area<>'kairos_demo') {
	for ($i=0;$i<count($elenco);$i++) {
		$elenco_email=$elenco[$i];
		//echo "elenco email: $elenco_email<br>";
		//mail("","$oggetto","$messaggio",	"From:$email_mittente\nReply-To:$email_mittente\nBCC:$elenco_email");

		mail_job($id_package,"",$oggetto,$messaggio,"$email_mittente","$email_mittente","$elenco_email");
mysql_select_db($DBASE,$db);	
	};
	
	if ($invia_staff=="on") {
	for ($i=0;$i<count($elenco_staff);$i++) {
		$elenco_email=$elenco_staff[$i];
		//echo "elenco email staff: $elenco_email<br>";
		//mail("","$oggetto","$messaggio",	"From:$email_mittente\nReply-To:$email_mittente\nBCC:$elenco_email");

	mail_job($id_package,"",$oggetto,$messaggio,"$email_mittente","$email_mittente","$elenco_email");
mysql_select_db($DBASE,$db);	
	};
	};

};
echo "
<p>
<span class=testo>
<b>$stringa[messaggio_inviato]<b>
</span>
</p>
";
?>

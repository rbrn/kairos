<?php

$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];

$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione_s;

$query="SELECT * FROM corso WHERE id_corso='$id_corso_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$descr_corso=$riga["descrizione"];

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_index><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso_s><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s><span class=testo><b>$stringa[corso]:</b> $descr_corso: $descr_edizione</span></a>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[invio_newsletter])."</b></span>
</td></tr>



<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>
";

$id_utente=$kairos_cookie[0];
$oggetto=$_REQUEST["oggetto"];
$messaggio=$_REQUEST["messaggio"];
$id_gruppo_news=$_REQUEST["id_gruppo_news"];
$invia_staff=$_REQUEST["invia_staff"];

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

$query = "SELECT email,nome,cognome FROM utenti WHERE id_utente='$id_utente'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$email_mittente=$riga["email"];
$nome_mittente=$riga["nome"];
$cognome_mittente=$riga["cognome"];

if (!$id_gruppo_news) {
$query="SELECT email FROM iscrizioni_corso,utenti WHERE utenti.id_utente=iscrizioni_corso.id_utente AND iscrizioni_corso.id_corso='$id_corso_s' AND iscrizioni_corso.id_edizione='$id_edizione_s'";
} else {
	list($id_gruppo,$tipo_gruppo)=split("-",$id_gruppo_news);
	if ($tipo_gruppo==0) {
		$query="SELECT email FROM iscrizioni_corso,utenti WHERE utenti.id_utente=iscrizioni_corso.id_utente AND iscrizioni_corso.id_corso='$id_corso_s' AND iscrizioni_corso.id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo'";
	} else {
		$query="SELECT email FROM iscrizioni_gruppo_pw,utenti WHERE utenti.id_utente=iscrizioni_gruppo_pw.id_utente AND iscrizioni_gruppo_pw.id_corso='$id_corso_s' AND iscrizioni_gruppo_pw.id_edizione='$id_edizione_s' AND iscrizioni_gruppo_pw.id_gruppo='$id_gruppo'";
	}

};

$result_iscritti=$mysqli->query($query);

$indice=0;
$conta_email=0;

while ($utente = $result_iscritti->fetch_array()) {
	$email = $utente["email"];
	
	if ($email and !ereg('^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+'.'@'.'[-#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.'.'[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$', $email)) {
	$email = "";
	};
	
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

//STAFF ADMIN

$indice=0;
$conta_email=0;
	
$query="SELECT email FROM utenti WHERE stato=3";
$result=$mysqli->query($query);

while ($utente = $result->fetch_array()) {
	$email = $utente["email"];
	
	if ($email and !ereg('^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+'.'@'.'[-#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.'.'[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$', $email)) {
	$email = "";
	};

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


if ($invia_staff=="on") {

	//STAFF ESPERTI-DIREZIONE
	$query="SELECT  utenti.email FROM ruolo_utenti,utenti WHERE 
utenti.id_utente=ruolo_utenti.id_utente AND
(ruolo_utenti.ruolo='direttore' OR ruolo_utenti.ruolo='coordinatore' OR  ruolo_utenti.ruolo='docente' OR ruolo_utenti.ruolo='esperto') AND ruolo_utenti.id_corso='$id_corso_s'  AND ruolo_utenti.id_edizione='$id_edizione_s'";

	$result=$mysqli->query($query);

	while ($utente = $result->fetch_array()) {
		$email = $utente["email"];
		
		if ($email and !ereg('^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+'.'@'.'[-#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.'.'[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$', $email)) {
	$email = "";
		};

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
	
	
	//STAFF TUTOR
	$query="SELECT  utenti.email FROM gruppo_utenti,utenti 
WHERE utenti.id_utente=gruppo_utenti.id_tutor AND 
gruppo_utenti.id_corso='$id_corso_s' AND 
gruppo_utenti.id_edizione='$id_edizione_s'";

	$result=$mysqli->query($query);

	while ($utente = $result->fetch_array()) {
		$email = $utente["email"];
		
		if ($email and !ereg('^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+'.'@'.'[-#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.'.'[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$', $email)) {
	$email = "";
		};

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


mail_job($id_package,"",$oggetto,$messaggio,"$nome_mittente $cognome_mittente <$email_mittente>","$email_mittente","$elenco_email");
mysql_select_db($DBASE,$db);	


	};
	
	for ($i=0;$i<count($elenco_staff);$i++) {
		$elenco_email=$elenco_staff[$i];
		//echo "elenco email staff: $elenco_email<br>";

mail_job($id_package,"",$oggetto,$messaggio,"$nome_mittente $cognome_mittente <$email_mittente>","$email_mittente","$elenco_email");
mysql_select_db($DBASE,$db);	

	};
	
};
echo "
<p>
<span class=testo>
<b>$stringa[messaggio_inviato]<b>
</span>
</p>
";
echo "</td></tr></table><br>";
?>

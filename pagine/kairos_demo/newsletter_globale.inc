<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>$stringa[utility]</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[invio_newsletter_globale])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=utility_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=utility_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";


$id_utente=$kairos_cookie[0];
$oggetto=$_REQUEST["oggetto"];
$messaggio=$_REQUEST["messaggio"];

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


$query="SELECT email FROM utenti";
$result=$mysqli->query($query);

$indice=0;
$conta_email=0;

while ($utente = $result->fetch_array()) {
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


$messaggio = stripslashes($messaggio);
$oggetto = stripslashes($oggetto);
if ($cod_area<>'kairos_demo') {
	for ($i=0;$i<count($elenco);$i++) {
		$elenco_email=$elenco[$i];
		//echo "elenco email: $elenco_email<br>";
		//mail("","$oggetto","$messaggio",	"From:$email_mittente\nReply-To:$email_mittente\nBCC:$elenco_email");
		$id_package=uniqid("");
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

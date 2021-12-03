<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$dato_utente=$_REQUEST["dato_utente"];


$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE_UTENTI,$db);	

$errore="";
$query = "SELECT id_utente,pwd_utente,email FROM utenti where id_utente='$dato_utente'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

if (!$riga) {
	$query = "SELECT id_utente,pwd_utente,email FROM utenti where email='$dato_utente'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	if (!$riga) {
		$errore = "1";
	};
};		

if ($errore) {
		$msg="<b>$dato_utente</b>: $stringa[errore_no_dato]";
		$msg=ereg_replace(" ","%20",$msg);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
};

$id_utente = $riga["id_utente"];
$email = $riga["email"];
$pwd_utente = $riga["pwd_utente"];

if ($email) {
mysql_select_db("atlante");
$tipo_area='kairos';
$cod_area_base=substr($cod_area,7,strlen($cod_area));
$query="SELECT id_utente,nomescuola,dominio FROM abbonamenti_piattaforma WHERE cod_area='$cod_area_base'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
	
$id_utente0=$riga["id_utente"];
$nomescuola=$riga["nomescuola"];
$dominio_area=$riga["dominio"];

$query="SELECT email,nome,cognome FROM utenti WHERE id_utente='$id_utente0'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();		
	
$email_admin=$riga["email"];
$nome_admin=$riga["nome"];
$cognome_admin=$riga["cognome"];
mysql_select_db($DBASE);

if ($dominio_area) {
		$firma="http://$dominio_area";
	} else {
		$firma="http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com/scuole/$cod_area_base";
	};
	
$msg = "
$stringa[caro] $id_utente,
$stringa[ecco_parametri]:

$stringa[id]: $id_utente 		
$stringa[pw]: $pwd_utente 			

$stringa[scrivi_parametri]

$nome_admin $cognome_admin ($id_utente0)
$stringa[amministratore_area]
$firma"; 


$id_package=uniqid("");	
mail_job($id_package,"$email","[$cod_area]: $stringa[parametri_accesso]","$msg","$nome_admin $cognome_admin <$email_admin>","$email_admin","");
mysql_select_db($DBASE,$db);	
//@mail("$email","[$cod_area]: $stringa[parametri_accesso]","$msg","From:$email_admin\nReply-To:$email_admin");

/*
$subject="[$cod_area]: $stringa[parametri_accesso]";
$subject=addslashes($subject);
$msg=addslashes($msg);

$fd = popen("/usr/sbin/sendmail -t","w"); 
fputs($fd, "To: $email\n"); 
fputs($fd, "From: $email_admin\n"); 
fputs($fd, "Subject: $subject\n"); 
fputs($fd, "X-Mailer: PHP\n"); 
fputs($fd, "$msg\n"); 
pclose($fd);
*/

};

if ($id_utente=="enza62" or $id_utente=="emcinelli" or $id_utente=="AntonioTul") {
	$msg="$stringa[id]: <b>$id_utente</b>. $stringa[pw_inviata]";
} else {
	$msg="$stringa[id]: <b>$id_utente</b>, $stringa[email]: <b>$email</b>. $stringa[pw_inviata]";
};
$msg=ereg_replace(" ","%20",$msg);
Header("Location:index.php?risorsa=msg&msg=$msg");
?>

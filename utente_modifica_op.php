<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$ruolo=ruolo_utente($kairos_cookie[0]);
if ($ruolo<>"admin") {
	$msg="Accesso riservato solo allo staff.";
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};


$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];
$immagine=$_FILES["immagine"]["tmp_name"];
$immagine_size=$_FILES["immagine"]["size"];
$immagine_name=$_FILES["immagine"]["name"];
$immagine_type=$_FILES["immagine"]["type"];

$id_utente=$_REQUEST["id_utente0"];
$ex_email=$_REQUEST["ex_email"];
$pwd_utente=$_REQUEST["pwd_utente"];
$nome=$_REQUEST["nome"];
$cognome=$_REQUEST["cognome"];
$indirizzo=$_REQUEST["indirizzo"];
$cap=$_REQUEST["cap"];
$citta=$_REQUEST["citta"];
$prov=$_REQUEST["prov"];
$telefono=$_REQUEST["telefono"];
$email=$_REQUEST["email"];
$sitoweb=$_REQUEST["sitoweb"];
$sesso=$_REQUEST["sesso"];
$eta=$_REQUEST["eta"];
$professione=$_REQUEST["professione"];
$interesse=$_REQUEST["interesse"];
$newsletter=$_REQUEST["newsletter"];
$biografia=$_REQUEST["biografia"];
$scuola=$_REQUEST["scuola"];
$stato=$_REQUEST["stato"];
$ex_stato=$_REQUEST["ex_stato"];
$ruolo_scuola=$_REQUEST["ruolo_scuola"];
$materia=$_REQUEST["materia"];
$liberatoria=$_REQUEST["liberatoria"];

// controllo se tutti i campi obbligatori sono stati compilati

$errore = "";

if ($immagine_name) {
	$est = strtolower(substr($immagine_name,-3));
	if ($est != "gif" and $est != "jpg") {
		$errore .= "<br>$stringa[errore_gif_jpg]";
	};
};			
		
if ($immagine_size > $MAX_FILE_SIZE) {
		$errore .= "<br>$stringa[errore_max_file]";
};	
				
if (!$nome) {
		$errore .= "<br>$stringa[errore_manca_nome]";
	};	

if (!$cognome) {
	$errore .= "<br>$stringa[errore_manca_cognome]";
	};	
	

if ($cod_area<>"kairos_larimart") {
if (!$indirizzo) {
	$errore .= "<br>$stringa[errore_manca_indirizzo]";
};			
		
if (!$cap) {
	$errore .= "<br>$stringa[errore_manca_cap]";
};			

if (!$citta) {
	$errore .= "<br>$stringa[errore_manca_citta]";
};	

if (!$prov) {
	$errore .= "<br>$stringa[errore_manca_prov]";
};			

if (!$scuola) {
	$errore .= "<br>$stringa[errore_manca_scuola]";
};				
		
if (!$telefono) {
	$errore .= "<br>$stringa[errore_manca_telefono]";
};	

if ($ruolo_scuola=='Insegnante' and !$materia) {
	$errore .= "<br>$stringa[errore_manca_materia]";
};	


if (!$email) {
	$errore .= "<br>$stringa[errore_manca_email]";
};

/*		
if (!ereg('^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+'.'@'.'[-#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.'.'[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$', $email)) {
	$errore .= "<br>$stringa[errore_email_invalido]";
};

if (!$eta) {
		$errore .= "<br>$stringa[errore_manca_eta]";
};

if (!$sesso) {
		$errore .= "<br>$stringa[errore_manca_sesso]";
};


if ($email<>$ex_email) {
	$query = "SELECT id_utente FROM utenti where email='$email'";
	$result = mysql_query($query,$db);
	$riga = mysql_fetch_array($result);
	if ($riga) {
		$errore = "<br>$stringa[errore_email_esiste]";
	};
};	
*/	

};
		
if ($errore) {
		$msg= "<b>$stringa[errore]</b>:<br><br><b>".$errore."</b>";
		echo "
	<html>
	<head><title>Kair�s: $stringa[errore]</title>
	<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
	<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
	</HEAD>
	<BODY bgcolor=$colore_sfondo>
	<p>
	<span class=testo>$msg</span>
	</p>
	<span class=testo>
	<a href=javascript:history.back()>[".$stringa[indietro]."]</a>
	</span>
	</body>
	</html>";
	exit();
};


$cod_area_base=substr($cod_area,7,strlen($cod_area));
if ($cod_area_base=='itcgluzzatti' or $cod_area_base=='ipsiaeascione') {
	$operazione="update";
	require "./include/".$cod_area_base."_replica_db.inc";
	mysql_select_db($DBASE);
} else {
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
	$result = $mysqli->query($query);
};

if ($immagine_name) {
	$immagine_name = trim("$id_utente.$est");
	$immagine_name = ereg_replace(" ","",$immagine_name);
	$immagine_name = strtolower($immagine_name);
	$fullpath = $PATH_ROOT_FILE."foto_utenti/$cod_area/".$immagine_name;
	copy($immagine,$fullpath);	
};

if ($ex_stato==0 and $stato<>0) {
	$tipo_area='kairos';
	$cod_area_base=substr($cod_area,7,strlen($cod_area));

	$query="SELECT * FROM abbonamenti_piattaforma WHERE cod_area='$cod_area_base'";
    $result = $mysqli->query($query);
    $riga= $result->fetch_array();
	$utente_admin=$riga["id_utente"];
	$nomescuola=$riga["nomescuola"];
	$dominio_area=$riga["dominio"];
	$query="SELECT email,nome,cognome FROM utenti WHERE id_utente='$utente_admin'";
    $result = $mysqli->query($query);
	$riga= $result->fetch_array();
	$email_admin=$riga["email"];
	$nome_admin=$riga["nome"];
	$cognome_admin=$riga["cognome"];
	
	if ($dominio_area) {
		$firma="http://$dominio_area";
	} else {
		$firma=APP_URL."/kairos/$cod_area_base";
	};
	$msg = "
$stringa[caro] $id_utente,
$stringa[ecco_parametri]:

$stringa[id]: $id_utente 		
$stringa[pw]: $pwd_utente 		

$stringa[scrivi_parametri]

$nome_admin $cognome_admin ($utente_admin)
$stringa[amministratore_area]
$firma
"; 
if ($email) {
	mail("$email","[$cod_area]: $stringa[parametri_accesso]","$msg","From:$email_admin\nReply-To:$email_admin");
	$id_package=uniqid("");	
	mail_job($id_package,"$email","[$cod_area]: $stringa[parametri_accesso]","$msg","$nome_admin $cognome_admin <$email_admin>","$email_admin","");

};
};


echo "<p><font face=verdana size=-1>$stringa[utente_modificato]</span></p><a href=javascript:self.close()>[".$stringa[chiudi]."]</a></font>";
		
?>

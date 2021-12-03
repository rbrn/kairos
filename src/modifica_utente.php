<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
 
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];
$immagine=$_FILES["immagine"]["tmp_name"];
$immagine_size=$_FILES["immagine"]["size"];
$immagine_name=$_FILES["immagine"]["name"];
$immagine_type=$_FILES["immagine"]["type"];

$id_utente=$_REQUEST["id_utente"];
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
$ruolo_scuola=$_REQUEST["ruolo_scuola"];
$materia=$_REQUEST["materia"];

			
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
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	if ($riga) {
		$errore = "<br>$stringa[errore_email_esiste]";
	};
};	
*/
	
};
		
if ($errore) {
		$msg= "<b>$stringa[errore]</b>:<br><br><b>".$errore."</b>";
		$msg=ereg_replace(" ","%20",$msg);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
};

$cod_area_base=substr($cod_area,7,strlen($cod_area));
if ($cod_area_base=='itcgluzzatti' or $cod_area_base=='ipsiaeascione') {
	$operazione="modifica";
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
			ruolo_scuola='$ruolo_scuola',
			materia='$materia'
			WHERE id_utente='$id_utente'";
			
	$result=$mysqli->query($query);
};

if ($immagine_name) {
	$immagine_name = trim("$id_utente.$est");
	$immagine_name = str_replace(" ","",$immagine_name);
	$immagine_name = strtolower($immagine_name);
	$fullpath = $PATH_ROOT_FILE."foto_utenti/$cod_area/".$immagine_name;
	
	$img_gif=$PATH_ROOT_FILE."foto_utenti/$cod_area/".strtolower($id_utente).".gif";
	if (file_exists($img_gif)) unlink($img_gif);
	
	$img_jpg=$PATH_ROOT_FILE."foto_utenti/$cod_area/".strtolower($id_utente).".jpg";
	if (file_exists($img_jpg)) unlink($img_jpg);
	
	copy($immagine,$fullpath);	
};

setCookies($id_utente,md5($pwd_utente));

if ($cod_area=='kairos_area_corsi') {
mysql_select_db("atlante",$db);

$query = "UPDATE utenti SET
			pwd_utente='$pwd_utente',
			nome='$nome',
			cognome='$cognome',
			indirizzo='$indirizzo',
			cap='$cap',
			citta='$citta',
			prov='$prov',
			telefono='$telefono',
			email='$email'
			WHERE id_utente='$id_utente'";
		
$result=$mysqli->query($query);
};

Header("Location:index.php?risorsa=index");
		
?>

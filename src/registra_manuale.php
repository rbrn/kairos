<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
 
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_utente=$_REQUEST["id_utente"];
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
$ruolo_scuola=$_REQUEST["ruolo_scuola"];
$materia=$_REQUEST["materia"];
$tutor_fortic=$_REQUEST["tutor_fortic"];
$scuola_fortic=$_REQUEST["scuola_fortic"];

$id_c=$_REQUEST["id_c"];
$id_g=$_REQUEST["id_g"];

$id_gruppo_reg=$_REQUEST["id_gruppo_reg"];

// controllo se tutti i campi obbligatori sono stati compilati

$errore = "";
$id_utente=trim($id_utente);
$id_utente = str_replace(" ","",$id_utente);
$id_utente=strtolower($id_utente);
	
$pwd_utente=trim($pwd_utente);
$pwd_utente = str_replace(" ","",$pwd_utente);
$pwd_utente=strtolower($pwd_utente);
	
if (!$id_utente) {
	$errore .= "<br>$stringa[errore_manca_id]";
} else {	 
	if (eregi("[^a-zA-Z0-9_\.]{1,}",$id_utente)) {
		$errore .= "<br>$stringa[errore_solo_lettere]";
	};
};

if (!$pwd_utente) {
	$errore .= "<br>$stringa[errore_manca_pw]";
} else {
	if (eregi("[^a-zA-Z0-9_\.]{1,}",$pwd_utente)) {
		$errore .= "<br>$stringa[errore_solo_lettere_pw]";
	};
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

if (!$scuola and $ruolo_scuola<>"Nessuno") {
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


		
if ($email and !ereg('^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+'.'@'.'[-#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.'.'[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$', $email)) {
	$errore .= "<br>$stringa[errore_email_invalido]";
};

/*
if (!$eta) {
		$errore .= "<br>$stringa[errore_manca_eta]";
};

if (!$sesso) {
		$errore .= "<br>$stringa[errore_manca_sesso]";
};
*/
};

// controllo se esiste giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ l'ID utente

if (!$errore) {
	$query = "SELECT id_utente FROM utenti where id_utente='$id_utente'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	if ($riga) {
		$errore = "<br>$stringa[errore_id_esiste]";
	};
};

		
if ($errore) {
		$msg= "<b>$stringa[errore]</b>:<br><br><b>".$errore."</b>";
		$msg=ereg_replace(" ","%20",$msg);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
};

/*
if (!$errore) {
	if ($email) {
	$query = "SELECT id_utente FROM utenti where email='$email'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	if ($riga) {
		$errore = "<br>$stringa[errore_email_esiste]";
	};
	};
};	
*/

// tutto OK inserisco i dati dell'utente nella tabella
			
// mi invento una password...

if (!$pwd_utente) {			
	$pwd_utente = substr(join('', gettimeofday()), 0, 10);
};
		
$privacy="";

$cod_area_base=substr($cod_area,7,strlen($cod_area));
if ($cod_area_base=='itcgluzzatti' or $cod_area_base=='ipsiaeascione') {
	$operazione="insert";
	require "./include/".$cod_area_base."_replica_db.inc";
	mysql_select_db($DBASE);
} else {			
	$query = "INSERT INTO utenti (
id_utente,pwd_utente,data_reg,nome,cognome,indirizzo,cap,citta,prov,telefono,email,sitoweb,sesso,eta,professione,interesse,newsletter,privacy,showme,scuola,stato,ruolo_scuola,materia) VALUES (
 '$id_utente',
'$pwd_utente',NOW(), '$nome','$cognome','$indirizzo', '$cap', '$citta',
'$prov', '$telefono','$email','$sitoweb', '$sesso', '$eta','$professione', '$interesse','$newsletter','$privacy','on','$scuola','$stato','$ruolo_scuola','$materia')";
	$result=$mysqli->query($query);
};

if ($cod_area=='kairos_fortic' and $tutor_fortic) {
	$query="REPLACE INTO tutor_fortic SET id_utente='$id_utente',scuola='$scuola_fortic'";
	$mysqli->query($query);
};

if ($stato==1) {
for ($i=0;$i<count($id_g);$i++) {
	list($corso,$edizione,$gruppo)=split(" ",$id_g[$i]);
	$indice="$corso $edizione";
	$gruppo_corso[$indice]=$gruppo;
};

for ($i=0;$i<count($id_c);$i++) {
	$corso=$id_c[$i];
		
	if ($gruppo_corso[$corso]) {
		$gruppo=$gruppo_corso[$corso];
	} else {
		$gruppo="";
	};
	list($id_cor,$id_ed)=split(" ",$corso);
	$query="INSERT INTO iscrizioni_corso (id_corso,id_edizione,id_gruppo,id_utente,data_iscrizione) VALUES ('$id_cor','$id_ed','$gruppo','$id_utente',NOW())";
	$mysqli->query($query);
	
};
};

if ($cod_area=="kairos_larimart") {
	$query="SELECT * FROM edizioni WHERE stato='attiva'";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_corso=$riga["id_corso"];
		$id_edizione=$riga["id_edizione"];
		$query_i="INSERT INTO iscrizioni_corso SET
		id_utente='$id_utente',
		id_corso='$id_corso',
		id_edizione='$id_edizione',
		id_gruppo='$id_gruppo_reg'";
		$mysqli->query($query_i);
	};
};

$msg=$stringa[registrazione_man_fatta];
$msg=ereg_replace(" ","%20",$msg);

header("Location:index.php?risorsa=msg&msg=$msg");
			
?>

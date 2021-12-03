<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
 
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_utente=mysql_real_escape_string($_REQUEST["id_utente"])	;
$pwd_utente=$_REQUEST["pwd_utente"];
$nome=mysql_real_escape_string($_REQUEST["nome"]);
$cognome=mysql_real_escape_string($_REQUEST["cognome"]);
$indirizzo=mysql_real_escape_string($_REQUEST["indirizzo"]);
$cap=$_REQUEST["cap"];
$citta=mysql_real_escape_string($_REQUEST["citta"]);
$prov=mysql_real_escape_string($_REQUEST["prov"]);
$telefono=$_REQUEST["telefono"];
$email=$_REQUEST["email"];
$sitoweb=$_REQUEST["sitoweb"];
$sesso=$_REQUEST["sesso"];
$eta=$_REQUEST["eta"];
$professione=mysql_real_escape_string($_REQUEST["professione"]);
$interesse=mysql_real_escape_string($_REQUEST["interesse"]);
$newsletter=$_REQUEST["newsletter"];
$biografia=mysql_real_escape_string($_REQUEST["biografia"]);
$scuola=mysql_real_escape_string($_REQUEST["scuola"]);
$ruolo_scuola=mysql_real_escape_string($_REQUEST["ruolo_scuola"]);
$materia=mysql_real_escape_string($_REQUEST["materia"]);
$tutor_fortic=mysql_real_escape_string($_REQUEST["tutor_fortic"]);
$scuola_fortic=mysql_real_escape_string($_REQUEST["scuola_fortic"]);

$id_eproffaro=mysql_real_escape_string($_REQUEST["id_eproffaro"]);
$autorizzo_privacy=$_REQUEST["autorizzo_privacy"];

if ($cod_area=="kairos_atlanteragazzi") $ruolo_scuola="Studente";

$id_c=$_REQUEST["id_c"];
$id_g=$_REQUEST["id_g"];

$id_gruppo_reg=$_REQUEST["id_gruppo_reg"];

$codice_cd=$_REQUEST["codice_cd"];
$codice_libro=$_REQUEST["codice_libro"];

if ($cod_area=="kairos_librinrete") {
	$materia=".";
	$ruolo_scuola="Insegnante";
};
/*
for ($i=0;$i<count($id_g);$i++) {
	list($corso,$edizione,$gruppo)=split(" ",$id_g[$i]);
	$indice="$corso $edizione";
	$gruppo_corso[$indice]=$gruppo;
};

for ($i=0;$i<count($id_c);$i++) {
	$corso=$id_c[$i];
	echo "corso: $corso";

	if ($gruppo_corso[$corso]) {
		echo " - gruppo: $gruppo_corso[$corso]<br>";
	} else {
		echo " - gruppo non presente<br>";
	};
};

exit();
*/

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

if (!$id_eproffaro and $cod_area=="kairos_atlanteragazzi") {
	$errore .= "<br>Manca l'ID dell'insegnante e-prof di cui sei alunno/a";
};	

if (!$nome) {
	$errore .= "<br>$stringa[errore_manca_nome]";
};	

if (!$cognome) {
	$errore .= "<br>$stringa[errore_manca_cognome]";
};	

if ($codice_cd) {
	$codice_cd=trim($codice_cd);
	$numero=substr($codice_cd,0,4);
	$c1=substr($numero,0,1);
	$c2=substr($numero,1,1);
	$c3=substr($numero,2,1);
	$c4=substr($numero,3,1);

	$d1=abs(($c4-$c3+$c2-$c1) % 10);
	$d2=abs(($c4+3*$c1-1) % 10);
	$d3=abs(($c1-$c3+2*$c4-1) % 10);
	$d4=abs(($c2-$c3+$c1-$c4) % 10);
	$codice=$c1.$c2.$c3.$c4."-".$d1.$d2.$d3.$d4;	
	
	if ($codice<>$codice_cd) {
		$errore .= "<br>Codice CD errato";
	};
};

if ($cod_area=="kairos_librinrete" and !$codice_libro) {
	$errore .="<br>Manca il Codice Libro";
};

if ($codice_libro) {
	$codice_libro=trim($codice_libro);
	list($prefisso_base,$i,$calcolo)=split("-",$codice_libro);
	$c1=substr($i,0,1);
	$c2=substr($i,1,1);
	$c3=substr($i,2,1);
	$c4=substr($i,3,1);
	$c5=substr($i,4,1);
	if (!$c5) $c5="0";

	$d1=abs(($c4-$c3+$c2-$c1) % 10);
	$d2=abs(($c4+4*$c1-1) % 10);
	$d3=abs(($c1-$c3+3*$c4-1) % 10);
	$d4=abs(($c2-$c3+$c1-$c4) % 10);
	$d5=abs((3*$c4-$c3+$c5-$c1) % 10);

	$codice=$prefisso_base."-".$c1.$c2.$c3.$c4.$c5."-".$d1.$d2.$d3.$d4.$d5;

	if ($codice<>$codice_libro) {
		$errore .= "<br>Codice Libro non valido";
	};

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

if ($ruolo_scuola=='Insegnante' and !$materia and $cod_area<>"kairos_amicosole" and $cod_area<>'kairos_oppla' and $cod_area<>"kairos_bandaingamba") {
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
		$errore .= "<br>$stringa[errore_id_esiste]";
	};
};

if (!$errore and $cod_area=="kairos_atlanteragazzi") {
	$query = "SELECT id_utente FROM utenti where id_utente='$id_eproffaro'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	if (!$riga) {
		$errore .= "<br>Non esiste l'insegnante e-prof con ID: $id_eproffaro";
	};
};


if (!$errore and $cod_area=="kairos_librinrete" and $codice_libro and $codice_libro<>"amicosole-50000-59455" and $prefisso_base<>"agenzia") {
	$query = "SELECT id_utente FROM utenti where codice_libro='$codice_libro'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	if ($riga) {
		$errore .= "<br>Il Codice Libro ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ stato usato da un altro utente";
	};
};

if ($cod_area=="kairos_librinrete") {
	$prefisso_base=trim(strtolower($prefisso_base));
	if ($prefisso_base<>"amicosole" and $prefisso_base<>"villaggiorete" and $prefisso_base<>"quadratomagico" and $prefisso_base<>"dirittoeconomia" and $prefisso_base<>"azienda" and $prefisso_base<>"agenzia") {
		$errore .= "<br>Hai indicato un codice libro errato!";
	};
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

if ($cod_area=="kairos_amicosole" or $cod_area=='kairos_oppla' or $cod_area=="kairos_bandaingamba") {

	if ($autorizzo_privacy<>"1") {

		$errore .= "<br>E' necessario fornire il consenso al trattamento dei dati";
	};
};

if ($errore) {
		$msg= "<b>$stringa[errore]</b>:<br><br><b>".$errore."</b>";
		$msg=ereg_replace(" ","%20",$msg);
		Header("Location:index.php?risorsa=msg&msg=$msg");
		exit();
};

// tutto OK inserisco i dati dell'utente nella tabella
			
// mi invento una password...

if (!$pwd_utente) {			
	$pwd_utente = substr(join('', gettimeofday()), 0, 10);
};
		
$privacy="";
			
$stato=0;
if ($cod_area=='kairos_demo') {
	$stato=2;
};

if ($cod_area=='kairos_larimart' and $codice_cd) $stato=1;
if ($cod_area=='kairos_librinrete' and $codice_libro) $stato=1;
if ($cod_area=='kairos_librinrete' and $codice_libro and $prefisso_base=="agenzia") $stato=2;
if ($cod_area=='kairos_oppla') $stato=1;
if ($cod_area=='kairos_bandaingamba') $stato=1;

$cod_area_base=substr($cod_area,7,strlen($cod_area));
if ($cod_area_base=='itcgluzzatti' or $cod_area_base=='ipsiaeascione') {
	$operazione="insert";
	require "./include/".$cod_area_base."_replica_db.inc";
	mysql_select_db($DBASE);
} else {
	if ($cod_area<>"kairos_librinrete") {
		if ($cod_area<>"kairos_atlanteragazzi") {
			$query = "INSERT INTO utenti (
id_utente,pwd_utente,data_reg,nome,cognome,indirizzo,cap,citta,prov,telefono,email,sitoweb,sesso,eta,professione,interesse,newsletter,privacy,showme,scuola,stato,ruolo_scuola,materia) VALUES (
 '$id_utente',
'$pwd_utente',NOW(), '$nome','$cognome','$indirizzo', '$cap', '$citta',
'$prov', '$telefono','$email','$sitoweb', '$sesso', '$eta','$professione', '$interesse','$newsletter','$privacy','on','$scuola','$stato','$ruolo_scuola','$materia')";
		} else {
			$query = "INSERT INTO utenti (
id_utente,pwd_utente,data_reg,nome,cognome,indirizzo,cap,citta,prov,telefono,email,sitoweb,sesso,eta,professione,interesse,newsletter,privacy,showme,scuola,stato,ruolo_scuola,materia,id_eproffaro) VALUES (
 '$id_utente',
'$pwd_utente',NOW(), '$nome','$cognome','$indirizzo', '$cap', '$citta',
'$prov', '$telefono','$email','$sitoweb', '$sesso', '$eta','$professione', '$interesse','$newsletter','$privacy','on','$scuola','$stato','$ruolo_scuola','$materia','$id_eproffaro')";
		}
	} else {
	$query = "INSERT INTO utenti (
id_utente,pwd_utente,data_reg,nome,cognome,indirizzo,cap,citta,prov,telefono,email,sitoweb,sesso,eta,professione,interesse,newsletter,privacy,showme,scuola,stato,ruolo_scuola,materia,codice_libro) VALUES (
 '$id_utente',
'$pwd_utente',NOW(), '$nome','$cognome','$indirizzo', '$cap', '$citta',
'$prov', '$telefono','$email','$sitoweb', '$sesso', '$eta','$professione', '$interesse','$newsletter','$privacy','on','$scuola','$stato','$ruolo_scuola','$materia','$codice_libro')";
	};
	$result=$mysqli->query($query);
	if ($prefisso_base=="amicosole") {
		$query = "INSERT INTO utenti (
id_utente,pwd_utente,data_reg,nome,cognome,indirizzo,cap,citta,prov,telefono,email,sitoweb,sesso,eta,professione,interesse,newsletter,privacy,showme,scuola,stato,ruolo_scuola,materia) VALUES (
 '$id_utente',
'$pwd_utente',NOW(), '$nome','$cognome','$indirizzo', '$cap', '$citta',
'$prov', '$telefono','$email','$sitoweb', '$sesso', '$eta','$professione', '$interesse','$newsletter','$privacy','on','$scuola','0','Insegnante','$materia')";
		mysql_select_db("kairos_amicosole");
		$result=$mysqli->query($query);
		mysql_select_db($DBASE); 
	};
};


if ($cod_area=='kairos_fortic' and $tutor_fortic) {
	$query="REPLACE INTO tutor_fortic SET id_utente='$id_utente',scuola='$scuola_fortic'";
	$mysqli->query($query);
};

if ($stato==0) {
$iscrizioni="";
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
	$iscrizioni .= "$id_cor ($id_ed) gruppo: $gruppo \n";
	$mysqli->query($query);
	
};
/*
if (!$iscrizioni) {
	$errore="E' necessario selezionare almeno un corso da seguire in Kairos";
	$msg= "<b>$stringa[errore]</b>:<br><br><b>".$errore."</b>";
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};
*/
};

$prefisso_base=trim(strtolower($prefisso_base));

if ($cod_area=="kairos_librinrete" and $stato==1) {
	switch ($prefisso_base) {
		case "amicosole":
			$id_corso="01amicosole";
			$testo="Amicosole";
			break;
			
		case "quadratomagico":
			$id_corso="02quadratomagico";
			$testo="Il quadrato magico";
			break;
	
		case "villaggiorete":
			$id_corso="03villaggiorete";
			$testo="Dal villaggio alla rete";
			break;
			
		case "dirittoeconomia":
			$id_corso="04dirittoeconomia";
			$testo="Il mondo del diritto e dell'economia ";
			break;
			
		case "azienda":
			$id_corso="05azienda";
			$testo=" Entriamo in azienda ";
			break;
			
		case "prova":
			$id_corso="prova_reg";
			$testo=" Prova registrazione ";
			break;
			
		case "agenzia":
			$id_corso="redazione";
			$testo=" Staff e Redazione ";
			break;
	};

	$id_edizione="edizione1";
	
	$id_min="Generale";
	$query_cg="SELECT * FROM iscrizioni_corso WHERE id_gruppo='$id_min' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
	$result_cg=$mysqli->query($query_cg);
	$min=$result_cg->num_rows;
	
	
	//individuo il gruppo a cui iscrivere l'utente
	$query_g="SELECT * FROM gruppo_utenti WHERE tipo_gruppo='0' AND id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_gruppo<>'Generale'";
	$result_g=$mysqli->query($query_g);
	
	while ($riga_g=$result_g->fetch_array()) {
		$id_gruppo_reg=$riga_g[id_gruppo];
		$query_cg="SELECT * FROM iscrizioni_corso WHERE id_gruppo='$id_gruppo_reg' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
		$result_cg=$mysqli->query($query_cg);
		$n=$result_cg->num_rows;
	
		if ($n<$min) {
			$min=$n;
			$id_min=$id_gruppo_reg;
		};
	};
	
	if ($min>=50) {
		$query_g="SELECT * FROM gruppo_utenti WHERE tipo_gruppo='0' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
		$result_g=$mysqli->query($query_g);
		$n=$result_g->num_rows;
		$n++;
		$id_min="gruppo".$n;
		
		$query_i="INSERT INTO gruppo_utenti SET
		id_corso='$id_corso',
		id_edizione='$id_edizione',
		id_gruppo='$id_min',
		tipo_gruppo='0',
		descrizione='$id_min'";
		$mysqli->query($query_i);
		
		$msg="E' stato creato un nuovo gruppo a cui e' necessario assegnare descrizione e tutor: $id_min";
		
		$msg=stripslashes($msg);
		
		$id_package=uniqid("");	
		mail_job($id_package,"aquadrino@garamond.it","[$cod_area] creato nuovo gruppo","$msg","sysadmin@garamond.it","sysadmin@garamond.it","");
		mysql_select_db($DBASE,$db);	
	};
		
	$query_i="INSERT INTO iscrizioni_corso SET
	id_utente='$id_utente',
	id_corso='$id_corso',
	id_edizione='$id_edizione',
	data_iscrizione=NOW(),
	id_gruppo='$id_min'";
	$mysqli->query($query_i);
};

if ($cod_area<>'kairos_demo' and $cod_area<>'kairos_librinrete' and $cod_area<>'kairos_oppla' and $cod_area<>"kairos_bandaingamba") {
	mysql_select_db("atlante");
	$tipo_area='kairos';
	$cod_area_base=substr($cod_area,7,strlen($cod_area));
	$query="SELECT id_utente FROM abbonamenti_piattaforma WHERE cod_area='$cod_area_base'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	
	$id_utente0=$riga["id_utente"];
	
 	$query="SELECT email FROM utenti WHERE id_utente='$id_utente0'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();		
	
	$email=$riga["email"];

	if ($cod_area=='kairos_itc_scuola') $email="consulenti@garamond.it";
	
	if (!$email) {
		$email="sysadmin@garamond.it";
	};
	
	mysql_select_db($DBASE);
	
	$msg = "
	$stringa[utente_si_e_registrato] ($cod_area):
	
	$stringa[id]: $id_utente
	$stringa[nome]: $nome
	$stringa[cognome]: $cognome";
	
	if ($iscrizioni) $msg .= "
	$stringa[iscrizioni_effettuate]:\n$iscrizioni\n"; 
	
	if ($cod_area=='kairos_fortic' and $tutor_fortic) $msg .= "\nUtente tutor ForTIC\n";
	
	$msg .="\n$stringa[conferma_registrazione_guida]\n$codice_cd"; 

	$msg=stripslashes($msg);
	//mail("$email","[$cod_area] $stringa[richiesta_registrazione]","$msg","From:fleo@garamond.it\nReply-To:fleo@garamond.it");

	$id_package=uniqid("");	
	mail_job($id_package,"$email","[$cod_area] $stringa[richiesta_registrazione]","$msg","sysadmin@garamond.it","sysadmin@garamond.it","");

	mysql_select_db($DBASE,$db);	

	if ($cod_area=='kairos_larimart') {
		$msg="<b>$stringa[grazie], $id_utente!</b> La tua richiesta di registrazione ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ stata inoltrata all'amministratore del sistema che provvederÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ ad autorizzarla entro le prossime 24 ore lavorative. Se hai inserito un <b>Codice CD</b> valido, la tua registrazione ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ invece immediatamente attiva e puoi giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ entrare con i parametri di ID e PW che hai scelto.";
	} else {
		$msg="<b>$stringa[grazie], $id_utente!</b> <br><br> $stringa[richiesta_inoltrata]";
	};
	
	$msg=ereg_replace(" ","%20",$msg);
} else {
	if ($cod_area=='kairos_demo') {
	$msg = "
Ciao $nome $cognome,
$stringa[benvenuto_demo]

$stringa[id]: $id_utente 		
$stringa[pw]: $pwd_utente 			

$stringa[scrivi_parametri]

Garamond Editoria e Formazione
http://www.garamond.it";

	//mail("$email","Garamond: $stringa[registrazione_demo]","$msg","From:atlante@garamond.it\nReply-To:atlante@garamond.it");

	$id_package=uniqid("");	
	//mail_job($id_package,"$email","Garamond: $stringa[registrazione_demo]","$msg","atlante@garamond.it","atlante@garamond.it","");
	mysql_select_db($DBASE,$db);	
	
$msg = "
	Il seguente utente si e registrato all'area demo di Kairos:
	
	Id: $id_utente
	Nome: $nome
	Cognome: $cognome"; 

	$msg=stripslashes($msg);
	//mail("ordini@garamond.it","[Kairos_demo] Registrazione","$msg","From:fleo@garamond.it\nReply-To:fleo@garamond.it");
	
	$id_package=uniqid("");	
	//mail_job($id_package,"ordini@garamond.it","[Kairos_demo] Registrazione","$msg","sysadmin@garamond.it","sysadmin@garamond.it","");
	mysql_select_db($DBASE,$db);	
	$msg="<b>$stringa[grazie], $id_utente!</b> <br><br> $stringa[parametri_inviati]";
	$msg=ereg_replace(" ","%20",$msg);
	};

	if ($cod_area=='kairos_librinrete') {
	$msg = "
Ciao $nome $cognome,
ti diamo il benvenuto all'area Libri in Rete dedicata al testo: $testo
Ti riepiloghiamo i parametri di accesso:

$stringa[id]: $id_utente
$stringa[pw]: $pwd_utente

$stringa[scrivi_parametri]

La redazione Libri in Rete RCS-Education
http://librinrete.garamond.it";

	$id_package=uniqid("");
	//mail_job($id_package,"$email","Libri In Rete: conferma registrazione","$msg","librinrete@garamond.it","librinrete@garamond.it","");
	mysql_select_db($DBASE,$db);

$msg = "
	Il seguente utente si ? registrato all'area Libri in Rete:

	Id: $id_utente
	Nome: $nome
	Cognome: $cognome
	Testo: $testo
	";

	$msg=stripslashes($msg);

	$id_package=uniqid("");
	//mail_job($id_package,"ordini@garamond.it","[Librinrete] Registrazione","$msg","sysadmin@garamond.it","sysadmin@garamond.it","");
	mysql_select_db($DBASE,$db);
	$msg="<b>$stringa[grazie], $id_utente!</b> <br><br> Puoi gi? accedere all'area con i parametri che hai indicato nella registrazione e che ti abbiamo comunque inviato anche al tuo e-mail.";
	$msg=ereg_replace(" ","%20",$msg);
	};


	if ($cod_area=='kairos_oppla') {
	$msg = "
Ciao $nome $cognome,
ti diamo il benvenuto all'area dedicata al testo: Oppla'
Ti riepiloghiamo i parametri di accesso:

$stringa[id]: $id_utente
$stringa[pw]: $pwd_utente

$stringa[scrivi_parametri]

La redazione
http://oppla.garamond.it";

	$id_package=uniqid("");
	//mail_job($id_package,"$email","Oppla: conferma registrazione","$msg","redazione@rcs.it","redazione@rcs.it","");
	mysql_select_db($DBASE,$db);

	$msg="<b>$stringa[grazie], $id_utente!</b> <br><br> Puoi gi? accedere all'area con i parametri che hai indicato nella registrazione e che ti abbiamo comunque inviato anche al tuo e-mail.";
	$msg=ereg_replace(" ","%20",$msg);
	};

	if ($cod_area=='kairos_bandaingamba') {
	$msg = "
Ciao $nome $cognome,
ti diamo il benvenuto all'area dedicata al testo: Bandaingamba
Ti riepiloghiamo i parametri di accesso:

$stringa[id]: $id_utente
$stringa[pw]: $pwd_utente

$stringa[scrivi_parametri]

La redazione
http://bandaingamba.garamond.it";

	$id_package=uniqid("");
	//mail_job($id_package,"$email","bandaingamba: conferma registrazione","$msg","redazione@rcs.it","redazione@rcs.it","");
	mysql_select_db($DBASE,$db);

	$msg="<b>$stringa[grazie], $id_utente!</b> <br><br> Puoi gi? accedere all'area con i parametri che hai indicato nella registrazione e che ti abbiamo comunque inviato anche al tuo e-mail.";
	$msg=ereg_replace(" ","%20",$msg);
	};
};

if ($cod_area=="kairos_larimart" and $stato==1) {
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

if ($cod_area=="kairos_atlanteragazzi") {
	$query="SELECT * FROM edizioni WHERE stato='attiva'";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_corso=$riga["id_corso"];
		$id_edizione=$riga["id_edizione"];
		$query_i="INSERT INTO iscrizioni_corso SET
		id_utente='$id_utente',
		id_corso='$id_corso',
		id_edizione='$id_edizione',
		id_gruppo='generale'";
		$mysqli->query($query_i);
	};
};


header("Location:index.php?risorsa=msg&msg=$msg");
			
?>

<?php
require "../../include/init_sito.inc";
require "../../include/funzioni_sito.inc";
require "../../include/funzioni_lo_viewer.inc";

$risorsa=$_REQUEST["risorsa"];
$kairos=$_REQUEST["kairos"];

if (isset($cod_area)) {
	$kairos_cookie[4]=$cod_area;
	setcookie("kairos_cookie[4]",$kairos_cookie[4],0,"/",$dominio);
};

$id_utente="";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

if ($kairos) {
	$cod_area=$kairos;
	$DBASE=$kairos;
	$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
	mysql_select_db($DBASE,$db);
};

$id_corso=id_corso($risorsa);

mysql_select_db($DBASE,$db);
$query="SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_corso'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$titolo_corso=$riga["titolo"];

$query="SELECT tipo,id_autore,id_gruppo FROM risorse_materiali WHERE id_risorsa='$risorsa'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$tipo=$riga["tipo"];
$id_autore=$riga["id_autore"];
$id_gruppo=$riga["id_gruppo"];

$query="SELECT * FROM lo WHERE id_lo='$risorsa'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$lo_skin=$riga["lo_skin"];
$lo_tipo_lom=trim($riga["lo_tipo_lom"]);
$lo_modocontinua=$riga["lo_modocontinua"];
$lo_bloccoavanzamento=$riga["lo_bloccoavanzamento"];

switch (strtolower($lo_tipo_lom)) {
	case "lezione":
	case "glossario":
	case "risorsa informativa":
	case "guida/tutoriale":
	case "esperimento":
	case "gioco didattico":
	case "simulazione":
	case "studio di caso":
	case "simulation":
	case "lecture":
	case "diagram":
	case "figure":
	case "graph":
	case "index":
	case "slide":
	case "table":
	case "narrative text":
	case "experiment":
	case "problemstatement":

		$format="a";
		break;
		
	case "esercizi e pratica":
	case "risoluzione di problemi":
	case "exercise":
	
		$format="b";
		break;
		
	case "questionario":
	case "verifica":
	case "autovalutazione":
	case "questionnaire":
	case "selfassessment":
	case "exam":
	
		$format="c";
		break;
};



if (!$lo_skin) $lo_skin="default";
$path_img="skins/$lo_skin";

$n_pagina=0;
$n_appr=0;
$n_item=0;

$pagina_finale=0;
tot_pagine($id_corso);

$max_score=0;
max_score($id_corso);
$punteggiominimo=floor($max_score/2)+1;


?>
/* --- SHELL ACCESSIBILE: DESCRIZIONE DEL LEARNING OBJECT --- */

	var codice = "1";
	var tipolo = "<?php echo($format);?>";
	var bloccoavanzamento = <?php echo($lo_bloccoavanzamento);?>; 
	var modocontinua = <?php echo($lo_modocontinua);?>; 
	var visualizzasoluzioni = 3;
	if (tipolo=='c') visualizzasoluzioni=1;
	var puntinegativi = 0; // 1 = sottrae punti per test errato
	 
	var punteggiominimo = <?php echo($punteggiominimo);?>; //punteggio per il superamento del modulo
	var punteggiosoglia = 0; //punteggio minimo per proseguire
	var nometutoriale = new Array();
	var numerotutoriale = new Array();
	var successivo = new Array();
	var precedente = new Array();
	var tipotutoriale = new Array();
	var puntitutoriale = new Array();
	var tutorialealternativo = new Array();
	var tutorialeprincipale = new Array();
	var nomeapprofondimento = new Array();

	nometutoriale[0]="homepage";
	tipotutoriale["homepage"]=0;
	precedente["homepage"]="";
	
	<?php 
	$i_pag=1;
	$i_appr=1;
	$codice_array="";
	$codice_array_nav="";
	$padre_alternativo="";
	$risorsa_principale="";
	$tut_att="homepage";
	$tut_alt="";
	$num_tut=1;
	$id_ultimo_alt="";
	$id_ultimo_pr="";
	
	array_lo($risorsa);
	
	$codice_array.= "successivo['$tut_att']='';\n";
	if ($id_ultimo_alt) $codice_array.= "successivo['$id_ultimo_alt']=successivo['$id_ultimo_pr'];\n";
	$codice_array.="\n".$codice_array_nav;
	
	if (!$esporta) {
		echo ($codice_array);
		/*
		$fd=fopen("./array_lo.js","w");
		fwrite($fd,$codice_array);
		fclose($fd);
		*/
	};
	
	?>

		  
	var messaggiofeedback = new Array();
	messaggiofeedback[1] = "La missione ÃÂÃÂ¨ quasi fallita"; // tag Alt immagine di riepilogo livello 1
	messaggiofeedback[2] = "La prestazione ÃÂÃÂ¨ piuttosto modesta"; // tag Alt immagine di riepilogo livello 2
	messaggiofeedback[3] = "Il successo ÃÂÃÂ¨ ancora lontano"; // tag Alt immagine di riepilogo livello 3
	messaggiofeedback[4] = "La prestazione ÃÂÃÂ¨ superiore alla media"; // tag Alt immagine di riepilogo livello 4
	messaggiofeedback[5] = "La prestazione ÃÂÃÂ¨ esaltante"; // tag Alt immagine di riepilogo livello 5
	messaggiofeedback[6] = "La missione ÃÂÃÂ¨ quasi fallita"; // messaggio di riepilogo livello 1
	messaggiofeedback[7] = "La prestazione ÃÂÃÂ¨ piuttosto modesta"; // messaggio di riepilogo livello 2
	messaggiofeedback[8] = "Il successo ÃÂÃÂ¨ ancora lontano"; // messaggio di riepilogo livello 3
	messaggiofeedback[9] = "La prestazione ÃÂÃÂ¨ superiore alla media"; // messaggio di riepilogo livello 4
	messaggiofeedback[10] = "La prestazione ÃÂÃÂ¨ esaltante"; // messaggio di riepilogo livello 5
	messaggiofeedback[11] = "Commento inviato"; // invio del commento alla piattaforma
	messaggiofeedback[12] = "Il commento non puÃÂÃÂ² superare i 4000 caratteri!"; // superamento del limite del commento
	messaggiofeedback[13] = "Prima rispondi bene!"; //messaggio per mancata risposta al test
	messaggiofeedback[14] = "Prima rispondi!"; //messaggio per mancata risposta al test
	messaggiofeedback[15] = "La tua missione ÃÂÃÂ¨ fallita. Ricomincia!"; //messaggio di superamento livello di soglia
	messaggiofeedback[16] = "Hai giÃÂÃÂ  risposto. Vai avanti."; // messaggio per test giÃÂÃÂ  affrontato
	messaggiofeedback[17] = "Prima di ritentare, studia!"; // messaggio per mancato accesso al tutoriale dopo errore
	messaggiofeedback[18] = "Non hai ancora risposto!"; // messaggio per mancata risposta
	messaggiofeedback[19] = "Andiamo male: la missione ÃÂÃÂ¨ in pericolo"; // tag Alt immagine test livello 1
	messaggiofeedback[20] = "Prestazione ancora modesta: fai attenzione"; // tag Alt immagine test livello 2
	messaggiofeedback[21] = "Il successo ÃÂÃÂ¨ ancora lontano"; // tag Alt immagine test livello 3
	messaggiofeedback[22] = "La situazione ÃÂÃÂ¨ incoraggiante: continua cosÃÂÃÂ¬"; // tag Alt immagine test livello 4
	messaggiofeedback[23] = "Prestazione esaltante: il successo ÃÂÃÂ¨ vicino"; // tag Alt immagine test livello 5
	messaggiofeedback[24] = "Prova effettuata, ma non superata"; // messaggio per test giÃÂÃÂ  effettuato
	messaggiofeedback[25] = "Prova superata"; // messaggio per test giÃÂÃÂ  superato;
	messaggiofeedback[26] = "Per le soluzioni, sfiora con il puntatore le icone accanto alle risposte"; // messaggio per evidenziazione soluzioni
	messaggiofeedback[27] = "Hai visualizzato le soluzioni: non puoi piÃÂÃÂ¹ rispondere"; // messaggio per soluzini visualizzate
	messaggiofeedback[28] = "La tua risposta ÃÂÃÂ¨ esatta"; // tag Title del feedback positivo
	messaggiofeedback[29] = "La tua risposta ÃÂÃÂ¨ errata"; // tag Title del feedback negativo
	messaggiofeedback[30] = "Questa ÃÂÃÂ¨ la risposta corretta"; // tag Title del feedback negativo (con risposta chiusa)
	messaggiofeedback[31] = "La tua risposta ÃÂÃÂ¨ errata. Quella corretta ÃÂÃÂ¨: "; // tag Title del feedback negativo (con risposta testuale esatta)
	messaggiofeedback[32] = "La tua risposta ÃÂÃÂ¨ errata. Quella corretta ÃÂÃÂ¨ la numero "; // tag Title del feedback negativo (con selezione)

	var messaggiotest = new Array();
	messaggiotest[0] = "Risposta esatta! Vai avanti"; // messaggio di default per risposta esatta
	messaggiotest[1] = "Hai sbagliato! Studia!!"; // messaggio di default per risposta errata
	

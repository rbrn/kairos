<?php
$excludeTemplate = true;
require "./include/init_sito.inc";
require "./include/funzioni_lo_viewer.inc";
require "./include/funzioni_sito.inc";
/* ****************** INIZIO PROCEDURA ************* */

$risorsa=$_REQUEST["risorsa"];
$kairos=$_REQUEST["kairos"];
if (!isset($_REQUEST["esporta"])) $_REQUEST["esporta"]="";
$esporta=$_REQUEST["esporta"];
$nomarchio=$_REQUEST["nomarchio"];




if (isset($cod_area)) {
	$kairos_cookie[4]=$cod_area;
	setcookie("kairos_cookie[4]",$kairos_cookie[4],0,"/",$dominio);
};

$id_utente="";
$geogebra=false;

$cod_area0=$cod_area;


//echo $cod_area0 . " cod area";


/* controllo legittimita' download */
/*
if ($kairos) {
	$ruolo=ruolo_utente($kairos_cookie[0]);
	if ($ruolo<>"admin" and $ruolo<>"staff") {
		$query2="SELECT * FROM lo_purchase WHERE id_utente='$kairos_cookie[0]' AND id_lo='$id_lo' AND stato_ordine='2' LIMIT 1";
		$result2=$mysqli->query($query2);
		if (!$result2->num_rows) {
			$msg="Per poter eseguire/scaricare questo Learning Object ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ necessario prima ordinarlo e riceverne conferma dall'amministrazione";
			$msg=str_replace(" ","%20",$msg);
			Header("Location:index.php?risorsa=msg&msg=$msg");
			exit();
		};
	};
	
	$azione_log="visto online";
	if ($esporta) $azione_log="scaricato";

	$query="INSERT INTO lo_log SET
id_utente='$kairos_cookie[0]',
data_log=NOW(),
id_lo='$risorsa',
azione='$azione_log'";
	$mysqli->query($query);

};
*/
/* -------------- */

if ($cod_area=="kairos_curriculumdigitale" or $cod_area=="kairos_learningobject") {
	mysql_select_db("atlante",$db);
	$query="SELECT nome,cognome,nomescuola,cittascuola FROM utenti WHERE id_utente='$kairos_cookie[0]'";
} else {
	$query="SELECT nome,cognome,scuola,citta FROM utenti WHERE id_utente='$kairos_cookie[0]'";
	
};


$result=$mysqli->query($query);
$riga=$result->fetch_array();
$nome_utente=stripslashes(trim($riga["nome"])." ".trim($riga["cognome"]));
$nomescuola=stripslashes(trim($riga["scuola"]));
$cittascuola=stripslashes(trim($riga["citta"]));


$id_corso=id_corso($risorsa);
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
$lo_licenza=$riga["lo_licenza"];

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

if ($esporta) {
	$path_img="img";
} else {
	$path_img="skins/$lo_skin";
};

$query="SELECT nome,cognome FROM utenti WHERE id_utente='$id_autore'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$nome_autore=$riga[nome]." ".$riga[cognome];	

$nometutoriale=array();

$n_pagina=0;
$n_appr=0;
$n_item=0;
$tot_pagine=0;
$max_score=0;
$pagina_finale=0;

tot_pagine($id_corso);
max_score($id_corso);
$punteggiominimo=floor($max_score/2)+1;

$i_pag=1;
$i_appr=1;
tipo_pagina($risorsa);
	  
if ($esporta) {
$path_file=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa";
if (!file_exists($path_file)) {
	mkdir($path_file,0777);
};

$path_file=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/formule";
if (!file_exists($path_file)) {
	mkdir($path_file,0777);
};

$path_file=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell";
if (!file_exists($path_file)) {
	mkdir($path_file,0777);
};

$path_file=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/script";
if (!file_exists($path_file)) {
	mkdir($path_file,0777);
};

$path_file=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/img";
if (!file_exists($path_file)) {
	mkdir($path_file,0777);
};
};

if ($esporta) {
	$pimg="img";
} else {
	$pimg="skins/$lo_skin";
};
	
$codice.="<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Strict//EN\"
\"http://www.w3.org/TR/html4/strict.dtd\">
<html lang=\"it\">
<head>
   <title>$titolo_corso</title>
   <meta http-equiv=\"Content-Type\" content=\"text/html; charset=ISO-8859-1\">
   <meta http-equiv=\"Pragma\" content=\"no-cache\">
   <meta http-equiv=\"expired\" content=\"01-Mar-94 00:00:01 GMT\">

   <link rel=\"stylesheet\" href=\"shell/$pimg/tutoriale.css\" type=\"text/css\">";
   
   if ($esporta) {
   $codice.="<script type=\"text/javascript\" src=\"shell/script/lo.js\"></script>";
   } else {
   $codice.="<script type=\"text/javascript\" src=\"shell/script/lo.js.php?risorsa=$risorsa&amp;esporta=0&amp;kairos=$kairos\"></script>";
   };
   
   $codice.="<script type=\"text/javascript\" src=\"shell/script/api_comm(piattaforma).js\"></script>
   <script type=\"text/javascript\" src=\"shell/script/main.js\"></script>";
   
   if ($esporta) {
   $codice.="<script type=\"text/javascript\" src=\"shell/script/jfunzioni.js\"></script>
   <script type=\"text/javascript\" src=\"shell/script/jfunzioni_test.js\"></script>";
   } else {
   $codice.="<script type=\"text/javascript\" src=\"shell/script/jfunzioni.js.php?lo_skin=$lo_skin\"></script>
   <script type=\"text/javascript\" src=\"shell/script/jfunzioni_test.js.php?lo_skin=$lo_skin\"></script>";
   };
   
   $codice.="<script type=\"text/javascript\">
      caricamedia(\"shell/$pimg/messaggio.mp3\");
      caricamedia(\"shell/$pimg/ok.mp3\");
      caricamedia(\"shell/$pimg/ko.mp3\");
   </script>

</head>

<body id=\"body\" onload=\"inizializza()\">

<!-- SCHERMATA -->

<div id=\"testata_1\"></div>
<div id=\"testata_2\"></div>
<div id=\"testata_3\"></div>
<div id=\"lato_sx\"></div>
<div id=\"lato_dx\"></div>
<div id=\"base_1\"></div>
<div id=\"base_2\"></div>
<div id=\"base_3\"></div>";

if (($cod_area0=="kairos_curriculumdigitale" or $cod_area0=="kairos_itc_scuola") and !$nomarchio) {
if ($esporta) {
	marchio($nome_utente,$lo_skin);
	$codice.="<div id=\"marchio\"><img src=\"shell/img/marchio.png\" alt=\"Learning Object di: $nome_utente\"></div>";
} else {
$codice.="<div id=\"marchio\"><img src=\"shell/marchiatura/marchio.php?nome=$nome_utente\" alt=\"Learning Object di: $nome_utente\"></div>";
};
};

$codice.="
<p class=\"nascosto\">
   <a name=\"inizio_a\"></a>
   <script type=\"text/javascript\">
      if (multimedia == 1)
         document.write(\"<a href='#' onClick='disattivamedium();return false;' onKeyPress='disattivamedium();return false;' title=\\\"Per usare il lettore di schermo, disattiva l'audio e gli altri contributi multimediali. Alcune animazioni Flash saranno sostituite da pagine alternative\\\"><\/a>\");
   </script>
   Attenzione: tutte le pagine prevedono un titolo iniziale di livello 1. Per una lettura ordinata, a ogni nuova pagina ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ preferibile accedere al titolo.
   <a href=\"#homepage_a\" onClick=\"window.open('#homepage_a','_self');\" onKeyPress=\"window.open('#homepage_a','_self');\" title=\"Salta la descrizione dei pulsanti\"></a>

<!--  PULSANTI -->
<p>
<span class=\"nascosto\">Pulsanti di uso generale:</span>

<a id=\"pulsanteindice\" href=\"#sommario_a\" onClick=\"vai('sommario');return false;\" onKeypress=\"vai('sommario');return false;\">
   <img id=\"indice\" onMouseOver=\"roll(this,'indice')\" onMouseOut=\"noroll(this,'indice')\" src=\"shell/$path_img/pulsante_indice.gif\" alt=\"Indice generale\">
</a>

<a id=\"pulsantehome\" href=\"#homepage_a\"  onClick=\"tutoriale('homepage');return false;\" onKeypress=\"tutoriale('homepage');return false;\">
   <img id=\"home\" onMouseOver=\"roll(this,'home')\" onMouseOut=\"noroll(this,'home')\" src=\"shell/$path_img/pulsante_home.gif\" alt=\"Home\">
</a>

<a id=\"pulsantecredits\" href=\"#paginacredits_a\" onClick=\"vai('paginacredits');return false;\" onKeypress=\"vai('paginacredits');return false;\">
   <img id=\"credits\" onMouseOver=\"roll(this,'credits')\" onMouseOut=\"noroll(this,'credits')\" src=\"shell/$path_img/pulsante_credits.gif\" alt=\"Informazioni e credits\">
</a>

<a id=\"pulsantehelp\" href=\"#paginahelp_a\" onClick=\"vai('paginahelp');return false;\" onKeypress=\"vai('paginahelp');return false;\">
   <img id=\"help\" onMouseOver=\"roll(this,'help')\" onMouseOut=\"noroll(this,'help')\" src=\"shell/$path_img/pulsante_help.gif\" alt=\"Help\">
</a>

<a id=\"pulsanteuscita\" href=\"#esci_a\" onClick=\"vai('esci');return false;\" onKeypress=\"vai('esci');return false;\">
   <img id=\"uscita\" onMouseOver=\"roll(this,'uscita')\" onMouseOut=\"noroll(this,'uscita')\"src=\"shell/$path_img/pulsante_uscita.gif\" alt=\"Uscita\">
</a>

<script type=\"text/javascript\">
   pulsantiambiente();
</script>

<!-- TESTO PRINCIPALE -->
<div id=\"contenuto\">

<div id=\"titolo_lo\">
   
</div>

<!-- HOME PAGE -->
<div id=\"homepage\" class=\"contenutotutoriale\">
<p><a name=\"homepage_a\"></a>
<div id=\"copertina\"></div>";

visualizza_home($id_corso);

$codice.="
<hr class=\"linea\">
</div>
<p>
<script type=\"text/javascript\">
      comandi(\"homepage\");
   </script>
   <noscript>
   <p>
";

switch ($format) {
	case "a":
	  	$codice.="<a href=\"#sommario_a\" accesskey=\"a\" tabindex=\"30\">";
	  	break;

	case "b":
	case "c":
   		$codice.="<a href=\"#tutoriale1_a\" accesskey=\"a\" tabindex=\"30\">";
		break;
};
   
$codice.="<img class=\"pulsanteavanti\" src=\"shell/$path_img/pulsante_avanti.gif\" alt=\"Vai alla pagina successiva\">
   </a>";
   
$codice.=" <p class=\"comunicazioni\">
         Attenzione: per sfruttare le funzioni avanzate del corso e necessario abilitare Javascript sul browser.
   </noscript>
   </div>";

$codice.="

<!-- TUTORIALE -->";

$p=1;		
$d=1;
$padre_alternativo="";
$risorsa_principale="";
genera_pagina($risorsa);

$codice.="

<!-- PAGINE DI SERVIZIO -->

<!-- Conferma uscita -->
<div id=\"esci\" class=\"contenutoapprofondimento\">
<p><a name=\"esci_a\"></a>
<div id=\"logouscita\"></div>
<div id=\"testouscita\">
<h1>Riepilogo</h1>
<p>
<div class=\"rigabox\">
   <label class=\"riepilogo\" for=\"riepilogopunti\">Nei test effettuati hai ottenuto</label>
   <input class=\"datireadonly\" id=\"riepilogopunti\" readonly size=\"1\">
   <label for=\"riepilogopuntimax\">punti su</label>
   <input class=\"datireadonly\" id=\"riepilogopuntimax\" readonly size=\"1\">
</div>
<div class=\"rigabox\">
   <label class=\"riepilogo\" for=\"riepilogopuntitotalimin\">Per superare la prova devi arrivare a</label>
   <input class=\"datireadonly\" id=\"riepilogopuntitotalimin\" readonly size=\"1\">
</div>
<div class=\"rigabox\">
   <label class=\"riepilogo\" for=\"riepilogopagine\">Il numero di pagine visualizzate ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½</label>
   <input class=\"datireadonly\" id=\"riepilogopagine\" readonly size=\"1\">
   <label for=\"riepilogopaginemax\">su un totale di</label>
   <input class=\"datireadonly\" id=\"riepilogopaginemax\" readonly size=\"1\"><br>
</div>
<div class=\"rigabox\">
   <label class=\"riepilogo\" for=\"riepilogostatus\">Il corso ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½</label>
   <input class=\"datireadonly\" id=\"riepilogostatus\" readonly size=\"50\">
</div>
  
<div id=\"fineuscita\">
   <br>Confermi l'uscita da questa sessione di lavoro?<br>
   <p>
   <span class=\"nascosto\">Principali funzioni:</span>
   <script type=\"text/javascript\">
      document.write(\"<a href='#' onClick=\\\"chiudi();return false;\\\" onKeyPress='chiudi();return false;'><img class='pulsantesi' onMouseOver=\\\"roll(this,'si')\\\" onMouseOut=\\\"noroll(this,'si')\\\" src='shell/$path_img/pulsante_si.gif' alt='Esci dal corso'><\/a>\");
   </script>
   <a href=\"#sommario_a\" accesskey=\"t\" tabindex=\"10\" onClick=\"ritornaindietro();return false;\" onKeyPress=\"ritornaindietro();return false;\">
      <img id=\"no1\" onMouseOver=\"roll('no',1)\" onMouseOut=\"noroll(this,'no')\" src=\"shell/$path_img/pulsante_no.gif\" alt=\"Torna indietro\"></a>
   <noscript>
      <p>
      Per confermare l'uscita dal corso chiudi la finestra del browser o digita Alt-F4.
   </noscript>
   <span class=\"nascosto\">Fine della pagina di uscita dal corso. Per riascoltarla torna al titolo.</span>
</div>
</div>
</div>

<!-- Help -->
<div id=\"paginahelp\" class=\"contenutoservizio\">
<p><a name=\"paginahelp_a\"></a>
<div class=\"testata_s_01\"></div>
<div class=\"testata_s_02\"></div>
<div class=\"testata_s_03\"></div>
<div class=\"testata_s_04\"></div>
<div class=\"testata_s_05\"></div>
<h1>Istruzioni per l'uso</h1>
<div class=\"testoservizio\">
<h2>I comandi di navigazione</h2>
<p>
Questo corso ha una struttura sequenziale che permette di seguire facilmente il flusso di informazioni multimediali (testi, immagini, filmati, animazioni) e prove di verifica con pochissimi comandi.<br>
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_indietro.gif\" alt=\"Pulsante 'Indietro'\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_avanti.gif\" alt=\"Pulsante 'Avanti'\">
I pulsanti \"Indietro\" e \"Avanti\" e consentono di scorrere le pagine. Se il pulsante \"Avanti\" non ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ visibile, a meno che non si tratti dell'ultima pagina, nella schermata ci sono certamente indicazioni su come proseguire.<br>
Da alcune pagine, tramite collegamenti ipertestuali, si possono raggiungere voci di glossario e altri documenti di approfondimento. Questi collegamenti sono preceduti da piccole icone come queste: <img src=\"shell/$path_img/puls_a.gif\" alt=\"Icona degli Approfondimenti\"> e <img src=\"shell/$path_img/puls_g.gif\" alt=\"Icona del glossario\">.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_home.gif\" alt=\"Pulsante 'Home'\">
Il pulsante \"Home\" consente di raggiungere direttamente la pagina iniziale (\"home page\"), che contiene una scheda sintetica del corso.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_indice.gif\" alt=\"Pulsante 'Indice'\">
Il pulsante \"Indice\" consente di raggiungere direttamente l'indice del corso. Da qui puÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ essere possibile accedere alle diverse pagine.<br>
Un segno di spunta compare accanto a ogni pagina visitata <img src=\"shell/$path_img/visto.gif\" alt=\"Segno di spunta\">.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_help.gif\" alt=\"Pulsante 'Help'\">
Il pulsante \"Help\" consente di accedere alla pagina delle istruzioni (questa!), che contiene indicazioni sulle diverse funzioni e sui comandi.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_credits.gif\" alt=\"Pulsante 'Informazioni'\">
 Il pulsante \"Informazioni\" consente di accedere alla pagina con informazioni sugli autori. Equivale ai titoli di coda di un film (<em>credits</em>).
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_torna.gif\" alt=\"Pulsante 'Torna'\">
Il pulsante \"Torna\" serve a tornare indietro. Il suo funzionamento ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ differente a seconda dei casi:
<ul>
<li>Nelle pagine di Help, di Informazione, di Glossario o negli altri Approfondimenti, torna alla pagina chiamante.
<li>Nelle pagine con contenuti teorici, torna all'ultimo test effettuato o alla pagina di riepilogo.
</ul>

<h2>I comandi per le esercitazioni e i test</h2>
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_verifica.gif\" alt=\"Pulsante 'Verifica'\">
Il pulsante \"Verifica\" permette di controllare l'esito di un test e di assegnare i relativi punteggi.<br>
Senza premere questo pulsante, il test non ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ considerato valido.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_studio.gif\" alt=\"Pulsante 'Studia'\">
Il pulsante \"Studia\" (o \"Vai a vedere\") permette di collegare un test alle pagine che contengono le necessarie conoscenze teoriche.<br>
Dopo un errore, l'accesso a queste pagine puÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ essere reso obbligatorio: ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ un modo per facilitare la prosecuzione dell'attivitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½.<br>
In molti casi, la pagina collegata da questo pulsante varia a seconda dell'errore commesso (se sono stati commessi piÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ errori, il sistema tiene conto del primo).
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_soluzioni.gif\" alt=\"Pulsante 'Soluzione'\">
Il pulsante \"Soluzione\" permette di conoscere le soluzioni dei test.<br>
Accanto a ciascuna risposta compare una delle icone: <img class=\"immagineinlinea\" src=\"shell/$path_img/feedback_ok.gif\" alt=\"Risposta esatta\"> o <img class=\"immagineinlinea\" src=\"shell/$path_img/feedback_ko.gif\" alt=\"Risposta errata\">.<br>
Sfiorando col puntatore del mouse questa icona ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ possibile conoscere la risposta esatta.<br>
Attenzione: il pulsante \"Soluzione\" compare solo dopo alcuni tentativi di risposta. Vedere le soluzioni ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ facoltativo, ma (naturalmente) una volta visualizzate non sarÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ piÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ possibile rispondere nella stessa sessione.<br>
Visualizzando la soluzione, inoltre, i punti previsti per quel test vengono sottratti.
<h2>I comandi per gestire l'interfaccia e la multimedialitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½</h2>
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_ingrandisci.gif\" alt=\"Pulsante 'Ingrandisci'\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_rimpicciolisci.gif\" alt=\"Pulsante 'Rimpicciolisci'\">
I pulsanti \"Ingrandisci\" e \"Rimpicciolisci\" permettono di modificare a piacere le dimensioni dei caratteri del testo.<br>
Senza limiti.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_zoom.gif\" alt=\"Pulsante 'Zoom'\">
Il pulsante \"Zoom\" permette di scegliere tra due possibili dimensioni della schermata, per adattarle a quelle del monitor.<br>
Il pulsante ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ attivo solo all'inizio del corso, fino a quando non si comincia a navigare per le diverse pagine.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_suonoon.gif\" alt=\"Pulsante suono 'On'\">
<img class=\"immaginehelpsx\" src=\"shell/$path_img/pulsante_suonooff.gif\" alt=\"Pulsante 'Off'\">
Il pulsanti \"Attiva/disattiva audio, video e animazioni\" permettono di attivare o disabilitare tutti i contenuti multimediali: suoni, filmati, animazioni Flash, ecc.<br>
Tuttavia, alcuni brevi suoni particolarmente importanti (quelli che accompagnano i messaggi) sono sempre abilitati.

<h2>Le funzioni per l 'accessibilitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½</h2>
<p>
<hr class=\"linea\">
Oltre agli accorgimenti previsti dalla normativa vigente (legge 4 del 2004), sono presenti molte funzioni per facilitare al massimo l'accessibilitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ dei contenuti.<br>
In particolare:
<ul>
<li>Per ogni pagina ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ sempre presente, anche quando non ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ visibile, un titolo di primo livello che consente di tornare velocemente a inizio pagina attraverso i comandi del lettore di schermo.
<li>Sono presenti comandi nascosti per disattivare fin dall'inizio i componenti audio, video e le animazioni che potrebbero interferire con i lettori di schermo.
<li>Anche quando sono disabilitati, i contenuti multimediali si possono attivare, pagina per pagina, con comandi nascosti che permettono di procedere solo dopo aver terminato l'esplorazione della pagina.
<li>I pulsanti di navigazione sono replicati da comandi nascosti attivi nelle diverse pagine.
<li>Per le pagine il cui contenuto essenziale ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ costituito da animazioni interattive (come i test che prevedono il trascinamento di oggetti, chiamati anche \"drag and drop\"), il sistema passa automaticamente alle pagine alternative se verifica che i contenuti multimediali sono disabilitati o se non ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ installato il plugin Flash.
</ul>
</div>
<p>
   <span class=\"nascosto\">Principali funzioni:</span>
   <a href=\"#homepage_a\" accesskey=\"t\" tabindex=\"10\" onClick=\"ritornaindietro();return false;\" onKeyPress=\"ritornaindietro();return false;\">
      <img class=\"pulsantetornaindietro\" onMouseOver=\"roll(this,'tornaindietro')\" onMouseOut=\"noroll(this,'tornaindietro')\" src=\"shell/$path_img/pulsante_tornaindietro.gif\" alt=\"Torna indietro\">
   </a>
   <span class=\"nascosto\">Fine dell'help. Per riascoltarlo torna al titolo.</span>
</div>";



$path_file=$PATH_ROOT_FILE."materiali/$cod_area/".$risorsa."_credits.txt";
if (file_exists($path_file)) {
	$nomi_credits_file=join('',file($path_file));
	$nomi_credits=explode("\t",$nomi_credits_file);
	$nome_autore_credits=stripslashes($nomi_credits[0]);
	$nome_coordinatore_credits=stripslashes($nomi_credits[1]);
};




if (($cod_area0=="kairos_curriculumdigitale" or $cod_area0=="kairos_itc_scuola"  or $cod_area0=="kairos_learningobject") and !$nomarchio) {
$codice.="<div id=\"paginacredits\" class=\"contenutoservizio\">
<p><a name=\"paginacredits_a\"></a>
<div class=\"testata_s_1\"></div>
<div class=\"testata_s_2\"></div>
<div class=\"testata_s_3\"></div>
<h1>Credits</h1>
<div class=\"testoservizio\">
<div class=\"logo_garamond\"></div>
<h2>Licenza d'uso</h2>";

	if ($lo_licenza) {
		$codice.=$lo_licenza."</div>
<p>
   <span class=\"nascosto\">Principali funzioni:</span>
   <a href=\"#homepage_a\" accesskey=\"t\" tabindex=\"200\" onClick=\"ritornaindietro();return false;\" onKeyPress=\"ritornaindietro();return false;\">
      <img class=\"pulsantetornaindietro\" onMouseOver=\"roll(this,'tornaindietro')\" onMouseOut=\"noroll(this,'tornaindietro')\" src=\"shell/$path_img/pulsante_tornaindietro.gif\" alt=\"Torna indietro\">
   </a>
   <span class=\"nascosto\">Fine dei credits. Per riascoltarli torna al titolo.</span>
</div>";
	} else {
		$codice.="
<p>
Il presente Learning Object (LO) &egrave; di propriet&agrave; di Garamond Srl ed &egrave; concesso in licenza d'uso esclusivo al legittimo titolare
<p>
".strtoupper($nome_utente)."<br>
".strtoupper($nomescuola)."<br>
".strtoupper($cittascuola)."
<p>
che ha facolt&agrave; di eseguirlo online e scaricarlo sui suoi computer, disponendo della sua fruizione senza alcun vincolo di tempo, di sessioni di studio o di sede di esecuzione, online e offline.
<p>
Non &egrave; consentito l'uso del presente LO da parte di soggetti non titolari della presente licenza, e specificamente l'installazione, l'esecuzione e la riproduzione su computer o altri dispositivi elettronici personali, di scuole o di enti che non abbiano acquistato la regolare licenza. 
<p>
Non &egrave; consentita la copia, la traduzione, la riproduzione, la modifica e la manipolazione dei contenuti del presente LO, integrale o anche parziale, senza il permesso scritto dell'editore Garamond Srl.

<p>
<strong>Produzione editoriale</strong><br>
Garamond Editoria e Formazione - Roma
<p>
<strong>Progettazione didattica</strong><br>
Vindice Deplano
<p>
<strong>Ideazione e produzione storyboard e testi</strong><br>
$nome_autore_credits
<p>
<strong>Coordinamento disciplinare</strong><br>
$nome_coordinatore_credits
<p>
<strong>Redazione</strong><br>
Paola Ricci (coordinamento), Rossella Baldazzi, Mimma Basile, Francesca Policaro, Brunella Pellegrini, Martina Quadrino, Ida Taci, Stefano Tura
<p>
<strong>Progettazione e sviluppo editor LO</strong><br>
Francesco Leonetti
<p>
<strong>Progettazione e sviluppo funzioni per l'accessibilit&agrave;</strong><br>
Glaux Srl
<p>
<strong>Progettazione e realizzazione grafica</strong><br>
Cristiana Giovannini (coordinamento), Daniele Quartu
<p>
<strong>Animazioni</strong><br>
Andrea Blasio (coordinamento), Alessandro Avenali, Gaetano Ermito, Diana Oreffice, Pasquale Gagliano
<p>
<strong>Audio, musiche ed effetti sonori</strong><br>
Luca De Carlo, Gio Gio' Rapattoni (voce)
<p>
<strong>Comunicazione</strong><br>
Chiara Calzavara

</div>
<p>
   <span class=\"nascosto\">Principali funzioni:</span>
   <a href=\"#homepage_a\" accesskey=\"t\" tabindex=\"200\" onClick=\"ritornaindietro();return false;\" onKeyPress=\"ritornaindietro();return false;\">
      <img class=\"pulsantetornaindietro\" onMouseOver=\"roll(this,'tornaindietro')\" onMouseOut=\"noroll(this,'tornaindietro')\" src=\"shell/$path_img/pulsante_tornaindietro.gif\" alt=\"Torna indietro\">
   </a>
   <span class=\"nascosto\">Fine dei credits. Per riascoltarli torna al titolo.</span>
</div>";
	};

} else {
$codice.="<div id=\"paginacredits\" class=\"contenutoservizio\">
<p><a name=\"paginacredits_a\"></a>
<div class=\"testata_s_1\"></div>
<div class=\"testata_s_2\"></div>
<div class=\"testata_s_3\"></div>
<h1>Credits</h1>
<div class=\"testoservizio\">";
if ($cod_area0!="kairos_tdm")
	$codice.="<div class=\"logo_garamond\"></div>";
if ($cod_area0=="kairos_curriculumdigitale" or $cod_area0=="kairos_itc_scuola"  or $cod_area0=="kairos_learningobject") {
	$codice.="<h2>Licenza d'uso</h2>";

	if ($lo_licenza) {
		$codice.=$lo_licenza;
	} else {
		$codice.="<p>Il presente Learning Object (LO) ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ di proprietÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ 
di Garamond Srl ed ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ concesso in licenza d'uso 
esclusivo al legittimo titolare, da intendersi 
come il singolo alunno della scuola selezionata 
dal Ministero della Pubblica Istruzione per il 
Progetto DIGI Scuola, per il quale la stessa 
scuola ha effettuato l'acquisto di una singola 
licenza, alle condizioni definite nel 
\"Marketplace\" della piattaforma web DIGI Scuola.
<p>
Il titolare della licenza d'uso, cosÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ come sopra 
definito, ha facoltÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ di eseguirlo online nella 
\"Piattaforma di fruizione\" della piattaforma web 
DIGI Scuola, disponendo della sua fruizione senza 
alcun vincolo di tempo, di sessioni di studio o 
di sede di esecuzione domestica, scolastica o di altro tipo.
<p>
Il titolare della licenza d'uso ha anche la 
facoltÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ di scaricare il presente LO sul proprio 
computer o di eseguirlo - online e offline - su 
di esso o su altre piattaforme della scuola che 
ha acquistato la regolare licenza, registrandosi 
sul sito web di Garamond \"<strong>Curriculum Digitale</strong>\" 
(http://www.curriculumdigitale.it).
";
	};

};
if ($cod_area0=="kairos_tdm") {
	$codice.="<h2>Licenza d'uso</h2>";
$codice.="<p>Il presente Learning Object (LO) ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ di proprietÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ 
di Trevi Digital Media ed ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ concesso in licenza 
d'uso esclusivo al legittimo titolare, da 
intendersi come il singolo alunno della scuola 
selezionata dal Ministero della Pubblica
Istruzione per il Progetto DIGI Scuola, per il 
quale la stessa scuola ha effettuato l'acquisto 
di una singola licenza, alle condizioni definite 
nel \"Marketplace\" della piattaforma web DIGI Scuola.
<p>
Il titolare della licenza d'uso, cosÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ come sopra 
definito, ha facoltÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ di eseguirlo online nella 
\"Piattaforma di fruizione\" della piattaforma web DIGI Scuola,
disponendo della sua fruizione senza alcun 
vincolo di tempo, di sessioni di studio o di sede 
di esecuzione domestica, scolastica o di altro tipo.
<p>
<strong>Produzione editoriale</strong><br>
Trevi Digital Media - Roma
<p>
<strong>Hanno collaborato</strong>
<p>
<strong>Ideazione e produzione storyboard e testi</strong><br>
$nome_autore_credits
<p>
<strong>Redazione</strong><br>
Daniela Nardari e Tiziana Pier Mattei
";
}
else {
$codice.="<p>
<strong>Produzione editoriale</strong><br>
Garamond Editoria e Formazione - Roma
<p>
<strong>Hanno collaborato</strong>
<p>
<strong>Progettazione didattica</strong><br>
Vindice Deplano
<p>
<strong>Ideazione e produzione storyboard e testi</strong><br>
$nome_autore_credits
<p>
<strong>Coordinamento disciplinare</strong><br>
$nome_coordinatore_credits
<p>
<strong>Redazione</strong><br>
Paola Ricci e Paolo Pomes (coordinamento), Katia Azzinari, Claudio Bafera, Mimma Basile, Martina Quadrino, Stefano Tura
<p>
<strong>Progettazione e realizzazione grafica</strong><br>
Cristiana Giovannini
<p>
<strong>Animazioni</strong><br>
Elisistemi S.r.l.(coordinamento)
<p>
<strong>Audio, musiche ed effetti sonori</strong><br>
Luca De Carlo, Gio Gio' Rapattoni, Loquendo TTS (voce)";
}
if ($cod_area0<>"kairos_curriculumdigitale" and $cod_area0<>"kairos_itc_scuola" and $cod_area0<>"kairos_tdm" ) {
$codice.="<h2>Licenza d'uso</h2>
<p class=\"centrato\">
<img class=\"immaginecredits\" src=\"shell/$path_img/creative_commons.gif\" alt=\"Logo della licenza Creative Commons\"><br>
<strong>\"Creative Commons - Attribuzione, Non Commerciale, Condividi allo stesso modo 2.5 Italia\"</strong>
<p>
Questo learning object ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ distribuito da Garamond secondo la Licenza Creative Commons che consente di riprodurlo e ridistribuirlo a condizione che siano rispettate queste condizioni:
<p class=\"centrato\">
<img src=\"shell/$path_img/creative_commons_attribuzione.gif\" alt=\"Logo della licenza Creative Commons - Attribuzione\">
<img src=\"shell/$path_img/creative_commons_non_commerciale.gif\" alt=\"Logo della licenza Creative Commons - Non commerciale\">
<img src=\"shell/$path_img/creative_commons_condividi.gif\" alt=\"Logo della licenza Creative Commons - Condividi allo stesso modo\">
<p>
<strong>Attribuzione</strong>. Si deve attribuire la paternitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ dell'opera nei modi indicati dall'autore o da chi ha dato l'opera in licenza.<br>
<strong>Non commerciale</strong>. Non si puÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ usare quest'opera per fini commerciali.<br>
<strong>Condividi allo stesso modo</strong>. Se si altera o si trasforma quest'opera, o se la si usa per crearne un'altra, si puÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ distribuire l'opera risultante solo con una licenza identica a questa.
<p>
Il Commons Deed della presente licenza \"Creative Commons - Attribuzione, Non Commerciale, Condividi allo stesso modo 2.5 Italia\" ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ pubblicato sul sito web: http://creativecommons.org/licenses/by-nc-sa/2.5/it/<br>
La licenza integrale ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ pubblicata sul sito web http://creativecommons.org/licenses/by-nc-sa/2.5/it/legalcode";
}

$codice.="</div>
<p>
   <span class=\"nascosto\">Principali funzioni:</span>
   <a href=\"#homepage_a\" accesskey=\"t\" tabindex=\"200\" onClick=\"ritornaindietro();return false;\" onKeyPress=\"ritornaindietro();return false;\">
      <img class=\"pulsantetornaindietro\" onMouseOver=\"roll(this,'tornaindietro')\" onMouseOut=\"noroll(this,'tornaindietro')\" src=\"shell/$path_img/pulsante_tornaindietro.gif\" alt=\"Torna indietro\">
   </a>
   <span class=\"nascosto\">Fine dei credits. Per riascoltarli torna al titolo.</span>
</div>";

};



$codice.="<!-- Indice generale -->
<div id=\"sommario\" class=\"contenutoservizio\">
<p><a name=\"sommario_a\"></a>
<h1>Indice generale</h1>
<div class=\"testoservizio\">
<p>";

$codice.="<div id=\"sommarioriga_homepage\" class=\"rigabox\">
      <a href=\"#homepage_a\" class=\"sommario1\" onClick=\"ritornatutoriale('homepage');return false\" onKeyPress=\"ritornatutoriale('homepage');return false\">Copertina</a>
      <img id=\"sommarioimm_homepage\" class=\"sommarioimm\" src=\"shell/$path_img/vuoto.gif\" alt=\"\">
   </div>";

$i_pag=0;
indice($risorsa);

$codice.="
</div>

<p>
   <span class=\"nascosto\">Principali funzioni:</span>
   <a href=\"#homepage_a\" accesskey=\"t\" tabindex=\"10\" onClick=\"ritornaindietro();return false;\" onKeyPress=\"ritornaindietro();return false;\">
      <img class=\"pulsantetornaindietro\" onMouseOver=\"roll(this,'tornaindietro')\" onMouseOut=\"noroll(this,'tornaindietro')\" src=\"shell/$path_img/pulsante_tornaindietro.gif\" alt=\"Torna indietro\">
   </a>
   <span class=\"nascosto\">Fine dell'indice generale. Per riascoltarlo torna al titolo.</span>
</div>

<!-- FINE TESTO -->
</div>

<!-- STRUMENTI DI NAVIGAZIONE -->
<div id=\"navigazionetutoriale\">
<p><span class=\"nascosto\">Principali funzioni:</span>   
   <script type=\"text/javascript\">
      pulsantinavigazione();
   </script>
   <a href=\"#sommario_a\" accesskey=\"i\" tabindex=\"80\" onClick=\"vai('sommario');return false;\" onKeyPress=\"vai('sommario');return false;\" title=\"Vai all'indice generale dell'argomento\"></a>
  <span id=\"comandohome\"> <a href=\"#homepage_a\" accesskey=\"p\" tabindex=\"85\" onClick=\"tutoriale('homepage');return false;\" onKeyPress=\"tutoriale('homepage');return false;\" title=\"Vai alla homa page\"></a></span>
   <a href=\"#paginacredits_a\" accesskey=\"r\" tabindex=\"90\" onClick=\"vai('paginacredits');return false;\" onKeyPress=\"vai('paginacredits');return false;\" title=\"Vai ai credits\"></a>
   <a href=\"#paginahelp_a\" accesskey=\"h\" tabindex=\"95\" onClick=\"vai('paginahelp');return false;\" onKeyPress=\"vai('paginahelp');return false;\" title=\"Vai all'help\"></a>
   <a href=\"#esci_a\" accesskey=\"e\" tabindex=\"100\" onClick=\"vai('esci');return false;\" onKeyPress=\"vai('esci');return false;\" title=\"Esci dal corso\"></a>
   Fine della pagina. Per riascoltarla torna al titolo.
</div>

</body>
</html>";


if ($esporta) {
$codice_array="";
$codice_array_nav="";
$i_pag=1;
$i_appr=1;
$num_tut=1;
$tut_att="homepage";
$tut_alt="";
$id_ultimo_alt="";
$id_ultimo_pr="";
array_lo($risorsa);
$codice_array.= "successivo['$tut_att']='';\n";
if ($id_ultimo_alt) $codice_array.= "successivo['$id_ultimo_alt']=successivo['$id_ultimo_pr'];\n";
$codice_array.="\n".$codice_array_nav;

$file_script=$PATH_ROOT_FILE."shell/script/lo_esporta.js";
$script_lo=implode('', file($file_script));
$script_lo=str_replace("<%tipolo%>",$format,$script_lo);
$script_lo=str_replace("<%bloccoavanzamento%>",$lo_bloccoavanzamento,$script_lo);
$script_lo=str_replace("<%modocontinua%>",$lo_modocontinua,$script_lo);
$script_lo=str_replace("<%punteggiominimo%>",$punteggiominimo,$script_lo);
$script_lo=str_replace("<%array_lo%>",$codice_array,$script_lo);



$path_file=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/lo.htm";
$fp=fopen($path_file,"w");
fwrite($fp,$codice);
fclose($fp);
$path0=$PATH_ROOT_FILE."shell/";
$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/";

$path_file=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/script/lo.js";
$fp=fopen($path_file,"w");
fwrite($fp,$script_lo);
fclose($fp);

if ($geogebra) {
copy($path0."script/geogebra.jar",$path1."/script/geogebra.jar");
};

copy($path0."script/jfunzioni_esporta.js",$path1."/script/jfunzioni.js");
copy($path0."script/jfunzioni_test_esporta.js",$path1."/script/jfunzioni_test.js");
copy($path0."script/main.js",$path1."/script/main.js");
copy($path0."script/api_comm(piattaforma).js",$path1."/script/api_comm(piattaforma).js");
copyr($path0."skins/$lo_skin",$path1."img");

/** esporto xml lom **/

require_once("./lom/config_xml_lom.php");
require_once("./lom/variabili_xml_lom.php");
require_once("./lom/funzioni_xml_lom.php");

$id_lo=$risorsa;

$query="SELECT * FROM lo WHERE id_lo='$id_lo'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$id_profile=$riga[id_profile];

$encode="LOM";

$xml="";

xml_lo($id_lo,$id_profile);

$path_file=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/lom.xml";
$fp=fopen($path_file,"w");
fwrite($fp,$xml);
fclose($fp);

$path_file=$PATH_ROOT_FILE."shell/scorm_template/imsmanifest.xml";
$manifest=join('',file($path_file));

$id_org_manifest="ORG_".$id_lo;
$id_item_manifest="ITEM_".$id_lo;
$id_risorsa_manifest="RES_".$id_lo;

$manifest=str_replace("id_org",$id_org_manifest,$manifest);
$manifest=str_replace("id_item",$id_item_manifest,$manifest);
$manifest=str_replace("id_risorsa",$id_risorsa_manifest,$manifest);
$manifest=str_replace("TITOLO",$titolo_corso,$manifest);

$path_file=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/imsmanifest.xml";
$fp=fopen($path_file,"w");
fwrite($fp,$manifest);
fclose($fp);

copy($PATH_ROOT_FILE."shell/scorm_template/adlcp_rootv1p2.xsd",$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/adlcp_rootv1p2.xsd");
copy($PATH_ROOT_FILE."shell/scorm_template/ims_xml.xsd",$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/ims_xml.xsd");
copy($PATH_ROOT_FILE."shell/scorm_template/imscp_rootv1p1p2.xsd",$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/imscp_rootv1p2.xsd");
copy($PATH_ROOT_FILE."shell/scorm_template/imsmd_rootv1p2p1.xsd",$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/imsmd_rootv1p2.xsd");
copy($PATH_ROOT_FILE."shell/scorm_template/start.htm",$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/start.htm");

$filezip=$id_lo.".zip";
$cur_dir=getcwd();
chdir($PATH_ROOT_FILE."materiali/$cod_area");
$zip = new ZipArchive();

if ($zip->open($filezip, ZIPARCHIVE::CREATE)!==TRUE) {
   
    //exit("cannot open <$filezip>\n");
    
}



$iterator = new RecursiveIteratorIterator(new RecursiveDirectoryIterator($risorsa));

foreach ($iterator as $key=>$value) {

$zip->addFile(realpath($key), $key) or die ("ERROR: Impossibile aggiungere file: $key");
}

$zip->close();



//exit;
//$comando="/usr/bin/zip -r ".$PATH_ROOT_FILE."materiali/$cod_area/$filezip *";

//exec($comando);
chdir($cur_dir);

	
$file_download=$PATH_ROOT_FILE."materiali/$cod_area/$filezip";



if (file_exists($file_download)) {
	Header("Location:".$PATH_ROOT."materiali/$cod_area/$filezip");
	/*
	$doc = fopen($file_download,"rb");
	header("Content-Type: application/zip");
	header( "Content-Disposition: attachment; filename=$filename" ); 
	fpassthru($doc);
	*/	
} else {
	die("Problemi nell'esportazione del LO");
	exit();
};
} else {
	echo ($codice);
};
?>

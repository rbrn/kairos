<?php
require "./include/funzioni_lo_esporta.inc";

/* ****************** INIZIO PROCEDURA ************* */

$risorsa=$_REQUEST["risorsa"];

if (isset($cod_area)) {
	$kairos_cookie[4]=$cod_area;
	setcookie("kairos_cookie[4]",$kairos_cookie[4],0,"/",$dominio);
};

require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$id_utente="";

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
$format="a";
if ($lo_tipo_lom<>"lezione") $format="b";

if (!$lo_skin) $lo_skin="default";
$path_img="skins/$lo_skin";


$query="SELECT nome,cognome FROM utenti WHERE id_utente='$id_autore'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$nome_autore=$riga[nome]." ".$riga[cognome];	

$blocco_id=array();
$tipotutoriale=array();
$n_pagina=0;
$n_appr=0;
$n_item=0;
$tot_pagine=0;
$max_score=0;
$pagina_finale=0;
tot_pagine($id_corso);
max_score($id_corso);
$punteggiominimo=floor($max_score/2)+1;
$codice="";

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


$codice.="<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Strict//EN\"
\"http://www.w3.org/TR/html4/strict.dtd\">
<html lang=\"it\">
<head>
   <title>$titolo_corso</title>
   <meta http-equiv=\"Content-Type\" content=\"text/html; charset=ISO-8859-1\">
   <meta http-equiv=\"Pragma\" content=\"no-cache\">
   <meta http-equiv=\"expired\" content=\"01-Mar-94 00:00:01 GMT\">

   <link rel=\"stylesheet\" href=\"shell/img/tutoriale.css\" type=\"text/css\">
   
<script type=\"text/javascript\">
      var codice = \"1\";
      var tipolo = \"$format\";
      var paginetotali = $tot_pagine;
      var punteggiomassimo = $max_score; //punteggio massimo teorico
      var punteggiominimo = $punteggiominimo; //punteggio per il superamento del modulo
      var punteggiosoglia = 0; //punteggio minimo per proseguire
      var paginafinale = $pagina_finale; //pagina di riepilogo
      var tipotutoriale = new Array(); //1=tutoriale 2=test/esercitazione 3=introduzione 4=riepilogo 5=test/esercitazione alternativa
	  var mediumblocco= new Array; 
	  var blocco_id = new Array;
	  var appr_id = new Array;";

	  $i_pag=1;
	  $i_appr=1;
	  tipo_pagina($risorsa);
	 
   $codice.="</script>
   <script type=\"text/javascript\" src=\"shell/script/api_comm(piattaforma).js\"></script>
   <script type=\"text/javascript\" src=\"shell/script/main.js\"></script>
   <script type=\"text/javascript\" src=\"shell/script/jfunzioni.js\"></script>
   <script type=\"text/javascript\" src=\"shell/script/jfunzioni_test.js\"></script>
   <script type=\"text/javascript\">
      caricamedia(\"shell/img/messaggio.mp3\",\"audio_messaggio\");
      caricamedia(\"shell/img/ok.mp3\",\"audio_ok\");
      caricamedia(\"shell/img/ko.mp3\",\"audio_ko\");
   </script>

</head>

<body id=\"body\" onLoad=\"inizializza();\" onUnload=\"traccia();\">

<!-- SCHERMATA -->

<div id=\"testata_01\"></div>
<div id=\"testata_02\"></div>
<div id=\"testata_03\"></div>
<div id=\"testata_04\"></div>
<div id=\"testata_05\"></div>
<div id=\"lato_sx\"></div>
<div id=\"lato_dx\"></div>
<div id=\"base_01\"></div>
<div id=\"base_02\"></div>
<div id=\"base_03\"></div>

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

<a id=\"pulsanteindice\" href=\"#sommario_a\" onMouseOver=\"roll('indice')\" onMouseOut=\"noroll('indice')\" onClick=\"vai('sommario');noroll('indice');return false;\" onKeypress=\"vai('sommario');return false;\">
   <img id=\"indice\" src=\"shell/img/pulsante_indice.gif\" alt=\"Indice generale\">
</a>

<a id=\"pulsantehome\" href=\"#homepage_a\" onMouseOver=\"roll('home')\" onMouseOut=\"noroll('home')\" onClick=\"homepage();noroll('home');return false;\" onKeypress=\"homepage();return false;\">
   <img id=\"home\" src=\"shell/img/pulsante_home.gif\" alt=\"Home\">
</a>

<a id=\"pulsantecredits\" href=\"#paginacredits_a\" onMouseOver=\"roll('credits')\" onMouseOut=\"noroll('credits')\" onClick=\"vai('paginacredits');noroll('credits');return false;\" onKeypress=\"vai('paginacredits');return false;\">
   <img id=\"credits\" src=\"shell/img/pulsante_credits.gif\" alt=\"Informazioni e credits\">
</a>

<a id=\"pulsantehelp\" href=\"#paginahelp_a\" onMouseOver=\"roll('help')\" onMouseOut=\"noroll('help')\" onClick=\"vai('paginahelp');noroll('help');return false;\" onKeypress=\"vai('paginahelp');return false;\">
   <img id=\"help\" src=\"shell/img/pulsante_help.gif\" alt=\"Help\">
</a>

<a id=\"pulsanteuscita\" href=\"#esci_a\" onMouseOver=\"roll('uscita')\" onMouseOut=\"noroll('uscita')\" onClick=\"vai('esci');noroll('uscita');return false;\" onKeypress=\"vai('esci');return false;\">
   <img id=\"uscita\" src=\"shell/img/pulsante_uscita.gif\" alt=\"Uscita\">
</a>

<script type=\"text/javascript\">
   document.write(\"<span id='pulsantezoom'>\");
   if (dimensionipagina==2)
      document.write(\"<a href='#' onMouseOver=\\\"roll('zoom')\\\" onMouseOut=\\\"noroll('zoom')\\\" onClick=\\\"diminuiscizoom();return false;\\\" onKeypress=\\\"diminuiscizoom();return false;\\\"><img class='pulsantezoom' id='zoom' src='shell/img/pulsante_zoom.gif' alt='Rimpicciolisci la finestra'><\/a>\");
   else
      document.write(\"<a href='#' onMouseOver=\\\"roll('zoom')\\\" onMouseOut=\\\"noroll('zoom')\\\" onClick=\\\"aumentazoom();return false;\\\" onKeypress=\\\"aumentazoom();return false;\\\"><img class='pulsantezoom' id='zoom' src='shell/img/pulsante_zoom.gif' alt='Ingrandisci la finestra'><\/a>\");
   document.write(\"<\/span>\");
      
   document.write(\"<a href='#' onMouseOver=\\\"roll('ingrandisci')\\\" onMouseOut=\\\"noroll('ingrandisci')\\\" onClick='incrementa();return false;' onKeypress='incrementa();return false;'><img class='pulsanteingrandisci' id='ingrandisci' src='shell/img/pulsante_ingrandisci.gif' alt='Ingrandisci i caratteri'><\/a>\");
   document.write(\"<a href='#' onMouseOver=\\\"roll('rimpicciolisci')\\\" onMouseOut=\\\"noroll('rimpicciolisci')\\\" onClick='decrementa();return false;' onKeypress='decrementa();return false;'><img class='pulsanterimpicciolisci' id='rimpicciolisci' src='shell/img/pulsante_rimpicciolisci.gif' alt='Rimpicciolisci i caratteri'><\/a>\");

   document.write(\"<a id='pulsantesuonoon' href='#' onMouseOver=\\\"roll('suonoon')\\\" onMouseOut=\\\"noroll('suonoon')\\\" onClick='attivamedium();return false;' onKeypress='attivamedium();return false;'><img class='pulsantesuono' id='suonoon' src='shell/img/pulsante_suonoon.gif' alt=\\\"Attiva audio, video e animazioni\\\"><\/a>\");
   document.write(\"<a id='pulsantesuonoff' href='#' onMouseOver=\\\"roll('suonooff')\\\" onMouseOut=\\\"noroll('suonooff')\\\" onClick='disattivamedium();return false;' onKeypress='disattivamedium();return false;'><img class='pulsantesuono' id='suonooff' src='shell/img/pulsante_suonooff.gif' alt=\\\"Disattiva audio, video e animazioni\\\"><\/a>\");
   
   document.write(\"<a id='pulsantehistory' href='#' onMouseOver=\\\"roll('history')\\\" onMouseOut=\\\"noroll('history')\\\" onClick=\\\"indietro();noroll('history');return false;\\\" onKeypress='indietro();return false;'><img id='history' src='shell/img/pulsante_history.gif' alt=\\\"Torna all'ultimo test o riepilogo\\\"><\/a>\");
</script>

<!-- TESTO PRINCIPALE -->
<div id=\"contenuto\">

<div id=\"titolo_lo\">
   $titolo_corso
</div>

<!-- HOME PAGE -->
<div id=\"homepage\" class=\"contenutotutoriale\">
<p><a name=\"homepage_a\"></a>
<div id=\"copertina\"></div>";

visualizza_home($id_corso);

$codice.="<hr class=\"linea\">
</div>
<p>";

   if ($format=="a") {
   $codice.="<a href=\"#sommario_a\" accesskey=\"a\" tabindex=\"30\" onMouseOver=\"roll('avanti','0')\" onMouseOut=\"noroll('avanti','0')\" onClick=\"vai('sommario');noroll('avanti','0');return false;\" onKeyPress=\"vai('sommario');return false;\">";
   };
   
   if ($format=="b") {
   $codice.="<a href=\"#tutoriale1_a\" accesskey=\"a\" tabindex=\"30\" onMouseOver=\"roll('avanti','0')\" onMouseOut=\"noroll('avanti','0')\" onClick=\"tutoriale(1);noroll('avanti','0');return false;\" onKeyPress=\"tutoriale(1);return false;\">";
   };
	
	$codice.="<img class=\"pulsanteavanti\" id=\"avanti0\" src=\"shell/img/pulsante_avanti.gif\" alt=\"Vai alla pagina successiva\">
   </a>
<p class=\"nascosto\">   
   Principali funzioni:   
   <script type=\"text/javascript\">
      if (multimedia == 1)
         document.write(\"<a href='#' accesskey='d' tabindex='1' onClick='disattivamedium();return false;' onKeyPress='disattivamedium();return false;' title=\\\"Se non lo hai giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ fatto, disattiva l'audio e gli altri contributi multimediali\\\"><\/a>\");
      document.write(\"<a href='#' accesskey='u' tabindex='60' onClick='indietro();return false;' onKeyPress='indietro();return false;' title=\\\"Torna all'ultima pagina visitata\\\"><\/a>\");
   </script>
   <a href=\"#\" accesskey=\"m\" tabindex=\"10\" onClick=\"avviamedium();return false;\" onKeyPress=\"avviamedium();return false;\" title=\"Ascolta l'audio\"></a>
   <a href=\"#paginacredits_a\" accesskey=\"r\" tabindex=\"80\" onClick=\"vai('paginacredits');return false;\" onKeyPress=\"vai('paginacredits');return false;\" title=\"Vai ai credits\"></a>
   <a href=\"#paginahelp_a\" accesskey=\"h\" tabindex=\"90\" onClick=\"vai('paginahelp');return false;\" onKeyPress=\"vai('paginahelp');return false;\" title=\"Vai all'help\"></a>
   <a href=\"#esci_a\" accesskey=\"e\" tabindex=\"100\" onClick=\"vai('esci');return false;\" onKeyPress=\"vai('esci');return false;\" title=\"Esci dal corso\"></a>
   Fine della home page. Per riascoltarla torna al titolo.
</div>

<!-- TUTORIALE -->";


$p=1;		
$d=1;
genera_pagina($risorsa);

$codice.="<!-- PAGINE DI SERVIZIO -->

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
   <label class=\"riepilogo\" for=\"riepilogopagine\">Il numero di prove affrontate ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½</label>
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
      document.write(\"<a href='#' onMouseOver=\\\"roll('si',1)\\\" onMouseOut=\\\"noroll('si',1)\\\" onClick=\\\"chiudi();noroll('si',1);return false;\\\" onKeyPress='chiudi();return false;'><img class='pulsantesi' id='si1' src='shell/img/pulsante_si.gif' alt='Esci dal corso'><\/a>\");
   </script>
   <a href=\"#sommario_a\" accesskey=\"t\" tabindex=\"10\" onMouseOver=\"roll('no',1)\" onMouseOut=\"noroll('no',1)\" onClick=\"ritornaindietro();noroll('no',1);return false;\" onKeyPress=\"ritornaindietro();return false;\">
      <img id=\"no1\" src=\"shell/img/pulsante_no.gif\" alt=\"Torna indietro\">
   </a>
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
<img class=\"immaginehelpsx\" src=\"shell/img/pulsante_indietro.gif\" alt=\"Pulsante 'Avanti'\">
<img class=\"immaginehelpsx\" src=\"shell/img/pulsante_avanti.gif\" alt=\"Pulsante 'Avanti'\">
I pulsanti \"Indietro\" e \"Avanti\" e consentono di scorrere le pagine. Se il pulsante \"Avanti\" non ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ visibile, a meno che non si tratti dell'ultima pagina, nella schermata ci sono certamente indicazioni su come proseguire.<br>
Da alcune pagine tramite collegamenti ipertestuali si possono raggiungere voci di glossario e altri documenti di approfondimento. Questi collegamenti sono preceduti da una piccola icona: <img src=\"shell/img/puls_a.gif\" alt=\"Icona degli Approfondimenti\">.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/img/pulsante_home.gif\" alt=\"Pulsante 'Home'\">
Il pulsante \"Home\" consente di raggiungere direttamente la pagina iniziale (\"home page\"), che contiene una scheda sintetica del corso.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/img/pulsante_indice.gif\" alt=\"Pulsante 'Indice'\">
Il pulsante \"Indice\" consente di raggiungere direttamente l'indice del corso. Da qui ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ possibile accedere a qualunque pagina.<br>
Un segno di spunta compare accando a ogni pagina visitata <img src=\"shell/img/visto.gif\" alt=\"Segno di spunta\">.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/img/pulsante_help.gif\" alt=\"Pulsante 'Help'\">
Il pulsante \"Help\" consente di accedere alla pagina delle istruzioni (questa!), che contiene indicazioni sulle funzioni di navigazione, di gestione dell'interfaccia, sulle funzioni per l'accessibilitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/img/pulsante_credits.gif\" alt=\"Pulsante 'Informazioni'\">
 Il pulsante \"Informazioni\" consente di accedere alla pagina con informazioni sugli autori. Equivale ai titoli di coda di un film (<em>credits</em>).
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/img/pulsante_torna.gif\" alt=\"Pulsante 'Torna'\">
Per tornare indietro dalle pagine di Help, di Informazioni o dagli Approfondimenti, si deve usare il pulsante \"Torna\".

<h2>I comandi per gestire l'interfaccia</h2>
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/img/pulsante_ingrandisci.gif\" alt=\"Pulsante 'Ingrandisci'\">
<img class=\"immaginehelpsx\" src=\"shell/img/pulsante_rimpicciolisci.gif\" alt=\"Pulsante 'Rimpicciolisci'\">
I pulsanti \"Ingrandisci\" e \"Rimpicciolisci\" permettono di modificare a piacere le dimensioni dei caratteri del testo.<br>
Senza limiti.
<p>
<hr class=\"linea\">
<img class=\"immaginehelpsx\" src=\"shell/img/pulsante_zoom.gif\" alt=\"Pulsante 'Zoom'\">
Il pulsante \"Zoom\" permette di scegliere tra due possibili dimensioni della schermata, per adattarle a quelle monitor.<br>
Il pulsante ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ attivo solo all'inizio del corso, fino a quando non si comincia a navigare per le diverse pagine.
</div>
<p>
   <span class=\"nascosto\">Principali funzioni:</span>
   <a href=\"#homepage_a\" accesskey=\"t\" tabindex=\"10\" onMouseOver=\"roll('tornaindietro',2)\" onMouseOut=\"noroll('tornaindietro',2)\" onClick=\"ritornaindietro();noroll('tornaindietro',2);return false;\" onKeyPress=\"ritornaindietro();return false;\">
      <img class=\"pulsantetornaindietro\" id=\"tornaindietro2\" src=\"shell/img/pulsante_tornaindietro.gif\" alt=\"Torna indietro\">
   </a>
   <span class=\"nascosto\">Fine dell'help. Per riascoltarlo torna al titolo.</span>
</div>

<!-- Credits -->
<div id=\"paginacredits\" class=\"contenutoservizio\">
<p><a name=\"paginacredits_a\"></a>
<div class=\"testata_s_01\"></div>
<div class=\"testata_s_02\"></div>
<div class=\"testata_s_03\"></div>
<div class=\"testata_s_04\"></div>
<div class=\"testata_s_05\"></div>
<h1>Credits</h1>
<div class=\"testoservizio\">
<p>
Credits del corso...<br>

</div>
<p>
   <span class=\"nascosto\">Principali funzioni:</span>
   <a href=\"#homepage_a\" accesskey=\"t\" tabindex=\"10\" onMouseOver=\"roll('tornaindietro',3)\" onMouseOut=\"noroll('tornaindietro',3)\" onClick=\"ritornaindietro();noroll('tornaindietro',3);return false;\" onKeyPress=\"ritornaindietro();return false;\">
      <img class=\"pulsantetornaindietro\" id=\"tornaindietro3\" src=\"shell/img/pulsante_tornaindietro.gif\" alt=\"Torna indietro\">
   </a>
   <span class=\"nascosto\">Fine dei credits. Per riascoltarli torna al titolo.</span>
</div>

<!-- Indice generale -->
<div id=\"sommario\" class=\"contenutoservizio\">
<p><a name=\"sommario_a\"></a>
<h1>Indice generale</h1>
<div class=\"testoservizio\">
<p>";
     
	$i_pag=0;
	indice($risorsa);

$codice.="
</div>

<p>
   <span class=\"nascosto\">Principali funzioni:</span>
   <a href=\"#homepage_a\" accesskey=\"t\" tabindex=\"10\" onMouseOver=\"roll('tornaindietro',3)\" onMouseOut=\"noroll('tornaindietro',4)\" onClick=\"ritornaindietro();noroll('tornaindietro',4);return false;\" onKeyPress=\"ritornaindietro();return false;\">
      <img class=\"pulsantetornaindietro\" id=\"tornaindietro4\" src=\"shell/img/pulsante_tornaindietro.gif\" alt=\"Torna indietro\">
   </a>
   <span class=\"nascosto\">Fine dell'indice generale. Per riascoltarlo torna al titolo.</span>
</div>

<!-- FINE TESTO -->
</div>

<!-- STRUMENTI DI NAVIGAZIONE -->
<div id=\"navigazionetutoriale\">
<p class=\"nascosto\">   
   Principali funzioni:   
   <script type=\"text/javascript\">
      if (multimedia == 1)
         document.write(\"<a href='#' accesskey='d' tabindex='1' onClick='disattivamedium();return false;' onKeyPress='disattivamedium();return false;' title=\\\"Se non lo hai giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ fatto, disattiva l'audio e gli altri contributi multimediali\\\"><\/a>\");
      document.write(\"<a href='#' accesskey='u' tabindex='75' onClick='indietro();return false;' onKeyPress='indietro();return false;' title=\\\"Torna all'ultima pagina visitata\\\"><\/a>\");
   </script>
   <a href=\"#sommario_a\" accesskey=\"i\" tabindex=\"80\" onClick=\"sommario();return false;\" onKeyPress=\"sommario();return false;\" title=\"Vai all'indice generale dell'argomento\"></a>
   <a href=\"#homepage_a\" accesskey=\"p\" tabindex=\"85\" onClick=\"homepage();return false;\" onKeyPress=\"homepage();return false;\" title=\"Vai alla homa page\"></a>
   <a href=\"#paginacredits_a\" accesskey=\"r\" tabindex=\"90\" onClick=\"vai('paginacredits');return false;\" onKeyPress=\"vai('paginacredits');return false;\" title=\"Vai ai credits\"></a>
   <a href=\"#paginahelp_a\" accesskey=\"h\" tabindex=\"95\" onClick=\"vai('paginahelp');return false;\" onKeyPress=\"vai('paginahelp');return false;\" title=\"Vai all'help\"></a>
   <a href=\"#esci_a\" accesskey=\"e\" tabindex=\"100\" onClick=\"vai('esci');return false;\" onKeyPress=\"vai('esci');return false;\" title=\"Esci dal corso\"></a>
   Fine della pagina. Per riascoltarla torna al titolo.
</div>

</body>
</html>";


$path_file=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/start.htm";
$fp=fopen($path_file,"w");
fwrite($fp,$codice);
fclose($fp);
$path0=$PATH_ROOT_FILE."shell/";
$path1=$PATH_ROOT_FILE."materiali/$cod_area/$risorsa/shell/";

copy($path0."script/jfunzioni_esporta.js",$path1."/script/jfunzioni.js");
copy($path0."script/jfunzioni_test_esporta.js",$path1."/script/jfunzioni_test.js");
copy($path0."script/main.js",$path1."/script/main.js");
copy($path0."script/api_comm(piattaforma).js",$path1."/script/api_comm(piattaforma).js");
copyr($path0.$path_img,$path1."img");

/** esporto xml lom **/

require "./lom/config_xml_lom.php";
require "./lom/variabili_xml_lom.php";
require "./lom/funzioni_xml_lom.php";

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
$id_risorsa_manifest=$id_lo;

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

$filezip=$id_lo.".zip";
$cur_dir=getcwd();
chdir($PATH_ROOT_FILE."materiali/$cod_area/$risorsa");
$comando="/usr/bin/zip -r ".$PATH_ROOT_FILE."materiali/$cod_area/$filezip *";
exec($comando);
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
?>

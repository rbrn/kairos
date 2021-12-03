/* --- SHELL ACCESSIBILE: FUNZIONI E ISTRUZIONI DI AVVIO --- */

/* -- ACQUISIZIONE PARAMETRI -- */
function acquisisciparametri(){ // accetta i parametri da piattaforma e se presenti da querystring
	iniziacorso();
	punteggio = init_score;
	var stringa = init_suspendData;
	if (stringa){
		var parametri = stringa.split(",");
		if (parametri[0] > 0)
			dimensionicarattere = Number(parametri[0]);
		if (parametri[1] > 0)
			dimensionipagina = Number(parametri[1]);
		if (parametri[2] > 0)
			multimedia = Number(parametri[2]);
		if (parametri[3] > 0)
			punteggiomassimo = Number(parametri[3]);
		for(var i=4;i < parametri.length;i++){
			nodovisitato[i-3] = Number(parametri[i]);
		}
	}
	stringa = location.href.split("?");
	if (stringa[1]){
		var parametri = stringa[1].split(",");
		if (parametri[0] > 0)
			dimensionicarattere = Number(parametri[0]);
		if (parametri[1] > 0)
			dimensionipagina = Number(parametri[1]);
		if (parametri[2] > 0)
			multimedia = Number(parametri[2]);
	 }
}

/* -- VISUALIZZAZIONE PAGINE TUTORIALI -- */
function tutoriale(blocco,provenienza){ // visualizza la pagina prescelta e gestisce il menù
	finemedium();
	switch (elementoattivo){
		case 0: // home
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			document.getElementById("navigazionetutoriale").style.display="block";
			document.getElementById("pulsantezoom").style.display="none";
			break;
		case 2: // tutoriale
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			break;
		case 4: // sommario
			document.getElementById("pulsantezoom").style.display="none";
			document.getElementById("sommario").style.display="none";
			document.getElementById("navigazionetutoriale").style.display="block";
			document.getElementById("pulsanteindice").style.display="inline";
			document.getElementById("pulsantehome").style.display="inline";
			break;
	}
	if (tipotutoriale[blocco] == 1)
		document.getElementById("pulsantehistory").style.display="inline";
	else
		document.getElementById("pulsantehistory").style.display="none";
	switch (tipomenu){
		case 0:
			if (!nodovisitato[blocco] || nodovisitato[blocco] < 1){
				nodovisitato[blocco] = 1;
				nodivisitati++;
				document.getElementById("sommarioimm"+blocco).src = "../immagini/visto.gif";
				document.getElementById("sommarioimm"+blocco).alt = "Pagina visitata";
			}
			if (provenienza != 1){
				stacknodi.push(blocco);
				puntatorestack = stacknodi.length - 1;
			}
			document.getElementById("sommarioriga"+tutorialeattivo).style.backgroundColor="#ffffff";
			document.getElementById("sommarioriga"+blocco).style.backgroundColor="#efefef";
			break;
	}
	document.getElementById("pulsantehome").style.display="inline";
	document.getElementById("pulsanteindice").style.display="inline";

	tutorialeattivo = String(blocco);
	document.getElementById("tutoriale"+tutorialeattivo).style.display="block";
	window.open("#tutoriale"+tutorialeattivo+"_a","_self");
	iniziamedium("tut"+tutorialeattivo);
	elementoattivo = 2;
}

function indietro(){ // torna all'ultima pagina tutoriale visitata
	if (puntatorestack > 0 && tipotutoriale[tutorialeattivo] == 0 && elementoattivo !=4)
		puntatorestack--;
	if (puntatorestack > -1)
		tutoriale(stacknodi[puntatorestack],1);
}

function visualizzapagina(){ // visualizza il numero della pagina e il totale delle pagine
	numeropagina++;
	document.write("<p><span class='nascosto'>Pagina<\/span>");
	document.write("<span class='numeropagina'>"+numeropagina+" </span>");
	document.write("<span class='nascosto'> su <\/span>");
	document.write("<span class='totalepagine'> / "+paginetotali+"</span>");
}

/* -- VISUALIZZAZIONE HOME -- */
function homepage(){ // accede alla home page
	finemedium();
	switch (elementoattivo){
      		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="none";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			document.getElementById("pulsantehistory").style.display="inline";
			break;
      		case 4: // sommario
			document.getElementById("sommario").style.display="none";
			break;
	}
	document.getElementById("pulsantehome").style.display="none";
	document.getElementById("pulsanteindice").style.display="none";
	document.getElementById("homepage").style.display="block";
	window.open("#homepage_a","_self");
	iniziamedium("home");
	elementoattivo = 0;
}

/* -- VISUALIZZAZIONE INDICE -- */
function sommario(){ // accede all'indice generale del tutoriale
	finemedium();
	switch (elementoattivo){
      		case 0: // home
			document.getElementById("homepage").style.display="none";
			document.getElementById("pulsantehome").style.display="inline";
			break;
		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="none";
			document.getElementById("pulsanteindice").style.display="none";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			break;
	}
	document.getElementById("pulsantehistory").style.display="inline";
	document.getElementById("sommarioriga"+tutorialeattivo).style.fontWeight="bold";
	document.getElementById("sommario").style.display="block";
	window.open("#sommario_a","_self");
	elementoattivo = 4;
}

/* -- VISUALIZZAZIONE APPROFONDIMENTI -- */
function approfondimento(puntatorearrivo){ // visualizza approfondimento di primo livello
	finemedium();		
	document.getElementById("navigazionetutoriale").style.display="none";
	document.getElementById("pulsantehistory").style.display="none";
	document.getElementById("pulsantehome").style.display="none";
	document.getElementById("pulsanteindice").style.display="none";
	document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
	document.getElementById("approfondimento"+puntatorearrivo).style.display="block";
	window.open("#approfondimento"+approfondimentoattivo+"_a","_self");
	approfondimentoattivo = String(puntatorearrivo);
	elementoattivo = 5;
}

function approfondimento2(puntatorearrivo){ // visualizza approfondimento di secondo livello
	finemedium();		
	document.getElementById("approfondimento"+approfondimentoattivo).style.display="none";
	document.getElementById("approfondimento"+puntatorearrivo).style.display="block";
	window.open("#approfondimento"+approfondimentoattivo2+"_a","_self");
	approfondimentoattivo2 = String(puntatorearrivo);
	elementoattivo = 6;
}

function ritorna(){ // ritorna da approfondimenti
	if (elementoattivo == 6){
		document.getElementById("approfondimento"+approfondimentoattivo).style.display="block";
		document.getElementById("approfondimento"+approfondimentoattivo2).style.display="none";
		window.open("#approfondimento"+approfondimentoattivo+"_a","_self");
		elementoattivo = 5;
	}
	else {
		document.getElementById("approfondimento"+approfondimentoattivo).style.display="none";
		document.getElementById("tutoriale"+tutorialeattivo).style.display="block";
		if (tipotutoriale[tutorialeattivo] == 1)
			document.getElementById("pulsantehistory").style.display="inline";
		document.getElementById("pulsantehome").style.display="inline";
		document.getElementById("pulsanteindice").style.display="inline";
		document.getElementById("navigazionetutoriale").style.display="block";
		window.open("#tutoriale"+tutorialeattivo+"_a","_self");
		iniziamedium("tut"+tutorialeattivo);
		approfondimentoattivo = 0;
		elementoattivo = 2;
	}
}

/* -- VISUALIZZAZIONE PAGINE DI SERVIZIO -- */
function vai(puntatorearrivo){ // accesso alle pagine che permettono di tornare al punto di partenza
	finemedium();		
	document.getElementById("pulsantecredits").style.display="none";
	document.getElementById("pulsantehelp").style.display="none";
	document.getElementById("pulsanteuscita").style.display="none";
	switch (elementoattivo){
		case 0: // home
			document.getElementById("pulsantehistory").style.display="none";
			document.getElementById("homepage").style.display="none";
			break;
		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="none";
			document.getElementById("pulsantehistory").style.display="none";
			document.getElementById("pulsantehome").style.display="none";
			document.getElementById("pulsanteindice").style.display="none";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			break;
		case 4: // sommario
			document.getElementById("pulsantehistory").style.display="none";
			document.getElementById("pulsantehome").style.display="none";
			document.getElementById("sommario").style.display="none";
			break;
		case 5: // approfondimenti
			document.getElementById("approfondimento"+approfondimentoattivo).style.display="none";
			break;
		case 6: // approfondimenti II livello
			document.getElementById("approfondimento"+approfondimentoattivo2).style.display="none";
			break;
       	}
	paginaservizioattiva = puntatorearrivo;
	document.getElementById(paginaservizioattiva).style.display="block";
	window.open("#"+paginaservizioattiva+"_a","_self");
	if (puntatorearrivo == "esci"){ // pagina di riepilogo
		document.getElementById("riepilogopagine").value = nodivisitati;
		document.getElementById("riepilogopaginemax").value = paginetutoriali;
		document.getElementById("riepilogopunti").value = punteggio;
		document.getElementById("riepilogopuntimax").value = punteggiomassimo;
		document.getElementById("riepilogopuntitotalimin").value = punteggiominimo;
		document.getElementById("riepilogopuntitotalimax").value = punteggiototale;		
		if (nodivisitati == paginetutoriali){
			if (punteggio >= punteggiominimo)
				document.getElementById("riepilogostatus").value = "superato.";
			else
				document.getElementById("riepilogostatus").value = "completato.";
		}
		else
			document.getElementById("riepilogostatus").value = "da completare.";
	}
}

function ritornaindietro(){
	document.getElementById(paginaservizioattiva).style.display="none";
	document.getElementById("pulsantecredits").style.display="inline";
	document.getElementById("pulsantehelp").style.display="inline";
	document.getElementById("pulsanteuscita").style.display="inline";
	switch (elementoattivo){
		case 0: // home
			document.getElementById("homepage").style.display="block";
			window.open("#homepage_a","_self");
			iniziamedium("homepage");
			break;
		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="block";
			if (tipotutoriale[tutorialeattivo] == 1)
				document.getElementById("pulsantehistory").style.display="inline";
			document.getElementById("pulsantehome").style.display="inline";
			document.getElementById("pulsanteindice").style.display="inline";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="block";
			window.open("#tutoriale"+tutorialeattivo+"_a","_self");
			iniziamedium("tut"+tutorialeattivo);
			break;
     		case 4: // sommario
			document.getElementById("pulsantehistory").style.display="inline";
			document.getElementById("pulsantehome").style.display="inline";
			document.getElementById("sommario").style.display="block";
			window.open("#sommario_a","_self");
			break;
		case 5: // approfondimenti
			document.getElementById("approfondimento"+approfondimentoattivo).style.display="block";
			window.open("#approfondimento"+approfondimentoattivo+"_a","_self");
			break;
		case 6: // approfondimenti II livello
			document.getElementById("approfondimento"+approfondimentoattivo2).style.display="block";
			window.open("#approfondimento"+approfondimentoattivo2+"_a","_self");
			break;
       	}
}

/* -- MESSAGGI -- */
function inviamessaggio(testo,pagina,feedback){ // invia messaggi di sistema
	if (document.getElementById("messaggio"+pagina))
		document.getElementById("messaggio"+pagina).value = testo;
	if (testo != "" && feedback != "")
		feedbacksonoro(feedback);
}

/* -- INIZIALIZZAZIONE -- */
function inizializza(){ // nasconde tutte le pagine tranne la home e imposta i parametri iniziali
	var contatore = 0;
	impostacaratteri();
	document.getElementById("esci").style.display="none";
	document.getElementById("navigazionetutoriale").style.display="none";
	document.getElementById("paginahelp").style.display="none";
	document.getElementById("pulsantehistory").style.display="none";
	document.getElementById("pulsanteindice").style.display="none";
	document.getElementById("pulsantehome").style.display="none";
	document.getElementById("paginacredits").style.display="none";
	document.getElementById("sommario").style.display="none";
	if (multimedia==1)
		document.getElementById("pulsantesuonoon").style.display="none";
	else
		document.getElementById("pulsantesuonoff").style.display="none";


	contatore = 1; // nasconde il tutoriale e imposta il parametro
	while (document.getElementById("tutoriale"+contatore)){
		document.getElementById("tutoriale"+contatore).style.display="none";
		switch (tipomenu){
			case 0:
				if (nodovisitato[contatore] > 0){
					nodivisitati++;
					document.getElementById("sommarioimm"+contatore).src = "../immagini/visto.gif";
					document.getElementById("sommarioimm"+contatore).alt = "Pagina visitata";
				}
				break;
		}
		contatore++;
		paginetutoriali++;
	}
	contatore = 1; // nasconde gli approfondimenti
	while (document.getElementById("approfondimento"+contatore)){
		document.getElementById("approfondimento"+contatore).style.display="none";
		contatore++;
	}

	homepage();
	window.open("#inizio_a","_self");
	document.getElementById("body").style.display="block";
}

/* -- DIMENSIONE CARATTERI -- */
function impostacaratteri(){ // imposta il carattere in funzione del parametro inviato dalla querystring
	document.getElementById("contenuto").style.fontSize = String(dimensionicarattere) + "em";
}

function incrementa(){ // aumenta le dimensioni del carattere del 10%
	dimensionicarattere = dimensionicarattere + 0.1;
	document.getElementById("contenuto").style.fontSize = String(dimensionicarattere) + "em";
}

function decrementa(){ // diminuisce le dimensioni del carattere del 10%
	dimensionicarattere = dimensionicarattere - 0.1;
	document.getElementById("contenuto").style.fontSize = String(dimensionicarattere) + "em";
}

/* -- ROLLOVER -- */
function roll(immagine,progressivo){ // carica l'immagine di rollover
	if (progressivo)
	   var elemento = immagine+progressivo;
	else
	   var elemento = immagine;
	document.getElementById(elemento).src = "../immagini/pulsante_"+immagine+"_r.gif"
}

function noroll(immagine,progressivo){ // ricarica l'immagine normale
	if (progressivo)
	   var elemento = immagine+progressivo;
	else
	   var elemento = immagine;
	document.getElementById(elemento).src = "../immagini/pulsante_"+immagine+".gif";
}

/* -- DIMENSIONE SCHERMATA -- */
function aumentazoom(){ // aumenta le dimensioni della schermata
	var nomefile = location.href.split("#");
	nomefile = nomefile[0].split("?");
	dimensionipagina = 2;
	traccia();
	window.open(nomefile[0]+"?"+dimensionicarattere+','+dimensionipagina+','+multimedia,"_self");
}
multimedia

function diminuiscizoom(){ // diminuisce le dimensioni della schermata
	var nomefile = location.href.split("#");
	nomefile = nomefile[0].split("?");
	dimensionipagina = 1;
	traccia();
	window.open(nomefile[0]+"?"+dimensionicarattere+','+dimensionipagina+','+multimedia,"_self");
}

/* -- COMMENTI -- */
function contacaratteri(target,contatore,massimo){
 	StrLen = target.value.length;
	if(StrLen > massimo ){
		target.value = target.value.substring(0,massimo);
		CharsLeft = 0;
	}
	else {
		CharsLeft = massimo - StrLen;
	}
	document.getElementById("contatore"+contatore).value = massimo - target.value.length;
}

/* -- MULTIMEDIA -- */
function caricamedia(fileinput,posizione,immagine){ // carica i file multimediali
	var tipomedium = fileinput.split(".");
	var tipo = tipomedium[1];
	var nomefile = tipomedium[0];
	document.write("<p>");
	switch (tipo){
		case "mp3":
			if (tipobrowser == 1){
				document.write("<object class='audio' id='audio_"+nomefile+"' classid='clsid:22d6f312-b0f6-11d0-94ab-0080c74c7e95'>");
				document.write("<param name='filename' value='"+fileinput+"'>");
			}
	 		else{
				document.write("<object class='audio' id='audio_"+nomefile+"' data='"+fileinput+"'>");
			}
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='type' value='audio/x-mpeg'>");
			break;
		case "wmv":
			if (tipobrowser == 1 || tipobrowser == 2){
				document.write("<object class='video"+posizione+"' id='videowm_"+nomefile+"' classid='clsid:6BF52A52-394A-11D3-B153-00C04F79FAA6' type='application/x-oleobject' codebase='http://activex.microsoft.com/activex/controls/mplayer/en/nsmp2inf.cab#Version=6,4,5,715'>");
				document.write("<param name='url' value='"+fileinput+"'>");
			}
			else{
	      			document.write("<object class='video"+posizione+"' id='videowm_"+nomefile+"' data='"+fileinput+"'>");
			}
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='stretchToFit value='true'>");
			document.write("<param name='volume' value='60'>");
			break;

		case "mov":
			if (tipobrowser == 1){
				document.write("<object class='video"+posizione+"' id='videoqt_"+nomefile+"' classid='clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B' codebase='http://www.apple.com/qtactivex/qtplugin.cab'>");
				document.write("<param name='src' value='"+fileinput+"'>");
			}
			else{
      				document.write("<object class='video"+posizione+"' id='videoqt_"+nomefile+"' >");
				document.write("<param name='codetype' value='video/x-quicktime'>");
				document.write("<param name='type' value='video/x-quicktime'>");
			}
				document.write("<param name='autoplay' value='false'>");
				document.write("<param name='controller' value='true'>");
				document.write("<param name='enablejavascript' value='true'>");
				document.write("<param name='scale' value='tofit'>");
				document.write("<param name='volume' value='60'>");
			break;
		case "rpm":
			if (tipobrowser == 1){
				document.write("<object class='video"+posizione+"' classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'>");
				document.write("<param name='src' value='"+fileinput+"'>");
				document.write("<param name='autostart' value='false'>");
				document.write("<param name='controls' value='ImageWindow'>");
				document.write("<param name='console' value='video1'>");
				document.write("<param name='maintainaspect' value='true'>");
				document.write("</object>");
				document.write("<object class='videorp2"+posizione+"' id='videorp_"+nomefile+"' classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'>");
				document.write("<param name='src' value='"+fileinput+"'>");
				document.write("<param name='console' value='video1'>");
				document.write("<param name='controls' value='ControlPanel'>");
			}
			else{
				document.write("<object class='video"+posizione+"' id='videorp_"+nomefile+"' data='"+fileinput+"'>");
				document.write("<param name='src' value='"+fileinput+"'>");
				document.write("<param name='type' value='video/x-pn-realaudio-plugin'>");
				document.write("<param name='autostart' value='false'>");
				document.write("<param name='controls' value='ControlPanel'>");
				document.write("<param name='maintainaspect' value='true'>");
			}
			break;
		case "swf":
				document.write("<object class='animazione' id='flash_"+nomefile+"' type='application/x-shockwave-flash' data='"+fileinput+"'>");
   				document.write("<param name='movie' value='"+fileinput+"'>");
   				document.write("<param name='play' value='false'>");
			break;
		}
	document.write("<img src='"+immagine+"' alt=''>");
	document.write("</object>");
}

function attivamedium(){ // attiva il suono/filmato/animazione tramite pulsante
	multimedia = 1;
	if (document.getElementById(mediumattivo))
		playmedium();
	document.getElementById("pulsantesuonoon").style.display="none";
	document.getElementById("pulsantesuonoff").style.display="inline";
}

function disattivamedium(){ // disattiva il suono/filmato/animazione tramite pulsante
	multimedia = 0;
	stopmedium();
	document.getElementById("pulsantesuonoff").style.display="none";
	document.getElementById("pulsantesuonoon").style.display="inline";
}

function iniziamedium(nomemedium){ // attiva il suono/filmato/animazione
	if (document.getElementById("audio_"+nomemedium)){
		mediumattivo = "audio_"+nomemedium;
	}
	if (document.getElementById("flash_"+nomemedium)){
		mediumattivo = "flash_"+nomemedium;
	}
	if (document.getElementById("videowm_"+nomemedium)){
		mediumattivo = "videowm_"+nomemedium;
	}
	if (document.getElementById("videoqt_"+nomemedium)){
		mediumattivo = "videoqt_"+nomemedium;
	}
	if (document.getElementById("videorp_"+nomemedium)){
		mediumattivo = "videorp_"+nomemedium;
	}
	if (mediumattivo!="" && multimedia==1)
		playmedium();
}

function finemedium(){ // termina il suono/filmato/animazione
	stopmedium();
	mediumattivo = "";
}

function avviamedium(){ // attiva il suono/filmato/animazione con ritardo
	if (document.getElementById(mediumattivo)){
		setTimeout("playmedium()",2500);
	}
}

function feedbacksonoro(nomefeedback){ // invia un feedback sonoro
	if (document.getElementById("audio_"+nomefeedback)){
		setTimeout("try{document.getElementById('audio_"+nomefeedback+"').Play()}catch(e){}",100);
	}
}

function playmedium(){ // avvia il suono/filmato/animazione con modalità differenziate
	var tipomedium = mediumattivo.split("_");
	switch (tipomedium[0]){
		case "audio":
			setTimeout("try{document.getElementById('"+mediumattivo+"').Play()}catch(e){}",100);
			break;
		case "flash":
			try{
				document.getElementById(mediumattivo).Play();
			}
			catch(e){}
			break;
		case "videoqt":
			setTimeout("try{document.getElementById('"+mediumattivo+"').Play()}catch(e){}",500);
			break;
		case "videorp":
			setTimeout("try{document.getElementById('"+mediumattivo+"').DoPlay()}catch(e){}",500);
			break;
		case "videowm":
			setTimeout("try{document.getElementById('"+mediumattivo+"').Controls.Play()}catch(e){}",500);
			break;
	}
}

function stopmedium(){ // interrompe il suono/filmato/animazione con modalità differenziate
	if (document.getElementById(mediumattivo)){
		var tipomedium = mediumattivo.split("_");
		switch (tipomedium[0]){
			case "audio":
				try{
					document.getElementById(mediumattivo).Stop();
				}
				catch(e){}
				break;
			case "flash":
				try{
					document.getElementById(mediumattivo).StopPlay();
				}
				catch(e){}
				break;
			case "videoqt":
				try{
					document.getElementById(mediumattivo).Stop();
				}
				catch(e){}
				break;
			case "videorp":
				try{
					document.getElementById(mediumattivo).DoStop();
				}
				catch(e){}
				break;
			case "videowm":
				try{
					document.getElementById(mediumattivo).Controls.Stop();
				}
				catch(e){}
				break;
		}
	}
}

/* -- RICERCA PLUG-IN -- */
function cercaplugin(){  // cerca i plug-in disponibili in browser diversi da IE
	if (navigator.plugins && navigator.plugins.length > 0){
		for(var i=0;i < navigator.plugins.length;i++){
			if(navigator.plugins[i].name.indexOf("Flash") >= 0 || navigator.plugins[i].description.indexOf("Flash") >= 0)
				plugin_fl = 1;
			if(navigator.plugins[i].name.indexOf("RealPlayer") >= 0 || navigator.plugins[i].description.indexOf("RealPlayer") >= 0){
				plugin_rp = 1;
			}
			if(navigator.plugins[i].name.indexOf("QuickTime") >= 0 || navigator.plugins[i].description.indexOf("Quick Time") >= 0){
				plugin_qt = 1;
			}
			if(navigator.plugins[i].name.indexOf("Windows Media") >= 0 || navigator.plugins[i].description.indexOf("Windows Media") >= 0){
				plugin_wm = 1;
			}
		}
	}
}

function comunicaplugin(){ // elenca i plug-in disponibili
	var comunicazione = "";
	if (plugin_qt + plugin_wm + plugin_rp == 0)
		comunicazione =	"Per gestire audio e video è necessario installare Windows Media Player, Real Player, QuickTime.<br>";
	if (plugin_fl == 0)
		comunicazione =	comunicazione + "Per le animazioni è necessario Flash.";
	if (comunicazione != "")
		document.write("<p class='comunicazioni'>"+comunicazione);
}

/* -- USCITA -- */
function chiudi(){ // predispone la chiusura della finestra del browser
	traccia(); 
	self.close(); 
}

function traccia(){ // memorizza i dati
	var stato = new String;
	if (nodivisitati == paginetutoriali){
		tutorialeattivo = "1";
		if (punteggio >= punteggiominimo)
			stato = "passed";
		else
			stato = "completed";
	}
	else
		stato = "incomplete";
 	var dati = dimensionicarattere+ ","+dimensionipagina+","+multimedia+","+punteggiomassimo+nodovisitato.join();
	concludicorso(stato,tutorialeattivo,punteggio,dati);
}

/* -- ISTRUZIONI INIZIALI -- */

/* -- Assegnazione variabili -- */
var tutorialeattivo = "1";
var approfondimentoattivo = "1";
var approfondimentoattivo2 = "0";
var paginaservizioattiva = new String;
var mediumattivo = "";
var elementoattivo = 0; // 0= home 2=tutoriale 4=indice 5/6=approfondimento
var numeropagina = 0;
var dimensionicarattere = 1;
var dimensionipagina = 1;
var multimedia = 0;
var paginetutoriali = 0;
var punteggio = 0; //punteggio ottenuto
var punteggiomassimo = 0; //punteggio massimo ottenibile
var numeroerrore = -1; // primo errore rilevato nella pagina;
var nodivisitati = 0;
var nodovisitato = new Array;
var stacknodi = new Array;
var puntatorestack = -1;
var nohistory = 0; // pulsante history 0= abilitato 1=disabilitato

/* -- Identificazione browser -- */
var tipobrowser = new Number;
var plugin_qt = 0; // Quick Time
var plugin_wm = 0; // Windows Media Player
var plugin_rp = 0; // Real Player
var plugin_fl = 0; // Flash
switch (navigator.appName){
	case "Microsoft Internet Explorer": 
 		tipobrowser = 1;
		document.writeln("<script language='VBscript'>");
		document.writeln("on error resume next");
		document.writeln('plugin_fl = IsObject(CreateObject("ShockwaveFlash.ShockwaveFlash.6"))');
		document.writeln('plugin_wm = IsObject(CreateObject("MediaPlayer.MediaPlayer.1"))');
		document.writeln('plugin_rp = IsObject(CreateObject("rmocx.RealPlayer G2 Control"))');
		document.writeln('plugin_rp = IsObject(CreateObject("RealPlayer.RealPlayer(tm) ActiveX Control (32-bit)"))');
		document.writeln('plugin_rp = IsObject(CreateObject("RealVideo.RealVideo(tm) ActiveX Control (32-bit)"))');
		document.writeln("qtime = false");
		document.writeln('Set qtime = CreateObject("QuickTimeCheckObject.QuickTimeCheck.1")');
		document.writeln("If IsObject(qtime) Then");
		document.writeln("If qtime.IsQuickTimeAvailable(0) Then");
		document.writeln("plugin_qt = 1");
		document.writeln("End If");
		document.writeln("End If");
		document.writeln("</script>");
		break;
	case "Netscape": 
		tipobrowser = 2;
		cercaplugin();
		break;
	case "Opera": 
		tipobrowser = 3;
		cercaplugin();
		break;
	default: 
		tipobrowser = 3;
		cercaplugin();
		break;
}

/* -- Configurazione ambiente -- */
acquisisciparametri();
window.moveTo(0,0);
if (dimensionipagina==2){
	document.write("<link rel='stylesheet' href='../stili/tutoriale2.css' type='text/css'>");
	window.resizeTo(1024,755);
}
else{
	document.write("<link rel='stylesheet' href='../stili/hidden.css' type='text/css'>");
	window.resizeTo(800,595);
}
/* -- ROUTINE DI GESTIONE PAGINA -- */
var tutorialeattivo = "1";
var approfondimentoattivo = "1";
var approfondimentoattivo2 = "0";
var paginaservizioattiva = new String;
var mediumattivo = "";
var elementoattivo = 0; // 0= home 2=tutoriale 4=indice 5/6=approfondimento
var numeropagina = 0;
var messaggio = new String;
var dimensionicarattere = 1;
var dimensionipagina = 1;
var multimedia = 0;
var paginetutoriali = new Number;
var punteggio = 0;
var punteggiomassimo = 0;
var paginetest = new Array;

/* -- CONFIGURAZIONE BROWSER -- */
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
		if (plugin_wm == 1){
			plugin_qt = 0;
			plugin_rp = 0;
		}
		else if (plugin_qt == 1)
			plugin_rp = 0;
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
			paginetest[i-3] = Number(parametri[i]);
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
function tutoriale(blocco){  // visualizza la pagina prescelta e gestisce il menù
	finemedium();
	switch (elementoattivo){
      		case 0: // prima volta
			if (init_bookmark > 0)
				blocco = init_bookmark;
			if (init_bookmark > 1)
				document.getElementById("pulsantezoom").style.display="none";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			document.getElementById("navigazionetutoriale").style.display="block";
			break;
      		case 2: // tutoriale
			if (messaggio != "")
				cancellamessaggio("messaggio"+tutorialeattivo);
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			document.getElementById("pulsantezoom").style.display="none";
			break;
     		case 4: // sommario
			document.getElementById("pulsantezoom").style.display="none";
			document.getElementById("sommario").style.display="none";
			document.getElementById("navigazionetutoriale").style.display="block";
			document.getElementById("pulsanteindice").style.display="inline";
			break;
	}
	switch (tipomenu){
		case 0:
			document.getElementById("indice"+tutorialeattivo).style.backgroundColor="#ffffff";
			document.getElementById("indice"+blocco).style.fontVariant="small-caps";
			document.getElementById("indice"+blocco).style.backgroundColor="#efefef";
			break;
	}
	tutorialeattivo = String(blocco);
	document.getElementById("tutoriale"+tutorialeattivo).style.display="block";
	window.open("#tutoriale"+tutorialeattivo+"_a","_self");
	iniziamedium("tut"+tutorialeattivo);
	elementoattivo = 2;
}

function visualizzapagina(){ // visualizza il numero della pagina e il totale delle pagine
	numeropagina++;
	document.write("<p><span class='nascosto'>Pagina<\/span>");
	document.write("<span class='numeropagina'>"+numeropagina+" </span>");
	document.write("<span class='nascosto'> su <\/span>");
	document.write("<span class='totalepagine'> / "+ultimapagina+"</span>");
}

/* -- VISUALIZZAZIONE INDICE -- */
function sommario(){ // accede all'indice generale del tutoriale
	finemedium();
	switch (elementoattivo){
      		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="none";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			break;
	}
	document.getElementById("pulsanteindice").style.display="none";
	document.getElementById("indice"+tutorialeattivo).style.fontWeight="bold";
	document.getElementById("sommario").style.display="block";
	window.open("#sommario_a","_self");
	elementoattivo = 4;
}

/* -- VISUALIZZAZIONE APPROFONDIMENTI -- */
function approfondimento(puntatorearrivo){ // visualizza approfondimento di primo livello
	finemedium();		
	document.getElementById("navigazionetutoriale").style.display="none";
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
      		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="none";
			document.getElementById("pulsantehome").style.display="none";
			document.getElementById("pulsanteindice").style.display="none";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			break;
     		case 4: // sommario
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
}

function ritornaindietro(){
	document.getElementById(paginaservizioattiva).style.display="none";
	document.getElementById("pulsantecredits").style.display="inline";
	document.getElementById("pulsantehelp").style.display="inline";
	document.getElementById("pulsanteuscita").style.display="inline";
	switch (elementoattivo){
      		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="block";
			document.getElementById("pulsantehome").style.display="inline";
			document.getElementById("pulsanteindice").style.display="inline";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="block";
			window.open("#tutoriale"+tutorialeattivo+"_a","_self");
			iniziamedium("tut"+tutorialeattivo);
			break;
     		case 4: // sommario
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
function inviamessaggio(testo,pagina){ // invia messaggi di sistema
	messaggio = testo;
	document.getElementById("messaggio"+pagina).value = messaggio;
	feedbacksonoro("messaggio");
}

function cancellamessaggio(pagina){ // invia messaggi di sistema
	messaggio = "";
	document.getElementById(pagina).value = messaggio;
}

/* -- INIZIALIZZAZIONE -- */
function inizializza(){ // nasconde tutte le pagine tranne la home e imposta i parametri iniziali
	var contatore = 0;
	impostacaratteri();
	document.getElementById("esci").style.display="none";
	document.getElementById("navigazionetutoriale").style.display="none";
	document.getElementById("paginahelp").style.display="none";
	document.getElementById("paginacredits").style.display="none";
	document.getElementById("sommario").style.display="none";
	if (multimedia==1)
		document.getElementById("pulsantesuonoon").style.display="none";
	else
		document.getElementById("pulsantesuonoff").style.display="none";


	contatore = 1; // nasconde il tutoriale
	while (document.getElementById("tutoriale"+contatore)){
		document.getElementById("tutoriale"+contatore).style.display="none";
		contatore++;
		paginetutoriali++;
	}

	contatore = 1; // nasconde gli approfondimenti
	while (document.getElementById("approfondimento"+contatore)){
		document.getElementById("approfondimento"+contatore).style.display="none";
		contatore++;
	}
	tutoriale(1);
	riepilogopunteggi();
	document.getElementById("body").style.display="block";
}

function azzera(){ // azzera punteggi e segnalibro
	init_bookmark = 0;
	punteggio = 0;
}

/* -- DIMENSIONE CARATTERI -- */
function impostacaratteri(){ // imposta il carattere in funzione del parametro inviato dalla querystring
	var stringa = String(dimensionicarattere) + "em";
	document.getElementById("contenuto").style.fontSize = stringa;
}

function incrementa(){ // aumenta le dimensioni del carattere del 10%
	dimensionicarattere = dimensionicarattere + 0.1;
	var stringa = String(dimensionicarattere) + "em";
	document.getElementById("contenuto").style.fontSize = stringa;
}

function decrementa(){ // diminuisce le dimensioni del carattere del 10%
	dimensionicarattere = dimensionicarattere - 0.1;
	var stringa = String(dimensionicarattere) + "em";
	document.getElementById("contenuto").style.fontSize = stringa;
}

/* -- ROLLOVER -- */
function roll(immagine,progressivo){ // carica l'immagine di rollover
	if (progressivo)
	   var elemento = immagine+String(progressivo);
	else
	   var elemento = immagine;
	document.getElementById(elemento).src = "../immagini/pulsante_"+immagine+"_r.gif"
}

function noroll(immagine,progressivo){ // ricarica l'immagine normale
	if (progressivo)
	   var elemento = immagine+String(progressivo);
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
	window.open(nomefile[0]+"?"+dimensionicarattere+','+dimensionipagina,"_self");
}

function diminuiscizoom(){ // diminuisce le dimensioni della schermata
	var nomefile = location.href.split("#");
	nomefile = nomefile[0].split("?");
	dimensionipagina = 1;
	traccia();
	window.open(nomefile[0]+"?"+dimensionicarattere+','+dimensionipagina,"_self");
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
function caricasuono(fileaudio){ // carica i file audio
	if (plugin_qt + plugin_wm + plugin_rp > 0){
		if (tipobrowser == 1){
			document.write("<object class='audio' id='audio_"+fileaudio+"' classid='clsid:22d6f312-b0f6-11d0-94ab-0080c74c7e95'>");
			document.write("<param name='filename' value='"+fileaudio+".mp3'>");
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='type' value='audio/x-mpeg'>");
			document.write("</object>");
		}
	 	else{
			document.write("<object class='audio' id='audio_"+fileaudio+"' data='"+fileaudio+".mp3'>");
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='type' value='audio/x-mpeg'>");
			document.write("</object>");
		}
	}
}

function caricavideo(filevideo,posizione){ // carica i file video
	if (tipobrowser == 1){
		if (plugin_wm == 1){
			document.write("<object class='video"+posizione+"' id='videowm_"+filevideo+"' classid='clsid:6BF52A52-394A-11d3-B153-00C04F79FAA6'>");
			document.write("<param name='url' value='"+filevideo+".wmv'>");
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='UIMode' value='full'>");
			document.write("<param name='CanSeek' value='true'>");
			document.write("<param name='enable' value='true'>");
			document.write("<param name='CanSeekToMarkers' value='true'>");
			document.write("<param name='volume' value='60'>");
			document.write("</object>");
			return;
		}
		if (plugin_qt == 1){
			document.write("<object class='video"+posizione+"' id='videoqt_"+filevideo+"' classid='clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B' codebase='http://www.apple.com/qtactivex/qtplugin.cab'>");
			document.write("<param name='src' value='"+filevideo+".mov'>");
			document.write("<param name='autoplay' value='false'>");
			document.write("<param name='showcontrols' value='true'>");
			document.write("<param name='scale' value='tofit'>");
			document.write("<param name='volume' value='60'>");
			document.write("</object>");
			return;

		}
		if (plugin_rp == 1){
			document.write("<object class='video"+posizione+"' classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'>");
			document.write("<param name='src' value='"+filevideo+".ram'>");
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='console' value='video1'>");
			document.write("<param name='maintainaspect' value='true'>");
			document.write("<param name='controls' value='ImageWindow'>");
			document.write("</object>");

			document.write("<object class='videorp2"+posizione+"' id='videorp_"+filevideo+"' classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'>");
			document.write("<param name='src' value='"+filevideo+".ram'>");
			document.write("<param name='console' value='video1'>");
			document.write("<param name='controls' value='controlpanel'>");
			document.write("</object>");
			return;
		}

	}
	else{
		if (plugin_qt == 1){
      			document.write("<object class='videosx' id='videoqt_"+filevideo+"' data='"+filevideo+".mov'>");
			document.write("<param name='autoplay' value='false'>");
			document.write("<param name='showcontrols' value='true'>");
			document.write("<param name='scale' value='tofit'>");
			document.write("<param name='type' value='video/x-quicktime'>");
			document.write("<param name='volume' value='60'>");
			document.write("</object>");
			return;
		}
	}
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

/* -- TEST -- */
function verificatest(pagina,rispostaesatta,punti,messaggiook,messaggioko){ // verifica le domande a risposta chiusa
	var contatore = 0;
	var risposta = 0;
	if (paginetest[pagina] > 0){
		inviamessaggio("Hai già risposto. Vai avanti.",pagina);
		return;
	}
	if (!messaggiook)
		messaggiook = "Risposta esatta!";
	if (!messaggioko)
		messaggioko = "Hai sbagliato!";		
	while (document.getElementById("test"+pagina).elements[contatore]){
		if (document.getElementById("test"+pagina).elements[contatore].checked)
			risposta = contatore + 1;
		contatore++;
	}
	if (risposta == 0)
		inviamessaggio("Non hai ancora risposto",pagina);
	else if (risposta == rispostaesatta){
		inviamessaggio(messaggiook,pagina);
		punteggio = punteggio + punti;
		paginetest[pagina] = 1;
	}
	else {
		inviamessaggio(messaggioko,pagina);
		if (punti > 0)
			paginetest[pagina] = 2;
	}
	riepilogopunteggi(punti);
}

function avantitest(pagina,destinazione){ // accede alla pagina tutoriale se c'è stata risposta al test
	if (paginetest[pagina] > 0)
		tutoriale(destinazione);
	else
		inviamessaggio("Prima devi rispondere!",pagina);
}

function riepilogopunteggi(punti){ // imposta i punteggi nella pagina di riepilogo
	if (punti > 0)
		punteggiomassimo = punteggiomassimo + punti;
	document.getElementById("riepilogopunti").value = punteggio;
	document.getElementById("riepilogopuntimax").value = punteggiomassimo;
}

/* -- USCITA -- */
/*
function chiudi(){ // predispone la chiusura della finestra del browser
	traccia(); 
	self.close(); 
}


function traccia(){ // memorizza i dati
 	var dati = dimensionicarattere+ ","+dimensionipagina+","+multimedia+paginetest.join();
	if (tutorialeattivo == ultimapagina)
		concludicorso("completed","1",punteggio,dati);
	else
		concludicorso("incomplete",tutorialeattivo,punteggio,dati);
}
*/

/* -- RICERCA PLUG-IN -- */
function cercaplugin(){  // cerca i plug-in disponibili in browser diversi da IE
	if (navigator.plugins && navigator.plugins.length > 0){
		for(var i=0;i < navigator.plugins.length;i++){
			if(navigator.plugins[i].name.indexOf("Flash") >= 0 || navigator.plugins[i].description.indexOf("Flash") >= 0)
				plugin_fl = 1;
			if(navigator.plugins[i].name.indexOf("QuickTime") >= 0 || navigator.plugins[i].description.indexOf("Quick Time") >= 0){
				plugin_qt = 1;
				return;
			}
			if(navigator.plugins[i].name.indexOf("Windows Media") >= 0 || navigator.plugins[i].description.indexOf("Windows Media") >= 0){
				plugin_wm = 1;
				return;
			}
			if(navigator.plugins[i].name.indexOf("RealPlayer") >= 0 || navigator.plugins[i].description.indexOf("RealPlayer") >= 0){
				plugin_rp = 1;
				return;
			}
		}
	}
}

function comunicaplugin(){ // elenca i plug-in disponibili
		if (plugin_qt + plugin_wm + plugin_rp == 0)
			document.write("Per gestire audio e video è necessario installare Windows Media Player, Real Player o QuickTime.");
		else{
			document.write("Per gestire audio e video sarà utilizzato ");
			if (plugin_wm == 1)
				document.write("Windows Media Player.");
			if (plugin_rp == 1)
				document.write("Real Player.");
			if (plugin_qt == 1)
				document.write("QuickTime.");
		} 
		if (plugin_fl == 0)
			document.write("<br>Per vedere le animazioni è necessario installare Flash Player.");
		else
			document.write("<br>Flash Player è installato.");
}

/* -- USCITA -- */
function chiudi(){ // predispone la chiusura della finestra del browser
	traccia(); 
	self.close(); 
}

function traccia(){ // memorizza i dati
	var stato = new String;
	if (tutorialeattivo == ultimapagina){
		tutorialeattivo = "1";
		stato = "completed";
	} else {
		stato = "incomplete";
 	};
	var dati = dimensionicarattere+ ","+dimensionipagina+","+multimedia+","+punteggiomassimo+paginetest.join();

	concludicorso(stato,tutorialeattivo,punteggio,dati);
}
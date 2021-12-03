/* --- SHELL ACCESSIBILE: FUNZIONI E ISTRUZIONI DI AVVIO --- */

/* -- ACQUISIZIONE PARAMETRI -- */
function acquisisciparametri(){ // accetta i parametri da piattaforma e se presenti da querystring
	iniziacorso();
	var stringa = init_suspendData;
	if (stringa){
		var parametri = stringa.split(",");
		if (parametri[0] > 0)
			dimensionicarattere = Number(parametri[0]);
		if (parametri[1] > 0)
			dimensionipagina = Number(parametri[1]);
		if (parametri[2] > 0)
			multimedia = Number(parametri[2]);
		if (modocontinua){
			if (init_score > 0)
				punteggio = init_score;
			for(var i=3;i < parametri.length;i++){
				if (parametri[i] != null)
					nodovisitato[nometutoriale[i-2]] = Number(parametri[i])
			}
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
function muovi(direzione){ // accesso alle pagina da pulsanti
	switch (direzione){
		case 1: // avanti
			if (tipotutoriale[tutorialeattivo] != 2)
				tutoriale(successivo[tutorialeattivo]);
			else{
				switch (tipolo){
					case "a":
						if (nodovisitato[tutorialeattivo] == 3 || nodovisitato[tutorialeattivo] == 5 || ((nodovisitato[tutorialeattivo] == 2 || nodovisitato[tutorialeattivo] == 4) && bloccoavanzamento == 0))
							tutoriale(successivo[tutorialeattivo]);
						else
							inviamessaggio(messaggiofeedback[13],tutorialeattivo,"messaggio");
						break;
					case "b":
						if (nodovisitato[tutorialeattivo] == 1 || ((nodovisitato[tutorialeattivo] == 2 || nodovisitato[tutorialeattivo] == 4) && bloccoavanzamento == 1))
							inviamessaggio(messaggiofeedback[13],tutorialeattivo,"messaggio");
						else if (punteggio >= punteggiosoglia)
							tutoriale(successivo[tutorialeattivo]);
						else{
							azzera();
							inviamessaggio(messaggiofeedback[15],1,"ko");
							tutoriale(nometutoriale[1]);
						}
						break;
					case "c":
						if (nodovisitato[tutorialeattivo] > 1)
							tutoriale(successivo[tutorialeattivo]);
						else
							inviamessaggio(messaggiofeedback[14],tutorialeattivo,"messaggio");
						break;
				}
			}
			break;
		case 2: // indietro
			tutoriale(precedente[tutorialeattivo]);
			break;
	}
}

function tutoriale(pagina,ritorno){ // visualizza la pagina prescelta e gestisce il menù
	var blocco = pagina;
	finemedium();
	document.getElementById(tutorialeattivo).style.display="none";
	if (tutorialealternativo[blocco] && (multimedia == 0 || nodoplugin[blocco] == 0))
		blocco = tutorialealternativo[blocco];
	if (ritorno == 1 && puntatorestack == ""){ // memorizza la pagina chiamante
		if (tutorialeprincipale[tutorialeattivo] == null)
			puntatorestack = tutorialeattivo;
		else
			puntatorestack = tutorialeprincipale[tutorialeattivo];
	}
	if (puntatorestack != ""){ // modalità protetta
		document.getElementById("comandohome").style.display="none";
		document.getElementById("pulsantehistory").style.display="inline";
		document.getElementById("pulsanteindice").style.display="none";
		document.getElementById("pulsantehome").style.display="none";
	}
	else{
		document.getElementById("comandohome").style.display="inline";
		document.getElementById("pulsantehistory").style.display="none";
		document.getElementById("pulsantehome").style.display="inline";
		document.getElementById("pulsanteindice").style.display="inline";
	}
	if (multimedia == 1) // comando nascosto di disabilitazione
		document.getElementById("comandomultimedia").style.display="block";
	else
		document.getElementById("comandomultimedia").style.display="none";
	if (successivo[pagina] != "" && (puntatorestack == "" || tipotutoriale[successivo[pagina]] != 2)) // pulsante "Avanti"
		document.getElementById("pulsanteavanti").style.display="inline";
	else
		document.getElementById("pulsanteavanti").style.display="none";
	if (precedente[pagina] != "" && (puntatorestack == "" || tipotutoriale[precedente[pagina]] != 2))// pulsante "Indietro"
		document.getElementById("pulsanteindietro").style.display="inline";
	else
		document.getElementById("pulsanteindietro").style.display="none";
	switch (tipotutoriale[blocco]){// tipo tutoriale
		case 0: // home
			document.getElementById("pulsantehome").style.display="none";
			document.getElementById("comandohome").style.display="none";
			break;
		case 2: // test
			switch (nodovisitato[blocco]){// tipo tutoriale
				case 2:
					inviamessaggio(messaggiofeedback[24],blocco);
					break;
				case 3:
					inviamessaggio(messaggiofeedback[25],blocco);
					break;
				case 4:
					inviamessaggio(messaggiofeedback[24],blocco);
					break;
				case 5:
					inviamessaggio(messaggiofeedback[27],blocco);
					break;
				default:
					inviamessaggio("",blocco,"messaggio");
					break;
			}
			inviapunteggio(blocco);
			break;
		case 3: // introduzione
			inviamessaggio("",blocco,"messaggio");
			break;
		case 4: // riepilogo
			document.getElementById("punteggio_"+blocco).value = punteggio;
			var classepunteggio = (punteggiomassimo - punteggio)/(punteggiomassimo / 4);
			if (classepunteggio > 4){
				document.getElementById("feedback_"+blocco).src = "shell/img/riepilogo_01.gif";
				document.getElementById("feedback_"+blocco).alt = messaggiofeedback[1];
				inviamessaggio(messaggiofeedback[6],blocco);
			}
			else if (classepunteggio > 3){
				document.getElementById("feedback_"+blocco).src = "shell/img/riepilogo_02.gif";
				document.getElementById("feedback_"+blocco).alt = messaggiofeedback[2];
				inviamessaggio(messaggiofeedback[7],blocco);
				}
			else if (classepunteggio > 2){
				document.getElementById("feedback_"+blocco).src = "shell/img/riepilogo_03.gif";
				document.getElementById("feedback_"+blocco).alt = messaggiofeedback[3];
				inviamessaggio(messaggiofeedback[8],blocco);
			}
			else if (classepunteggio > 1){
				document.getElementById("feedback_"+blocco).src = "shell/img/riepilogo_04.gif";
				document.getElementById("feedback_"+blocco).alt = messaggiofeedback[4];
				inviamessaggio(messaggiofeedback[9],blocco);
			}
			else{
				document.getElementById("feedback_"+blocco).src = "shell/img/riepilogo_05.gif";
				document.getElementById("feedback_"+blocco).alt = messaggiofeedback[5];
				inviamessaggio(messaggiofeedback[10],blocco);
			}
			break;
		case 5: // commenti
			inviamessaggio("",blocco,"messaggio");
			break;
	}
	if (tutorialeprincipale[blocco] != null){// indice
		document.getElementById("sommarioimm_"+tutorialeprincipale[blocco]).src = "shell/img/visto.gif";
		document.getElementById("sommarioimm_"+tutorialeprincipale[blocco]).alt = "Pagina visitata";
		document.getElementById("sommarioriga_"+tutorialeprincipale[blocco]).style.backgroundColor="#efefef";
	}
	else{
		document.getElementById("sommarioimm_"+blocco).src = "shell/img/visto.gif";
		document.getElementById("sommarioimm_"+blocco).alt = "Pagina visitata";
		document.getElementById("sommarioriga_"+blocco).style.backgroundColor="#efefef";
	}
	if (tutorialeprincipale[tutorialeattivo] != null){
		if (tutorialeprincipale[tutorialeattivo] != tutorialeprincipale[blocco])
			document.getElementById("sommarioriga_"+tutorialeprincipale[tutorialeattivo]).style.backgroundColor="#ffffff";
	}
	else
		document.getElementById("sommarioriga_"+tutorialeattivo).style.backgroundColor="#ffffff";
	if (nodovisitato[blocco] < 1 || nodovisitato[blocco] == null){// memorizzazione pagine visitate
		nodovisitato[blocco] = 1;
		if (tutorialeprincipale[blocco] != null && nodovisitato[tutorialeprincipale[blocco]] < 1)
			nodovisitato[tutorialeprincipale[blocco]] = 1;
	}
	tutorialeattivo = blocco;
	switch (iniziocorso){ // operazioni iniziali
		case 1: // prima volta
			iniziocorso = 2;
			window.open("#inizio_a","_self");
			if (init_suspendData != "" && modocontinua)
				document.getElementById("pulsantecontinua").style.display="inline";
			break;
		case 2: // seconda volta
			iniziocorso = 3;
			document.getElementById("pulsantezoom").style.display="none";
			document.getElementById("pulsantecontinua").style.display="none";
			window.open("#"+tutorialeattivo+"_a","_self");
			break;
		case 3: // a regime
			window.open("#"+tutorialeattivo+"_a","_self");
			break;
	}
	document.getElementById(tutorialeattivo).style.display="block";
	iniziamedium();
	elementoattivo = 2;
}

function indietrohistory(){ // torna all'ultima pagina tutoriale visitata
	if (puntatorestack != ""){
		var puntatore = puntatorestack;
		puntatorestack = "";
		tutoriale(puntatore);
	}
}

function visualizzapagina(pagina){ // visualizza il numero della pagina e gli elementi tipici della pagina
	document.write("<p><span class='nascosto'>Pagina<\/span>");
	if (tutorialeprincipale[pagina] != null){
		if (numerotutoriale[tutorialeprincipale[pagina]] > 0){
			document.write("<span class='numeropagina'>"+numerotutoriale[tutorialeprincipale[pagina]]+" </span>");
			document.write("<span class='nascosto'> su <\/span>");
			document.write("<span class='totalepagine'> / "+paginetutoriali+"</span>");
		}
	}
	else if (numerotutoriale[pagina] > 0){
		document.write("<span class='numeropagina'>"+numerotutoriale[pagina]+" </span>");
		document.write("<span class='nascosto'> su <\/span>");
		document.write("<span class='totalepagine'> / "+paginetutoriali+"</span>");
	}
	switch (tipotutoriale[pagina]){
		case 1: // tutoriale
			scriviareamessaggio(pagina);
			break;
		case 2: // test
			scriviareamessaggio(pagina);
			scriviareapunteggio(pagina);
			break;
		case 3: // introduzione
			scriviareamessaggio(pagina);
			break;
		case 4: // riepilogo
			scriviareamessaggio(pagina);
			scriviareapunteggio(pagina);
			break;
		case 5: // commento
			scriviareamessaggio(pagina);
			document.write("<div class='areapunteggio'>");
			document.write("<div class='intestazionepunteggio'><label for='contatore_"+pagina+"'>Caratteri</label></div>");
			document.write("<input class='punteggio' accesskey='r' tabindex='90' id='contatore_"+pagina+"' readonly size='4' maxlength='4'><br>");
			document.write("<span class='punteggiobase'>max 4000</span>");
			document.write("</div>");
			break;
		case 6: // test tipo cruciverba
			scriviareamessaggio(pagina);
			scriviareapunteggio(pagina);
		}
}

function scriviareamessaggio(pagina){ // inserisce l'oggetto messaggio
	document.write("<div class='areamessaggio'>");
	document.write("<label class='nascosto' for='messaggio_"+pagina+"'>Messaggio:</label>");
	document.write("<input class='messaggio' accesskey='g' tabindex='120' id='messaggio_"+pagina+"' readonly size='100' maxlength='100'>");
	document.write("</div>");
}

function scriviareapunteggio(pagina){ // inserisce l'oggetto punteggio
	document.write("<div class='areapunteggio'>");
	document.write("<div class='intestazionepunteggio'><label for='punteggio_"+pagina+"'>Punti</label></div>");
	document.write("<input class='punteggio' accesskey='u' tabindex='130' id='punteggio_"+pagina+"' readonly size='2' maxlength='2'><br>");
	document.write("<span class='punteggiobase'>su "+punteggiomassimo+"</span>");
	document.write("</div>");
	document.write("<p><img id='feedback_"+pagina+"' class='feedbackpunteggio'>");
}

function comandi(pagina,tipotest,rispostaesatta,tutorialetest,messaggio,animazione){ //inserisce i comandi nascosti per gestire audio, video e animazioni
	var stringa = new String;
	if (mediumblocco[pagina]){
		var medium = mediumblocco[pagina].split(".");
		switch (medium[1]){
			case "mp3":
				stringa = "l'audio";
				break;
			case "mov":
				stringa = "il video";
				break;
			case "rpm":
				stringa = "il video";
				break;
			case "wmv":
				stringa = "il video";
				break;
			case "swf":
				stringa = "l'animazione";
				break;
		}
		document.write("<a href='#' accesskey='m' tabindex='100' onClick='avviamedium();return false;' onKeyPress='avviamedium();return false;' title=\"Ascolta "+stringa+"\"></a>");
		document.write("<a href='#' accesskey='f' tabindex='101' onClick='stopmedium();return false;' onKeyPress='stopmedium();return false;' title=\"Ferma "+stringa+"\"></a>");
	}
	switch (tipotutoriale[pagina]){
		case 2:
		
				stringa = "'verificatest("+tipotest+","+rispostaesatta+","+messaggio+");return false'";
				document.write("<a href='#' accesskey='v' tabindex='150' onClick="+stringa+" onKeyPress="+stringa+">");
				document.write("<img class='pulsanteverifica' onMouseOver='roll(this,\"verifica\")' onMouseOut='noroll(this,\"verifica\")' src='shell/img/pulsante_verifica.gif' alt='Verifica la risposta'></a>");
				
				stringa = "'mostrasoluzioni("+tipotest+","+rispostaesatta+");return false'";
				document.write("<a href='#' accesskey='l' tabindex='165' onClick="+stringa+" onKeyPress="+stringa+">");
				document.write("<img id='pulsantesoluzioni_"+pagina+"' class='pulsantesoluzioni' onMouseOver='roll(this,\"soluzioni\")' onMouseOut='noroll(this,\"soluzioni\")' src='shell/img/pulsante_soluzioni.gif' alt='Mostra le soluzioni'></a>");

			if (tipolo != "c"){ // diverso da solo test
				stringa = "'studio("+tutorialetest+");return false'";
				document.write("<a href='#' accesskey='s' tabindex='160' onClick="+stringa+" onKeyPress="+stringa+">");
				document.write("<img class='pulsantestudio' onMouseOver='roll(this,\"studio\")' onMouseOut='noroll(this,\"studio\")' src='shell/img/pulsante_studio.gif' alt='Studia'></a>");
					
				if (animazione){
					stringa = "'studioanimazione("+"\""+animazione+"\""+");return false'";
					document.write("<a href='#' accesskey='s' tabindex='160' onClick="+stringa+" onKeyPress="+stringa+">");
					document.write("<img class='pulsanteanimazione' onMouseOver='roll(this,\"animazione\")' onMouseOut='noroll(this,\"animazione\")' src='shell/img/pulsante_animazione.gif' alt='Rivedi'></a>");
				}
			}
			break;
		case 5:
			stringa = "'setcommento(unescape(document.getElementById(\"commento_"+pagina+"\""+").value));return false'";
			document.write("<a href='#' accesskey='n' tabindex='150' onClick="+stringa+" onKeyPress="+stringa+">");
			document.write("<img class='pulsanteinvia' onMouseOver='roll(this,\"invia\")' onMouseOut='noroll(this,\"invia\")' src='shell/img/pulsante_invia.gif' alt='Invia il commento'></a>");
	}
}

/* -- VISUALIZZAZIONE APPROFONDIMENTI -- */
function approfondimento(pagina){ // visualizza approfondimento di primo livello
	finemedium();
	document.getElementById("navigazionetutoriale").style.display="none";
	document.getElementById("pulsantehome").style.display="none";
	document.getElementById("pulsanteindice").style.display="none";
	document.getElementById(tutorialeattivo).style.display="none";
	if (document.getElementById(approfondimentoattivo))
		document.getElementById(approfondimentoattivo).style.display="none";
	document.getElementById(pagina).style.display="block";
	approfondimentoattivo = pagina;
	window.open("#"+approfondimentoattivo+"_a","_self");
	elementoattivo = 5;
}

function approfondimento2(pagina){ // visualizza approfondimento di secondo livello
	finemedium();		
	document.getElementById(approfondimentoattivo).style.display="none";
	document.getElementById(pagina).style.display="block";
	approfondimentoattivo2 = pagina;
	window.open("#"+approfondimentoattivo2+"_a","_self");
	elementoattivo = 6;
}

function ritorna(){ // ritorna da approfondimenti
	if (elementoattivo == 6){
		document.getElementById(approfondimentoattivo).style.display="block";
		document.getElementById(approfondimentoattivo2).style.display="none";
		window.open("#"+approfondimentoattivo+"_a","_self");
		elementoattivo = 5;
	}
	else{
		document.getElementById(approfondimentoattivo).style.display="none";
		document.getElementById(tutorialeattivo).style.display="block";
		if (puntatorestack != ""){
			document.getElementById("pulsantehistory").style.display="inline";
			document.getElementById("pulsanteindice").style.display="none";
			document.getElementById("pulsantehome").style.display="none";
		}
		else{
			document.getElementById("pulsantehistory").style.display="none";
			if (tipotutoriale[tutorialeattivo] != 0)
				document.getElementById("pulsantehome").style.display="inline";
			document.getElementById("pulsanteindice").style.display="inline";
		}
		document.getElementById("navigazionetutoriale").style.display="block";
		window.open("#"+tutorialeattivo+"_a","_self");
		iniziamedium();
		approfondimentoattivo = "";
		elementoattivo = 2;
	}
}

/* -- VISUALIZZAZIONE PAGINE DI SERVIZIO -- */
function vai(puntatorearrivo){ // accesso alle pagine che permettono di tornare al punto di partenza
	finemedium();		
	document.getElementById("pulsantecredits").style.display="none";
	document.getElementById("pulsantehelp").style.display="none";
	document.getElementById("pulsanteindice").style.display="none";
	document.getElementById("pulsanteuscita").style.display="none";
	switch (elementoattivo){
		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="none";
			document.getElementById("pulsantehome").style.display="none";
			document.getElementById(tutorialeattivo).style.display="none";
			break;
		case 5: // approfondimenti
			document.getElementById(approfondimentoattivo).style.display="none";
			break;
		case 6: // approfondimenti II livello
			document.getElementById(approfondimentoattivo2).style.display="none";
			break;
		}
	paginaservizioattiva = puntatorearrivo;
	document.getElementById(paginaservizioattiva).style.display="block";
	window.open("#"+paginaservizioattiva+"_a","_self");
	if (puntatorearrivo == "esci"){ // pagina di riepilogo
		var nodivisitati = contapaginevisitate();
		document.getElementById("riepilogopagine").value = nodivisitati;
		document.getElementById("riepilogopaginemax").value = paginetutoriali;
		document.getElementById("riepilogopunti").value = punteggio;
		document.getElementById("riepilogopuntimax").value = punteggiomassimo;
		document.getElementById("riepilogopuntitotalimin").value = punteggiominimo;
		if (init_status == "completed")
			document.getElementById("riepilogostatus").value = "stato completato in precedenza.";
		else if (init_status == "passed")
			document.getElementById("riepilogostatus").value = "stato superato in precedenza.";		
		else if (nodivisitati != paginetutoriali)
			document.getElementById("riepilogostatus").value = "da completare.";
		else if (punteggio >= punteggiominimo)
			document.getElementById("riepilogostatus").value = "superato.";
		else
			document.getElementById("riepilogostatus").value = "completato.";
	}
}

function ritornaindietro(){
	document.getElementById(paginaservizioattiva).style.display="none";
	document.getElementById("pulsantecredits").style.display="inline";
	document.getElementById("pulsantehelp").style.display="inline";
	document.getElementById("pulsanteuscita").style.display="inline";
	switch (elementoattivo){
		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="block";
			if (puntatorestack != ""){
				document.getElementById("pulsantehistory").style.display="inline";
				document.getElementById("pulsanteindice").style.display="none";
				document.getElementById("pulsantehome").style.display="none";
			}
			else{
				document.getElementById("pulsantehistory").style.display="none";
				if (tipotutoriale[tutorialeattivo] != 0)
					document.getElementById("pulsantehome").style.display="inline";
				document.getElementById("pulsanteindice").style.display="inline";
			}
			document.getElementById(tutorialeattivo).style.display="block";
			window.open("#"+tutorialeattivo+"_a","_self");
			iniziamedium();
			break;
		case 5: // approfondimenti
			document.getElementById(approfondimentoattivo).style.display="block";
			window.open("#"+approfondimentoattivo+"_a","_self");
			break;
		case 6: // approfondimenti II livello
			document.getElementById(approfondimentoattivo2).style.display="block";
			window.open("#"+approfondimentoattivo2+"_a","_self");
			break;
		}
}

function ritornatutoriale(blocco){
	document.getElementById(paginaservizioattiva).style.display="none";
	document.getElementById("navigazionetutoriale").style.display="block";
	document.getElementById("pulsantecredits").style.display="inline";
	document.getElementById("pulsantehelp").style.display="inline";
	document.getElementById("pulsanteuscita").style.display="inline";
	document.getElementById("pulsanteindice").style.display="inline";
	tutoriale(blocco);
}

/* -- MESSAGGI -- */
function inviamessaggio(testo,pagina,feedback){ // invia messaggi di sistema
	if (document.getElementById("messaggio_"+pagina))
		document.getElementById("messaggio_"+pagina).value = testo;
	if (testo != "" && feedback != "")
		feedbacksonoro(feedback);
}

/* -- INIZIALIZZAZIONE -- */
function inizializza(){ // nasconde tutte le pagine tranne la home e imposta i parametri iniziali
	var contatore = 0;
	impostacaratteri();
	document.getElementById("esci").style.display="none";
	document.getElementById("paginahelp").style.display="none";
	document.getElementById("paginacredits").style.display="none";
	document.getElementById("pulsantecontinua").style.display="none";
	document.getElementById("sommario").style.display="none";
	if (multimedia==1)
		document.getElementById("pulsantesuonoon").style.display="none";
	else
		document.getElementById("pulsantesuonoff").style.display="none";

	contatore = 1; // nasconde il tutoriale
	while (nometutoriale[contatore]){
		numerotentativi[nometutoriale[contatore]] = 0;
		document.getElementById(nometutoriale[contatore]).style.display="none";
		if (nodovisitato[nometutoriale[contatore]] > 0 && tutorialeprincipale[nometutoriale[contatore]] == null){
			document.getElementById("sommarioimm_"+nometutoriale[contatore]).src = "shell/img/visto.gif";
			document.getElementById("sommarioimm_"+nometutoriale[contatore]).alt = "Pagina visitata";
		}
		contatore++;
	}

	contatore = 1; // nasconde gli approfondimenti
	while (nomeapprofondimento[contatore]){
		document.getElementById(nomeapprofondimento[contatore]).style.display="none";
		contatore++;
	}
	document.getElementById("body").style.display="block";
	tutoriale("homepage");
}

function contapagine(){// conta le pagine tutoriali significative e il punteggio massimo
	var contatore = 1;
	var pagine = 0;
	while (nometutoriale[contatore]){
		if (tutorialeprincipale[nometutoriale[contatore]] == null){
			pagine++;
			if (tipotutoriale[nometutoriale[contatore]] == 2)
			punteggiomassimo = punteggiomassimo + puntitutoriale[nometutoriale[contatore]];
		}
		contatore++;
	}
	return pagine;
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
function roll(elemento,immagine){ // carica l'immagine di rollover
	elemento.src = "shell/img/pulsante_"+immagine+"_r.gif"
}

function noroll(elemento,immagine){ // ricarica l'immagine normale
	elemento.src = "shell/img/pulsante_"+immagine+".gif";
}

/* -- DIMENSIONE SCHERMATA -- */
function aumentazoom(){ // aumenta le dimensioni della schermata
	var nomefile = location.href.split("#");
	nomefile = nomefile[0].split("?");
	dimensionipagina = 2;
	window.open(nomefile[0]+"?"+dimensionicarattere+','+dimensionipagina+','+multimedia,"_self");
}

function diminuiscizoom(){ // diminuisce le dimensioni della schermata
	var nomefile = location.href.split("#");
	nomefile = nomefile[0].split("?");
	dimensionipagina = 1;
	window.open(nomefile[0]+"?"+dimensionicarattere+','+dimensionipagina+','+multimedia,"_self");
}

/* -- COMMENTI -- */
function contacaratteri(target,massimo){
	document.getElementById("contatore_"+tutorialeattivo).value = target.value.length;
	if (target.value.length > massimo){
		inviamessaggio(messaggiofeedback[12],tutorialeattivo,"messaggio");
	}
}

/* -- MULTIMEDIA -- */
function caricamedia(fileinput,pagina,posizione,immagine,testo){ // carica i file multimediali
	var tipo = fileinput.substr(fileinput.length-3,3);
	var path = fileinput.substr(0,fileinput.length-4);
	var nomi_path = path.split("/");
	var ultimo = nomi_path.length-1;
	var nomefile = nomi_path[ultimo];
	if (!pagina)
		pagina = "globale";
	else
		mediumblocco[pagina] = nomefile+"."+tipo;
	switch (tipo){
		case "mp3":
			if (tipobrowser == 1){
				document.write("<object class='audio' id='"+nomefile+"_"+pagina+"' classid='clsid:22d6f312-b0f6-11d0-94ab-0080c74c7e95'>");
			}
			else{
				document.write("<object class='audio' id='"+nomefile+"_"+pagina+"' data='"+fileinput+"'>");
			}
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='filename' value='"+fileinput+"'>");
			document.write("<param name='type' value='audio/x-mpeg'>");
			break;
		case "wmv":
			nodoplugin[pagina] = plugin_wm;
			if (tipobrowser == 1 || tipobrowser == 2){
				document.write("<object class='video"+posizione+"' id='"+nomefile+"_"+pagina+"' classid='clsid:6BF52A52-394A-11D3-B153-00C04F79FAA6' type='application/x-oleobject' codebase='http://activex.microsoft.com/activex/controls/mplayer/en/nsmp2inf.cab#Version=6,4,5,715'>");
			}
			else{
				document.write("<object class='video"+posizione+"' id='"+nomefile+"_"+pagina+"' data='"+fileinput+"'>");
				document.write("<param name='enabled' value='true'>");
			}
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='stretchToFit' value='true'>");
			document.write("<param name='type' value='video/x-ms-wmv'>");
			document.write("<param name='url' value='"+fileinput+"'>");
			document.write("<param name='volume' value='60'>");
			document.write("<img src='"+immagine+"' alt='"+testo+"'>");
			break;
		case "mov":
			nodoplugin[pagina] = plugin_qt;
			if (tipobrowser == 1){
				document.write("<object class='video"+posizione+"' id='"+nomefile+"_"+pagina+"' classid='clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B' codebase='http://www.apple.com/qtactivex/qtplugin.cab'>");
				document.write("<param name='controller' value='false'>");
			}
			else{
				document.write("<object class='video"+posizione+"' id='"+nomefile+"_"+pagina+"' data='"+fileinput+"'>");
				document.write("<param name='controller' value='true'>");
			}
			document.write("<param name='autoplay' value='false'>");
			document.write("<param name='enablejavascript' value='true'>");
			document.write("<param name='kioskmode' value='true'>");
			document.write("<param name='scale' value='aspect'>");
			document.write("<param name='src' value='"+fileinput+"'>");
			document.write("<param name='type' value='video/x-quicktime'>");
			document.write("<param name='volume' value='60'>");
			document.write("<img src='"+immagine+"' alt='"+testo+"'>");
			break;
		case "rpm":
			nodoplugin[pagina] = plugin_rp;
			if (tipobrowser == 1){
				document.write("<object class='video"+posizione+"' id='"+nomefile+"_"+pagina+"' classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'>");
			}
			else{
				document.write("<object class='video"+posizione+"' id='"+nomefile+"_"+pagina+"' data='"+fileinput+"'>");
			}
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='console' value='"+pagina+"'>");
			document.write("<param name='controls' value='All'>");
			document.write("<param name='maintainaspect' value='true'>");
			document.write("<param name='src' value='"+fileinput+"'>");
			document.write("<param name='type' value='video/x-pn-realaudio-plugin'>");
			document.write("<img src='"+immagine+"' alt='"+testo+"'>");
			break;
		case "swf":
			nodoplugin[pagina] = plugin_fl;
			document.write("<object class='animazione"+posizione+"' id='"+nomefile+"_"+pagina+"' type='application/x-shockwave-flash' data='"+fileinput+"'>");
			document.write("<param name='movie' value='"+fileinput+"'>");
			document.write("<param name='allowScriptAccess' value='always'>");
			document.write("<param name='quality' value='high'>");
			document.write("<param name='play' value='false'>");
			document.write("<param name='wmode' value='transparent'>");
			document.write("<img src='"+immagine+"' alt='"+testo+"'>");
			break;
		case "ggb":
			nodoplugin[pagina] = plugin_ja;
			if (tipobrowser == 1){
				document.write("<object class='animazione"+posizione+"' id='"+nomefile+"_"+pagina+"' code='geogebra.GeoGebraApplet'>");
			}
			else{
				document.write("<object class='animazione"+posizione+"' id='"+nomefile+"_"+pagina+"' classid='java:geogebra.GeoGebraApplet'>");
			}
			document.write("<param name='archive' value='shell/script/geogebra.jar'>");
			document.write("<param name='filename' value='"+fileinput+"'>");
			document.write("<param name='framePossible' value='false'>");
			document.write("<param name='type' value='application/java'>");
			break;
		}
	document.write("</object>");
}

function attivamedium(){ // attiva il suono/filmato/animazione tramite pulsante
	multimedia = 1;
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

function iniziamedium(){ // inizializa il suono/filmato/animazione
	mediumattivo = 0;
	if (mediumblocco[tutorialeattivo]){
		var medium = mediumblocco[tutorialeattivo].split(".");
		if (document.getElementById(medium[0]+"_"+tutorialeattivo)){
			mediumattivo = 1;
			if (multimedia==1)
				setTimeout("playmedium()",200);
		}
	}
}

function finemedium(){ // termina il suono/filmato/animazione
	stopmedium();
	mediumattivo = 0;
}

function avviamedium(){ // attiva il suono/filmato/animazione con ritardo
	setTimeout("playmedium()",2500);
}

function playmedium(){ // avvia il suono/filmato/animazione con modalità differenziate
	if (mediumattivo && mediumblocco[tutorialeattivo]){
		var medium = mediumblocco[tutorialeattivo].split(".");
		var nomemedium = medium[0]+"_"+tutorialeattivo;
		switch (medium[1]){
			case "mp3":
				setTimeout("try{document.getElementById('"+nomemedium+"').Play()}catch(e){}",100);
			case "swf":
				try{
					document.getElementById(nomemedium).Play();
				}
				catch(e){}
				break;
			case "mov":
				setTimeout("try{document.getElementById('"+nomemedium+"').Play()}catch(e){}",500);
				break;
			case "rpm":
				setTimeout("try{document.getElementById('"+nomemedium+"').DoPlay()}catch(e){}",500);
				break;
			case "wmv":
				setTimeout("try{document.getElementById('"+nomemedium+"').Controls.Play()}catch(e){}",500);
				break;
		}
	}
}

function stopmedium(){ // interrompe il suono/filmato/animazione con modalità differenziate
	if (mediumattivo && mediumblocco[tutorialeattivo]){
		var medium = mediumblocco[tutorialeattivo].split(".");
		var nomemedium = medium[0]+"_"+tutorialeattivo;
		switch (medium[1]){
			case "mp3":
				try{
					document.getElementById(nomemedium).Stop();
				}
				catch(e){}
				break;
			case "swf":
				try{
					document.getElementById(nomemedium).StopPlay();
				}
				catch(e){}
				break;
			case "mov":
				try{
					document.getElementById(nomemedium).Stop();
				}
				catch(e){}
				break;
			case "rpm":
				try{
					document.getElementById(nomemedium).DoStop();
				}
				catch(e){}
				break;
			case "wmv":
				try{
					document.getElementById(nomemedium).Controls.Stop();
				}
				catch(e){}
				break;
		}
	}
}

function feedbacksonoro(nomefeedback){ // invia un feedback sonoro
	if (document.getElementById(nomefeedback+"_globale")){
		setTimeout("try{document.getElementById('"+nomefeedback+"_globale').Play()}catch(e){}",100);
	}
}

/* -- RICERCA PLUG-IN -- */
function cercaplugin(){ // cerca i plug-in disponibili in browser diversi da IE
	if (navigator.plugins && navigator.plugins.length > 0){
		for(var i=0;i < navigator.plugins.length;i++){
			if(navigator.plugins[i].name.indexOf("Flash") >= 0 || navigator.plugins[i].description.indexOf("Flash") >= 0)
				plugin_fl = 1;
			if(navigator.plugins[i].name.indexOf("RealPlayer") >= 0 || navigator.plugins[i].description.indexOf("RealPlayer") >= 0)
				plugin_rp = 1;
			if(navigator.plugins[i].name.indexOf("QuickTime") >= 0 || navigator.plugins[i].description.indexOf("Quick Time") >= 0)
				plugin_qt = 1;
			if(navigator.plugins[i].name.indexOf("Windows Media") >= 0 || navigator.plugins[i].description.indexOf("Windows Media") >= 0)
				plugin_wm = 1;
			if(navigator.plugins[i].name.indexOf("Java") >= 0 || navigator.plugins[i].description.indexOf("Java") >= 0 && navigator.javaEnabled())
				plugin_ja = 1;
		}
	}
}

function comunicaplugin(){ // elenca i plug-in disponibili
	var comunicazione = "";
	if (plugin_qt + plugin_wm + plugin_rp == 0)
		comunicazione = "Per gestire audio e video è necessario installare Windows Media Player, Real Player, QuickTime.<br>";
	if (plugin_fl == 0)
		comunicazione = comunicazione + "Per le animazioni è necessario Flash.";
	if (plugin_ja == 0)
		comunicazione = comunicazione + " Per le applet è necessario Java.";
	if (comunicazione != "")
		document.write("<p class='comunicazioni'>"+comunicazione);
}

/* -- USCITA -- */
function chiudi(){ // predispone la chiusura della finestra del browser
	top.close();
}

function traccia(){ // memorizza i dati
	var stato = new String;
	var nodivisitati = contapaginevisitate();
	if (nodivisitati == paginetutoriali){
		if (punteggio >= punteggiominimo)
			stato = "passed";
		else
			stato = "completed";
		tutorialeattivo = "homepage";
	}
	else{
		stato = "incomplete";
	}
	var dati = dimensionicarattere + "," + dimensionipagina + "," + multimedia;
	for(var i=1;i < nometutoriale.length;i++){
			if (nodovisitato[nometutoriale[i]] > 0){
				if (nodovisitato[nometutoriale[i]] == 4 || nodovisitato[nometutoriale[i]] == 5)
					nodovisitato[nometutoriale[i]] = 2;
				dati = dati + ","+nodovisitato[nometutoriale[i]];
			}
			else
				dati = dati + ",0";
	}
	concludicorso(stato,tutorialeattivo,punteggio,punteggiomassimo,dati);
}

function contapaginevisitate(){ // conta le pagine visitate
	var contatore = 1;
	var pagine = 0;
	while (nometutoriale[contatore]){
		if (nodovisitato[nometutoriale[contatore]] > 0 && tutorialeprincipale[nometutoriale[contatore]] == null)
			pagine++;
		contatore++;
	}
	return pagine;
}

/* -- PULSANTI -- */
function pulsantiambiente(){
	document.write("<span id='pulsantezoom'>");
	if (dimensionipagina==2)
		document.write("<a href='#' onClick='diminuiscizoom();return false;' onKeypress='diminuiscizoom();return false;'><img class='pulsantezoom' onMouseOver=\"roll(this,'zoom')\" onMouseOut=\"noroll(this,'zoom')\"  src='shell/img/pulsante_zoom.gif' alt='Rimpicciolisci la finestra'><\/a>");
	else
		document.write("<a href='#' onClick='aumentazoom();return false;' onKeypress='aumentazoom();return false;'><img class='pulsantezoom' onMouseOver=\"roll(this,'zoom')\" onMouseOut=\"noroll(this,'zoom')\" src='shell/img/pulsante_zoom.gif' alt='Ingrandisci la finestra'><\/a>");
	document.write("<\/span>");
	document.write("<a href='#' onClick='incrementa();return false;' onKeypress='incrementa();return false;'><img class='pulsanteingrandisci' onMouseOver=\"roll(this,'ingrandisci')\" onMouseOut=\"noroll(this,'ingrandisci')\" src='shell/img/pulsante_ingrandisci.gif' alt='Ingrandisci i caratteri'><\/a>");
	document.write("<a href='#' onClick='decrementa();return false;' onKeypress='decrementa();return false;'><img class='pulsanterimpicciolisci' onMouseOver=\"roll(this,'rimpicciolisci')\" onMouseOut=\"noroll(this,'rimpicciolisci')\"  src='shell/img/pulsante_rimpicciolisci.gif' alt='Rimpicciolisci i caratteri'><\/a>");
	document.write("<a id='pulsantesuonoon' href='#' onClick='attivamedium();return false;' onKeypress='attivamedium();return false;'><img class='pulsantesuono' onMouseOver=\"roll(this,'suonoon')\" onMouseOut=\"noroll(this,'suonoon')\" src='shell/img/pulsante_suonoon.gif' alt=\"Attiva audio, video e animazioni\"><\/a>");
	document.write("<a id='pulsantesuonoff' href='#' onClick='disattivamedium();return false;' onKeypress='disattivamedium();return false;'><img class='pulsantesuono' onMouseOver=\"roll(this,'suonooff')\" onMouseOut=\"noroll(this,'suonooff')\" src='shell/img/pulsante_suonooff.gif' alt=\"Disattiva audio, video e animazioni\"><\/a>");
}

function pulsantinavigazione(){
	document.write("<a id='comandomultimedia' href='#' accesskey='d' tabindex='110' onClick='disattivamedium();return false;' onKeyPress='disattivamedium();return false;' title=\"Per usare il lettore di schermo, disattiva l'audio e gli altri contributi multimediali. Eventuali animazioni Flash saranno sostituite da pagine alternative\"><\/a>");
	document.write("<a id='pulsanteindietro' href='#' accesskey='o' tabindex='200' onClick='muovi(2);return false;' onKeypress='muovi(2);return false;'><img id='indietro' onMouseOver=\"roll(this,'indietro')\" onMouseOut=\"noroll(this,'indietro')\" src='shell/img/pulsante_indietro.gif' alt=\"Indietro\"><\/a>");
	document.write("<a id='pulsanteavanti' href='#' accesskey='a' tabindex='210' onClick='muovi(1);return false;' onKeypress='muovi(1);return false;'><img id='avanti' onMouseOver=\"roll(this,'avanti')\" onMouseOut=\"noroll(this,'avanti')\" src='shell/img/pulsante_avanti.gif' alt=\"Avanti\"><\/a>");
	document.write("<a id='pulsantehistory' href='#' accesskey='u' tabindex='900' onClick='indietrohistory();return false;' onKeypress='indietrohistory();return false;'><img id='history' onMouseOver=\"roll(this,'history')\" onMouseOut=\"noroll(this,'history')\" src='shell/img/pulsante_history.gif' alt=\"Torna all'ultima pagina di test o al riepilogo\"><\/a>");
	document.write("<span id='pulsantecontinua'><a href='#' accesskey='q' tabindex='115' onClick=\"tutoriale('"+init_bookmark+"');return false;\" onKeyPress=\"tutoriale('"+init_bookmark+"');return false;\"><img id='continua' onMouseOver=\"roll(this,'continua')\" onMouseOut=\"noroll(this,'continua')\" src='shell/img/pulsante_continua.gif' alt='Continua il corso al punto in cui è stato interrotto'></a><\/span>");
}

/* -- ISTRUZIONI INIZIALI -- */

/* -- Assegnazione variabili -- */
var approfondimentoattivo = "";
var approfondimentoattivo2 = "";
var dimensionicarattere = 1;
var dimensionipagina = 1;
var elementoattivo = 2; // 2=tutoriale 4=indice 5/6=approfondimento
var iniziocorso = 1;
var mediumattivo = 0;
var multimedia = 1;
var mediumblocco = new Array;
var numeroerrore = 0; // primo errore rilevato nella pagina;
var numerotentativi = new Array; // numero dei tentativi consecutivi di risposta a un test;
var modohistory = 0; //
var nodoplugin = new Array;
var nodovisitato = new Array;
var paginaservizioattiva = new String;
var puntatorestack = new String;
var punteggio = 0; //punteggio ottenuto
var punteggiomassimo = new Number; //punteggio massimo teorico
var tutorialeattivo = "homepage";
var paginetutoriali = contapagine();

/* -- Identificazione browser -- */
var tipobrowser = new Number;
var plugin_qt = 0; // Quick Time
var plugin_wm = 0; // Windows Media Player
var plugin_rp = 0; // Real Player
var plugin_fl = 0; // Flash
var plugin_ja = 0; // Java
switch (navigator.appName){
	case "Microsoft Internet Explorer":
		tipobrowser = 1;
		plugin_fl = 1;
		document.writeln("<script language='VBscript'>");
		document.writeln("on error resume next");
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
		document.writeln('plugin_ja = IsObject(CreateObject("JavaWebStart.isInstalled"))');
		document.writeln('plugin_ja = IsObject(CreateObject("JavaWebStart.isInstalled.1.4.2.0"))');
		document.writeln('plugin_ja = IsObject(CreateObject("JavaWebStart.isInstalled.1.5.0.0"))');
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
	document.write("<link rel='stylesheet' href='shell/img/tutoriale2.css' type='text/css'>");
	window.resizeTo(1024,755);
}
else{
	document.write("<link rel='stylesheet' href='shell/img/hidden.css' type='text/css'>");
	window.resizeTo(800,595);
}

/* -- Avvio -- */
//window.onload = inizializza;
window.onunload = traccia;

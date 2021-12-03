/* --- SHELL ACCESSIBILE 2007: FUNZIONI --- */

/* -- ACQUISIZIONE PARAMETRI -- */
function acquisisciparametri(){ // accetta i parametri da piattaforma e se presenti da querystring
	var contatore = 1;
	var nomepagina;
	var spostamento = 0;
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
		if (parametri[3] > 0)
			modofruizione = Number(parametri[3]);
		if (modocontinua){
			if (init_score > 0)
				punteggio = init_score;
			spostamento = 3;
			for(var i=1;i < successione[0].length;i++){
				nomepagina = successione[0][i];
				spostamento++
				if (parametri[spostamento] != null)
					nodi[nomepagina].visitato = Number(parametri[spostamento])
			}
			for(var i=1;i < successione[0].length;i++){
				nomepagina = successione[0][i];
				if (nodi[nomepagina].tipo == 2){
					contatore = 1;
					while (test[nomepagina+"_"+contatore]){
						spostamento++;
						if (parametri[spostamento] != null)
							test[nomepagina+"_"+contatore].risultato = parametri[spostamento];
						spostamento++;
						if (parametri[spostamento] != null)
							test[nomepagina+"_"+contatore].rispostaitem = parametri[spostamento];
						spostamento++;
						if (parametri[spostamento] != null)
							test[nomepagina+"_"+contatore].status = parametri[spostamento];
						contatore++;
					}
				}
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
		if (parametri[3] > 0)
			modofruizione = Number(parametri[3]);
	}
}

/* -- VISUALIZZAZIONE PAGINE TUTORIALI -- */
function muovi(direzione){ // accesso alle pagina da pulsanti
	switch (direzione){
		case 1: // avanti
			if (nodi[tutorialeattivo].tipo != 2)
				tutoriale(nodi[tutorialeattivo].successivo,0);
			else{
				switch (modofruizione){
					case 1:
						if (nodi[tutorialeattivo].visitato == 1 || nodi[tutorialeattivo].visitato == 3 || nodi[tutorialeattivo].visitato == 5 || ((nodi[tutorialeattivo].visitato == 2 || nodi[tutorialeattivo].visitato == 4) && bloccoavanzamento == 0))
							tutoriale(nodi[tutorialeattivo].successivo,0);
						else
							inviamessaggio(messaggiofeedback[13],tutorialeattivo,1); // mancata risposta esatta al test
					break;
					case 2:
						if ((nodi[tutorialeattivo].visitato == 2 || nodi[tutorialeattivo].visitato == 4) && bloccoavanzamento == 1)
							inviamessaggio(messaggiofeedback[13],tutorialeattivo,1); // mancata risposta esatta al test
						else
							tutoriale(nodi[tutorialeattivo].successivo,0);
					break;
					case 3:
						if (nodi[tutorialeattivo].visitato > 1)
							tutoriale(nodi[tutorialeattivo].successivo,0);
						else
							inviamessaggio(messaggiofeedback[14],tutorialeattivo,1); // mancata risposta al test
					break;
				}
			}
			break;
		case 2: // indietro
			if (nodi[nodi[tutorialeattivo].precedente].tutorialealternativo != "" && (multimedia == 0 || nodi[nodi[tutorialeattivo].precedente].plugin == 0)){
				var paginealternative = nodi[nodi[tutorialeattivo].precedente].tutorialealternativo.split("|");
				tutoriale(paginealternative[paginealternative.length-1],0);
			}
			else
				tutoriale(nodi[tutorialeattivo].precedente,0);
			break;
	}
}

function tutoriale(pagina,ritorno){ // visualizza la pagina prescelta e gestisce il menù
	var blocco = pagina;
	if (iniziocorso != 1)
		finemedium();
	document.getElementById(tutorialeattivo).style.visibility="hidden";
	if (nodi[blocco].tutorialealternativo != "" && (multimedia == 0 || nodi[blocco].plugin == 0)){ // pagina alternativa
		var paginealternative = nodi[blocco].tutorialealternativo.split("|");
		blocco = paginealternative[0];
	}
	if (ritorno == 1 && puntatorestack == ""){ // memorizza la pagina chiamante se in modalità protetta
		if (nodi[tutorialeattivo].tutorialeprincipale == "")
			puntatorestack = tutorialeattivo;
		else
			puntatorestack = nodi[tutorialeattivo].tutorialeprincipale;
	}
	if (puntatorestack != ""){ // modalità protetta
		document.getElementById("comandohome").style.visibility="hidden";
		document.getElementById("pulsantehistory").style.visibility="visible";
		document.getElementById("pulsanteindice").style.visibility="hidden";
		document.getElementById("pulsantehome").style.visibility="hidden";
	}
	else{
		document.getElementById("comandohome").style.visibility="visible";
		document.getElementById("pulsantehistory").style.visibility="hidden";
		document.getElementById("pulsantehome").style.visibility="visible";
		document.getElementById("pulsanteindice").style.visibility="visible";
	}
	if (multimedia == 1) // comando nascosto di disabilitazione
		document.getElementById("comandomultimedia").style.visibility="visible";
	else
		document.getElementById("comandomultimedia").style.visibility="hidden";
	if (modofruizione == 2) // comando nascosto di attivazione animazione del gioco
		document.getElementById("comandoanimazionegioco").style.visibility="hidden";
	if (nodi[blocco].tipo != 0 && nodi[blocco].successivo != "" && (puntatorestack == "" || nodi[nodi[blocco].successivo].tipo == nodi[blocco].tipo)) // pulsante "Avanti"
		document.getElementById("pulsanteavanti").style.visibility="visible";
	else
		document.getElementById("pulsanteavanti").style.visibility="hidden";
	if (nodi[blocco].precedente != "" && (puntatorestack == "" || nodi[nodi[blocco].precedente].tipo == nodi[blocco].tipo))// pulsante "Indietro"
		document.getElementById("pulsanteindietro").style.visibility="visible";
	else
		document.getElementById("pulsanteindietro").style.visibility="hidden";
	switch (nodi[blocco].tipo){// tipo tutoriale
		case 0: // home
			layouthome();
			document.getElementById("copertina").style.backgroundImage="url(../immagini/layout_0/copertina"+dimensionipagina+".jpg)"
			document.getElementById("pulsanteingrandisci").style.visibility="hidden";
			document.getElementById("pulsanterimpicciolisci").style.visibility="hidden";
			document.getElementById("pulsanteinizia").style.visibility="visible";
			document.getElementById("pulsantehome").style.visibility="hidden";
			document.getElementById("pulsantezoom").style.visibility="visible";
			document.getElementById("titolo_lo").style.visibility="hidden";
			document.getElementById("pulsantemodo1").style.visibility="visible";
			document.getElementById("pulsantemodo2").style.visibility="visible";
			document.getElementById("comandohome").style.visibility="hidden";
			document.getElementById("percorso_test").style.visibility="hidden";
			if (modofruizione == 2){
				document.getElementById("indicatore_modo_2").style.visibility="visible";
				document.getElementById("comandoanimazionegioco").style.visibility="visible";
				document.getElementById("animazionehome").style.visibility="visible";
			}
			else if (modofruizione == 1)
				document.getElementById("indicatore_modo_1").style.visibility="visible";
		break;
		case 1: // tutoriale
			document.getElementById("pulsanteingrandisci").style.visibility="visible";
			document.getElementById("pulsanterimpicciolisci").style.visibility="visible";
			document.getElementById("titolo_lo").style.visibility="visible";
			document.getElementById("percorso_test").style.visibility="hidden";
			document.getElementById("copertina").style.backgroundImage="url(../immagini/layout_"+modofruizione+"/copertina"+dimensionipagina+".jpg)";
			invianumero(blocco);
		break;
		case 2: // test
			document.getElementById("pulsanteingrandisci").style.visibility="visible";
			document.getElementById("pulsanterimpicciolisci").style.visibility="visible";
			document.getElementById("titolo_lo").style.visibility="visible";
			document.getElementById("percorso_test").style.visibility="visible";
			document.getElementById("copertina").style.backgroundImage="url(../immagini/layout_"+modofruizione+"/copertina_test"+dimensionipagina+".jpg)";
			impostamarcatore(blocco,2);
			switch (nodi[blocco].visitato){// tipo tutoriale
				case 2: // test effettuato non superato;
					inviamessaggio(messaggiofeedback[24],blocco);
					break;
				case 3: // test effettuato e superato;
					inviamessaggio(messaggiofeedback[25],blocco);
					break;
				case 4: // test effettuato e non superato: accesso al tutoriale
					inviamessaggio(messaggiofeedback[24],blocco);
					break;
				case 5: // test effettuato e soluzioni visualizzate
					inviamessaggio(messaggiofeedback[27],blocco);
					break;
				default:
					inviamessaggio("",blocco,1);
					break;
			}
			document.getElementById("punteggio_"+blocco).value = punteggio+" su "+punteggiomassimo;
			var baseanimazione = 4;
			var classepunteggio = calcolaclasse(punteggio);
			if (modofruizione == 2 && classepunteggio != classeattuale && (nodi[pagina].visitato == 0 || nodi[pagina].visitato == 1 || nodi[pagina].visitato == 2)){
				classeattuale = classepunteggio;
				avviaanimazionegioco(baseanimazione+classepunteggio);
				document.getElementById("comandoanimazionegioco").style.visibility="visible";
			}
		break;
		case 3: // introduzione
			document.getElementById("pulsanteingrandisci").style.visibility="visible";
			document.getElementById("pulsanterimpicciolisci").style.visibility="visible";
			document.getElementById("titolo_lo").style.visibility="visible";
			document.getElementById("percorso_test").style.visibility="hidden";
			document.getElementById("copertina").style.backgroundImage="url(../immagini/layout_"+modofruizione+"/copertina"+dimensionipagina+".jpg)"
			invianumero(blocco);
			inviamessaggio("",blocco,1);
		break;
		case 4: // riepilogo
			document.getElementById("pulsanteingrandisci").style.visibility="visible";
			document.getElementById("pulsanterimpicciolisci").style.visibility="visible";
			document.getElementById("titolo_lo").style.visibility="visible";
			document.getElementById("percorso_test").style.visibility="hidden";
			document.getElementById("copertina").style.backgroundImage="url(../immagini/layout_"+modofruizione+"/copertina_test"+dimensionipagina+".jpg)";
			document.getElementById("punteggio_"+blocco).value = punteggio+" su "+punteggiomassimo;
			var baseanimazione = 9;
			var basemessaggio = 6;
			var classepunteggio = calcolaclasse(punteggio);
			if (modofruizione == 2){
				avviaanimazionegioco(baseanimazione+classepunteggio);
				document.getElementById("comandoanimazionegioco").style.visibility="visible";
			}
			inviamessaggio(messaggiofeedback[basemessaggio+classepunteggio],blocco);
		break;
		case 5: // commenti
			document.getElementById("pulsanteingrandisci").style.visibility="visible";
			document.getElementById("pulsanterimpicciolisci").style.visibility="visible";
			document.getElementById("titolo_lo").style.visibility="visible";
			document.getElementById("percorso_test").style.visibility="hidden";
			document.getElementById("copertina").style.backgroundImage="url(../immagini/layout_"+modofruizione+"/copertina"+dimensionipagina+".jpg)"
			document.getElementById("numero_"+pagina).value="Commenti";
			inviamessaggio("",blocco,1);
		break;
		case 6: // filtro per domanda finale
			document.getElementById("pulsanteingrandisci").style.visibility="visible";
			document.getElementById("pulsanterimpicciolisci").style.visibility="visible";
			document.getElementById("titolo_lo").style.visibility="visible";
			document.getElementById("percorso_test").style.visibility="visible";
			document.getElementById("copertina").style.backgroundImage="url(../immagini/layout_"+modofruizione+"/copertina_filtro"+dimensionipagina+".jpg)";
			document.getElementById("punteggio_"+blocco).value = punteggio+" su "+punteggiomassimo;
			document.getElementById("filtro_punteggio").value = Math.floor(punteggio/punteggiomassimo*100);
			document.getElementById("filtro_punteggiomin").value = punteggiosoglia;
			document.getElementById("filtro_tutoriale").value = contapaginevisitate();
			document.getElementById("filtro_tutorialemin").value = tutorialesoglia;
			if (punteggio/punteggiomassimo*100 >= punteggiosoglia && contapaginevisitate() >= tutorialesoglia){
				document.getElementById("filtro_conclusioni").value = " puoi andare alla domanda finale.";
				document.getElementById("pulsanteavanti").style.visibility="visible";
				avviaanimazionegioco(30);
			}
			else{
				document.getElementById("filtro_conclusioni").value = " mi dispiace, ma non puoi andare alla domanda finale.";
				document.getElementById("pulsanteavanti").style.visibility="hidden";
				avviaanimazionegioco(31);
			}
			inviamessaggio("",blocco,1);
		break;
	}
	if (nodi[blocco].tutorialeprincipale != ""){// indice se pagina alternativa
		document.getElementById("sommarioimm_"+nodi[nodi[blocco].tutorialeprincipale].progressivo).src = "../immagini/visto.gif";
		document.getElementById("sommarioimm_"+nodi[nodi[blocco].tutorialeprincipale].progressivo).alt = "Pagina visitata";
		document.getElementById("sommarioriga_"+nodi[nodi[blocco].tutorialeprincipale].progressivo).style.backgroundColor="#efefef";
	}
	else{// indice se pagina principale
		document.getElementById("sommarioimm_"+nodi[blocco].progressivo).src = "../immagini/visto.gif";
		document.getElementById("sommarioimm_"+nodi[blocco].progressivo).alt = "Pagina visitata";
		document.getElementById("sommarioriga_"+nodi[blocco].progressivo).style.backgroundColor="#efefef";
	}
	if (nodi[tutorialeattivo].tutorialeprincipale != ""){
		if (nodi[tutorialeattivo].tutorialeprincipale != nodi[blocco].tutorialeprincipale)
			document.getElementById("sommarioriga_"+nodi[nodi[tutorialeattivo].tutorialeprincipale].progressivo).style.backgroundColor="#ffffff";
	}
	else{
		document.getElementById("sommarioriga_"+nodi[tutorialeattivo].progressivo).style.backgroundColor="#ffffff";
	}
	if (nodi[tutorialeattivo].tipo == 2){ // gestione percorso
		if (nodi[tutorialeattivo].visitato == 1)
			impostamarcatore(tutorialeattivo,1)
		else
			impostamarcatore(tutorialeattivo,3)
	}
	if (nodi[blocco].visitato == 0){// memorizzazione pagine visitate
		nodi[blocco].visitato = 1;
		if (nodi[blocco].tutorialeprincipale != "" && nodi[nodi[blocco].tutorialeprincipale].visitato < 1)
			nodi[nodi[blocco].tutorialeprincipale].visitato = 1;
	}
	tutorialeattivo = blocco;
	switch (iniziocorso){ // operazioni iniziali
		case 1: // prima volta
			iniziocorso = 2;
			window.open("#inizio_a","_self");
			if (init_suspendData != "" && modocontinua)
				document.getElementById("pulsantecontinua").style.visibility="visible";
			else
				document.getElementById("pulsantecontinua").style.visibility="hidden";
			if (modofruizione == 0){
				document.getElementById("pulsanteindice").style.visibility="hidden";
				document.getElementById("pulsanteinizia").style.visibility="hidden";
			}
			else
				impostafruizione(modofruizione);
		break;
		case 2: // seconda volta
			media["homepage_1"].attivazione = 0;
			iniziocorso = 3;
		case 3: // a regime
			window.open("#"+tutorialeattivo+"_a","_self");
		break;
	}
	document.getElementById(tutorialeattivo).style.visibility="visible";
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

function invianumero(pagina){ // scrive dinamicamente il numero di pagina
	document.getElementById("numero_"+pagina).value=nodi[pagina].numeropagina + " di " + paginetutoriali;
}

function impostamarcatore(pagina,stato){
	if (nodi[pagina].alternativo == 1)
		pagina = nodi[pagina].tutorialeprincipale;
	switch (stato){
		case 1:
			document.getElementById("marcatoretest_" + pagina).src = "../immagini/marcatore_blu.gif";
			document.getElementById("marcatoretest_" + pagina).alt = "\""+nodi[tutorialeattivo].titolo+": prova da effettuare.\""
		break;
		case 2:
			document.getElementById("marcatoretest_" + pagina).src = "../immagini/marcatore_giallo.gif";
			document.getElementById("marcatoretest_" + pagina).alt = "\""+nodi[pagina].titolo+": prova in corso.\""
		break;
		case 3:
			document.getElementById("marcatoretest_" + pagina).src = "../immagini/marcatore_rosso.gif";
			document.getElementById("marcatoretest_" + pagina).alt = "\""+nodi[tutorialeattivo].titolo+": prova effettuata.\""
		break;
	}
}

function calcolaclasse(punti){
	var classe = 5 - Math.ceil((punteggiomassimo - punti)/(punteggiomassimo / 5));
	if (classe == 5)
		classe = 4;
	return classe;
}

/* -- COSTRUZIONE ELEMENTI DI PAGINA -- */

function avvisoiniziale(){
	if (multimedia == 1)
		document.write("<a href='#' onClick='disattivamedium();return false;' onKeyPress='disattivamedium();return false;' title=\"Per usare il lettore di schermo, disattiva l'audio e gli altri contributi multimediali. Alcune animazioni Flash saranno sostituite da pagine alternative\"></a>");
}

function scriviindice(){
	var nomepagina;
	var indice = 0;
	for(var i=0;i < successione[0].length;i++){
		nomepagina = successione[0][i];
		if (nodi[nomepagina].alternativo == 0){
			document.write("<div id='sommarioriga_"+indice+"' class='rigabox'>");
			document.write("<a href='#' onClick='ritornatutoriale(\""+indice+"\");return false' onKeyPress='ritornatutoriale(\""+indice+"\");return false'>");
			document.write("<label class='nascosto' for='sommariotitolo_"+indice+"'>Vai alla pagina:</label>");
			document.write("<input id='sommariotitolo_"+indice+"' class='sommariotitolo' readonly size='50' maxlength='50' value=''>");
			document.write("</a>");
			document.write("<img id='sommarioimm_"+indice+"' class='sommarioimm' src='../immagini/vuoto.gif' alt=''>");
			indice++;
			document.write("</div>");
		}
	}
}

function scriviuscita(){
	document.write("<div id='bloccouscita'>");
	document.write("<div id='uscita_sx'></div>");
	document.write("<div id='uscita_dx'></div>");
	document.write("<div id='testouscita'>");
	document.write("<div class='labelriepilogo'><label for='riepilogopunti'>PUNTEGGIO</label></div>");
	document.write("<div class='datiriepilogo'>");
	document.write("<input class='datireadonly' id='riepilogopunti' readonly size='1'>");
	document.write("<label for='riepilogopuntimax'>su </label>");
	document.write("<input class='datireadonly' id='riepilogopuntimax' readonly size='1'><br>");
	document.write("<label for='riepilogopuntitotalimin'>punteggio minimo richiesto </label>");
	document.write("<input class='datireadonly' id='riepilogopuntitotalimin' readonly size='1'>");
	document.write("<br><br></div>");
	document.write("<div class='labelriepilogo'><label for='riepilogopagine'>PAGINE VISUALIZZATE</label></div>");
	document.write("<div class='datiriepilogo'>");
	document.write("<br><input class='datireadonly' id='riepilogopagine' readonly size='1'>");
	document.write("<label for='riepilogopaginemax'>su </label>");
	document.write("<input class='datireadonly' id='riepilogopaginemax' readonly size='1'>");
	document.write("<br><br></div>");
	document.write("<div class='labelriepilogo'><label for='riepilogostatus'>Il corso è </label>");
	document.write("<input class='datireadonly' id='riepilogostatus' readonly size='30'></div>");
	document.write("<div class='datiriepilogo'>Confermi l'uscita?<br>");
	document.write("<span class='nascosto'>Principali funzioni:</span>");
	document.write("<a href='#' tabindex='210' onClick=\"chiudi();return false;\" onKeyPress='chiudi();return false;'><img onMouseOver=\"roll(this,'si')\" onMouseOut=\"noroll(this,'si')\" src='../immagini/pulsante_si.gif' alt='Esci dal corso'></a>");
	document.write("<a href='#' accesskey='t' tabindex='200' onClick='ritornaindietro();return false;' onKeyPress='ritornaindietro();return false;'><img onMouseOver=\"roll(this,'no')\" onMouseOut=\"noroll(this,'no')\" src='../immagini/pulsante_no.gif' alt='Torna indietro'></a>");
	document.write("</div></div></div>");
}

function percorsotest(){
	var nomepagina;
	document.write("<div id='percorso_test'>");
	for(var i=0;i < successione[0].length;i++){
		nomepagina = successione[0][i];
		if (nodi[nomepagina].tipo == 2 && nodi[nomepagina].alternativo == 0){
			if (nodi[nomepagina].visitato > 1)
				document.write("<img id='marcatoretest_"+nomepagina+"' class='marcatore' src='../immagini/marcatore_rosso.gif' alt=\""+nodi[nomepagina].titolo+": prova effettuata.\">");
			else
				document.write("<img id='marcatoretest_"+nomepagina+"' class='marcatore' src='../immagini/marcatore_blu.gif' alt=\""+nodi[nomepagina].titolo+": prova da effettuare.\">");
		}
	}
	document.write("</div>")
}

function costruiscipagina(pagina, classetest, classerisposta, classedomanda){ // visualizza il numero della pagina e gli elementi tipici della pagina
	switch (nodi[pagina].tipo){
		case 0: // home
			comunicaplugin();
			document.write("<div id='marchio'></div>");
			document.write("<div id='indicatore_modo_1'><p class='nascosto'>Sei in modalità lezione.</div>");
			document.write("<div id='indicatore_modo_2'><p class='nascosto'>Sei in modalità gioco.</div>");
			document.write("<div id='animazionehome'></div>");
		break;
		case 1: // tutoriale
			scriviareanumero(pagina);
			scriviareamessaggio(pagina);
		break;
		case 2: // test
			scriviareamessaggio(pagina);
			scriviareapunteggio(pagina);
			visualizzatest(pagina, classetest, classerisposta, classedomanda)
		break;
		case 3: // introduzione
			scriviareanumero(pagina);
			scriviareamessaggio(pagina);
		break;
		case 4: // riepilogo
			scriviareamessaggio(pagina);
			scriviareapunteggio(pagina);
		break;
		case 5: // commenti
			scriviareanumero(pagina);
			scriviareamessaggio(pagina);
			document.write("<div class='testotest'><form action=''>");
			document.write("<p><label for='commento_"+pagina+"' class='domanda'>Invia i tuoi commenti al docente.</label>");
			document.write("<p><textarea class='areacommento' tabindex='1' id='commento_"+pagina+"' rows='15' cols='40' onKeyUp='contacaratteri(this,4000)' onFocus='contacaratteri(this,4000)'></textarea>");
			document.write("<p><label for='mailcommento_"+pagina+"' class='domanda'>E-mail del docente:</label><br>");
			document.write("<input class='areamail' tabindex='2' id='mailcommento_"+pagina+"'></input>");
			document.write("</form></div>");
			document.write("<div class='areacaratteri'>");
			document.write("<div class='intestazionecaratteri'><label for='contatore_"+pagina+"'>Caratteri</label></div>");
			document.write("<input class='testocaratteri' accesskey='r' tabindex='90' id='contatore_"+pagina+"' readonly size='4' maxlength='4'><br>");
			document.write("<span class='testocaratteri'>max 4000</span>");
			document.write("</div>");
		break;
		case 6: // filtro
			scriviareamessaggio(pagina);
			scriviareapunteggio(pagina);
			document.write("<div class='testofiltro'>");
			document.write("<strong>Adesso facciamo il punto della situazione prima della domanda finale</strong>:<ol>");
			document.write("<li><label for='filtro_punteggio'>Nei test effettuati fin qui, hai ottenuto il </label><input class='datireadonly' id='filtro_punteggio' readonly size='1'>% del punteggio totale. ");
			document.write("<label for='filtro_punteggiomin'>Per accedere all'ultima domanda, è necesssario raggiungere almeno il </label><input class='datireadonly' id='filtro_punteggiomin' readonly size='1'>%.<br><br>");
			document.write("<li><label for='filtro_tutoriale'>Hai studiato </label><input class='datireadonly' id='filtro_tutoriale' readonly size='1'> pagine di teoria; ");
			document.write("<label for='filtro_tutorialemin'>il minimo per proseguire è </label><input class='datireadonly' id='filtro_tutorialemin' readonly size='1'>.");
			document.write("</ol>");
			document.write("<label for='filtro_conclusioni'>Per questo </label><input class='datireadonly' id='filtro_conclusioni' readonly size='50'>");
			document.write("</div>");
		}
}

function scriviareanumero(pagina){ // inserisce l'oggetto numero pagina
	document.write("<p><label class='nascosto' for='numero_"+pagina+"'>Numero pagina:</label>");
	document.write("<input class='numeropagina' id='numero_"+pagina+"' readonly size='8' maxlength='8'>");
}

function scriviareamessaggio(pagina){ // inserisce l'oggetto messaggio
	document.write("<div class='areamessaggio'>");
	document.write("<p><label class='nascosto' for='messaggio_"+pagina+"'>Messaggio:</label>");
	document.write("<input class='messaggio' accesskey='g' tabindex='120' id='messaggio_"+pagina+"' readonly size='100' maxlength='100'>");
	document.write("</div>");
}

function scriviareapunteggio(pagina){ // inserisce l'oggetto punteggio
	document.write("<p><label class='nascosto' for='punteggio_"+pagina+"'>Punti</label>");
	document.write("<input class='punteggio' accesskey='u' tabindex='130' id='punteggio_"+pagina+"' readonly size='8' maxlength='10'>");
}

function comandi(pagina){ //inserisce i comandi nascosti per gestire audio, video e animazioni
	var stringa = new String;
	var contatore = 1;
	var identificatore = 1;
	document.write("<p>"); 
	while (media[pagina+"_"+contatore]){
		identificatore = pagina + "_" + contatore;
		switch (media[identificatore].classe){
			case 1:
				stringa = "l'audio.";
			break;
			case 2:
				stringa = "il video.";
			break;
			case 3:
				stringa = "l'animazione.";
			break;
		}
		stringa = stringa + " Elemento multimediale numero " + contatore + ".";
		document.write("<a href='#' accesskey='m' tabindex='100' onClick='playmedium("+identificatore+");return false;' onKeyPress='playmedium("+identificatore+");return false;' title=\"Ascolta "+stringa+"\"></a>");
		document.write("<a href='#' accesskey='f' tabindex='101' onClick='stopmedium("+identificatore+");return false;' onKeyPress='stopmedium("+identificatore+");return false;' title=\"Ferma "+stringa+"\"></a>");
		contatore++;
	}
	switch (nodi[pagina].tipo){
		case 1:
// pulsante Test
			if (nodi[pagina].testtutoriale != ""){
				document.write("<a href='#' id='pulsantetest_"+pagina+"' accesskey='v' tabindex='150' onClick='test();return false' onKeyPress='test();return false'>");
				document.write("<img class='pulsantetest' onMouseOver='roll(this,\"test\")' onMouseOut='noroll(this,\"test\")' src='../immagini/pulsante_test.gif' alt='Vai al test'></a>");
			}
		break;
		case 2:
// pulsante Verifica
			document.write("<a href='#' accesskey='v' tabindex='150' onClick='verificatest();return false' onKeyPress='verificatest();return false'>");
			document.write("<img class='pulsanteverifica' onMouseOver='roll(this,\"verifica\")' onMouseOut='noroll(this,\"verifica\")' src='../immagini/pulsante_verifica.gif' alt='Verifica la risposta'></a>");
// pulsante Studio
			if (modofruizione != "3"){ // diverso da solo test
				document.write("<a href='#' accesskey='s' tabindex='160' onClick='studio();return false' onKeyPress='studio();return false'>");
				document.write("<img class='pulsantestudio' onMouseOver='roll(this,\"studio\")' onMouseOut='noroll(this,\"studio\")' src='../immagini/pulsante_studio.gif' alt='Studia'></a>");
// pulsante Soluzioni
				document.write("<a href='#' accesskey='l' tabindex='165' onClick='mostrasoluzioni();return false' onKeyPress='mostrasoluzioni();return false'>");
				document.write("<img id='pulsantesoluzioni_"+pagina+"' class='pulsantesoluzioni' onMouseOver='roll(this,\"soluzioni\")' onMouseOut='noroll(this,\"soluzioni\")' src='../immagini/pulsante_soluzioni.gif' alt='Mostra le soluzioni'></a>");
			}
		break;
		case 5:
			stringa = "'setcommento(unescape(document.getElementById(\"commento_"+pagina+"\""+").value),unescape(document.getElementById(\"mailcommento_"+pagina+"\""+").value));return false'";
			document.write("<a href='#' accesskey='n' tabindex='150' onClick="+stringa+" onKeyPress="+stringa+">");
			document.write("<img class='pulsanteinvia' onMouseOver='roll(this,\"invia\")' onMouseOut='noroll(this,\"invia\")' src='../immagini/pulsante_invia.gif' alt='Invia il commento'></a>");
		break;
	}
	document.write("</p>");
}

function costruiscisuccessione(){
	var contatore1_tutoriale = 2;
	var contatore1_riepilogo = paginetutoriali + 1;
	var contatore1_commento = paginetutoriali + 2;
	var contatore1_test = paginetutoriali + 3;
	var contatore2_test = 2;
	var contatore2_filtro = paginetest + 1;
	var contatore2_riepilogo = paginetest + 3;
	var contatore2_commento = paginetest + 4;
	var contatore2_tutoriale = paginetest + 5;
	var appoggio1 = new Array;
	var appoggio2 = new Array;
	var contatore1 = 0;
	var contatore2 = 0;
	appoggio1[0] = "homepage";
	appoggio2[0] = "homepage";
	for(var i=1;i < successione[0].length;i++){
		nomepagina = successione[0][i];
		if (nodi[nomepagina].alternativo == 0){
			switch (nodi[nomepagina].tipo){
				case 1:
					appoggio1[contatore1_tutoriale] = nomepagina;
					contatore1_tutoriale++;
					appoggio2[contatore2_tutoriale] = nomepagina;
					contatore2_tutoriale++;
				break;
				case 2:
					appoggio1[contatore1_test] = nomepagina;
					contatore1_test++;
					appoggio2[contatore2_test] = nomepagina;
					contatore2_test++;
					if (contatore2_test == paginetest + 1){
						contatore2_test++;
					}
				break;
				case 3:
					appoggio1[1] = nomepagina;
					appoggio2[1] = nomepagina;
				break;
				case 4:
					appoggio1[contatore1_riepilogo] = nomepagina;
					appoggio2[contatore2_riepilogo] = nomepagina;
				break;
				case 5:
					appoggio1[contatore1_commento] = nomepagina;
					appoggio2[contatore2_commento] = nomepagina;
				break;
				case 6:
					appoggio2[contatore2_filtro] = nomepagina;
				break;
			}
		}
	}
	for(var i=0;i < Math.max(appoggio1.length,appoggio2.length);i++){
		if (appoggio1[i]){
			successione[1][contatore1] = appoggio1[i];
			contatore1++;
		}
		if (appoggio2[i]){
			successione[2][contatore2] = appoggio2[i];
			contatore2++;
		}
	}
}

/* -- VISUALIZZAZIONE APPROFONDIMENTI -- */
function approfondimento(pagina){ // visualizza approfondimento di primo livello
	if (elementoattivo == 2){
		finemedium();
		chiudielementi(1);
		document.getElementById(tutorialeattivo).style.visibility="hidden";
	}
	else if (document.getElementById(approfondimentoattivo))
		document.getElementById(approfondimentoattivo).style.visibility="hidden";
	document.getElementById(pagina).style.visibility="visible";
	approfondimentoattivo = pagina;
	window.open("#"+approfondimentoattivo+"_a","_self");
	elementoattivo = 5;
}

function approfondimento2(pagina){ // visualizza approfondimento di secondo livello
	document.getElementById(approfondimentoattivo).style.visibility="hidden";
	document.getElementById(pagina).style.visibility="visible";
	approfondimentoattivo2 = pagina;
	window.open("#"+approfondimentoattivo2+"_a","_self");
	elementoattivo = 6;
}

function ritorna(){ // ritorna da approfondimenti
	if (elementoattivo == 6){
		document.getElementById(approfondimentoattivo).style.visibility="visible";
		document.getElementById(approfondimentoattivo2).style.visibility="hidden";
		window.open("#"+approfondimentoattivo+"_a","_self");
		elementoattivo = 5;
	}
	else{
		document.getElementById(approfondimentoattivo).style.visibility="hidden";
		ripristinaelementi(1);
		document.getElementById(tutorialeattivo).style.visibility="visible";
		window.open("#"+tutorialeattivo+"_a","_self");
		iniziamedium();
		approfondimentoattivo = "";
		elementoattivo = 2;
	}
}

function chiudielementi(livello){
	stato_elementi[livello]["animazionegioco"]=document.getElementById("animazionegioco").style.visibility;
	stato_elementi[livello]["animazionehome"]=document.getElementById("animazionehome").style.visibility;
	stato_elementi[livello]["comandomultimedia"]=document.getElementById("comandomultimedia").style.visibility;
	stato_elementi[livello]["indicatore_modo_1"]=document.getElementById("indicatore_modo_1").style.visibility;
	stato_elementi[livello]["indicatore_modo_2"]=document.getElementById("indicatore_modo_2").style.visibility;
	stato_elementi[livello]["navigazionetutoriale"]=document.getElementById("navigazionetutoriale").style.visibility;
	stato_elementi[livello]["pulsanteavanti"]=document.getElementById("pulsanteavanti").style.visibility;
	stato_elementi[livello]["pulsantecontinua"]=document.getElementById("pulsantecontinua").style.visibility;
	stato_elementi[livello]["pulsantecredits"]=document.getElementById("pulsantecredits").style.visibility;
	stato_elementi[livello]["pulsantehelp"]=document.getElementById("pulsantehelp").style.visibility;
	stato_elementi[livello]["pulsantehistory"]=document.getElementById("pulsantehistory").style.visibility;
	stato_elementi[livello]["pulsantehome"]=document.getElementById("pulsantehome").style.visibility;
	stato_elementi[livello]["pulsanteindice"]=document.getElementById("pulsanteindice").style.visibility;
	stato_elementi[livello]["pulsanteindietro"]=document.getElementById("pulsanteindietro").style.visibility;
	stato_elementi[livello]["pulsanteingrandisci"]=document.getElementById("pulsanteingrandisci").style.visibility;
	stato_elementi[livello]["pulsanterimpicciolisci"]=document.getElementById("pulsanterimpicciolisci").style.visibility;
	stato_elementi[livello]["pulsanteinizia"]=document.getElementById("pulsanteinizia").style.visibility;
	stato_elementi[livello]["pulsantemodo1"]=document.getElementById("pulsantemodo1").style.visibility;
	stato_elementi[livello]["pulsantemodo2"]=document.getElementById("pulsantemodo2").style.visibility;
	stato_elementi[livello]["pulsantesuonoon"]=document.getElementById("pulsantesuonoon").style.visibility;
	stato_elementi[livello]["pulsantesuonooff"]=document.getElementById("pulsantesuonooff").style.visibility;
	stato_elementi[livello]["pulsanteuscita"]=document.getElementById("pulsanteuscita").style.visibility;
	stato_elementi[livello]["pulsantezoom"]=document.getElementById("pulsantezoom").style.visibility;
	document.getElementById("animazionegioco").style.visibility="hidden";
	document.getElementById("animazionehome").style.visibility="hidden";
	document.getElementById("comandomultimedia").style.visibility="hidden";
	document.getElementById("indicatore_modo_1").style.visibility="hidden";
	document.getElementById("indicatore_modo_2").style.visibility="hidden";
	document.getElementById("navigazionetutoriale").style.visibility="hidden";
	document.getElementById("pulsanteavanti").style.visibility="hidden";
	document.getElementById("pulsantecontinua").style.visibility="hidden";
	document.getElementById("pulsantehistory").style.visibility="hidden";
	document.getElementById("pulsantehome").style.visibility="hidden";
	document.getElementById("pulsanteindice").style.visibility="hidden";
	document.getElementById("pulsanteindietro").style.visibility="hidden";
	document.getElementById("pulsanteinizia").style.visibility="hidden";
	document.getElementById("pulsantemodo1").style.visibility="hidden";
	document.getElementById("pulsantemodo2").style.visibility="hidden";
	document.getElementById("pulsantesuonoon").style.visibility="hidden";
	document.getElementById("pulsantesuonooff").style.visibility="hidden";
	document.getElementById("pulsantezoom").style.visibility="hidden";
	document.getElementById("pulsanteingrandisci").style.visibility="visible";
	document.getElementById("pulsanterimpicciolisci").style.visibility="visible";
	if (livello == 2){
		document.getElementById("pulsanteuscita").style.visibility="hidden";
		document.getElementById("pulsantecredits").style.visibility="hidden";
		document.getElementById("pulsantehelp").style.visibility="hidden";
	}
}

function ripristinaelementi(livello){
	document.getElementById("animazionehome").style.visibility=stato_elementi[livello]["animazionehome"];
	document.getElementById("animazionegioco").style.visibility=stato_elementi[livello]["animazionegioco"];
	document.getElementById("comandomultimedia").style.visibility=stato_elementi[livello]["comandomultimedia"];
	document.getElementById("indicatore_modo_1").style.visibility=stato_elementi[livello]["indicatore_modo_1"];
	document.getElementById("indicatore_modo_2").style.visibility=stato_elementi[livello]["indicatore_modo_2"];
	document.getElementById("navigazionetutoriale").style.visibility=stato_elementi[livello]["navigazionetutoriale"];
	document.getElementById("pulsanteavanti").style.visibility=stato_elementi[livello]["pulsanteavanti"];
	document.getElementById("pulsantecontinua").style.visibility=stato_elementi[livello]["pulsantecontinua"];
	document.getElementById("pulsantecredits").style.visibility=stato_elementi[livello]["pulsantecredits"];
	document.getElementById("pulsantehelp").style.visibility=stato_elementi[livello]["pulsantehelp"];
	document.getElementById("pulsantehistory").style.visibility=stato_elementi[livello]["pulsantehistory"];
	document.getElementById("pulsantehome").style.visibility=stato_elementi[livello]["pulsantehome"];
	document.getElementById("pulsanteindice").style.visibility=stato_elementi[livello]["pulsanteindice"];
	document.getElementById("pulsanteindietro").style.visibility=stato_elementi[livello]["pulsanteindietro"];
	document.getElementById("pulsanteingrandisci").style.visibility=stato_elementi[livello]["pulsanteingrandisci"];
	document.getElementById("pulsanterimpicciolisci").style.visibility=stato_elementi[livello]["pulsanterimpicciolisci"];
	document.getElementById("pulsanteinizia").style.visibility=stato_elementi[livello]["pulsanteinizia"];
	document.getElementById("pulsantemodo1").style.visibility=stato_elementi[livello]["pulsantemodo1"];
	document.getElementById("pulsantemodo2").style.visibility=stato_elementi[livello]["pulsantemodo2"];
	document.getElementById("pulsantesuonoon").style.visibility=stato_elementi[livello]["pulsantesuonoon"];
	document.getElementById("pulsantesuonooff").style.visibility=stato_elementi[livello]["pulsantesuonooff"];
	document.getElementById("pulsanteuscita").style.visibility=stato_elementi[livello]["pulsanteuscita"];
	document.getElementById("pulsantezoom").style.visibility=stato_elementi[livello]["pulsantezoom"];
}

/* -- VISUALIZZAZIONE PAGINE DI SERVIZIO -- */
function vai(puntatorearrivo){ // accesso alle pagine che permettono di tornare esclusivamente al punto di partenza
	finemedium();
	chiudielementi(2);
	switch (elementoattivo){
		case 2: // tutoriale
			document.getElementById(tutorialeattivo).style.visibility="hidden";
		break;
		case 5: // approfondimenti
			document.getElementById(approfondimentoattivo).style.visibility="hidden";
		break;
		case 6: // approfondimenti II livello
			document.getElementById(approfondimentoattivo2).style.visibility="hidden";
		break;
	}
	if (puntatorearrivo == "esci"){ // pagina di riepilogo
		if (nodi[tutorialeattivo].tipo == 0){
			document.getElementById("pulsanteingrandisci").style.visibility="hidden";
			document.getElementById("pulsanterimpicciolisci").style.visibility="hidden";
			layoutuscitahome();
		}
		else
			layoutuscitastandard();
		var nodivisitati = contapaginevisitate();
		document.getElementById("riepilogopagine").value = nodivisitati;
		document.getElementById("riepilogopaginemax").value = paginetutoriali;
		document.getElementById("riepilogopunti").value = punteggio;
		document.getElementById("riepilogopuntimax").value = punteggiomassimo;
		document.getElementById("riepilogopuntitotalimin").value = Math.floor(punteggiominimo/100*punteggiomassimo);
		if (init_status == "completed")
			document.getElementById("riepilogostatus").value = "stato completato in precedenza.";
		else if (init_status == "passed")
			document.getElementById("riepilogostatus").value = "stato superato in precedenza.";
		else if (nodivisitati != paginetutoriali)
			document.getElementById("riepilogostatus").value = "da completare.";
		else if (punteggio >= Math.floor(punteggiominimo/100*punteggiomassimo))
			document.getElementById("riepilogostatus").value = "stato superato.";
		else
			document.getElementById("riepilogostatus").value = "stato completato.";
	}
	paginaservizioattiva = puntatorearrivo;
	document.getElementById(paginaservizioattiva).style.visibility="visible";
	window.open("#"+paginaservizioattiva+"_a","_self");
}

function ritornaindietro(){
	document.getElementById(paginaservizioattiva).style.visibility="hidden";
	ripristinaelementi(2);
	switch (elementoattivo){
		case 2: // tutoriale
			document.getElementById(tutorialeattivo).style.visibility="visible";
			window.open("#"+tutorialeattivo+"_a","_self");
			iniziamedium();
		break;
		case 5: // approfondimenti
			document.getElementById(approfondimentoattivo).style.visibility="visible";
			window.open("#"+approfondimentoattivo+"_a","_self");
		break;
		case 6: // approfondimenti II livello
			document.getElementById(approfondimentoattivo2).style.visibility="visible";
			window.open("#"+approfondimentoattivo2+"_a","_self");
		break;
	}
}

function ritornatutoriale(numero){ // va alla pagina tutoriale dall'indice
	var nomepagina = successione[modofruizione][numero]
	if (!nomepagina)
		return;
	document.getElementById(paginaservizioattiva).style.visibility="hidden";
	ripristinaelementi(2);
	if (nodi[tutorialeattivo].tipo == 0){
		document.getElementById("pulsanteinizia").style.visibility="hidden";
		document.getElementById("pulsantecontinua").style.visibility="hidden";
		document.getElementById("pulsantemodo1").style.visibility="hidden";
		document.getElementById("pulsantemodo2").style.visibility="hidden";
		document.getElementById("pulsantezoom").style.visibility="hidden";
		modificalayout();
	}
	if (nodi[nomepagina].tipo != 0){
		document.getElementById("animazionehome").style.visibility="hidden";
		document.getElementById("indicatore_modo_1").style.visibility="hidden";
		document.getElementById("indicatore_modo_2").style.visibility="hidden";
	}
	tutoriale(nomepagina);
}

/* -- MESSAGGI -- */
function inviamessaggio(testo,pagina,feedback){ // invia messaggi di sistema
	if (document.getElementById("messaggio_"+pagina))
		document.getElementById("messaggio_"+pagina).value = testo;
	if (testo != "" && feedback && document.getElementById("globale_"+feedback))
		playmedium("globale_"+feedback)
}

/* -- INIZIALIZZAZIONE -- */
function inizializza(){ // nasconde tutte le pagine tranne la home e imposta i parametri iniziali
	var contatore = 1;
	var nomepagina;
	impostacaratteri();
	document.getElementById("esci").style.visibility="hidden";
	document.getElementById("paginahelp").style.visibility="hidden";
	document.getElementById("paginacredits").style.visibility="hidden";
	document.getElementById("pulsantecontinua").style.visibility="hidden";
	document.getElementById("pulsanteinizia").style.visibility="hidden";
	document.getElementById("sommario").style.visibility="hidden";
	if (multimedia==1) // imposta i pulsanti multimedia
		document.getElementById("pulsantesuonoon").style.visibility="hidden";
	else
		document.getElementById("pulsantesuonooff").style.visibility="hidden";
	stato_elementi[0]["pulsantesuonoon"]=document.getElementById("pulsantesuonoon").style.visibility;
	stato_elementi[0]["pulsantesuonooff"]=document.getElementById("pulsantesuonooff").style.visibility;
	for(var i=0;i < successione[0].length;i++){ // nasconde il tutoriale e inizializza l'array numerotentativi;
		nomepagina = successione[0][i];
		nodi[nomepagina].tentativi = 0;
		document.getElementById(nomepagina).style.visibility="hidden";
		if (nodi[nomepagina].alternativo == 0){
			if (nodi[nomepagina].tipo == 1 || nodi[nomepagina].tipo == 3) // conta le pagine tutoriali
				paginetutoriali++;
			else if (nodi[nomepagina].tipo == 2) // conta le pagine di test e il puntaggio massimo
				paginetest++;
				punteggiomassimo = punteggiomassimo + nodi[nomepagina].punti;
		}
		contatore = 1;
		nodi[nomepagina].plugin = 1; // verifica la presenza di plugin
		while (media[nomepagina+"_"+contatore]){
			if (media[nomepagina+"_"+contatore].plugin == 0)
				nodi[nomepagina].plugin = 0;
			contatore++;
		}
	}
	contatore = 1;
	while (nomeapprofondimento[contatore]){ // nasconde gli approfondimenti
		document.getElementById(nomeapprofondimento[contatore]).style.visibility="hidden";
		contatore++;
	}
	tutorialesoglia = Math.floor(tutorialesoglia/100*paginetutoriali);
	document.getElementById("body").style.visibility="visible";
	if (autosuccessione == 1)
		costruiscisuccessione();
	tutoriale("homepage");
}

function predisponipagine(){
	for(var i=0;i < successione[0].length;i++){
		var nomepagina = successione[0][i];
		if (nodi[nomepagina].tutorialealternativo != ""){
			var paginealternative = nodi[nomepagina].tutorialealternativo.split("|");
			for(var i1=0;i1 < paginealternative.length;i1++){
				nodi[paginealternative[i1]].tutorialeprincipale = nomepagina;
				nodi[paginealternative[i1]].tipo = nodi[nomepagina].tipo;
				nodi[paginealternative[i1]].punti = nodi[nomepagina].punti;
				nodi[paginealternative[i1]].testtutoriale = nodi[nomepagina].testtutoriale;
			}
		}
	}
}

function impostafruizione(modo){ // imposta la successione delle pagine in base al modo di fruizione
	var nomepagina = "";
	var indice = 0;
	var numerotutoriale = 0;
	var numerotest = 0;
	var spostamento = 0;
	modofruizione = modo;
	for(var i=0;i < successione[modo].length;i++){
		nomepagina = successione[modo][i];
		document.getElementById("sommariotitolo_"+indice).value = nodi[nomepagina].titolo;
		nodi[nomepagina].progressivo = indice;
		nodi[nomepagina].precedente = "";
		nodi[nomepagina].successivo = "";
		switch (nodi[nomepagina].tipo){
			case 1:
				numerotutoriale++;
				nodi[nomepagina].numeropagina = numerotutoriale;
				if (modofruizione == 2){
					document.getElementById("sommariotitolo_"+indice).style.fontWeight="normal";
					document.getElementById("sommariotitolo_"+indice).style.paddingLeft="20px";
				}
				else{
					document.getElementById("sommariotitolo_"+indice).style.fontWeight="bold";
					document.getElementById("sommariotitolo_"+indice).style.paddingLeft="0px";
				}
			break;
			case 2:
				numerotest++;
				nodi[nomepagina].numeropagina = numerotest;
				document.getElementById("marcatoretest_"+nomepagina).style.left=spostamento+"px";
				spostamento = spostamento + 16;
				if (modofruizione == 1){
					document.getElementById("sommariotitolo_"+indice).style.fontWeight="normal";
					document.getElementById("sommariotitolo_"+indice).style.paddingLeft="20px";
				}
				else{
					document.getElementById("sommariotitolo_"+indice).style.fontWeight="bold";
					document.getElementById("sommariotitolo_"+indice).style.paddingLeft="0px";
				}
			break;
			case 3:
				numerotutoriale++;
				nodi[nomepagina].numeropagina = numerotutoriale;
				document.getElementById("sommariotitolo_"+indice).style.fontWeight="bold";
				document.getElementById("sommariotitolo_"+indice).style.paddingLeft="0px";
			break;
			default:
				document.getElementById("sommariotitolo_"+indice).style.fontWeight="bold";
				document.getElementById("sommariotitolo_"+indice).style.paddingLeft="0px";
			break;
		}
		if (nodi[nomepagina].visitato > 0 ){
			document.getElementById("sommarioimm_"+indice).src = "../immagini/visto.gif";
			document.getElementById("sommarioimm_"+indice).alt = "Pagina visitata";
		}
		else{
			document.getElementById("sommarioimm_"+indice).src = "../immagini/vuoto.gif";
			document.getElementById("sommarioimm_"+indice).alt = "";
		}
		indice++;
	}
	if (indice < successione[0].length){
		for(var i=indice;i < successione[0].length;i++){
			if (document.getElementById("sommariotitolo_"+i)){
				document.getElementById("sommariotitolo_"+i).value = "";
				document.getElementById("sommarioimm_"+i).src = "../immagini/vuoto.gif";
				document.getElementById("sommarioimm_"+i).alt = "";
			}
		}
	}
	document.getElementById("pulsanteindice").style.visibility="visible";
	document.getElementById("pulsanteinizia").style.visibility="visible";
	switch (modofruizione){
		case 1:
			document.getElementById("animazionegioco").style.visibility="hidden";
			document.getElementById("animazionehome").style.visibility="hidden";
			document.getElementById("indicatore_modo_1").style.visibility="visible";
			document.getElementById("indicatore_modo_2").style.visibility="hidden";
			document.getElementById("comandoanimazionegioco").style.visibility="hidden";
			for(var i=0;i < successione[modo].length;i++){ // imposta pagine precedenti e successive
				nomepagina = successione[modo][i];
				switch (nodi[nomepagina].tipo){
					case 2:
					break;
					case 1:
						if (nodi[nomepagina].testtutoriale != ""){
							var paginetesttutoriale = nodi[nomepagina].testtutoriale.split("|");
							for(var i1=0;i1 < paginetesttutoriale.length;i1++){
								if (i1 == 0)
									nodi[paginetesttutoriale[i1]].precedente = "";
								else
									nodi[paginetesttutoriale[i1]].precedente = paginetesttutoriale[i1-1];
								if (i1 == paginetesttutoriale.length-1)
									nodi[paginetesttutoriale[i1]].successivo = "";
								else
									nodi[paginetesttutoriale[i1]].successivo = paginetesttutoriale[i1+1];
								if (nodi[paginetesttutoriale[i1]].tutorialealternativo != "")
									impostapaginealternative(paginetesttutoriale[i1]);
							}
						}
					default:
						if (i > 0)
							nodi[nomepagina].precedente = successione[modo][i-1];
						if (i < successione[modo].length-1 && nodi[nomepagina].ultimapagina == 0)
								nodi[nomepagina].successivo = successione[modo][i+1];
						if (nodi[nomepagina].tutorialealternativo != "")
							impostapaginealternative(nomepagina);
					break;
				}
			}
		break;
		case 2:
			document.getElementById("animazionegioco").style.visibility="visible";
			document.getElementById("animazionehome").style.visibility="visible";
			document.getElementById("indicatore_modo_1").style.visibility="hidden";
			document.getElementById("indicatore_modo_2").style.visibility="visible";
			document.getElementById("comandoanimazionegioco").style.visibility="visible";
			for(var i=0;i < successione[modo].length;i++){
				nomepagina = successione[modo][i];
					if (i > 0)
						nodi[nomepagina].precedente = successione[modo][i-1];
					if (i < successione[modo].length-1 && nodi[nomepagina].ultimapagina == 0)
						nodi[nomepagina].successivo = successione[modo][i+1];
					if (nodi[nomepagina].tutorialealternativo != "")
						impostapaginealternative(nomepagina);
			}
		break;
	}
}

function impostapaginealternative(nomepagina){
	var paginealternative = nodi[nomepagina].tutorialealternativo.split("|");
	for(var i1=0;i1 < paginealternative.length;i1++){
		nodi[paginealternative[i1]].numeropagina = nodi[nomepagina].numeropagina;
		if (i1 == 0)
			nodi[paginealternative[i1]].precedente = nodi[nomepagina].precedente;
		else
			nodi[paginealternative[i1]].precedente = paginealternative[i1-1];
		if (i1 == paginealternative.length-1)
			nodi[paginealternative[i1]].successivo = nodi[nomepagina].successivo;
		else
			nodi[paginealternative[i1]].successivo = paginealternative[i1+1];
	}
}

function iniziafruizione(){ // inizia un lo
	modificalayout();
	document.getElementById("pulsantemodo1").style.visibility="hidden";
	document.getElementById("indicatore_modo_1").style.visibility="hidden";
	document.getElementById("pulsantemodo2").style.visibility="hidden";
	document.getElementById("indicatore_modo_2").style.visibility="hidden";
	document.getElementById("animazionehome").style.visibility="hidden";
	document.getElementById("pulsantecontinua").style.visibility="hidden";
	document.getElementById("pulsanteinizia").style.visibility="hidden";
	document.getElementById("pulsantezoom").style.visibility="hidden";
	muovi(1);
}

function continuafruizione(){ // prosegue un lo dal punto in cui è stato interrotto
	modificalayout();
	document.getElementById("pulsantemodo1").style.visibility="hidden";
	document.getElementById("indicatore_modo_1").style.visibility="hidden";
	document.getElementById("pulsantemodo2").style.visibility="hidden";
	document.getElementById("indicatore_modo_2").style.visibility="hidden";
	document.getElementById("animazionehome").style.visibility="hidden";
	document.getElementById("pulsantecontinua").style.visibility="hidden";
	document.getElementById("pulsanteinizia").style.visibility="hidden";
	document.getElementById("pulsantezoom").style.visibility="hidden";
	tutoriale(init_bookmark);
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
	elemento.src = "../immagini/pulsante_"+immagine+"_r.gif"
}

function noroll(elemento,immagine){ // ricarica l'immagine normale
	elemento.src = "../immagini/pulsante_"+immagine+".gif";
}

/* -- DIMENSIONE SCHERMATA -- */
function cambiazoom(){ // modifica le dimensioni della schermata
	var nomefile = location.href.split("#");
	nomefile = nomefile[0].split("?");
	if (dimensionipagina == 1)
		dimensionipagina = 2;
	else
		dimensionipagina = 1;
	window.open(nomefile[0]+"?"+dimensionicarattere+','+dimensionipagina+','+multimedia+','+modofruizione,"_self");
}

/* -- RITARDO -- */
function ritardo(millisecondi){
	var tempoiniziale = new Date().getTime();
	var tempofinale = new Number;
	while (tempofinale < tempoiniziale + millisecondi){
		tempofinale = new Date().getTime();
	}
}

/* -- COMMENTI -- */
function contacaratteri(target,massimo){
	document.getElementById("contatore_"+tutorialeattivo).value = target.value.length;
	if (target.value.length > massimo){
		inviamessaggio(messaggiofeedback[12],tutorialeattivo,1);
	}
}

/* -- MULTIMEDIA -- */
function caricamedia(fileinput,pagina,progressivo,attivazione,stile,immagine,testo){ // carica i file multimediali
	var identificatore = "";
	var nomi_path = fileinput.split("/");
	var nomefile = nomi_path[nomi_path.length-1].split(".");
	if (progressivo)
		identificatore = pagina+"_"+progressivo;
	else
		identificatore = pagina+"_"+trovaidentificatore(pagina);
	media[identificatore] = new medium(nomefile[1],nomefile[0],attivazione);
	document.write("<p class='paginaoggetto'>");
	switch (media[identificatore].tipomedium){
		case "mp3":
			media[identificatore].classe = 1;
			media[identificatore].plugin = plugin_fl;
			break;
		case "wmv":
			media[identificatore].classe = 2;
			media[identificatore].plugin = plugin_wm;
			if (tipobrowser == 1 || tipobrowser == 2)
				document.write("<object class='"+stile+"' id='"+identificatore+"' classid='clsid:6BF52A52-394A-11D3-B153-00C04F79FAA6' type='application/x-oleobject' codebase='http://activex.microsoft.com/activex/controls/mplayer/en/nsmp2inf.cab#Version=6,4,5,715'>");
			else{
				document.write("<object class='"+stile+"' id='"+identificatore+"' data='"+fileinput+"'>");
				document.write("<param name='enabled' value='true'>");
			}
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='stretchToFit' value='true'>");
			document.write("<param name='type' value='video/x-ms-wmv'>");
			document.write("<param name='url' value='"+fileinput+"'>");
			document.write("<param name='volume' value='60'>");
			document.write("<img src='"+immagine+"' alt=\""+testo+"\">");
			break;
		case "mov":
			media[identificatore].classe = 2;
			media[identificatore].plugin = plugin_qt;
			if (tipobrowser == 1){
				document.write("<object class='"+stile+"' id='"+identificatore+"' classid='clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B' codebase='http://www.apple.com/qtactivex/qtplugin.cab'>");
				document.write("<param name='controller' value='false'>");
			}
			else{
				document.write("<object class='"+stile+"' id='"+identificatore+"' data='"+fileinput+"'>");
				document.write("<param name='controller' value='true'>");
			}
			document.write("<param name='autoplay' value='false'>");
			document.write("<param name='enablejavascript' value='true'>");
			document.write("<param name='kioskmode' value='true'>");
			document.write("<param name='scale' value='aspect'>");
			document.write("<param name='src' value='"+fileinput+"'>");
			document.write("<param name='type' value='video/x-quicktime'>");
			document.write("<param name='volume' value='60'>");
			document.write("<img src='"+immagine+"' alt=\""+testo+"\">");
			break;
		case "rm":
		case "ram":
		case "rpm":
			media[identificatore].classe = 2;
			media[identificatore].plugin = plugin_rp;
			if (tipobrowser == 1)
				document.write("<object class='"+stile+"' id='"+identificatore+"' classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'>");
			else
				document.write("<object class='"+stile+"' id='"+identificatore+"' data='"+fileinput+"'>");
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='backgroundcolor' value='white'>");
			document.write("<param name='console' value='"+pagina+"'>");
			document.write("<param name='controls' value='ImageWindow'>");
			document.write("<param name='maintainaspect' value='true'>");
			document.write("<param name='src' value='"+fileinput+"'>");
			document.write("<param name='type' value='video/x-pn-realaudio-plugin'>");
			document.write("<img src='"+immagine+"' alt=\""+testo+"\">");
			break;
		case "swf":
			media[identificatore].classe = 3;
			media[identificatore].plugin = plugin_fl;
			if (tipobrowser == 1)
				document.write("<object class='"+stile+"' id='"+identificatore+"' classid='clsid:d27cdb6e-ae6d-11cf-96b8-444553540000'>");
			else
				document.write("<object class='"+stile+"' id='"+identificatore+"' type='application/x-shockwave-flash' data='"+fileinput+"'>");
			document.write("<param name='movie' value='"+fileinput+"'>");
			document.write("<param name='allowScriptAccess' value='always'>");
			document.write("<param name='quality' value='high'>");
			document.write("<param name='play' value='false'>");
			document.write("<img src='"+immagine+"' alt=\""+testo+"\">");
			break;
		case "flv":
			media[identificatore].classe = 2;
			media[identificatore].plugin = plugin_fl;
			if (tipobrowser == 1)
				document.write("<object class='"+stile+"' id='"+identificatore+"' classid='clsid:d27cdb6e-ae6d-11cf-96b8-444553540000'>");
			else
				document.write("<object class='"+stile+"' id='"+identificatore+"' type='application/x-shockwave-flash' data='videoplayer.swf'>");
			document.write("<param name='movie' value='videoplayer.swf'>");
			document.write("<param name='allowScriptAccess' value='always'>");
			document.write("<param name='quality' value='high'>");
			document.write("<param name='FlashVars' value='nomevideo="+fileinput+"'>");
			document.write("<param name='play' value='false'>");
			document.write("<img src='"+immagine+"' alt=\""+testo+"\">");
			break;
		case "dcr":
			media[identificatore].classe = 3;
			media[identificatore].plugin = plugin_sw;
			if (tipobrowser == 1){
				document.write("<object class='"+stile+"' id='"+identificatore+"' classid='clsid:166B1BCA-3F9C-11CF-8075-444553540000' codebase='http://download.macromedia.com/director/cabs/sw.cab'>");
			}
			else{
				document.write("<object class='"+stile+"' id='"+identificatore+"' data='"+fileinput+"'>");
			}
			document.write("<param name='play' value='false'>");
			document.write("<param name='src' value='"+fileinput+"'>");
			document.write("<param name='type' value='application/x-director'>");
			break;
		case "ggb":
			media[identificatore].classe = 3;
			media[identificatore].plugin = plugin_ja;
			if (tipobrowser == 1)
				document.write("<object class='"+stile+"' id='"+identificatore+"' code='geogebra.GeoGebraApplet'>");
			else
				document.write("<object class='"+stile+"' id='"+identificatore+"' classid='java:geogebra.GeoGebraApplet'>");
			document.write("<param name='archive' value='../script/geogebra.jar'>");
			document.write("<param name='filename' value='"+fileinput+"'>");
			document.write("<param name='framePossible' value='false'>");
			document.write("<param name='type' value='application/java'>");
			break;
		}
	document.write("</object>");
}

function caricaanimazionegioco(){
	document.write("<p>");
	if (tipobrowser == 1)
		document.write("<object id='animazionegioco' classid='clsid:d27cdb6e-ae6d-11cf-96b8-444553540000'>");
	else
		document.write("<object id='animazionegioco' type='application/x-shockwave-flash' data='animazionegioco.swf'>");
	document.write("<param name='movie' value='animazionegioco.swf'>");
	document.write("<param name='allowScriptAccess' value='always'>");
	document.write("<param name='quality' value='high'>");
	document.write("<param name='play' value='true'>");
	document.write("</object>");
}

function caricaplayer(){
	document.write("<p>");
	if (tipobrowser == 1)
		document.write("<object id='player' classid='clsid:d27cdb6e-ae6d-11cf-96b8-444553540000'>");
	else
		document.write("<object id='player' type='application/x-shockwave-flash' data='soundplayer.swf'>");
	document.write("<param name='movie' value='soundplayer.swf'>");
	document.write("<param name='allowScriptAccess' value='always'>");
	document.write("<param name='quality' value='high'>");
	document.write("<param name='play' value='true'>");
	document.write("</object>");
}

function avviaanimazionegioco(animazione,sblocco){
	if(nodi[tutorialeattivo].tipo == 0){
		var contatore = 1;
		while (media[tutorialeattivo+"_"+contatore]){
			stopmedium(tutorialeattivo+"_"+contatore);
			contatore++;
		}
	}
	if (animazione)
		animazioneattiva = animazione;
	else
		animazione = animazioneattiva;
	if (multimedia == 1 || sblocco == 1){
		animazionegiocoattiva = 1;
		if (animazione == 1){
			try{setTimeout("document.getElementById('animazionegioco').azione(true)",200);}catch(e){};
		}
		else
			try{document.getElementById("animazionegioco").azione(animazione);}catch(e){};
		if (sblocco == 1)
			document.getElementById("comandoanimazionegioco").style.visibility="hidden";
	}
}

function stopanimazionegioco(){
	if (animazionegiocoattiva == 1){
		try{document.getElementById("animazionegioco").azione(0);}catch(e){};
		animazionegiocoattiva = 0;
	}
}

function attivamedium(){ // attiva il suono/filmato/animazione tramite pulsante
	multimedia = 1;
	document.getElementById("pulsantesuonoon").style.visibility="hidden";
	document.getElementById("pulsantesuonooff").style.visibility="visible";
	stato_elementi[0]["pulsantesuonoon"]="hidden";
	stato_elementi[0]["pulsantesuonooff"]="visible";
	iniziamedium();
}

function disattivamedium(){ // disattiva il suono/filmato/animazione tramite pulsante
	multimedia = 0;
	document.getElementById("pulsantesuonooff").style.visibility="hidden";
	document.getElementById("pulsantesuonoon").style.visibility="visible";
	stato_elementi[0]["pulsantesuonoon"]="visible";
	stato_elementi[0]["pulsantesuonooff"]="hidden";
	finemedium();
}

function iniziamedium(){ // inizializza i suoni/filmati/animazioni della pagina
	var contatore = 1;
	var identificatore = "";
	mediumattivo = 0;
	if (multimedia==1){
		while (media[tutorialeattivo+"_"+contatore]){
			identificatore = tutorialeattivo+"_"+contatore;
			if (media[identificatore].attivazione == 1){
				mediumattivo = 1;
				playmedium(identificatore);
			}
			contatore++;
		}
	}
}

function finemedium(){ // termina i suoni/filmati/animazioni della pagina
	var contatore = 1;
	while (media[tutorialeattivo+"_"+contatore]){
		stopmedium(tutorialeattivo+"_"+contatore);
		contatore++;
	}
	if(modofruizione == 2){
		stopanimazionegioco();
	}
	mediumattivo = 0;
}

function playmedium(identificatore){ // avvia il suono/filmato/animazione con modalità differenziate
	switch (media[identificatore].tipomedium){
		case "swf":
			if (plugin_fl == 1){
				try{setTimeout("document.getElementById('"+identificatore+"').azione(true)",100);}catch(e){};
				try{document.getElementById(identificatore).Play();}catch(e){};
			}
		break;
		case "dcr":
			if (plugin_sw == 1)
				try{document.getElementById(identificatore).Play();}catch(e){};
		break;
		case "flv":
			if (plugin_fl == 1)
				try{setTimeout("document.getElementById('"+identificatore+"').azione(true)",100);}catch(e){};
		break;
		case "mp3":
			if (plugin_fl == 1)
				try{setTimeout("document.getElementById('player').azione(media['"+identificatore+"'].nomefilemedium+'.mp3',true)",500);}catch(e){};
		break;
		case "ggb":
		break;
		case "wmv":
			if (plugin_wm == 1)
				setTimeout("document.getElementById('"+identificatore+"').Controls.Play()",100);
		break;
		case "mov":
			if (plugin_qt == 1)
				setTimeout("document.getElementById('"+identificatore+"').Play()",100);
		break;
		case "rm":
		case "ram":
		case "rpm":
			if (plugin_rp == 1)
				setTimeout("document.getElementById('"+identificatore+"').DoPlay()",100);
		break;
	}
}

function stopmedium(identificatore){ // interrompe il suono/filmato/animazione con modalità differenziate
	switch (media[identificatore].tipomedium){
		case "swf":
			if (plugin_fl == 1){
				try{document.getElementById(identificatore).azione(false);}catch(e){};
				try{document.getElementById(identificatore).StopPlay();}catch(e){};
			}
		break;
		case "dcr":
			if (plugin_sw == 1)
				try{document.getElementById(identificatore).Stop();}catch(e){};
		break;
		case "flv":
			if (plugin_fl == 1)
				try{document.getElementById(identificatore).azione(false);}catch(e){};
		break;
		case "mp3":
			if (plugin_fl == 1)
				try{document.getElementById("player").azione(media[identificatore].nomefilemedium+".mp3",false);}catch(e){};
		break;
		case "ggb":
		break;
		case "wmv":
			if (plugin_wm == 1)
				document.getElementById(identificatore).Controls.Stop();
		break;
		case "mov":
			if (plugin_qt == 1)
				document.getElementById(identificatore).Stop();
		break;
		case "rm":
		case "ram":
		case "rpm":
			if (plugin_rp == 1)
				document.getElementById(identificatore).DoStop();
		break;
	}
}

function trovaidentificatore(pagina){ // individua il primo identificatore libero
	var contatore = 1;
	while (media[pagina+"_"+contatore]){
		contatore++;
	}
	return contatore;
}

/* -- RICERCA PLUG-IN -- */
function cercaplugin(){ // cerca i plug-in disponibili in browser diversi da IE
	if (navigator.plugins && navigator.plugins.length > 0){
		for(var i=0;i < navigator.plugins.length;i++){
			if(navigator.plugins[i].name.indexOf("Flash") >= 0 || navigator.plugins[i].description.indexOf("Flash") >= 0){
				plugin_fl = 1;}
			if(navigator.plugins[i].name.indexOf("Shockwave") >= 0 || navigator.plugins[i].description.indexOf("Shockwave") >= 0)
				plugin_sw = 1;
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
	if (plugin_fl == 0)
		comunicazione = "Per audio, video e animazioni è necessario Flash.";
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
	var contatore = 1;
	var nomepagina;
	var stato = new String;
	var segnalibro = new String;
	if (contapaginevisitate() == paginetutoriali){
		if (punteggio >= (punteggiominimo/100)*punteggiomassimo)
			stato = "passed";
		else
			stato = "completed";
		tutorialeattivo = "homepage";
	}
	else{
		stato = "incomplete";
	}
	if (puntatorestack == "")
		segnalibro = tutorialeattivo;
	else
		segnalibro = puntatorestack;
	var dati = dimensionicarattere + "," + dimensionipagina + "," + multimedia + "," + modofruizione;
	for(var i=1;i < successione[0].length;i++){
		nomepagina = successione[0][i];
		if (nodi[nomepagina].visitato > 0){
			if (nodi[nomepagina].visitato == 4 || nodi[nomepagina].visitato == 5)
				nodi[nomepagina].visitato = 2;
			dati = dati + ","+nodi[nomepagina].visitato;
		}
		else
			dati = dati + ",0";
	}
	for(var i=1;i < successione[0].length;i++){
		nomepagina = successione[0][i];
		if (nodi[nomepagina].tipo == 2){
				contatore = 1;
			while (test[nomepagina+"_"+contatore]){
				dati = dati + "," + test[nomepagina+"_"+contatore].risultato + "," + test[nomepagina+"_"+contatore].rispostaitem + "," + test[nomepagina+"_"+contatore].status;
				contatore++;
			}
		}
	}
	concludicorso(stato,segnalibro,punteggio,punteggiomassimo,dati);
}

function contapaginevisitate(){ // conta le pagine visitate
	var nomepagina;
	var pagine = 0;
	for(var i=0;i < successione[0].length;i++){
		nomepagina = successione[0][i];
		if ((nodi[nomepagina].tipo == 1 || nodi[nomepagina].tipo == 3) && nodi[nomepagina].visitato > 0 && nodi[nomepagina].alternativo == 0)
			pagine++;
	}
	return pagine;
}

/* -- PULSANTI -- */
function pulsantiambiente(){
	document.write("<a id='comandoanimazionegioco' href='#' accesskey='n' tabindex='115' onClick='avviaanimazionegioco(,1);return false;' onKeyPress='avviaanimazionegioco(,1);return false;' title=\"Attiva l'animazione del gioco\"></a>");
	document.write("<a id='pulsantezoom' href='#' onClick='cambiazoom();return false;' onKeypress='cambiazoom();return false;'><img id='zoom' onMouseOver=\"roll(this,'zoom')\" onMouseOut=\"noroll(this,'zoom')\"  src='../immagini/pulsante_zoom.gif' alt='Modifica le dimensioni della finestra'><\/a>");
	document.write("<a id='pulsanteingrandisci' href='#' onClick='incrementa();return false;' onKeypress='incrementa();return false;'><img id='ingrandisci' onMouseOver=\"roll(this,'ingrandisci')\" onMouseOut=\"noroll(this,'ingrandisci')\" src='../immagini/pulsante_ingrandisci.gif' alt='Ingrandisci i caratteri'><\/a>");
	document.write("<a id='pulsanterimpicciolisci' href='#' onClick='decrementa();return false;' onKeypress='decrementa();return false;'><img id='rimpicciolisci' onMouseOver=\"roll(this,'rimpicciolisci')\" onMouseOut=\"noroll(this,'rimpicciolisci')\"  src='../immagini/pulsante_rimpicciolisci.gif' alt='Rimpicciolisci i caratteri'><\/a>");
	document.write("<a id='pulsantesuonoon' href='#' onClick='attivamedium();return false;' onKeypress='attivamedium();return false;'><img id='suonoon' onMouseOver=\"roll(this,'suonoon')\" onMouseOut=\"noroll(this,'suonoon')\" src='../immagini/pulsante_suonoon.gif' alt=\"Attiva audio, video e animazioni\"><\/a>");
	document.write("<a id='pulsantesuonooff' href='#' onClick='disattivamedium();return false;' onKeypress='disattivamedium();return false;'><img id='suonooff' onMouseOver=\"roll(this,'suonooff')\" onMouseOut=\"noroll(this,'suonooff')\" src='../immagini/pulsante_suonooff.gif' alt=\"Disattiva audio, video e animazioni\"><\/a>");
}

function pulsantinavigazione(){
	document.write("<a id='comandomultimedia' href='#' accesskey='d' tabindex='110' onClick='disattivamedium();return false;' onKeyPress='disattivamedium();return false;' title=\"Per usare il lettore di schermo, disattiva l'audio e gli altri contributi multimediali. Eventuali animazioni Flash saranno sostituite da pagine alternative\"><\/a>");
	document.write("<a id='pulsanteindietro' href='#' accesskey='o' tabindex='200' onClick='muovi(2);return false;' onKeypress='muovi(2);return false;'><img id='indietro' onMouseOver=\"roll(this,'indietro')\" onMouseOut=\"noroll(this,'indietro')\" src='../immagini/pulsante_indietro.gif' alt=\"Indietro\"><\/a>");
	document.write("<a id='pulsanteavanti' href='#' accesskey='a' tabindex='210' onClick='muovi(1);return false;' onKeypress='muovi(1);return false;'><img id='avanti' onMouseOver=\"roll(this,'avanti')\" onMouseOut=\"noroll(this,'avanti')\" src='../immagini/pulsante_avanti.gif' alt=\"Avanti\"><\/a>");
	document.write("<a id='pulsantehistory' href='#' accesskey='u' tabindex='900' onClick='indietrohistory();return false;' onKeypress='indietrohistory();return false;'><img id='history' onMouseOver=\"roll(this,'history')\" onMouseOut=\"noroll(this,'history')\" src='../immagini/pulsante_history.gif' alt=\"Torna indietro\"><\/a>");
	document.write("<a id='pulsantemodo1' href='#' accesskey='1' tabindex='105' onClick='stopanimazionegioco();impostafruizione(1);return false;' onKeypress='stopanimazionegioco();impostafruizione(1);return false;'><img id='modo1' onMouseOver=\"roll(this,'modo1')\" onMouseOut=\"noroll(this,'modo1')\" src='../immagini/pulsante_modo1.gif' alt='"+descrizionesuccessione[1]+"'><\/a>");
	document.write("<a id='pulsantemodo2' href='#' accesskey='2' tabindex='106' onClick='impostafruizione(2);avviaanimazionegioco(1);return false;' onKeypress='impostafruizione(2);avviaanimazionegioco(1);return false;'><img id='modo2' onMouseOver=\"roll(this,'modo2')\" onMouseOut=\"noroll(this,'modo2')\" src='../immagini/pulsante_modo2.gif' alt='"+descrizionesuccessione[2]+"'><\/a>");
	document.write("<a id='pulsanteinizia' href='#' accesskey='z' tabindex='114' onClick='iniziafruizione();return false;' onKeyPress='iniziafruizione();return false;'><img id='inizia' onMouseOver=\"roll(this,'inizia')\" onMouseOut=\"noroll(this,'inizia')\" src='../immagini/pulsante_inizia.gif' alt='Inizia il corso secondo la modalità prescelta'></a>");
	document.write("<a id='pulsantecontinua' href='#' accesskey='q' tabindex='115' onClick='continuafruizione();return false;' onKeyPress='continuafruizione();return false;'><img id='continua' onMouseOver=\"roll(this,'continua')\" onMouseOut=\"noroll(this,'continua')\" src='../immagini/pulsante_continua.gif' alt='Continua il corso dal punto in cui è stato interrotto'></a>");
	document.write("<a href='#sommario_a' accesskey='i' tabindex='910' onClick=\"vai('sommario');return false;\" onKeyPress=\"vai('sommario');return false;\" title=\"Vai all'indice\"></a>");
	document.write("<a href='#esci_a' accesskey='e' tabindex='990' onClick=\"vai('esci');return false;\" onKeyPress=\"vai('esci');return false;\" title='Esci dal corso'></a>");
}

/* -- ASSEGNAZIONE VARIABILI -- */
var animazionegiocoattiva = 0;
var approfondimentoattivo = "";
var approfondimentoattivo2 = "";
var dimensionicarattere = 1;
var dimensionipagina = 1;
var classeattuale = -1;
var elementoattivo = 2; // 2=tutoriale 4=indice 5/6=approfondimento
var id_timeout;
var iniziocorso = 1;
var mediumattivo = 0;
var messaggioerrore = new String;
var modofruizione = new Number;
var modohistory = 0;
var multimedia = 1;
var nomeapprofondimento = new Array();
var animazioneattiva = 0;
var paginaservizioattiva = new String;
var paginetutoriali = new Number // totale delle pagine tutoriali (introduzione + tutoriale)
var paginetest = new Number // totale delle pagine test
var puntatorestack = new String;
var punteggio = 0; //punteggio ottenuto
var punteggiomassimo = new Number; //punteggio massimo teorico
var stato_elementi = new Array; // stato degli elementi dell'interfaccia
stato_elementi[0] = new Array;
stato_elementi[1] = new Array;
stato_elementi[2] = new Array;
var tutorialeattivo = "homepage";
var tutorialeerrore = new String;

var nodi = new Array; // array di oggetti
var test = new Array; // array di oggetti
var media = new Array; // array di oggetti
var cruciverba = new Array; // array di oggetti

var codice = new String; // codice univoco per tracciamento locale
var titololo = new String; // titolo del lo
var bloccoavanzamento = new Number; // 1: obbligo di superare il test per proseguire
var autosuccessione = new Number; // 1: consente di generare automaticamente le successioni
var modocontinua = new Number; // 1: consente prosecuzione dopo sospensione
var visualizzasoluzioni = new Number; // numero tentativi errati per visualizzare soluzioni
var puntinegativi = new Number; // 1 = sottrae punti per test errato
var punteggiominimo = new Number; //punteggio percentuale per considerare superato il modulo
var punteggiosoglia = new Number; //punteggio percentuale minimo per accedere alla domanda finale
var tutorialesoglia = new Number; //percentuale minima di pagine tutoriali per accedere alla domanda finale

var tipobrowser = new Number;
var plugin_qt = 0; // Quick Time
var plugin_wm = 0; // Windows Media Player
var plugin_rp = 0; // Real Player
var plugin_fl = 0; // Flash
var plugin_sw = 0; // Shockwave
var plugin_ja = 0; // Java

var successione = new Array;
successione[0] = new Array;
successione[1] = new Array;
successione[2] = new Array;
successione[3] = new Array;

var descrizionesuccessione = new Array;
descrizionesuccessione[1] = "Lezione";
descrizionesuccessione[2] = "Gioco";
descrizionesuccessione[3] = "Test";

// oggetti
function nodo(tipo, titolo, punti, tutorialealternativo, tutorialetest, messaggiotestesatto, messaggiotesterrore, tutorialeprincipale, alternativo, testtutoriale, numeropagina, ultimapagina, precedente, successivo, tentativi, plugin, visitato, progressivo){
	this.tipo = tipo || 0;
	this.titolo = titolo || "";
	this.punti = punti || 0;
	this.tutorialealternativo = tutorialealternativo || "";
	this.tutorialetest = tutorialetest || "";
	this.messaggiotestesatto = messaggiotestesatto || "";
	this.messaggiotesterrore = messaggiotesterrore || "";
	this.tutorialeprincipale = tutorialeprincipale || "";
	this.alternativo = alternativo || 0;
	this.testtutoriale = testtutoriale || "";
	this.numeropagina = numeropagina || 0;
	this.ultimapagina = ultimapagina || 0;
	this.precedente = precedente || "";
	this.successivo = successivo || "";
	this.tentativi = tentativi || 0;
	this.plugin = plugin || "";
	this.visitato = visitato || 0;
	this.progressivo = progressivo || 0;
}

function item(tipoitem, testolegend, domanda, testo, opzioni, rispostaesatta, tutorialeitem, messaggioitem, direzione, immaginedomanda, testoalternativodomanda, mediadomanda, attivomediadomanda, classemediadomanda, immaginerisposta, testoalternativorisposta, mediarisposta, attivomediarisposta, classemediarisposta, identificatoremedia, rispostaitem, risultato, status){
	this.tipoitem = tipoitem || 0; // tipo di item;
	this.testolegend = testolegend || ""; // testo della domanda principale o delle istruzioni
	this.domanda = domanda || ""; // testo precedente l'input
	this.testo = testo || ""; // testo successivo all'input
	this.opzioni = opzioni || ""; // elenco delle opzioni
	this.rispostaesatta = rispostaesatta || ""; // risposte esatte
	this.tutorialeitem = tutorialeitem || ""; // tutoriali per errore
	this.messaggioitem = messaggioitem || ""; // messaggi di errore
	this.direzione = direzione || 0; // orientemento del testo della domanda
	this.immaginedomanda = immaginedomanda || ""; // immagine associata alla domanda
	this.testoalternativodomanda = testoalternativodomanda || ""; // testo alternativo immagine associata alla domanda;
	this.mediadomanda = mediadomanda || ""; // file multimediale associato alla domanda
	this.attivomediadomanda = attivomediadomanda || ""; // flag di attivazione del file associato alla domanda;
	this.classemediadomanda = classemediadomanda || ""; // classe del file associato alla domanda;
	this.immaginerisposta = immaginerisposta || ""; // immagine associata alle risposte
	this.testoalternativorisposta = testoalternativorisposta || "";// testo alternativo immagine associata alle risposte;
	this.mediarisposta = mediarisposta || ""; // file multimediale associato alla domanda
	this.attivomediarisposta = attivomediarisposta || ""; // flag di attivazione del file associato alle risposte;
	this.classemediarisposta = classemediarisposta || ""; // classe del file associato alle risposte;
	this.identificatoremedia = identificatoremedia || ""; // identificatore file multimediale associato alla domanda
	this.rispostaitem = rispostaitem || ""; // risposta dell'utente
	this.risultato = risultato || 0; // 0: non risposto; 1: errore; 2: esatto
	this.status = status || 0; // 0: possibile risposta; 1; risposta bloccata
}

function medium(tipomedium, nomefilemedium, attivazione, plugin, classe){
	this.tipomedium = tipomedium || "";
	this.nomefilemedium = nomefilemedium || "";
	this.attivazione = attivazione || 0;
	this.plugin = plugin || 0;
	this.classe = classe || ""; // 1 = audio; 2 = video; 3 = animazione;
}

function cruci(larghezza, altezza, casellenere, caselle, attivo){
	this.larghezza = larghezza || 0;
	this.altezza = altezza || 0;
	this.casellenere = casellenere || "";
	this.caselle = new Array;
	this.attivo = attivo || 0;
}

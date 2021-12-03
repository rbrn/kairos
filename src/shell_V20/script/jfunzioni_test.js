/* --- SHELL ACCESSIBILE: FUNZIONI DI GESTIONE TEST --- */

/* -- NAVIGAZIONE -- */
function test(){
	var paginetest = nodi[tutorialeattivo].testtutoriale.split("|");
	tutoriale(paginetest[0],1);
}

/* -- VISUALIZZAZIONE -- */
function visualizzatest(pagina, classetest, classerisposta, classedomanda){
	var contatore = 1;
	var contatore1 = 1;
	var codicetest = new String;
	var identificatoremedium = 0;
	var risposte = new String;
	var immaginirisposte = new String;
	var mediarisposte = new String;
	var attivomediarisposte = new String;
	var classemediarisposte = new String;
	var risposteitem = new String;
	document.write("<div class="+classetest+"><div class="+classerisposta+">");
	while (test[pagina+"_"+contatore]){
		codicetest = pagina+"_"+contatore;
		switch (test[codicetest].tipoitem){
			case 1: // domande a risposta chiusa
				test[codicetest].opzioni = eliminacampi(test[codicetest].opzioni);
				risposte = test[codicetest].opzioni.split("|");
				immaginirisposte = test[codicetest].immaginerisposta.split("|");
				testoalternativorisposte = test[codicetest].testoalternativorisposta.split("|");
				mediarisposte = test[codicetest].mediarisposta.split("|");
				attivomediarisposte = test[codicetest].attivomediarisposta.split("|");
				classemediarisposte = test[codicetest].classemediarisposta.split("|");
				document.write("<form id='test_"+codicetest+"' action=''><fieldset>");
				if (test[codicetest].direzione == 1){ // orizzontale
					if (test[codicetest].testolegend != ""){
						document.write("<legend class="+classedomanda+">"+test[codicetest].testolegend+"</legend><p>");
						for(var i=1; i<risposte.length+1; i++){
							document.write("<span class ='colonnatestint_"+i+"'>"+risposte[i-1]+"</span>");
						}
					document.write("<br><br>");
					}
					else
						document.write("<legend class='nascosto'>Stesse indicazioni del test precedente su questa pagina.</legend>");
					if (test[codicetest].mediadomanda)
						inseriscimedia(pagina,test[codicetest].mediadomanda,test[codicetest].attivomediadomanda,test[codicetest].classemediadomanda);
					if (test[codicetest].immaginedomanda)
						document.write("<img class='immagineinlinea' src='"+test[codicetest].immaginedomanda+"' alt=\""+test[codicetest].testoalternativodomanda+"\">");
					document.write("<div class ='areatestdomanda'>");
					document.write("<div class ='colonnatestdomanda'>"+test[codicetest].domanda+"</div>");
					document.write("<div class ='areatestrisposte'>");
					for(var i=1; i<risposte.length+1; i++){
						if (test[codicetest].rispostaitem == i){
							document.write("<input class='colonnatest_"+i+"' type='radio' tabindex='"+contatore+"' name='test_"+codicetest+"' id='test"+i+"_"+codicetest+"' checked>");
							if (test[codicetest].risultato == 1)
								document.write("<label for='test"+i+"_"+codicetest+"'> <img id='testimm"+i+"_"+codicetest+"' class='immaginecolonnatest_"+i+"' src='../immagini/feedback_ko.gif' alt='"+messaggiofeedback[29]+"'>");
							else
								document.write("<label for='test"+i+"_"+codicetest+"'> <img id='testimm"+i+"_"+codicetest+"' class='immaginecolonnatest_"+i+"' src='../immagini/feedback_ok.gif' alt='"+messaggiofeedback[28]+"'>");
						}
						else{
							document.write("<input class='colonnatest_"+i+"' type='radio' tabindex='"+contatore+"' name='test_"+codicetest+"' id='test"+i+"_"+codicetest+"'>");
							document.write("<label for='test"+i+"_"+codicetest+"'> <img id='testimm"+i+"_"+codicetest+"' class='immaginecolonnatest_"+i+"' src='../immagini/vuoto.gif' alt=''>");
						}
						document.write("<span class='nascosto'>"+risposte[i-1]+"</span>");
						document.write("</label>");
					}
					document.write("</div></div>");
				}
				else{ // verticale
					if (test[codicetest].mediadomanda)
						inseriscimedia(pagina,test[codicetest].mediadomanda,test[codicetest].attivomediadomanda,test[codicetest].classemediadomanda);
					if (test[codicetest].immaginedomanda)
						document.write("<p><img class='immagine' src='"+test[codicetest].immaginedomanda+"' alt=\""+test[codicetest].testoalternativodomanda+"\">");
					if (test[codicetest].testolegend != "")
						document.write("<legend class="+classedomanda+">"+test[codicetest].testolegend+"</legend>");
					for(var i=1; i<risposte.length+1; i++){
						if (test[codicetest].rispostaitem == i){
							document.write("<input type='radio' tabindex='"+contatore+"' name='test_"+codicetest+"' id='test"+i+"_"+codicetest+"' checked>");
							if (test[codicetest].risultato == 1)
								document.write("<label for='test"+i+"_"+codicetest+"'> <img id='testimm"+i+"_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ko.gif' alt='"+messaggiofeedback[29]+"'>");
							else
								document.write("<label for='test"+i+"_"+codicetest+"'> <img id='testimm"+i+"_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ok.gif' alt='"+messaggiofeedback[28]+"'>");
						}
						else{
							document.write("<input type='radio' tabindex='"+contatore+"' name='test_"+codicetest+"' id='test"+i+"_"+codicetest+"'>");
							document.write("<label for='test"+i+"_"+codicetest+"'> <img id='testimm"+i+"_"+codicetest+"' class='immagineinlinea' src='../immagini/vuoto.gif' alt=''>");
						}
						if (mediarisposte[i-1])
							inseriscimedia(pagina,mediarisposte[i-1],attivomediarisposte[i-1],classemediarisposte[i-1]);
						if (immaginirisposte[i-1])
							document.write("<img class='immagineinlinea' src='"+immaginirisposte[i-1]+"' alt=\""+testoalternativorisposte[i-1]+"\">");
						document.write(risposte[i-1]);
						document.write("</label>");
						document.write("<br>");
					}
				}
				document.write("</fieldset></form>");
			break;
			case 2: // domande a scelta multipla
				test[codicetest].opzioni = eliminacampi(test[codicetest].opzioni);
				risposte = test[codicetest].opzioni.split("|");
				immaginirisposte = test[codicetest].immaginerisposta.split("|");
				testoalternativorisposte = test[codicetest].testoalternativorisposta.split("|");
				mediarisposte = test[codicetest].mediarisposta.split("|");
				attivomediarisposte = test[codicetest].attivomediarisposta.split("|");
				classemediarisposte = test[codicetest].classemediarisposta.split("|");
				risposteitem = test[codicetest].rispostaitem.split("|");
				document.write("<form id='test_"+codicetest+"' action=''>");
				if (test[codicetest].mediadomanda)
					inseriscimedia(pagina,test[codicetest].mediadomanda,test[codicetest].attivomediadomanda,test[codicetest].classemediadomanda);
				if (test[codicetest].immaginedomanda)
					document.write("<p><img class='immagine' src='"+test[codicetest].immaginedomanda+"' alt=\""+test[codicetest].testoalternativodomanda+"\">");
				document.write("<fieldset><legend class="+classedomanda+">");
				switch (test[codicetest].risultato){
					default:
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/vuoto.gif' alt=''>");
					break;
					case "1":
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ko.gif' alt='"+messaggiofeedback[29]+"'>");
					break;
					case "2":
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ok.gif' alt='"+messaggiofeedback[28]+"'>");
					break;
				}
				document.write(test[codicetest].testolegend+"</legend>");
				document.write(test[codicetest].domanda + " ");
				for(var i=1; i<risposte.length+1; i++){
					if (risposteitem[i-1] == "1")
						document.write("<input type='checkbox' tabindex='"+contatore+"' id='test"+i+"_"+codicetest+"' checked>");
					else
						document.write("<input type='checkbox' tabindex='"+contatore+"' id='test"+i+"_"+codicetest+"'>");
					document.write("<label for='test"+i+"_"+codicetest+"'>");
					document.write(" <img id='testimm"+i+"_"+codicetest+"' class='immagineinlinea' src='../immagini/vuoto.gif' alt=''>");
					if (mediarisposte[i-1])
						inseriscimedia(pagina,mediarisposte[i-1],attivomediarisposte[i-1],classemediarisposte[i-1]);
					if (immaginirisposte[i-1])
						document.write("<img class='immagineinlinea' src='"+immaginirisposte[i-1]+"' alt=\""+testoalternativorisposte[i-1]+"\">");
					document.write(risposte[i-1]);
					document.write("</label>");
					if (test[codicetest].direzione == 0)
						document.write("<br>");
				}
				document.write("</form></fieldset>");
			break;
			case 3: // domande con completamento di frasi
				if (test[codicetest].testolegend != ""){
					document.write("<form action=''>");
					if (test[codicetest].mediadomanda)
						inseriscimedia(pagina,test[codicetest].mediadomanda,test[codicetest].attivomediadomanda,test[codicetest].classemediadomanda);
					if (test[codicetest].immaginedomanda)
						document.write("<p><img class='immagine' src='"+test[codicetest].immaginedomanda+"' alt=\""+test[codicetest].testoalternativodomanda+"\">");
					document.write("<fieldset><legend class="+classedomanda+">"+test[codicetest].testolegend+"</legend>");
				}
				document.write("<label for='test_"+codicetest+"'>"+test[codicetest].domanda);
				if (test[codicetest].mediarisposta)
						inseriscimedia(pagina,test[codicetest].mediarisposta,test[codicetest].attivomediarisposta,test[codicetest].classemediarisposta);
				if (test[codicetest].immaginerisposta)
					document.write("<img class='immagineinlinea' src='"+test[codicetest].immaginerisposta+"' alt=\""+test[codicetest].testoalternativorisposta+"\">");
				switch (test[codicetest].risultato){
					default:
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/vuoto.gif' alt=''></label><input type='text' tabindex='"+contatore+"' id='test_"+codicetest+"' size='"+test[codicetest].rispostaesatta.length+"'>"+test[codicetest].testo);
					break;
					case "1":
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ko.gif' alt='"+messaggiofeedback[29]+"'></label><input type='text' tabindex='"+contatore+"' id='test_"+codicetest+"' size='"+test[codicetest].rispostaesatta.length+"' value=\""+test[codicetest].rispostaitem+"\">"+test[codicetest].testo);
					break;
					case "2":
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ok.gif' alt='"+messaggiofeedback[28]+"'></label><input type='text' tabindex='"+contatore+"' id='test_"+codicetest+"' size='"+test[codicetest].rispostaesatta.length+"' value=\""+test[codicetest].rispostaitem+"\">"+test[codicetest].testo);
					break;
				}
				if (test[codicetest].direzione == 0)
					document.write("<p>");
				if (!test[pagina+"_"+(contatore+1)] || test[pagina+"_"+(contatore+1)].tipoitem != 3 || test[pagina+"_"+(contatore+1)].testolegend != "")
					document.write("</form></fieldset>");
			break;
			case 4: // domande con selezione di opzioni
				test[codicetest].opzioni = eliminacampi(test[codicetest].opzioni);
				if (nodi[pagina].alternativo == 0)
					risposte = test[codicetest].opzioni.split("|");
				else
					risposte = test[codicetest].opzioni.split("|").sort();
				if (test[codicetest].testolegend != ""){
					document.write("<form action=''>");
 					if (test[codicetest].mediadomanda)
						inseriscimedia(pagina,test[codicetest].mediadomanda,test[codicetest].attivomediadomanda,test[codicetest].classemediadomanda);
					if (test[codicetest].immaginedomanda)
						document.write("<p><img class='immagine' src='"+test[codicetest].immaginedomanda+"' alt=\""+test[codicetest].testoalternativodomanda+"\">");
					document.write("<fieldset><legend class="+classedomanda+">"+test[codicetest].testolegend+"</legend>");
				}
				document.write("<label for='test_"+codicetest+"'>"+test[codicetest].domanda);
				if (test[codicetest].mediarisposta)
						inseriscimedia(pagina,test[codicetest].mediarisposta,test[codicetest].attivomediarisposta,test[codicetest].classemediarisposta);
				if (test[codicetest].immaginerisposta)
					document.write("<img class='immagineinlinea' src='"+test[codicetest].immaginerisposta+"' alt=\""+test[codicetest].testoalternativorisposta+"\">");
				switch (test[codicetest].risultato){
					default:
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/vuoto.gif' alt=''></label>");
					break;
					case "1":
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ko.gif' alt='"+messaggiofeedback[29]+"'></label>");
					break;
					case "2":
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ok.gif' alt='"+messaggiofeedback[28]+"'></label>");
					break;
				}
				document.write("<select tabindex='1' id='test_"+codicetest+"'>");
				for(var i=1; i<risposte.length+1; i++){
					if(test[codicetest].rispostaitem == risposte[i-1]){
						document.write("<option id='test"+(i-1)+"_"+codicetest+"' value=\""+risposte[i-1]+"\" selected>"+risposte[i-1]);
					}
					else
						document.write("<option id='test"+(i-1)+"_"+codicetest+"' value=\""+risposte[i-1]+"\">"+risposte[i-1]);
				}
				document.write("</select>");
				document.write(test[codicetest].testo);
				if (test[codicetest].direzione == 0)
					document.write("<p>");
				if (!test[pagina+"_"+(contatore+1)] || test[pagina+"_"+(contatore+1)].tipoitem != 4 || test[pagina+"_"+(contatore+1)].testolegend != "")
					document.write("</form></fieldset>");
			break;
			case 5: // test drag & drop
				document.write("<p class='nascosto'>"+messaggiofeedback[33]);
				test[codicetest].identificatoremedia = trovaidentificatore(pagina);
				document.write("<div id='test_"+codicetest+"' class='paginaintera'>");
				caricamedia(test[codicetest].mediadomanda,pagina,test[codicetest].identificatoremedia,1,classerisposta,test[codicetest].immaginedomanda,test[codicetest].testoalternativodomanda);
				document.write("</div></div>");
				document.write("<div class='"+classedomanda+"'>");
				switch (test[codicetest].risultato){
					default:
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/vuoto.gif' alt=''>");
					break;
					case "1":
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ko.gif' alt='"+messaggiofeedback[29]+"'>");
					break;
					case "2":
						document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ok.gif' alt='"+messaggiofeedback[28]+"'>");
					break;
				}
				document.write(" "+test[codicetest].testolegend+"</p>");
			break;
			case 6: // cruciverba
				if (cruciverba[pagina].attivo == 0){
					if (cruciverba[pagina].casellenere != ""){
						var nere = cruciverba[pagina].casellenere.split("|");
						for(var i=0; i<nere.length; i++){
							cruciverba[pagina].caselle[nere[i]] = -1
						}
					}
					cruciverba[pagina].attivo = 1;
					var numerocaselle = cruciverba[pagina].larghezza * cruciverba[pagina].altezza;
					var tabindice = 0;
					document.write("<table class='cruciverba' cellspacing='0' summary='Schema del cruciverba'><tr>");
					for(var i=1; i<numerocaselle+1; i++){
						document.write("<td><div class='casella'>");
						if (cruciverba[pagina].caselle[i] == -1)
							document.write("<img class='casellanera' src='../immagini/cruci_nera.gif' alt='Casella nera'>");
						else{
							if (cruciverba[pagina].caselle[i])
								document.write("<img class='immaginecasella' src='../immagini/cruci_"+cruciverba[pagina].caselle[i]+".gif' alt='Casella "+cruciverba[pagina].caselle[i]+"'>");
							document.write("<input class='crucireadonly' id='casella_"+pagina+"_"+i+"' readonly size='1' maxlength='1' value =''></div>");
						}
						if ((i)%cruciverba[pagina].larghezza == 0 && i <= numerocaselle-cruciverba[pagina].larghezza)
							document.write("</tr><tr>");
					}
					document.write("</tr></table></div>");
					document.write("<div class='"+classedomanda+"'>");// definizioni del cruciverba
					document.write("<form id='test_"+pagina+"'' action=''>");
					document.write("<fieldset><legend class='domanda'>Orizzontali</legend>");
					contatore1 = 1;
					while (test[pagina+"_"+contatore1]){
						codicetest = pagina+"_"+contatore1;
						if (test[codicetest].direzione == 0){
							inseriscidefinizione(pagina,contatore1,tabindice);
							tabindice = tabindice + 2;
						}
						contatore1++;
					}
					document.write("</fieldset><fieldset><legend class='domanda'>Verticali</legend>");
					contatore1 = 1;
					while (test[pagina+"_"+contatore1]){
						codicetest = pagina+"_"+contatore1;
						if (test[codicetest].direzione==1){
							inseriscidefinizione(pagina,contatore1,tabindice);
							tabindice = tabindice + 2;
						}
						contatore1++;
					}
					document.write("</fieldset></form>");
				}
			break;
		}
		contatore++;
	}
	document.write("</div></div>");
}

function inseriscimedia(pagina,medium,attivo,classe){
	var progressivomedium = trovaidentificatore(pagina);
	var identificatore = pagina+"_"+progressivomedium
	document.write("<p><a href='#' tabindex='"+progressivomedium+"' onClick='playmedium(\""+identificatore+"\");return false' onKeyPress='playmedium(\""+identificatore+"\");return false'>");
	document.write("<img class='immagineinlinea' onMouseOver='roll(this,\"mediaon\")' onMouseOut='noroll(this,\"mediaon\")' src='../immagini/pulsante_mediaon.gif' alt=\"Avvia l'elemento multimediale\"></a>");
	document.write("<a href='#' tabindex='"+progressivomedium+"' onClick='stopmedium(\""+identificatore+"\");return false' onKeyPress='stopmedium(\""+identificatore+"\");return false'>");
	document.write("<img class='immagineinlinea' onMouseOver='roll(this,\"mediaoff\")' onMouseOut='noroll(this,\"mediaoff\")' src='../immagini/pulsante_mediaoff.gif' alt=\"Interrompi l'elemento multimediale\"></a>");
	caricamedia(medium,pagina,progressivomedium,attivo,classe);
}

function inseriscidefinizione(pagina,contatore,tabindice){
	var codicetest = pagina+"_"+contatore;
	document.write("<label for='test_"+codicetest+"'>"+test[codicetest].opzioni+". "+test[codicetest].domanda);
	if (test[codicetest].mediarisposta)
		inseriscimedia(pagina,test[codicetest].mediarisposta,test[codicetest].attivomediarisposta,test[codicetest].classemediarisposta);
	if (test[codicetest].immaginerisposta)
		document.write("<img class='immagineinlinea' src='"+test[codicetest].immaginerisposta+"' alt=\""+test[codicetest].testoalternativorisposta+"\">");
	switch (test[codicetest].risultato){
		default:
			document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/vuoto.gif' alt=''></label><input type='text' tabindex='"+tabindice+"' id='test_"+codicetest+"' size='"+test[codicetest].rispostaesatta.length+"'>");
		break;
		case "1":
				document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ko.gif' alt='"+messaggiofeedback[29]+"'></label><input type='text' tabindex='"+tabindice+"' id='test_"+codicetest+"' size='"+test[codicetest].rispostaesatta.length+"' value=\""+test[codicetest].rispostaitem+"\">");
				inseriscirisposta(pagina,contatore);
		break;
		case "2":
			document.write("<img id='testimm_"+codicetest+"' class='immagineinlinea' src='../immagini/feedback_ok.gif' alt='"+messaggiofeedback[28]+"'></label><input type='text' tabindex='"+tabindice+"' id='test_"+codicetest+"' size='"+test[codicetest].rispostaesatta.length+"' value=\""+test[codicetest].rispostaitem+"\">");
			inseriscirisposta(pagina,contatore);
		break;
	}
	tabindice++;
	document.write("<a href='#' tabindex='"+tabindice+"' onClick='inseriscirisposta(\""+pagina+"\",\""+contatore+"\");return false' onKeyPress='inseriscirisposta(\""+pagina+"\",\""+contatore+"\");return false'>");
	document.write("<img class='immagineinlinea' onMouseOver=\"roll(this,'verifica2')\" onMouseOut=\"noroll(this,'verifica2')\" src='../immagini/pulsante_verifica2.gif' alt='Controlla'>");
	document.write("</a><br>");
}

function inseriscirisposta(pagina,contatore){
	var casella = 0;
	var codicetest = pagina+"_"+contatore;
	var numerocaselle = cruciverba[pagina].larghezza * cruciverba[pagina].altezza;
	var spostamento = 1;
	test[codicetest].rispostaitem = document.getElementById("test_"+codicetest).value.toUpperCase();
	if (test[codicetest].rispostaitem != "")
		test[codicetest].rispostaitem = eliminaspazi(test[codicetest].rispostaitem);
	for(var casellainiziale=1; casellainiziale<numerocaselle+1; casellainiziale++){
		if (cruciverba[pagina].caselle[casellainiziale] == test[codicetest].opzioni)
			break;
	}
	if (test[codicetest].direzione == 1)
		spostamento = cruciverba[pagina].larghezza;
	for (var i=0; i<test[codicetest].rispostaesatta.length; i++){
		casella = casellainiziale + i * spostamento;
		document.getElementById("casella_"+pagina+"_"+(casella)).value = test[codicetest].rispostaitem.charAt(i);
	}
}

function eliminacampi(testo){
	while (testo.length > 0 && testo.charAt(testo.length-1) == "|"){
		testo = testo.slice(0,testo.length-1);
	}
	return testo;
}

/* -- NAVIGAZIONE -- */
function studio(){ // accede al tutoriale in funzione dell'errore
	if (puntatorestack != ""){
		if (nodi[tutorialeattivo].visitato == 2){
			nodi[tutorialeattivo].visitato = 4;
			if (nodi[tutorialeattivo].tutorialeprincipale != "")
				nodi[nodi[tutorialeattivo].tutorialeprincipale].visitato = 4;
			inviamessaggio("",tutorialeattivo);
		}
		indietrohistory();
		return;
	}
	if (nodi[tutorialeattivo].visitato == 2){
		nodi[tutorialeattivo].visitato = 4;
		if (nodi[tutorialeattivo].tutorialeprincipale != "")
			nodi[nodi[tutorialeattivo].tutorialeprincipale].visitato = 4;
		inviamessaggio("",tutorialeattivo);
		if (tutorialeerrore != "")
			tutoriale(tutorialeerrore,1);
		else
			tutoriale(nodi[tutorialeattivo].tutorialetest,1);
	}
	else
		tutoriale(nodi[tutorialeattivo].tutorialetest,1);
}

function azzera(){ // azzera punteggi e segnalibro
	init_bookmark = "";
	punteggio = 0;
	var contatore = 1;
	var nomepagina = new String;
	var testazzera = new String;
	for(var i=0;i < successione[0].length;i++){
		nomepagina = successione[0][i];
		nodi[nomepagina].visitato = 0;
		inviamessaggio("",nomepagina);
		if (nodi[nomepagina].tipo == 2){
			while (document.getElementById("test_"+nomepagina+"_"+contatore)){
				testazzera = nomepagina+"_"+contatore;
				test[testazzera].status = 0;
				test[testazzera].rispostaitem = "";
				test[testazzera].risultato = 0;
				if (test[testazzera].tipoitem == 1 || test[testazzera].tipoitem == 0){
					for(var i=1;i < document.getElementById("test_"+testazzera).elements.length;i++){
						document.getElementById("testimm"+i+"_"+testazzera).src = "../immagini/vuoto.gif";
						document.getElementById("testimm"+i+"_"+testazzera).alt = "";
					}
				}
				else{
					document.getElementById("testimm_"+testazzera).src = "../immagini/vuoto.gif";
					document.getElementById("testimm_"+testazzera).alt = "";
				}
				contatore++;
			}
		}
	}
}

/* -- VERIFICA ESITO -- */
function verificatest(){ // verifica test
	tutorialeerrore = "";
	var contatore = 1;
	var casella = 0;
	var numerocaselle = 0;
	var spostamento = 0;
	var risposte = new String;
	var tipoerrore = 0;
	var messaggioerrore = new String;
	var testattivo = new String;
	var messaggi = new Array;
	var tutoriali = new Array;
	var risposteesatte = new Array;
	switch (nodi[tutorialeattivo].visitato){
		default:
			while (document.getElementById("test_"+tutorialeattivo+"_"+contatore)){
				testattivo = tutorialeattivo+"_"+contatore;
				if (test[testattivo].status == 0){
					switch (test[testattivo].tipoitem){
						case 1: // domande a risposta chiusa
							risposte = test[testattivo].opzioni.split("|");
							messaggi = test[testattivo].messaggioitem.split("|");
							tutoriali = test[testattivo].tutorialeitem.split("|");
							for(var i=1; i<risposte.length+1; i++){
								if (document.getElementById("test"+i+"_"+testattivo).checked == true){
									test[testattivo].rispostaitem = i;
									if (i == test[testattivo].rispostaesatta){ // esatta
										test[testattivo].risultato = 2;
										document.getElementById("testimm"+i+"_"+testattivo).src = "../immagini/feedback_ok.gif";
										document.getElementById("testimm"+i+"_"+testattivo).alt = messaggiofeedback[28];
									}
									else{ // errore
										test[testattivo].risultato = 1;
										if (tipoerrore == 0){
											if (tutoriali.length > 1 && tutoriali[i-1])
												tutorialeerrore = tutoriali[i-1];
											else
												tutorialeerrore = tutoriali[0];
											if (messaggi.length > 1 && messaggi[i-1])
												messaggioerrore = messaggi[i-1];
											else
												messaggioerrore = messaggi[0];
										}
									}
								}
								else{
									document.getElementById("testimm"+i+"_"+testattivo).src = "../immagini/vuoto.gif";
									document.getElementById("testimm"+i+"_"+testattivo).alt = "";
								}
							}
						break;
						case 2: // domande a scelta multipla
							risposte = test[testattivo].opzioni.split("|");
							messaggi = test[testattivo].messaggioitem.split("|");
							tutoriali = test[testattivo].tutorialeitem.split("|");
							risposteesatte = test[testattivo].rispostaesatta.split("|");
							test[testattivo].rispostaitem = "";
							for(var i=1; i<risposte.length+1; i++){
								if (document.getElementById("test"+i+"_"+testattivo).checked == true){
									test[testattivo].risultato = 2;
									test[testattivo].rispostaitem = test[testattivo].rispostaitem + "1";
								}
								else{
									test[testattivo].rispostaitem = test[testattivo].rispostaitem + "0";
								}
								if (i < risposte.length)
									test[testattivo].rispostaitem = test[testattivo].rispostaitem + "|";
							}
							if (test[testattivo].risultato == 2){
								for(var i=1; i<risposte.length+1; i++){
									if ((document.getElementById("test"+i+"_"+testattivo).checked == false && risposteesatte[i-1] == "1") || (document.getElementById("test"+i+"_"+testattivo).checked == true && risposteesatte[i-1] == "0")){
										test[testattivo].risultato = 1; // errore
										if (tipoerrore == 0 && messaggioerrore == ""){
											if (tutoriali.length > 1 && tutoriali[i-1])
												tutorialeerrore = tutoriali[i-1];
											else
												tutorialeerrore = tutoriali[0];
											if (messaggi.length > 1 && messaggi[i-1])
												messaggioerrore = messaggi[i-1];
											else
												messaggioerrore = messaggi[0];
										}
									}
								}
							}
							if (test[testattivo].risultato == 2){
								document.getElementById("testimm_"+testattivo).src = "../immagini/feedback_ok.gif";
								document.getElementById("testimm_"+testattivo).alt = messaggiofeedback[28];
							}
						break;
						case 3: // domande con completamento di frasi
							risposteesatte = test[testattivo].rispostaesatta.split("|");
							test[testattivo].rispostaitem = document.getElementById("test_"+testattivo).value;
							if (test[testattivo].rispostaitem != ""){
								test[testattivo].rispostaitem = eliminaspazi(test[testattivo].rispostaitem);
								document.getElementById("test_"+testattivo).value = test[testattivo].rispostaitem;
								for(var r=0; r<risposteesatte.length; r++){
									if (test[testattivo].rispostaitem == risposteesatte[r]){
										test[testattivo].risultato = 2;
										break;
									}
								}
								if (test[testattivo].risultato == 2){ // esatta
									document.getElementById("testimm_"+testattivo).src = "../immagini/feedback_ok.gif";
									document.getElementById("testimm_"+testattivo).alt = messaggiofeedback[28];
								}
								else{ // errore
									test[testattivo].risultato = 1;
									if (tipoerrore == 0){
										messaggioerrore = test[testattivo].messaggioitem;
										tutorialeerrore = test[testattivo].tutorialeitem;
									}
								}
							}
						break;
						case 4: // domande con selezione di opzioni
							messaggi = test[testattivo].messaggioitem.split("|");
							tutoriali = test[testattivo].tutorialeitem.split("|");
							test[testattivo].rispostaitem = document.getElementById("test_"+testattivo).value;
							if (test[testattivo].rispostaitem != ""){
								if (test[testattivo].rispostaitem == test[testattivo].rispostaesatta){ // esatta
									test[testattivo].risultato = 2;
									document.getElementById("testimm_"+testattivo).src = "../immagini/feedback_ok.gif";
									document.getElementById("testimm_"+testattivo).alt = messaggiofeedback[28];
								}
								else{ // errore
									test[testattivo].risultato = 1;
									i = 1;
									while(document.getElementById("test"+i+"_"+testattivo)){
										if (document.getElementById("test"+i+"_"+testattivo).value == test[testattivo].rispostaitem){
											if (tipoerrore == 0){
												if (tutoriali.length > 1 && tutoriali[i-1])
													tutorialeerrore = tutoriali[i-1];
												else
													tutorialeerrore = tutoriali[0];
												if (messaggi.length > 1 && messaggi[i-1])
													messaggioerrore = messaggi[i-1];
												else
													messaggioerrore = messaggi[0];
											}
											break;
										}
									i++;
									}
								}
							}
						break;
						case 5: // test drag & drop
							test[testattivo].risultato = Number(document.getElementById(tutorialeattivo+"_"+test[testattivo].identificatoremedia).GetVariable("_root.flagrispostaesatta"));
							if (test[testattivo].risultato == 2){ // esatta
									document.getElementById("testimm_"+testattivo).src = "../immagini/feedback_ok.gif";
									document.getElementById("testimm_"+testattivo).alt = messaggiofeedback[28];
							}
							else if (test[testattivo].risultato == 1 && tipoerrore == 0){
								messaggioerrore = test[testattivo].messaggioitem;
								tutorialeerrore = test[testattivo].tutorialeitem;
							}
						break;
						case 6: // cruciverba
							casella = 0;
							numerocaselle = cruciverba[tutorialeattivo].larghezza * cruciverba[tutorialeattivo].altezza;
							spostamento = 1;
							for(var casellainiziale=1; casellainiziale<numerocaselle+1; casellainiziale++){
								if (cruciverba[tutorialeattivo].caselle[casellainiziale] == test[testattivo].opzioni)
									break;
							}
							if (test[testattivo].direzione == 1)
								spostamento = cruciverba[tutorialeattivo].larghezza;
							test[testattivo].rispostaitem = "";
							for (var i=0; i<test[testattivo].rispostaesatta.length; i++){
								casella = casellainiziale + i * spostamento;
								test[testattivo].rispostaitem = test[testattivo].rispostaitem + document.getElementById("casella_"+tutorialeattivo+"_"+(casella)).value;
							}
							if (test[testattivo].rispostaitem != ""){
								document.getElementById("test_"+testattivo).value = test[testattivo].rispostaitem;
								if (test[testattivo].rispostaitem == test[testattivo].rispostaesatta.toUpperCase()){ // esatta
									test[testattivo].risultato = 2;
									document.getElementById("testimm_"+testattivo).src = "../immagini/feedback_ok.gif";
									document.getElementById("testimm_"+testattivo).alt = messaggiofeedback[28];
								}
								else{ // errore
									test[testattivo].risultato = 1;
									if (tipoerrore == 0){
										if (test[testattivo].direzione == 0)
											messaggioerrore = test[testattivo].opzioni+" orizzontale: "+test[testattivo].messaggioitem;
										tutorialeerrore = test[testattivo].tutorialeitem;
									}
								}
							}
						break;
					}
				}
				if (tipoerrore == 0){
					if (test[testattivo].risultato == 0) // mancata risposta al test 
						tipoerrore = 1;
					else if (test[testattivo].risultato == 1) // errore 
						tipoerrore = 2;
				}
				if (test[testattivo].risultato == 2)
					test[testattivo].status = 1;
				contatore++;
			}
			feedback(tipoerrore,messaggioerrore);
			break;
		case 2:
			if (modofruizione == "3")
				inviamessaggio(messaggiofeedback[16],tutorialeattivo,1);
			else
				inviamessaggio(messaggiofeedback[17],tutorialeattivo,1);
		break;
		case 3:
			inviamessaggio(messaggiofeedback[16],tutorialeattivo,1);
		break;
		case 5:
			inviamessaggio(messaggiofeedback[27],tutorialeattivo,1);
		break;
	}
}

function feedback(tipo,messaggio){ // gestione esito della pagina
	var feedback = new Number;
	var punti = nodi[tutorialeattivo].punti;
	switch (tipo){
		case 0: // nessun errore
			nodi[tutorialeattivo].visitato = 3; // impostazione nodo visitato
			if (nodi[tutorialeattivo].tutorialeprincipale != "")
				nodi[nodi[tutorialeattivo].tutorialeprincipale].visitato = 3;
			if (nodi[tutorialeattivo].tutorialealternativo != "")
				nodi[nodi[tutorialeattivo].tutorialealternativo].visitato = 3;
			if (modofruizione == 1) // impostazione tipo di feedback
				feedback = 2;
			else if (modofruizione == 2)
				avviaanimazionegioco(20);
			if (nodi[tutorialeattivo].messaggiotestesatto) // invio messaggi
				inviamessaggio(nodi[tutorialeattivo].messaggiotestesatto,tutorialeattivo,feedback);
			else
				inviamessaggio(messaggiotest[0],tutorialeattivo,feedback);
			punteggio = punteggio + punti; // gestione punteggi
		break
		case 1: // mancata risposta
			inviamessaggio(messaggiofeedback[18],tutorialeattivo,1); // messaggio di mancata risposta
		break
		case 2: // errori
			if (modofruizione == 1) // impostazione tipo di feedback
				feedback = 3;
			else if (modofruizione == 2)
				avviaanimazionegioco(21);
			if (messaggio) // messaggio di errore
				inviamessaggio(messaggio,tutorialeattivo,feedback);
			else if (nodi[tutorialeattivo].messaggiotesterrore)
				inviamessaggio(nodi[tutorialeattivo].messaggiotesterrore,tutorialeattivo,feedback);
			else
				inviamessaggio(messaggiotest[1],tutorialeattivo,feedback);
			nodi[tutorialeattivo].tentativi++; // gestione pulsante soluzioni
			if (nodi[tutorialeattivo].tentativi == visualizzasoluzioni && visualizzasoluzioni > 0)
				document.getElementById("pulsantesoluzioni_"+tutorialeattivo).style.visibility="visible";
			nodi[tutorialeattivo].visitato = 2; // impostazione nodo visitato
			if (nodi[tutorialeattivo].tutorialeprincipale != "")
				nodi[nodi[tutorialeattivo].tutorialeprincipale].visitato = 2;
			if (modofruizione != "3" && puntinegativi == 1) // gestione punteggi
				punteggio = punteggio - punti;
		break
	}
	document.getElementById("punteggio_"+tutorialeattivo).value = punteggio+" su "+punteggiomassimo;
}

function mostrasoluzioni(tipotest,rispostaesatta){ // presentazione soluzioni test
	if (nodi[tutorialeattivo].visitato != 2 && nodi[tutorialeattivo].visitato != 4)
		return;
	inviamessaggio(messaggiofeedback[26],tutorialeattivo,1);
	nodi[tutorialeattivo].visitato = 5;
	if (nodi[tutorialeattivo].tutorialeprincipale != "")
		nodi[nodi[tutorialeattivo].tutorialeprincipale].visitato = 5;
	var contatore = 1;
	var risposteesatte = new String;
	while (document.getElementById("test_"+tutorialeattivo+"_"+contatore)){
		var testattivo = tutorialeattivo+"_"+contatore;
		switch (test[testattivo].tipoitem){
			case 1: // domande a risposta chiusa
				if (test[testattivo].risultato == 2){
					document.getElementById("testimm"+test[testattivo].rispostaitem+"_"+testattivo).src = "../immagini/feedback_ok.gif";
					document.getElementById("testimm"+test[testattivo].rispostaitem+"_"+testattivo).alt = messaggiofeedback[28];
					document.getElementById("testimm"+test[testattivo].rispostaitem+"_"+testattivo).title = messaggiofeedback[28];
				}
				else{
					document.getElementById("testimm"+test[testattivo].rispostaitem+"_"+testattivo).src = "../immagini/feedback_ko.gif";
					document.getElementById("testimm"+test[testattivo].rispostaitem+"_"+testattivo).alt = messaggiofeedback[29];
					document.getElementById("testimm"+test[testattivo].rispostaitem+"_"+testattivo).title = messaggiofeedback[29];
					document.getElementById("testimm"+test[testattivo].rispostaesatta+"_"+testattivo).src = "../immagini/feedback_ok.gif";
					document.getElementById("testimm"+test[testattivo].rispostaesatta+"_"+testattivo).alt = messaggiofeedback[30];
					document.getElementById("testimm"+test[testattivo].rispostaesatta+"_"+testattivo).title = messaggiofeedback[30];
				}
			break;

			case 2: // domande a scelta multipla
				risposteesatte = test[testattivo].rispostaesatta.split("|");
				for(var i=1;i < document.getElementById("test_"+testattivo).elements.length;i++){
					if ((document.getElementById("test"+i+"_"+testattivo).checked == true && risposteesatte[i-1] == "1") || (document.getElementById("test"+i+"_"+testattivo).checked == false && risposteesatte[i-1] == "0")){

						document.getElementById("testimm"+i+"_"+testattivo).src = "../immagini/feedback_ok.gif";
						document.getElementById("testimm"+i+"_"+testattivo).alt = messaggiofeedback[28];
						document.getElementById("testimm"+i+"_"+testattivo).title = messaggiofeedback[28];
					}
					else{
						document.getElementById("testimm"+i+"_"+testattivo).src = "../immagini/feedback_ko.gif";
						document.getElementById("testimm"+i+"_"+testattivo).alt = messaggiofeedback[29];
						document.getElementById("testimm"+i+"_"+testattivo).title = messaggiofeedback[29];
					}
				}
			break;
			case 3: // domande con completamento di frasi
			case 4: // domande con selezione di opzioni
			case 5: // test drag & drop
			case 6: // cruciverba
				if (test[testattivo].risultato == 2){
					document.getElementById("testimm_"+testattivo).src = "../immagini/feedback_ok.gif";
					document.getElementById("testimm_"+testattivo).alt = messaggiofeedback[28];
					document.getElementById("testimm_"+testattivo).title = messaggiofeedback[28];
				}
				else{
					document.getElementById("testimm_"+testattivo).src = "../immagini/feedback_ko.gif";
					document.getElementById("testimm_"+testattivo).alt = messaggiofeedback[31] + test[testattivo].rispostaesatta;
					document.getElementById("testimm_"+testattivo).title = messaggiofeedback[31] + test[testattivo].rispostaesatta;
				}
			break;
		}
		contatore++
	}
}

function eliminaspazi(testo){
	var nuovotesto = new String;
	for(var i=0; i<testo.length; i++){
		if (testo.charAt(i) != " " || (i > 0 && testo.charAt(i-1) != " ") ){
			nuovotesto = nuovotesto + testo.charAt(i)
		}
	}
	if (nuovotesto.charAt(nuovotesto.length-1) == " ")
		nuovotesto =  nuovotesto.slice(0,nuovotesto.length-1);
	return nuovotesto;
}

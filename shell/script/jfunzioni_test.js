/* --- SHELL ACCESSIBILE: FUNZIONI DI GESTIONE TEST --- */

/* -- VISUALIZZAZIONE -- */
function inviapunteggio(pagina){ // invia i punteggi
	document.getElementById("punteggio_"+pagina).value = punteggio;
	var classepunteggio = (punteggiomassimo - punteggio)/(punteggiomassimo / 4);
	if (classepunteggio > 4){
		document.getElementById("feedback_"+pagina).src = "feed_01.gif";
		document.getElementById("feedback_"+pagina).alt = messaggiofeedback[19];
	}
	else if (classepunteggio > 3){
		document.getElementById("feedback_"+pagina).src = "feed_02.gif";
		document.getElementById("feedback_"+pagina).alt = messaggiofeedback[20];
	}
	else if (classepunteggio > 2){
		document.getElementById("feedback_"+pagina).src = "feed_03.gif";
		document.getElementById("feedback_"+pagina).alt = messaggiofeedback[21];
	}
	else if (classepunteggio > 1){
		document.getElementById("feedback_"+pagina).src = "feed_04.gif";
		document.getElementById("feedback_"+pagina).alt = messaggiofeedback[22];
	}
	else{
		document.getElementById("feedback_"+pagina).src = "feed_05.gif";
		document.getElementById("feedback_"+pagina).alt = messaggiofeedback[23];
	}
}

/* -- NAVIGAZIONE -- */
function studio(tutorialetest){ // accede al tutoriale in funzione dell'errore
	if (nodovisitato[tutorialeattivo] == 2){
		nodovisitato[tutorialeattivo] = 4;
		if (tutorialeprincipale[tutorialeattivo] != null)
			nodovisitato[tutorialeprincipale[tutorialeattivo]] = 4;
		inviamessaggio("",tutorialeattivo);
		if (tutorialetest && tutorialetest[numeroerrore])
			tutoriale(tutorialetest[numeroerrore],1);
		else
			tutoriale(tutorialetest[0],1);
	}
	else
		tutoriale(tutorialetest[0],1);
}

function studioanimazione(animazione){ // accede al tutoriale in funzione dell'errore
	if (nodovisitato[tutorialeattivo] == 2){
		nodovisitato[tutorialeattivo] = 4;
		if (tutorialeprincipale[tutorialeattivo] !=null)
			nodovisitato[tutorialeprincipale[tutorialeattivo]] = 4;
		inviamessaggio("",tutorialeattivo);
	}
	tutoriale(animazione,1);
}

function azzera(){ // azzera punteggi e segnalibro
	init_bookmark = "";
	punteggio = 0;
	var contatore = 1;
	while (nodovisitato[contatore]){
		nodovisitato[contatore] = 0;
		inviamessaggio("",contatore);
		contatore++;
	}
}

/* -- ESERCITAZIONI/TEST -- */
function verificatest(tipotest,rispostaesatta,messaggio){ // verifica test
	numeroerrore = 0;
	var contatore = 1;
	var risposta = 0;
	switch (nodovisitato[tutorialeattivo]){
		default:
			switch (tipotest){
				case 1: // domande a risposta chiusa
					while (document.getElementById("test_"+tutorialeattivo).elements[contatore]){
						if (document.getElementById("test_"+tutorialeattivo).elements[contatore].checked == true){
							if (contatore == rispostaesatta[1])
								risposta = 2;
							else{
								risposta = 1;
								numeroerrore = contatore;
							}
						break;
						}
					contatore++;
					}
					break;
				case 2: // domande a scelta multipla
					while (document.getElementById("test_"+tutorialeattivo).elements[contatore]){
						if (document.getElementById("test_"+tutorialeattivo).elements[contatore].checked == true)
							risposta = 2;
						contatore++;
					}
					if (risposta == 2){
						contatore = 0;
						while (document.getElementById("test_"+tutorialeattivo).elements[contatore]){
							if ((document.getElementById("test_"+tutorialeattivo).elements[contatore].checked == false && rispostaesatta[contatore] > 0) || (document.getElementById("test_"+tutorialeattivo).elements[contatore].checked == true && rispostaesatta[contatore] == 0)){
							risposta = 1;
							numeroerrore = contatore;
							break;
							}
						contatore++;
						}
					}
					break;
				case 3: // domande con completamento di frasi
					while (document.getElementById("test_"+tutorialeattivo).elements[contatore]){
						if (document.getElementById("test_"+tutorialeattivo).elements[contatore].value != "")
							risposta = 2;
						contatore++;
					}
					if (risposta == 2){
						contatore = 1;
						while (document.getElementById("test_"+tutorialeattivo).elements[contatore]){
							if (document.getElementById("test_"+tutorialeattivo).elements[contatore].value != rispostaesatta[contatore]){
								risposta = 1;
								numeroerrore = contatore;
								break;
							}
						contatore++;
						}
					}
					break;
				case 4: // domande multiple a risposta chiusa
					var contatore1 = 1;
					var risposta1 = 0;
					var sottopagina = "test"+contatore1+"_"+tutorialeattivo;
					while (document.getElementById(sottopagina)){
						while (document.getElementById(sottopagina).elements[contatore]){
							if (document.getElementById(sottopagina).elements[contatore].checked == true){
								if (contatore == rispostaesatta[contatore1])
									risposta = 2;
								else{
									risposta = 1;
									numeroerrore = contatore1;
								}
							risposta1 = 1;
							break;
							}
							contatore++;
						}
						if (risposta1 == 0){
							risposta = 1;
							numeroerrore = contatore1;
						}
						if (risposta == 1)
							break
						contatore = 1;
						contatore1++;
						risposta1 = 0;
						sottopagina = "test"+contatore1+"_"+tutorialeattivo;
					}
					break;
				case 5: // domande con selezione di opzioni
					while (document.getElementById("test_"+tutorialeattivo).elements[contatore]){
						if (document.getElementById("test_"+tutorialeattivo).elements[contatore].value != "")
							risposta = 2;
						contatore++;
					}
					if (risposta == 2){
						contatore = 1;
						while (document.getElementById("test_"+tutorialeattivo).elements[contatore]){
							if (document.getElementById("test_"+tutorialeattivo).elements[contatore].value != rispostaesatta[contatore]){
								risposta = 1;
								numeroerrore = contatore;
								break;
							}
						contatore++;
						}
					}
					break;
				case 6: // drag and drop in flash
					var medium = mediumblocco[tutorialeattivo].split(".");
					risposta = Number(document.getElementById(medium[0]+"_"+tutorialeattivo).GetVariable("_root.flagrispostaesatta"));
					if (risposta == 1)
						numeroerrore = 1;
					break;
			}
			rispostatest(risposta,messaggio);
			break;
		case 2:
			if (tipolo == "c")
				inviamessaggio(messaggiofeedback[16],tutorialeattivo,"messaggio");
			else
				inviamessaggio(messaggiofeedback[17],tutorialeattivo,"messaggio");
			break;
		case 3:
			inviamessaggio(messaggiofeedback[16],tutorialeattivo,"messaggio");
			break;
	}
}

function rispostatest(risposta,messaggio){
	if (tutorialeprincipale[tutorialeattivo] != null)
		var punti = puntitutoriale[tutorialeprincipale[tutorialeattivo]];
	else
		var punti = puntitutoriale[tutorialeattivo];
	switch (risposta){
		case 0:
			inviamessaggio(messaggiofeedback[18],tutorialeattivo,"messaggio");
			break;
		case 1:
			nodovisitato[tutorialeattivo] = 2;
			if (tutorialeprincipale[tutorialeattivo] != null)
				nodovisitato[tutorialeprincipale[tutorialeattivo]] = 2;
			if (messaggio[numeroerrore])
				var testomessaggio = messaggio[numeroerrore];
			else
				var testomessaggio = messaggio[1]
			inviamessaggio(testomessaggio,tutorialeattivo,"ko");
			punteggio = punteggio - punti;
			break;
		case 2:
			nodovisitato[tutorialeattivo] = 3;
			if (tutorialeprincipale[tutorialeattivo] != null)
				nodovisitato[tutorialeprincipale[tutorialeattivo]] = 3;
			inviamessaggio(messaggio[0],tutorialeattivo,"ok");
			punteggio = punteggio + punti;
			break;
		}
	inviapunteggio(tutorialeattivo);
}

/* -- ESERCITAZIONI CRUCIVERBA -- */
function visualizzacruciverba(pagina,caselle,altezza,definizione,nomecaselle,nomedefinizione,nometutoriale,nomemessaggio,nomeflag){
	var numerocaselle = caselle[0] * altezza;
	var contatore = 1;
	var contatore1 = 1;
	var stringa = new String;
	var stringaid = new String;
	var cambiodefinizioni = 0;
	var tabindice = 0;
	document.write("<div class='areadefinizioni'>");// definizioni del cruciverba
	document.write("<form id='test_"+pagina+"'' action=''>");
	document.write("<fieldset><legend class='domanda'>Orizzontali</legend>");
	for (contatore=1; contatore<definizione.length; contatore++){
		if (definizione[contatore][1]=='v' && cambiodefinizioni==0){
			document.write("</fieldset><fieldset><legend class='domanda'>Verticali</legend>");
			cambiodefinizioni = 1;
		}
		stringaid = "test"+contatore+"_"+pagina;
		document.write("<label for='"+stringaid+"'>"+definizione[contatore][0]+". "+definizione[contatore][2]+"</label>");
		stringa = definizione[contatore][3];
		tabindice++;
		document.write(" <input type='text' tabindex='"+tabindice+"' id='"+stringaid+"' size='"+stringa.length+"'>");
		tabindice++;
		stringa="'verificacruciverba(\""+stringaid+"\","+nomedefinizione+","+contatore+","+nomemessaggio+","+nomeflag+","+nomecaselle+");return false'";
		document.write("<a href='#' tabindex='+tabindice+' onClick="+stringa+" onKeyPress="+stringa+">");
		document.write("<img class='pulsanteverifica2' onMouseOver=\"roll(this,'verifica2')\" onMouseOut=\"noroll(this,'verifica2')\" src='../immagini/pulsante_verifica2.gif' alt='Controlla'>");
		document.write("</a><br>");
	}
	document.write("</fieldset></form></div>");

	document.write("<div class='areacruciverba'>");// schema del cruciverba
	document.write("<table class='cruciverba' cellspacing='0' summary='Schema del cruciverba'><tr>");
	contatore = 1;
	while (contatore <= numerocaselle){
		document.write("<td><div class='casella'>");
		if (caselle[contatore] == -1)
			document.write("<img class='casellanera' src='../immagini/cruci_nera.gif' alt='Casella nera'>");
		else{
			if (caselle[contatore]){
				for (contatore1=1; contatore1<definizione.length; contatore1++){
					if (definizione[contatore1][0] == caselle[contatore]){
						definizione[contatore1][4] = contatore;
					}
				}
				document.write("<img class='immaginecasella' src='../immagini/cruci_"+caselle[contatore]+".gif' alt='Casella "+caselle[contatore]+"'>");
			}
			document.write("<input class='crucireadonly' id='casella_"+pagina+"_"+contatore+"' readonly size='1' maxlength='1'></div>");
		}
		document.write("</div>");
		if ((contatore)%caselle[0] == 0)
			document.write("</tr><tr>");
		contatore++;
	}
document.write("</tr></table></div>");
}

function verificacruciverba(domanda,definizione,numerorisposta,messaggio,flagrisposte,caselle){
	var testorisposta = document.getElementById(domanda).value;
	testorisposta = testorisposta.toUpperCase();
	var contatore = 0;
	var spostamento = 1;
	var casellainiziale = definizione[numerorisposta][4];
	if (flagrisposte[numerorisposta] == 2){
		inviamessaggio(messaggiofeedback[16],tutorialeattivo,"messaggio");
		return;
	}
	if (definizione[numerorisposta][1] == 'v')
		spostamento = caselle[0];
	if (testorisposta == definizione[numerorisposta][3].toUpperCase()){
		flagrisposte[numerorisposta] = 2;
		while (testorisposta.charAt(contatore)){
			casella = casellainiziale + contatore * spostamento;
			document.getElementById("casella_"+tutorialeattivo+"_"+(casella)).value = testorisposta.charAt(contatore);
			contatore++;
		}
	}
	else if(testorisposta !=""){
		numeroerrore = numerorisposta;
		flagrisposte[numerorisposta] = 1;
	}
	else
		(flagrisposte[numerorisposta]) = 0;
	rispostatest(flagrisposte[numerorisposta],messaggio);
}

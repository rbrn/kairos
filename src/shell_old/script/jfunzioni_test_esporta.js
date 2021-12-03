/* --- SHELL ACCESSIBILE: FUNZIONI DI GESTIONE TEST --- */

/* -- VISUALIZZAZIONE -- */
function visualizzatest(pagina){ // visualizza messaggi e punteggi
	document.write("<div class='areamessaggio'>");
	document.write("<label class='nascosto' for='messaggio"+pagina+"'>Messaggio:</label>");
	document.write("<input class='messaggio' id='messaggio"+pagina+"' readonly size='70' maxlength='70'>");
	document.write("</div>");
	document.write("<div class='areapunteggio'>");
	document.write("<div class='intestazionepunteggio'><label for='punteggio"+pagina+"'>Punti</label></div>");
	document.write("<input class='punteggio' id='punteggio"+pagina+"' readonly size='2' maxlength='2'><br>");
	document.write("<span class='punteggiobase'>su "+punteggiomassimo+"</span>");
	document.write("</div>");
	document.write("<p><img id='feedback"+pagina+"' class='feedbackpunteggio'>");
}

function inviapunteggio(pagina){ // invia i punteggi
	document.getElementById("punteggio"+pagina).value = punteggio;
	var classepunteggio = (punteggiomassimo - punteggio)/(punteggiomassimo / 4);
	if (classepunteggio > 4){
		document.getElementById("feedback"+pagina).src = "shell/img/feed_01.jpg";
		document.getElementById("feedback"+pagina).alt = "Andiamo male: la missione è in pericolo";
	}
	else if (classepunteggio > 3){
		document.getElementById("feedback"+pagina).src = "shell/img/feed_02.jpg";
		document.getElementById("feedback"+pagina).alt = "Prestazione ancora modesta: fai attenzione";
	}
	else if (classepunteggio > 2){
		document.getElementById("feedback"+pagina).src = "shell/img/feed_03.jpg";
		document.getElementById("feedback"+pagina).alt = "Il successo è ancora lontano";
	}
	else if (classepunteggio > 1){
		document.getElementById("feedback"+pagina).src = "shell/img/feed_04.jpg";
		document.getElementById("feedback"+pagina).alt = "La situazione è incoraggiante: continua così";
	}
	else{
		document.getElementById("feedback"+pagina).src = "shell/img/feed_05.jpg";
		document.getElementById("feedback"+pagina).alt = "Prestazione esaltante: il successo è vicino";
	}
}		

/* -- AZZERAMENTO PUNTEGGI -- */
function azzera(){ // azzera punteggi e segnalibro
	init_bookmark = 0;
	punteggio = 0;
}

/* -- NAVIGAZIONE -- */
function avantitest(pagina,destinazione,destinazione2){ // accede alla pagina tutoriale o a quella alternativa
	if (destinazione2 && (multimedia == 0 || plugin_fl ==0))
		destinazione = destinazione2;
	if (nodovisitato[pagina] < 3)
		inviamessaggio("Prima rispondi bene!",pagina,"audio_messaggio");
	else if (punteggio > punteggiosoglia || tipolo == "a"){
		switch (tipotutoriale[destinazione]){
			case 4: // riepilogo
				document.getElementById("punteggio"+destinazione).value = punteggio;
				var classepunteggio = (punteggiomassimo - punteggio)/(punteggiomassimo / 4);
				if (classepunteggio > 4){
					document.getElementById("feedback"+destinazione).src = "shell/img/riepilogo_01.jpg";
					document.getElementById("feedback"+destinazione).alt = "La missione è quasi fallita";
					inviamessaggio("Ce l'hai fatta per un pelo: la tua missione è quasi fallita.",destinazione);
				}
				else if (classepunteggio > 3){
					document.getElementById("feedback"+destinazione).src = "shell/img/riepilogo_02.jpg";
					document.getElementById("feedback"+destinazione).alt = "La prestazione è piuttosto modesta";
					inviamessaggio("Ce l'hai fatta, ma la tua prestazione è piuttosto modesta.",destinazione);
					}
				else if (classepunteggio > 2){
					document.getElementById("feedback"+destinazione).src = "shell/img/riepilogo_03.jpg";
					document.getElementById("feedback"+destinazione).alt = "Il successo è ancora lontano";
					inviamessaggio("Insomma... questa volta è andata così così.",destinazione);
				}
				else if (classepunteggio > 1){
					document.getElementById("feedback"+destinazione).src = "shell/img/riepilogo_04.jpg";
					document.getElementById("feedback"+destinazione).alt = "La prestazione è superiore alla media";
					inviamessaggio("Bene! Una prestazione superiore alla media.",destinazione);
				}
				else{
					document.getElementById("feedback"+destinazione).src = "shell/img/riepilogo_05.jpg";
					document.getElementById("feedback"+destinazione).alt = "La prestazione è esaltante";
					inviamessaggio("Splendido! Hai raggiunto il successo con una prestazione esaltante.",destinazione);
				}
				break
		}
		tutoriale(destinazione);
	}
	else {
		azzera();
		inviamessaggio("La tua missione è fallita. Ricomincia!",1,"ko");
		tutoriale(1);
	}
}

function studio(pagina,destinazione,tutorialetest){ // accede al tutoriale in funzione dell'errore
	if (nodovisitato[pagina] == 2){
		nodovisitato[pagina] = 1;
		inviamessaggio("",pagina);
		if (tutorialetest[numeroerrore])
			tutoriale(tutorialetest[numeroerrore]);
		else
			tutoriale(destinazione);
	}
	else
		tutoriale(destinazione);
}

/* -- ESERCITAZIONI/TEST -- */
function verificatest(tipotest,pagina,rispostaesatta,punti,messaggiook,messaggioko,casesensitive){ // verifica test
	numeroerrore = -1;
	var contatore = 1;
	var risposta = 0;
	if (!messaggiook)
		messaggiook = "Risposta esatta! Vai avanti";
	if (!messaggioko)
		messaggioko = "Hai sbagliato! Studia!!";
	switch (nodovisitato[pagina]){
		case 1:
			switch (tipotest){
				case 1: // domande a risposta chiusa
					while (document.getElementById("test"+pagina).elements[contatore]){
						if (document.getElementById("test"+pagina).elements[contatore].checked == true){
							if (contatore == rispostaesatta)
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
					while (document.getElementById("test"+pagina).elements[contatore]){
						if (document.getElementById("test"+pagina).elements[contatore].checked == true)
							risposta = 2;
						contatore++;
					}
					if (risposta == 2){
						contatore = 0;
						while (document.getElementById("test"+pagina).elements[contatore]){
							if ((document.getElementById("test"+pagina).elements[contatore].checked == false && rispostaesatta[contatore] > 0) || (document.getElementById("test"+pagina).elements[contatore].checked == true && rispostaesatta[contatore] == 0)){
							risposta = 1;
							numeroerrore = contatore;
							break;
							}
						contatore++;
						}
					}
					break;
				case 3: // domande con completamento di frasi
					while (document.getElementById("test"+pagina).elements[contatore]){
						if (document.getElementById("test"+pagina).elements[contatore].value != "")
							risposta = 2;
						contatore++;
					}
					if (risposta == 2){
						contatore = 1;
						while (document.getElementById("test"+pagina).elements[contatore]){
							if (document.getElementById("test"+pagina).elements[contatore].value != rispostaesatta[contatore]){
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
					var sottopagina = pagina+"_"+contatore1;
					while (document.getElementById("test"+sottopagina)){
						while (document.getElementById("test"+sottopagina).elements[contatore]){
							if (document.getElementById("test"+sottopagina).elements[contatore].checked == true){
								if (contatore == rispostaesatta[contatore1])
									risposta = 2;
								else{
									risposta = 1;
									numeroerrore = contatore1;
									break;
								}
							}
							contatore++;
						}
						if (risposta == 1)
							break
						contatore = 1;
						contatore1++;
						sottopagina = pagina+"_"+contatore1;
					}
					break;
				case 5: // domande con selezione di opzioni
					while (document.getElementById("test"+pagina).elements[contatore]){
						if (document.getElementById("test"+pagina).elements[contatore].value != "")
							risposta = 2;
						contatore++;
					}
					if (risposta == 2){
						contatore = 1;
						while (document.getElementById("test"+pagina).elements[contatore]){
							if (document.getElementById("test"+pagina).elements[contatore].value != rispostaesatta[contatore]){
								risposta = 1;
								numeroerrore = contatore;
								break;
							}
						contatore++;
						}
					}
					break;
			}
			rispostatest(risposta,pagina,punti,messaggiook,messaggioko)
			break;
		case 2:
			inviamessaggio("Prima di ritentare, studia!",pagina,"audio_messaggio");
			break;
		case 3:
			inviamessaggio("Hai già risposto. Vai avanti.",pagina,"audio_messaggio");
			break;
	}
}

function rispostatest(risposta,pagina,punti,messaggiook,messaggioko){
	switch (risposta){
		case 0:
			inviamessaggio("Non hai ancora risposto!",pagina,"audio_messaggio");
			break;
		case 2:
			nodovisitato[pagina] = 3;
			inviamessaggio(messaggiook,pagina,"audio_ok");
			punteggio = punteggio + punti;
			break;
		case 1:
			nodovisitato[pagina] = 2;
			inviamessaggio(messaggioko,pagina,"audio_ko");
			punteggio = punteggio - punti;
			roll('studio',pagina);
			break;
		}
	inviapunteggio(pagina);
}

function VerificaTestDD(parametro){ // verifica test drag and drop in flash
	var parametri = parametro.split("-");
	var flagrisposta = parametri[0];
	var pagina = parametri[1];
	numeroerrore = -1;
	var punti = 1;
	var risposta = 0;
	var messaggiook = "Risposta esatta! Vai avanti";
	var messaggioko = "Hai sbagliato! Studia!!";
	switch (nodovisitato[pagina]){
		case 1:
			if (flagrisposta == 2){
				numeroerrore = 1;
				rispostatest(1,pagina,punti,messaggiook,messaggioko);
alert("flagrisposta:"+flagrisposta);
			}
			else
				rispostatest(2,pagina,punti,messaggiook,messaggioko);
			break;
		case 2:
			inviamessaggio("Prima di ritentare, studia!",pagina,"audio_messaggio");
			break;
		case 3:
			inviamessaggio("Hai già risposto. Vai avanti.",pagina,"audio_messaggio");
			break;
	}
}

function update_check(divName,pagina,max_risposte) {
	var div=document.getElementById(divName);
		
	var objCheckBoxes = div.getElementsByTagName('input');
	if(!objCheckBoxes)
		return;
	
	var countCheckBoxes = objCheckBoxes.length;
	if (countCheckBoxes) {
		var n_checked=0;
		for (var i = 0; i < countCheckBoxes; i++) {
			if (objCheckBoxes[i].checked) {
				n_checked++;
				if (n_checked>max_risposte) {
					var msg="massimo "+max_risposte+" risposte";
					inviamessaggio(msg,pagina,"audio_messaggio");
					objCheckBoxes[i].checked=false;
				}
			}
		}		
	}
}

function textCounter(field,counter,maxlimit,linecounter) {
	
	var fieldWidth =  parseInt(field.offsetWidth);
	var charcnt = field.value.length;        

	
	if (charcnt > maxlimit) { 
		field.value = field.value.substring(0, maxlimit);
	}

	else { 
	
	var percentage = parseInt(100 - (( maxlimit - charcnt) * 100)/maxlimit) ;
	var w=200;
	/*
	if (parseInt((fieldWidth*percentage)/100) > 20) {
		w=parseInt((fieldWidth*percentage)/100);
	};
	*/
	document.getElementById(counter).style.width =  w+"px";
	document.getElementById(counter).innerHTML="Caratteri: "+charcnt+" su max "+maxlimit
	
	setcolor(document.getElementById(counter),percentage,"background-color");
	}
}

function setcolor(obj,percentage,prop){
	obj.style[prop] = "rgb(80%,"+(100-percentage)+"%,"+(100-percentage)+"%)";
}
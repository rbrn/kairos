<?php
$path_img="skins/".$_REQUEST["lo_skin"];
?>
/* --- SHELL ACCESSIBILE: FUNZIONI DI GESTIONE TEST --- */

/* -- VISUALIZZAZIONE -- */
function inviapunteggio(pagina){ // invia i punteggi
	document.getElementById("punteggio_"+pagina).value = punteggio;
	var classepunteggio = (punteggiomassimo - punteggio)/(punteggiomassimo / 4);
	if (classepunteggio > 4){
		document.getElementById("feedback_"+pagina).src = "shell/<?php echo $path_img ?>/feed_01.gif";
		document.getElementById("feedback_"+pagina).alt = messaggiofeedback[19];
	}
	else if (classepunteggio > 3){
		document.getElementById("feedback_"+pagina).src = "shell/<?php echo $path_img ?>/feed_02.gif";
		document.getElementById("feedback_"+pagina).alt = messaggiofeedback[20];
	}
	else if (classepunteggio > 2){
		document.getElementById("feedback_"+pagina).src = "shell/<?php echo $path_img ?>/feed_03.gif";
		document.getElementById("feedback_"+pagina).alt = messaggiofeedback[21];
	}
	else if (classepunteggio > 1){
		document.getElementById("feedback_"+pagina).src = "shell/<?php echo $path_img ?>/feed_04.gif";
		document.getElementById("feedback_"+pagina).alt = messaggiofeedback[22];
	}
	else{
		document.getElementById("feedback_"+pagina).src = "shell/<?php echo $path_img ?>/feed_05.gif";
		document.getElementById("feedback_"+pagina).alt = messaggiofeedback[23];
	}
}

/* -- NAVIGAZIONE -- */
function avantitest(destinazione){ // accede alla pagina tutoriale
	switch (tipolo){
		case "a":
			if (nodovisitato[tutorialeattivo] == 3)
				tutoriale(destinazione);
			else
				inviamessaggio(messaggiofeedback[13],tutorialeattivo,"messaggio");
			break;
		case "b":
			if (nodovisitato[tutorialeattivo] < 3)
				inviamessaggio(messaggiofeedback[13],tutorialeattivo,"messaggio");
			else if (punteggio > punteggiosoglia)
				tutoriale(destinazione);
			else{
				azzera();
				inviamessaggio(messaggiofeedback[15],1,"ko");
				tutoriale(1);
			}
			break;
		case "c":
			if (nodovisitato[tutorialeattivo] > 1)
				tutoriale(destinazione);
			else
				inviamessaggio(messaggiofeedback[14],tutorialeattivo,"messaggio");
			break;
	}
}

function studio(tutorialetest){ // accede al tutoriale in funzione dell'errore
	if (nodovisitato[tutorialeattivo] == 2){
		nodovisitato[tutorialeattivo] = 1;
		if (tutorialeprincipale[tutorialeattivo])
			nodovisitato[tutorialeprincipale[tutorialeattivo]] = 1;
		inviamessaggio("",tutorialeattivo);
		if (tutorialetest && tutorialetest[numeroerrore])
			tutoriale(tutorialetest[numeroerrore]);
		else
			tutoriale(tutorialetest[0]);
	}
	else
		tutoriale(tutorialetest[0]);
}

function studioanimazione(animazione){ // accede al tutoriale in funzione dell'errore
	if (nodovisitato[tutorialeattivo] == 2){
		nodovisitato[tutorialeattivo] = 1;
		if (tutorialeprincipale[tutorialeattivo])
			nodovisitato[tutorialeprincipale[tutorialeattivo]] = 1;
		inviamessaggio("",tutorialeattivo);
	}
	
	tutoriale(animazione);
}

function azzera(){ // azzera punteggi e segnalibro
	init_bookmark = 0;
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
		case 1:
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
					var sottopagina = "test"+contatore1+"_"+tutorialeattivo;
					while (document.getElementById(sottopagina)){
						while (document.getElementById(sottopagina).elements[contatore]){
							if (document.getElementById(sottopagina).elements[contatore].checked == true){
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
					var path=mediumblocco[mediumattivo].substr(0,mediumblocco[mediumattivo].length-4);
					var nomi_path = path.split("/");
					var ultimo=nomi_path.length-1;
					var nomefile = nomi_path[ultimo];
					var nomemedium = nomefile+"_"+mediumattivo;
					risposta = Number(document.getElementById(nomemedium).GetVariable("_root.flagrispostaesatta"));
					if (risposta == 1)
						numeroerrore = 1;
					break;
			}
			rispostatest(risposta,messaggio)
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
	if (tutorialeprincipale[tutorialeattivo])
		var punti = puntitutoriale[tutorialeprincipale[tutorialeattivo]];
	else
		var punti = puntitutoriale[tutorialeattivo];
	switch (risposta){
		case 0:
			inviamessaggio(messaggiofeedback[18],tutorialeattivo,"messaggio");
			break;
		case 1:
			nodovisitato[tutorialeattivo] = 2;
			if (tutorialeprincipale[tutorialeattivo])
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
			if (tutorialeprincipale[tutorialeattivo])
				nodovisitato[tutorialeprincipale[tutorialeattivo]] = 3;
			inviamessaggio(messaggio[0],tutorialeattivo,"ok");
			punteggio = punteggio + punti;
			break;
		}
	inviapunteggio(tutorialeattivo);
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
					inviamessaggio(msg,pagina,"messaggio");
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

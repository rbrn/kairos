<?php
$path_img="skins/".$_REQUEST["lo_skin"];
?>
/* --- SHELL ACCESSIBILE: FUNZIONI DI GESTIONE TEST --- */

/* -- VISUALIZZAZIONE -- */
function inviapunteggio(pagina){ // invia i punteggi
	document.getElementById("punteggio_"+pagina).value = punteggio;
	var classepunteggio = (punteggiomassimo - punteggio)/(punteggiomassimo / 5);
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
					rispostatest(risposta,messaggio);
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
					rispostatest(risposta,messaggio);
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
					rispostatest(risposta,messaggio);
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
						if (risposta == 1)
							break
						if (risposta1 == 0)
							numeroerrore = contatore1;
						contatore = 1;
						contatore1++;
						sottopagina = "test"+contatore1+"_"+tutorialeattivo;
					}
					rispostatest(risposta,messaggio);
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
					rispostatest(risposta,messaggio);
					break;
				case 6: // drag and drop in flash
					var medium = mediumblocco[tutorialeattivo].split(".");
					risposta = Number(document.getElementById(medium[0]+"_"+tutorialeattivo).GetVariable("_root.flagrispostaesatta"));
					if (risposta == 1)
						numeroerrore = 1;
					rispostatest(risposta,messaggio);
					break;
				case 7: // cruciverba
					var casellainiziale = 0;
					var contarisposte = 0;
					var contatore1 = 0;
					var lunghezza = 0;
					var spostamento = 0;
					var testorisposta = new String;
					if (tutorialeprincipale[tutorialeattivo] != null)
						var punti = puntitutoriale[tutorialeprincipale[tutorialeattivo]];
					else
						var punti = puntitutoriale[tutorialeattivo];
					while (rispostaesatta[contatore]){
						casellainiziale = rispostaesatta[contatore][4];
						lunghezza = rispostaesatta[contatore][3].length;
						testorisposta = "";
						if (rispostaesatta[contatore][1] == 'v')
							spostamento = rispostaesatta[0][0];
						else
							spostamento = 1;
						for (contatore1=0; contatore1<lunghezza; contatore1++){
							casella = casellainiziale + contatore1 * spostamento;
							testorisposta = testorisposta + document.getElementById("casella_"+tutorialeattivo+"_"+(casella)).value;
						}
						if (testorisposta == ""){// nessuna risposta
							inviamessaggio(rispostaesatta[contatore][0]+" "+rispostaesatta[contatore][1]+" - " + messaggiofeedback[18],tutorialeattivo,"messaggio");
							break;
						}
						else if (testorisposta != rispostaesatta[contatore][3].toUpperCase()){// errore
							risposta = 1;
							numeroerrore = contatore;
							numerotentativi[tutorialeattivo]++;// gestione pulsante soluzioni
							if (numerotentativi[tutorialeattivo] == visualizzasoluzioni && visualizzasoluzioni > 0)
								document.getElementById("pulsantesoluzioni_"+tutorialeattivo).style.display="block";
							nodovisitato[tutorialeattivo] = 2;
							if (tutorialeprincipale[tutorialeattivo] != null)
								nodovisitato[tutorialeprincipale[tutorialeattivo]] = 2;
							if (messaggio[numeroerrore])
								inviamessaggio(rispostaesatta[contatore][0]+" "+rispostaesatta[contatore][1]+" - "+messaggio[numeroerrore],tutorialeattivo,"ko");
							else
								inviamessaggio(rispostaesatta[contatore][0]+" "+rispostaesatta[contatore][1]+" - "+messaggio[1],tutorialeattivo,"ko");
							if (tipolo != "c" && puntinegativi != 0)
								punteggio = punteggio - punti;
							break;
						}
						contatore++;
					}
					if (risposta == 0 && testorisposta != ""){// nessun errore
						risposta = 2;
						nodovisitato[tutorialeattivo] = 3;
						if (tutorialeprincipale[tutorialeattivo] != null)
							nodovisitato[tutorialeprincipale[tutorialeattivo]] = 3;
						inviamessaggio(messaggio[0],tutorialeattivo,"ok");
						punteggio = punteggio + punti;
					}
					inviapunteggio(tutorialeattivo);
					break;
			}
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
		case 5:
			inviamessaggio(messaggiofeedback[27],tutorialeattivo,"messaggio");
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
			numerotentativi[tutorialeattivo]++;// gestione pulsante soluzioni
			if (numerotentativi[tutorialeattivo] == visualizzasoluzioni && visualizzasoluzioni > 0)
				document.getElementById("pulsantesoluzioni_"+tutorialeattivo).style.display="block";
			nodovisitato[tutorialeattivo] = 2; // impostazione nodo visitato
			if (tutorialeprincipale[tutorialeattivo] != null)
				nodovisitato[tutorialeprincipale[tutorialeattivo]] = 2;
			if (messaggio[numeroerrore]) // invio messaggi
				var testomessaggio = messaggio[numeroerrore];
			else
				var testomessaggio = messaggio[1]
			inviamessaggio(testomessaggio,tutorialeattivo,"ko");
			if (tipolo != "c" && puntinegativi != 0)
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

function mostrasoluzioni(tipotest,rispostaesatta,punti){ // presentazione soluzioni test
	if (nodovisitato[tutorialeattivo] != 2 && nodovisitato[tutorialeattivo] != 4)
		return;
	inviamessaggio(messaggiofeedback[26],tutorialeattivo,"messaggio");
	if (tutorialeprincipale[tutorialeattivo] != null) // gestione punteggio
		var punti = puntitutoriale[tutorialeprincipale[tutorialeattivo]];
	else
		var punti = puntitutoriale[tutorialeattivo];
	if (tipolo != "c"){
		punteggio = punteggio - punti;
		if (punteggio < 0)
			punteggio = 0;
		inviapunteggio(tutorialeattivo);
	}
	nodovisitato[tutorialeattivo] = 5; // gestione flag status nodo
	if (tutorialeprincipale[tutorialeattivo] != null)
		nodovisitato[tutorialeprincipale[tutorialeattivo]] = 5;
	numeroerrore = 0;
	var contatore = 1;
	switch (tipotest){
		case 1: // domande a risposta chiusa
			while (document.getElementById("test_"+tutorialeattivo).elements[contatore]){
				if (document.getElementById("test_"+tutorialeattivo).elements[contatore].checked == true && contatore == rispostaesatta[1]){
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ok.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[28];
				}
				else if (document.getElementById("test_"+tutorialeattivo).elements[contatore].checked == true && contatore != rispostaesatta[1]){
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ko.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[29];
				}
				else if (document.getElementById("test_"+tutorialeattivo).elements[contatore].checked == false && contatore == rispostaesatta[1]){
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ko.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[30];
				}
				else{
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/vuoto.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = "";
				}
			contatore++;
			}
			break;
		case 2: // domande a scelta multipla
			while (document.getElementById("test_"+tutorialeattivo).elements[contatore]){
				if ((document.getElementById("test_"+tutorialeattivo).elements[contatore].checked == true && rispostaesatta[contatore] == 1) || (document.getElementById("test_"+tutorialeattivo).elements[contatore].checked == false && rispostaesatta[contatore] == 0)){
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ok.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[28];
				}
				else{
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ko.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[29];
				}
				contatore++;
			}
			break;
		case 3: // domande con completamento di frasi
			while (document.getElementById("test_"+tutorialeattivo).elements[contatore]){
				if (document.getElementById("test_"+tutorialeattivo).elements[contatore].value == rispostaesatta[contatore]){
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ok.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[28];
				}
				else{
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ko.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[31]+ rispostaesatta[contatore];
				}
				contatore++;
			}
			break;
		case 4: // domande multiple a risposta chiusa
			var contatore1 = 1;
			var risposta1 = 0;
			var sottopagina = "test"+contatore1+"_"+tutorialeattivo;
			while (document.getElementById(sottopagina)){
				while (document.getElementById(sottopagina).elements[contatore]){
					if (document.getElementById(sottopagina).elements[contatore].checked == true && contatore == rispostaesatta[contatore1]){
						document.getElementById("testimm"+contatore1+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ok.gif";
						document.getElementById("testimm"+contatore1+"_"+tutorialeattivo).title = messaggiofeedback[28];
						risposta1 = 1;
						break;
					}
					else if (document.getElementById(sottopagina).elements[contatore].checked == true && contatore != rispostaesatta[contatore1]){
						document.getElementById("testimm"+contatore1+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ko.gif";
						document.getElementById("testimm"+contatore1+"_"+tutorialeattivo).title = messaggiofeedback[32] + rispostaesatta[contatore1];
						risposta1 = 1;
						break;
					}
					contatore++;
				}
				contatore = 1;
				if (risposta1 == 0){
					document.getElementById("testimm"+contatore1+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ko.gif";
					document.getElementById("testimm"+contatore1+"_"+tutorialeattivo).title = messaggiofeedback[32] + rispostaesatta[contatore1];
				}
				else
					risposta1 = 0;
				contatore1++;
				sottopagina = "test"+contatore1+"_"+tutorialeattivo;
			}
			break;
		case 5: // domande con selezione di opzioni
			while (document.getElementById("test_"+tutorialeattivo).elements[contatore]){
				if (document.getElementById("test_"+tutorialeattivo).elements[contatore].value == rispostaesatta[contatore]){
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ok.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[28];
				}
				else{
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ko.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[31]+ rispostaesatta[contatore];
				}
				contatore++;
			}
			break;
		case 6: // drag and drop in flash
			document.getElementById("testimm1_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ko.gif";
			document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[31]+ rispostaesatta[1];
			break;
		case 7: // cruciverba
			var casellainiziale = 0;
			var contarisposte = 0;
			var contatore1 = 0;
			var lunghezza = 0;
			var spostamento = 0;
			var testorisposta = new String;
			while (rispostaesatta[contatore]){
				casellainiziale = rispostaesatta[contatore][4];
				lunghezza = rispostaesatta[contatore][3].length;
				testorisposta = "";
				if (rispostaesatta[contatore][1] == 'v')
					spostamento = rispostaesatta[0][0];
				else
					spostamento = 1;
				for (contatore1=0; contatore1<lunghezza; contatore1++){
					casella = casellainiziale + contatore1 * spostamento;
					testorisposta = testorisposta + document.getElementById("casella_"+tutorialeattivo+"_"+(casella)).value;
				}
				if (testorisposta == rispostaesatta[contatore][3].toUpperCase()){
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ok.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[28];
				}
				else{
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).src = "shell/<?php echo($path_img);?>/feedback_ko.gif";
					document.getElementById("testimm"+contatore+"_"+tutorialeattivo).title = messaggiofeedback[31]+ rispostaesatta[contatore][3];
				}
				contatore++;
			}
			break;
	}
}


/* -- ESERCITAZIONI CRUCIVERBA -- */
function visualizzacruciverba(pagina,caselle,definizione){
	var numerocaselle = definizione[0][0] * definizione[0][1];
	var contatore = 1;
	var contatore1 = 1;
	var stringa = new String;
	var stringaid = new String;
	var stringaimmid = new String;
	var cambiodefinizioni = 0;
	var tabindice = 0;
	document.write("<div class='areacruciverba'>");// schema del cruciverba
	document.write("<table class='cruciverba' cellspacing='0' summary='Schema del cruciverba'><tr>");
	contatore = 1;
	while (contatore <= numerocaselle){
		document.write("<td><div class='casella'>");
		if (caselle[contatore] == -1)
			document.write("<img class='casellanera' src='shell/<?php echo $path_img ?>/cruci_nera.gif' alt='Casella nera'>");
		else{
			if (caselle[contatore]){
				for (contatore1=1; contatore1<definizione.length; contatore1++){
					if (definizione[contatore1][0] == caselle[contatore]){
						definizione[contatore1][4] = contatore;
					}
				}
				document.write("<img class='immaginecasella' src='shell/<?php echo $path_img ?>/cruci_"+caselle[contatore]+".gif' alt='Casella "+caselle[contatore]+"'>");
			}
			document.write("<input class='crucireadonly' id='casella_"+pagina+"_"+contatore+"' readonly size='1' maxlength='1'></div>");
		}
		document.write("</div>");
		if ((contatore)%definizione[0][0] == 0)
			document.write("</tr><tr>");
		contatore++;
	}
	document.write("</tr></table></div>");

	document.write("<div class='areadefinizioni'>");// definizioni del cruciverba
	document.write("<form id='test_"+pagina+"'' action=''>");
	document.write("<fieldset><legend class='domanda'>Orizzontali</legend>");
	for (contatore=1; contatore<definizione.length; contatore++){
		if (definizione[contatore][1]=='v' && cambiodefinizioni==0){
			document.write("</fieldset><fieldset><legend class='domanda'>Verticali</legend>");
			cambiodefinizioni = 1;
		}
		stringaid = "test"+contatore+"_"+pagina;
		stringaimmid = "testimm"+contatore+"_"+pagina;
		document.write("<label for='"+stringaid+"'>"+definizione[contatore][0]+". "+definizione[contatore][2]+" <img id='"+stringaimmid+"' class='immagineinlinea' src='shell/<?php echo $path_img ?>/vuoto.gif' alt=''></label>");
		stringa = definizione[contatore][3];
		tabindice++;
		document.write(" <input type='text' tabindex='"+tabindice+"' id='"+stringaid+"' size='"+stringa.length+"'>");
		tabindice++;
		stringa="'inseriscicruciverba(\""+stringaid+"\",\""+definizione[contatore][1]+"\","+definizione[contatore][3].length+","+definizione[contatore][4]+","+definizione[0][0]+");return false'";
		document.write("<a href='#' tabindex='+tabindice+' onClick="+stringa+" onKeyPress="+stringa+">");
		document.write("<img class='immagineinlinea' onMouseOver=\"roll(this,'verifica2')\" onMouseOut=\"noroll(this,'verifica2')\" src='shell/<?php echo $path_img ?>/pulsante_verifica2.gif' alt='Controlla'>");
		document.write("</a><br>");
	}
	document.write("</fieldset></form></div>");
}

function inseriscicruciverba(domanda,tipo,lunghezza,casellainiziale,larghezza){
	var testorisposta = document.getElementById(domanda).value.toUpperCase();
	var contatore = 0;
	var casella = 0;
	var spostamento = 1;
	if (tipo == 'v')
		spostamento = larghezza;
	for (contatore=0; contatore<lunghezza; contatore++){
		casella = casellainiziale + contatore * spostamento;
			document.getElementById("casella_"+tutorialeattivo+"_"+(casella)).value = testorisposta.charAt(contatore);
	}
}


/* --- SHELL ACCESSIBILE: DESCRIZIONE DEL LEARNING OBJECT --- */

	var codice = "2";
	var tipolo = "a";
	var bloccoavanzamento = 0;
	var modocontinua = 1;

	var punteggiominimo = 5; //punteggio per il superamento del modulo
	var punteggiosoglia = 0; //punteggio minimo per proseguire

	var nometutoriale = new Array();
	nometutoriale[0] = "homepage";
	nometutoriale[1] = "tutoriale1";
	nometutoriale[2] = "tutoriale2";
	nometutoriale[3] = "tutoriale3";
	nometutoriale[4] = "tutoriale4";
	nometutoriale[5] = "tutoriale5";
	nometutoriale[6] = "tutoriale6";
	nometutoriale[7] = "tutoriale7";
	nometutoriale[8] = "tutoriale8";
	nometutoriale[9] = "tutoriale9";
	nometutoriale[10] = "tutoriale10";
	nometutoriale[11] = "tutoriale11";
	nometutoriale[12] = "tutoriale12";
	nometutoriale[13] = "tutoriale13";
	nometutoriale[14] = "tutoriale14";
	nometutoriale[15] = "tutoriale15";
	nometutoriale[16] = "tutoriale7alt";

	var numerotutoriale = new Array();
	numerotutoriale["tutoriale1"] = 1;
	numerotutoriale["tutoriale2"] = 2;
	numerotutoriale["tutoriale3"] = 3;
	numerotutoriale["tutoriale4"] = 4;
	numerotutoriale["tutoriale15"] = 5;
	numerotutoriale["tutoriale5"] = 6;
	numerotutoriale["tutoriale6"] = 7;
	numerotutoriale["tutoriale7"] = 8;
	numerotutoriale["tutoriale8"] = 9;
	numerotutoriale["tutoriale9"] = 10;
	numerotutoriale["tutoriale10"] = 11;
	numerotutoriale["tutoriale11"] = 12;
	numerotutoriale["tutoriale12"] = 13;
	numerotutoriale["tutoriale13"] = 14;
	numerotutoriale["tutoriale14"] = 15;

	var successivo = new Array();
	successivo["homepage"] = "tutoriale2"
	successivo["tutoriale1"] = "tutoriale2"
	successivo["tutoriale2"] = "tutoriale3";
	successivo["tutoriale3"] = "tutoriale4";
	successivo["tutoriale4"] = "tutoriale15";
	successivo["tutoriale15"] = "tutoriale5";
	successivo["tutoriale5"] = "tutoriale6";
	successivo["tutoriale6"] = "tutoriale7";
	successivo["tutoriale7"] = "tutoriale8";
	successivo["tutoriale8"] = "tutoriale9";
	successivo["tutoriale9"] = "tutoriale10";
	successivo["tutoriale10"] = "tutoriale11";
	successivo["tutoriale11"] = "tutoriale12";
	successivo["tutoriale12"] = "tutoriale13";
	successivo["tutoriale13"] = "tutoriale14";
	successivo["tutoriale14"] = "";
	successivo["tutoriale7alt"] = "tutoriale8";

	var precedente = new Array();
	precedente["homepage"] = ""
	precedente["tutoriale1"] = "";
	precedente["tutoriale2"] = "tutoriale1";
	precedente["tutoriale3"] = "tutoriale2";
	precedente["tutoriale4"] = "tutoriale3";
	precedente["tutoriale15"] = "tutoriale4";
	precedente["tutoriale5"] = "tutoriale15";
	precedente["tutoriale6"] = "tutoriale5";
	precedente["tutoriale7"] = "tutoriale6";
	precedente["tutoriale8"] = "";
	precedente["tutoriale9"] = "tutoriale8";
	precedente["tutoriale10"] = "tutoriale9";
	precedente["tutoriale11"] = "tutoriale10";
	precedente["tutoriale12"] = "tutoriale11";
	precedente["tutoriale13"] = "";
	precedente["tutoriale14"] = "tutoriale13";
	precedente["tutoriale7alt"] = "tutoriale6";


	var tipotutoriale = new Array(); //0=homepage 1=tutoriale 2=test/esercitazione 3=introduzione 4=riepilogo 5=commento
	tipotutoriale["homepage"]=0;
	tipotutoriale["tutoriale1"] = 3;
	tipotutoriale["tutoriale2"] = 1;
	tipotutoriale["tutoriale3"] = 1;
	tipotutoriale["tutoriale4"] = 2;
	tipotutoriale["tutoriale5"] = 2;
	tipotutoriale["tutoriale6"] = 2;
	tipotutoriale["tutoriale7"] = 2;
	tipotutoriale["tutoriale8"] = 1;
	tipotutoriale["tutoriale9"] = 1;
	tipotutoriale["tutoriale10"] = 2;
	tipotutoriale["tutoriale11"] = 2;
	tipotutoriale["tutoriale12"] = 2;
	tipotutoriale["tutoriale13"] = 4;
	tipotutoriale["tutoriale14"] = 5;
	tipotutoriale["tutoriale15"] = 2;
	tipotutoriale["tutoriale7alt"] = 2;

	var puntitutoriale = new Array();
	puntitutoriale["tutoriale4"] = 2;
	puntitutoriale["tutoriale5"] = 2;
	puntitutoriale["tutoriale6"] = 2;
	puntitutoriale["tutoriale7"] = 2;
	puntitutoriale["tutoriale10"] = 2;
	puntitutoriale["tutoriale11"] = 2;
	puntitutoriale["tutoriale12"] = 2;
	puntitutoriale["tutoriale15"] = 2;

	var tutorialealternativo = new Array();
	tutorialealternativo["tutoriale7"] = "tutoriale7alt";
	var tutorialeprincipale = new Array();
	tutorialeprincipale["tutoriale7alt"] = "tutoriale7";

	var nomeapprofondimento = new Array();
	nomeapprofondimento[1] = "approfondimento1";
	nomeapprofondimento[2] = "approfondimento2";

	var messaggiofeedback = new Array();
	messaggiofeedback[1] = "La missione è quasi fallita"; // tag Alt immagine di riepilogo livello 1
	messaggiofeedback[2] = "La prestazione è piuttosto modesta"; // tag Alt immagine di riepilogo livello 2
	messaggiofeedback[3] = "Il successo è ancora lontano"; // tag Alt immagine di riepilogo livello 3
	messaggiofeedback[4] = "La prestazione è superiore alla media"; // tag Alt immagine di riepilogo livello 4
	messaggiofeedback[5] = "La prestazione è esaltante"; // tag Alt immagine di riepilogo livello 5
	messaggiofeedback[6] = "La missione è quasi fallita"; // messaggio di riepilogo livello 1
	messaggiofeedback[7] = "La prestazione è piuttosto modesta"; // messaggio di riepilogo livello 2
	messaggiofeedback[8] = "Il successo è ancora lontano"; // messaggio di riepilogo livello 3
	messaggiofeedback[9] = "La prestazione è superiore alla media"; // messaggio di riepilogo livello 4
	messaggiofeedback[10] = "La prestazione è esaltante"; // messaggio di riepilogo livello 5
	messaggiofeedback[11] = "Commento inviato"; // invio del commento alla piattaforma
	messaggiofeedback[12] = "Il commento non può superare i 4000 caratteri!"; // superamento del limite del commento
	messaggiofeedback[13] = "Prima rispondi bene!"; //messaggio per mancata risposta al test
	messaggiofeedback[14] = "Prima rispondi!"; //messaggio per mancata risposta al test
	messaggiofeedback[15] = "La tua missione è fallita. Ricomincia!"; //messaggio di superamento livello di soglia
	messaggiofeedback[16] = "Hai già risposto. Vai avanti."; // messaggio per test già affrontato
	messaggiofeedback[17] = "Prima di ritentare, studia!"; // messaggio per mancato accesso al tutoriale dopo errore
	messaggiofeedback[18] = "Non hai ancora risposto!"; // messaggio per mancata risposta
	messaggiofeedback[19] = "Andiamo male: la missione è in pericolo"; // tag Alt immagine test livello 1
	messaggiofeedback[20] = "Prestazione ancora modesta: fai attenzione"; // tag Alt immagine test livello 2
	messaggiofeedback[21] = "Il successo è ancora lontano"; // tag Alt immagine test livello 3
	messaggiofeedback[22] = "La situazione è incoraggiante: continua così"; // tag Alt immagine test livello 4
	messaggiofeedback[23] = "Prestazione esaltante: il successo è vicino"; // tag Alt immagine test livello 5
	messaggiofeedback[24] = "Prova effettuata, ma non superata"; // messaggio per test già effettuato
	messaggiofeedback[25] = "Prova superata"; // messaggio per test già superato;

	var messaggiotest = new Array();
	messaggiotest[0] = "Risposta esatta! Vai avanti"; // messaggio di default per risposta esatta
	messaggiotest[1] = "Hai sbagliato! Studia!!"; // messaggio di default per risposta errata

/* --- SHELL ACCESSIBILE: DESCRIZIONE DEL LEARNING OBJECT --- */

	var codice = "1";
	var tipolo = "b";
	var bloccoavanzamento = 1;
	var modocontinua = 1;
	var visualizzasoluzioni = 3;
	if (tipolo=='c') visualizzasoluzioni=1;
	var puntinegativi = 0; // 1 = sottrae punti per test errato
	
	var punteggiominimo = 1; //punteggio per il superamento del modulo
	var punteggiosoglia = 0; //punteggio minimo per proseguire
	var nometutoriale = new Array();
	var numerotutoriale = new Array();
	var successivo = new Array();
	var precedente = new Array();
	var tipotutoriale = new Array();
	var puntitutoriale = new Array();
	var tutorialealternativo = new Array();
	var tutorialeprincipale = new Array();
	var nomeapprofondimento = new Array();
	
	nometutoriale[0]="homepage";
	tipotutoriale["homepage"]=0;
	precedente["homepage"]="";
	
	nomeapprofondimento[1]='item_525462177b7c8';
nomeapprofondimento[2]='item_5254636bd0bd8';
successivo['homepage']='';


	  
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
	messaggiofeedback[26] = "Per le soluzioni, sfiora con il puntatore le icone accanto alle risposte"; // messaggio per evidenziazione soluzioni
	messaggiofeedback[27] = "Hai visualizzato le soluzioni: non puoi più rispondere"; // messaggio per soluzini visualizzate
	messaggiofeedback[28] = "La tua risposta è esatta"; // tag Title del feedback positivo
	messaggiofeedback[29] = "La tua risposta è errata"; // tag Title del feedback negativo
	messaggiofeedback[30] = "Questa è la risposta corretta"; // tag Title del feedback negativo (con risposta chiusa)
	messaggiofeedback[31] = "La tua risposta è errata. Quella corretta è: "; // tag Title del feedback negativo (con risposta testuale esatta)
	messaggiofeedback[32] = "La tua risposta è errata. Quella corretta è la numero "; // tag Title del feedback negativo (con selezione)

	var messaggiotest = new Array();
	messaggiotest[0] = "Risposta esatta! Vai avanti"; // messaggio di default per risposta esatta
	messaggiotest[1] = "Hai sbagliato! Studia!!"; // messaggio di default per risposta errata
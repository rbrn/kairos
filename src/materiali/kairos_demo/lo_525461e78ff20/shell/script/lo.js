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
	messaggiofeedback[1] = "La missione � quasi fallita"; // tag Alt immagine di riepilogo livello 1
	messaggiofeedback[2] = "La prestazione � piuttosto modesta"; // tag Alt immagine di riepilogo livello 2
	messaggiofeedback[3] = "Il successo � ancora lontano"; // tag Alt immagine di riepilogo livello 3
	messaggiofeedback[4] = "La prestazione � superiore alla media"; // tag Alt immagine di riepilogo livello 4
	messaggiofeedback[5] = "La prestazione � esaltante"; // tag Alt immagine di riepilogo livello 5
	messaggiofeedback[6] = "La missione � quasi fallita"; // messaggio di riepilogo livello 1
	messaggiofeedback[7] = "La prestazione � piuttosto modesta"; // messaggio di riepilogo livello 2
	messaggiofeedback[8] = "Il successo � ancora lontano"; // messaggio di riepilogo livello 3
	messaggiofeedback[9] = "La prestazione � superiore alla media"; // messaggio di riepilogo livello 4
	messaggiofeedback[10] = "La prestazione � esaltante"; // messaggio di riepilogo livello 5
	messaggiofeedback[11] = "Commento inviato"; // invio del commento alla piattaforma
	messaggiofeedback[12] = "Il commento non pu� superare i 4000 caratteri!"; // superamento del limite del commento
	messaggiofeedback[13] = "Prima rispondi bene!"; //messaggio per mancata risposta al test
	messaggiofeedback[14] = "Prima rispondi!"; //messaggio per mancata risposta al test
	messaggiofeedback[15] = "La tua missione � fallita. Ricomincia!"; //messaggio di superamento livello di soglia
	messaggiofeedback[16] = "Hai gi� risposto. Vai avanti."; // messaggio per test gi� affrontato
	messaggiofeedback[17] = "Prima di ritentare, studia!"; // messaggio per mancato accesso al tutoriale dopo errore
	messaggiofeedback[18] = "Non hai ancora risposto!"; // messaggio per mancata risposta
	messaggiofeedback[19] = "Andiamo male: la missione � in pericolo"; // tag Alt immagine test livello 1
	messaggiofeedback[20] = "Prestazione ancora modesta: fai attenzione"; // tag Alt immagine test livello 2
	messaggiofeedback[21] = "Il successo � ancora lontano"; // tag Alt immagine test livello 3
	messaggiofeedback[22] = "La situazione � incoraggiante: continua cos�"; // tag Alt immagine test livello 4
	messaggiofeedback[23] = "Prestazione esaltante: il successo � vicino"; // tag Alt immagine test livello 5
	messaggiofeedback[24] = "Prova effettuata, ma non superata"; // messaggio per test gi� effettuato
	messaggiofeedback[25] = "Prova superata"; // messaggio per test gi� superato;
	messaggiofeedback[26] = "Per le soluzioni, sfiora con il puntatore le icone accanto alle risposte"; // messaggio per evidenziazione soluzioni
	messaggiofeedback[27] = "Hai visualizzato le soluzioni: non puoi pi� rispondere"; // messaggio per soluzini visualizzate
	messaggiofeedback[28] = "La tua risposta � esatta"; // tag Title del feedback positivo
	messaggiofeedback[29] = "La tua risposta � errata"; // tag Title del feedback negativo
	messaggiofeedback[30] = "Questa � la risposta corretta"; // tag Title del feedback negativo (con risposta chiusa)
	messaggiofeedback[31] = "La tua risposta � errata. Quella corretta �: "; // tag Title del feedback negativo (con risposta testuale esatta)
	messaggiofeedback[32] = "La tua risposta � errata. Quella corretta � la numero "; // tag Title del feedback negativo (con selezione)

	var messaggiotest = new Array();
	messaggiotest[0] = "Risposta esatta! Vai avanti"; // messaggio di default per risposta esatta
	messaggiotest[1] = "Hai sbagliato! Studia!!"; // messaggio di default per risposta errata
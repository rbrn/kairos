/* --- SHELL ACCESSIBILE: DESCRIZIONE DEL LEARNING OBJECT --- */

	var codice = "1";
	var tipolo = "a";
	var bloccoavanzamento = 0;
	var modocontinua = 0;
	
	var punteggiominimo = 4; //punteggio per il superamento del modulo
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
	
	nometutoriale[1]='item_43f4a1888be14';
tipotutoriale["item_43f4a1888be14"]=3;
numerotutoriale["item_43f4a1888be14"]=1;
precedente['item_43f4a1888be14']='';
successivo['homepage']='item_43f4a1888be14';
nometutoriale[2]='item_43f4c3c095821';
tipotutoriale["item_43f4c3c095821"]=1;
numerotutoriale["item_43f4c3c095821"]=2;
precedente['item_43f4c3c095821']='item_43f4a1888be14';
successivo['item_43f4a1888be14']='item_43f4c3c095821';
tutorialealternativo["item_43f4c3c095821"] = "item_43f5b374634f1";
nomeapprofondimento[1]='item_43f4a17c48abe';
nometutoriale[3]='item_43f4a1e44cebe';
tipotutoriale["item_43f4a1e44cebe"]=2;
puntitutoriale["item_43f4a1e44cebe"]=2;
numerotutoriale["item_43f4a1e44cebe"]=3;
precedente['item_43f4a1e44cebe']='item_43f4c3c095821';
successivo['item_43f4c3c095821']='item_43f4a1e44cebe';
nometutoriale[4]='item_43f583a73878b';
tipotutoriale["item_43f583a73878b"]=2;
puntitutoriale["item_43f583a73878b"]=2;
numerotutoriale["item_43f583a73878b"]=4;
precedente['item_43f583a73878b']='item_43f4a1e44cebe';
successivo['item_43f4a1e44cebe']='item_43f583a73878b';
tutorialealternativo["item_43f583a73878b"] = "item_43f5838b2563b";
tutorialeprincipale["item_43f5838b2563b"] = "item_43f583a73878b";
nometutoriale[5]='item_43f4c621b2033';
tipotutoriale["item_43f4c621b2033"]=2;
puntitutoriale["item_43f4c621b2033"]=2;
numerotutoriale["item_43f4c621b2033"]=5;
precedente['item_43f4c621b2033']='item_43f583a73878b';
successivo['item_43f583a73878b']='item_43f4c621b2033';
nometutoriale[6]='item_43f620dccdeaf';
tipotutoriale["item_43f620dccdeaf"]=1;
numerotutoriale["item_43f620dccdeaf"]=6;
precedente['item_43f620dccdeaf']='item_43f4c621b2033';
successivo['item_43f4c621b2033']='item_43f620dccdeaf';
tutorialealternativo["item_43f620dccdeaf"] = "item_43f620f71d4e0";
nometutoriale[7]='item_43f4a207bbc89';
tipotutoriale["item_43f4a207bbc89"]=4;
numerotutoriale["item_43f4a207bbc89"]=7;
precedente['item_43f4a207bbc89']='item_43f620dccdeaf';
successivo['item_43f620dccdeaf']='item_43f4a207bbc89';
nometutoriale[8]='item_43f4b43a96f4e';
tipotutoriale["item_43f4b43a96f4e"]=5;
numerotutoriale["item_43f4b43a96f4e"]=8;
precedente['item_43f4b43a96f4e']='item_43f4a207bbc89';
successivo['item_43f4a207bbc89']='item_43f4b43a96f4e';
nomeapprofondimento[2]='item_43f4a1fca0ccc';
nometutoriale[9]='item_43f5838b2563b';
tipotutoriale["item_43f5838b2563b"]=2;
nometutoriale[10]='item_43f5b374634f1';
tipotutoriale["item_43f5b374634f1"]=1;
numerotutoriale["item_43f5b374634f1"]=9;
tutorialeprincipale["item_43f5b374634f1"] = "item_43f4c3c095821";
nometutoriale[11]='item_43f5b380e413c';
tipotutoriale["item_43f5b380e413c"]=1;
tutorialeprincipale["item_43f5b380e413c"] = "item_43f4c3c095821";
precedente['item_43f5b380e413c']='item_43f5b374634f1';
successivo['item_43f5b374634f1']='item_43f5b380e413c';
nometutoriale[12]='item_43f61f987ec88';
tipotutoriale["item_43f61f987ec88"]=1;
tutorialeprincipale["item_43f61f987ec88"] = "item_43f4c3c095821";
precedente['item_43f61f987ec88']='item_43f5b380e413c';
successivo['item_43f5b380e413c']='item_43f61f987ec88';
nometutoriale[13]='item_43f620f71d4e0';
tipotutoriale["item_43f620f71d4e0"]=1;
tutorialeprincipale["item_43f620f71d4e0"] = "item_43f620dccdeaf";
nometutoriale[14]='item_43f631f581cd2';
tipotutoriale["item_43f631f581cd2"]=1;
tutorialeprincipale["item_43f631f581cd2"] = "item_43f620dccdeaf";
precedente['item_43f631f581cd2']='item_43f620f71d4e0';
successivo['item_43f620f71d4e0']='item_43f631f581cd2';
successivo['item_43f4b43a96f4e']='';
successivo['item_43f631f581cd2']=successivo['item_43f620dccdeaf'];

precedente['item_43f5b374634f1']=precedente['item_43f4c3c095821'];
precedente['item_43f5838b2563b']=precedente['item_43f583a73878b'];
successivo['item_43f5838b2563b']=successivo['item_43f583a73878b'];
precedente['item_43f620f71d4e0']=precedente['item_43f620dccdeaf'];
precedente['item_43f5b374634f1']=precedente['item_43f4c3c095821'];
successivo['item_43f61f987ec88']=successivo['item_43f4c3c095821'];
precedente['item_43f620f71d4e0']=precedente['item_43f620dccdeaf'];

	  
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
	
	var messaggiotest = new Array();
	messaggiotest[0] = "Risposta esatta! Vai avanti"; // messaggio di default per risposta esatta
	messaggiotest[1] = "Hai sbagliato! Studia!!"; // messaggio di default per risposta errata
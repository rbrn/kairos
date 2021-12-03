var tipo_blocco = new Array;
var mediumblocco= new Array;
var blocco_id = new Array;
var appr_id = new Array;
<?php
$path_img="skins/".$_REQUEST[lo_skin];
$risorsa=$_REQUEST["risorsa"];
$kairos_cookie=$_COOKIE["kairos_cookie"];

$DBHOST = "localhost";
$DBUSER = "g_user_db";
$DBPWD = "gara29mond";
$DBASE=$kairos_cookie[4];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

function tipo_pagina($id_padre) {
	global $i_pag,$i_appr;
	global $db;
	global $DBASE;
	
	mysql_select_db($DBASE,$db);	
	$query="SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo='200' or tipo='201' or tipo='20') ORDER BY posizione";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_risorsa=$riga["id_risorsa"];
		$titolo=$riga["titolo"];
		$tipo_risorsa=$riga["tipo"];
		$id_pagina=$riga["id_gruppo"];
		
		switch ($tipo_risorsa) {
			case '20':
				tipo_pagina($id_risorsa);
				break;
			
			case '200':
				$id_pagina=$riga["id_gruppo"];
				$query_p="SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
				$result_p=$mysqli->query($query_p);
				$riga_p=$result_p->fetch_array();
				$approfondimento=$riga_p["approfondimento"];
				if ($approfondimento<>"on") {
					echo "tipo_blocco[$i_pag]='contenuto';
					blocco_id[$i_pag]='$id_pagina';";
					$i_pag++;
				} else {
					echo "appr_id[$i_appr]='$id_pagina';";
					$i_appr++;
				};
				break;
				
			case '201':
				echo "tipo_blocco[$i_pag]='test';
				blocco_id[$i_pag]='$id_pagina';";
				$i_pag++;
				break;
		};
		
	};	
};

$i_pag=1;
$i_appr=1;
tipo_pagina($risorsa);

?>

/* -- ROUTINE DI GESTIONE PAGINA -- */
var tutorialeattivo = "1";
var messaggio_attivo="";
var approfondimentoattivo = "1";
var approfondimentoattivo2 = "0";
var paginaservizioattiva = new String;
var mediumattivo = "";
var elementoattivo = 0; // 0= home 2=tutoriale 4=indice 5/6=approfondimento
var numeropagina = 0;
var messaggio = new String;
var dimensionicarattere = 1;
var dimensionipagina = 1;
var multimedia = 0;
var paginetutoriali = new Number;
var punteggio = 0;
var punteggiomassimo = 0;
var paginetest = new Array;
var nodivisitati = 0;
var nodovisitato = new Array;

var stacknodi = new Array;
var puntatorestack = 0;
var in_stack=true;

/* -- CONFIGURAZIONE BROWSER -- */
var tipobrowser = new Number;
var plugin_qt = 0; // Quick Time
var plugin_wm = 0; // Windows Media Player
var plugin_rp = 0; // Real Player
var plugin_fl = 0; // Flash
switch (navigator.appName){
	case "Microsoft Internet Explorer": 
 		tipobrowser = 1;
		document.writeln("<script language='VBscript'>");
		document.writeln("on error resume next");
		document.writeln('plugin_fl = IsObject(CreateObject("ShockwaveFlash.ShockwaveFlash.6"))');
		document.writeln('plugin_wm = IsObject(CreateObject("MediaPlayer.MediaPlayer.1"))');
		document.writeln('plugin_rp = IsObject(CreateObject("rmocx.RealPlayer G2 Control"))');
		document.writeln('plugin_rp = IsObject(CreateObject("RealPlayer.RealPlayer(tm) ActiveX Control (32-bit)"))');
		document.writeln('plugin_rp = IsObject(CreateObject("RealVideo.RealVideo(tm) ActiveX Control (32-bit)"))');
		document.writeln("qtime = false");
		document.writeln('Set qtime = CreateObject("QuickTimeCheckObject.QuickTimeCheck.1")');
		document.writeln("If IsObject(qtime) Then");
		document.writeln("If qtime.IsQuickTimeAvailable(0) Then");
		document.writeln("plugin_qt = 1");
		document.writeln("End If");
		document.writeln("End If");
		document.writeln("</script>");
		if (plugin_wm == 1){
			plugin_qt = 0;
			plugin_rp = 0;
		}
		else if (plugin_qt == 1)
			plugin_rp = 0;
		break;
	case "Netscape": 
		tipobrowser = 2;
		cercaplugin();
		break;
	case "Opera": 
		tipobrowser = 3;
		cercaplugin();
		break;
	default: 
		tipobrowser = 3;
		cercaplugin();
		break;
}
	
/* -- ACQUISIZIONE PARAMETRI -- */
function acquisisciparametri(){ // accetta i parametri da piattaforma e se presenti da querystring
	iniziacorso();
	punteggio = init_score;
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
			punteggiomassimo = Number(parametri[3]);
		for(var i=4;i < parametri.length;i++){
			paginetest[i-3] = Number(parametri[i]);
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
	 }
}

/* -- VISUALIZZAZIONE PAGINE TUTORIALI -- */
function tutoriale(blocco){  // visualizza la pagina prescelta e gestisce il menÃÂÃÂ¹
	finemedium();
	switch (elementoattivo){
      		case 0: // home page
			document.getElementById("pulsantezoom").style.display="none";
			document.getElementById("homepage").style.display="none";
			document.getElementById("navigazionetutoriale").style.display="none";
			break;
			
      		case 2: // tutoriale
			if (messaggio_attivo != "")
				cancellamessaggio(messaggio_attivo);
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			document.getElementById("pulsantezoom").style.display="none";
			break;
     		case 4: // sommario
			document.getElementById("pulsantezoom").style.display="none";
			document.getElementById("sommario").style.display="none";
			document.getElementById("navigazionetutoriale").style.display="block";
			document.getElementById("pulsanteindice").style.display="inline";
			break;
	}
	switch (tipomenu){
		case 0:
			document.getElementById("indice"+tutorialeattivo).style.backgroundColor="#ffffff";
			document.getElementById("indice"+blocco).style.fontVariant="small-caps";
			document.getElementById("indice"+blocco).style.backgroundColor="#efefef";
			if (in_stack){
				stacknodi.push(blocco);
				puntatorestack++;
				//alert (puntatorestack+'->'+blocco);
			}
			break;
	}
	in_stack=true;
	tutorialeattivo = String(blocco);
	document.getElementById("pulsantezoom").style.display="none";
	document.getElementById("pulsantehome").style.display="inline";
	document.getElementById("pulsantehistory").style.display="inline";
	document.getElementById("tutoriale"+tutorialeattivo).style.display="block";
	window.open("#tutoriale"+tutorialeattivo+"_a","_self");
	if (mediumblocco[tutorialeattivo]) {
		iniziamedium(mediumblocco[tutorialeattivo]);
	};
	elementoattivo = 2;
	if (blocco==ultimapagina) {
		LMSSetValue( "cmi.core.lesson_status", "completed" );	
	}
}

function visualizzapagina(numeropagina){ // visualizza il numero della pagina e il totale delle pagine
	document.write("<p><span class='nascosto'>Pagina<\/span>");
	document.write("<span class='numeropagina'>"+numeropagina+" </span>");
	document.write("<span class='nascosto'> su </span>");
	document.write("<span class='totalepagine'> / "+ultimapagina+"</span>");
}


/* -- VISUALIZZAZIONE HOME -- */
function homepage(){ // accede all'home page del lo
	finemedium();
	switch (elementoattivo){
      		case 2: // tutoriale
			if (messaggio_attivo != "")
				cancellamessaggio(messaggio_attivo);
			document.getElementById("navigazionetutoriale").style.display="none";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			break;
			
			case 4: // indice
			document.getElementById("sommario").style.display="none";
			break;
	}
	document.getElementById("pulsantezoom").style.display="none";
	document.getElementById("pulsanteindice").style.display="none";		
	document.getElementById("pulsantehome").style.display="none";
	document.getElementById("pulsantehistory").style.display="none";
	document.getElementById("homepage").style.display="block";
	window.open("#homepage_a","_self");
	elementoattivo = 0;
}

/* -- VISUALIZZAZIONE INDICE -- */
function sommario(){ // accede all'indice generale del tutoriale
	finemedium();
	switch (elementoattivo){
      		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="none";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			break;
			
			case 0: // home
			document.getElementById("homepage").style.display="none";
			break;
	}
	document.getElementById("pulsantezoom").style.display="none";
	document.getElementById("pulsanteindice").style.display="none";
	document.getElementById("pulsantehome").style.display="inline";
	
	document.getElementById("indice"+tutorialeattivo).style.fontWeight="bold";
	document.getElementById("sommario").style.display="block";
	window.open("#sommario_a","_self");
	elementoattivo = 4;
}

/* -- VISUALIZZAZIONE APPROFONDIMENTI -- */
function approfondimento(puntatorearrivo){ // visualizza approfondimento di primo livello
	finemedium();		
	document.getElementById("navigazionetutoriale").style.display="none";
	document.getElementById("pulsantehome").style.display="none";
	document.getElementById("pulsantehistory").style.display="none";
	document.getElementById("pulsanteindice").style.display="none";
	document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
	document.getElementById("approfondimento"+puntatorearrivo).style.display="block";
	window.open("#approfondimento"+approfondimentoattivo+"_a","_self");
	approfondimentoattivo = String(puntatorearrivo);
	elementoattivo = 5;
}

function approfondimento2(puntatorearrivo){ // visualizza approfondimento di secondo livello
	finemedium();		
	document.getElementById("approfondimento"+approfondimentoattivo).style.display="none";
	document.getElementById("approfondimento"+puntatorearrivo).style.display="block";
	window.open("#approfondimento"+approfondimentoattivo2+"_a","_self");
	approfondimentoattivo2 = String(puntatorearrivo);
	elementoattivo = 6;
}

function ritorna(){ // ritorna da approfondimenti
	if (elementoattivo == 6){
		document.getElementById("approfondimento"+approfondimentoattivo).style.display="block";
		document.getElementById("approfondimento"+approfondimentoattivo2).style.display="none";
		window.open("#approfondimento"+approfondimentoattivo+"_a","_self");
		elementoattivo = 5;
	}
	else {
		document.getElementById("approfondimento"+approfondimentoattivo).style.display="none";
		document.getElementById("tutoriale"+tutorialeattivo).style.display="block";
		document.getElementById("pulsantehome").style.display="inline";
		document.getElementById("pulsanteindice").style.display="inline";
		document.getElementById("navigazionetutoriale").style.display="block";
		window.open("#tutoriale"+tutorialeattivo+"_a","_self");
		if (mediumblocco[tutorialeattivo]) {
		iniziamedium(mediumblocco[tutorialeattivo]);
		};
		approfondimentoattivo = 0;
		elementoattivo = 2;
	}
}

function indietro(){ // torna all'ultima pagina tutoriale visitata
	if (puntatorestack > 0) {
		puntatorestack--;
		in_stack=false;
		tutoriale(stacknodi[puntatorestack]);
		
	}
}

/* -- VISUALIZZAZIONE PAGINE DI SERVIZIO -- */
function vai(puntatorearrivo){ // accesso alle pagine che permettono di tornare al punto di partenza
	finemedium();		
	document.getElementById("pulsantecredits").style.display="none";
	document.getElementById("pulsantehelp").style.display="none";
	document.getElementById("pulsanteuscita").style.display="none";
	if (puntatorearrivo=='esci') {
		chiudi();
	} else {
	switch (elementoattivo){
      		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="none";
			document.getElementById("pulsantehome").style.display="none";
			document.getElementById("pulsanteindice").style.display="none";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="none";
			break;
     		case 4: // sommario
			document.getElementById("sommario").style.display="none";
			break;
		case 5: // approfondimenti
			document.getElementById("approfondimento"+approfondimentoattivo).style.display="none";
			break;
		case 6: // approfondimenti II livello
			document.getElementById("approfondimento"+approfondimentoattivo2).style.display="none";
			break;
       	}
	paginaservizioattiva = puntatorearrivo;
	document.getElementById(paginaservizioattiva).style.display="block";
	window.open("#"+paginaservizioattiva+"_a","_self");
	};
}

function ritornaindietro(){
	document.getElementById(paginaservizioattiva).style.display="none";
	document.getElementById("pulsantecredits").style.display="inline";
	document.getElementById("pulsantehelp").style.display="inline";
	document.getElementById("pulsanteuscita").style.display="inline";
	switch (elementoattivo){
      		case 2: // tutoriale
			document.getElementById("navigazionetutoriale").style.display="block";
			document.getElementById("pulsantehome").style.display="inline";
			document.getElementById("pulsanteindice").style.display="inline";
			document.getElementById("tutoriale"+tutorialeattivo).style.display="block";
			window.open("#tutoriale"+tutorialeattivo+"_a","_self");
			if (mediumblocco[tutorialeattivo]) {
				iniziamedium(mediumblocco[tutorialeattivo]);
			};
			break;
     		case 4: // sommario
			document.getElementById("sommario").style.display="block";
			window.open("#sommario_a","_self");
			break;
		case 5: // approfondimenti
			document.getElementById("approfondimento"+approfondimentoattivo).style.display="block";
			window.open("#approfondimento"+approfondimentoattivo+"_a","_self");
			break;
		case 6: // approfondimenti II livello
			document.getElementById("approfondimento"+approfondimentoattivo2).style.display="block";
			window.open("#approfondimento"+approfondimentoattivo2+"_a","_self");
			break;
       	}
}

/* -- MESSAGGI -- */
function inviamessaggio(testo,pagina){ // invia messaggi di sistema
	messaggio_attivo="messaggio"+pagina;
	messaggio = testo;
	document.getElementById(messaggio_attivo).style.display = "block";
	document.getElementById(messaggio_attivo).value = messaggio;
	feedbacksonoro("messaggio");
}

function cancellamessaggio(messaggio_attivo){ // invia messaggi di sistema
	document.getElementById(messaggio_attivo).value = "";
	document.getElementById(messaggio_attivo).style.display = "none";
	messaggio_attivo = "";
}

/* -- INIZIALIZZAZIONE -- */
function inizializza(){ // nasconde tutte le pagine tranne la home e imposta i parametri iniziali

	var contatore = 0;
	impostacaratteri();
	var init_launch_data=LMSGetValue("cmi.launch_data");
	document.getElementById("esci").style.display="none";
	document.getElementById("navigazionetutoriale").style.display="none";
	document.getElementById("paginahelp").style.display="none";
	document.getElementById("paginacredits").style.display="none";

	document.getElementById("sommario").style.display="none";

	if (multimedia==1)
		document.getElementById("pulsantesuonoon").style.display="none";
	else
		document.getElementById("pulsantesuonoff").style.display="none";


	contatore = 1; // nasconde il tutoriale
	while (document.getElementById("tutoriale"+contatore)){
		document.getElementById("tutoriale"+contatore).style.display="none";
		contatore++;
		paginetutoriali++;
	}

	contatore = 1; // nasconde gli approfondimenti
	while (document.getElementById("approfondimento"+contatore)){
		document.getElementById("approfondimento"+contatore).style.display="none";
		contatore++;
	}
	
	document.getElementById("pulsantestampa").style.display="none";
	document.getElementById("body").style.display="block";
	
	if (init_launch_data) {
		var blocco_preview=0;
		for (i=1;i<=blocco_id.length;i++) {
			if (blocco_id[i]==init_launch_data) blocco_preview=i;
		};
		if (blocco_preview) {
			tutoriale(blocco_preview);
		} else {
			homepage();
		};
	} else {
		homepage();
	};
	//riepilogopunteggi();
	

}

function azzera(){ // azzera punteggi e segnalibro
	init_bookmark = 0;
	punteggio = 0;
}

/* -- DIMENSIONE CARATTERI -- */
function impostacaratteri(){ // imposta il carattere in funzione del parametro inviato dalla querystring
	var stringa = String(dimensionicarattere) + "em";
	document.getElementById("contenuto").style.fontSize = stringa;
}

function incrementa(){ // aumenta le dimensioni del carattere del 10%
	dimensionicarattere = dimensionicarattere + 0.1;
	var stringa = String(dimensionicarattere) + "em";
	document.getElementById("contenuto").style.fontSize = stringa;
}

function decrementa(){ // diminuisce le dimensioni del carattere del 10%
	dimensionicarattere = dimensionicarattere - 0.1;
	var stringa = String(dimensionicarattere) + "em";
	document.getElementById("contenuto").style.fontSize = stringa;
}

/* -- ROLLOVER -- */
function roll(immagine,progressivo){ // carica l'immagine di rollover
	if (progressivo)
	   var elemento = immagine+String(progressivo);
	else
	   var elemento = immagine;
	   document.getElementById(elemento).src = "shell/<? echo $path_img ?>/pulsante_"+immagine+"_r.gif";
	
}

function noroll(immagine,progressivo){ // ricarica l'immagine normale
	if (progressivo)
	   var elemento = immagine+String(progressivo);
	else
	   var elemento = immagine;
	   document.getElementById(elemento).src = "shell/<? echo $path_img ?>/pulsante_"+immagine+".gif";
	
}

/* -- DIMENSIONE SCHERMATA -- */
function aumentazoom(){ // aumenta le dimensioni della schermata
	var nomefile = location.href.split("#");
	nomefile = nomefile[0].split("?");
	dimensionipagina = 2;
	traccia();
	window.open(nomefile[0]+"?"+dimensionicarattere+','+dimensionipagina,"_self");
}

function diminuiscizoom(){ // diminuisce le dimensioni della schermata
	var nomefile = location.href.split("#");
	nomefile = nomefile[0].split("?");
	dimensionipagina = 1;
	traccia();
	window.open(nomefile[0]+"?"+dimensionicarattere+','+dimensionipagina,"_self");
}

/* -- COMMENTI -- */
function contacaratteri(target,contatore,massimo){
 	StrLen = target.value.length;
	if(StrLen > massimo ){
		target.value = target.value.substring(0,massimo);
		CharsLeft = 0;
	}
	else {
		CharsLeft = massimo - StrLen;
	}
	document.getElementById("contatore"+contatore).value = massimo - target.value.length;
}

/* -- MULTIMEDIA -- */
function caricamedia(fileinput,idfile,posizione,immagine,w,h){ // carica i file multimediali
	var start=fileinput.length-3;
	var end=fileinput.length;
	var tipo = fileinput.substr(start,end);

	
	document.write("<p>");
	switch (tipo){
		case "mp3":
			if (tipobrowser == 1){
				document.write("<object class='audio' id='"+idfile+"' classid='clsid:22d6f312-b0f6-11d0-94ab-0080c74c7e95'>");
				document.write("<param name='filename' value='"+fileinput+"'>");
			}
	 		else{
				document.write("<object class='audio' id='"+idfile+"' data='"+fileinput+"'>");
			}
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='type' value='audio/x-mpeg'>");
			break;
		case "wmv":
			if (tipobrowser == 1){
				document.write("<object class='video"+posizione+"' id='"+idfile+"' classid='clsid:6BF52A52-394A-11d3-B153-00C04F79FAA6'>");
				document.write("<param name='url' value='"+fileinput+"'>");
				document.write("<param name='UIMode' value='full'>");
				document.write("<param name='CanSeek' value='true'>");
				document.write("<param name='enable' value='true'>");
				document.write("<param name='CanSeekToMarkers' value='true'>");
			}
			else{
	      			document.write("<object class='video"+posizione+"' id='"+idfile+"' data='"+fileinput+"'>");
				document.write("<param name='type' value='video/x-ms-wmv'>");
				document.write("<param name='controls' value='true'>");
				document.write("<param name='enable' value='false'>");
				document.write("<param name='UIMode' value='full'>");
				document.write("<param name='CanSeek' value='true'>");
				document.write("<param name='CanSeekToMarkers' value='true'>");
			}
			document.write("<img src='"+immagine+"' alt='' width='"+w+"' height='"+h+"'>");
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='volume' value='60'>");
			break;
		case "mov":
			if (tipobrowser == 1){
				document.write("<object class='video"+posizione+"' id='"+idfile+"' classid='clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B' codebase='http://www.apple.com/qtactivex/qtplugin.cab'>");
				document.write("<param name='src' value='"+fileinput+"'>");
			}
			else{
      				document.write("<object class='video"+posizione+"' id='"+idfile+"' data='"+fileinput+"'>");
				document.write("<param name='type' value='video/x-quicktime'>");
			}
				document.write("<param name='autoplay' value='false'>");
				document.write("<param name='showcontrols' value='true'>");
				document.write("<param name='scale' value='tofit'>");
				document.write("<param name='volume' value='60'>");
			break;
		case "rpm":
			if (tipobrowser == 1){
				document.write("<object class='video"+posizione+"' classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'>");
				document.write("<param name='src' value='"+fileinput+"'>");
				document.write("<param name='autostart' value='false'>");
				document.write("<param name='controls' value='ImageWindow'>");
				document.write("<param name='console' value='video1'>");
				document.write("<param name='maintainaspect' value='true'>");
				document.write("</object>");
				document.write("<object class='videorp2"+posizione+"' id='"+idfile+"' classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'>");
				document.write("<param name='src' value='"+fileinput+"'>");
				document.write("<param name='console' value='video1'>");
				document.write("<param name='controls' value='ControlPanel'>");
			}
			else{
				document.write("<object class='video"+posizione+"' id='"+idfile+"' data='"+fileinput+"'>");
				document.write("<param name='src' value='"+fileinput+"'>");
				document.write("<param name='type' value='video/x-pn-realaudio-plugin'>");
				document.write("<param name='autostart' value='false'>");
//				document.write("<param name='console' value='_unique'>");
				document.write("<param name='controls' value='ControlPanel'>");
				document.write("<param name='maintainaspect' value='true'>");
			}
			break;
		case "swf":
				document.write("<object class='animazione"+posizione+"' id='"+idfile+"' type='application/x-shockwave-flash' data='"+fileinput+"'>");
   				document.write("<param name='movie' value='"+fileinput+"'>");
   				document.write("<param name='play' value='false'>");
				document.write("<img src='"+immagine+"' alt='' width='"+w+"' height='"+h+"'>");
			break;
		}
	document.write("</object>");
}

function caricasuono(id_audio,fileaudio){ // carica i file audio
	if (plugin_qt + plugin_wm + plugin_rp > 0){
		if (tipobrowser == 1){
			document.write("<object class='audio' id='audio_"+id_audio+"' classid='clsid:22d6f312-b0f6-11d0-94ab-0080c74c7e95'>");
			document.write("<param name='filename' value='"+fileaudio+"'>");
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='type' value='audio/x-mpeg'>");
			document.write("</object>");
		}
	 	else{
			document.write("<object class='audio' id='audio_"+id_audio+"' data='"+fileaudio+"'>");
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='type' value='audio/x-mpeg'>");
			document.write("</object>");
		}
	}
}

function caricavideo(filevideo,posizione){ // carica i file video
	if (tipobrowser == 1){
		if (plugin_wm == 1){
			document.write("<object class='video"+posizione+"' id='videowm_"+filevideo+"' classid='clsid:6BF52A52-394A-11d3-B153-00C04F79FAA6'>");
			document.write("<param name='url' value='"+filevideo+".wmv'>");
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='UIMode' value='full'>");
			document.write("<param name='CanSeek' value='true'>");
			document.write("<param name='enable' value='true'>");
			document.write("<param name='CanSeekToMarkers' value='true'>");
			document.write("<param name='volume' value='60'>");
			document.write("</object>");
			return;
		}
		if (plugin_qt == 1){
			document.write("<object class='video"+posizione+"' id='videoqt_"+filevideo+"' classid='clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B' codebase='http://www.apple.com/qtactivex/qtplugin.cab'>");
			document.write("<param name='src' value='"+filevideo+".mov'>");
			document.write("<param name='autoplay' value='false'>");
			document.write("<param name='showcontrols' value='true'>");
			document.write("<param name='scale' value='tofit'>");
			document.write("<param name='volume' value='60'>");
			document.write("</object>");
			return;

		}
		if (plugin_rp == 1){
			document.write("<object class='video"+posizione+"' classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'>");
			document.write("<param name='src' value='"+filevideo+".ram'>");
			document.write("<param name='autostart' value='false'>");
			document.write("<param name='console' value='video1'>");
			document.write("<param name='maintainaspect' value='true'>");
			document.write("<param name='controls' value='ImageWindow'>");
			document.write("</object>");

			document.write("<object class='videorp2"+posizione+"' id='videorp_"+filevideo+"' classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'>");
			document.write("<param name='src' value='"+filevideo+".ram'>");
			document.write("<param name='console' value='video1'>");
			document.write("<param name='controls' value='controlpanel'>");
			document.write("</object>");
			return;
		}

	}
	else{
		if (plugin_qt == 1){
      			document.write("<object class='videosx' id='videoqt_"+filevideo+"' data='"+filevideo+".mov'>");
			document.write("<param name='autoplay' value='false'>");
			document.write("<param name='showcontrols' value='true'>");
			document.write("<param name='scale' value='tofit'>");
			document.write("<param name='type' value='video/x-quicktime'>");
			document.write("<param name='volume' value='60'>");
			document.write("</object>");
			return;
		}
	}
}

function attivamedium(){ // attiva il suono/filmato/animazione tramite pulsante
	multimedia = 1;
	if (document.getElementById(mediumattivo))
		playmedium();
	document.getElementById("pulsantesuonoon").style.display="none";
	document.getElementById("pulsantesuonoff").style.display="inline";
}

function disattivamedium(){ // disattiva il suono/filmato/animazione tramite pulsante
	multimedia = 0;
	stopmedium();
	document.getElementById("pulsantesuonoff").style.display="none";
	document.getElementById("pulsantesuonoon").style.display="inline";
}

function iniziamedium(nomemedium){ // attiva il suono/filmato/animazione
	if (document.getElementById(nomemedium)){
		mediumattivo = nomemedium;
	}
	
	if (mediumattivo!="" && multimedia==1)
		playmedium();
}

function finemedium(){ // termina il suono/filmato/animazione
	stopmedium();
	mediumattivo = "";
}

function avviamedium(){ // attiva il suono/filmato/animazione con ritardo
	if (document.getElementById(mediumattivo)){
		setTimeout("playmedium()",2500);
	}
}

function feedbacksonoro(nomefeedback){ // invia un feedback sonoro
	if (document.getElementById("audio_"+nomefeedback)){
		setTimeout("try{document.getElementById('audio_"+nomefeedback+"').Play()}catch(e){}",100);
	}
}

function playmedium(){ // avvia il suono/filmato/animazione con modalitÃÂÃÂ  differenziate
	var tipomedium = mediumattivo.split("_");
	switch (tipomedium[0]){
		case "audio":
			setTimeout("try{document.getElementById('"+mediumattivo+"').Play()}catch(e){}",100);
			break;
		case "flash":
			try{
				document.getElementById(mediumattivo).Play();
			}
			catch(e){}
			break;
		case "videoqt":
			setTimeout("try{document.getElementById('"+mediumattivo+"').Play()}catch(e){}",500);
			break;
		case "videorp":
			setTimeout("try{document.getElementById('"+mediumattivo+"').DoPlay()}catch(e){}",500);
			break;
		case "videowm":
			setTimeout("try{document.getElementById('"+mediumattivo+"').Controls.Play()}catch(e){}",500);
			break;
	}
}

function stopmedium(){ // interrompe il suono/filmato/animazione con modalitÃÂÃÂ  differenziate
	if (document.getElementById(mediumattivo)){
		var tipomedium = mediumattivo.split("_");
		switch (tipomedium[0]){
			case "audio":
				try{
					document.getElementById(mediumattivo).Stop();
				}
				catch(e){}
				break;
			case "flash":
				try{
					document.getElementById(mediumattivo).StopPlay();
				}
				catch(e){}
				break;
			case "videoqt":
				try{
					document.getElementById(mediumattivo).Stop();
				}
				catch(e){}
				break;
			case "videorp":
				try{
					document.getElementById(mediumattivo).DoStop();
				}
				catch(e){}
				break;
			case "videowm":
				try{
					document.getElementById(mediumattivo).Controls.Stop();
				}
				catch(e){}
				break;
		}
	}
}

/* -- TEST -- */
function verificatest(pagina,rispostaesatta,punti,messaggiook,messaggioko){ // verifica le domande a risposta chiusa
	var contatore = 0;
	var risposta = 0;
	if (paginetest[pagina] > 0){
		inviamessaggio("Hai giÃÂÃÂ  risposto. Vai avanti.",pagina);
		return;
	}
	if (!messaggiook)
		messaggiook = "Risposta esatta!";
	if (!messaggioko)
		messaggioko = "Hai sbagliato!";		
	while (document.getElementById("test"+pagina).elements[contatore]){
		if (document.getElementById("test"+pagina).elements[contatore].checked)
			risposta = contatore + 1;
		contatore++;
	}
	if (risposta == 0)
		inviamessaggio("Non hai ancora risposto",pagina);
	else if (risposta == rispostaesatta){
		inviamessaggio(messaggiook,pagina);
		punteggio = punteggio + punti;
		paginetest[pagina] = 1;
	}
	else {
		inviamessaggio(messaggioko,pagina);
		if (punti > 0)
			paginetest[pagina] = 2;
	}
	riepilogopunteggi(punti);
}

function avantitest(pagina,destinazione){ // accede alla pagina tutoriale se c'ÃÂÃÂ¨ stata risposta al test
	if (paginetest[pagina] > 0)
		tutoriale(destinazione);
	else
		inviamessaggio("Prima devi rispondere!",pagina);
}

function riepilogopunteggi(punti){ // imposta i punteggi nella pagina di riepilogo
	if (punti > 0)
		punteggiomassimo = punteggiomassimo + punti;
	document.getElementById("riepilogopunti").value = punteggio;
	document.getElementById("riepilogopuntimax").value = punteggiomassimo;
}


/* -- RICERCA PLUG-IN -- */
function cercaplugin(){  // cerca i plug-in disponibili in browser diversi da IE
	if (navigator.plugins && navigator.plugins.length > 0){
		for(var i=0;i < navigator.plugins.length;i++){
			if(navigator.plugins[i].name.indexOf("Flash") >= 0 || navigator.plugins[i].description.indexOf("Flash") >= 0)
				plugin_fl = 1;
			if(navigator.plugins[i].name.indexOf("QuickTime") >= 0 || navigator.plugins[i].description.indexOf("Quick Time") >= 0){
				plugin_qt = 1;
				return;
			}
			if(navigator.plugins[i].name.indexOf("Windows Media") >= 0 || navigator.plugins[i].description.indexOf("Windows Media") >= 0){
				plugin_wm = 1;
				return;
			}
			if(navigator.plugins[i].name.indexOf("RealPlayer") >= 0 || navigator.plugins[i].description.indexOf("RealPlayer") >= 0){
				plugin_rp = 1;
				return;
			}
		}
	}
}

function comunicaplugin(){ // elenca i plug-in disponibili
		if (plugin_qt + plugin_wm + plugin_rp == 0)
			document.write("Per gestire audio e video ÃÂÃÂ¨ necessario installare Windows Media Player, Real Player o QuickTime.");
		else{
			document.write("Per gestire audio e video sarÃÂÃÂ  utilizzato ");
			if (plugin_wm == 1)
				document.write("Windows Media Player.");
			if (plugin_rp == 1)
				document.write("Real Player.");
			if (plugin_qt == 1)
				document.write("QuickTime.");
		} 
		if (plugin_fl == 0)
			document.write("<br>Per vedere le animazioni ÃÂÃÂ¨ necessario installare Flash Player.");
		else
			document.write("<br>Flash Player ÃÂÃÂ¨ installato.");
}

/* -- USCITA -- */
function chiudi(){ // predispone la chiusura della finestra del browser
	traccia(); 
	top.close(); 
}

function traccia(){ // memorizza i dati
	var dati = dimensionicarattere+ ","+dimensionipagina+","+multimedia+","+punteggiomassimo+paginetest.join();

	concludicorso(tutorialeattivo,dati);
};

function hidestatus(){
	window.status="";
	return true;
}

function no_rightclick() {
	//return true;
	alert("Funzione non attiva");
	return false;

}

/*-- FUNZIONI PER GESTIONE LINK INTERNI -- */

function tutoriale_id(id_pagina) {
	var blocco_link=0;
	for (var i=1;i<=blocco_id.length;i++) {
		if (blocco_id[i]==id_pagina) blocco_link=i;
	};
	if (blocco_link) tutoriale(blocco_link);

};


function approfondimento_id(id_pagina) {
	var blocco_link=0;
	for (var i=1;i<=appr_id.length;i++) {
		if (appr_id[i]==id_pagina) blocco_link=i;
	};
	if (blocco_link) approfondimento(blocco_link);

};

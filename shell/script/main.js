/* CMI-API-CMI Scorm Communication Batch */

/*************** variabili **************/
var init_bookmark = new String();
var init_entry = new String();
var init_launch_data = new String();
var init_lesson_mode = new String();
var init_score = new Number();
var init_status = new String();
var init_studentName = new String();
var init_suspendData = new String();
var init_time = new Date();
var init_total_time = new String();
var init_total_time_sec = new Number();
var actual_bookmark = new Number();
var tempoiniziale = new Date().getTime();

//aggiunta fleo
var init_launch_data = new String();

/************* funzioni di gestione del tracciamento **************/
function iniziacorso(){
	LMSInitialize();
	init_bookmark = LMSGetValue("cmi.core.lesson_location");
	init_launch_data=LMSGetValue("cmi.launch_data");
	init_status = LMSGetValue("cmi.core.lesson_status");
	init_suspendData = LMSGetValue("cmi.suspend_data");
	init_score = Number(LMSGetValue("cmi.core.score.raw"));
	
	//aggiunta fleo
	init_launch_data=LMSGetValue("cmi.launch_data");
}

function setcommento(commento){
	if (init_status != "completed" && init_status != "passed"){
		LMSSetValue("cmi.comments", commento);
		LMSCommit("");
		inviamessaggio(messaggiofeedback[11],tutorialeattivo,"messaggio");
	}
}

function concludicorso(status,bookmark,punti,puntimax,dati){
	if (tempoiniziale != 0){
		var tempofinale = new Date().getTime();
		var secondi = ((tempofinale - tempoiniziale) / 1000);
		var tempoformattato = formattatempo(secondi);
	}
	else
		tempoformattato = "00:00:00.0";
	LMSSetValue("cmi.core.lesson_location",bookmark);
	LMSSetValue("cmi.suspend_data",dati);
	LMSSetValue("cmi.core.session_time",tempoformattato);
	LMSSetValue("cmi.core.score.max",puntimax);
	if (init_status != "completed" && init_status != "passed"){
		if (punti > 0)
			LMSSetValue("cmi.core.score.raw",punti);
		else
			LMSSetValue("cmi.core.score.raw",0);
		LMSSetValue("cmi.core.lesson_status",status);
	}
	LMSCommit("");
	LMSSetValue("cmi.core.exit","logout");
	LMSFinish("");
}

/************* funzioni di gestione del tempo **************/
function formattatempo(ts){
	var sec = (ts % 60);
	ts -= sec;
	var tmp = (ts % 3600);  //# of seconds in the total # of minutes
	ts -= tmp;              //# of seconds in the total # of hours
	sec = Math.round(sec*100)/100;
	var strSec = new String(sec);
	var strWholeSec = strSec;
	var strFractionSec = "";
	if (strSec.indexOf(".") != -1){
		strWholeSec = strSec.substring(0, strSec.indexOf("."));
		strFractionSec = strSec.substring(strSec.indexOf(".")+1, strSec.length);
	}
	if (strWholeSec.length < 2)
		strWholeSec = "0" + strWholeSec;
	strSec = strWholeSec;
	if (strFractionSec.length)
		strSec = strSec+ "." + strFractionSec;
	if ((ts % 3600) != 0 )
		var hour = 0;
	else
		var hour = (ts / 3600);
	if ( (tmp % 60) != 0 )
		var min = 0;
	else
		var min = (tmp / 60);
	if ((new String(hour)).length < 2)
		hour = "0"+hour;
	if ((new String(min)).length < 2)
		min = "0"+min;
	var rtnVal = hour+":"+min+":"+strSec;
	return rtnVal;
}

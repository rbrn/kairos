/* CMI-API-CMI Scorm Communication Batch */

/*************** variabili **************/

var init_studentName = new String();
var init_bookmark = new String();
var init_status = new String();
var init_lesson_mode = new String();
var init_entry = new String();
var init_suspendData = new String();
var init_time = new Date();
var init_total_time = new String();
var init_total_time_sec = new Number();
var init_score = new Number();
var actual_bookmark = new Number();
var startDate;

/************* funzioni  **************/
function iniziacorso(){
	LMSInitialize();
	init_bookmark = LMSGetValue("cmi.core.lesson_location");
	init_status = LMSGetValue("cmi.core.lesson_status");
	init_suspendData = LMSGetValue("cmi.suspend_data");
	init_score = Number(LMSGetValue("cmi.core.score.raw"));
	
	startTimer();
	
}

function setcommento(commento){
	if ((init_status != "completed") && (init_status != "passed")){
      		LMSSetValue("cmi.comments", commento);
		LMSCommit("");
	}
}

function concludicorso(status,bookmark,punteggio,dati){
	computeTime();
	var parametri = dati.split(",");
	punteggiomassimo = Number(parametri[3]);
	LMSSetValue("cmi.core.lesson_location",bookmark);
	LMSSetValue("cmi.suspend_data",dati);
	if (init_status != "completed" && init_status != "passed"){
		LMSSetValue("cmi.core.score.raw",punteggio);
		LMSSetValue("cmi.core.score.max",punteggiomassimo);
		LMSSetValue("cmi.core.lesson_status",status);
	}
	LMSCommit("");
	LMSSetValue("cmi.core.exit","logout");
	LMSFinish("");
}

function startTimer()
{
   startDate = new Date().getTime();
}

function computeTime()
{
   if ( startDate != 0 )
   {
      var currentDate = new Date().getTime();
      var elapsedSeconds = ( (currentDate - startDate) / 1000 );
      var formattedTime = convertTotalSeconds( elapsedSeconds );
   }
   else
   {
      formattedTime = "00:00:00.0";
   }
	
   LMSSetValue( "cmi.core.session_time", formattedTime );
   		
}

function convertTotalSeconds(ts)
{
   var sec = (ts % 60);

   ts -= sec;
   var tmp = (ts % 3600);  //# of seconds in the total # of minutes
   ts -= tmp;              //# of seconds in the total # of hours

   // convert seconds to conform to CMITimespan type (e.g. SS.00)
   sec = Math.round(sec*100)/100;
   
   var strSec = new String(sec);
   var strWholeSec = strSec;
   var strFractionSec = "";

   if (strSec.indexOf(".") != -1)
   {
      strWholeSec =  strSec.substring(0, strSec.indexOf("."));
      strFractionSec = strSec.substring(strSec.indexOf(".")+1, strSec.length);
   }
   
   if (strWholeSec.length < 2)
   {
      strWholeSec = "0" + strWholeSec;
   }
   strSec = strWholeSec;
   
   if (strFractionSec.length)
   {
      strSec = strSec+ "." + strFractionSec;
   }


   if ((ts % 3600) != 0 )
      var hour = 0;
   else var hour = (ts / 3600);
   if ( (tmp % 60) != 0 )
      var min = 0;
   else var min = (tmp / 60);

   if ((new String(hour)).length < 2)
      hour = "0"+hour;
   if ((new String(min)).length < 2)
      min = "0"+min;

   var rtnVal = hour+":"+min+":"+strSec;

   return rtnVal;
}
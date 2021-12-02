/*********** AICC call ***********/


/*****************************************************************************************************************/
// Typical API Calls  
//
// keyName					Return Value			Comment
/*****************************************************************************************************************/
// "cmi.core.student_id"			CMIIdentifier
// "cmi.core.student_name"			CMIString255
// "cmi.core.lesson_location"			CMIString255			+++++ BOOKMARK ++++++
// "cmi.core.credit"				CMIVocabulary
// "cmi.core.lesson_status"		 	CMIVocabulary			....
// "cmi.core.entry"			 	CMIVocabulary			ab-initio/resume/[empty string] student has been in the AU before.
// "cmi.core.score.raw"				CMIDecimal or CMIBlank
// "cmi.core.score.max"				CMIDecimal or CMIBlank
// "cmi.core.score.min"				CMIDecimal or CMIBlank
// "cmi.core.total_time"		 	CMITimespan			total time of student's sessions
// "cmi.core.lesson_mode"		 	CMIVocabulary			browse/normal/review
// "cmi.suspend_data"				CMIString4096			+++++ BOOKMARK?? ++++++
// "cmi.launch_data"				CMIString4096
// "cmi.student_data.attempt_number"	 	CMIInteger
// "cmi.student_data.mastery_score"	 	CMIDecimal
// "cmi.student_data.max_time_allowed"		CMITimespan
// "cmi.student_data.time_limit_action"	 	CMIVocabulary
/****************************************************************************************************************/

/*********** Soft API redirection ***********/
/*          [all AICC API function]         */
/*********** FUNZIONI DI GESTIONE DATI ****/
var datigvp = new String();
datipiattaforma = new Array();
vocipiattaforma = new Array();
	vocipiattaforma [0] = "cmi.core.student_id";
	vocipiattaforma [1] =  "cmi.core.student_name";
	vocipiattaforma [2] =  "cmi.core.lesson_location";
	vocipiattaforma [3] =  "cmi.core.credit";
	vocipiattaforma [4] =  "cmi.core.lesson_status";
	vocipiattaforma [5] = "cmi.core.entry";
	vocipiattaforma [6] =  "cmi.core.score.raw";
	vocipiattaforma [7] = "cmi.core.score.max";
	vocipiattaforma [8] =  "cmi.core.score.min";
	vocipiattaforma [9] =  "cmi.core.total_time";
	vocipiattaforma [10] =  "cmi.core.lesson_mode";
	vocipiattaforma [11] =  "cmi.suspend_data";
	vocipiattaforma [12] =  "cmi.launch_data";
	vocipiattaforma [13] =  "cmi.student_data.attempt_number";
	vocipiattaforma [14] =  "cmi.student_data.mastery_score";
	vocipiattaforma [15] =  "cmi.student_data.max_time_allowed";
	vocipiattaforma [16] = "cmi.student_data.time_limit_action";
	vocipiattaforma [17] = "cmi.comments";
	
/*********** FUNZIONI DI SCRITTURA ****/
function LMSSetValue(name,value){
	for (var i=0; i<18; i++){
		if (name==vocipiattaforma [i]){
			datipiattaforma [i] = value;
			return;
		}
	}
}

function LMSCommit(parameter){
	var valore = new String();
	for (var i=0; i<17; i++){
		valore = valore + datipiattaforma [i] +":";
	}
	var nameEQ = codice + "=";
	var date = new Date();
	date.setTime(date.getTime()+(1000*24*60*60*1000));
	var expires = "; expires="+date.toGMTString();
	document.cookie = nameEQ+valore+expires+"; path=/";
	nameEQ = codice + "c" + "=";
	valore = datipiattaforma [17];
	document.cookie = nameEQ+valore+expires+"; path=/";		
}

/*********** FUNZIONI DI LETTURA ****/
function LMSInitialize(parametro){
	datigvp = caricadati(codice);
	if (datigvp != null){
	var ca = datigvp.split(':');
		for(var i=0;i < ca.length;i++){
			var c = ca[i];
			while (c.charAt(0)==' ') c = c.substring(1,c.length);
			datipiattaforma[i]= c;
			if (c.indexOf(datigvp) == 0) return c.substring(datigvp.length,c.length);
		}
	}
	else {
		for (var i=0; i<17; i++){
			datipiattaforma [i] = "";
		}
	}
}
		
function caricadati(name){
	var nameEQ = name + "=";
	var ca = document.cookie.split(';');
	for(var i=0;i < ca.length;i++){
		var c = ca[i];
		while (c.charAt(0)==' ') c = c.substring(1,c.length);
		if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
	}
	return null;
}

function LMSGetValue(name){
	for (var i=0; i<17; i++){
		if (name==vocipiattaforma [i]){
			return datipiattaforma [i];
		}
	}
}

/*********** FUNZIONI DI PIATTAFORMA NON SUPPORTATE ***********/
function LMSFinish(parameter){
	return;
}
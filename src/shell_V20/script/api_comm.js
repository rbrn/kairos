/*
	CMI-API-CMI Scorm Communication Script
	ver 1.01
*/

debug = false;

/*********** AICC/SCORM call ***********/

	/*********** Soft API detection ***********/
	API = findAPI(window);
	if(API == null){
		var debugCalling = debugCall("Error: could not find API", null);
	}
	function findAPI(win){
		if(win.API != null){
			return win.API;	
		}else if(win.parent == null || win.parent == win){
			if(win.opener != null){
				return findAPI(win.opener);
			}else{
				return null;
			}
		}else{
			return findAPI(win.parent);
		}
	}
	
	/********************************************/
	
	
	function debugCall (message2show, response){
		if(debug) alert(message2show + "\nreturn: " +response);
		return response;
	}
	
	function checkSetCondition(){
		return ( API!=null && init_lesson_mode!="browse" && init_lesson_mode!="review" && init_status!="completed" && init_status!="passed" );
	}
	/*********** Soft API redirection ***********/
	/*          [all AICC API function]         */
	
function LMSGetValue(keyName){
	try{
		var response = (API == null) ? false : API.LMSGetValue(keyName);
		return (debug) ? debugCall("LMSGetValue("+keyName+")\n", response): response ;
	}
	catch(e){}
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
		// "cmi.core.score.raw"			 	CMIDecimal or CMIBlank
		// "cmi.core.score.max"			 	CMIDecimal or CMIBlank
		// "cmi.core.score.min"			 	CMIDecimal or CMIBlank
		// "cmi.core.total_time"		 	CMITimespan			total time of student's sessions
		// "cmi.core.lesson_mode"		 	CMIVocabulary			browse/normal/review
		// "cmi.suspend_data"			 	CMIString4096			+++++ BOOKMARK?? ++++++
		// "cmi.launch_data"			 	CMIString4096
		// "cmi.student_data.attempt_number"	 	CMIInteger
		// "cmi.student_data.mastery_score"	 	CMIDecimal
		// "cmi.student_data.max_time_allowed"	 	CMITimespan
		// "cmi.student_data.time_limit_action"	 	CMIVocabulary
		/****************************************************************************************************************/
}

function LMSSetValue(keyName,keyValue){
	try{
		var response = checkSetCondition() ? API.LMSSetValue(keyName,keyValue) : false ;
		return (debug) ? debugCall("LMSSetValue("+keyName+","+keyValue+")\n", response) : response ;
	}
	catch(e){}
}

function LMSCommit(parameter){
	try{
		var response = checkSetCondition() ? API.LMSCommit("") : false ;
		return (debug) ? debugCall("LMSCommit("+parameter+")\n", response) : response ;
	}
	catch(e){}
}

function LMSInitialize(parameter){
	try{
		var response = (API == null) ? false : API.LMSInitialize("");
		return (debug) ? debugCall("LMSInitialize("+parameter+")\n", response) : response ;
	}
	catch(e){}
}

function LMSFinish(parameter){
	try{
		var response = (API == null) ? false : API.LMSFinish("");
		return (debug) ? debugCall("LMSFinish("+parameter+")\n", response) : response ;
	}
	catch(e){}
}

function LMSGetLastError(){
	try{
		var response = (API == null) ? false : API.LMSGetLastError();
		return (debug) ? debugCall("LMSGetLastError()\n", response) : response ;
	}
	catch(e){}
}

function LMSGetErrorString(errorNumber){
	try{
		var response = (API == null) ? false : API.LMSGetErrorString(errorNumber);
		return (debug) ? debugCall("LMSGetErrorString("+errorNumber+")\n", response) : response ;
	}
	catch(e){}
}

function LMSGetDiagnostic(parameter){
	try{
		var response = (API == null) ? false : API.LMSGetDiagnostic(parameter);
		return (debug) ? debugCall("LMSGetDiagnostic("+parameter+")\n", response) : response ;
	}
	catch(e){}
}

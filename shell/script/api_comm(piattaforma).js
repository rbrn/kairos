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
		var response = (API == null) ? false : API.LMSGetValue(keyName);
		return (debug) ? debugCall("LMSGetValue("+keyName+")\n", response): response ;
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
		var response = checkSetCondition() ? API.LMSSetValue(keyName,keyValue) : false ;
		return (debug) ? debugCall("LMSSetValue("+keyName+","+keyValue+")\n", response) : response ;
		/*****************************************************************************************************************************************/
		// Typical API Calls                            			
		//                                              			
		// keyName					keyValue		Return Value			Comment
		/*****************************************************************************************************************************************/
		// "cmi.core.lesson_location"						CMIString255			+++++ BOOKMARK ++++++
		// "cmi.core.exit"				time-out/suspend/logout	CMIVocabulary
		// "cmi.core.lesson_status"		 	p/c/f/i/b/n		CMIVocabulary			passed/completed/failed/incomplete/browsed/not attempted
		// "cmi.core.score.raw"			 				CMIDecimal or CMIBlank
		// "cmi.core.session_time"						CMITimespan
		// "cmi.suspend_data"			 				CMIString4096			+++++ BOOKMARK?? ++++++
		// "cmi.student_data.attempt_number"	 				CMIInteger
		// "cmi.student_data.mastery_score"	 				CMIDecimal
		// "cmi.student_data.max_time_allowed"	 				CMITimespan
		// "cmi.student_data.time_limit_action"	 				CMIVocabulary
		/*****************************************************************************************************************************************/
	}
	function LMSCommit(parameter){
		var response = checkSetCondition() ? API.LMSCommit("") : false ;
		return (debug) ? debugCall("LMSCommit("+parameter+")\n", response) : response ;
	}
	function LMSInitialize(parameter){
		var response = (API == null) ? false : API.LMSInitialize("");
		return (debug) ? debugCall("LMSInitialize("+parameter+")\n", response) : response ;
	}
	function LMSFinish(parameter){
		var response = (API == null) ? false : API.LMSFinish("");
		return (debug) ? debugCall("LMSFinish("+parameter+")\n", response) : response ;
	}
	function LMSGetLastError(){
		var response = (API == null) ? false : API.LMSGetLastError();
		return (debug) ? debugCall("LMSGetLastError()\n", response) : response ;
	}
	function LMSGetErrorString(errorNumber){
		var response = (API == null) ? false : API.LMSGetErrorString(errorNumber);
		return (debug) ? debugCall("LMSGetErrorString("+errorNumber+")\n", response) : response ;
	}
	function LMSGetDiagnostic(parameter){
		var response = (API == null) ? false : API.LMSGetDiagnostic(parameter);
		return (debug) ? debugCall("LMSGetDiagnostic("+parameter+")\n", response) : response ;
	}
	/********************************************/

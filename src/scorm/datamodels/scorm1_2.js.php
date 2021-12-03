<?php
require "../../include/init_sito.inc";
$scoid=$_REQUEST['scoid'];
$launch_data=$_REQUEST['launch_data'];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_utente=$kairos_cookie[0];

$query="SELECT * FROM scorm_scoes_track WHERE userid='$id_utente' AND scoid='$scoid' AND element='cmi.core.lesson_status'";

$result=$mysqli->query($query);
$riga=$result->fetch_array();
if (!$riga) {
	$stato="not attempted";
} else {
	$stato=$riga['value'];
};

$lesson_mode="";
if ($stato=="completed") $lesson_mode="review";

$query="SELECT * FROM scorm_scoes_track WHERE userid='$id_utente' AND scoid='$scoid' AND element='cmi.suspend_data'";

$result=$mysqli->query($query);
$riga=$result->fetch_array();
$suspend_data=$riga['value'];

$query="SELECT * FROM scorm_scoes_track WHERE userid='$id_utente' AND scoid='$scoid' AND element='cmi.core.lesson_location'";

$result=$mysqli->query($query);
$riga=$result->fetch_array();
$lesson_location=$riga['value'];


$query="SELECT * FROM scorm_scoes_track WHERE userid='$id_utente' AND scoid='$scoid' AND element='cmi.core.score.raw'";

$result=$mysqli->query($query);
$riga=$result->fetch_array();
$score_raw=$riga['value'];

?>
//
// SCORM 1.2 API Implementation
//
    // Standard Data Type Definition
    CMIString256 = '^.{0,255}$';
    //CMIString4096 = '^[.|\\n|\\r]{0,4095}$';
    CMIString4096 = '^.{0,4096}$';
    CMITime = '^([0-2]{1}[0-9]{1}):([0-5]{1}[0-9]{1}):([0-5]{1}[0-9]{1})(\.[0-9]{1,2})?$';
    CMITimespan = '^([0-9]{2,4}):([0-9]{2}):([0-9]{2})(\.[0-9]{1,2})?$';
    CMIInteger = '^\\d+$';
    CMISInteger = '^-?([0-9]+)$';
    CMIDecimal = '^-?([0-9]{0,3})(\.[0-9]{1,2})?$';
    CMIIdentifier = '^\\w{1,255}$';
    CMIFeedback = CMIString256; // This must be redefined
    CMIIndex = '[._](\\d+).';
    // Vocabulary Data Type Definition
    CMIStatus = '^passed$|^completed$|^failed$|^incomplete$|^browsed$';
    CMIStatus2 = '^passed$|^completed$|^failed$|^incomplete$|^browsed$|^not attempted$';
    CMIExit = '^time-out$|^suspend$|^logout$|^$';
    CMIType = '^true-false$|^choice$|^fill-in$|^matching$|^short-answer$|^performance$|^sequencing$|^likert$|^numeric$';
    CMIResult = '^correct$|^wrong$|^unanticipated$|^neutral$|^([0-9]{0,3})?(\.[0-9]{1,2})?$';
    NAVEvent = '^previous$|^continue$';
    // Children lists
    cmi_children = 'core, suspend_data, launch_data, comments, objectives, student_data, student_preference, interactions';
    core_children = 'student_id, student_name, lesson_location, credit, lesson_status, entry, score, total_time, lesson_mode, exit, session_time';
    score_children = 'raw, min, max';
    objectives_children = 'id, score, status';
    student_data_children = 'mastery_score, max_time_allowed, time_limit_action';
    student_preference_children = 'audio, language, speed, text';
    interactions_children = 'id, objectives, time, type, correct_responses, weighting, student_response, result, latency';
    // Data ranges
    score_range = '0#100';
    audio_range = '-1#100';
    speed_range = '-100#100';
    weighting_range = '-100#100';
    text_range = '-1#1';
    // The SCORM 1.2 data model
    var datamodel =  {
        'cmi._children':{'defaultvalue':cmi_children, 'mod':'r', 'writeerror':'402'},
        'cmi._version':{'defaultvalue':'3.4', 'mod':'r', 'writeerror':'402'},
        'cmi.core._children':{'defaultvalue':core_children, 'mod':'r', 'writeerror':'402'},
        'cmi.core.student_id':{'defaultvalue':'<?php echo $id_utente ?>', 'mod':'rw', 'writeerror':'403'},
        'cmi.core.student_name':{'defaultvalue':'<?php echo $nome_utente?>', 'mod':'re', 'writeerror':'403'},
        'cmi.core.lesson_location':{'defaultvalue':'<?php echo $lesson_location?>', 'format':CMIString256, 'mod':'rw', 'writeerror':'405'},
        'cmi.core.credit':{'defaultvalue':'', 'mod':'rw', 'writeerror':'403'},
        'cmi.core.lesson_status':{'defaultvalue':'<?php echo $stato ?>', 'format':CMIStatus, 'mod':'rw', 'writeerror':'405'},
        'cmi.core.entry':{'defaultvalue':'', 'mod':'r', 'writeerror':'403'},
        'cmi.core.score._children':{'defaultvalue':score_children, 'mod':'r', 'writeerror':'402'},
        'cmi.core.score.raw':{'defaultvalue':'<?php echo $score_raw ?>', 'format':CMIDecimal, 'range':score_range, 'mod':'rw', 'writeerror':'405'},
        'cmi.core.score.max':{'defaultvalue':'', 'format':CMIDecimal, 'range':score_range, 'mod':'rw', 'writeerror':'405'},
        'cmi.core.score.min':{'defaultvalue':'', 'format':CMIDecimal, 'range':score_range, 'mod':'rw', 'writeerror':'405'},
        'cmi.core.total_time':{'defaultvalue':'', 'mod':'r', 'writeerror':'403'},
        'cmi.core.lesson_mode':{'defaultvalue':'<?php echo $lesson_mode ?>', 'mod':'r', 'writeerror':'403'},
        'cmi.core.exit':{'defaultvalue':'', 'format':CMIExit, 'mod':'w', 'readerror':'404', 'writeerror':'405'},
        'cmi.core.session_time':{'format':CMITimespan, 'mod':'w', 'defaultvalue':'00:00:00', 'readerror':'404', 'writeerror':'405'},
        'cmi.suspend_data':{'defaultvalue':'<?php echo $suspend_data ?>', 'format':CMIString4096, 'mod':'rw', 'writeerror':'405'},
        'cmi.launch_data':{'defaultvalue':'<?php echo $launch_data ?>', 'mod':'r', 'writeerror':'403'},
        'cmi.comments':{'defaultvalue':'', 'format':CMIString4096, 'mod':'rw', 'writeerror':'405'},
        'cmi.comments_from_lms':{'mod':'r', 'writeerror':'403'},
        'cmi.objectives._children':{'defaultvalue':objectives_children, 'mod':'r', 'writeerror':'402'},
        'cmi.objectives._count':{'mod':'r', 'defaultvalue':'0', 'writeerror':'402'},
        'cmi.objectives.n.id':{'pattern':CMIIndex, 'format':CMIIdentifier, 'mod':'rw', 'writeerror':'405'},
        'cmi.objectives.n.score._children':{'pattern':CMIIndex, 'mod':'r', 'writeerror':'402'},
        'cmi.objectives.n.score.raw':{'defaultvalue':'', 'pattern':CMIIndex, 'format':CMIDecimal, 'range':score_range, 'mod':'rw', 'writeerror':'405'},
        'cmi.objectives.n.score.min':{'defaultvalue':'', 'pattern':CMIIndex, 'format':CMIDecimal, 'range':score_range, 'mod':'rw', 'writeerror':'405'},
        'cmi.objectives.n.score.max':{'defaultvalue':'', 'pattern':CMIIndex, 'format':CMIDecimal, 'range':score_range, 'mod':'rw', 'writeerror':'405'},
        'cmi.objectives.n.status':{'pattern':CMIIndex, 'format':CMIStatus2, 'mod':'rw', 'writeerror':'405'},
        'cmi.student_data._children':{'defaultvalue':student_data_children, 'mod':'r', 'writeerror':'402'},
        'cmi.student_data.mastery_score':{'defaultvalue':'', 'mod':'r', 'writeerror':'403'},
        'cmi.student_data.max_time_allowed':{'defaultvalue':'', 'mod':'r', 'writeerror':'403'},
        'cmi.student_data.time_limit_action':{'defaultvalue':'', 'mod':'r', 'writeerror':'403'},
        'cmi.student_preference._children':{'defaultvalue':student_preference_children, 'mod':'r', 'writeerror':'402'},
        'cmi.student_preference.audio':{'defaultvalue':'0', 'format':CMISInteger, 'range':audio_range, 'mod':'rw', 'writeerror':'405'},
        'cmi.student_preference.language':{'defaultvalue':'', 'format':CMIString256, 'mod':'rw', 'writeerror':'405'},
        'cmi.student_preference.speed':{'defaultvalue':'0', 'format':CMISInteger, 'range':speed_range, 'mod':'rw', 'writeerror':'405'},
        'cmi.student_preference.text':{'defaultvalue':'0', 'format':CMISInteger, 'range':text_range, 'mod':'rw', 'writeerror':'405'},
        'cmi.interactions._children':{'defaultvalue':interactions_children, 'mod':'r', 'writeerror':'402'},
        'cmi.interactions._count':{'mod':'r', 'defaultvalue':'0', 'writeerror':'402'},
        'cmi.interactions.n.id':{'pattern':CMIIndex, 'format':CMIIdentifier, 'mod':'w', 'readerror':'404', 'writeerror':'405'},
        'cmi.interactions.n.objectives._count':{'pattern':CMIIndex, 'mod':'r', 'defaultvalue':'0', 'writeerror':'402'},
        'cmi.interactions.n.objectives.n.id':{'pattern':CMIIndex, 'format':CMIIdentifier, 'mod':'w', 'readerror':'404', 'writeerror':'405'},
        'cmi.interactions.n.time':{'pattern':CMIIndex, 'format':CMITime, 'mod':'w', 'readerror':'404', 'writeerror':'405'},
        'cmi.interactions.n.type':{'pattern':CMIIndex, 'format':CMIType, 'mod':'w', 'readerror':'404', 'writeerror':'405'},
        'cmi.interactions.n.correct_responses._count':{'pattern':CMIIndex, 'mod':'r', 'defaultvalue':'0', 'writeerror':'402'},
        'cmi.interactions.n.correct_responses.n.pattern':{'pattern':CMIIndex, 'format':CMIFeedback, 'mod':'w', 'readerror':'404', 'writeerror':'405'},
        'cmi.interactions.n.weighting':{'pattern':CMIIndex, 'format':CMIDecimal, 'range':weighting_range, 'mod':'w', 'readerror':'404', 'writeerror':'405'},
        'cmi.interactions.n.student_response':{'pattern':CMIIndex, 'format':CMIFeedback, 'mod':'w', 'readerror':'404', 'writeerror':'405'},
        'cmi.interactions.n.result':{'pattern':CMIIndex, 'format':CMIResult, 'mod':'w', 'readerror':'404', 'writeerror':'405'},
        'cmi.interactions.n.latency':{'pattern':CMIIndex, 'format':CMITimespan, 'mod':'w', 'readerror':'404', 'writeerror':'405'},
        'nav.event':{'defaultvalue':'', 'format':NAVEvent, 'mod':'w', 'readerror':'404', 'writeerror':'405'}
    };
    //
    // Datamodel inizialization
    //
    var cmi = new Object();
        cmi.core = new Object();
        cmi.core.score = new Object();
        cmi.objectives = new Object();
        cmi.student_data = new Object();
        cmi.student_preference = new Object();
        cmi.interactions = new Object();

    // Navigation Object
    var nav = new Object();

    for (element in datamodel) {
        if (element.match(/\.n\./) == null) {
            if ((typeof eval('datamodel["'+element+'"].defaultvalue')) != 'undefined') {
                eval(element+' = datamodel["'+element+'"].defaultvalue;');
            } else {
                eval(element+' = "";');
            }
        }
    }


    if (cmi.core.lesson_status == '') {
        cmi.core.lesson_status = 'not attempted';
    } 
    
	
    //
    // API Methods definition
    //
    var Initialized = false;

    function LMSInitialize (param) {
        errorCode = "0";
        if (param == "") {
            if (!Initialized) {
                Initialized = true;
                errorCode = "0";
                return "true";
            } else {
                errorCode = "101";
            }
        } else {
            errorCode = "201";
        }
        return "false";
    }
    
    function LMSFinish (param) {
        errorCode = "0";
        if (param == "") {
            if (Initialized) {
                Initialized = false;
                result = StoreData(cmi,'finish');  
                return "true";
            } else {
                errorCode = "301";
            }
        } else {
            errorCode = "201";
        }
        return "false";
    }
    
    function LMSGetValue (element) {
        errorCode = "0";
        if (Initialized) {
            if (element !="") {
                expression = new RegExp(CMIIndex,'g');
                elementmodel = element.replace(expression,'.n.');
                if ((typeof eval('datamodel["'+elementmodel+'"]')) != "undefined") {
                    if (eval('datamodel["'+elementmodel+'"].mod') != 'w') {
                            element = element.replace(expression, "_$1.");
                            elementIndexes = element.split('.');
                        subelement = 'cmi';
                        i = 1;
                        while ((i < elementIndexes.length) && (typeof eval(subelement) != "undefined")) {
                            subelement += '.'+elementIndexes[i++];
                        }
                            if (subelement == element) {
                            errorCode = "0";
                            return eval(element);
                        } else {
                            errorCode = "0"; // Need to check if it is the right errorCode
                        }
                    } else {
                        errorCode = eval('datamodel["'+elementmodel+'"].readerror');
                    }
                } else {
                    childrenstr = '._children';
                    countstr = '._count';
                    if (elementmodel.substr(elementmodel.length-childrenstr.length,elementmodel.length) == childrenstr) {
                        parentmodel = elementmodel.substr(0,elementmodel.length-childrenstr.length);
                        if ((typeof eval('datamodel["'+parentmodel+'"]')) != "undefined") {
                            errorCode = "202";
                        } else {
                            errorCode = "201";
                        }
                    } else if (elementmodel.substr(elementmodel.length-countstr.length,elementmodel.length) == countstr) {
                        parentmodel = elementmodel.substr(0,elementmodel.length-countstr.length);
                        if ((typeof eval('datamodel["'+parentmodel+'"]')) != "undefined") {
                            errorCode = "203";
                        } else {
                            errorCode = "201";
                        }
                    } else {
                        errorCode = "201";
                    }
                }
            } else {
                errorCode = "201";
            }
        } else {
            errorCode = "301";
        }
        return "";
    }
    
    function LMSSetValue (element,value) {
        errorCode = "0";
        if (Initialized) {
            if (element != "") {
                expression = new RegExp(CMIIndex,'g');
                elementmodel = element.replace(expression,'.n.');
                if ((typeof eval('datamodel["'+elementmodel+'"]')) != "undefined") {
                    if (eval('datamodel["'+elementmodel+'"].mod') != 'r') {
                        expression = new RegExp(eval('datamodel["'+elementmodel+'"].format'));
                        value = value+'';
                        matches = value.match(expression);
                        if (matches != null) {
                            //Create dynamic data model element
                            if (element != elementmodel) {
                                elementIndexes = element.split('.');
                                subelement = 'cmi';
                                for (i=1;i < elementIndexes.length-1;i++) {
                                    elementIndex = elementIndexes[i];
                                    if (elementIndexes[i+1].match(/^\d+$/)) {
                                        if ((typeof eval(subelement+'.'+elementIndex)) == "undefined") {
                                            eval(subelement+'.'+elementIndex+' = new Object();');
                                            eval(subelement+'.'+elementIndex+'._count = 0;');
                                        }
                                        if (elementIndexes[i+1] == eval(subelement+'.'+elementIndex+'._count')) {
                                            eval(subelement+'.'+elementIndex+'._count++;');
                                        } 
                                        if (elementIndexes[i+1] > eval(subelement+'.'+elementIndex+'._count')) {
                                            errorCode = "201";
                                        }
                                        subelement = subelement.concat('.'+elementIndex+'_'+elementIndexes[i+1]);
                                        i++;
                                    } else {
                                        subelement = subelement.concat('.'+elementIndex);
                                    }
                                    if ((typeof eval(subelement)) == "undefined") {
                                        eval(subelement+' = new Object();');
                                        if (subelement.substr(0,14) == 'cmi.objectives') {
                                            eval(subelement+'.score = new Object();');
                                            eval(subelement+'.score._children = score_children;');
                                            eval(subelement+'.score.raw = "";');
                                            eval(subelement+'.score.min = "";');
                                            eval(subelement+'.score.max = "";');
                                        }
                                        if (subelement.substr(0,16) == 'cmi.interactions') {
                                            eval(subelement+'.objectives = new Object();');
                                            eval(subelement+'.objectives._count = 0;');
                                            eval(subelement+'.correct_responses = new Object();');
                                            eval(subelement+'.correct_responses._count = 0;');
                                        }
                                    }
                                }
                                element = subelement.concat('.'+elementIndexes[elementIndexes.length-1]);
                            }
                            //Store data
                            if (errorCode == "0") {
                                if ((typeof eval('datamodel["'+elementmodel+'"].range')) != "undefined") {
                                    range = eval('datamodel["'+elementmodel+'"].range');
                                    ranges = range.split('#');
                                    value = value*1.0;
                                    if ((value >= ranges[0]) && (value <= ranges[1])) {
                                        eval(element+'="'+value+'";');
                                        errorCode = "0";
                                        return "true";
                                    } else {
                                        errorCode = eval('datamodel["'+elementmodel+'"].writeerror');
                                    }
                                } else {
                                    if (element == 'cmi.comments') {
                                        eval(element+'+="'+value+'";');
                                    } else {
                                        eval(element+'="'+value+'";');
                                    }
                                    errorCode = "0";
                                    return "true";
                                }
                            }
                        } else {
                            errorCode = eval('datamodel["'+elementmodel+'"].writeerror');
                        }
                    } else {
                        errorCode = eval('datamodel["'+elementmodel+'"].writeerror');
                    }
                } else {
                    errorCode = "201"
                }
            } else {
                errorCode = "201";
            }
        } else {
            errorCode = "301";
        }
        return "false";
    }
    
    function LMSCommit (param) {
        errorCode = "0";
        if (param == "") {
            if (Initialized) {
                result = StoreData(cmi,'commit');
                return "true";
            } else {
                errorCode = "301";
            }
        } else {
            errorCode = "201";
        }
        return "false";
    }
    
    function LMSGetLastError () {
        return errorCode;
    }
    
    function LMSGetErrorString (param) {
        if (param != "") {
            var errorString = new Array();
            errorString["0"] = "No error";
            errorString["101"] = "General exception";
            errorString["201"] = "Invalid argument error";
            errorString["202"] = "Element cannot have children";
            errorString["203"] = "Element not an array - cannot have count";
            errorString["301"] = "Not initialized";
            errorString["401"] = "Not implemented error";
            errorString["402"] = "Invalid set value, element is a keyword";
            errorString["403"] = "Element is read only";
            errorString["404"] = "Element is write only";
            errorString["405"] = "Incorrect data type";
            return errorString[param];
        } else {
           return "";
        }
    }
    
    function LMSGetDiagnostic (param) {
        if (param == "") {
            param = errorCode;
        }
        return param;
    }

   
    function CollectData(data,parent) {
        var datastring = '';
        for (property in data) {
            if (typeof data[property] == 'object') {
                datastring += CollectData(data[property],parent+'.'+property);
            } else {
                element = parent+'.'+property;
                expression = new RegExp(CMIIndex,'g');
                elementmodel = element.replace(expression,'.n.');
                if ((typeof eval('datamodel["'+elementmodel+'"]')) != "undefined") {
                    if (eval('datamodel["'+elementmodel+'"].mod') != 'r') {
                        elementstring = '&'+underscore(element)+'='+escape(data[property]);
                        if ((typeof eval('datamodel["'+elementmodel+'"].defaultvalue')) != "undefined") {
                            //if (eval('datamodel["'+elementmodel+'"].defaultvalue') != data[property]) {
                                datastring += elementstring;
                            //}
                        } else {
                            datastring += elementstring;
                        }
                    }
                }
            }
        }
        return datastring;
    }

    function StoreData(data,azione) {
        var datastring = CollectData(data,'cmi');
		datastring='azione='+azione+'&scoid=<?php echo $scoid ?>'+datastring;
        //popupwin(datastring);
		
        var myRequest = NewHttpReq();
        result = DoRequest(myRequest,"<?php echo $PATH_ROOT ?>scorm/datamodel.php",datastring);
        results = result.split('\n');
        errorCode = results[1];
        return results[0];
    }


	function underscore(str) {
    	return str.replace(/\./g,"__");
	}


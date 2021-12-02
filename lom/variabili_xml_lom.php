<?php
$opt_lang=array("x-none","ab","aa","af","sq","am","ar","hy","as","ay","az","ba","eu","bn","dz","bh","bi","br","bg","my","be","km","ca","zh","kw","co","hr","cs","da","nl","en","eo","et","fo","fj","fi","fr","fy","gl","ka","de","el","kl","gn","gu","ha","he","hi","hu","id","ia","ie","iu","ik","ga","is","it","ja","jw","kn","ks","kk","rw","ky","rn","ko","ku","lo","la","lv","ln","lt","lb","mk","mg","ms","ml","mt","gv","mi","mr","mo","mn","na","ne","i-sami-no","no","no-nyn","no-bok","oc","or","om","ps","fa","pl","pt","pa","qu","rm","ro","ru","sm","sg","sa","gd","sr","sh","st","tn","sn","sd","si","ss","sk","sl","so","es","su","sv","sw","tl","tg","ta","tt","te","th","bo","ti","to","ts","tr","tk","tw","ug","uk","ur","uz","vi","vo","cy","wo","xh","yi","yo","za","zu");

sort($opt_lang);

$opt_structure=array("atomic","branched","collection","hierarchical","linear","mixed","networked","parceled");

$opt_aggrlevel=array("1","2","3","4");

$opt_status=array("draft","final","revised","unvailable");

$opt_role=array("author","publisher","unknown","initiator","terminator","validator","editor","graphical designer","technical implementer","content provider","technical validator","educational validator","script writer","instructional designer","subject matter expert");

$opt_role_mm=array("creator","validator");

$opt_format=array("x-none","text/html","text/xml","text/plain","text/css","text/richtext","application/zip","application/pdf","application/octet-stream","application/excel","application/msword","application/mspowerpoint","application/x-javascript","application/x-troff-msvideo","application/x-shockwave-flash","application/x-compressed","application/x-zip-compressed","application/rtf","image/jpeg","image/gif","image/bmp","image/tiff","image/pict","image/x-quicktime","audio/aiff","audio/x-aiff","audio/midi","audio/mpeg","audio/wav","audio/x-mpeg","audio/mpeg3","audio/x-mpeg3","audio/x-realaudio","audio/x-pn-realaudio","audio/x-wav","video/mpeg","video/quicktime","video/avi");

sort($opt_format);

$opt_type=array("operating system","browser");		

$opt_name=array("none","any","ms-windows","macos","linux","unix","pc-dos","multi-os","ms-internet explorer","netscape communicator","mozilla","firefox","safari","opera","amaya","konqueror","camino");		

$opt_intertype=array("active","expositive","mixed");

$opt_learestype=array("exercise","simulation","questionnaire","diagram","figure","graph","index","slide","table","narrative text","exam","experiment","problem statement","self assessment","lecture");

$opt_interlevel=array("very low","low","medium","high","very high");

$opt_ieurole=array("teacher","author","learner","manager");

$opt_context=array("school","higher education","training","other");

$opt_difficulty=array("very easy","easy","medium","difficult","very difficult");

$opt_yn=array("yes","no");

$opt_kind=array("ispartof","haspart","isversionof","hasversion","isformatof","hasformat","references","isreferencedby","isbasedon","isbasisfor","requires","isrequiredby");

$opt_purpose=array("discipline","idea","prerequisite","educational objective","accessibility","restrictions","educational level","skill level","security level","competency");

?>

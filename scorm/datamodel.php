<?php
require "../include/init_sito.inc";
$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBNAME);

$scoid=$_POST["scoid"];
$azione=$_POST["azione"];
$id_utente=$kairos_cookie[0];

$esito = true;

$query="SELECT * FROM scorm_scoes_track WHERE userid='$id_utente' AND scoid='$scoid' AND element='cmi.core.lesson_status'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$stato_sessione=$riga["value"];
if ($stato_sessione<>"completed" and $stato_sessione<>"passed") {
foreach ($_POST as $element => $value) {
	if (substr($element,0,3) == 'cmi') {
		$element = str_replace('__','.',$element);
        $element = preg_replace('/_(\d+)/',".\$1",$element);
		
		$query="SELECT * FROM scorm_scoes_track WHERE userid='$id_utente' AND scoid='$scoid' AND element='$element'";
		$result=$mysqli->query($query);
        if ($result->num_rows) {
			$query="UPDATE scorm_scoes_track SET
			value='$value',
			timemodified=NOW()
			WHERE userid='$id_utente' AND scoid='$scoid' AND element='$element'";
			$result=$mysqli->query($query);
        } else {
            $query="INSERT INTO scorm_scoes_track SET
			userid='$id_utente',
			scormid='0',
			scoid='$scoid',
			element='$element',
			value='$value',
			timemodified=NOW()";
	$result=$mysqli->query($query);
		};
   };  
};
};

if ($esito) {
    echo "true\n0";
} else {
   echo "false\n101";
}

?>


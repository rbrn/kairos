<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
 
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_utente=$kairos_cookie[0];
$id_corso=$_REQUEST["id_corso"];

$query="SELECT id_edizione,stato FROM edizioni WHERE 
id_corso='$id_corso' ORDER BY id_edizione DESC";
$result = $mysqli->query($query);
$riga=$result->fetch_array();

$id_edizione=$riga[id_edizione];
$stato=$riga[stato];

$query="SELECT * FROM iscrizioni_corso WHERE id_utente='$id_utente' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result = $mysqli->query($query);
$riga=$result->fetch_array();
if (!$riga) {
$query="INSERT INTO iscrizioni_corso (id_corso,id_edizione,id_gruppo,id_utente,data_iscrizione) VALUES ('$id_corso','$id_edizione','Generale','$id_utente',NOW())";
    $result = $mysqli->query($query);
};

if ($stato=='attiva') {
	$iscrizione=$stringa[iscrizione_fatta_edizione_attiva];
} else {
	$iscrizione=$stringa[iscrizione_fatta_edizione_inattiva];
};

$msg="<b>$stringa[grazie], $id_utente!</b> <br><br> $stringa[iscrizione_fatta]<br>$iscrizione";
$msg=ereg_replace(" ","%20",$msg);

header("Location:index.php?risorsa=msg&msg=$msg");
			
?>

<?php
require "./include/init_sito.inc";
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

reset($HTTP_POST_VARS);
list($key, $messaggi) = each($HTTP_POST_VARS);
while (list($key, $val) = each($HTTP_POST_VARS)) {
	$id_messaggio=$val;
	
	$query = "SELECT stato,id_mittente,id_destinatario,data_lettura FROM messaggi WHERE id_messaggio=$id_messaggio";
    $result = $mysqli->query($query,$db);
    $riga=$result->fetch_array();
	$stato=$riga["stato"];
	$id_mittente=$riga["id_mittente"];
	$id_destinatario=$riga["id_destinatario"];
	$data_lettura=$riga["data_lettura"];
	if ($stato<>0) {
		$query = "DELETE FROM messaggi WHERE id_messaggio=$id_messaggio";
        $result = $mysqli->query($query,$db);
	} else {
		if ($kairos_cookie[0]==$id_mittente) {
			$nuovo_stato=1;
			if ($data_lettura=='0000-00-00 00:00:00') {
				$query = "DELETE FROM messaggi WHERE id_messaggio=$id_messaggio";
                $result = $mysqli->query($query,$db);
			};
		} else {
			$nuovo_stato=2;
		};
		$query = "UPDATE messaggi SET stato=$nuovo_stato WHERE id_messaggio=$id_messaggio";
        $result = $mysqli->query($query);
	};

};
Header("Location:index.php?risorsa=messaggi&messaggi=$messaggi");
?>

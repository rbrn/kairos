<?php
require "./include/init_sito.inc";

$id_gruppo=$_REQUEST[id_gruppo];
$id_utente=$kairos_cookie[0];

if ($id_gruppo and $id_utente) {
	$db = mysql_connect("localhost",$DBUSER,$DBPWD);
	mysql_select_db($DBASE,$db);			

	$query = "SELECT id_utente FROM iscrizioni_gruppo_pw WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_utente='$id_utente'";
	$result=$mysqli->query($query);

	if (!$result->num_rows) {
		$query="INSERT INTO iscrizioni_gruppo_pw SET"
		." id_corso='$id_corso_s',"
		." id_edizione='$id_edizione_s',"
		." id_utente='$id_utente',"
		." id_gruppo='$id_gruppo'";
        $result = $mysqli->query($query);
	};
			
};

header("Location:gruppo_pw_iscritti.php?id_gruppo=$id_gruppo");
?>

<?php
function date_diff($date1, $date2)
{
//$date1  today, or any other day
//$date2  date to check against

$d1 = explode("-", $date1);
$y1 = $d1[0];
$m1 = $d1[1];
$d1 = $d1[2];

$d2 = explode("-", $date2);
$y2 = $d2[0];
$m2 = $d2[1];
$d2 = $d2[2];

$date1_set = mktime(0,0,0, $m1, $d1, $y1);
$date2_set = mktime(0,0,0, $m2, $d2, $y2);

return(round(($date2_set-$date1_set)/(60*60*24))); 
} 

$da_aa=$_REQUEST["da_aa"];
$da_mm=$_REQUEST["da_mm"];
$da_gg=$_REQUEST["da_gg"];

$a_aa=$_REQUEST["a_aa"];
$a_mm=$_REQUEST["a_mm"];
$a_gg=$_REQUEST["a_gg"];

$dossier=$_REQUEST["dossier"];
$id_gruppo_stat=$_REQUEST["id_gruppo_stat"];
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];

$da_data=$da_aa."-".$da_mm."-".$da_gg." 00:00:00";
$a_data=$a_aa."-".$a_mm."-".$a_gg." 23:59:59";

$da_data1=$da_aa."-".$da_mm."-".$da_gg;
$a_data1=$a_aa."-".$a_mm."-".$a_gg;

$diff=date_diff($da_data1,$a_data1);

if ($diff>7 and $ruolo<>"admin" and $ruolo<>"staff") {
	echo "
<p><span class=titolopagina>$stringa[statistiche_corso]</span><br>
<span class=sottotitolopagina>$stringa[dal]: $da_gg/$da_mm/$da_aa $stringa[al]: $a_gg/$a_mm/$a_aa</span></p>

<p><span class=testo>
$stringa[max_7_giorni]
</span>
</p>";
exit();
};

$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione_s;

$query="SELECT * FROM corso WHERE id_corso='$id_corso_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$descr_corso=$riga["descrizione"];

if ($diff>31) {
	echo "
<p><span class=titolopagina>$stringa[statistiche_corso]</span>
<br>
<span class=sottotitolopagina>$descr_corso: $descr_edizione</span>
</p>
<span class=sottotitolopagina>$stringa[dal]: $da_gg/$da_mm/$da_aa $stringa[al]: $a_gg/$a_mm/$a_aa</span></p>

<p><span class=testo>
$stringa[max_30_giorni]
</span>
</p>";
exit();
};
	
$id_utente=$kairos_cookie[0];

$query="SELECT email FROM utenti WHERE id_utente='$id_utente' LIMIT 1";
$result=$mysqli->query($query);

$riga=$result->fetch_array();
$email_utente=$riga["email"];

$descr_gruppo="";
$tipo_gruppo="";
if ($id_gruppo_stat) {
	if ($id_gruppo_stat<>'99staff') {
	$query="SELECT descrizione,tipo_gruppo FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_stat'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$descr_gruppo=$riga["descrizione"];
	$tipo_gruppo=$riga["tipo_gruppo"];
	} else {
	$descr_gruppo="Staff tutor";
	};
};		

mysql_select_db("atlante",$db);
$query="INSERT INTO stat_job SET
data_stat=now(),
stato='stat_wait',
da_data='$da_data',
a_data='$a_data',
id_gruppo='$id_gruppo_stat',
tipo_gruppo='$tipo_gruppo',
descr_gruppo='$descr_gruppo',
id_corso='$id_corso_s',
id_edizione='$id_edizione_s',
dossier='$dossier',
id_db='$DBASE',
id_utente='$id_utente',
email_utente='$email_utente',
lingua='$lingua'
";
$result=$mysqli->query($query);

mysql_select_db($DBASE,$db);

echo "
<p><span class=titolopagina>$stringa[statistiche_corso]</span><br>
<span class=sottotitolopagina>$stringa[dal]: $da_gg/$da_mm/$da_aa $stringa[al]: $a_gg/$a_mm/$a_aa</span></p>

<p><span class=testo>
$stringa[stat_msg]
<br><br>
[<a href=index.php?risorsa=stats_corso_form&dossier=$dossier&id_corso=$id_corso_s&id_edizione=$id_edizione_s>$stringa[indietro]</a>]
</span>
</p>";


?>
<br>

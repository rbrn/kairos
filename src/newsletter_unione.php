<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

if ($nome_org) {
	$titolo_org=$nome_org;
} else {
	$titolo_org=$cod_area_base;
};

$id_utente=$kairos_cookie[0];
$oggetto=$_REQUEST["oggetto"];
$messaggio_orig=$_REQUEST["messaggio"];
$noadmin=$_REQUEST["noadmin"];
$nostaff=$_REQUEST["nostaff"];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE_UTENTI,$db);

$query="SELECT email,id_utente,pwd_utente FROM utenti WHERE id_utente='$id_utente'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$email_mittente=$riga["email"];
$id_utente_mittente=$riga["id_utente"];
$pwd_utente_mittente=$riga["pwd_utente"];
	
$where="";
if ($noadmin) {
	if ($where) $where .= " AND ";
	$where.="stato<>'3'";
};

if ($nostaff) {
	if ($where) $where .= " AND ";
	$where.="stato<>'2'";
};

$query1="SELECT email,id_utente,pwd_utente FROM utenti";

if ($where) $where = " WHERE ".$where;

$query = $query1.$where;


$result_iscritti=mysql_query($query,$db);


$indice=0;

while ($utente = $result_iscritti->fetch_array()) {
	$email = $utente["email"];
	$id_utente=$utente["id_utente"];
	$pwd_utente=$utente["pwd_utente"];
	
		$elenco[$indice] .= $email.":".$id_utente.":".$pwd_utente;
		$indice++;
	
	
};

$elenco[$indice] .= $email_mittente.":".$id_utente_mittente.":".$pwd_utente_mittente;
$indice++;

$oggetto = stripslashes($oggetto);


for ($i=0;$i<$indice;$i++) {
	list($email_utente,$id_utente,$pwd_utente)=split(":",$elenco[$i]);
	$id_package=uniqid("");	
	$messaggio = stripslashes($messaggio_orig);
	$messaggio = str_replace("[id_utente]",$id_utente,$messaggio);
	$messaggio = str_replace("[pwd_utente]",$pwd_utente,$messaggio);
	
	//echo " email: ($id_package) $email_utente id: $id_utente pw: $pwd_utente <br> $messaggio <br> <hr size=1>";

	mail_job($id_package,"$email_utente","$titolo_org: $oggetto","$messaggio","$email_mittente","$email_mittente","");

	mysql_select_db($DBASE,$db);	
};

$msg="Il messaggio e' stato inviato.";
$msg=str_replace(" ","%20",$msg);
Header("Location:index.php?risorsa=msg&msg=$msg");

?>

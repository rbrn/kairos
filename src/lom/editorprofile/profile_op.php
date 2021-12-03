<?php
require "./config.php";

$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);

$id_profile=$_REQUEST[id_profile];
$descrizione=$_REQUEST[descrizione];
$azione=$_REQUEST[azione];

if ($azione=="modifica") {
	$query="UPDATE profile SET descrizione='$descrizione' WHERE id_profile='$id_profile'";
	$mysqli->query($query);
	Header("Location:index.php");
	exit();
};

$errore="";
$id_profile=trim(str_replace(" ","",$id_profile));
if (!$id_profile) {
	$errore.="Manca identificativo<br>";
};

if (!$errore) {
	$query="SELECT * FROM profile WHERE id_profile='$id_profile'";
	$result=$mysqli->query($query);
	if ($result->num_rows) {
		$errore.="Identificativo giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ esistente <br>";
	};
};

if ($errore) {
	$msg=$errore;
	Header("Location:msg.php?msg=$errore");
	exit();
};

$query="INSERT INTO profile SET id_profile='$id_profile',descrizione='$descrizione'";
$mysqli->query($query);

$query="SELECT * FROM lo_schema WHERE id_profile='default'";
$result=$mysqli->query($query);
while ($riga=$result->fetch_array()) {

	$id_lom=addslashes($riga[id_lom]);
	$id_lom_sup=addslashes($riga[id_lom_sup]);
	$nome=addslashes($riga[nome]);
	$size=addslashes($riga[size]);
	$valuespace=addslashes($riga[valuespace]);
	$langstring=addslashes($riga[langstring]);
	$tipocampo=addslashes($riga[tipocampo]);
	$datetype=addslashes($riga[datetype]);
	$val_default=addslashes($riga[val_default]);
	$obbligatorio=addslashes($riga[obbligatorio]);

	$query1="INSERT INTO lo_schema SET
	id_lom='$id_lom',
	id_profile='$id_profile',
	id_lom_sup='$id_lom_sup',
	nome='$nome',
	size='$size',
	valuespace='$valuespace',
	langstring='$langstring',
	tipocampo='$tipocampo',
	datetype='$datetype',
	val_default='$val_default',
	obbligatorio='$obbligatorio'
	";
	$mysqli->query($query1);
	echo mysql_error();
};
Header("Location:index.php");
?>

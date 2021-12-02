<?php
require "../config.php";

$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);

$id_lom=$_REQUEST[id_lom];
$id_lom_sup=$_REQUEST[id_lom_sup];
$id_profile=$_REQUEST[id_profile];

$nome=$_REQUEST[nome];
$size=$_REQUEST[size];
$valuespace=$_REQUEST[valuespace];
$langstring=$_REQUEST[langstring];
$tipocampo=$_REQUEST[tipocampo];
$datetype=$_REQUEST[datetype];
$val_default=$_REQUEST[val_default];
$obbligatorio=$_REQUEST[obbligatorio];
$commento=$_REQUEST[commento];

if ($obbligatorio=="on") {
	$obbligatorio=1;
} else {
	$obbligatorio=0;
};

if ($langstring=="on") {
	$langstring=1;
} else {
	$langstring=0;
};

$azione=$_REQUEST[azione];
$ex_id_lom=trim($_REQUEST[ex_id_lom]);
$tipo_md=$_REQUEST[tipo_md];

$errore="";
$id_lom=trim(str_replace(" ","",$id_lom));
if (!$id_lom) {
	$errore.="Manca ID LOM<br>";
};

if ((!$errore and $azione=="nuovo") or (!$errore and $azione=="modifica" and $id_lom<>$ex_id_lom)) {
	$query="SELECT * FROM lo_schema WHERE id_lom='$id_lom' AND id_profile='$id_profile'";
	$result=$mysqli->query($query);
	if ($result->num_rows) {
		$errore.="ID LOM giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ in uso <br>";
	};
};

if ($tipo_md=="gruppo") {
	if ($azione=="modifica" and !$errore and $id_lom<>$ex_id_lom) {
		$query="UPDATE lo_schema SET id_lom_sup='$id_lom' WHERE id_lom_sup='$ex_id_lom' AND id_profile='$id_profile'";
		$mysqli->query($query);
	};
};

if ($errore) {
	$msg=$errore;
	Header("Location:msg.php?msg=$errore");
	exit();
};

if ($azione=="modifica") {
	$query="UPDATE lo_schema SET ";
	$where="WHERE id_lom='$ex_id_lom' AND id_profile='$id_profile'";
} else {
	$query="INSERT INTO lo_schema SET ";
	$where="";
}; 

$query .="
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
	obbligatorio='$obbligatorio',
	commento='$commento'
	 ".$where;

$mysqli->query($query);
Header("Location:profile_index.php?id_lom=$id_lom_sup&id_profile=$id_profile");
exit();

	


?>

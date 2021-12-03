<?php
require "./include/init_sito.inc";

$risorsa_padre=$_REQUEST["risorsa_padre"];
$titolo=mysql_real_escape_string($_REQUEST["titolo"]);
$approfondimento=mysql_real_escape_string($_REQUEST["approfondimento"]);
$riepilogo=mysql_real_escape_string($_REQUEST["riepilogo"]);
$glossario=mysql_real_escape_string($_REQUEST["glossario"]);
$id_autore=mysql_real_escape_string($_REQUEST["id_autore"]);
$tipo_pagina=mysql_real_escape_string($_REQUEST["tipo_pagina"]);
$id_alternativo=mysql_real_escape_string($_REQUEST["link_tutoriale"]);

$id_utente=$kairos_cookie[0];
			
$query = "INSERT INTO lo_pagina SET  
titolo='$titolo',
approfondimento='$approfondimento',
riepilogo='$riepilogo',
glossario='$glossario',
tipo_pagina='$tipo_pagina',
id_editor='$id_utente',
id_alternativo='$id_alternativo'
";

if(!$mysqli->query($query)) die($mysqli->error);

$id_pagina= $mysqli->insert_id;

$query="SELECT max(posizione) AS num_pag FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' AND (tipo='20' or tipo='200' or tipo='201' or tipo='202')";
$result = $mysqli->query($query);
$riga=$result->fetch_array();
$posizione=$riga[num_pag]+1;

$id_risorsa=uniqid("item_");
$query = "INSERT INTO risorse_materiali SET  
id_risorsa='$id_risorsa',
tipo='200',
titolo='$titolo',
risorsa_padre='$risorsa_padre',
posizione='$posizione',
id_editor='$id_utente',
id_autore='$id_autore',
data_crea=now(),
data_mod=now(),
livello='1',
id_gruppo='$id_pagina'
";

$result = $mysqli->query($query);

$query="INSERT INTO materiale_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='creato',"
." data_evento=NOW()";
$mysqli->query($query);


if ($id_alternativo) {
	$alternativo_di=$id_risorsa;
	$query="SELECT id_gruppo FROM risorse_materiali WHERE id_risorsa='$id_alternativo'";
	$result = $mysqli->query($query);
	$riga= $result->fetch_array();
	$id_pagina_alt=$riga[id_gruppo];
	
	$query="UPDATE lo_pagina SET alternativo_di='$alternativo_di' WHERE id_pagina='$id_pagina_alt'";
	$result = $mysqli->query($query,$db);
};

if ($tipo_pagina<>"5") {
	$url="index.php?risorsa=lo_pagina_asset_edit&id_pagina=$id_pagina&risorsa_padre=$risorsa_padre";
} else {
	$url="index.php?risorsa=repository_index&id_cartella=$risorsa_padre";
};
//$url="index.php?risorsa=repository_index&id_cartella=$risorsa_padre";

Header("Location: $url");

?>

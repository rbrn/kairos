<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_pagina=$_REQUEST["id_pagina"];
$id_risorsa=$_REQUEST["id_risorsa"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$tipo_pagina=$_REQUEST["tipo_pagina"];
$ex_tipo_pagina=$_REQUEST["ex_tipo_pagina"];

$titolo=mysql_real_escape_string($_REQUEST["titolo"]);
$approfondimento=trim($_REQUEST["approfondimento"]);
$riepilogo=mysql_real_escape_string($_REQUEST["riepilogo"]);
$glossario=mysql_real_escape_string($_REQUEST["glossario"]);
$id_autore=mysql_real_escape_string($_REQUEST["id_autore"]);
$id_alternativo=mysql_real_escape_string($_REQUEST["link_tutoriale"]);
$link_cancella=$_REQUEST["link_cancella"];

$id_utente=$kairos_cookie[0];

if ($link_cancella=="on") $id_alternativo="";
	
$query = "UPDATE lo_pagina SET  
tipo_pagina='$tipo_pagina',
titolo='$titolo',
riepilogo='$riepilogo',
approfondimento='$approfondimento',
glossario='$glossario',
id_alternativo='$id_alternativo'
WHERE id_pagina='$id_pagina'
";
$result=$mysqli->query($query);

if ($tipo_pagina<>$ex_tipo_pagina) {
	$query = "DELETE FROM lo_pagina_asset WHERE id_pagina='$id_pagina' AND tipo_asset<>'1'";
	$result=$mysqli->query($query);
};

$query = "UPDATE risorse_materiali 		
			SET 
				risorsa_padre='$risorsa_padre',
				titolo='$titolo',
				id_autore='$id_autore'
			WHERE id_risorsa='$id_risorsa'";

$result=$mysqli->query($query);


$query="INSERT INTO materiale_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='modificato',"
." data_evento=NOW()";
$mysqli->query($query);

if ($id_alternativo) {
	$alternativo_di=$id_risorsa;
	$query="SELECT id_gruppo FROM risorse_materiali WHERE id_risorsa='$id_alternativo'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$id_pagina=$riga[id_gruppo];
	
	$query="UPDATE lo_pagina SET alternativo_di='$alternativo_di' WHERE id_pagina='$id_pagina'";
	$result=$mysqli->query($query);
};

$url="index.php?risorsa=repository_index&id_cartella=$risorsa_padre";
	
Header("Location: $url");

?>

<?php
require "./include/init_sito.inc";

$id_item=$_REQUEST["id_item"];
$id_risorsa=$_REQUEST["id_risorsa"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$tipo_item=$_REQUEST["tipo_item"];
$ex_tipo_item=$_REQUEST["ex_tipo_item"];
$titolo=mysql_real_escape_string($_REQUEST["titolo"]);
$consegna=mysql_real_escape_string($_REQUEST["consegna"]);
$mostra_titolo=mysql_real_escape_string(trim($_REQUEST["mostra_titolo"]));
$domanda= mysql_real_escape_string($_REQUEST["testo"]) ;
$alternativo=$_REQUEST["alternativo"];
$link_tutoriale=mysql_real_escape_string($_REQUEST["link_tutoriale"]);
$link_tutoriale_post=mysql_real_escape_string($_REQUEST["link_tutoriale_post"]);
$link_tutoriale_ref=$_REQUEST["link_tutoriale_ref"];
$id_alternativo=$_REQUEST["id_alternativo"];
$peso=$_REQUEST["peso"];
$msg_ok=$_REQUEST["msg_ok"];
$msg_ko=$_REQUEST["msg_ko"];



$query = "INSERT INTO lo_test_item SET  
tipo_item='$tipo_item',
domanda='$domanda',
titolo='$titolo',
legend='$consegna',
mostra_titolo='$mostra_titolo',
id_editor='$id_utente',
peso='$peso',
msg_ok='$msg_ok',
msg_ko='$msg_ko',
alternativo='$alternativo',
id_alternativo='$id_alternativo',
link_tutoriale='$link_tutoriale',
link_tutoriale_post='$link_tutoriale_post',
link_tutoriale_ref='$link_tutoriale_ref'
";
if(!$result = $mysqli->query($query)) die($mysqli->error);

$id_item=$mysqli->insert_id;

$query="SELECT max(posizione) AS num_pag FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' AND (tipo='20' or tipo='200' or tipo='201' or tipo='202')";
$result = $mysqli->query($query);
$riga=$result->fetch_array();
$posizione=$riga[num_pag]+1;

$id_risorsa=uniqid("item_");
$query = "INSERT INTO risorse_materiali SET  
id_risorsa='$id_risorsa',
tipo='201',
titolo='$titolo',
risorsa_padre='$risorsa_padre',
posizione='$posizione',
id_editor='$id_utente',
id_autore='$id_utente',
data_crea=now(),
data_mod=now(),
livello='1',
id_gruppo='$id_item'
";
$result = $mysqli->query($query);

$query="INSERT INTO materiale_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='creato',"
." data_evento=NOW()";
$result = $mysqli->query($query);

if ($tipo_item=="3") {
	$query="INSERT INTO lo_test_item_opzioni SET
	id_item='$id_item',
	posizione='1',
	punteggio='0',
	risposta_opzione='$stringa[vero]',
	id_editor='$id_utente'";
    $result = $mysqli->query($query);
	
	$query="INSERT INTO lo_test_item_opzioni SET
	id_item='$id_item',
	posizione='2',
	punteggio='0',
	risposta_opzione='$stringa[falso]',
	id_editor='$id_utente'";
    $result = $mysqli->query($query);
	
};

if ($id_alternativo) {
	$alternativo_di=$id_risorsa;
	$query="SELECT id_gruppo FROM risorse_materiali WHERE id_risorsa='$id_alternativo'";
    $result = $mysqli->query($query);
	$riga=$result->fetch_array();
	$id_item=$riga[id_gruppo];
	
	$query="UPDATE lo_test_item SET alternativo_di='$alternativo_di' WHERE id_item='$id_item'";
    $result = $mysqli->query($query);
};
		
$url="index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre";

Header("Location: $url");

?>

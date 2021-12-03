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

$cancella_link_tutoriale=$_REQUEST["cancella_link_tutoriale"];
$cancella_link_tutoriale_post=$_REQUEST["cancella_link_tutoriale_post"];
$cancella_link_tutoriale_ref=$_REQUEST["cancella_link_tutoriale_ref"];
$cancella_id_alternativo=$_REQUEST["cancella_id_alternativo"];

$id_utente=$kairos_cookie[0];

if ($cancella_link_tutoriale=="on") $link_tutoriale="";
if ($cancella_link_tutoriale_post=="on") $link_tutoriale_post="";
if ($cancella_link_tutoriale_ref=="on") $link_tutoriale_ref="";
if ($cancella_id_alternativo=="on") $id_alternativo="";
			
$query = "UPDATE lo_test_item SET  
tipo_item='$tipo_item',
domanda='$domanda',
titolo='$titolo',
legend='$consegna',
mostra_titolo='$mostra_titolo',
altro='$altro',
peso='$peso',
msg_ok='$msg_ok',
msg_ko='$msg_ko',
alternativo='$alternativo',
id_alternativo='$id_alternativo',
link_tutoriale='$link_tutoriale',
link_tutoriale_post='$link_tutoriale_post',
link_tutoriale_ref='$link_tutoriale_ref'
WHERE id_item='$id_item'
";
if(!$result=$mysqli->query($query)) die($mysqli->error);

if ($tipo_item<>$ex_tipo_item) {
	$query = "DELETE FROM lo_test_item_opzioni WHERE id_item='$id_item'";
    if(!$result=$mysqli->query($query)) die($mysqli->error);
	
	$query = "DELETE FROM lo_test_dragdrop WHERE id_item='$id_item'";
    if(!$result=$mysqli->query($query)) die($mysqli->error);
	
	if ($tipo_item=="3") {
	$query="INSERT INTO lo_test_item_opzioni SET
	id_item='$id_item',
	posizione='1',
	punteggio='0',
	risposta_opzione='$stringa[vero]',
	id_editor='$id_utente'";
        if(!$result=$mysqli->query($query)) die($mysqli->error);
	
	$query="INSERT INTO lo_test_item_opzioni SET
	id_item='$id_item',
	posizione='2',
	punteggio='0',
	risposta_opzione='$stringa[falso]',
	id_editor='$id_utente'";
        if(!$result=$mysqli->query($query)) die($mysqli->error);
	
	};
};

$query = "UPDATE risorse_materiali 		
			SET 
				risorsa_padre='$risorsa_padre',
				titolo='$titolo'
			WHERE id_risorsa='$id_risorsa'";

if(!$result=$mysqli->query($query)) die($mysqli->error);


$query="INSERT INTO materiale_storia SET"
." id_risorsa='$id_risorsa',"
." id_utente='$id_utente',"
." evento='modificato',"
." data_evento=NOW()";
if(!$result=$mysqli->query($query)) die($mysqli->error);

if ($id_alternativo) {
	$alternativo_di=$id_risorsa;
	$query="SELECT id_gruppo FROM risorse_materiali WHERE id_risorsa='$id_alternativo'";
    if(!$result=$mysqli->query($query)) die($mysqli->error);
	$riga=$result->fetch_array();
	$id_item=$riga[id_gruppo];
	
	$query="UPDATE lo_test_item SET alternativo_di='$alternativo_di' WHERE id_item='$id_item'";
    if(!$result=$mysqli->query($query)) die($mysqli->error);
};

$url="index.php?risorsa=repository_index&id_cartella=$risorsa_padre";
	
Header("Location: $url");

?>

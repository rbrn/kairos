<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$risorsa_padre=$_REQUEST["risorsa_padre"];
$id_item=$_REQUEST["id_item"];
$azione=$_REQUEST["azione"];
$id_item_opzione=$_REQUEST["id_item_opzione"];
$punteggio=$_REQUEST["punteggio"];
$tipo_opzione=$_REQUEST["tipo"];
$id_item_esatto=$_REQUEST["id_item_esatto"];
$x_p=$_REQUEST["x_p"];
$y_p=$_REQUEST["y_p"];
$msg_pezzo=$_REQUEST["msg_pezzo"];
$f_url=$_REQUEST["f_url"];
$id_utente=$kairos_cookie[0];

/*
echo "
id_test=$id_test<br>
id_sezione=$id_sezione<br>
id_item=$id_item<br>
azione=$azione<br>
msg_pezzo=$msg_pezzo<br>
x_p=$x_p<br>
y_p=$y_p<br>
";
*/
if ($azione=="nuovo") {
$query = "INSERT INTO lo_test_item_opzioni SET  
id_item='$id_item',
tipo_opzione='$tipo_opzione',
id_item_esatto='$id_item_esatto',
punteggio='$punteggio',
id_editor='$id_utente'
";
} else {
$query = "UPDATE lo_test_item_opzioni SET  
id_item_esatto='$id_item_esatto',
punteggio='$punteggio'
WHERE id_item_opzione='$id_item_opzione'
";
};
$result=$mysqli->query($query);

echo mysql_error();

if ($azione=="nuovo") {
	$id_item_opzione=$mysqli->insert_id;
	$query="INSERT INTO lo_test_dragdrop SET
	id_item_opzione='$id_item_opzione',
	id_item='$id_item',
	tipo_opzione='$tipo_opzione',
	x_p='$x_p',
	y_p='$y_p',
	messaggio='$msg_pezzo',
	immagine='$f_url'";
} else {
	$query="UPDATE lo_test_dragdrop SET
	tipo_opzione='$tipo_opzione',
	x_p='$x_p',
	y_p='$y_p',
	messaggio='$msg_pezzo',
	immagine='$f_url'
	WHERE id_item_opzione='$id_item_opzione'";
};
$mysqli->query($query);

echo mysql_error();
$url="index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre";

Header("Location: $url");

?>

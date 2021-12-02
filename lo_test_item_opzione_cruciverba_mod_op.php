<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$id_item_opzione=$_REQUEST["id_item_opzione"];

$riga_casella=$_REQUEST["riga_casella"];
$col_casella=$_REQUEST["col_casella"];
$etichetta=$_REQUEST["etichetta"];
$verso=$_REQUEST["verso"];
$definizione=$_REQUEST["definizione"];
$risposta_giusta=$_REQUEST["risposta_giusta"];
$msg_ko=$_REQUEST["msg_ko"];

$query="SELECT * FROM lo_test_item_cruciverba WHERE id_item='$id_item'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$num_orz=$riga["larghezza"];
$num_ver=$riga["altezza"];

if (!$col_casella) $col_casella=1;
if (!$riga_casella) $riga_casella=1;

if ($col_casella>$num_orz) $col_casella=$num_orz;
if ($riga_casella>$num_ver) $riga_casella=$num_ver;

$posizione=($riga_casella-1)*$num_orz+$col_casella;
			
$query = "UPDATE lo_test_item_opzioni_cruciverba SET  
posizione='$posizione',
etichetta='$etichetta',
verso='$verso',
definizione='$definizione',
risposta_giusta='$risposta_giusta',
msg_ko='$msg_ko'
WHERE id_item_opzione='$id_item_opzione'
";
$result=$mysqli->query($query);

$url="index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre";

Header("Location: $url");

?>

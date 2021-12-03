<?php

require_once 'include/properties.php';

$cod_area=$_GET["cod_area"];
$id_utente=$_GET["id_utente"];

$query = "SELECT id_utente,stanza,date_format(data_invito,\"%d/%m/%Y %H:%i:%s\") as data_inv FROM invito_chat WHERE id_invitato='$id_utente' ORDER BY data_invito DESC";
$result = $myqli->query($query);
$invito = $result->fetch_array();


$query = "DELETE FROM invito_chat WHERE id_invitato='$id_utente'";
$result = $mysqli->query($query);

$feedback='{"stanza":"0"}';

if ($invito) {
	$stanza=$invito["stanza"];
	$id_host=$invito["id_utente"];
	$data_invito=$invito["data_inv"];
	
	$feedback='{"stanza":"'.$stanza.'","id_host":"'.$id_host.'","data_invito":"'.$data_invito.'"}';
	
};
print($feedback);
?>

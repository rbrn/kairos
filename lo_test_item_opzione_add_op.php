<?php
require "./include/init_sito.inc";

$id_item = $_REQUEST["id_item"];
$risorsa_padre = $_REQUEST["risorsa_padre"];
$risposta_opzione = mysql_real_escape_string($_REQUEST["opzione"]);
$punteggio = $_REQUEST["punteggio"];

$id_utente = $kairos_cookie[0];
$ope = $_REQUEST["ope"];

$query = "SELECT MAX(posizione) AS max_pos FROM lo_test_item_opzioni WHERE id_item='$id_item'";
$result = $mysqli->query($query);

$riga = $result->fetch_array();
$posizione = $riga[max_pos] + 1;

if ($ope == 1) {
    $query = "INSERT INTO lo_test_item_opzioni SET
id_item='$id_item',
posizione='$posizione',
risposta_opzione='$risposta_opzione',
punteggio='$punteggio',
id_editor='$id_utente'
";

    $result = $mysqli->query($query);
}
if ($ope == 2) {
    $righePassate = split(';', $risposta_opzione);
    $maxrow = count($righePassate);
    if ($maxrow > 1) {
        for ($i = 0; $i < $maxrow; $i++) {
            $opzione = split(':', $righePassate[$i]);
            if (count($opzione) > 1) {
                $query = "INSERT INTO lo_test_item_opzioni SET
			id_item='$id_item',
			posizione='$posizione',
			risposta_opzione='$opzione[0]',
			punteggio='$opzione[1]',
			id_editor='$id_utente'
			";
                $posizione++;
                $result = $mysqli->query($query);
            }
        }
    }
}

$url = "index.php?risorsa=lo_test_item_edit&id_item=$id_item&risorsa_padre=$risorsa_padre";

Header("Location: $url");

?>

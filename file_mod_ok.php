<?php

require "./include/init_sito.inc";

require "./include/funzioni_sito.inc";


$id_risorsa = $_REQUEST["id_risorsa"];

$era_admin = $_REQUEST["era_admin"];

$ex_titolo = mysql_real_escape_string($_REQUEST["ex_titolo"]);

$ex_file_size = $_REQUEST["ex_file_size"];


$risorsa_padre = $_REQUEST["risorsa_padre"];

$descrizione = mysql_real_escape_string($_REQUEST["descrizione"]);

$parole_chiave = mysql_real_escape_string($_REQUEST["parole_chiave"]);

$livello = mysql_real_escape_string($_REQUEST["livello"]);

$id_gruppo = $_REQUEST["id_gruppo"];


$MAX_FILE_SIZE = $_REQUEST["MAX_FILE_SIZE"];


$titolo = $_FILES["titolo"]["tmp_name"];

$titolo_size = $_FILES["titolo"]["size"];

$titolo_name = $_FILES["titolo"]["name"];


$db = mysql_connect($DBHOST, $DBUSER, $DBPWD);

mysql_select_db($DBASE, $db);


if ($titolo_size > $MAX_FILE_SIZE) {

    $errore .= "<br>$stringa[errore_max_file]";

};


if ($errore) {

    $msg = ereg_replace(" ", "%20", $errore);

    Header("Location:index.php?risorsa=msg&msg=$msg");

    exit();

};


if ($titolo_name) {

    if (risorsa_admin($id_risorsa)) {

        $fullpath = $PATH_ARCHIVI_ADMIN . $ex_titolo;

    } else {

        $fullpath = $PATH_ARCHIVI . $ex_titolo;

    };

    if (file_exists($fullpath)) {

        unlink($fullpath);

    };


    $copia = true;


} else {

    $titolo_name = $ex_titolo;

    $titolo_size = $ex_file_size;

    $copia = false;

};


$id_utente = $kairos_cookie["0"];


$query = "UPDATE risorse

			SET 

				risorsa_padre='$risorsa_padre',

				titolo='$titolo_name',

				descrizione='$descrizione',

				parole_chiave='$parole_chiave',

				id_gruppo='$id_gruppo',

				file_size='$titolo_size',

				livello='$livello',

				id_autore='$id_utente'

			WHERE id_risorsa='$id_risorsa'";

$result = $mysqli->query($query);

if ($copia) {

    $titolo_name = trim($titolo_name);

    $titolo_name = ereg_replace(" ", "", $titolo_name);

    $titolo_name = strtolower($titolo_name);

    if (risorsa_admin($id_risorsa)) {

        $fullpath = $PATH_ARCHIVI_ADMIN . $titolo_name;

    } else {

        $fullpath = $PATH_ARCHIVI . $titolo_name;

    };

    copy($titolo, $fullpath);

} else {

    $era_admin = $era_admin ? true : false;

    if (risorsa_admin($id_risorsa) <> $era_admin) {

        if ($era_admin) {

            $fullpath0 = $PATH_ARCHIVI_ADMIN . $titolo_name;

            $fullpath = $PATH_ARCHIVI . $titolo_name;

            copy($fullpath0, $fullpath);

            unlink($fullpath0);

        } else {

            $fullpath0 = $PATH_ARCHIVI . $titolo_name;

            $fullpath = $PATH_ARCHIVI_ADMIN . $titolo_name;

            copy($fullpath0, $fullpath);

            unlink($fullpath0);

        };

    };

};


Header("Location:index.php?risorsa=admin_index&id_cartella=$risorsa_padre");

?>

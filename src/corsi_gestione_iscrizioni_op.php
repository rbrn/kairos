<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect($DBHOST, $DBUSER, $DBPWD);
mysql_select_db($DBASE, $db);

$cerca_reg = mysql_real_escape_string($_REQUEST["cerca_reg"]);
$cerca_iscr = mysql_real_escape_string($_REQUEST["cerca_iscr"]);
$copia_iscr = mysql_real_escape_string($_REQUEST["copia_iscr"]);

$id_corso_s = mysql_real_escape_string($_REQUEST["id_corso"]);
$id_edizione_s = mysql_real_escape_string($_REQUEST["id_edizione"]);

$id_corso_edizione_form = mysql_real_escape_string($_REQUEST["id_corso_edizione_form"]);
list($id_corso_new, $id_edizione_new) = split(" ", $id_corso_edizione_form);

$id_u = $_REQUEST["id_u"];

for ($i = 0; $i < count($id_u); $i++) {
    if ($cerca_reg) {
        $id_utente = $id_u[$i];
    } else {
        list($id_utente, $id_corso0, $id_edizione0) = split(" ", $id_u[$i]);
        if ($copia_iscr <> "on") {
            $query = "DELETE FROM iscrizioni_corso WHERE id_utente='$id_utente' AND id_corso='$id_corso0' AND id_edizione='$id_edizione0'";
            $result = $mysqli->query($query);


            $query = "DELETE FROM iscrizioni_gruppo_pw WHERE id_utente='$id_utente' AND id_corso='$id_corso0' AND id_edizione='$id_edizione0'";
            $result = $mysqli->query($query);

        };

    };

    $query = "SELECT * FROM iscrizioni_corso WHERE id_utente='$id_utente' AND id_corso='$id_corso_new' AND id_edizione='$id_edizione_new'";
    $result=$mysqli->query($query);

    if (!$result->num_rows) {
        $query = "INSERT INTO iscrizioni_corso SET
		 id_utente='$id_utente',
		 id_corso='$id_corso_new',
		 id_edizione='$id_edizione_new',
		 id_gruppo='generale',
		 data_iscrizione=NOW()";
        $result=$mysqli->query($query);
    };

};

if ($cerca_reg) {
    Header("Location:index.php?risorsa=corsi_gestione_iscrizioni_form&id_corso=$id_corso_new&id_edizione=$id_edizione_new");
} else {
    Header("Location:index.php?risorsa=corsi_gestione_iscrizioni_form&id_corso=$id_corso_s&id_edizione=$id_edizione_s");
};

?>

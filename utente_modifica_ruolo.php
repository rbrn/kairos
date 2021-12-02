<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$ruolo = ruolo_utente($kairos_cookie[0]);
if ($ruolo <> "admin") {
    $msg = "Accesso riservato solo allo staff.";
    $msg = ereg_replace(" ", "%20", $msg);
    Header("Location:index.php?risorsa=msg&msg=$msg");
    exit();
};


$stato = $_REQUEST["ruolo_new"];
$id_u = $_REQUEST["id_u"];
$id_corso_edizione_form = $_REQUEST["id_corso_edizione_form"];
list($id_corso_new, $id_edizione_new) = split(" ", $id_corso_edizione_form);

$iscrivi_utenti = $_REQUEST["iscrivi_utenti"];
$modifica_ruolo = $_REQUEST["modifica_ruolo"];

if ($modifica_ruolo) {
    $tipo_area = 'kairos';
    $cod_area_base = substr($cod_area, 7, strlen($cod_area));

    $query = "SELECT email,nome,cognome FROM utenti WHERE id_utente='$utente_admin'";
    $result = $mysqli->query($query);
    $riga = $result->fetch_array();
    $email_admin = $riga["email"];
    $nome_admin = $riga["nome"];
    $cognome_admin = $riga["cognome"];

    for ($i = 0; $i < count($id_u); $i++) {
        $id_utente = $id_u[$i];
        $query = "SELECT * FROM utenti WHERE id_utente='$id_utente'";
        $result = $mysqli->query($query);
        $riga = $result->fetch_array();
        $ex_stato = $riga["stato"];
        $email = $riga["email"];
        $pwd_utente = $riga["pwd_utente"];
        if ($stato <> $ex_stato) {
            $query = "UPDATE utenti SET stato='$stato' WHERE id_utente='$id_utente'";
            $result = $mysqli->query($query);

            if ($ex_stato == 0 and $stato <> 0) {
                $msg = "
$stringa[caro] $id_utente,
$stringa[ecco_parametri] $nomescuola:

$stringa[id]: $id_utente 		
$stringa[pw]: $pwd_utente 		

$stringa[scrivi_parametri]

$nome_admin $cognome_admin ($utente_admin)
$stringa[amministratore_area]
" . APP_URL . "/$cod_area_base";
                $id_package = uniqid("");
                if ($mail_enalbled) {
                    mail_job($id_package, "$email", "[$cod_area]: $stringa[parametri_accesso]", "$msg", "$email_admin", "$email_admin", "");
                }

                mail("$email", "[$cod_area]: $stringa[parametri_accesso]", "$msg", "From:$email_admin\nReply-To:$email_admin");
            };
        };
    };
} else {
    for ($i = 0; $i < count($id_u); $i++) {
        $id_utente = $id_u[$i];

        $query = "SELECT * FROM iscrizioni_corso WHERE id_utente='$id_utente' AND id_corso='$id_corso_new' AND id_edizione='$id_edizione_new'";
        $result = $mysqli->query($query);
        if ($result->num_rows == 0) {
            $query = "INSERT INTO iscrizioni_corso SET
		 id_utente='$id_utente',
		 id_corso='$id_corso_new',
		 id_edizione='$id_edizione_new',
		 id_gruppo='generale',
		 data_iscrizione=NOW()";
            if(!$result = $mysqli->query($query)) die($mysqli->error) ;
        };
    };

};

if ($modifica_ruolo) {
    Header("Location:index.php?risorsa=utenti_cerca");
} else {
    Header("Location:index.php?risorsa=utenti_iscrizione_cerca");
}

?>

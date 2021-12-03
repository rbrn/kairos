<?php
require_once("./include/init_sito.inc");
require "./include/funzioni_sito.inc";

$user = $_REQUEST['id'];

$user_res = $mysqli->query("select * from utenti where id_utente = '$user'");
if ($user_res) {
    $user_details = $user_res->fetch_array();
    $pwd_utente_form=$user_details["pwd_utente"];
    Header("Location:login.php?id_utente_form=$user&pwd_utente_form=$pwd_utente_form&risorsa=index&social=true");
} else {
    Header("Location:pagina.php?risorsa=do_login");
    exit();
}
?>
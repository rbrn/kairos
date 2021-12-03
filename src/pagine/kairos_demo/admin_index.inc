<?php
require "./include/function_admin.inc";
$id_cartella=$_REQUEST["id_cartella"];

if (!isset($id_cartella)) {
	$id_cartella="root";
};

$ruolo=ruolo_utente($id_utente);

if (($id_cartella=='admin' or risorsa_admin($id_cartella)) and $ruolo<>'admin') {
	$id_cartella="root";
};


$tpl->assign("stringa", $stringa );
$tpl->assign("ruolo", $ruolo);

// draw the template
$tpl->draw( "admin_index_template" );




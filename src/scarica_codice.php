<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
require "./include/function_admin.inc";
$id_risorsa=$_REQUEST["id_risorsa"];
$id_utente=$kairos_cookie[0];
$ruolo=ruolo_utente($id_utente);

if ($id_utente and ($ruolo=='staff' or $ruolo=='admin')) {
	if (risorsa_admin($id_risorsa)) {
		$file_codice=$PATH_ROOT_FILE."pagine/$id_risorsa.inc";
	} else {
		$file_codice=$PATH_ROOT_FILE."pagine/$cod_area/$id_risorsa.inc";
	};

	$doc = fopen($file_codice,"rb");
	$filename=$id_risorsa.".htm";
	header("Content-Type: text/plain");
	header( "Content-Disposition: attachment; filename=$filename" ); 	
	fpassthru($doc);
};
?>

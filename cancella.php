<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$ruolo=ruolo_utente($kairos_cookie[0]);
$file=$_REQUEST[file];
$ritorno=$_REQUEST[ritorno];

if ($ruolo=="staff" or $ruolo=="admin") {
	$path_file=$PATH_ROOT_FILE."/".$file;
	if (file_exists($path_file)) unlink($path_file);
};
Header("Location:$ritorno");	
?>

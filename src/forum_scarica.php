<?php

require "./include/init_sito.inc";

require "./include/funzioni_sito.inc";



if ( !isset($kairos_cookie[0]) ){

	$query = $_SERVER["QUERY_STRING"];

	$PHP_SELF=$_SERVER["PHP_SELF"];

	if ($query) {

		$url = "$PHP_SELF?$query";

	} else {

		$url ="$PHP_SELF";

	};

	$location="Location: $PATH_ROOT"."index.php?risorsa=do_login&url=$url";

	Header($location);

	exit();

};



$id_utente=$kairos_cookie[0];



refresh_utente($id_utente);



$file=$_REQUEST["file"];



$file_download=$PATH_ARCHIVI."forum/".$file;







if (file_exists($file_download)) {

	$doc = fopen($file_download,"rb");

	$type= getmimetype($file);

	header("Content-Type: $type");

	header( "Content-Disposition: attachment; filename=$file" ); 	

	fpassthru($doc);

} else {
	
	$msg=$stringa[errore_file_rimosso];

	$msg=ereg_replace(" ","%20",$msg);

	Header("Location:index.php?risorsa=msg&msg=$msg");
}

?>

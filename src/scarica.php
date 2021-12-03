<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$file=$_REQUEST["file"];
$dir=$_REQUEST["dir"];

if ($kairos_cookie[0]) {
	$nomefile = $PATH_ARCHIVI.$dir."/".$file;
	$doc = fopen($nomefile,"rb");
	$type= getmimetype($file);
	header("Content-Type: $type");
	header( "Content-Disposition: attachment; filename=$file" ); 
	fpassthru($doc);
};

?>

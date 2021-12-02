<?php
require "./include/init_sito.inc";

$script=$_REQUEST["script"];
$risorsa=$_REQUEST["risorsa"];

if ($kairos_cookie[7]=='1') {
	setcookie("kairos_cookie[7]","",0,"/",$dominio);
} else {
	setcookie("kairos_cookie[7]","1",0,"/",$dominio);
};

Header("Location:$script?risorsa=$risorsa");
?>


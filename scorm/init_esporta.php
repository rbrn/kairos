<?php
require "../include/init_sito.inc";

$DBASE = $cod_area;
$PATH_ROOT="/var/www/html/prototipo/kairos/";
$PATH_PAGINE = "/var/www/html/prototipo/kairos/materiali/$cod_area/";
$PATH_MEDIA = "/var/www/html/prototipo/kairos/materiali_img/$cod_area/";
$PATH_ARCHIVI = "/var/www/archivi/kairos/materiali/$cod_area/";
$PATH_MODULO="/var/www/archivi/kairos/moduli/$cod_area";

if ($gruppo) {
$PATH_PAGINE = "/var/www/html/prototipo/kairos/materiali/$cod_area/gruppo/";
$PATH_MEDIA = "/var/www/html/prototipo/kairos/materiali_img/$cod_area/gruppo/";
$PATH_ARCHIVI = "/var/www/archivi/kairos/materiali/$cod_area/gruppo/";
$PATH_MODULO="/var/www/archivi/kairos/moduli/$cod_area/gruppo";
};

if (!is_dir($PATH_MODULO)) {
	@mkdir($PATH_MODULO,0755);
};
$PATH_MODULO.="/";
	
$server=$_SERVER["SERVER_NAME"];

$URL_IMG="http://$server/materiali_img/$cod_area";

if ($gruppo) {
$URL_IMG="http://$server/materiali_img/$cod_area/gruppo";
};

//$URL_LINK="http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com/kairos2/materiali_browse.php?risorsa=";

?>

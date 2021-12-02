<?php
$cod_area=$kairos_cookie[4];
if (!$cod_area) $cod_area="kairos_demo";
require "../pagine/$cod_area/colori.inc";
$server=$_SERVER["SERVER_NAME"];

$base="";
if ($server) $base="kairos/";
if ($server=="localhost") $base="kairos/";
?>

_editor_url = "/<?=$base?>html_editor/";
_editor_lang = "it";


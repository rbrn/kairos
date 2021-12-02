<?php
$tipo_news=$_REQUEST["tipo_news"];

$tpl->assign("stringa", $stringa );
$tpl->assign("testo", $testo);
$tpl->assign("tipo_news", $tipo_news);
$tpl->assign("colore_scuro", $colore_scuro);

// draw the template
$tpl->draw( "news_create" );

?>





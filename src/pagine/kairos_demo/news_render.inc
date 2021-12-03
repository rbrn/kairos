<?php


$query = "SELECT id_news,url,url_label,testo,id_utente,date_format(data_news,\"%d/%m/%Y\") as data_n FROM hp_news where tipo=1 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY data_news DESC";
$result = $mysqli->query($query);

while (($item_news = $result->fetch_array()) and $news <= 5) {

}

$tpl->assign("item_news", $result->fetch_array());

$tpl->assign("stringa", $stringa );
$tpl->draw( "news_render" );

<!-- Wrap all page content here -->
<?php

$script = $_SERVER["PHP_SELF"];
$query_string = $_SERVER["QUERY_STRING"];
if (!$query_string) {
    $query_string = "risorsa=$risorsa";
};
$query_string = str_replace("&lingua=it", "", $query_string);
$query_string = str_replace("&lingua=ro", "", $query_string);
$query_string = str_replace("&lingua=us", "", $query_string);

$tpl->assign("stringa", $stringa);
$tpl->assign("ruolo", $ruolo);
$tpl->assign("id_utente", $id_utente);
$tpl->assign("script", $script);
$tpl->assign("query_string", $query_string);
$tpl->assign("target", $target);
$tpl->assign("server", $server);
$tpl->assign("port", SOCIAL_API_PORT);
$tpl->assign("context", SOCIAL_API_CONTEXT);

$tpl->draw("testata_new_template");


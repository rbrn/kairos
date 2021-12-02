<?php

$server = $_SERVER["SERVER_NAME"];
$PROFILE = getCurrentProfileFromServerName($server);

include "profiles/$PROFILE.php";

$kairos_cookie = $_REQUEST["kairos_cookie"];
$kairos_cookie_lingua = $_REQUEST["kairos_cookie_lingua"];
$kairos_cookie_area = $_REQUEST["kairos_cookie_area"];

$PATH_ROOT_FILE =$SERVER_ROOT."kairos/";
$LANG_FILES = $PATH_ROOT_FILE."translation/";
$DBHOST = DBHOST;
$DBUSER = DBUSER;
$DBPWD = DBPWD;

function getCurrentProfileFromServerName($server)
{
    if ($server === "localhost")
        return Profiles::DEVELOPMENT;
    else
        return Profiles::PRODUCTION;
}

interface Profiles
{
    const PRODUCTION = "production";
    const DEVELOPMENT = "development";
}

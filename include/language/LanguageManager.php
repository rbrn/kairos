<?php

class LanguageManager {


    /**
     * @param $server
     * @param $dominio
     * @param $kairos_cookie_lingua
     * @param $lifetime
     * @param $lingua
     */
    public static function handleLanguageAssets($server, $dominio)
    {
        $kairos_cookie_lingua = $_COOKIE["kairos_cookie_lingua"];
        $lifetime = "0";
        if ($server <> "localhost")
            $lifetime = mktime(12, 50, 30, 6, 20, 2050);
        $lingua = $_REQUEST["lingua"];


        if (isset($lingua)) {
            $kairos_cookie_lingua = $lingua;
            setcookie("kairos_cookie_lingua", $lingua, $lifetime, "/", $dominio);
        } else {
            $lingua = $kairos_cookie_lingua;
        };

        if (!isset($lingua)) {
            if (!isset($kairos_cookie_lingua)) {
                $lingua = "it";
                $kairos_cookie_lingua = $lingua;
                setcookie("kairos_cookie_lingua", $lingua, $lifetime, "/", $dominio);
            };
        };
    }

}

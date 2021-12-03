<?php

ini_set('display_errors',1);
ini_set('display_startup_errors',1);
error_reporting(-1);
ini_set('error_reporting', E_ERROR | E_WARNING | E_PARSE);
/**
 * @package Kairos
 */
include_once 'properties.php';

$kairos_pubblici = array();
$server = $_SERVER["SERVER_NAME"];
$usanuovoeditor = true;

preg_replace("^([aA-zZ]+)\.(.+)$", $server, $parti);
$dominio = $parti[2];

$risorsa = $_REQUEST["risorsa"];
$cod_area = $_REQUEST["cod_area"];
$kairos_cookie = $_COOKIE["kairos_cookie"];
$kairos_cookie_lingua = $_COOKIE["kairos_cookie_lingua"];
$atlante_cookie = $_COOKIE["atlante_cookie"];
$wimba_cookie = $_COOKIE["wimba_cookie"];
$id_utente = $_REQUEST["id_utente"];
$url = $_REQUEST["url"];

$id_corso_ed_s = $kairos_cookie[2];
list($id_corso_s, $id_edizione_s, $id_gruppo_s, $id_tutor_s) = preg_split(" ", $id_corso_ed_s);

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


//forum
$id_forum = $_REQUEST["id_forum"];
$id_post = $_REQUEST["id_post"];
$id_post_padre = $_REQUEST["id_post_padre"];
$vista = $_REQUEST["vista"];

$modo = $_REQUEST["modo"];
$pagina = $_REQUEST["pagina"];
$op = $_REQUEST["op"];

$msg = $_REQUEST["msg"];

//news
$tipo_news = $_REQUEST["tipo_news"];
$id_news = $_REQUEST["id_news"];

//calendario
$day = $_REQUEST["day"];
$month = $_REQUEST["month"];
$year = $_REQUEST["year"];
$action = $_REQUEST["action"];
$modify = $_REQUEST["modify"];
$id = $_REQUEST["id"];
$time = $_REQUEST["time"];
$subject = $_REQUEST["subject"];
$description = $_REQUEST["description"];

$PATH_ROOT = "http://$server/" . APP_CONTEXT;

$PATH_ARCHIVI_ADMIN = KAIROS_PATH_ARCHIVES;

$db = mysqli_connect($DBHOST, $DBUSER, $DBPWD);

$wimba_lc = "";
$editor_lo = "";

$editor_lo = true;

if ($redirect) {
    $query = "SELECT * FROM abbonamenti_piattaforma WHERE dominio='$server'";
    $result = $mysqli->query($query);
    if ($result->num_rows) {
        $riga = $result->fetch_array();
        $PATH_ROOT = "http://" . $server . "/";
        $cod_area = $riga[tipo_area] . "_" . $riga[cod_area];
        $wimba_lc = $riga["liveclassroom"];
        $editor_lo = $riga["editor_lo"];
    };
};

if (isset($cod_area)) {
    $kairos_cookie[4] = $cod_area;
    setcookie("kairos_cookie[4]", $kairos_cookie[4], 0, "/", $dominio);
};

if (!isset($cod_area)) {
    if (!isset($kairos_cookie[4])) {
        $cod_area = "kairos_demo";
        $kairos_cookie[4] = $cod_area;
        setcookie("kairos_cookie[4]", $kairos_cookie[4], 0, "/", $dominio);
    };
};

$cod_area = $kairos_cookie[4];

if (!$cod_area) {
    $cod_area = "kairos_demo";
    setcookie("kairos_cookie[4]", $kairos_cookie[4], 0, "/", $dominio);
};

$PATH_ARCHIVI = KAIROS_PATH_ARCHIVES . $cod_area . "/";


$DBASE = $cod_area;
$DBASE_UTENTI = $cod_area;

define("C_DB_TYPE", "mysql");
define("C_DB_HOST", $DBHOST);
define("C_DB_NAME", $cod_area);
define("C_DB_USER", $DBUSER);
define("C_DB_PASS", $DBPWD);
define("C_MSG_TBL", "c_messages");
define("C_MSG_TBL_ARCH", "c_messages_archive");
define("C_USR_TBL", "c_users");
define("C_REG_TBL", "c_reg_users");
$DefaultChatRooms = array("Generale");

$mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);


/* check connection */
if ($mysqli->connect_errno) {
    printf("Connect failed: %s\n", $mysqli->connect_error);
    exit();
}

$lingua = $kairos_cookie_lingua;
$file_lingua = $LANG_FILES . "stringhe_" . $lingua . ".inc";

if (!file_exists($file_lingua)) {
    $lingua = "it";
    setcookie("kairos_cookie_lingua", $lingua, $lifetime, "/", $dominio);
    $file_lingua = "stringhe_it.inc";
};

if (file_exists($file_lingua)) {
    require "$file_lingua";
}

if (file_exists($PATH_ROOT_FILE . "/pagine/$cod_area/colori.inc")) {
    require $PATH_ROOT_FILE . "/pagine/$cod_area/colori.inc";

}

if ($id_corso_s) {
    $ok = false;
    $query = "select * from edizioni where id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
    $result = $mysqli->query($query);
    if ($result->num_rows) $ok = true;

    if (!$ok) {
        $query = "SELECT iscrizioni_corso.id_corso,iscrizioni_corso.id_edizione,iscrizioni_corso.id_gruppo FROM iscrizioni_corso,edizioni WHERE
iscrizioni_corso.id_corso=edizioni.id_corso AND iscrizioni_corso.id_edizione=edizioni.id_edizione AND 
edizioni.stato='attiva' AND 
iscrizioni_corso.id_utente='$kairos_cookie[0]'";

        $result = $mysqli->query($query);

        if ($result->num_rows == 1) {
            $riga = $result->fetch_array();
            $id_corso_s = $riga[id_corso];
            $id_edizione_s = $riga[id_edizione];
            $id_gruppo_s = $riga[id_gruppo];

            $query = "SELECT id_tutor FROM gruppo_utenti WHERE id_gruppo='$id_gruppo_s' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
            $result = $mysqli->query($query);
            $riga = $result->fetch_array();
            $id_tutor = $riga["id_tutor"];
            $valore = $id_corso_s . " " . $id_edizione_s . " " . $id_gruppo . " " . $id_tutor;
            setcookie("kairos_cookie[2]", "$valore", 0, "/", $dominio);

        } else {
            $id_corso_s = "";
            $id_edizione_s = "";
            $id_gruppo_s = "";
            $id_tutor_s = "";
            setcookie("kairos_cookie[2]", "", 0, "/", $dominio);
        }
    } else {
        $riga = $riga = $result->fetch_array();
        $descr_edizione_s = $riga[descrizione];
    };
};


$opera = false;
if (!preg_replace('MSIE', $_SERVER["HTTP_USER_AGENT"]) or !preg_replace('Windows', $_SERVER["HTTP_USER_AGENT"])) {
    $win_ie = false;
} else {
    $win_ie = true;
};

if (preg_replace('Opera', $_SERVER["HTTP_USER_AGENT"])) {
    $win_ie = false;
    $opera = true;
};

if (preg_replace('Mozilla', $_SERVER["HTTP_USER_AGENT"]) and !preg_replace('MSIE', $_SERVER["HTTP_USER_AGENT"])) {
    $win_ie = false;
};


$tipo_area_base = 'kairos';
$cod_area_base = substr($cod_area, 7, strlen($cod_area));


if ($redirect) {

    $query = "SELECT * FROM abbonamenti_piattaforma WHERE tipo_area='$tipo_area_base' and cod_area='$cod_area_base'";
    $result = $mysqli->query($query);
    if ($result->num_rows) {
        $riga = $result->fetch_array();
        $server_base = $riga[dominio];

        if ($server_base) {
            if ($server <> $server_base) {
                $query = $_SERVER["QUERY_STRING"];
                $PHP_SELF = basename($_SERVER["PHP_SELF"]);
                if ($query) {
                    $url = "$PHP_SELF?$query";
                } else {
                    $url = "$PHP_SELF";
                };
                $url = "http://" . $server_base . "/" . $url;
                Header("Location: $url");
                exit();
            };
        };
    };
};

$wimba = false;
if (!$wimba_cookie or !$wimba) {
    $wimba_cookie = "off";
    setcookie("wimba_cookie", $wimba_cookie, $lifetime, "/");
};

$n_news = 8;
$colore_sfondo_menu = "#281d8f";
$colore_barra_testata = "#e0e4f6";
$colore_scuro_neutro = "#cccccc";
$colore_sfondo_neutro = "#efefef";

$suoni_chat = array("cucu", "unoallavolta", "uffa", "silenzio", "interessante", "divertente", "cambioargomento", "ahem", "alleluia", "applauso", "bacio", "risata", "risatina", "telefono", "tosse", "vetro", "voila", "ahi", "arpa", "asino", "boing", "boom", "cane", "cavallo", "ciao", "citofono", "dong", "evviva", "flauto", "gabbiano", "gallina", "gallo", "gatto", "grilli", "mucca", "ops", "papera", "pianto", "scacciapensieri", "trombe", "uccellino");


if (($kairos_cookie[0])) {
    $id_utente = $kairos_cookie[0];
    $pwd_utente = $kairos_cookie[1];

    $ok = true;
    if (!in_array($cod_area, $kairos_pubblici)) {
        $query = "SELECT id_utente,pwd_utente FROM utenti WHERE id_utente='$id_utente' and stato<>0";
        $result = $mysqli->query($query);
        $riga = $result->fetch_array();

        if ($riga) {
            $pwd_utente1 = $riga["pwd_utente"];
            if ($pwd_utente == md5($pwd_utente1)) {
                $ok = true;
            } else {
                $ok = false;
            }
        } else {
            $ok = false;
        };
    };

    if (!$ok) {
        setcookie("kairos_cookie[0]", "", 0, "/", $dominio); //identificativo
        setcookie("kairos_cookie[1]", "", 0, "/", $dominio); //password

        setcookie("kairos_cookie[0]", "", 0, "/", "garamond.it"); //identificativo
        setcookie("kairos_cookie[1]", "", 0, "/", "garamond.it");

        $msg = $stringa[errore_no_parametri];
        $msg = preg_replace_replace(" ", "%20", $msg);
        //deleteCookies();
        Header("Location:index.php?risorsa=msg&msg=$msg");
        exit();
    };
}

?>

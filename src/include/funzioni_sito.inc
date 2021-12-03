<?php
function refresh_utente($id_utente)
{
    global $DBASE, $DBUSER, $DBPWD, $DBHOST;
    global $cod_area;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "SELECT id_utente FROM inlinea WHERE id_utente='$id_utente'";
    $result = $mysqli->query($query);
    $riga = $result->fetch_array();

    if ($riga) {
        $query = "UPDATE inlinea SET data_conn=NOW() where id_utente='$id_utente'";
        $result = $mysqli->query($query);
    } else {
        connect_utente($id_utente);
    };


}

;

function log_utente($id_utente, $dettagli)
{
    global $DBASE, $DBUSER, $DBPWD, $USER_ADMIN, $id_corso_s, $id_edizione_s, $id_gruppo_s,$DBHOST;
    global $cod_area;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
    $query = "INSERT INTO log_sito(id_utente,data_log,dettagli,id_corso,id_edizione,id_gruppo) VALUES ('$id_utente',NOW(),'$dettagli','$id_corso_s','$id_edizione_s','$id_gruppo_s')";
    $result = $mysqli->query($query);
}

;

function log_errore($errore)
{
    $fp = fopen(KAIROS_PATH . "/kairos_error.log", "a");
    fwrite($fp, $errore);
    fclose($fp);
}

;

function log_materiali($id_utente, $dettagli)
{
    global $DBASE, $DBUSER, $DBPWD, $USER_ADMIN, $id_corso_s, $id_edizione_s, $id_gruppo_s,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
    $query = "INSERT INTO log_materiali(id_utente,data_log,dettagli,id_corso,id_edizione,id_gruppo) VALUES ('$id_utente',NOW(),'$dettagli','$id_corso_s','$id_edizione_s','$id_gruppo_s')";
    $result = $mysqli->query($query);
}

;

function connect_utente($id_utente)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $DBHOST;
    global $cod_area;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "INSERT INTO inlinea (id_utente,data_conn) VALUES ('$id_utente',NOW())";
    $result = $mysqli->query($query);
}

;

function authenticateUser($user, $password)
{
    global $DBASE, $DBUSER, $DBPWD, $DBASE_UTENTI, $kairos_cookie, $DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
    $cod_area = $kairos_cookie[4];

    $query = "SELECT id_utente,pwd_utente FROM utenti WHERE id_utente='$user'";

    if (!$result = $mysqli->query($query)) die($mysqli->error);
    $riga = $result->fetch_array();

    if ($riga) {
        $pwd_utente = $riga["pwd_utente"];
        if ($password == md5($pwd_utente)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

function deleteCookies()
{
    global $dominio;
    setcookie("kairos_cookie[0]", "", 0, "/", $dominio); //identificativo
    setcookie("kairos_cookie[1]", "", 0, "/", $dominio); //password
    setcookie("kairos_cookie[2]", "", 0, "/", $dominio); //id_corso id_edizione
    setcookie("kairos_cookie[3]", "", 0, "/", $dominio); //query url
    //setcookie("kairos_cookie[4]","",0,"/"); //cod_area
    setcookie("kairos_cookie[5]", "", 0, "/", $dominio); //cartella
    //setcookie("kairos_cookie[6]","",0,"/"); //lingua
    setcookie("kairos_cookie[7]", "", 0, "/", $dominio); //mostra_postit
    setcookie("kairos_cookie[8]", "", 0, "/", $dominio); //eprof valido
}

;


function setCookies($user, $password)
{
    global $dominio;
    $kairos_cookie[0] = $user;
    $kairos_cookie[1] = $password;

    setcookie("kairos_cookie[0]", $kairos_cookie[0], 0, "/", $dominio);
    setcookie("kairos_cookie[1]", $kairos_cookie[1], 0, "/", $dominio);
    setcookie("eureka_cookie[0]", $user, 0, "/", $dominio);
    setcookie("eureka_cookie[1]", $password, 0, "/", $dominio);
    setcookie("koine_cookie[0]", $user, 0, "/", $dominio);
    setcookie("koine_cookie[1]", $password, 0, "/", $dominio);

}

;


function getmimetype($file_name)
{
    $est = substr($file_name, -3);

    switch (strtolower($est)) {
        case "zip":
            return "application/zip";
            break;

        case "exe":
            return "application/octet-stream";
            break;

        case "xls":
            return "application/excel";
            break;

        case "doc":
            return "application/msword";
            break;

        case "pdf":
            return "application/pdf";
            break;

        case "rtf":
            return "application/rtf";
            break;

        case "jpg":
            return "image/jpeg";
            break;

        case "gif":
            return "image/gif";
            break;

        case "mid":
            return "audio/midi";
            break;

        case "mp3":
            return "audio/mpeg";
            break;

        case "ra":
            return "audio/x-realaudio";
            break;

        case "ram":
            return "audio/x-pn-realaudio";
            break;

        case "wav":
            return "audio/x-wav";
            break;

        case "avi":
            return "audio/x-msvideo";
            break;

        case "htm":
            return "text/html";
            break;

        case "txt":
            return "text/plain";
            break;

        case "mpg":
            return "video/mpeg";
            break;

        case "mov":
            return "video/quicktime";
            break;

        default:
            return "application/octet-stream";
    };
}

;

function parse_code($txt)
{
    $new_txt = htmlentities($txt);
    return $new_txt;
}

;


function parse_link($txt)
{
    //trasformo email
    $txt = eregi_replace("(([a-z0-9_]|\\-|\\.)+@([^[:space:]]*)([[:alnum:]-])\.([^[:space:]]*)([[:alnum:]-]))", "<a href=\"mailto:\\1\">\\1</a>", $txt);

    //riconosco le url
    $txt = eregi_replace("([[:alnum:]]+)://([^[:space:]]*)([[:alnum:]#\?/&=])", "<a href=\"\\1://\\2\\3\" target=\"_blank\">\\1://\\2\\3</A>", $txt);
    return $txt;
}

;


function parse_href($txt)
{
    //riconosco le url
    $txt = eregi_replace("<a href=([^>]*)>", "<a href=\\1 target=\"_blank\">", $txt);
    return $txt;

}

;

function ruolo_utente($id_utente)
{
    global $DBASE, $DBASE_UTENTI, $DBUSER, $DBPWD, $PATH_ROOT, $kairos_cookie, $DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $cod_area = $kairos_cookie["4"];


    if ($cod_area == 'kairos_facciamo') {
        return ruolo_utente_Facciamo($id_utente);
    } else {

        $query = "SELECT stato FROM utenti WHERE id_utente='$id_utente'";
        $result = $mysqli->query($query);

        $stato = 0;
        if (@$result->num_rows) {
            $riga = $result->fetch_array();
            $stato = $riga["stato"];
        };


        switch ($stato) {
            case 0:
                $ruolo = "attesa";
                break;

            case 1:
                $ruolo = "utente";
                break;

            case 2:
                $ruolo = "staff";
                break;

            case 3:
                $ruolo = "admin";
                break;

            default:
                $ruolo = "utente";
                break;

        };
        return $ruolo;
    };
}

;

function ruolo_utente_Facciamo($id_utente)
{

    if ($id_utente == 'fleo' or $id_utente == 'ghigo' or $id_utente == 'chc' or $id_utente == 'momis') {
        $ruolo = "admin";
    } else {
        $ruolo = "utente";
    };


    return $ruolo;

}

;

function risorsa_admin($id_risorsa)
{
    return false;
}

;

function id_corso($id_risorsa)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
    $query = "SELECT risorsa_padre FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
    $result = $mysqli->query($query);
    $riga = $result->fetch_array();
    $id_padre = $riga["risorsa_padre"];

    if ($id_padre == 'root') {
        return $id_risorsa;
    } else {
        return id_corso($id_padre);
    };

}

;

function gruppo_nodo($id_risorsa)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "SELECT risorsa_padre,id_gruppo FROM materiali_gruppo WHERE id_risorsa='$id_risorsa'";
    $result = $mysqli->query($query);
    $riga = $result->fetch_array();
    $id_padre = $riga["risorsa_padre"];
    $id_gruppo = $riga["id_gruppo"];

    if ($id_padre == 'root') {
        return $id_gruppo;
    } else {
        return gruppo_nodo($id_padre);
    };

}

;

function dati_nodo($id_risorsa)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "SELECT risorsa_padre,id_gruppo,titolo,id_corso,id_edizione FROM materiali_gruppo WHERE id_risorsa='$id_risorsa'";
    $result = $mysqli->query($query);
    $riga = $result->fetch_array();
    $id_padre = $riga["risorsa_padre"];
    $id_gruppo = $riga["id_gruppo"];
    $id_corso = $riga["id_corso"];
    $id_edizione = $riga["id_edizione"];
    $titolo = $riga["titolo"];

    if ($id_padre == 'root') {
        $query = "SELECT descrizione FROM gruppo_utenti WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
        $result = $mysqli->query($query);
        $riga = $result->fetch_array();
        $descr_gruppo = $riga[descrizione];
        $dati[id_modulo] = $id_risorsa;
        $dati[titolo] = $titolo;
        $dati[id_corso] = $id_corso;
        $dati[id_edizione] = $id_edizione;
        $dati[descr_gruppo] = $descr_gruppo;
        $dati[id_gruppo] = $id_gruppo;
        return $dati;
    } else {
        return dati_nodo($id_padre);
    };

}

;


function materiali_pag_prec($id_risorsa, $risorsa_superiore)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $DBHOST;
    global $id_corso;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "SELECT id_risorsa FROM risorse_materiali WHERE  (tipo=0 OR tipo=4) and risorsa_padre='$risorsa_superiore' ORDER BY posizione,id_risorsa";
    $result = $mysqli->query($query);
    $pag_prec = "";
    $continua = true;
    while (($riga = $result->fetch_array()) and $continua) {
        $pag_att = $riga["id_risorsa"];
        if ($pag_att == $id_risorsa) {
            $continua = false;
        } else {
            $pag_prec = $pag_att;
        };

    };
    return $pag_prec;
}

;

function materiali_pag_succ($id_risorsa, $risorsa_superiore)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $DBHOST;
    global $id_corso;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "SELECT id_risorsa FROM risorse_materiali WHERE  (tipo=0 OR tipo=4) and risorsa_padre='$risorsa_superiore' ORDER BY posizione DESC";
    $result = $mysqli->query($query);
    $pag_succ = "";
    $continua = true;
    while (($riga = $result->fetch_array()) and $continua) {
        $pag_att = $riga["id_risorsa"];
        if ($pag_att == $id_risorsa) {
            $continua = false;
        } else {
            $pag_succ = $pag_att;
        };
    };
    return $pag_succ;
}

;


function capitolo($id_padre, $id_nodo, $margine = "false", $target = "")
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $HTTP_COOKIE_VARS;
    global $win_ie, $opera,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_padre' AND (tipo=0 OR tipo=2 OR tipo=4) ORDER BY posizione";

    $result = $mysqli->query($query);

    if ($margine == "true") {
        echo "<ul style=\"list-style-type:none;margin-left:5px\">\n";
    } else {
        echo "<ul style=\"list-style-type:none\">\n";
    };

    while ($risorsa = $result->fetch_array()) {

        echo "<li>\n";
        $id_risorsa = $risorsa["id_risorsa"];
        $tipo = $risorsa["tipo"];
        $titolo = $risorsa["titolo"];

        if ($tipo == 4) {
            $id_gruppo = $risorsa[id_gruppo];
            $query_t = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
            $result_t = $mysqli->query($query_t);
            $riga_t = $result_t->fetch_array();
            $titolo = $riga_t[titolo];
        };


        if ($tipo == 2) {
            $cap0 = "cap0_" . $id_risorsa;
            $cap1 = "cap1_" . $id_risorsa;
            $val_capitolo = $HTTP_COOKIE_VARS["capitolo"];
            $val = $val_capitolo[$cap1];
            $aperto = ($val or padre($id_risorsa, $id_nodo));
            if (!$win_ie) $aperto = true;

            if ($aperto) {
                $immagine = "img/forum/meno.gif";
            } else {
                $immagine = "img/forum/piu.gif";
            };
            echo "<div id=$cap0 onClick=\"mostra_capitolo(this,'$cap1')\" style=\"cursor:hand\"><img name=img_" . $cap1 . " src=\"$immagine\" width=\"11\" height=\"11\" alt=\"\" border=\"0\">\n";
        };

        if ($tipo == 2) {
            if ($win_ie or $opera) {
                echo "<span class=testopiccolomenu><a href=\"javascript:;\" >$titolo</a></span>";
            } else {
                echo "<span class=testopiccolomenu><a href=\"javascript:;\">$titolo</a></span>";
            };
        } else {
            if ($id_risorsa == $id_nodo) {
                echo "<img src=	\"img/dot1.gif\" width=\"10\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolomenu><b>$titolo</b></span>";
            } else {
                if ($tipo <> 1) {
                    if ($win_ie or $opera) {
                        echo "<img src=	\"img/dot1.gif\" width=\"10\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolomenu><a href=\"materiali_browse.php?risorsa=$id_risorsa\" $target onClick=\"window.event.cancelBubble=true\">$titolo</a></span>";
                    } else {
                        echo "<img src=	\"img/dot1.gif\" width=\"10\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolomenu><a href=\"materiali_browse.php?risorsa=$id_risorsa\" $target>$titolo</a></span>";
                    }
                } else {
                    $file_size = $risorsa["file_size"];
                    $descrizione = $risorsa["descrizione"];
                    if ($win_ie or $opera) {
                        echo "<span class=testopiccolomenu>- <a href=\"materiali_browse.php?risorsa=$id_risorsa\" $target onClick=\"window.event.cancelBubble=true\" alt=\"$descrizione\">$titolo</a><br>$descrizione<br>(" . stringa_filesize($file_size) . ")</span>";
                    } else {
                        echo "<span class=testopiccolomenu>- <a href=\"materiali_browse.php?risorsa=$id_risorsa\"  $target  alt=\"$descrizione\">$titolo</a><br>$descrizione<br>(" . stringa_filesize($file_size) . ")</span>";
                    }
                };
            };
        };


        if ($tipo == 2) {
            if ($aperto) {
                $display = "Visible";
            } else {
                $display = "None";
            };
            if ($win_ie or $opera) {
                echo "<div id=$cap1 style=\"Display:$display\" onClick=\"window.event.cancelBubble=true\">\n";
            } else {
                echo "<div id=$cap1 style=\"Display:$display\">\n";
            }
            capitolo($id_risorsa, $id_nodo, "false", $target);
            echo "</div></div>\n";
        }

        echo "</li>";


    };

    echo "</ul>";

}

;


function materiali_gruppo_pag_prec($id_risorsa, $risorsa_superiore)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $DBHOST;
    global $id_corso_s, $id_edizione_s;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "SELECT id_risorsa FROM materiali_gruppo WHERE  (tipo=0) and risorsa_padre='$risorsa_superiore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY posizione,id_risorsa";
    $result = $mysqli->query($query);
    $pag_prec = "";
    $continua = true;
    while (($riga = $result->fetch_array()) and $continua) {
        $pag_att = $riga["id_risorsa"];
        if ($pag_att == $id_risorsa) {
            $continua = false;
        } else {
            $pag_prec = $pag_att;
        };

    };
    return $pag_prec;
}

;

function materiali_gruppo_pag_succ($id_risorsa, $risorsa_superiore)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $DBHOST;
    global $id_corso_s, $id_edizione_s;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "SELECT id_risorsa FROM materiali_gruppo WHERE  (tipo=0) and risorsa_padre='$risorsa_superiore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY posizione DESC";
    $result = $mysqli->query($query);
    $pag_succ = "";
    $continua = true;
    while (($riga = $result->fetch_array()) and $continua) {
        $pag_att = $riga["id_risorsa"];
        if ($pag_att == $id_risorsa) {
            $continua = false;
        } else {
            $pag_succ = $pag_att;
        };
    };
    return $pag_succ;
}

;


function capitolo_gruppo($id_padre, $id_nodo, $margine = "false", $target = "")
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $HTTP_COOKIE_VARS;
    global $win_ie, $opera;
    global $id_corso_s, $id_edizione_s,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "SELECT * FROM materiali_gruppo WHERE risorsa_padre='$id_padre' AND (tipo=0 OR tipo=2) AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY posizione";

    $result = $mysqli->query($query);

    if ($margine == "true") {
        echo "<ul style=\"list-style-type:none;margin-left:5px\">\n";
    } else {
        echo "<ul style=\"list-style-type:none\">\n";
    };

    while ($risorsa = $result->fetch_array()) {

        echo "<li>\n";
        $id_risorsa = $risorsa["id_risorsa"];
        $tipo = $risorsa["tipo"];
        $titolo = $risorsa["titolo"];

        if ($tipo == 2) {
            $cap0 = "cap0_" . $id_risorsa;
            $cap1 = "cap1_" . $id_risorsa;
            $val_capitolo = $HTTP_COOKIE_VARS["capitolo"];
            $val = $val_capitolo[$cap1];
            $aperto = ($val or padre($id_risorsa, $id_nodo));
            if (!$win_ie) $aperto = true;

            if ($aperto) {
                $immagine = "img/forum/meno.gif";
            } else {
                $immagine = "img/forum/piu.gif";
            };
            echo "<div id=$cap0 onClick=\"mostra_capitolo(this,'$cap1')\" style=\"cursor:hand\"><img name=img_" . $cap1 . " src=\"$immagine\" width=\"11\" height=\"11\" alt=\"\" border=\"0\">\n";
        };

        if ($tipo == 2) {
            if ($win_ie or $opera) {
                echo "<span class=testopiccolomenu><a href=\"javascript:;\" >$titolo</a></span>";
            } else {
                echo "<span class=testopiccolomenu><a href=\"javascript:;\">$titolo</a></span>";
            };
        } else {
            if ($id_risorsa == $id_nodo) {
                echo "<img src=	\"img/dot1.gif\" width=\"10\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolomenu><b>$titolo</b></span>";
            } else {
                if ($tipo <> 1) {
                    if ($win_ie or $opera) {
                        echo "<img src=	\"img/dot1.gif\" width=\"10\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolomenu><a href=\"materiali_gruppo_browse.php?risorsa=$id_risorsa\" $target onClick=\"window.event.cancelBubble=true\">$titolo</a></span>";
                    } else {
                        echo "<img src=	\"img/dot1.gif\" width=\"10\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolomenu><a href=\"materiali_gruppo_browse.php?risorsa=$id_risorsa\" $target>$titolo</a></span>";
                    }
                } else {
                    $file_size = $risorsa["file_size"];
                    $descrizione = $risorsa["descrizione"];
                    if ($win_ie or $opera) {
                        echo "<span class=testopiccolomenu>- <a href=\"materiali_gruppo_browse.php?risorsa=$id_risorsa\" $target onClick=\"window.event.cancelBubble=true\" alt=\"$descrizione\">$titolo</a><br>$descrizione<br>(" . stringa_filesize($file_size) . ")</span>";
                    } else {
                        echo "<span class=testopiccolomenu>- <a href=\"materiali_gruppo_browse.php?risorsa=$id_risorsa\"  $target  alt=\"$descrizione\">$titolo</a><br>$descrizione<br>(" . stringa_filesize($file_size) . ")</span>";
                    }
                };
            };
        };


        if ($tipo == 2) {
            if ($aperto) {
                $display = "Visible";
            } else {
                $display = "None";
            };
            if ($win_ie or $opera) {
                echo "<div id=$cap1 style=\"Display:$display\" onClick=\"window.event.cancelBubble=true\">\n";
            } else {
                echo "<div id=$cap1 style=\"Display:$display\">\n";
            }
            capitolo_gruppo($id_risorsa, $id_nodo, "false", $target);
            echo "</div></div>\n";
        }

        echo "</li>";


    };

    echo "</ul>";

}

;

function padre($id_risorsa, $id_nodo)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $DBHOST;
    global $id_corso;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
    $query = "SELECT risorsa_padre FROM risorse_materiali WHERE id_risorsa='$id_nodo'";
    $result = $mysqli->query($query);
    $riga = $result->fetch_array();
    $id_padre = $riga["risorsa_padre"];

    if ($id_padre == $id_risorsa) {
        return true;
    } else {
        if ($id_padre == $id_corso) {
            return false;
        } else {
            return padre($id_risorsa, $id_padre);
        };
    };

}

;

function foglia($id_risorsa)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
    $query = "SELECT id_risorsa,tipo FROM risorse_materiali WHERE risorsa_padre='$id_risorsa' AND (tipo=0 OR tipo=4 OR tipo=2) ORDER BY posizione,id_risorsa LIMIT 1";
    $result = $mysqli->query($query);
    $riga = $result->fetch_array();
    $id_risorsa = $riga["id_risorsa"];
    $tipo = $riga["tipo"];

    if ($id_risorsa) {
        if ($tipo <> 2) {
            return $id_risorsa;
        } else {
            return foglia($id_risorsa);
        };
    } else {
        return $id_risorsa;
    };
}

;

function storia_corsi($id_utente)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $stringa, $DBHOST;
    global $kairos_cookie;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    if (!$kairos_cookie[9]) $ruolo = ruolo_utente($id_utente);
    if ($ruolo <> "admin") {
        $query = "SELECT corso.descrizione,corso.id_corso,iscrizioni_corso.id_edizione,iscrizioni_corso.id_gruppo FROM corso,iscrizioni_corso,edizioni WHERE corso.id_corso=iscrizioni_corso.id_corso AND iscrizioni_corso.id_corso=edizioni.id_corso AND iscrizioni_corso.id_edizione=edizioni.id_edizione AND edizioni.stato='attiva' AND iscrizioni_corso.id_utente='$id_utente'";
        $result = $mysqli->query($query);
        echo "
			<p>
			<span class=testo>
			<b>$stringa[utente_corsi_attivi]:</b>
			</span>
			<table border=0 width=100%>";

        while ($riga = $result->fetch_array()) {
            $id_corso = $riga["id_corso"];
            $descrizione = $riga["descrizione"];
            $id_edizione = $riga["id_edizione"];
            $id_gruppo = $riga["id_gruppo"];
            $query_g = "select descrizione from gruppo_utenti where id_gruppo='$id_gruppo' and id_corso='$id_corso' and id_edizione='$id_edizione'";
            $result_g = $mysqli->query($query_g);
            $riga_g = $result_g->fetch_array();
            $descr_gruppo = $riga_g["descrizione"];

            $pw = "";
            $query_g = "select gruppo_utenti.descrizione from gruppo_utenti,iscrizioni_gruppo_pw where iscrizioni_gruppo_pw.id_gruppo=gruppo_utenti.id_gruppo and gruppo_utenti.tipo_gruppo='1' and iscrizioni_gruppo_pw.id_corso='$id_corso' and iscrizioni_gruppo_pw.id_edizione='$id_edizione' and iscrizioni_gruppo_pw.id_utente='$id_utente'";
            $result_g = $mysqli->query($query_g);
            while ($riga_g = $result_g->fetch_array()) {
                $pw .= "$riga_g[descrizione]<br>";
            };

            if ($pw) $pw = "<br><br><b>Project Work:</b><br>$pw";

            echo "
				<tr><td>
				<span class=testo>
				$descrizione ($id_edizione) $stringa[gruppo]: $descr_gruppo
				$pw
				</span>
				</td></tr>";
        };
        echo "</table>";
    };
    if ($ruolo == "staff" or $ruolo == "admin") {
        $query = "SELECT corso.descrizione,corso.id_corso,gruppo_utenti.id_edizione,gruppo_utenti.id_gruppo,gruppo_utenti.descrizione as descr_gruppo FROM corso,gruppo_utenti,edizioni WHERE corso.id_corso=gruppo_utenti.id_corso AND gruppo_utenti.id_corso=edizioni.id_corso AND gruppo_utenti.id_edizione=edizioni.id_edizione AND edizioni.stato='attiva' AND gruppo_utenti.id_tutor='$id_utente'";
        $result = $mysqli->query($query);
        echo "
			<p>
			<span class=testo>
			<b>$stringa[utente_tutor]:</b>
			</span>
			<table border=0 width=100%>";

        while ($riga = $result->fetch_array()) {
            $id_corso = $riga["id_corso"];
            $descrizione = $riga["descrizione"];
            $id_edizione = $riga["id_edizione"];
            $id_gruppo = $riga["id_gruppo"];
            $descr_gruppo = $riga["descr_gruppo"];
            echo "
				<tr><td>
				<span class=testo>
				$descrizione ($id_edizione) $stringa[gruppo]: $descr_gruppo
				</span>
				</td></tr>";
        };
        echo "</table>";

    };


}

;

function verifica_test($id_utente, $id_test, $id_corso, $id_edizione)
{
    global $DBASE, $DBUSER, $DBPWD, $DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $ok = 0;
    $esito = "";
    $query2 = "SELECT punteggio_soglia FROM test WHERE id_test='$id_test'";
    $result2 = $mysqli->query($query2);
    $risorsa2 = $result2->fetch_array();
    $punteggio_soglia = $risorsa2["punteggio_soglia"];

    $query_c = "SELECT * FROM test_compilato WHERE id_utente='$id_utente' AND id_test='$id_test' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
    $result_c = $mysqli->query($query_c);
    $continua = true;
    while ($riga_c = $result_c->fetch_array() and $continua) {
        $punteggio = $riga_c["punteggio"];

        if ($punteggio >= $punteggio_soglia) {
            $ok++;
            $continua = false;
        };
    };

    if ($ok) $esito = "approvo";
    return $esito;

}

;


function verifica_corso($id_utente, $id_corso, $id_edizione)
{
    global $DBASE, $DBUSER, $DBPWD, $DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND tipo_risorsa=3";
    $result = $mysqli->query($query);
    $elenco_test = array();
    while ($test = $result->fetch_array()) {
        $id_test = $test["id_risorsa"];
        $query_t = "SELECT punteggio_soglia,tipo_test FROM test WHERE id_test='$id_test'";
        $result_t = $mysqli->query($query_t);
        $riga_t = $result_t->fetch_array();
        $tipo_test = $riga_t["tipo_test"];
        $punteggio_soglia = $riga_t["punteggio_soglia"];
        if ($tipo_test == 0) $elenco_test[] = "$id_test,$punteggio_soglia";
    };

    $esito = "";
    if (count($elenco_test)) {
        $ok = 0;
        for ($i = 0; $i < count($elenco_test); $i++) {
            list($id_test, $punteggio_soglia) = split(",", $elenco_test[$i]);
            //echo "controllo: $id_test ($punteggio_soglia)";
            $query_c = "SELECT * FROM test_compilato WHERE id_utente='$id_utente' AND id_test='$id_test' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
            $result_c = $mysqli->query($query_c);
            $continua = true;
            while ($riga_c = $result_c->fetch_array() and $continua) {
                $punteggio = $riga_c["punteggio"];
                if ($punteggio >= $punteggio_soglia) {
                    $ok++;
                    //echo " superato <br>";
                    $continua = false;
                };
            };
        };
        if ($ok == count($elenco_test)) $esito = "approvo";
    };
    return $esito;

}

;


function browse_cartella($id_padre)
{
    global $DBHOST, $DBASE, $DBUSER, $DBPWD, $kairos_cookie, $stringa;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query = "SELECT id_risorsa,id_autore,titolo,descrizione,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m,id_gruppo FROM risorse_materiali WHERE risorsa_padre='$id_padre' ORDER BY posizione,id_risorsa";
    $result = $mysqli->query($query);


    echo "
<ul>\n";
    while ($risorsa = $result->fetch_array()) {
        $id_risorsa = $risorsa["id_risorsa"];
        $id_gruppo = $risorsa["id_gruppo"];
        $id_autore = $risorsa["id_autore"];
        $titolo = $risorsa["titolo"];
        $descrizione = $risorsa["descrizione"];
        $file_size = $risorsa["file_size"];
        $tipo = $risorsa["tipo"];
        $data_m = $risorsa["data_m"];

        echo "<li style=\"list-style-type:none\">\n";

        echo "<span class=testo>";

        switch ($tipo) {
            case 0: //pagina web
                echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"$stringa[pagina_web]\"> <a href=materiali_browse.php?risorsa=$id_risorsa title=\"$id_risorsa\">$titolo</a>\n";
                break;

            case 4: //collegamento a pagina web
                $query_r = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
                $result_r = $mysqli->query($query_r);
                $risorsa_r = $result_r->fetch_array();

                $titolo = $risorsa_r["titolo"];

                echo "
			<img src=img/pagina_web_link.gif width=16 height=16 border=0 alt=\"$stringa[pagina_web]\"> <a href=materiali_browse.php?risorsa=$id_risorsa title=\"$id_gruppo\">$titolo</a>\n";
                break;

            case 1: //file
                $icona = "file.gif";
                $est = substr($titolo, -3);
                $tipi_file = array("zip", "exe", "xls", "doc", "pdf", "rtf", "jpg", "gif", "mid", "mp3",
                    "wav", "avi", "htm", "txt", "mpg", "bmp", "ppt");

                if (in_array($est, $tipi_file)) {
                    $icona = $est . ".gif";
                };

                echo "
			<img src=img/" . $icona . " width=16 height=16 border=0 alt=\"$stringa[file]\"> <a href=materiali_browse.php?risorsa=$id_risorsa title=\"$id_risorsa\">$titolo - " . stringa_filesize($file_size) . "</a><br>$descrizione<br><br>\n";
                break;

            case 2: //cartella
                echo "
			<img src=img/folder.gif width=18 height=16 alt=\"$stringa[cartella]\" border=0> <a href=materiali_browse.php?risorsa=$id_risorsa title=\"$stringa[apri_cartella] $id_risorsa\">$titolo</a>\n";
                break;
        };
        echo "</span>";
        echo "</li>\n";
    };

    echo "</ul>\n";
}

;

function risorsa_accessibile($id_risorsa)
{
    global $DBASE, $DBUSER, $DBPWD, $PATH_ROOT, $DBHOST;
    global $id_corso_s, $id_edizione_s, $id_gruppo_s;
    global $kairos_cookie;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $id_root = id_corso($id_risorsa);

    //vedo se la risorsa ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ comune

    $query = "SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_risorsa' AND (id_corso='' OR id_corso = NULL)";
    $result = $mysqli->query($query);
    //echo "id: $id_risorsa ".$result->num_rows."<br>";
    if ($result->num_rows) {
        return "comune";
        exit();
    };


    //vedo se il padre originario della risorsa appartiene all'area comune

    $query = "SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_root' AND id_corso=''";
    $result = $mysqli->query($query);
    //echo "id: $id_root ".$result->num_rows."<br>";
    if ($result->num_rows) {
        return "comune";
        exit();
    };

    //vedo se la risorsa appartiene al corso corrente

    $query = "SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_risorsa' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='' OR id_gruppo IS NULL)";
    $result = $mysqli->query($query);

    if ($result->num_rows) {
        return "corso";
        exit();
    };

    //vedo se il padre originario della risorsa appartiene al corso

    $query = "SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_root' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='' OR id_gruppo IS NULL)";
    $result = $mysqli->query($query);

    if ($result->num_rows) {
        return "corso";
        exit();
    };


    //vedo se la risorsa appartiene al corso e gruppo corrente

    $query = "SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_risorsa' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='$id_gruppo_s')";
    $result = $mysqli->query($query);

    if ($result->num_rows) {
        return "corso";
        exit();
    };

    //vedo se il padre originario della risorsa appartiene al corso e gruppo

    $query = "SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_root' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='$id_gruppo_s')";
    $result = $mysqli->query($query);

    if ($result->num_rows) {
        return "corso";
        exit();
    };

    //verifico l'attribuzione del materiale ad eventuali gruppi di pw

    $query2 = "SELECT * FROM iscrizioni_gruppo_pw WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_utente='$kairos_cookie[0]'";
    $result2 = $mysqli->query($query2);
    while ($riga = $result2->fetch_array()) {
        $id_gruppo_x = $riga["id_gruppo"];

        //vedo se la risorsa appartiene al corso e gruppo corrente

        $query = "SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_risorsa' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='$id_gruppo_x')";
        $result = $mysqli->query($query);

        if ($result->num_rows) {
            return "gruppo";
            exit();
        };

        //vedo se il padre originario della risorsa appartiene al corso e gruppo

        $query = "SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_root' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='$id_gruppo_x')";
        $result = $mysqli->query($query);

        if ($result->num_rows) {
            return "gruppo";
            exit();
        };
    };

    return false;

}

;

function stringa_filesize($filesize)
{
    $type = Array('Bytes', 'KB', 'MB', 'GB');

    for ($i = 0; $filesize > 1024; $i++)
        $filesize /= 1024;

    return round($filesize, 2) . " $type[$i]";
}

;

function mail_job($id_package, $mail_dest, $mail_oggetto, $mail_testo, $mail_from, $mail_reply_to, $mail_bcc)
{
    global $DBASE, $DBUSER, $DBPWD, $DBHOST;
    global $cod_area;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $codifica = "";
    if ($cod_area == "kairos_cyprus") $codifica = "iso-8859-7";

    $stato = "wait";
    $mail_dest = addslashes($mail_dest);
    $mail_oggetto = addslashes($mail_oggetto);
    $mail_testo = addslashes($mail_testo);
    $mail_from = addslashes($mail_from);
    $mail_reply_to = addslashes($mail_reply_to);
    $mail_bcc = addslashes($mail_bcc);

    $query = "INSERT INTO mail_job SET
	id_package='$id_package',
	stato='$stato',
	data_packet=NOW(),
	mail_dest='$mail_dest',
	mail_oggetto='$mail_oggetto',
	mail_testo='$mail_testo',
	mail_from='$mail_from',
	mail_reply_to='$mail_reply_to',
	mail_bcc='$mail_bcc',
	codifica='$codifica'";

    $mysqli->query($query);
}

;


function get_news_forum($query)
{
    global $DBASE, $DBUSER, $DBPWD, $DBHOST;
    global $id_corso_s, $id_edizione_s, $id_gruppo_s;
    global $kairos_cookie;
    global $stringa;

    $id_utente = $kairos_cookie[0];

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query2 = $query;
    $result2 = $mysqli->query($query2);

    $news_forum = array();

    while ($forum = $result2->fetch_array()) {
        $id_forum = $forum["id_forum"];
        $descrizione = $forum["descrizione"];

        $query_post = "SELECT * FROM forum_posts WHERE id_forum='$id_forum'";
        $result_post = $mysqli->query($query_post);
        $n_posts = $result_post->num_rows;

        //vediamo se ci sono interventi nuovi per l'utente


        $flag = "";
        if ($DBASE <> "kairos_masterunitus" or 1) {
            $da_leggere = false;
            $n = 0;
            while ($intervento = $result_post->fetch_array()) {
                $id_post = $intervento["id_post"];
                $query1 = "SELECT id_post FROM forum_read WHERE id_post='$id_post' AND id_utente='$id_utente'";

                $result1 = $mysqli->query($query1);
                $num_read = $result1->num_rows;

                if (!$num_read) {
                    $da_leggere = true;
                    /*
                    if ($id_utente=='fleo') {
                        echo "$id_post <br>";
                    };
                    */
                    $n++;
                };

            };

            $flag = "(<i>$stringa[new_post]: <b>$n</b></i>)";
        };

        if ($da_leggere) {
            $news_forum[] = "<a href=index.php?risorsa=forum_indice&id_forum=$id_forum>$descrizione</a> $flag;";
        };
    };

    return $news_forum;

}

;


function get_forum($query)
{
    global $DBASE, $DBUSER, $DBPWD, $DBHOST;
    global $id_corso_s, $id_edizione_s, $id_gruppo_s;
    global $kairos_cookie;
    global $stringa;

    $id_utente = $kairos_cookie[0];

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

    $query2 = $query;
    $result2 = $mysqli->query($query2);

    $the_forum = array();

    while ($forum = $result2->fetch_array()) {
        $id_forum = $forum["id_forum"];
        $descrizione = $forum["descrizione"];

        $query_post = "SELECT * FROM forum_posts WHERE id_forum='$id_forum'";
        $result_post = $mysqli->query($query_post);
        $n_posts = $result_post->num_rows;

        //vediamo se ci sono interventi nuovi per l'utente


        $da_leggere = false;

        $flag = "";
        if ($DBASE <> "kairos_masterunitus" or 1) {
            $n = 0;
            while ($intervento = $result_post->fetch_array()) {
                $id_post = $intervento["id_post"];
                $query1 = "SELECT id_post FROM forum_read WHERE id_post='$id_post' AND id_utente='$id_utente' LIMIT 1";

                $result1 = $mysqli->query($query1);
                $num_read = $result1->num_rows;

                if (!$num_read) {
                    $da_leggere = true;
                    $n++;
                };

            };

            if ($da_leggere) {
                $flag = "(<i>$stringa[new_post]: <b>$n</b> su $n_posts</i>)";
            } else {
                $flag = "($n_posts)";
            };

        };

        $the_forum[] = "<a href=index.php?risorsa=forum_indice&id_forum=$id_forum>$descrizione</a>&nbsp;$flag";

    };

    return $the_forum;

}

;

function multi_strpos($pattern, $sequence) {
    $n = -1;
    while (eregi($pattern, $sequence)) {
        $n++;
        $fragment = split($pattern, $sequence);
        $trimsize = (strlen($fragment[0]))+1;
        $sequence = "*".substr($sequence, $trimsize);
        $position[$n] = (strlen($fragment[0]) + $position[($n-1)]);
    };

    return $position;

};

function debug_math($position0, $position1)
{
    global $kairos_cookie;
    if ($kairos_cookie[0] == "lupinsky") {
        $fd = fopen("/var/www/html/prototipo/kairos/lupinsky/debugformula.txt", "a");
        fwrite($fd, "position0\n");
        foreach ($position0 as $key => $value) {
            if (isset($position1[$key]))
                $pos1 = $position1[$key];
            else
                $pos1 = " non c'e'";
            fwrite($fd, "[$key]:$value - $pos1\n");
        }
        $i = $key;
        while (isset($position1[$i])) {
            echo "pos1 in piu=$position1[$i]\n";
            $i++;
        }

    }
}

function parse_kairos($contenuto)
{


    //if ($kairos_cookie[0]=="fleo")
    //$fd=fopen("/var/www/html/prototipo/kairos/shell/script/debug_formula.txt","a");


    $texvc = "/var/www/html/prototipo/kairos/formule/texvc";
    $tmpDir = "/var/www/html/prototipo/kairos/formule/tmp";
    $imgDir = "/var/www/html/prototipo/kairos/formule";

    $contenuto_originale = $contenuto;

    $pattern = "ks:";
    $position0 = multi_strpos($pattern, $contenuto_originale);

    $pattern = ":/ks";
    $position1 = multi_strpos($pattern, $contenuto_originale);

    if ($position0) {

        while (list($index, $pos0) = each($position0)) {
            $pos1 = $position1[$index];
            $comando = substr($contenuto_originale, $pos0 + 3, $pos1 - $pos0 - 3);

            if ($comando) {
                list($azione, $parametro) = split(":", $comando);
                switch ($azione) {
                    case "dettagli_utente":
                        $codice = "<span class=testo><a class=miolink href=\"javascript:;\" title=\"Clicca per sapere chi ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½...\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$parametro','myRemoteUtente','height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$parametro</a></span>";
                        break;

                };
                $comando = "ks:" . $comando . ":/ks";
                $contenuto = str_replace($comando, $codice, $contenuto);
            };

        };
    };

    $contenuto_originale = $contenuto;

    $pattern = "math:";
    $position0m = multi_strpos($pattern, $contenuto_originale);

    $pattern = ":/math";
    $position1m = multi_strpos($pattern, $contenuto_originale);
    //if ($position0m)
    //	debug_math($position0m,$position1m);
    if ($position0m) {

        while (list($index, $pos0) = each($position0m)) {
            $pos1 = $position1m[$index];
            $formula = (substr($contenuto_originale, $pos0 + 5, $pos1 - $pos0 - 5));


            $pos_alt0 = strpos($formula, "[alt]");
            $pos_alt1 = strpos($formula, "[/alt]");

            $alt_txt_flag = false;
            if ($pos_alt0) {
                $alt_txt = substr($formula, $pos_alt0 + 5, $pos_alt1 - $pos_alt0 - 5);
                $formula = substr($formula, 0, $pos_alt0);
                $alt_txt_flag = true;
            };

            $formula1 = html_entity_decode(trim($formula));
            $formula1 = str_replace("<a>;", "", $formula1);
            $formula1 = str_replace("</a>", "", $formula1);

            if (!$alt_txt_flag) $alt_txt = $formula1;

            //echo $formula1."<br>";
            if ($formula) {
                $immagine = genera_formula($formula1);
                list($errore, $msg) = split(":", $immagine);
                if ($errore == "errore") {
                    $formula_img = "$formula <b>$msg</b>";
                } else {
                    $strImagePath = "formule/{$immagine}.png";
                    trasparenza_png($strImagePath);

                    $formula_img = "<img class=\"immagineinlinea\" src=\"formule/{$immagine}.png\" alt=\"$alt_txt\">";
                };
                //$formula=str_replace(">","&gt;",$formula1);
                //$formula=str_replace("<","&lt;",$formula);
                if ($alt_txt_flag) {
                    $stringa = "math:" . $formula . "[alt]" . $alt_txt . "[/alt]" . ":/math";
                } else {
                    $stringa = "math:" . $formula . ":/math";
                };

                //if ($kairos_cookie[0]=="fleo")
                //fwrite($fd,$stringa." => ".$formula_img."\r\n\r\n");

                $contenuto = str_replace($stringa, $formula_img, $contenuto);
            };

        };
    };

    //if ($kairos_cookie[0]=="fleo")
    //fclose($fd);

    return $contenuto;
}

;

function genera_formula($formula)
{

    $formula = (trim($formula));
    $texvc = "/var/www/html/prototipo/kairos/formule/texvc";
    $tmpDir = "/var/www/html/prototipo/kairos/formule/tmp";
    $imgDir = "/var/www/html/prototipo/kairos/formule";

    $tex = "\"$formula\"";

    $cmd = $texvc . ' ' .
        $tmpDir . ' ' .
        $imgDir . ' ' .
        $tex . ' iso-8859-1';

    $contents = shell_exec($cmd);

    $errore = "";
    if (strlen($contents) == 0) {
        $errore .= " errore in conversione formula";
        return "errore:$errore";
    };

    $retval = substr($contents, 0, 1);
    if (($retval == 'C') || ($retval == 'M') || ($retval == 'L')) {
        if ($retval == 'C')
            $conservativeness = 2;
        else if ($retval == 'M')
            $conservativeness = 1;
        else
            $conservativeness = 0;

        $outdata = substr($contents, 33);

        $i = strpos($outdata, "\000");

        $html = substr($outdata, 0, $i);
        $mathml = substr($outdata, $i + 1);
    } else if (($retval == 'c') || ($retval == 'm') || ($retval == 'l')) {
        $html = substr($contents, 33);

        if ($retval == 'c')
            $conservativeness = 2;
        else if ($retval == 'm')
            $conservativeness = 1;
        else
            $conservativeness = 0;

        $mathml = NULL;

    } else if ($retval == 'X') {
        $html = NULL;
        $mathml = substr($contents, 33);
        $conservativeness = 0;

    } else if ($retval == '+') {
        $html = NULL;
        $mathml = NULL;
        $conservativeness = 0;

    } else {
        $errbit = htmlspecialchars(substr($contents, 1));

        switch ($retval) {
            case 'E':
                $errore .= ' math_lexing_error ' . $errbit;
                break;
            case 'S':
                $errore .= ' math_syntax_error' . $errbit;
                break;
            case 'F':
                $errore .= ' math_unknown_function ' . $errbit;
                break;
            default:
                $errore .= ' math_unknown_error ' . $errbit;
                break;
        };
        return "errore:$errore";
    }


    $hash = substr($contents, 1, 32);

    if (!preg_match("/^[a-f0-9]{32}$/", $hash)) {
        $errore .= ' math_unknown_error';
        return "errore:$errore";
    }

    if (!file_exists("$imgDir/{$hash}.png")) {
        $errore .= ' math_image_error';
        return "errore:$errore";
    };

    if ($errore) {
        return "errore:$errore";
    } else {
        return ($hash);
    };
}

;

function trasparenza_png($immagine)
{

    $image = imagecreatefrompng($immagine);
    list($width, $height, $type, $attr) = getimagesize($immagine);
    $white_color = imagecolorallocate($image, 255, 255, 255);
    $trans_color = imagecolortransparent($image, $white_color);

    $max = 0;
    $width = $width - 1;
    $height = $height - 1;

    $i = 0;
    $j = 0;
    while ($j <= $height) {
        $i = 0;
        while ($i <= $width) {
            $rgb = ImageColorAt($image, $i, $j);
            if ($rgb > $max) $max = $rgb;
            $i++;
        }
        $j++;
    }

    $i = 0;
    $j = 0;
    while ($j <= $height) {
        $i = 0;
        while ($i <= $width) {
            $rgb = ImageColorAt($image, $i, $j);
            if ($rgb == $max)
                imagesetpixel($image, $i, $j, $white_color);
            $i++;
        }
        $j++;
    }

    imagepng($image, $immagine);
    imagedestroy($image);
}

;

function vocali_accentate_off($stringa)
{
    $stringa = str_replace("ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½", "a'", $stringa);
    $stringa = str_replace("ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½", "e'", $stringa);
    $stringa = str_replace("ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½", "i'", $stringa);
    $stringa = str_replace("ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½", "o'", $stringa);
    $stringa = str_replace("ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½", "u'", $stringa);
    return $stringa;
}

;

function lo_mostra($id_u, $id_corso, $id_edizione, $solodafare = true)
{
    global $DBASE, $DBUSER, $DBPWD, $DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
    $query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND (id_gruppo='' OR id_gruppo IS NULL) AND tipo_risorsa='20' ORDER BY ordine";
    $result = $mysqli->query($query);
    if ($result->num_rows) {
        echo "<ul style=\"list-style-type:none;margin-left:5px\">\n";
        while ($risorsa = $result->fetch_array()) {
            $id_risorsa = $risorsa["id_risorsa"];
            $tipo_risorsa = $risorsa["tipo_risorsa"];

            $query2 = "SELECT id_risorsa,id_autore,titolo,descrizione,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
            $result2 = $mysqli->query($query2);
            $risorsa2 = $result2->fetch_array();
            $id_autore = $risorsa2["id_autore"];
            $titolo = $risorsa2["titolo"];
            $descrizione = $risorsa2["descrizione"];

            $query_lo = "SELECT * FROM lo WHERE id_lo='$id_risorsa'";
            $result_lo = $mysqli->query($query_lo);
            $riga_lo = $result_lo->fetch_array();

            $lo_tipo = $riga_lo["lo_tipo"];
            $lo_url = $riga_lo["lo_url"];
            $width = $riga_lo["width"];
            $height = $riga_lo["height"];

            $query_lo = "SELECT * FROM scorm_scoes_track WHERE scoid='$id_risorsa' AND userid='$id_u' AND element='cmi.core.lesson_status'";
            $result_lo = $mysqli->query($query_lo);
            $riga_lo = $result_lo->fetch_array();
            $stato_lo = $riga_lo["value"];
            $icona_stato = "ico_lo_dacompletare.gif";
            if (!$riga_lo or $stato_lo == 'not attempted') $icona_stato = "ico_lo_maiaperto.gif";
            if ($stato_lo == 'incomplete') $icona_stato = "ico_lo_dacompletare.gif";
            if ($stato_lo == 'completed' or $stato_lo == 'passed' or $stato_lo == 'failed') $icona_stato = "ico_lo_completato.gif";

            if (($solodafare and $icona_stato <> "ico_lo_completato.gif") or !$solodafare) {
                echo "<li>\n";
                echo "<img src=\"img/$icona_stato\" width=\"17\" height=\"15\" alt=\"$stato_lo\" border=\"0\" align=middle>";
                echo "&nbsp;";

                if ($lo_tipo == '1') {
                    $tipo_lancio = "lo";
                } else {
                    $tipo_lancio = "url";
                    $tipo = 22;
                };

                echo "<a href=\"javascript:;\" onclick=\"javascript:apri_scheda('sco_viewer.php?id_risorsa=$id_risorsa&tipo=$tipo_lancio&url=$lo_url','myRemoteLO',        'height=$height,width=$width,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=0,scrollbars=0,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLO');\"><span class=testo>$titolo</span></a>";

                echo "</li><br>\n";
            };

        };
        echo "</ul>\n";
    };
}

;

?>

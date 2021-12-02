<?php
function thread_risorse($id_padre, $pagina)
{
    global $DBHOST, $DBASE, $DBUSER, $DBPWD, $kairos_cookie, $stringa, $mysqli, $pag_size;

    $id_utente = $kairos_cookie["0"];

    $query = "SELECT id_risorsa,id_autore,titolo,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m,id_gruppo FROM risorse_materiali WHERE risorsa_padre='$id_padre' ORDER BY posizione";
    $result = $mysqli->query($query);

    if (!$pag_size) $pag_size = 20;
    if (!$pagina) $pagina = 1;

    $tot_righe = $result->num_rows;
    $tot_pag = floor($tot_righe / $pag_size);
    if (($tot_righe % $pag_size) <> 0) $tot_pag++;

    $num = $tot_righe;

    echo "
<ul>\n";


//scorro fino alla pagina
    $num_pag = 1;
    $righe = 0;
    $progr = 0;
    $continua = true;
    $risorsa = $result->fetch_array();
    while ($num_pag <> $pagina and $continua) {
        if ($risorsa) {
            $righe++;
            $progr++;
        } else {
            $continua = false;
        };
        if ($righe > $pag_size) {
            $num_pag++;
            $righe = 1;
        };
        if ($num_pag <> $pagina) {
            $risorsa = $result->fetch_array();
        };
    };

    if (!$progr) $progr = 1;
    $righe = 1;
    $continua = true;
    while ($risorsa and  $continua) {
        $id_risorsa = $risorsa["id_risorsa"];
        $id_gruppo = $risorsa["id_gruppo"];
        $id_autore = $risorsa["id_autore"];
        $titolo = $risorsa["titolo"];
        $file_size = $risorsa["file_size"];
        $tipo = $risorsa["tipo"];
        $data_m = $risorsa["data_m"];

        echo "<li style=\"list-style-type:none\">\n";
        echo "<span class=testo>";
        echo "<a href=materiali_sposta.php?id_risorsa=$id_risorsa&risorsa_padre=$id_padre&azione=up&pagina=$pagina><img src=img/up.gif width=13 height=13 border=0 alt=\"$stringa[pagina_up]\"></a><a href=materiali_sposta.php?id_risorsa=$id_risorsa&risorsa_padre=$id_padre&azione=down&pagina=$pagina><img src=img/down.gif width=13 height=13 border=0 alt=\"$stringa[pagina_down]\"></a>";

        switch ($tipo) {
            case 0: //pagina web
                echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"$stringa[pagina_web]\"> <a href=materiali_browse.php?risorsa=$id_risorsa target=_blank title=\"$id_risorsa\">$titolo</a> ($id_autore - $data_m)  <a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo&pagina=$pagina><img src=img/modify.gif width=25 height=24 alt=\"$stringa[modifica]\" border=0></a><a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre&pagina=$pagina><img src=img/delete.gif width=25 height=24 alt=\"$stringa[cancella]\" border=0></a>\n";
                break;

            case 4: //collegamento a pagina web
                $query_r = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
                $result_r = $mysqli->query($query_r);
                $risorsa_r = $result_r->fetch_array();

                $titolo = $risorsa_r["titolo"];

                echo "
			<img src=img/pagina_web_link.gif width=16 height=16 border=0 alt=\"$stringa[pagina_web]\"> <a href=materiali_browse.php?risorsa=$id_risorsa target=_blank title=\"$id_gruppo\">$titolo</a> ($id_autore - $data_m)   <a href=materiali_form_mod.php?id_risorsa=$id_gruppo&tipo=0><img src=img/modify.gif width=25 height=24 alt=\"$stringa[modifica]\" border=0></a><a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre><img src=img/delete.gif width=25 height=24 alt=\"$stringa[cancella]\" border=0></a>\n";
                break;


            case 3: //nota
                echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0 alt=\"$stringa[nota]\">(*) <a href=materiali_browse.php?risorsa=$id_risorsa target=_blank title=\"$id_risorsa\">$titolo</a> ($id_autore - $data_m)  <a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo><img src=img/modify.gif width=25 height=24 alt=\"$stringa[modifica]\" border=0></a><a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre><img src=img/delete.gif width=25 height=24 alt=\"$stringa[cancella]\" border=0></a>\n";
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
			<img src=img/" . $icona . " width=16 height=16 border=0 alt=\"$stringa[file]\"> <a href=materiali_browse.php?risorsa=$id_risorsa title=\"$id_risorsa\">$titolo - $file_size Byte</a> ($id_autore - $data_m)  <a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo><img src=img/modify.gif width=25 height=24 alt=\"$stringa[modifica]\" border=0></a><a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre><img src=img/delete.gif width=25 height=24 alt=\"$stringa[cancella]\" border=0></a>\n";
                break;

            case 2: //cartella
                echo "
			<img src=img/folder.gif width=18 height=16 alt=\"$stringa[cartella]\" border=0> <a href=index.php?risorsa=materiali_index&id_cartella=$id_risorsa title=\"$stringa[apri_cartella] $id_risorsa\">$titolo</a>  ($id_autore - $data_m) <a href=materiali_form_mod.php?id_risorsa=$id_risorsa&tipo=$tipo><img src=img/modify.gif width=25 height=24 alt=\"$stringa[modifica]\" border=0></a><a href=index.php?risorsa=materiali_del&id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$id_padre><img src=img/delete.gif width=25 height=24 alt=\"$stringa[cancella]\" border=0></a><br>\n";
                break;
        };
        echo "</span>";
        echo "</li>\n";

        $righe++;
        $progr++;
        $risorsa = $result->fetch_array();
        if ($righe > $pag_size) {
            $continua = false;
        };

    };
    echo "</ul>\n";
    echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
    $i = 1;
    while ($i <= $tot_pag) {
        if ($i == $pagina) {
            echo "[<b>$i</b>]";
        } else {
            echo "
		[<a href=index.php?risorsa=materiali_index&pagina=$i&pag_size=$pag_size&id_cartella=$id_padre>$i</a>]
		";
        };
        $i++;
    };
    echo "</span><br>";

    echo "
<hr size=1>
<span class=testo><b>$stringa[repertorio_pagine]</b></span>
<br>
<form action=collegamento_risorse.php method=post>
<input type=hidden name=risorsa_padre value=\"$id_padre\">
";
    $query = "SELECT * FROM risorse_materiali WHERE tipo='0' AND risorsa_padre<>'$id_padre' ORDER BY id_risorsa";
    $result = $mysqli->query($query);
    $elenco = "";
    while ($riga = $result->fetch_array()) {
        $id_risorsa = $riga[id_risorsa];
        $titolo = $riga[titolo];
        $elenco .= "<option value=\"$id_risorsa\">$titolo ($id_risorsa)</option>";
    };
    echo "
<select multiple name=collega_risorse[] size=20>
$elenco
</select><br>
<input type=submit value=\"$stringa[collega_pagine]\">
</form>";

}

;


function cancella_contenuto($id_padre)
{
    global $DBHOST, $DBASE, $DBUSER, $DBPWD, $PATH_ARCHIVI_ADMIN, $PATH_ROOT_FILE, $mysqli;
    global $kairos_cookie;

    $cod_area = $kairos_cookie[4];

    $query = "SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_padre'";
    $result = $mysqli->query($query);
    while ($riga = $result->fetch_array()) {
        $id_figlio = $riga["id_risorsa"];
        $tipo_figlio = $riga["tipo"];

        if ($tipo_figlio == 0) {
            $file_codice = $PATH_ROOT_FILE . "materiali/$cod_area/$id_figlio.inc";
            if (file_exists($file_codice)) {
                unlink($file_codice);
            };
            $query_t = "DELETE FROM risorse_materiali WHERE id_gruppo='$id_figlio'";
            $mysqli->query($query_t);
        };


        if ($tipo_figlio == 1) {
            $query1 = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_figlio'";
            $result1 = $mysqli->query($query1);
            $riga1 = $result1->fetch_array();
            $titolo = $riga1["titolo"];
            $fullpath = $PATH_ARCHIVI_ADMIN . "materiali/$cod_area/" . $titolo;

            if (file_exists($fullpath)) {
                unlink($fullpath);
            };
        };

        if ($tipo_figlio == 2) {
            cancella_contenuto($id_figlio);
        };
        $query2 = "DELETE FROM risorse_materiali WHERE id_risorsa='$id_figlio'";
        $result2 = $mysqli->query($query2);
    };
}

;


function browse_folder($cartella, $tipo_file = '')
{
    global $PATH_ROOT, $PATH_ROOT_FILE, $cod_area, $stringa;

    if (!$cartella or $cartella == "/" or trim($cartella) == "" or ereg("^\\.(.+)$", $cartella)) {
        $cartella = "";
    };

    $dir_path = $PATH_ROOT_FILE . "materiali_img/$cod_area/" . $cartella;

    if (!is_dir($dir_path)) {
        $cartella = "";
        $dir_path = $PATH_ROOT_FILE . "materiali_img/$cod_area/" . $cartella;
    };

    if ($cartella <> "") {
        $padre = dirname($cartella);
        echo "
		[<a href=index.php?risorsa=materiali_cartella&tipo=$tipo_file&cartella=$padre>$stringa[dir_superiore]</a>]<br><hr>";
    };

    echo "<h1>" . $cartella . "</h1>";
    $i = 0;
    $d = dir($dir_path);
    while ($filename = $d->read()) {
        if (($filename != '.') && ($filename != '..')) {
            $prendi = true;
            $path_file = $PATH_ROOT_FILE . "materiali_img/$cod_area/" . $cartella . "/" . $filename;
            if ($tipo_file and !is_dir($path_file)) {
                ereg("^(.+)\.(.+)$", $filename, $parti);
                $est = $parti[2];

                switch ($tipo_file) {
                    case "audio":
                        if ($est <> 'wav' and $est <> 'au' and $est <> 'asf'
                            and $est <> 'mid'
                        ) {
                            $prendi = false;
                        };
                        break;

                    case "video":
                        if ($est <> 'avi' and $est <> 'mov' and $est <> 'mpg') {
                            $prendi = false;
                        };
                        break;

                    case "flash":
                        if ($est <> 'swf') {
                            $prendi = false;
                        };
                        break;

                    case "img":
                        if ($est <> 'gif' and $est <> 'jpg' and $est <> 'png') {
                            $prendi = false;
                        };
                        break;
                };
            };

            if ($prendi) {
                $entry[$i] = $filename;
                $i++;
            };
        };
    };
    $d->close();
    if ($i) {
        sort($entry);
    };

    for ($j = 0; $j < $i; $j++) {
        $filename = $entry[$j];
        $path_file = $PATH_ROOT_FILE . "materiali_img/$cod_area/" . $cartella . "/" . $filename;
        echo "
		<input type=checkbox name=$filename> ";
        if (is_dir($path_file)) {
            echo "
				<img src=img/folder.gif width=18 height=16 border=0> <a href=index.php?risorsa=materiali_cartella&tipo=$tipo_file&cartella=$cartella" . "/" . $filename . ">$filename</a><br>";
        } else {
            if ($cartella) {
                $val = $PATH_ROOT . "materiali_img/$cod_area/" . $cartella . "/" . $filename;
            } else {
                $val = $PATH_ROOT . "materiali_img/$cod_area/$filename";
            };
            echo "<a href=$val target=_blank>$filename</a> [<a href=\"javascript:;\" onclick=\"inserisci_indirizzo('$val');\">$stringa[inserisci]</a>] [<a href=\"javascript:;\" onclick=\"copia_indirizzo('$val');\">$stringa[copia_indirizzo]</a>] <br>\n";
        };
    };
}

;

function setup_posizione($id_padre)
{
    global $DBHOST, $DBASE, $DBUSER, $DBPWD,$mysqli;
    $pos = 1;
    $query = "SELECT id_risorsa,tipo FROM risorse_materiali WHERE risorsa_padre='$id_padre' ORDER BY posizione,id_risorsa";
    $result = $mysqli->query($query);
    while ($riga = $result->fetch_array()) {
        $id_risorsa = $riga["id_risorsa"];
        $tipo = $riga["tipo"];
        $query2 = "UPDATE risorse_materiali SET posizione='$pos' WHERE id_risorsa='$id_risorsa'";
        $mysqli->query($query2);
        $pos++;
        if ($tipo == 2) {
            setup_posizione($id_risorsa);
        };
    };
}

;

function contiene_pagina($id_cartella)
{
    global $DBHOST, $DBASE, $DBUSER, $DBPWD,$mysqli;

    $risultato = false;
    $query = "SELECT tipo FROM risorse_materiali WHERE risorsa_padre='$id_cartella' ORDER BY posizione,id_risorsa";
    $result = $mysqli->query($query);
    while ($riga = $result->fetch_array() and !$risultato) {
        $tipo = $riga["tipo"];
        if ($tipo == 0 or $tipo == 4) {
            $risultato = true;
        };
    };
    return $risultato;
}

;

function path_cartella($id_cartella)
{
    global $DBHOST, $DBASE, $DBUSER, $DBPWD,$mysqli;

    $db = mysql_connect($DBHOST, $DBUSER, $DBPWD);
    mysql_select_db($DBASE, $db);

    if ($id_cartella == "root") {
        return "";
    } else {

        $query = "select titolo,risorsa_padre FROM risorse_materiali WHERE id_risorsa='$id_cartella'";
        $result = $mysqli->query($query);
        $riga = $result->fetch_array();
        $titolo = $riga[titolo];
        $id_cartella_sup = $riga["risorsa_padre"];
        return path_cartella($id_cartella_sup) . "/" . "<a href=index.php?risorsa=materiali_index&id_cartella=$id_cartella>$titolo</a>";
    };
}

;

?>

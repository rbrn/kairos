<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_pagina = trim($_REQUEST["id_pagina"]);
$tipo_pagina = $_REQUEST["tipo_pagina"];
$risorsa_padre = $_REQUEST["risorsa_padre"];
$file_audio = trim($_REQUEST["file_audio"]);
$audio_cancella = trim($_REQUEST["audio_cancella"]);
$testo = $_REQUEST["testo"];

$id_utente = $kairos_cookie["0"];

if ($tipo_pagina == "1" or $tipo_pagina == "12" or $tipo_pagina == "13" or $tipo_pagina == "14" or $tipo_pagina == "15") {

    $result = $mysqli->query("SELECT * FROM lo_pagina_asset WHERE tipo_asset='1' AND id_pagina='$id_pagina'");

    if ( $result->num_rows ==0) {
        $query = "INSERT INTO lo_pagina_asset SET " .
            " id_pagina='$id_pagina'," .
            " tipo_asset='1'," .
            " id_editor='$id_utente'";
        if ($result = $mysqli->query($query)){
            echo 'The ID is: '.$mysqli->insert_id;
            $result->current_field;

            $id_pagina_asset = $mysqli->insert_id;
        } else {
            die($mysqli->error);
        }

			//$id_pagina_asset=$mysqli->insert_id;
		} else {
        $riga = $result->fetch_array();
        $id_pagina_asset = $riga["id_pagina_asset"];
        $query = "UPDATE lo_pagina_asset SET " .
            " id_editor='$id_utente'" .
            " WHERE id_pagina_asset='$id_pagina_asset'";
        $mysqli->query($query);
    };

    if ($testo) {
        $file_asset = $PATH_ROOT_FILE . "materiali/$cod_area/asset_" . $id_pagina . "_" . $id_pagina_asset . ".inc";
        $fp = fopen($file_asset, "w");
        if(!$fp) die("file cannot be created    " . $file_asset);
        fwrite($fp, stripslashes($testo));
        fclose($fp);
    };
};

$errore = "";


switch ($tipo_pagina) {
    case "2":
        $file_asset = $_REQUEST["file_immagine"];
        $alt_text = $_REQUEST["alt_text"];
        $tipo_asset = "2";
        if (!$file_asset) {
            $errore .= "<p>Manca il riferimento al file immagine</p>";
        };
        if (!$alt_text) {
            $errore .= "<p>Manca il testo alternativo</p>";
        };
        break;

    case "12":
        $file_asset = $_REQUEST["file_immagine"];
        $alt_text = $_REQUEST["alt_text"];
        $posizione = $_REQUEST["posizione"];
        $tipo_asset = "2";
        if (!$file_asset) {
            $errore .= "<p>Manca il riferimento al file immagine</p>";
        };
        if (!$alt_text) {
            $errore .= "<p>Manca il testo alternativo</p>";
        };
        break;


    case "3":
        $file_asset = $_REQUEST["file_video"];
        $alt_text = $_REQUEST["alt_text"];
        $alt_img = $_REQUEST["alt_img"];
        $tipo_asset = "3";
        if (!$file_asset) {
            $errore .= "<p>Manca il riferimento al file video</p>";
        };
        if (!$alt_text) {
            $errore .= "<p>Manca il testo alternativo</p>";
        };
        if (!$alt_img) {
            $errore .= "<p>Manca immagine alternativa</p>";
        };
        break;

    case "13":
        $file_asset = $_REQUEST["file_video"];
        $alt_text = $_REQUEST["alt_text"];
        $alt_img = $_REQUEST["alt_img"];
        $posizione = $_REQUEST["posizione"];
        $tipo_asset = "3";
        if (!$file_asset) {
            $errore .= "<p>Manca il riferimento al file video</p>";
        };
        if (!$alt_text) {
            $errore .= "<p>Manca il testo alternativo</p>";
        };
        if (!$alt_img) {
            $errore .= "<p>Manca immagine alternativa</p>";
        };
        break;

    case "4":
        $file_asset = $_REQUEST["file_flash"];
        $alt_text = $_REQUEST["alt_text"];
        $alt_img = $_REQUEST["alt_img"];
        $tipo_asset = "4";
        $width = $_REQUEST["f_w"];
        $height = $_REQUEST["f_h"];
        if (!$file_asset) {
            $errore .= "<p>Manca il riferimento al file Flash</p>";
        };
        if (!$alt_text) {
            $errore .= "<p>Manca il testo alternativo</p>";
        };
        if (!$alt_img) {
            $errore .= "<p>Manca immagine alternativa</p>";
        };
        break;

    case "14":
        $file_asset = $_REQUEST["file_flash"];
        $alt_text = $_REQUEST["alt_text"];
        $alt_img = $_REQUEST["alt_img"];
        $posizione = $_REQUEST["posizione"];
        $tipo_asset = "4";
        $width = $_REQUEST["f_w"];
        $height = $_REQUEST["f_h"];
        if (!$file_asset) {
            $errore .= "<p>Manca il riferimento al file Flash</p>";
        };
        if (!$alt_text) {
            $errore .= "<p>Manca il testo alternativo</p>";
        };
        if (!$alt_img) {
            $errore .= "<p>Manca immagine alternativa</p>";
        };
        break;

    case "15":
        $file_asset = $_REQUEST["file_geogebra"];
        $alt_text = $_REQUEST["alt_text"];
        $alt_img = $_REQUEST["alt_img"];
        $posizione = $_REQUEST["posizione"];
        $tipo_asset = "5";
        if (!$file_asset) {
            $errore .= "<p>Manca il riferimento al file ggb</p>";
        };
        if (!$alt_text) {
            $errore .= "<p>Manca il testo alternativo</p>";
        };
        if (!$alt_img) {
            $errore .= "<p>Manca immagine alternativa</p>";
        };
        break;

};

if ($errore) {
    $errore = ereg_replace(" ", "%20", $errore);
    header("Location:index.php?risorsa=msg&msg=$errore");
    exit();
};

if ($tipo_pagina == "2" or $tipo_pagina == "3" or $tipo_pagina == "4" or $tipo_pagina == "12" or $tipo_pagina == "13" or $tipo_pagina == "14" or $tipo_pagina == "15") {

    $query = "SELECT * FROM lo_pagina_asset WHERE tipo_asset='$tipo_asset' AND id_pagina='$id_pagina'";
    $result = $mysqli->query($query);

    if ($result->num_rows == 0) {
        $query = "INSERT INTO lo_pagina_asset SET " .
            " id_pagina='$id_pagina'," .
            " tipo_asset='$tipo_asset'," .
            " file_asset='$file_asset'," .
            " alt_text='$alt_text'," .
            " alt_img='$alt_img'," .
            " posizione='$posizione'," .
            " width='$width'," .
            " height='$height'," .
            " id_editor='$id_utente'";
        $mysqli->query($query);
        $id_pagina_asset = $mysqli->insert_id;
    } else {
        $riga = $result->fetch_array();
        $id_pagina_asset = $riga["id_pagina_asset"];
        $query = "UPDATE lo_pagina_asset SET " .
            " file_asset='$file_asset'," .
            " alt_text='$alt_text'," .
            " alt_img='$alt_img'," .
            " posizione='$posizione'," .
            " width='$width'," .
            " height='$height'," .
            " id_editor='$id_utente'" .
            " WHERE id_pagina_asset='$id_pagina_asset'";
        $mysqli->query($query);
    };
};

if ($file_audio) {
    $query = "SELECT * FROM lo_pagina_asset WHERE tipo_asset='5' AND id_pagina='$id_pagina'";
    $result = $mysqli->query($query);
    if ($audio_cancella == "on") {
        $riga = $result->fetch_array();
        $id_pagina_asset = $riga["id_pagina_asset"];
        $query = "DELETE FROM lo_pagina_asset " .
            " WHERE id_pagina_asset='$id_pagina_asset'";
        $mysqli->query($query);
    } else {
        if ($result->num_rows == 0) {
            $query = "INSERT INTO lo_pagina_asset SET " .
                " id_pagina='$id_pagina'," .
                " tipo_asset='5'," .
                " file_asset='$file_audio'," .
                " id_editor='$id_utente'";
            $mysqli->query($query);
            $id_pagina_asset = $mysqli->insert_id;
        } else {
            $riga = $result->fetch_array();
            $id_pagina_asset = $riga["id_pagina_asset"];
            $query = "UPDATE lo_pagina_asset SET " .
                " file_asset='$file_audio'," .
                " id_editor='$id_utente'" .
                " WHERE id_pagina_asset='$id_pagina_asset'";
            $mysqli->query($query);
        };
    };
};


if ($tipo_pagina == "12" and ($posizione == "1" or $posizione == "2")) {
    $query_img = "SELECT * FROM lo_pagina_asset WHERE id_pagina='$id_pagina' AND posizione_int>1 ORDER BY posizione_int";
    $result_img = $mysqli->query($query_img);
    while ($riga_img = $result_img->fetch_array()) {
        $id_pagina_asset_img = $riga_img["id_pagina_asset"];
        $nome_campo_img = "img_" . $id_pagina_asset_img;
        $nome_campo_alt_text = "alt_text_" . $id_pagina_asset_img;

        $file_asset = ${$nome_campo_img};
        $alt_text = ${$nome_campo_alt_text};

        $query = "UPDATE lo_pagina_asset SET " .
            " file_asset='$file_asset'," .
            " alt_text='$alt_text'," .
            " id_editor='$id_utente'" .
            " WHERE id_pagina_asset='$id_pagina_asset_img'";
        $mysqli->query($query);
    };
};
Header("Location:index.php?risorsa=repository_index&id_cartella=$risorsa_padre");
?>

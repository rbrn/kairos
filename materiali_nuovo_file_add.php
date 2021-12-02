<?php
/*error_reporting(E_ALL);
ini_set('display_errors', '1');*/
require "./include/init_sito.inc";
$cartella = $_REQUEST["cartella"];
$tipo_file = $_REQUEST["tipo"];
$dir = $_REQUEST["dir"];
$contesto = $_REQUEST["contesto"];
$nome_campo = $_REQUEST["nome_campo"];

$MAX_FILE_SIZE = $_REQUEST["MAX_FILE_SIZE"];
$file = $_FILES["file"]["tmp_name"];
$error = $_FILES["file"]["error"];

if($error > 0){
    switch ($error) {
        case 1:
            echo "the uploaded file exceeds the upload_max_filesize";

            exit;
        case 2:
            echo "The uploaded file exceeds the MAX_FILE_SIZE directive that was specified in the HTML form";
            exit;
        case 3:
            echo "The uploaded file was only partially uploaded";
            exit;
        case 4:
            echo "No file was uploaded";
            exit;
    }


}

$file_size = $_FILES["file"]["size"];
$file_name = $_FILES["file"]["name"];

$errore = "";
if ($file_size > $MAX_FILE_SIZE) {
    $errore .= "<br>$stringa[errore_max_file]";
};

if ($errore) {
    $msg = ereg_replace(" ", "%20", $errore);
    Header("Location:index.php?risorsa=msg&msg=$msg");
    exit();
};

if ($file_name) {
    $file_name = trim($file_name);
    $file_name = ereg_replace(" ", "", $file_name);
    $file_name = str_replace("'", "", $file_name);
    $file_name = str_replace("(", "", $file_name);
    $file_name = str_replace(")", "", $file_name);
    $file_name = stripslashes($file_name);
    $file_name = strtolower($file_name);
    $fullpath = $PATH_ROOT_FILE . "materiali_img/$cod_area/$dir/" . $cartella . "/" . $file_name;
    if (!copy($file, $fullpath)) {
        die("error uploading the file");
    }
};

Header("Location:index.php?risorsa=materiali_cartella&tipo=$tipo_file&cartella=$cartella&dir=$dir&contesto=$contesto&nome_campo=$nome_campo");
?>

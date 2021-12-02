<?php
$id_risorsa = $_REQUEST["id_risorsa"];
$tipo = $_REQUEST["tipo"];
$risorsa_padre = $_REQUEST["risorsa_padre"];

switch ($tipo) {
    case 200:
        $prompt = $stringa[conf_cancella_pagina];
        break;

    case 201:
        $prompt = $stringa[conf_cancella_verifica];
        break;

    case 20:
        $prompt = $stringa[conf_cancella_cartella];
        break;

    case 22:
        $prompt = $stringa[conf_cancella_cartella];
        break;

    case 202:
        $prompt = $stringa[conf_cancella_nota];
        break;
};
echo "
<p style=\"padding-top: 100px;\">&nbsp;&nbsp;<span class=testo>$prompt [<a href=repository_del_ok.php?id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$risorsa_padre>$stringa[si]</a>] [<a href=index.php?risorsa=repository_index&id_cartella=$risorsa_padre>$stringa[no]</a>]</span>
</p>
<br>";
?>

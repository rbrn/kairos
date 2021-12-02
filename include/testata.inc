<?php


use Rain\Tpl;
include "raintpl/library/Rain/Tpl.php";

$config = array(
    "tpl_dir"       => "raintpl/templates/kairos/",
    "cache_dir"     => "raintpl/cache/",
    "debug"         => true // set to false to improve the speed
);


Tpl::configure($config);
require_once('raintpl/library/Rain/Tpl/Plugin/PathReplace.php');
Rain\Tpl::registerPlugin(new Rain\Tpl\Plugin\PathReplace());
$tpl = new Tpl;

if ($nome_org) {
    $titolo_org = $nome_org;
} else {
    $titolo_org = $cod_area_base;
}


$usoeditor = false;
?>
<b></b>

<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta name="description" content="">
<meta name="author" content="">
<link rel="shortcut icon" href="bootstrap/assets/ico/favicon.png">

<title><?= $titolo_org ?>: <?= $titolo ?></title>

<!-- Bootstrap core CSS -->
<link href="bootstrap/dist/css/bootstrap.css" rel="stylesheet">
<link rel="stylesheet" href="bootstrap/font-awesome/css/font-awesome.min.css">
<!--[if IE 7]>
<link rel="stylesheet" href="bootstrap/font-awesome/css/font-awesome-ie7.min.css">
<![endif]-->
<!-- Custom styles for this template -->
<link href="bootstrap/dist/css/sticky-footer-navbar.css" rel="stylesheet">

<script src="bootstrap/assets/js/jquery.js"></script>
<script src="bootstrap/dist/js/bootstrap.min.js"></script>

<!-- HTML5 shim and Respond.js IE8 support of HTML5 elements and media queries -->
<!--[if lt IE 9]>
<script src="bootstrap/assets/js/html5shiv.js"></script>
<script src="bootstrap/assets/js/respond.min.js"></script>
<![endif]-->
<script language="JavaScript" src="script/funzioni.js"></script>
<meta name="keywords" content="<?= $parole_chiave ?>">
<meta name="description" content="<?= $descrizione ?>">

<?php
$segui_mouse = "";
if (($risorsa == "bacheca" or basename($_SERVER['PHP_SELF']) == 'materiali_browse.php') and $win_ie) {
    echo "
	<script language=\"JavaScript\" src=\"script/postit.js\"></script>
	";
    $segui_mouse = "onMouseMove=\"segui_mouse()\" onClick=\"basta_mouse()\"";
};

switch ($risorsa_superiore) {
    case "editor_contenuti":
        if ($usanuovoeditor) {
            $usoeditor = true;
            echo "
	<script type=\"text/javascript\" src=\"script/html_editor_conf.js.php\"></script>
	<script type=\"text/javascript\" src=\"html_editor/htmlarea.js.php\"></script>
	<script language=\"JavaScript\" src=\"script/html_editor.js.php?contesto=contenuti\"></script>
	<link rel=\"stylesheet\" href=\"stili/stile_html_editor.css\">
		";
        } else {
            echo "
	<script language=\"JavaScript\" src=\"script/script_editor_materiali.js\"></script>
	<link rel=\"stylesheet\" href=\"stili/stile_editor.css\">
		";
        };
        break;

    case "editor_collaborativo":
        if ($usanuovoeditor) {
            $usoeditor = true;
            echo "
	<script type=\"text/javascript\" src=\"script/html_editor_conf.js.php\"></script>
	<script type=\"text/javascript\" src=\"html_editor/htmlarea.js.php\"></script>
	<script language=\"JavaScript\" src=\"script/html_editor.js.php?contesto=contenuti_coll\"></script>

	<link rel=\"stylesheet\" href=\"stili/stile_html_editor.css\">
		";
        } else {
            echo "
	<script language=\"JavaScript\" src=\"script/script_editor_materiali_gruppo.js\"></script>
	<link rel=\"stylesheet\" href=\"stili/stile_editor.css\">
		";
        };
        break;

    case "forum":
        if ($usanuovoeditor) {
            echo "
	<script type=\"text/javascript\" src=\"script/html_editor_conf.js.php\"></script>
	<script type=\"text/javascript\" src=\"html_editor/htmlarea.js.php\"></script>
	<script language=\"JavaScript\" src=\"script/html_editor.js.php?contesto=forum\"></script>

	<link rel=\"stylesheet\" href=\"stili/stile_html_editor.css\">
	";

        } else {
            echo "
	<script language=\"JavaScript\" src=\"script/script_editor.js\"></script>
	<link rel=\"stylesheet\" href=\"stili/stile_editor.css\">
	";
        }
        break;
};

if ($risorsa == "test_item_add" or $risorsa == "test_item_mod" or $risorsa == "test_crea" or $risorsa == "test_modifica") {
    if ($usanuovoeditor) {
        $usoeditor = true;
        echo "
	<script type=\"text/javascript\" src=\"script/html_editor_conf.js.php\"></script>
	<script type=\"text/javascript\" src=\"html_editor/htmlarea.js.php\"></script>
	<script language=\"JavaScript\" src=\"script/html_editor.js.php?contesto=contenuti\"></script>

	<link rel=\"stylesheet\" href=\"stili/stile_html_editor.css\">
		";
    } else {
        echo "
	<script language=\"JavaScript\" src=\"script/script_editor_materiali.js\"></script>
	<link rel=\"stylesheet\" href=\"stili/stile_editor.css\">
		";
    };
};

if ($risorsa == "corsi_nuovo_form" or $risorsa == "corsi_mod_form" or $risorsa == "news_crea" or $risorsa == "news_mod") {
    if ($usanuovoeditor) {
        $usoeditor = true;
        echo "
	<script type=\"text/javascript\" src=\"script/html_editor_conf.js.php\"></script>
	<script type=\"text/javascript\" src=\"html_editor/htmlarea.js.php\"></script>
	<script language=\"JavaScript\" src=\"script/html_editor.js.php?contesto=news\"></script>

	<link rel=\"stylesheet\" href=\"stili/stile_html_editor.css\">
	";

    } else {
        echo "
	<script language=\"JavaScript\" src=\"script/script_editor.js\"></script>
	<link rel=\"stylesheet\" href=\"stili/stile_editor.css\">
	";
    }
};

if ($risorsa == "lo_test_item_add" or $risorsa == "lo_test_item_mod") {
    $id_cartella = id_corso($_REQUEST["risorsa_padre"]);
    $usoeditor = true;
    echo "
	<script type=\"text/javascript\" src=\"script/html_editor_lo_conf.js.php\"></script>
	<script type=\"text/javascript\" src=\"html_editor_lo/htmlarea.js.php?risorsa_padre=$id_cartella\"></script>
	<script language=\"JavaScript\" src=\"script/html_editor_lo.js.php?contesto=news\"></script>

	<link rel=\"stylesheet\" href=\"stili/stile_html_editor.css\">
	";
};

if ($risorsa == "lo_pagina_asset_edit") {
    $id_cartella = id_corso($_REQUEST["risorsa_padre"]);
    $id_pagina = $_REQUEST["id_pagina"];

    $query_lo = "SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
    $result_lo = $mysqli->query($query_lo);
    $riga_lo = $result_lo->fetch_array();

    $tipo_pagina = $riga_lo[tipo_pagina];
    $ok_editor = 0;
    if ($tipo_pagina == "1" or $tipo_pagina == "12" or $tipo_pagina == "13" or $tipo_pagina == "14" or $tipo_pagina == "15") {
        $ok_editor = 1;
        $usoeditor = true;
        echo "
	<script type=\"text/javascript\" src=\"script/html_editor_lo_conf.js.php\"></script>
	<script type=\"text/javascript\" src=\"html_editor_lo/htmlarea.js.php?risorsa_padre=$id_cartella\"></script>
	<script language=\"JavaScript\" src=\"script/html_editor_lo.js.php?contesto=lo\"></script>

	<link rel=\"stylesheet\" href=\"stili/stile_html_editor.css\">
	";
    };
};


if ($risorsa <> "forum_post" and $risorsa <> "forum_edit" and $risorsa <> "chat_stanza" and $risorsa <> "faq_new" and $risorsa <> "faq_edit" and !$usoeditor) {
    echo "<script type=\"text/javascript\" src=\"script/chat.js.php?wroot=" . $PATH_ROOT . "&serverUrl=" . $PATH_ROOT . "ajax.checkinvito.php&cod_area=$cod_area&id_utente=$kairos_cookie[0]\"></script>";
};

echo "
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
<link rel=\"stylesheet\" href=\"stili/stile_citazione.css\">
</head>
";

if ($risorsa == "index" and !$kairos_cookie[0]) {
    $focus = "window.focus();document.login.id_utente_form.focus()";
} else {
    $focus = "";
};

if (($risorsa == "forum_edit" or $risorsa == "forum_post" or $risorsa == "materiali_web_form_add" or $risorsa == "materiali_web_form_mod" or $risorsa == 'faq_new' or $risorsa == 'faq_edit' or $risorsa == "test_item_add" or $risorsa == "test_item_mod" or $risorsa == "corsi_nuovo_form" or $risorsa == "corsi_mod_form" or $risorsa == "news_crea" or $risorsa == "news_mod" or $risorsa == "materiali_gruppo_web_form_mod" or $risorsa == "materiali_gruppo_web_form_add" or $risorsa == "lo_test_item_add" or $risorsa == "lo_test_item_mod" or ($risorsa == "lo_pagina_asset_edit" and $ok_editor)) and $usanuovoeditor) {
    echo "
<body topmargin=\"0\" leftmargin=\"0\" bgcolor=\"#FFFFFF\" link=\"$colore_link\" onload=\"initEditor();carica_immagini();$focus\" $segui_mouse>";
} else {
    if (($risorsa == "forum_edit" or $risorsa == "forum_post" or  $risorsa == "materiali_web_form_add" or $risorsa == "materiali_web_form_mod"  or $risorsa == 'faq_new' or $risorsa == 'faq_edit' or $risorsa == "test_item_add" or $risorsa == "test_item_mod" or $risorsa == "corsi_nuovo_form" or $risorsa == "corsi_mod_form" or $risorsa == "news_crea" or $risorsa == "news_mod" or $risorsa == "materiali_gruppo_web_form_mod" or $risorsa == "materiali_gruppo_web_form_add" or $risorsa == "lo_test_item_add" or $risorsa == "lo_test_item_mod" or ($risorsa == "lo_pagina_asset_edit" and $ok_editor)) or (($risorsa == "test_crea" or $risorsa == "test_modifica") and $win_ie and $cod_area == 'kairos_patente')) {
        echo "
<body topmargin=\"0\" leftmargin=\"0\" bgcolor=\"#FFFFFF\" link=\"$colore_link\" onload=\"assegna_testo();carica_immagini();$focus\" $segui_mouse>";
    } else {
        echo "
<body topmargin=\"0\" leftmargin=\"0\" bgcolor=\"#FFFFFF\" link=\"$colore_link\" $segui_mouse onload=\"carica_immagini();$focus\">";
    };
};

//include_once 'testata_create.inc';
include 'testata_create_new.inc';


if ($risorsa <> "registrazione") {
    //include_once 'pagecomponents/menu_ambienti.inc';
};

if ($risorsa <> 'chat_stanza') {

    if ($id_corso_s) {
        $label = $descr_edizione_s;
        if (!$label) $label = $id_edizione_s;
        $str_edizione = ": $label ";
        $str_gruppo = "";
        $str_tutor = "";
        if ($id_gruppo_s) {
            $query_gr = "select descrizione from gruppo_utenti where id_gruppo='$id_gruppo_s' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
            $result_r = $mysqli->query($query_gr);
            $riga_gr = $result_r->fetch_array();
            $descr_gr = $riga_gr["descrizione"];
            $str_gruppo = "$stringa[gruppo]: <a class=miolink href=\"javascript:;\" title=\"$stringa[componenti_gruppo]\" onclick=\"javascript:apri_scheda('gruppo_iscritti.php?id_gruppo=$id_gruppo_s',                   'myRemoteGruppo',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowGruppo');\">$descr_gr</a>";
        };
    };

    if ($id_tutor_s) $str_tutor = "$stringa[tutor]:
<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_tutor_s',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_tutor_s</a>";

    echo "
<table width=\"100%\" border=\"0\" bgcolor=\"$colore_barra_testata\"  cellpadding=\"0\" cellspacing=\"0\" height=25>
<tr><td valign=\"middle\">

<span class=testopiccolo>";

    if ($descrizione_corso) {
        echo "
&nbsp;<img src=\"img/ico_corso.gif\" width=\"17\" height=\"15\" hspace=\"5\" align=\"absmiddle\">&nbsp;";


        $str_edizione = $descr_edizione_s;
        echo "<b>";


        if ($str_gruppo) echo " - $str_gruppo";
        if ($str_tutor) echo " - $str_tutor";

        echo "</b>&nbsp;";

        if ($ruolo == 'admin' or $ruolo == 'staff') {
            echo "[<a href=set_corso.php title=\"$stringa[annulla_setcorso_tip]\">$stringa[annulla_setcorso]</a>]";
        };
    };

    echo "</span>
</td>";

    echo "
<td align=right><span class=testopiccolo>";

    if ($win_ie and $id_utente and ($risorsa == "bacheca" or basename($_SERVER['PHP_SELF']) == 'materiali_browse.php')) {
        $script = basename($_SERVER['PHP_SELF']);
        echo "$stringa[postit]: [<a href=\"javascript:;\" onclick=\"nuovo_postit('" . $risorsa . "')\">$stringa[nuovo_p]</a>]";
        if ($risorsa <> "bacheca") {
            $query_p = "SELECT count(*) as num_postit FROM postit WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_pagina='$risorsa'";
            $result_p = $mysqli->query($query_p);
            $riga_p = $result_p->fetch_array();
            $num_postit = $riga_p[num_postit];
            if ($num_postit) {
                if ($kairos_cookie[7]) {
                    $str_m = $stringa[nascondi];
                } else {
                    $str_m = $stringa[mostra];
                };
                echo "&nbsp;[<a href=postit_mostra.php?risorsa=$risorsa&script=$script>$str_m</a>]";
            };
        };
        echo "&nbsp;|&nbsp;";
    };

    $script = $_SERVER["PHP_SELF"];
    $query_string = $_SERVER["QUERY_STRING"];
    if (!$query_string) {
        $query_string = "risorsa=$risorsa";
    };
    $query_string = str_replace("&lingua=it", "", $query_string);
    $query_string = str_replace("&lingua=uk", "", $query_string);

    echo "
</td></tr>";
    echo "</table>";


    if ($id_utente) {
//vedo se ci sono messaggi non letti per questo utente
        $query = "SELECT id_mittente FROM messaggi WHERE id_destinatario='$id_utente' AND data_lettura='0000-00-00 00:00:00' and stato=0 ORDER BY data_invio DESC";
        $result = $mysqli->query($query);
        $messaggio = $result->fetch_array();

        if ($messaggio and $risorsa <> 'messaggi') {
            echo "
	<table bgcolor=\"$colore_sfondo\" width=100%>
	<tr><td>
	<span class=testopiccolo>
	$stringa[nuovi_messaggi] <a href=index.php?risorsa=messaggi>$stringa[posta_interna]</a></span>
	</td></tr>
	</table>
	<br>";
        };
    };
};

if ($id_utente and $risorsa == "index" and $id_corso_s and $ruolo <> "staff" and $ruolo <> "admin") {
    $query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo_risorsa='3' AND (id_gruppo='' OR id_gruppo IS NULL) ORDER BY ordine";
    $result = $mysqli->query($query);
    $stringa_quest = "";
    $n_quest = 0;
    while ($result->num_rows > 0 && $riga = $result->fetch_array()) {
        $id_risorsa_test = $riga[id_risorsa];
        if ($id_risorsa_test <> "pw_azienda_2006" and $id_risorsa_test <> "pw_scuola_2006" and $id_risorsa_test <> "pw_uni_2006") {
            $query2 = "SELECT * FROM test_compilato WHERE id_test='$id_risorsa_test' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_utente='$id_utente'";
            $result2 = $mysqli->query($query2);
            if (!$result2->num_rows) {
                $query2 = "SELECT * FROM test WHERE id_test='$id_risorsa_test'";
                $result2 = $mysqli->query($query2);
                $riga2 = $result2->fetch_array();
                $stringa_quest .= "<a href=index.php?risorsa=test_compila_form&id_test=$id_risorsa_test>$riga2[titolo]</a><br>";
                $n_quest++;
            };
        };
    };

    if ($stringa_quest and $risorsa <> 'test_compila_form') {
        if ($n_quest == 1) {
            $str_m = "il seguente questionario";
        } else {
            $str_m = "i seguenti questionari";
        };
        echo "
	<br>
	<table bgcolor=\"$colore_sfondo\" width=100% cellspacing=5>
	<tr><td>
	<span class=testopiccolo>
	<b>Attenzione!</b> Per favore, dovresti compilare $str_m: <br>$stringa_quest</span>
	</td></tr>
	</table>
		<br>";
    };
};

?>

<!--  end testata -->

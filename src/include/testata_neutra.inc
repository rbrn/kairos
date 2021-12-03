<?php
require "./pagine/kairos_demo/colori.inc";
echo "
<html>
<head>
<title>$titolo</title>
<meta name=\"keywords\" content=\"$parole_chiave\">
<meta name=\"description\" content=\"$descrizione\">
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>";

switch ($risorsa_superiore) {

	case "cartella_materiali":
	echo "
	<script language=\"JavaScript\" src=\"script/script_materiali.js\"></script>";
	break;


    case "editor_contenuti":
	echo "
	<script language=\"JavaScript\" src=\"script/script_editor_materiali.js\"></script>
	<link rel=\"stylesheet\" href=\"stili/stile_editor.css\">
	";
	break;

    case "forum":
	echo "
	<script language=\"JavaScript\" src=\"script/script_editor.js\"></script>
	<link rel=\"stylesheet\" href=\"stili/stile_editor.css\">
	";
	break;
};

echo "
<link rel=\"stylesheet\" href=\"stili/kairos_demo/stile_sito.css\">
</head>
";

if ($risorsa_superiore=='cartella_materiali') {
	echo "
<body topmargin=\"0\" leftmargin=\"15\" bgcolor=\"#FFFFFF\" onLoad=\"if (document.all) beforeLoad()\">";
} else {
	if (($risorsa=="forum_edit" or $risorsa=="forum_post" or $risorsa=="materiali_web_form_mod" or $risorsa=="materiali_web_form_add") and $win_ie) {
		echo "
<body topmargin=\"0\" leftmargin=\"15\" bgcolor=\"#FFFFFF\" link=\"$colore_link\" onload=assegna_testo()>";
	} else {
		echo "
<body topmargin=\"0\" leftmargin=\"15\" bgcolor=\"#FFFFFF\" link=\"#535190\">";
	};
};	


echo "
<table width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=\"center\">
<tr><td>

<!-- MENU' AMBIENTI -->
<table width=\"100%\" border=\"0\" bgcolor=\"$colore_sfondo\"  cellpadding=\"0\" cellspacing=\"0\" height=\"20\">
<tr> 
<td align=left>"; 
require "./include/menu_ambienti.inc";		  
echo "
</td>

</tr>

<tr><td height=2 bgcolor=\"white\"><img src=\"img/trasp.gif\" width=\"1\" height=\"05\" alt=\"\" border=\"0\"></td></tr>

</table>
<!-- FINE MENU' AMBIENTI -->
";

?>

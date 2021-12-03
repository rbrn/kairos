<?php    echo "
<!-- MENU' AMBIENTI -->
<table width=\"100%\" border=\"0\" bgcolor=\"$colore_sfondo_menu\"  cellpadding=\"0\" cellspacing=\"0\" height=\"20\">";

echo "
<tr><td height=1><img src=\"img/trasp.gif\" width=\"1\" height=\"1\" alt=\"\" border=\"0\"></td></tr>";

echo "
<tr>
<td align=left>";
if (file_exists("./pagine/$cod_area/menu_ambienti.inc")) {
    require "./pagine/$cod_area/menu_ambienti.inc";
} else {
    require "./include/menu_ambienti.inc";
}


echo "</td></tr>";

if (0 and $win_ie and $id_utente and $id_utente <> 'iflabel') {
    echo "
<tr><td height=1><img src=\"img/trasp.gif\" width=\"1\" height=\"1\" alt=\"\" border=\"0\"><iframe NAME=\"check_invito\" frameborder=0 border=0 marginwidth=0 marginheight=0 width=\"0\" height=\"0\" SRC=\"check_invito.php\"></iframe></td></tr>";

} else {
    echo "
<tr><td height=1><img src=\"img/trasp.gif\" width=\"1\" height=\"1\" alt=\"\" border=\"0\"></td></tr>";
};

echo "
</table>
<!-- FINE MENU' AMBIENTI -->
";

?>

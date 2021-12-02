<?php


echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_utenti])."</b></span>
</td></tr>



<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=admin_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=admin_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";


echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
";


if ($ruolo=='admin') {
echo "
<tr><td>
<img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=registrazione_manuale>$stringa[registrazione_manuale]</a></span>
</td></tr>";

echo "
<tr><td>
<img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=utenti_cerca>$stringa[utenti_modifica]</a></span>
</td></tr>";

echo "
<tr><td>
<img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=utenti_iscrizione_cerca>$stringa[iscrizione_utenti]</a></span>
</td></tr>";

if ($cod_area=="kairos_oppla" or $cod_area=="kairos_bandaingamba" or $cod_area=="kairos_amicosole") {
echo "
<tr><td>
<img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=esporta_iscritti.php>Esporta Utenti</a></span>
</td></tr>";
}
};

echo "</table>";

echo "</td></tr></table>";
echo "</td></tr></table>";


echo "                </div>
            </div>
        </div>
    </div>
</div>";
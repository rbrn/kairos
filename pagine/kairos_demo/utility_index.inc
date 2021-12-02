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
<td valign=top width=100%><span class=testo><b>$stringa[utility]</b></span>
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
<tr><td>";

if ($ruolo=='admin') {

echo "

<tr><td>
<img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=forum_admin_index>$stringa[gestione_forum_comuni]</a></span>
</td></tr>

<tr><td>
<img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=newsletter_globale_form>$stringa[invio_newsletter_globale]</a></span>
</td></tr>

<tr><td>
<img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=materiali_sequenza_cerca&comuni=1>$stringa[sequenza_pubblicazione_comune]</a></span>
</td></tr>

<tr><td>
<img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=materiali_copia_form>$stringa[materiali_copia]</a></span>
</td></tr>


<tr><td>
<img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=configura.php target=_blank>$stringa[personalizza_interfaccia]</a></span>
</td></tr>";
};

echo "</table>";
echo "</td></tr></table>";
echo "</td></tr></table><br>";
echo "                </div>
            </div>
        </div>
    </div>
</div>";
?>

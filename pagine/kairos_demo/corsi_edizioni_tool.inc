<?php


echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

$id_edizione=$_REQUEST["id_edizione"];
$id_corso=$_REQUEST["id_corso"];

$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' ";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione;

$query="SELECT * FROM corso WHERE id_corso='$id_corso'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$descr_corso=$riga["descrizione"];

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_index><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>$descr_corso: $descr_edizione</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

echo "
<br>
\n";

echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
";

if ($ruolo=='admin') {
echo "
<tr><td>
<img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=corsi_gestione_iscrizioni_form&id_corso=$id_corso&id_edizione=$id_edizione>$stringa[gestione_iscrizioni]</a></span>
</td></tr>";
};
?>


<?php
echo "
<tr><td><img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=newsletter_form&id_corso=$id_corso&id_edizione=$id_edizione>$stringa[invio_newsletter]</a></span>
</td></tr>";
?>

<?php
//if ($ruolo=='admin') {
echo "
<tr><td><img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=materiali_sequenza_cerca&comuni=0&id_corso=$id_corso&id_edizione=$id_edizione>$stringa[sequenza_pubblicazione]</a></span>
</td></tr>";

if ($editor_lo) {
echo "
<tr><td><img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=lo_assegna_cerca&id_corso=$id_corso&id_edizione=$id_edizione>$stringa[lo_pubblicazione]</a></span>
</td></tr>";
};

//};
?>

<?php
if ($ruolo=="admin") {
echo "
<tr><td><img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=corsi_iscrizioni&id_corso=$id_corso&id_edizione=$id_edizione>$stringa[gestione_gruppi]</a></span>
</td></tr>";
};
?>

<?php 
echo "
<tr><td><img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=forum_admin_index&id_corso=$id_corso&id_edizione=$id_edizione>$stringa[gestione_forum]</a></span>
</td></tr>";
?>


<?php
if ($ruolo=='admin') {
echo "
<tr><td><img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=staff_index&id_corso=$id_corso&id_edizione=$id_edizione>$stringa[gestione_staff]</a></span>
</td></tr>";
};
?>

<?php
echo "
<tr><td><img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=stats_corso_form&id_corso=$id_corso&id_edizione=$id_edizione>$stringa[statistiche_corso]</a></span>
</td></tr>";
?>

<?php
echo "
<tr><td><img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=index.php?risorsa=report_corso_form&id_corso=$id_corso&id_edizione=$id_edizione>$stringa[report_corso]</a></span>
</td></tr>";
?>

<?php
if ($ruolo=="admin") {
echo "
<tr><td><img src=\"img/ico_quadratino.gif\" width=\"9\" height=\"9\" alt=\"\" border=\"0\">&nbsp;<span class=testopiccolo><a href=corsi_esporta_iscritti.php?id_corso=$id_corso&id_edizione=$id_edizione>$stringa[esporta_iscritti]</a></span>
</td></tr>";	
};
?>

</table>

</td></tr></table>
</td></tr></table><br>

<?php
echo "                </div>
</div>
</div>
</div>
</div>";
?>

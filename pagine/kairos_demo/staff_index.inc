<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];

$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione_s;

$query="SELECT * FROM corso WHERE id_corso='$id_corso_s'";
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
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso_s><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s><span class=testo><b>$stringa[corso]:</b> $descr_corso: $descr_edizione</span></a>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_staff])."</b></span>
</td></tr>



<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso&id_edizione=$id_edizione\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

?>


<TABLE BORDER=0 width=100%>
<tr>

<tr><td></td></tr>
<tr><td></td></tr>

<tr><td></td></tr>
<tr><td></td></tr>

<?php
echo "
<tr><td>
<span class=testo>[<a href=index.php?risorsa=staff_form&ruolo=direttore&id_corso=$id_corso_s&id_edizione=$id_edizione_s>$stringa[staff_direttore]</a>]</span>
</td></tr>";

echo "
<tr><td>
<span class=testo>[<a href=index.php?risorsa=staff_form&ruolo=coordinatore&id_corso=$id_corso_s&id_edizione=$id_edizione_s>$stringa[staff_coordinatore]</a>]</span>
</td></tr>
";


if ($id_corso_s) { 
echo "
<tr><td>
<span class=testo>[<a href=index.php?risorsa=staff_form&ruolo=docente&id_corso=$id_corso_s&id_edizione=$id_edizione_s>$stringa[staff_docente]</a>]</span>
</td></tr>
";
};



if ($id_corso_s) { 
echo "
<tr><td>
<span class=testo>[<a href=index.php?risorsa=staff_form&ruolo=esperto&id_corso=$id_corso_s&id_edizione=$id_edizione_s>$stringa[staff_esperto]</a>]</span>
</td></tr>";
};

?>

</table>

</td></tr></table>
<br>
<?php

echo "</div>
</div>
</div>
</div>
</div>";

?>
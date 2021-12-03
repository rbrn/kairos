<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";
$id_corso=$_REQUEST["id_corso"];
$id_edizione=$_REQUEST["id_edizione"];

$query="SELECT * FROM corso WHERE id_corso='$id_corso'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$descrizione_corso=$riga["descrizione"];

$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso' AND id_edizione='$id_edizione'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

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
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s><span class=testo><b>$stringa[corso]:</b> $descrizione_corso: $descr_edizione</span></a>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_gruppi])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[nuovo_gruppo])."</b></span>
</td></tr>


<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

echo "
<table border=0 width=600>
<tr>
<td>
<form action=corsi_nuovogruppo_op.php method=post name=modulo id=modulo>
<input type=hidden name=id_corso value=\"$id_corso\">
<input type=hidden name=id_edizione value=\"$id_edizione\">

<table border=0 wodth=100% cellspacing=2 cellpadding=2>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[id_gruppo]</b></span></p>
</td>
<td valign=top>
<input type=text size=20 name=id_gruppo>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[tipo]</b></span></p>
</td>
<td valign=top>
<select name=tipo_gruppo>
<option value=0>$stringa[gruppo_0]
<option value=1>$stringa[gruppo_1]
</select>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[descrizione]</b></span></p>
</td>
<td valign=top>
<input type=text size=40 name=descrizione>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[id_tutor] ($stringa[opzionale])</b></span></p>
</td>
<td valign=top>
<input type=text size=40 name=id_tutor> ";

echo "
<span class=\"testopiccolo\">
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup.php?ruolo=staff&campo=id_tutor','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup_op.php?ruolo=staff&campo=id_tutor','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["tutti"]."</a>]
</span>";

echo "
</td>
</tr>

<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=right><input type=submit value=$stringa[ok]></td></tr>
</table>

</form>


</td>
</tr>
</table>
</td>
</tr>
</table>
<br>";

?>

<?php
echo "                </div>
</div>
</div>
</div>
</div>";
?>


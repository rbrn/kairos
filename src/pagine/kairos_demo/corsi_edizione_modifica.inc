<?php
$id_edizioni=$_REQUEST["id_edizioni"];

$query = "SELECT * FROM edizioni WHERE id_edizioni='$id_edizioni' ";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

$id_corso=$riga["id_corso"];
$id_edizione=$riga["id_edizione"];
$descr_edizione=$riga["descrizione"];
$data_edizione=$riga["data_edizione"];
$durata=$riga["durata"];
$un_mis=$riga["un_mis"];
$stato=$riga["stato"];
$autoiscrizione=$riga["autoiscrizione"];

$query="SELECT * FROM corso WHERE id_corso='$id_corso'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$descrizione=$riga["descrizione"];

list($aa_oggi,$mm_oggi,$gg_oggi)=split("-",$data_edizione);

$gg="";
for ($i=1;$i<=31;$i++) {
	$giorno = "0".$i;
	$giorno=substr($giorno,-2);
	if ($i==$gg_oggi) {
		$gg .= "<option value=$giorno selected>$giorno</option>\n";
	} else {
		$gg .= "<option value=$giorno>$giorno</option>\n";
	};
};

$mm="";
for ($i=1;$i<=12;$i++) {
	$mese = "0".$i;
	$mese=substr($mese,-2);
	if ($i==$mm_oggi) {
		$mm .= "<option value=$mese selected>$mese</option>\n";
	} else {
		$mm .= "<option value=$mese>$mese</option>\n";
	};
};

$aa="";
for ($i=0;$i<=2;$i++) {
	$anno = $aa_oggi + $i;
	if ($anno==$anno_oggi) {
		$aa .= "<option value=$anno selected>$anno</option>\n";
	} else {
		$aa .= "<option value=$anno>$anno</option>\n";
	};
};

$unmis0="";
$unmis1="";
switch($un_mis) {
	case "mesi":
		$unmis0="selected";
		break;
		
	case "giorni":
		$unmis1="selected";
		break;
};

$stato0="";
$stato1="";
switch($stato) {
	case "attiva":
		$stato0="selected";
		break;
		
	case "inattiva":
		$stato1="selected";
		break;
};

$autoiscrizione_checked="";
if ($autoiscrizione) $autoiscrizione_checked="checked";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_index><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[modifica_edizione_corso])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>$descrizione ($id_corso)</b></span>
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
<form action=corsi_edizione_mod_op.php method=post>
<input type=hidden name=\"id_edizioni\" value=\"$id_edizioni\">

<table border=0 wodth=100% cellspacing=2 cellpadding=2>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[id_edizione]</b></span></p>
</td>
<td valign=top>
<span class=testo>$id_edizione</span>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[descrizione]</b></span></p>
</td>
<td valign=top>
<input type=\"text\" size=40 name=\"descrizione\" value=\"$descr_edizione\">
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[data_inizio]</b></span></p>
</td>
<td valign=top>
<select name=gg>
$gg
</select>
/
<select name=mm>
$mm
</select>
/
<select name=aa>
$aa
</select>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[durata]</b></span></p>
</td>
<td valign=top>
<input type=\"text\" size=05 name=\"durata\" value=\"$durata\"> <select name=un_mis>
<option value=\"mesi\" $unmis0>$stringa[mesi]</option>
<option value=\"giorni\" $unmis1>$stringa[giorni]</option>
</select>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[status]</b></span></p>
</td>
<td valign=top>
<select name=\"stato\">
<option value=\"attiva\" $stato0>$stringa[attiva]</option>
<option value=\"inattiva\" $stato1>$stringa[inattiva]</option></select>
</td>
</tr>

<tr>
<td valign=top align=right>
<input type=checkbox name=\"autoiscrizione\" $autoiscrizione_checked>
</td>
<td>
<span class=testo>$stringa[autoiscrizione]</span>
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
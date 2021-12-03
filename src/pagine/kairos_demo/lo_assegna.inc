<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];
$titolo_cerca=trim($_REQUEST["titolo_cerca"]);
$id_autore_cerca=trim($_REQUEST["id_autore_cerca"]);
$lo_tipo_lom_cerca=trim($_REQUEST["lo_tipo_lom_cerca"]);
$materia_cerca=trim($_REQUEST["materia_cerca"]);
$id_gruppo_cerca=$_REQUEST["id_gruppo_cerca"];

$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione_s;

$query="SELECT * FROM corso WHERE id_corso='$id_corso_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$descr_corso=$riga["descrizione"];

$where_s="";
if ($titolo_cerca) {
	$where_s.=" AND titolo like '$titolo_cerca%' ";
};
	
if ($id_autore_cerca) {
	$where_s.=" AND id_autore = '$id_autore_cerca'";
};

$query = "SELECT * FROM risorse_materiali WHERE (risorsa_padre='root') AND (tipo=20) $where_s ORDER BY posizione,id_risorsa";
$result=$mysqli->query($query);

$materiali_attesa="";
while ($risorsa = $result->fetch_array() ) {
	$id_risorsa = $risorsa["id_risorsa"];
	$id_gruppo = $risorsa["id_gruppo"];
	$titolo=htmlentities($risorsa["titolo"]);
	$tipo=$risorsa["tipo"];
	
	$prendi=true;
	
	$where_s="id_lo='$id_risorsa'";
	if ($lo_tipo_lom_cerca) {
		if ($where_s) $where_s.=" AND ";
		$where_s.="lo_tipo_lom like '$lo_tipo_lom_cerca%'";
	};
	
	if ($materia_cerca) {
		if ($where_s) $where_s.=" AND ";
		$where_s.="materia like '$materia_cerca%'";
	};
	
	if ($where_s) {
		$query2="SELECT id_lo FROM lo WHERE $where_s LIMIT 1";
		$result2=$mysqli->query($query2);
		if (!$result2->num_rows) $prendi=false;
	};
	
	if ($prendi) {
		$query2="SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_risorsa' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'  AND (id_gruppo='$id_gruppo_cerca') ";
		$result2=$mysqli->query($query2);
		if ($result2->num_rows) $prendi=false;
	};
	
	if ($prendi) $materiali_attesa .= "<option value=\"$id_risorsa\">$titolo</option>";
	
};


//PUBBLICATI

$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'  AND (id_gruppo='$id_gruppo_cerca') AND tipo_risorsa='20' ORDER BY ordine";


$result=$mysqli->query($query);

$materiali_pubblicati="";
while ($risorsa = $result->fetch_array() ) {
	$id_risorsa = $risorsa["id_risorsa"];
	$query2 = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
	$result2=$mysqli->query($query2);
	$riga2=$result2->fetch_array();
	$titolo=htmlentities($riga2["titolo"]);
	$materiali_pubblicati .= "<option value=\"$id_risorsa\">$titolo</option>";
};

$seq_pubb=$stringa[lo_pubblicazione];
$mat_not_pubb=$stringa[lo_non_pubblicati];
$mat_pubb=$stringa[lo_pubblicati];


$indietro="index.php?risorsa=lo_assegna_cerca&id_corso=$id_corso_s&id_edizione=$id_edizione_s";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>";


echo "
<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_index><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso_s><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s><span class=testo><b>$stringa[corso]:</b> $descr_corso: $descr_edizione</span></a>";
if ($id_gruppo_cerca)  echo "<br><br><span class=testo><b>GRUPPO:</b> $id_gruppo_cerca</span>";
echo "
</td></tr>";


echo "
<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($seq_pubb)."</b></span>
</td></tr>";



echo "
<tr>
<td valign=top width=100%>
<a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

echo "
<form action=lo_assegna_op.php method=post>
<input type=hidden name=id_corso value=\"$id_corso_s\">
<input type=hidden name=id_edizione value=\"$id_edizione_s\">
<input type=hidden name=titolo_cerca value=\"$titolo_cerca\">
<input type=hidden name=id_autore_cerca value=\"$id_autore_cerca\">
<input type=hidden name=lo_tipo_lom_cerca value=\"$lo_tipo_lom_cerca\">
<input type=hidden name=materia_cerca value=\"$materia_cerca\">
<input type=hidden name=id_gruppo_cerca value=\"$id_gruppo_cerca\">

<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"550\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">";

echo "<tr bgcolor=\"$colore_scuro\">";
echo "<td><span class=testonegativo><b>$mat_not_pubb</b></span></td><td>&nbsp;</td>
<td><span class=testonegativo><b>$mat_pubb</b></span></td>
</tr>";

echo "
<tr bgcolor=\"$colore_sfondo\">
<td valign=top>
<select multiple name=materiali_attesa[] size=10>
$materiali_attesa
</select>
</td>
<td valign=top width=10 valign=top>
<input type=submit name=aggiungi value=\">>\">
<br>
<input type=submit name=rimuovi value=\"<<\">
</td>
<td  valign=top>
<select multiple name=materiali_pubblicati[] size=10>
$materiali_pubblicati
</select>
</td>
</tr>";
echo "</table>";

echo "</td></tr></table>
</form>";

echo "</td></tr></table><br>";
?>

<?php
echo "                </div>
</div>
</div>
</div>
</div>";
?>

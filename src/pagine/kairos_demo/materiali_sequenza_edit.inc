<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

$comuni=$_REQUEST["comuni"];
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];

$id_gruppo_cerca=$_REQUEST["id_gruppo_cerca"];

$titolo_cerca=$_REQUEST["titolo_cerca"];
$id_autore_cerca=$_REQUEST["id_autore_cerca"];

if (!$comuni) {
$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione_s;

$query="SELECT * FROM corso WHERE id_corso='$id_corso_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$descr_corso=$riga["descrizione"];
};

$condizione="";
if ($titolo_cerca) {
	if ($condizione) $condizione.=" AND ";
	 $condizione.=" titolo LIKE '$titolo_cerca%' ";
	
}

if ($id_autore_cerca) {
	if ($condizione) $condizione.=" AND ";
	$condizione.=" id_autore = '$id_autore_cerca' ";
};


if ($condizione) $condizione.=" AND ";

$query = "SELECT * FROM risorse_materiali WHERE  $condizione (risorsa_padre='root') AND (tipo<>3) ORDER BY posizione,id_risorsa";
$result=$mysqli->query($query);


$materiali_attesa="";
while ($risorsa = $result->fetch_array() ) {
	$id_risorsa = $risorsa["id_risorsa"];
	$id_gruppo = $risorsa["id_gruppo"];
	$titolo=$risorsa["titolo"];
	$tipo=$risorsa["tipo"];
	
	if ($comuni=='1') {
		 $query2="SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_risorsa' AND (id_corso='' OR id_corso IS NULL)";
	} else {	
		$query2="SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_risorsa' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='$id_gruppo_cerca') ";
	};
	$result2=$mysqli->query($query2);

	if (!$result2->num_rows) {
		
 		switch ($tipo) {
			case 0:
				$valore="web-".$id_risorsa;
				$materiali_attesa .= "
				<option value=$valore>$stringa[web]: $titolo</option>";
				break;
				
			case 4:
				$valore="link-".$id_risorsa;
				
				$query3 = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
			$result3=$mysqli->query($query3);
			$riga3=$result3->fetch_array();
			$titolo=$riga3["titolo"];
			
				$materiali_attesa .= "
				<option value=$valore>$stringa[link]: $titolo</option>";
				break;	

			case 1:
				$valore="file-".$id_risorsa;
				$materiali_attesa .= "
				<option value=$valore>$stringa[file]: $titolo</option>";
				break;

			case 2:
				$id_risorsa0=foglia($id_risorsa);
				//if ($id_risorsa0 AND $id_risorsa0<>$id_risorsa) {
					$valore="cartella-".$id_risorsa;
					$materiali_attesa .= "
					<option value=$valore>$stringa[cartella]: $titolo</option>";
				//};
				break;
		
		};
	};
};

//TEST
$condizione="";
if ($titolo_cerca) {
	 $condizione.=" WHERE titolo LIKE '$titolo_cerca%' ";
	
}
$query = "SELECT * FROM test $condizione ORDER BY id_test";
$result=$mysqli->query($query);

while ($risorsa = $result->fetch_array() ) {
	$id_risorsa = $risorsa["id_test"];
	$titolo=$risorsa["titolo"];
	 
	 
	if ($comuni=='1') {
		 $query2="SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_risorsa' AND id_corso=''";
	} else {	
		$query2="SELECT id_risorsa FROM materiali_sequenza WHERE id_risorsa='$id_risorsa' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='$id_gruppo_cerca')";
	};
	
	$result2=$mysqli->query($query2);
	
	if (!$result2->num_rows) {
		$valore="test-".$id_risorsa;
		$materiali_attesa .= "
		<option value=$valore>$stringa[test]: $titolo</option>";
	};
};


//PUBBLICATI

if ($comuni=='1') {
	$query = "SELECT * FROM materiali_sequenza WHERE id_corso='' ORDER BY ordine";
} else {
	$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='$id_gruppo_cerca') ORDER BY ordine";
};

$result=$mysqli->query($query);

$materiali_pubblicati="";
while ($risorsa = $result->fetch_array() ) {
	$id_risorsa = $risorsa["id_risorsa"];
	$tipo_risorsa = $risorsa["tipo_risorsa"];
	
	switch ($tipo_risorsa) {
		case 0:
			$query2 = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
			$result2=$mysqli->query($query2);
			$riga2=$result2->fetch_array();
			$titolo=$riga2["titolo"];
			
			$valore="web-".$id_risorsa;
			$materiali_pubblicati .= "
			<option value=$valore>$stringa[web]: $titolo</option>";
			break;

		case 4:
			$query2 = "SELECT id_gruppo FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
			$result2=$mysqli->query($query2);
			$riga2=$result2->fetch_array();
			
			$id_gruppo=$riga2["id_gruppo"];
			
			$query2 = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
			$result2=$mysqli->query($query2);
			$riga2=$result2->fetch_array();
			$titolo=$riga2["titolo"];
			
			$valore="link-".$id_risorsa;
			$materiali_pubblicati .= "
			<option value=$valore>$stringa[link]: $titolo</option>";
			break;
				
		case 1:
			$query2 = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
			$result2=$mysqli->query($query2);
			$riga2=$result2->fetch_array();
			$titolo=$riga2["titolo"];
			
			$valore="file-".$id_risorsa;
			$materiali_pubblicati .= "
			<option value=$valore>$stringa[file]: $titolo (".stringa_filesize($file_size).")</option>";
			break;

		case 2:
			$query2 = "SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
			$result2=$mysqli->query($query2);
			$riga2=$result2->fetch_array();
			$titolo=$riga2["titolo"];
			
			$valore="cartella-".$id_risorsa;
			$materiali_pubblicati .= "
			<option value=$valore>$stringa[cartella]: $titolo</option>";
			break;
			
		case 3:
			$query2 = "SELECT titolo FROM test WHERE id_test='$id_risorsa'";
			$result2=$mysqli->query($query2);
			$riga2=$result2->fetch_array();
			$titolo=$riga2["titolo"];
			
			$valore="test-".$id_risorsa;
			$materiali_pubblicati .= "
			<option value=$valore>$stringa[test]: $titolo</option>";
			break;

	};
};

if ($comuni=='1') {
	$seq_pubb=$stringa[sequenza_pubblicazione_comune];
	$mat_not_pubb=$stringa[materiali_non_pubblicati_comune];
	$mat_pubb=$stringa[materiali_pubblicati_comune];
} else {
	$seq_pubb=$stringa[sequenza_pubblicazione];
	$mat_not_pubb=$stringa[materiali_non_pubblicati];
	$mat_pubb=$stringa[materiali_pubblicati];
};

if (!$comuni) {
 $indietro="index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s";
} else {
	 $indietro="index.php?risorsa=utility_index";
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>";

if (!$comuni) {
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

} else {
	echo "
	<tr>
<td valign=top width=100%><span class=testo><b>".$stringa[utility]."</b></span>
</td></tr>";
};

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
<table border=0 width=90%>
\n";

echo "
<tr>
<td>
<form action=materiali_sequenza_edit_op.php method=post>
<input type=\"hidden\" name=\"comuni\" value=\"$comuni\">
<input type=hidden name=id_corso value=\"$id_corso_s\">
<input type=hidden name=id_edizione value=\"$id_edizione_s\">
<input type=hidden name=titolo_cerca value=\"$titolo_cerca\">
<input type=hidden name=id_autore_cerca value=\"$id_autore_cerca\">
<input type=hidden name=id_gruppo_cerca value=\"$id_gruppo_cerca\">

<table border=0>

<tr>
<td width=300 valign=top>
<span class=testopiccolo>
$mat_not_pubb</span>
</td>
<td width=10>&nbsp;</td>
<td width=300 valign=top>
<span class=testopiccolo>$mat_pubb</span>
</td>
</tr>

<tr>
<td width=300 valign=top>
<select multiple name=materiali_attesa[] size=10>
$materiali_attesa
</select>
</td>
<td valign=top width=10 valign=top>
<input type=submit name=aggiungi value=\">>\">
<br>
<input type=submit name=rimuovi value=\"<<\">
</td>
<td width=300 valign=top>
<select multiple name=materiali_pubblicati[] size=10>
$materiali_pubblicati
</select>
</td>
</tr>
</table>


</form>
</td>
</tr>
\n";
echo "</table>";

echo "</td></tr></table><br>";
?>

<?php
echo "                </div>
</div>
</div>
</div>
</div>";
?>

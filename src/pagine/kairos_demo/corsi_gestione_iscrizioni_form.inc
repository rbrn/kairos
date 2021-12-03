<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];

if ($id_corso_s) {
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

$elenco_corsi="<option value=\"qualunque\">$stringa[qualunque]";
$query="SELECT * FROM edizioni WHERE stato='attiva' ORDER BY id_corso,id_edizione DESC";
$result=$mysqli->query($query);
	

while ($riga=$result->fetch_array()) {
$id_corso=$riga["id_corso"];
$id_edizione=$riga["id_edizione"];
$elenco_corsi .= "<option value=\"$id_corso $id_edizione\">$id_corso ($id_edizione)";
};

$data = getdate();
$gg_oggi=$data["mday"];
$mm_oggi=$data["mon"];
$aa_oggi=$data["year"];

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

$da_aa="";
for ($i=0;$i<=2;$i++) {
	$anno = $aa_oggi - $i;
	if ($i==2) {
		$da_aa .= "<option value=$anno selected>$anno</option>\n";
	} else {
		$da_aa .= "<option value=$anno>$anno</option>\n";
	};
};


$a_aa="";
for ($i=0;$i<=2;$i++) {
	$anno = $aa_oggi - $i;
	if ($anno==$anno_oggi) {
		$a_aa .= "<option value=$anno selected>$anno</option>\n";
	} else {
		$a_aa .= "<option value=$anno>$anno</option>\n";
	};
};


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
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_iscrizioni])."</b></span>
</td></tr>




<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

?>

<form action="index.php" method="GET">
<input type="hidden" name="risorsa" value="corsi_gestione_iscrizioni_lista">
<input type="hidden" name="id_corso" value="<?php echo($id_corso_s);?>">
<input type="hidden" name="id_edizione" value="<?php echo($id_edizione_s);?>">
<table border="0">
				
		<tr>
            <td align="right"><span class=testo><b><?php echo($stringa[identificativo]);?></b></span></td>
            <td><input type="text" size="10" maxlength=100 name="id_utente_cerca"></td>
        </tr>

	<tr>
	<td colspan=2>
	</td>
	</tr>		
        <tr>
            <td align="right"><span class=testo><b><?php echo($stringa[nome]);?></b></span></td>
            <td><span class=testo><input type="text" size="35" maxlength=100 name="nome"></span></td>
        </tr>
        <tr>
            <td align="right"><span class=testo><b><?php echo($stringa[cognome]);?></b></span></td>
            <td><input type="text" size="35" maxlength=100 name="cognome"></td>
        </tr>
		
		<tr>
            <td align="right"><span class=testo><b><?php echo($stringa[data_registrazione]);?>:</b></span></td>
            <td>
			<span class=testo><b><?php echo($stringa[dal]);?>:</b>
			<select name="da_reg_gg">
			<?php echo($gg);?>
			</select>
			/
			<select name="da_reg_mm">
			<?php echo($mm);?>
			</select>
			/<select name="da_reg_aa">
			<?php echo($da_aa);?>
			</select>
			<b><?php echo($stringa[al]);?>:</b>
			<select name="a_reg_gg">
			<?php echo($gg);?>
			</select>
			/
			<select name="a_reg_mm">
			<?php echo($mm);?>
			</select>
			/
			<select name="a_reg_aa">
			<?php echo($a_aa);?>
			</select>
			
			</span>
			
			</td>
        </tr>
		
		<tr>
		<td align=left colspan=2><span class=testo>
		<?php echo "$stringa[cerca_registrati]: <b>$descr_corso - $descr_edizione</b>";?>
		</span>
		<input type="submit" name="cerca_reg" value="<?php echo($stringa[cerca]);?>">
		</td>
		</tr>
		
		<tr>
		<td align=left colspan=2>
		<span class=testo>
		<?php echo($stringa[cerca_iscritti]);?>
		</span>
		<input type="submit" name="cerca_iscr" value="<?php echo($stringa[cerca]);?>">
		</td>
		</tr>
		
    </table>
	
</form>
</td></tr></table>
<br>
<?php

echo "</div>
</div>
</div>
</div>
</div>";

?>
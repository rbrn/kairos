<?php

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

$aa="";
for ($i=0;$i<=2;$i++) {
	$anno = $aa_oggi - $i;
	if ($anno==$anno_oggi) {
		$aa .= "<option value=$anno selected>$anno</option>\n";
	} else {
		$aa .= "<option value=$anno>$anno</option>\n";
	};
};

?>
<p><span class=titolopagina><?php echo($stringa[gestione_iscrizioni]);?></span>
<br>
<?php 
echo "<span class=sottotitolopagina>$descr_corso: $descr_edizione</span>";
?>
</p>
<hr size=1>
<span class=testo>[<a href=index.php?risorsa=corsi_index><?php echo($stringa[gestione_corsi]);?></a>]</span> 
<hr size=1>
<form action="index.php" method="GET">
<input type="hidden" name="risorsa" value="corsi_gestione_iscrizioni_lista">
<table border="0">
		<tr>
		<td align=left colspan=2><span class=testo>
		<b><?php echo($stringa[cerca_registrati]);?></b>
		</span>
		</td>
		</tr>
		
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
			<?php echo($aa);?>
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
			<?php echo($aa);?>
			</select>
			
			</span>
			<input type="submit" name="cerca_reg" value="<?php echo($stringa[cerca]);?>">
			</td>
        </tr>
		
		<tr>
		<td align=left colspan=2>
		<hr size=1>
		<span class=testo>
		<b><?php echo($stringa[cerca_iscritti]);?></b>
		</span>
		</td>
		</tr>
		
		<tr>
            <td align="right"><span class=testo><b><?php echo($stringa[corso]);?>:</b></span></td>
            <td>
			<select name="id_corso_edizione_form">
			<?php echo($elenco_corsi) ?>
			</select>
			</td>
		<tr>
			<td><span class=testo><b<?php echo($stringa[data_iscrizione]);?>:</b></span></td>
			<td>
			<span class=testo><b><?php echo($stringa[dal]);?>:</b>
			<select name="da_iscr_gg">
			<?php echo($gg);?>
			</select>
			/
			<select name="da_iscr_mm">
			<?php echo($mm);?>
			</select>
			/<select name="da_iscr_aa">
			<?php echo($aa);?>
			</select>
			<b><?php echo($stringa[al]);?>:</b>
			<select name="a_iscr_gg">
			<?php echo($gg);?>
			</select>
			/
			<select name="a_iscr_mm">
			<?php echo($mm);?>
			</select>
			/
			<select name="a_iscr_aa">
			<?php echo($aa);?>
			</select>
			</span>
			<input type="submit" name="cerca_iscr" value="<?php echo($stringa[cerca]);?>">
			</td>
		</tr>
	
    </table>
	
</form>
<br>

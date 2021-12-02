<TABLE BORDER=0 ALIGN=CENTER width=600>
<tr>
<td>
 
<?php

// parametro di richiamo: id_sondaggio


echo "<p><span class=sottotitolopagina>Questionario online:</span><br>";
$query = "SELECT titolo FROM sondaggio WHERE id_sondaggio='$id_sondaggio'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

echo "<span class=titolopagina>".$riga["titolo"]."</span></p><br><hr size=1>";

//calcolo quante sono le voci del sondaggio
$query = "SELECT count(*) as num_voci FROM item_sondaggio WHERE id_sondaggio='$id_sondaggio'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

$num_voci=$riga["num_voci"];

// estraggo le voci del sondaggio e le sottopongo

//controllo se il questionario prevede file allegati

$query= "SELECT id_item_sondaggio FROM item_sondaggio WHERE id_sondaggio='$id_sondaggio' AND tipo_item='2'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

if (!$riga) {
	echo "<form action=sondaggio_put.php method=post>\n";
} else {
	echo "
	<FORM action=sondaggio_put.php encType=multipart/form-data method=post>\n
	<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>\n";
};

echo "<input type=hidden name=id_utente value=$id_utente>\n";
echo "<input type=hidden name=id_sondaggio value=$id_sondaggio>\n";
echo "<input type=hidden name=num_voci value=$num_voci>\n";

$query = "SELECT * FROM item_sondaggio WHERE id_sondaggio='$id_sondaggio' ORDER BY num_item";
$result=$mysqli->query($query);
$item = $result->fetch_array();
$voce=1;

while ($item) {
	$id_item_sondaggio=$item["id_item_sondaggio"];
	$num_item = $item["num_item"];
	$tipo_item = $item["tipo_item"];
	$domanda = $item["domanda"];
	$risp1 = $item["risp1"];
	$risp2 = $item["risp2"];
	$risp3 = $item["risp3"];
	$risp4 = $item["risp4"];
	$risp5 = $item["risp5"];
	$risp6 = $item["risp6"];
	$risp7 = $item["risp7"];
	$risp8 = $item["risp8"];
	$risp_altro = $item["risp_altro"];
	
	echo "<input type=hidden name=tipo_voce_$voce value=$tipo_item>\n";
	echo "<input type=hidden name=id_item_sondaggio_voce_$voce value=$id_item_sondaggio>\n";
	echo "<input type=hidden name=risp_altro_voce_$voce value=$risp_altro>\n";

	echo "<p><span class=testo><strong>$voce. ";
	$domanda = ereg_replace("\n","<br>",$domanda);
	echo parse_link($domanda);
	echo "</strong></span></p>\n";

	switch($tipo_item) {
		case "0":
			// domanda aperta
			echo "<textarea name=risposta_aperta_$voce rows=8 cols=60></textarea>\n";
			break;
		case "1":
			// domanda chiusa
			for ($j=1; $j<=8; $j++) {
				$risposta = "risp".$j;
		
				if (${$risposta}) {
					$radio = "risp_voce_".$voce;
					echo "<input type=radio name=$radio value=$j><span class=testo>${$risposta}</span><br>\n";
					};
			};
	
			if ($risp_altro == 'on') {
				$radio = "risp_voce_".$voce;
				echo "<input type=radio name=$radio value=$j><span class=testo>Altro, specificare:";
				echo "<input type=text name=risposta_altro_voce_$voce maxLength=250 size=50></span>";
			};
			break;
			
		case "2":
			//file allegato
			echo "
			<span class=testo>File allegato (max. 5MB)</span>:<INPUT name=nome_file_voce_$voce type=file>";
			break;
	};
	$item = $result->fetch_array();
	$voce++;	
}; //fine del while delle voci

echo "<BR><P align=center><INPUT type=submit value=INVIA></P>";
echo "</FORM>";
?>
		
</td></tr>
</table>

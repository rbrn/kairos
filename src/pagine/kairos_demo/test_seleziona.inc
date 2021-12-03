<?php
$id_test=$_REQUEST["id_test"];
$query = "SELECT * FROM test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$test = $result->fetch_array();

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>SELEZIONA RISPOSTE TEST</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<span class=testo><b>".$test["titolo"]." ($id_test)</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=test_risultati&id_test=$id_test\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=test_risultati&id_test=$id_test\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

?>

<form action="index.php" method="post">
<input type="hidden" name="risorsa" value="test_seleziona_lista">
<input type="hidden" name="id_test" value="<?php echo($id_test) ?>">
<table border="0">

    	
<?php
	
$query = "SELECT * FROM item_test WHERE id_test='$id_test' ORDER BY num_item";
$result=$mysqli->query($query);

while ($item = $result->fetch_array()) {
	$id_item_test=$item["id_item_test"];
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
	
	if ($tipo_item=="1" or $tipo_item=="3") {
		$elenco = "<option value=\"*\">*</option>";
		echo "
		<tr>
            <td align=\"right\"><span class=\"testopiccolo\">$domanda</span></td>
            <td><SELECT name=d$id_item_test size=1>"; 
		
		for ($j=1; $j<=8; $j++) {
			$risposta = "risp".$j;
			
			if (${$risposta}) {
				$elenco .= "<option value=$j>${$risposta}</option>";
			};
		};
		
		if ($risp_altro == "on") {
			$elenco .= "<option value=altro>altro</option>";
		};
		
		echo "
			$elenco					
			</select></td>
        </tr>";
		
	};

};

			
	?> 
		

    </table>


<br>
    <p align="center"><input type="submit"  value="Seleziona utenti"></p>
	
</form>
<br>

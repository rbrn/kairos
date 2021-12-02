<?php
$id_test=$_REQUEST["id_test"];
$query = "SELECT * FROM test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$test = $result->fetch_array();
$tipo_test=$test["tipo_test"];
$num_domande=$test["num_domande"];
list ($data,$ora) = split(" ",$test["data_prima"]);
list ($aa,$mm,$gg) = split("-",$data);

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[risultati_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<span class=testo><b>".$test["titolo"]." ($id_test)</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=test_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=test_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

?>
<?php

echo "<span class=testopiccolo><b>$stringa[data_prima]:</b> $gg/$mm/$aa $ora <br></span>\n";

list ($data,$ora) = split(" ",$test["data_ultima"]);
list ($aa,$mm,$gg) = split("-",$data);
echo "<span class=testopiccolo><b>$stringa[data_ultima]:</b> $gg/$mm/$aa $ora <br></span>\n";
if ($ruolo=="staff" or $ruolo=="admin") {
printf( "<span class=testopiccolo><b>$stringa[tot_compilazioni]:</b> <a href=index.php?risorsa=test_risultati_elenco&id_test=%s&id_start=%s>%s</a></span> <br><br>\n",$id_test,0,$test["tot_prog"]);
} else {
printf( "<span class=testopiccolo><b>$stringa[tot_compilazioni]:</b> %s</span> <br><br>\n",$test["tot_prog"]);
};
echo "<span class=testopiccolo>[<a href=index.php?risorsa=test_seleziona&id_test=$id_test>Seleziona utenti in base alle risposte date</a>]</span><br><br>";
$tot_c = $test["tot_prog"];
// estraggo le voci del test mostro i totali

if (($tot_c > 0 and $tipo_test<>0) or ($tot_c > 0 and $tipo_test==0 and !$num_domande)) {
$query = "SELECT * FROM item_test WHERE id_test='$id_test' ORDER BY num_item";
$result=$mysqli->query($query);
$item = $result->fetch_array();
$voce=1;

while ($item) {
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
	$tot_risp1 = $item["tot_risp1"];
	$tot_risp2 = $item["tot_risp2"];
	$tot_risp3 = $item["tot_risp3"];
	$tot_risp4 = $item["tot_risp4"];
	$tot_risp5 = $item["tot_risp5"];
	$tot_risp6 = $item["tot_risp6"];
	$tot_risp7 = $item["tot_risp7"];
	$tot_risp8 = $item["tot_risp8"];
	$tot_risp_a = $item["tot_risp_a"];
	$tot_no_risp = $item["tot_no_risp"];
	
	$tot_no_risp=$tot_c-($tot_risp1+$tot_risp2+$tot_risp3+$tot_risp4+$tot_risp5+$tot_risp6+$tot_risp7+$tot_risp8+$tot_risp_a);

	if ($tot_no_risp<0) $tot_no_risp=0;
	
	
	echo "<p><span class=testo><b>$voce. ";
	$domanda = ereg_replace("\n","<br>",$domanda);
	echo ($domanda);
	echo "</b></span></p>\n";

	switch ($tipo_item) {
	
	case "0":
		// domanda aperta
		echo "<table border=0 cellspacing=2 width=400>\n";
		echo "<tr><td>\n";
		printf( "<span class=testopiccolo><a href=index.php?risorsa=test_risultati_dettaglio&id_item_test=%s&id_start=0&voce=risposta_aperta>%s</a></span>\n",$id_item_test,$stringa[risposte_aperte]);
		echo "</td></tr>\n";
		break;
		
	case "1":
		// domanda chiusa
		echo "<table border=0 cellspacing=2 width=400>\n";
		echo "<tr><td width=300>&nbsp;</td><td width=50><span class=testopiccolo><b>$stringa[num]</b></span></td><td width=50><span class=testopiccolo><b>%</b></span></td></tr>\n";
		for ($j=1; $j<=8; $j++) {
			$risposta = "risp".$j;
			if (${$risposta}) {
				$radio = "risp_voce_".$voce;
				$valore = "tot_risp".$j;
				$perc = round( (${$valore}/($tot_c)*100));
				printf("<tr><td width=300><li><span class=testopiccolo>${$risposta}</span></td><td width=50><span class=testopiccolo>%s</span></td><td width=50><span class=testopiccolo>%s</span></td></tr>\n",${$valore},$perc);
			};
		};
	
		if ($risp_altro) {
			$perc = round( ($tot_risp_a/($tot_c)*100));
			printf("<tr><td width=300><li><span class=testopiccolo><a href=index.php?risorsa=test_risultati_dettaglio&id_item_test=%s&id_start=0&voce=risp_altro>%s</a></span></td><td width=50><span class=testopiccolo>%s</span></td><td width=50><span class=testopiccolo>%s</span></td></tr>\n",$id_item_test,$stringa[altro],$tot_risp_a,$perc);
		};

		$perc = round(($tot_no_risp/$tot_c*100));
		printf("<tr><td width=300><li><span class=testopiccolo>%s</span></td><td width=50><span class=testopiccolo>%s</span></td><td width=50><span class=testopiccolo>%s</span></td></tr>\n",$stringa[non_risposto],$tot_no_risp,$perc);
		break;
	
	case "3":
		// domanda chiusa risposta multipla
		echo "<table border=0 cellspacing=2 width=400>\n";
		echo "<tr><td width=300>&nbsp;</td><td width=50><span class=testopiccolo><b>$stringa[num]</b></span></td><td width=50><span class=testopiccolo><b>%</b></span></td></tr>\n";
		for ($j=1; $j<=8; $j++) {
			$risposta = "risp".$j;
			if (${$risposta}) {
				$radio = "risp_voce_".$voce;
				$valore = "tot_risp".$j;
				$perc = round( (${$valore}/($tot_c)*100));
				printf("<tr><td width=300><li><span class=testopiccolo>${$risposta}</span></td><td width=50><span class=testopiccolo>%s</span></td><td width=50><span class=testopiccolo>%s</span></td></tr>\n",${$valore},$perc);
			};
		};
		
		if ($risp_altro) {
			$perc = round( ($tot_risp_a/($tot_c)*100));
			printf("<tr><td width=300><li><span class=testopiccolo><a href=index.php?risorsa=test_risultati_dettaglio&id_item_test=%s&id_start=0&voce=risp_altro>%s</a></span></td><td width=50><span class=testopiccolo>%s</span></td><td width=50><span class=testopiccolo>%s</span></td></tr>\n",$id_item_test,$stringa[altro],$tot_risp_a,$perc);
		};
		
		$perc = round(($tot_no_risp/$tot_c*100));
		printf("<tr><td width=300><li><span class=testopiccolo>%s</span></td><td width=50><span class=testopiccolo>%s</span></td><td width=50><span class=testopiccolo>%s</span></td></tr>\n",$stringa[non_risposto],$tot_no_risp,$perc);
		break;
		
	case "2":
		// domanda file allegato
		echo "<table border=0 cellspacing=2 width=400>\n";
		echo "<tr><td>\n";
		printf( "<span class=testopiccolo><a href=index.php?risorsa=test_risultati_dettaglio&id_item_test=%s&id_start=0&voce=file_allegato>%s</a></span>\n",$id_item_test,$stringa[file_allegato]);
		echo "</td></tr>\n";
		break;		
	};
	echo "</table>\n";
	$item = $result->fetch_array();
	$voce++;
}; //fine del while delle voci

};
echo "<br>";
?>

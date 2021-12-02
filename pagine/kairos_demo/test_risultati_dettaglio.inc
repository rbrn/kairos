<?php
$id_item_test=$_REQUEST["id_item_test"];
$id_start=$_REQUEST["id_start"];
$voce=$_REQUEST["voce"];
$valore_voce=$_REQUEST["valore"];

$query = "SELECT * FROM item_test WHERE id_item_test='$id_item_test'";
$result=$mysqli->query($query);
$item_test = $result->fetch_array();
$id_test = $item_test["id_test"];
echo "<table border=0 cellpadding=5 cellspacing=5><tr><td>";
echo "<p><span class=testo><B>$stringa[dettaglio_risposta]:</B><br>\n";

$domanda = $item_test["domanda"];

if ($voce=="risp_chiusa") {
	$indice="risp".$valore_voce;
	$risposta=$item_test[$indice];
};

/*
$domanda = ereg_replace("\n","<br>",$item_test["domanda"]);
echo parse_link($domanda)."</span><br>\n";
*/
echo "$domanda<br><br><b>$risposta</b></span><br>\n";

echo "<hr size=1>\n";	
printf( "<span class=testopiccolo>[<a href=index.php?risorsa=test_risultati&id_test=%s>%s</a>]</span> ",$id_test,$stringa[indietro]);
echo "<hr size=1>\n";	

if ($voce=="risp_chiusa") {
$query = "SELECT * FROM item_test_compilato WHERE  id_test='$id_test' AND id_item_test='$id_item_test' AND risp_chiusa='$valore_voce' AND id_item_test_compilato >= '$id_start' ORDER BY id_item_test_compilato";
} else {
$query = "SELECT * FROM item_test_compilato WHERE  id_test='$id_test' AND id_item_test='$id_item_test' AND id_item_test_compilato >= '$id_start' ORDER BY id_item_test_compilato";
};
$result=$mysqli->query($query);
$risposta = $result->fetch_array();
$righe = 1;
while ($risposta and $righe<=50) {
	if ($risposta[$voce] or $voce=='file_allegato') {
		$id_test_compilato=$risposta["id_test_compilato"];
		$query1 = "SELECT id_utente,year(data_compilazione) as yy,month(data_compilazione) as mm, dayofmonth(data_compilazione) as dd,hour(data_compilazione) as hh,minute(data_compilazione) as mi FROM test_compilato WHERE id_test_compilato = '$id_test_compilato'";
		$result1=$mysqli->query($query1);
		$dati_utente = $result1->fetch_array();
		echo "<p>";

		$id_autore = $dati_utente["id_utente"];
		echo "<span class=testopiccolo>
	<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_autore</a>
</span>";		


	echo "<span class=testopiccolo> - ".$dati_utente["dd"]."/".$dati_utente["mm"]."/".$dati_utente["yy"]." - ".$dati_utente["hh"].":".$dati_utente["mi"]." - </span>";
		printf("<span class=testopiccolo><a href=index.php?risorsa=test_compilato&id_test_compilato=%s>%s</a></span><br>\n",$id_test_compilato,$stringa[questionario_compilato]);
		if ($voce=='file_allegato') {
			if ($risposta["nome_file"]) {
				$nome_file=$risposta["nome_file"];
				$file_size=$risposta["file_size"];
				echo "<span class=testopiccolo>
				<a href=scarica.php?dir=test&file=$nome_file>
	$nome_file <i>(".stringa_filesize($file_size).")</i></span></a></span>";
			} else { 
				echo "<span class=testopiccolo>$stringa[no_file]</span>";
			};
		} else {
			if ($voce<>"risp_chiusa") {
				echo "<p><table border=0><tr><td><span class=testo>";
				$risposta = ereg_replace("\n","<br>",$risposta[$voce]);
				echo parse_link($risposta);
				echo "</span></td></tr></table></p>\n";
			};
			
		};
		$righe++;
	};
	$risposta = $result->fetch_array();
}; //fine del while delle voci

echo "<hr size=1>";

if ($risposta) {
	$id_item_test_compilato = $risposta["id_item_test_compilato"];
	printf( "<span class=testopiccolo>[<a href=index.php?risorsa=test_risultati_dettaglio&id_item_test=%s&id_start=%s&voce=%s&valore=$valore>%s</a>]</span>",$id_item_test,$id_item_test_compilato,$voce,">>");
	};
	
echo "</td></tr></table>";	
echo "<br><br>";
?>

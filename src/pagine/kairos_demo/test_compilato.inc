<?php
$id_test_compilato=$_REQUEST["id_test_compilato"];

$query = "SELECT id_test,id_utente,punteggio,punteggio_max,sequenza_domande,year(data_compilazione) as yy,month(data_compilazione) as mm, dayofmonth(data_compilazione) as dd,hour(data_compilazione) as hh,minute(data_compilazione) as mi FROM test_compilato WHERE id_test_compilato = '$id_test_compilato'";

$result=$mysqli->query($query);

$riga = $result->fetch_array();

$id_test=$riga["id_test"];
$id_utente1 = $riga["id_utente"];

if ($id_utente<>$id_utente1 AND $ruolo<>'admin' AND $ruolo<>'staff') {
	echo "<p><span class=testo>Non hai i privilegi di accesso a questa funzione</span></p>";
	exit();
};

$id_utente = $riga["id_utente"];

$data_comp = $riga["dd"]."/".$riga["mm"]."/".$riga["yy"]." - ".$riga["hh"].":".$riga["mi"];
$punteggio=$riga["punteggio"];
$punteggio_max=$riga["punteggio_max"];

$sequenza_domande=$riga["sequenza_domande"];

$query="SELECT tipo_test,titolo FROM test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$tipo_test=$riga["tipo_test"];

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[questionario_compilato])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<span class=testo><b>".$riga["titolo"]." ($id_test)</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

if ($id_utente) {
	$query = "SELECT cognome,nome,email FROM utenti where id_utente='$id_utente'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	$nome_utente=$riga["nome"];
	$cognome_utente=$riga["cognome"];
	$email_utente=$riga["email"];
};

echo "
<span class=testopiccolo>
<b>$stringa[utente]:</b> $nome_utente $cognome_utente <i>($id_utente)</i></span><br>
<span class=testopiccolo><b>$stringa[data]:</b> $data_comp</span><br>";

if ($tipo_test==0) {
	echo "<span class=testopiccolo><b>$stringa[punteggio]:</b> $punteggio/$punteggio_max</span><br>";
};
echo "<br>";

// estraggo le voci del test e le sottopongo
$query = "SELECT count(*) as num_voci FROM item_test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$num_voci=$riga["num_voci"];

$voci=array();
$query = "SELECT * FROM item_test WHERE id_test='$id_test' ORDER BY num_item";
$result=$mysqli->query($query);
$voce=1;
while ($riga=$result->fetch_array()) {
	$voci[$voce]=$riga["id_item_test"];
	$voce++;
};

if ($sequenza_domande) {
	$voci2=split(",",$sequenza_domande);
	$num_voci=count($voci2);
	for ($i=1;$i<=$num_voci;$i++) {
		$voci[$i]=$voci2[$i-1];
	};
};

for ($voce=1;$voce<=$num_voci;$voce++) {
	$query = "SELECT * FROM item_test WHERE id_test='$id_test' AND id_item_test=$voci[$voce]";
	$result=$mysqli->query($query);
	$item = $result->fetch_array();
	$id_item_test=$item["id_item_test"];
	$num_item = $item["num_item"];
	$tipo_item = $item["tipo_item"];
	$domanda = $item["domanda"];
	$risp1 = htmlentities($item["risp1"]);
	$risp2 = htmlentities($item["risp2"]);
	$risp3 = htmlentities($item["risp3"]);
	$risp4 = htmlentities($item["risp4"]);
	$risp5 = htmlentities($item["risp5"]);
	$risp6 = htmlentities($item["risp6"]);
	$risp7 = htmlentities($item["risp7"]);
	$risp8 = htmlentities($item["risp8"]);
	$punt_risp[1] = $item["punt_risp1"];
	$punt_risp[2] = $item["punt_risp2"];
	$punt_risp[3] = $item["punt_risp3"];
	$punt_risp[4] = $item["punt_risp4"];
	$punt_risp[5] = $item["punt_risp5"];
	$punt_risp[6] = $item["punt_risp6"];
	$punt_risp[7] = $item["punt_risp7"];
	$punt_risp[8] = $item["punt_risp8"];
	$risp_altro = htmlentities($item["risp_altro"]);
	$note = $item["note"];
	
	$query1="SELECT * FROM item_test_compilato WHERE id_test_compilato='$id_test_compilato' AND id_test='$id_test' AND id_item_test = '$id_item_test'";

	$result1=$mysqli->query($query1);
	$item_compilato = $result1->fetch_array();

	echo "<p><span class=testo><b>$voce. ";
	//$domanda = ereg_replace("\n","<br>",$domanda);
	echo ($domanda);
	echo "</b></span></p>\n";

	switch ($tipo_item) {
	case "0":
		// domanda aperta
		$risposta = $item_compilato["risposta_aperta"];
		echo "<p><table border=0><tr><td><span class=testo>";
		$risposta = ereg_replace("\n","<br>",$risposta);
		echo parse_link($risposta);
		echo "</span></td></tr></table></p>\n";
		break;
	
	case "1":
		// domanda chiusa
		$risp_item = $item_compilato["risp_chiusa"];
		$risposta_altro = $item_compilato["risp_altro"];
		for ($j=1; $j<=8; $j++) {
			$risposta = "risp".$j;
		
			if (${$risposta}) {
				$radio = "risp_voce_".$voce;
				echo "<input type=radio name=$radio value=$j ";

				if ($risp_item == $j and !$risposta_altro) {
					echo "checked";
				};
				echo "><span class=testopiccolo>${$risposta}</span><br>\n";
			};
		};
	
		if ($risposta_altro) {
			$radio = "risp_voce_".$voce;
			echo "<input type=radio name=$radio value=$j ";
			
			if ($risposta_altro) {
				echo "checked";
			};
			echo "><span class=testopiccolo>$stringa[altro]:</span>";
			echo "<input type=text name=risposta_altro_voce_$voce maxLength=60 size=50 value=\"$risposta_altro\">";
		};
		break;
	
	case "3":
		// domanda chiusa risposta multipla
		$risposta_altro = $item_compilato["risp_altro"];
		for ($j=1; $j<=8; $j++) {
			$risposta = "risp".$j;
		
			if (${$risposta}) {
				$box = "risp_box".$voce."_".$j;
				$campo="risp_box".$j;
				$risp_item=$item_compilato[$campo];
				echo "<input type=checkbox name=$box ";

				if ($risp_item == "1") {
					echo "checked";
				};
				echo "><span class=testopiccolo>${$risposta}</span><br>\n";
			};
		};
	
		if ($risposta_altro) {
			$box = "risp_voce_".$voce;
			echo "<input type=checkbox name=$box  ";
			
			
				echo "checked";
				
			echo "><span class=testopiccolo>$stringa[altro]:</span>";
			echo "<input type=text name=risposta_altro_voce_$voce maxLength=60 size=50 value=\"$risposta_altro\">";
		};
		break;

	case "2":
		//file allegato
		$nome_file=$item_compilato["nome_file"];
		$file_size=$item_compilato["file_size"];
		if ($nome_file) {
			echo "<span class=testopiccolo>
		<a href=scarica.php?dir=test&file=$nome_file>
	$nome_file <i>(".stringa_filesize($file_size).")</i></span></a></span>";	
		} else {
			echo "<span class=testopiccolo>$stringa[no_file]</span>";
		};
		break;
		
	};
	if ($note) {
		echo "<br><span class=testopiccolo><i>$note</i></span>";
	};
}; //fine del while delle voci

echo "<br><br>";

echo "</td></tr></table><br>";

?>

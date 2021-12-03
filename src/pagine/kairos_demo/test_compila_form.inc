<?php

// parametro di richiamo: id_test

$id_test=$_REQUEST["id_test"];

$query = "SELECT * FROM test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

if (!$riga) {
	echo "<p><span class=testo>$stringa[test_inesistente]</span></p>";
	exit();
};

$tipo_test=$riga["tipo_test"];
$num_domande=$riga["num_domande"];

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[compilazione_test])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>$riga[titolo]</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";



//calcolo quante sono le voci del test
$query = "SELECT count(*) as num_voci FROM item_test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

$num_voci=$riga["num_voci"];
$voci=array();
$voci[0]=0;
for ($i=0;$i<$num_voci;$i++) {
	$voci[$i]=$i+1;
};

$random=0;
if ($num_domande and $tipo_test=="0") {
	if ($num_domande>$num_voci) $num_domande=$num_voci;
	shuffle($voci);
	for ($i=0;$i<$num_voci;$i++) {
		if ($i>=$num_domande) $voci[$i]=0;
	};
	$num_voci=$num_domande;
	$random=1;
};
		
// estraggo le voci del test e le sottopongo

//controllo se il questionario prevede file allegati

$query= "SELECT id_item_test FROM item_test WHERE id_test='$id_test' AND tipo_item='2'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

if (!$riga) {
	echo "<form action=index.php method=post>\n";
} else {
	echo "
	<FORM action=index.php encType=multipart/form-data method=post>\n
	<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>\n";
};

echo "<input type=hidden name=risorsa value=\"test_compila_op\">\n";
echo "<input type=hidden name=id_test value=\"$id_test\">\n";
echo "<input type=hidden name=num_voci value=\"$num_voci\">\n";
echo "<input type=hidden name=random value=\"$random\">\n";

for ($voce=0;$voce<$num_voci;$voce++) {
	$query = "SELECT * FROM item_test WHERE id_test='$id_test' AND num_item=$voci[$voce]";
	$result=$mysqli->query($query);
	
	/*
	if (mysql_error()) 	echo mysql_error()."<br>$query<br>$num_voci : $voce -> $voci[$voce]";
	*/
	
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
	$risp_altro = $item["risp_altro"];
	
	$label=$voce+1;
	
	echo "<input type=hidden name=tipo_voce_$label value=\"$tipo_item\">\n";
	echo "<input type=hidden name=id_item_test_voce_$label value=\"$id_item_test\">\n";
	echo "<input type=hidden name=risp_altro_voce_$label value=\"$risp_altro\">\n";
	
	
	echo "<p><span class=testo><b>$label. ";
	//$domanda = str_replace("\n","<br>",$domanda);
	echo ($domanda);
	echo "</b></span></p>\n";
	
	switch($tipo_item) {
		case "0":
		// domanda aperta
			echo "<textarea name=risposta_aperta_$label rows=8 cols=60></textarea>\n";
			break;
		case "1":
		// domanda chiusa risposta singola
			for ($j=1; $j<=8; $j++) {
				$risposta = "risp".$j;
	
				if (${$risposta}) {
					$radio = "risp_voce_".$label;
					echo "<input type=radio name=$radio value=$j><span class=testopiccolo>${$risposta}</span><br>\n";
				};
			};
	
			if ($risp_altro == 'on') {
				$radio = "risp_voce_".$label;
				echo "<input type=radio name=$radio value=$j><span class=testopiccolo>$stringa[altro_specificare]:";
				echo "<input type=text name=risposta_altro_voce_$label maxLength=60 size=50></span>";
			};
			break;
		
		case "3":
		// domanda chiusa risposta multipla
			for ($j=1; $j<=8; $j++) {
				$risposta = "risp".$j;
	
				if (${$risposta}) {
					$box = "risp_voce_".$label."_".$j;
					echo "<input type=checkbox name=\"$box\"><span class=testopiccolo>${$risposta}</span><br>\n";
				};
			};
			if ($risp_altro == 'on') {
				$box = "risp_voce_".$label;
				echo "<input type=checkbox name=$box><span class=testopiccolo>$stringa[altro_specificare]:";
				echo "<input type=text name=risposta_altro_voce_$label maxLength=60 size=50></span>";
			};
			
			break;
			
		case "2":
			//file allegato
			echo "
			<span class=testopiccolo>$stringa[allega_file]</span>:<INPUT name=nome_file_voce_$label type=file>";
			break;
	};
}; //fine del while delle voci

echo "<BR><P align=center><INPUT type=submit value=$stringa[ok]></P>";
echo "</FORM>";

echo "</td></tr></table>";
?>

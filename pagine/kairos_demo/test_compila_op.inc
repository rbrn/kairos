<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

$id_test=$_REQUEST["id_test"];
$num_voci=$_REQUEST["num_voci"];
$random=$_REQUEST["random"];
$MAX_FILE_SIZE=$_REQUEST["MAX_FILE_SIZE"];

$query = "SELECT tipo_test,punteggio_soglia FROM test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$tipo_test=$riga["tipo_test"];
$punteggio_soglia=$riga["punteggio_soglia"];

$query = "INSERT INTO test_compilato (id_test,id_utente,data_compilazione,id_corso,id_edizione,id_gruppo) VALUES 	('$id_test','$id_utente',now(),'$id_corso_s','$id_edizione_s','$id_gruppo_s')";
$result=$mysqli->query($query);


$id_test_compilato = $mysqli->insert_id;


//notifico chiara
/*
if ($cod_area=="kairos_master") {
	$url="http://master.garamond.it/index.php?risorsa=test_compilato&id_test_compilato=$id_test_compilato";
	if ($id_test=="pw_azienda" or $id_test=="pw_scuola" or $id_test=="pw_uni") {
		$oggetto="Master e-learning: notifica questionario compilato";
		$messaggio="
		Ciao Chiara,
		ecco un questionario compilato: 
		$url
		
		Ciao ciao.";
		
		$id_package=uniqid("");
		mail_job($id_package,"chiara@astuto.it",$oggetto,$messaggio,"Francesco Leonetti <$fleo@garamond.it>","$fleo@garamond.it","");
		mysql_select_db($DBASE,$db);	
	};
};
*/
$punteggio=0;		
$punteggio_max=0;
$feedback="";
$sequenza_domande="";

for ($voce=1; $voce<=$num_voci; $voce++) {
			$valore = "id_item_test_voce_".$voce;
			$id_item_test = $_REQUEST[$valore];
			
			$valore = "risposta_aperta_".$voce;
			$risposta_aperta = $_REQUEST[$valore];
			
			$valore = "risp_voce_".$voce;
			$risp_chiusa = $_REQUEST[$valore];
			
			$valore = "risposta_altro_voce_".$voce;
			$risp_altro = $_REQUEST[$valore];

			for ($j=1; $j<=8; $j++) {
				$box = "risp_voce_".$voce."_".$j;
				$campo="risp_box".$j;
				if ($_REQUEST[$box]=="on") {
					${$campo}="1";
				} else {
					${$campo}="0";
				};
			};
			
			$valore = "nome_file_voce_".$voce;
			$nome_file = $_FILES[$valore]["tmp_name"];		
			$nome_file_name = $_FILES[$valore]["name"];	
			$nome_file_size = $_FILES[$valore]["size"];
			$nome_file_type = $_FILES[$valore]["type"];		
						
			if ($nome_file_name) {
				$nome_file_name = trim($nome_file_name);
				$nome_file_name = ereg_replace(" ","",$nome_file_name);
				$nome_file_name = strtolower($id_utente)."_".$nome_file_name;
				if (!is_dir($PATH_ARCHIVI."test")) {
					mkdir($PATH_ARCHIVI."test",0755);
				};
				$fullpath = $PATH_ARCHIVI."test/".$nome_file_name;
				copy($nome_file,$fullpath);	
			};
		
			$query = "INSERT INTO item_test_compilato SET ".
					"id_test_compilato='$id_test_compilato',".
					"id_test='$id_test',".
					"id_item_test='$id_item_test',".
					"risposta_aperta='$risposta_aperta',".
					"risp_chiusa='$risp_chiusa',".
					"risp_box1='$risp_box1',".
					"risp_box2='$risp_box2',".
					"risp_box3='$risp_box3',".
					"risp_box4='$risp_box4',".
					"risp_box5='$risp_box5',".
					"risp_box6='$risp_box6',".
					"risp_box7='$risp_box7',".
					"risp_box8='$risp_box8',".
					"risp_altro='$risp_altro',".
					"nome_file='$nome_file_name',".
					"file_size='$nome_file_size',".
					"file_type='$nome_file_type'";
					
			$result=$mysqli->query($query);
			
			
			if ($tipo_test==0) {
				$query="SELECT * FROM item_test WHERE id_test='$id_test' AND id_item_test='$id_item_test'";
				$result=$mysqli->query($query);
				$item=$result->fetch_array();
				$risp[1] = htmlentities($item["risp1"]);
				$risp[2] = htmlentities($item["risp2"]);
				$risp[3] = htmlentities($item["risp3"]);
				$risp[4] = htmlentities($item["risp4"]);
				$risp[5] = htmlentities($item["risp5"]);
				$risp[6] = htmlentities($item["risp6"]);
				$risp[7] = htmlentities($item["risp7"]);
				$risp[8] = htmlentities($item["risp8"]);
				$punt_risp[1] = $item["punt_risp1"];
				$punt_risp[2] = $item["punt_risp2"];
				$punt_risp[3] = $item["punt_risp3"];
				$punt_risp[4] = $item["punt_risp4"];
				$punt_risp[5] = $item["punt_risp5"];
				$punt_risp[6] = $item["punt_risp6"];
				$punt_risp[7] = $item["punt_risp7"];
				$punt_risp[8] = $item["punt_risp8"];
				$note = $item["note"];
				$peso = $item["peso"];
				$domanda = $item["domanda"];
				$punti_risposta=$punt_risp[$risp_chiusa];
				$punteggio += $punt_risp[$risp_chiusa];
				$punteggio_max += max($punt_risp);
				$feedback .= "
				<table border=1 cellpadding=5 width=100%>
				<tr><td>
				<span class=testo>
				$voce - <b>$domanda</b><br><br>";
				
				if ($risp_box1 or $risp_box2 or $risp_box3 or $risp_box4 or $risp_box5 or $risp_box6 or $risp_box6 or $risp_box8) {
					$feedback.= "$stringa[risposta_fornita]: <br><br>";
					for ($j=1; $j<=8; $j++) {
						$risposta = $risp[$j];
						$punti=$punt_risp[$j];
						$campo="risp_box".$j;
						if (${$campo}=="1") {
							$feedback .= "$risposta - $stringa[punteggio]: $punti<br>";
						};
					};
				} else { 
					$feedback.= "
					$stringa[risposta_fornita]: ".$risp[$risp_chiusa]."<br>
					$stringa[punteggio]: ".$punt_risp[$risp_chiusa]."<br><br>";
				};

				if ($note) {
					$feedback .=
				 	"<br><b>$stringa[note]:</b> <i>$note</i><p>&nbsp;</p>";
				};
				$feedback .= "
				</span>
				</td></tr>
				</table><br>";
				if ($random) $sequenza_domande .= "$id_item_test,";
			};
				
				
};

// incremento i totali progressivi
$query = "UPDATE test SET tot_prog = tot_prog + 1,data_ultima=NOW() WHERE id_test='$id_test'";
$result=$mysqli->query($query);
	
$query = "SELECT data_prima FROM test WHERE id_test='$id_test'"; 
$result=$mysqli->query($query);
$riga = $result->fetch_array();
if (!$riga["data_prima"]) {
	$query = "UPDATE test SET data_prima=NOW() WHERE id_test='$id_test'";
	$result=$mysqli->query($query);
};

	
for ($voce=1; $voce<=$num_voci; $voce++) {
			$valore = "tipo_voce_".$voce;
			$tipo_voce = $_REQUEST[$valore];
			
			$valore = "id_item_test_voce_".$voce;
			$id_item_test = $_REQUEST[$valore];
			
			if ($tipo_voce == '1') {

				$valore = "risp_voce_".$voce;
				$risp_chiusa = $_REQUEST[$valore];
			
				$valore = "risposta_altro_voce_".$voce;
				$risp_altro = $_REQUEST[$valore];
			
				if (!$risp_chiusa and !$risp_altro) {
					$query = "UPDATE item_test SET tot_no_risp = tot_no_risp + 1 WHERE id_item_test = '$id_item_test'";	
					$result=$mysqli->query($query);
					};
									
				if ($risp_chiusa >=1 and $risp_chiusa<=8) {
					$query = "UPDATE item_test SET tot_risp$risp_chiusa = tot_risp$risp_chiusa +1 WHERE id_item_test = '$id_item_test'";
					$result=$mysqli->query($query);
				};
				
				if ($risp_altro) {
					$query = "UPDATE item_test SET tot_risp_a = tot_risp_a +1 WHERE id_item_test = '$id_item_test'";
					$result=$mysqli->query($query);
				};				

			};	
			
			if ($tipo_voce == '3') {
				$valore = "risposta_altro_voce_".$voce;
				$risp_altro = $_REQUEST[$valore];
				
				$risposto=0;
				for ($j=1; $j<=8; $j++) {
					$box = "risp_voce_".$voce."_".$j;
					$campo="risp_box".$j;
					if ($_REQUEST[$box]=="on") {
						$risposto=1;
						$query = "UPDATE item_test SET tot_risp$j = tot_risp$j +1 WHERE id_item_test = '$id_item_test'";
						$result=$mysqli->query($query);
					};
				};
				
				if ($risp_altro) {
					$query = "UPDATE item_test SET tot_risp_a = tot_risp_a +1 WHERE id_item_test = '$id_item_test'";
					$result=$mysqli->query($query);
				};		
				
				if (!$risposto and !$risp_altro) {
					$query = "UPDATE item_test SET tot_no_risp = tot_no_risp + 1 WHERE id_item_test = '$id_item_test'";	
					$result=$mysqli->query($query);
				};				

			};	
};

if ($tipo_test==0) {
	if ($sequenza_domande) $sequenza_domande=substr($sequenza_domande,0,strlen($sequenza_domande)-1);
	$query = "UPDATE test_compilato SET punteggio='$punteggio',punteggio_max='$punteggio_max',sequenza_domande='$sequenza_domande' WHERE id_test_compilato=$id_test_compilato";
	$result=$mysqli->query($query);
	if ($punteggio_soglia>0) {
		if ($punteggio>=$punteggio_soglia) {
			$esito=$stringa[test_superato];
			$icona="img/forum/approvo.gif";
		} else {
			$esito=$stringa[test_non_superato];
			$icona="img/forum/disapprovo.gif";
		};
	};
	


	echo "
	<p><span class=testo>$stringa[punteggio_ottenuto]: <b>$punteggio</b> $stringa[punteggio_max] <b>$punteggio_max</b>.";
	if ($punteggio_soglia>0) {
		echo " <b>$esito</b> <img src=\"$icona\">";
	};
		echo "</p>".$feedback;
	} else {	
		echo "<p><span class=testo><b>$stringa[questionario_registrato]</b></span></p>";
	};

echo "</td></tr></table><br>";
?>

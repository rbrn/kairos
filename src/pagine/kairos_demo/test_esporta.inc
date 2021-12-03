<?php

function dim_file($filename) {
	$type = Array ('Byte', 'KB', 'MB', 'GB');
    $filesize = filesize ($filename);

    for ($i = 0; $filesize > 1024; $i++)
        $filesize /= 1024;

    return round ($filesize, 2)." $type[$i]"; 
};

// parametro di richiamo: id_test
$id_test=$_REQUEST["id_test"];
$query = "SELECT * FROM test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$tipo_test=$riga["tipo_test"];
$num_domande=$riga["num_domande"];


$path_test=$PATH_ROOT_FILE."test/$cod_area/";
$path_id_test=$path_test."$id_test/";
if (!is_dir($path_test)) {
	@mkdir($path_test,0755);
};

if (!is_dir($path_id_test)) {
	@mkdir($path_id_test,0755);
	@mkdir($path_id_test."media",0755);
	copy ("$PATH_ROOT_FILE/stili/stile_sito.css","$path_id_test/stile_sito.css");
	copy ("$PATH_ROOT_FILE/script/script_test.js","$path_id_test/script_test.js");
};

$testata="
<html>
<head>
<title>Test</title>
<link rel=\"stylesheet\" href=\"stile_sito.css\">
<script language=\"javascript\" src=\"script_test.js\"></script>
</head>
<body>
<table border=0 cellpadding=10>
<tr><td valign=top>
<p><span class=titolopagina>$stringa[compilazione_test]:</span><br>
<span class=testo><b>".$riga["titolo"]."</b></span></p>
<form name=\"test_form\" id=\"test_form\">\n
";

$piede.="
</form>\n
</td></tr>
</table>";

$fine="
</body>
</html>";

//calcolo quante sono le voci del test
$query = "SELECT count(*) as num_voci FROM item_test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

$num_voci=$riga["num_voci"];
$voci=array();
for ($i=1;$i<=$num_voci;$i++) {
	$voci[$i]=$i;
};

$pag_size=10;
$tot_pag=floor($num_voci/$pag_size);
if ( ($num_voci % $pag_size) <> 0) $tot_pag++;

$random=0;
$pagina=1;
$corpo="";
for ($voce=1;$voce<=$num_voci;$voce++) {
	$query = "SELECT * FROM item_test WHERE id_test='$id_test' AND num_item=$voci[$voce]";
	$result=$mysqli->query($query);
	$item = $result->fetch_array();
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
	$punt_risp[1] = $item["punt_risp1"];
	$punt_risp[2] = $item["punt_risp2"];
	$punt_risp[3] = $item["punt_risp3"];
	$punt_risp[4] = $item["punt_risp4"];
	$punt_risp[5] = $item["punt_risp5"];
	$punt_risp[6] = $item["punt_risp6"];
	$punt_risp[7] = $item["punt_risp7"];
	$punt_risp[8] = $item["punt_risp8"];
	$note = $item["note"];
	$corpo.="<p><span class=testo><b>$voce. ";
	$domanda = str_replace("\n","<br>",$domanda);
	
	//isolo dalla domanda le url a media (immagini, flash)
	eregi("SRC=\"*([^[:space:]^>^\"]*)\"*",$domanda,$parti);
	
	if ($parti[1]) {
		$url=$parti[1];
		$path=$PATH_ROOT."materiali_img/".$cod_area."/";
		$path2=$PATH_ROOT_FILE."materiali_img/".$cod_area."/";
		$file_img=str_replace($path,$path2,$parti[1]);
		if (file_exists($file_img)) {
			$filename=$path_id_test."media/".basename($file_img);
			copy ($file_img,$filename);
			$path=$PATH_ROOT."materiali_img/".$cod_area."/";
			$pos=strpos($url,basename($file_img));
			$resto=substr($url,0,$pos);
			$domanda=str_replace($resto,"media/",$domanda);
		};
	};

	$note = str_replace("\n","<br>",$note);
	$corpo.=$domanda;
	$corpo.="</b></span></p>\n";
	$corpo .= "<span class=testopiccolo><i>$note</i></span><br><br>";
	
	switch($tipo_item) {
		case "1":
			for ($j=1; $j<=8; $j++) {
				$risposta = "risp".$j;
	
				if (${$risposta}) {
					$radio = "risp_voce_".$voce;
					$note_i="";
					if ($punt_risp[$j]) $note_i="";
					$corpo.="<input type=radio name=$radio value=$j onclick=\"feedback($punt_risp[$j],'$note_i')\"><span class=testopiccolo>${$risposta}</span><br>\n";
				};
			};
			break;		
	};
	
	
	
	if (($voce % $pag_size) == 0) {
		if ($tot_pag > 1) {
			$link_prec="";
			$link_succ="";
			$pagina_prec=$pagina-1;
			$pagina_succ=$pagina+1;
			if ($pagina>1) $link_prec="test_".$id_test."_".$pagina_prec.".htm";
			if ($pagina<>$tot_pag) $link_succ="test_".$id_test."_".$pagina_succ.".htm";
		};
		
		$link="";
		if ($link_prec or $link_succ) {
			$link="<hr size=1>";
			if ($link_prec) {
				$link .= "<span class=testo>[<a href=$link_prec><<</a>]</span>";
			};
			
			if ($link_succ) {
				$link .= "<span class=testo>[<a href=$link_succ>>></a>]</span>";
			};
		};
		
		$path_file=$path_id_test."test_".$id_test."_".$pagina.".htm";
		$fd=fopen($path_file,"w");
		$testo=$testata.$corpo.$piede.$link.$fine;
		fwrite($fd,$testo);
		fclose($fd);
		$pagina++;
		$corpo="";
	};
}; 

if ( ($num_voci % $pag_size) <> 0) {
	if ($tot_pag > 1) {
			$link_prec="";
			$link_succ="";
			$pagina_prec=$pagina-1;
			$pagina_succ=$pagina+1;
			if ($pagina>1) $link_prec="test_".$id_test."_".$pagina_prec.".htm";
			if ($pagina<>$tot_pag) $link_succ="test_".$id_test."_".$pagina_succ.".htm";
		};
		
	$link="";
	if ($link_prec or $link_succ) {
		$link .= "<hr size=1>\n";
		if ($link_prec) {
			$link .= "<span class=testo>[<a href=$link_prec><<</a>]</span>";
		};
		
		if ($link_succ) {
			$link .= "<span class=testo>[<a href=$link_succ>>></a>]</span>";
		};
		$link .= "<hr size=1>";
	};
		
	$path_file=$path_id_test."test_".$id_test."_".$pagina.".htm";
	$fd=fopen($path_file,"w");
	$testo=$testata.$corpo.$piede.$link.$fine;
	fwrite($fd,$testo);
	fclose($fd);
	$pagina++;
	$corpo="";
};	


$zipfile="$path_test/test_".$id_test.".zip";
$comando="cd $path_test ; /usr/bin/zip -r $zipfile $id_test > /dev/null";
shell_exec($comando); 

$url=$PATH_ROOT."test/$cod_area/$id_test/test_".$id_test."_1.htm";
$url_zip=$PATH_ROOT."test/$cod_area/test_".$id_test.".zip";
$dim=dim_file($zipfile);

echo "
<p>
<span class=testo>
Test esportato offline in: <a href=\"$url\">$url</a>
</p>
<p>
File zip: <a href=\"$url_zip\">$url_zip</a> ($dim)
</p>
</span>
<br>";


?>

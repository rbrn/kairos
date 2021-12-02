<?php
		$dati_nodo=dati_nodo($risorsa);
		
		$id_corso_s=$dati_nodo[id_corso];
		$id_edizione_s=$dati_nodo[id_edizione];
		$descr_gruppo=$dati_nodo[descr_gruppo];
		$titolo=$dati_nodo[titolo];
		$id_modulo=$dati_nodo[id_modulo];
		$id_gruppo=$dati_nodo[id_gruppo];
		
		$query="SELECT tipo,id_autore FROM materiali_gruppo WHERE id_risorsa='$risorsa'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$tipo=$riga["tipo"];
		$id_autore=$riga["id_autore"];
		
		$pag_succ=materiali_gruppo_pag_succ($risorsa,$risorsa_superiore);
		$pag_prec=materiali_gruppo_pag_prec($risorsa,$risorsa_superiore);
		
		//header("Cache-Control: no-cache");
		//header("Pragma: no-cache");
		require "./include/testata.inc";
		echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[lavori_gruppo])."</td></tr>
<tr><td>";


		echo "
		<table border=0 bgcolor=\"white\" width=100%>
		<tr>
		<td width=50%><span class=sottotitolopagina>$titolo</span><br><span class=testo><b>$stringa[gruppo]:</b> <a class=miolink href=\"javascript:;\" title=\"$stringa[componenti_gruppo]\" onclick=\"javascript:apri_scheda('gruppo_pw_iscritti.php?id_gruppo=$id_gruppo',                   'myRemoteGruppo',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowGruppo');\">$descr_gruppo</a></span></td>";
		/*
		if ($id_autore) {
			$query="SELECT nome,cognome FROM utenti WHERE id_utente='$id_autore'";
			$result=$mysqli->query($query);
			$riga=$result->fetch_array();
			$nome_autore=$riga[nome]." ".$riga[cognome];
			
			echo "
			<td align=right>
			<span class=testopiccolo>$stringa[autore]:
			<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$nome_autore</a></span></td>
			";
		};	
		*/
		echo "
		<td align=right>
		<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back1','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back1\"></a>
		";
		if ($pag_prec) {
			echo "
			<a href=\"materiali_gruppo_browse.php?risorsa=$pag_prec\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_indietro1','','img/ico_indietro_over.gif',1)\"><img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_indietro1\"></a>
			";
		} else {
			echo "<img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_indietro1\">";
		};
		if ($pag_succ) {
			echo "
			<a href=\"materiali_gruppo_browse.php?risorsa=$pag_succ\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_fw1','','img/ico_avanti_over.gif',1)\"><img border=\"0\" src=\"img/ico_avanti.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[avanti]\" name=\"img_fw1\"></a>";
		} else {
			echo "<img border=\"0\" src=\"img/ico_avanti.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[avanti]\" name=\"img_fw1\">";
		};
		echo "</td></tr></table>";
		
		echo "
		<table border=0 cellpadding=5 width=100%>
		<tr>";
		
		echo "<td valign=top>";
		
		echo "<span class=testo>";
		
		if (file_exists("./materiali/$cod_area/gruppo/$id_pagina.inc")) {
			require "./materiali/$cod_area/gruppo/$id_pagina.inc";
		};
		
		echo "</span>";
		
		echo "</td>";
		echo "<td valign=top bgcolor=$colore_sfondo_neutro width=180 cellpadding=3>";
		
		capitolo_gruppo($id_modulo,$risorsa,"true");
		
		$query_f="SELECT * FROM materiali_gruppo WHERE risorsa_padre='$risorsa_superiore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo=1 ORDER BY posizione,id_risorsa";
		$result_f=$mysqli->query($query_f);
		
		if ($result_f->num_rows) {
			echo "
			<hr size=1>
			<ul style=\"list-style-type:none\">
			<li><span class=testopiccolo><b>$stringa[download]:</b></span><br>
			";
			while ($riga_f=$result_f->fetch_array()) {
				$id_file=$riga_f["id_risorsa"];
				$file_size=$riga_f["file_size"];
				$titolo_f=$riga_f["titolo"];
				$descrizione_f=$riga_f["descrizione"];
				echo "
				<span class=testopiccolo><a href=\"materiali_gruppo_browse.php?risorsa=$id_file\"  alt=\"$descrizione_f\">$titolo_f</a><br>(".stringa_filesize($file_size).")<br>$descrizione_f</span>
				<br><br>";
			};
			echo "</li></ul>";
		};
		
		
		echo "</td>";
		
		echo "</tr>
		</table>";
		
		echo "
		<table border=0 bgcolor=white width=100%>
		<tr>
		<td width=50%><span class=sottotitolopagina>$titolo</span><!--<br><span class=testo><b>$titolo_pagina</b></span>--></td>";
		
		if ($id_autore) {
			$query="SELECT nome,cognome FROM utenti WHERE id_utente='$id_autore'";
			$result=$mysqli->query($query);
			$riga=$result->fetch_array();
			$nome_autore=$riga[nome]." ".$riga[cognome];
			
			echo "
			<td align=right>
			<span class=testopiccolo>$stringa[autore]:
			<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$nome_autore</a></span></td>
			";
		};	
		
		echo "
		<td align=right>
		<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back2','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back2\"></a>
		";
		if ($pag_prec) {
			echo "
			<a href=\"materiali_gruppo_browse.php?risorsa=$pag_prec\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_indietro2','','img/ico_indietro_over.gif',1)\"><img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_indietro2\"></a>
			";
		} else {
			echo "<img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_indietro2\">";
		};
		if ($pag_succ) {
			echo "
			<a href=\"materiali_gruppo_browse.php?risorsa=$pag_succ\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_fw2','','img/ico_avanti_over.gif',1)\"><img border=\"0\" src=\"img/ico_avanti.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[avanti]\" name=\"img_fw2\"></a>";
		} else {
			echo "<img border=\"0\" src=\"img/ico_avanti.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[avanti]\" name=\"img_fw2\">";
		};
		
		echo "</td></tr></table>";
		
		echo "</td></tr></table><br>";
		
		require "./include/piede.inc";
?>

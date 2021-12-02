<?php
		$id_corso=id_corso($risorsa);
		
		mysql_select_db($DBASE,$db);
		$query="SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_corso'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$titolo=$riga["titolo"];
		
		$query="SELECT tipo,id_autore,id_gruppo FROM risorse_materiali WHERE id_risorsa='$risorsa'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$tipo=$riga["tipo"];
		$id_autore=$riga["id_autore"];
		$id_gruppo=$riga["id_gruppo"];
		
		if ($tipo==4) {
			$query="SELECT id_autore FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
			$result=$mysqli->query($query);
			$riga=$result->fetch_array();
			$id_autore=$riga["id_autore"];
		};
			
		
		$pag_succ=materiali_pag_succ($risorsa,$risorsa_superiore);
		$pag_prec=materiali_pag_prec($risorsa,$risorsa_superiore);
		
		//header("Cache-Control: no-cache");
		//header("Pragma: no-cache");
		require "./include/testata.inc";
		echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[materiali])."</td></tr>
<tr><td>";


		echo "
		<table border=0 bgcolor=\"white\" width=100%>
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
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back1','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back1\"></a>
		";
		if ($pag_prec) {
			echo "
			<a href=\"materiali_browse.php?risorsa=$pag_prec\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_indietro1','','img/ico_indietro_over.gif',1)\"><img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_indietro1\"></a>
			";
		} else {
			echo "<img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_indietro1\">";
		};
		if ($pag_succ) {
			echo "
			<a href=\"materiali_browse.php?risorsa=$pag_succ\"
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
		
		if (file_exists("./materiali/$cod_area/$id_pagina.inc")) {
			if ($cod_area=="kairos_itc_scuola" or $cod_area=="kairos_area_corsi") {
				$contenuto=implode('',file("./materiali/$cod_area/$id_pagina.inc"));
				$contenuto=parse_kairos($contenuto);
				echo $contenuto;
			} else {	
				require "./materiali/$cod_area/$id_pagina.inc";
			};
		};
		
		echo "</span>";

if ($kairos_cookie[0]<>"ospite") {		
		echo "<hr size=1>";

		echo "
<form action=risorse_materiali_commento_nuovo.php method=post>
<input type=hidden name=id_risorsa value=\"$risorsa\">";

echo "
<table border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" align=\"center\">

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\">
";

echo "
<tr>
<td colspan=2>
<span class=testo>$stringa[aggiungi_commento]:</span>
</td>
</tr>
<tr>
<td colspan=2 align=right><textarea name=testo rows=04 cols=40></textarea></td>
</tr>
<!--
<tr>
<td align=left><span class=testo>$stringa[lettore]:</span></td>
<td align=left><span class=testo>$id_utente</span></td>
</tr>
-->
<tr>
<td colspan=2 align=center>
<input type=submit value=\"$stringa[btn_aggiungi_commento]\">
</td>
</tr>
</table>
</td></tr></table>
</form>";
};

	$query="SELECT * FROM risorse_materiali_commenti WHERE id_risorsa='$risorsa' ORDER BY data_commento DESC";
	$result=$mysqli->query($query);

if ($result->num_rows) {
	echo "
	<hr size=1>
	<span class=testo><b>$stringa[commenti_lettori]</b></span><br><br>
	<table border=0 width=450 cellpadding=3 align=center>";
	while ($riga=$result->fetch_array()) {
		$id_commento=$riga["id_commento"];
		$id_lettore=$riga["id_utente"];
		$testo = str_replace("\n","<br>",$riga["testo"]);
		$testo = parse_link($testo);	
			
        /*aggiunto per differenziare commenti
		//identificare il tipo di ruolo utente che ha inserito il commento
        costinaldea@gmail.com  13 giugno 2009
		*/	
        
      	$ruolo_utente_commento = ruolo_utente($riga['id_utente']);
        //creare lo stile x ruolo  
		$stile_commento  = define_style($ruolo_utente_commento);
	

		$data_com = $riga["data_commento"];
		ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_com,$parti);
		$data_com=$parti[3]."/".$parti[2]."/".$parti[1]." ".$parti[4].":".$parti[5].":".$parti[6];
		echo "
		<tr>
		<td width=450 style=\"$stile_commento\">
		";
		echo "		
			<span class=testo><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_lettore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\"><b>$id_lettore</b></a></span>";
		echo " - <span class=testo>$data_com</span>
		</td>
		</tr>
		<tr>
		<td width=450 style=\"$stile_commento\"><span class=testo>$testo</span>
		";
		
		if ($ruolo=='admin' or $ruolo=='staff' or $kairos_cookie[0]==$id_lettore) {
			echo "
			<p><a href=\"index.php?risorsa=msg&msg=conf_canc&pagina=risorse_materiali_commento_del.php&id_commento=$id_commento&id_risorsa=$risorsa\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_commento','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_commento\"></a></p>";
		};
		
		echo "	
		</td>
		</tr>

		<tr>
		<td width=450><hr size=1></td>
		</tr>
		";		
	};
	echo "</table>";
} else {
	echo "<p>&nbsp;</p>";
};


		
		echo "</td>";
		echo "<td valign=top bgcolor=$colore_sfondo_neutro width=180 cellpadding=3>";
		
		capitolo($id_corso,$risorsa,"true");
		
		$query_f="SELECT * FROM risorse_materiali WHERE risorsa_padre='$risorsa_superiore' AND tipo=1 ORDER BY posizione,id_risorsa";
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
				
				$file_download=$PATH_ARCHIVI_ADMIN."materiali/$cod_area/".$titolo_f;
				if (file_exists($file_download)) {
					$file_size=filesize($file_download);
				};
				
				echo "
				<span class=testopiccolo><a href=\"materiali_browse.php?risorsa=$id_file\"  alt=\"$descrizione_f\">$titolo_f</a><br>(".stringa_filesize($file_size).")<br>$descrizione_f</span>
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
			<a href=\"materiali_browse.php?risorsa=$pag_prec\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_indietro2','','img/ico_indietro_over.gif',1)\"><img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_indietro2\"></a>
			";
		} else {
			echo "<img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_indietro2\">";
		};
		if ($pag_succ) {
			echo "
			<a href=\"materiali_browse.php?risorsa=$pag_succ\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_fw2','','img/ico_avanti_over.gif',1)\"><img border=\"0\" src=\"img/ico_avanti.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[avanti]\" name=\"img_fw2\"></a>";
		} else {
			echo "<img border=\"0\" src=\"img/ico_avanti.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[avanti]\" name=\"img_fw2\">";
		};
		
		echo "</td></tr></table>";
		
		echo "</td></tr></table><br>";
		
		require "./include/piede.inc";

			function define_style($ro){
		
			switch($ro){
				case "admin":
					$style = "background-color: #FFCC33;";

				break;

				case "utente":
					$style = "background-color: white;";
				break;
					
				case "staff":
					$style = "background-color: #CCFF66;";

				break;

				case "attesa":
				
				break;
            }
		return $style;
     }
?>
		

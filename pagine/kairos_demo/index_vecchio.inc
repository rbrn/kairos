<!-- CONTENUTO DELLA PAGINA -->
<table width="100%" border="0" cellspacing=2 cellpadding=0>
  <tr>  
	<!-- PRIMA COLONNA -->	
	
<!-- BOX LOGIN --->
<?php
	if (!isset($kairos_cookie[0])) {
	echo "
<td width=\"15%\" valign=\"top\"> 	
<table width=\"152\" border=\"1\" cellpadding=\"0\" cellspacing=\"0\" bgcolor=\"$colore_sfondo\" bordercolor=\"$colore_bordo\">
        <tr> 
          <td  height=25 valign=\"top\" align=center bgcolor=\"$colore_scuro\" >
		  <span class=testopiccolonegativo><b>$stringa[login]</b></span>
		  </td>
        </tr>";
		
		echo "
        <tr> 
          <td valign=\"top\">
		  <form action=login.php method=post>
			<input type=hidden name=risorsa value=\"index\">
            <table width=\"144\" border=\"0\" align=\"center\" bgcolor=\"$colore_sfondo\">
              <tr> 
                <td width=\"23\"> 
                  <div align=\"center\"><span class=testopiccolo><b>$stringa[id]</b></div>
                </td>
               <td width=\"83\"> 
                  <input type=\"text\" name=\"id_utente_form\" size=\"12\">
                </td>
                <td width=\"22\"> </td>
              </tr>
              <tr> 
                <td width=\"23\" height=\"23\"> 
                  <div align=\"center\"><span class=testopiccolo><b>$stringa[pw]</b></div>
                </td>
                <td width=\"83\" height=\"23\"> 
                  <input type=\"password\" name=\"pwd_utente_form\" size=\"12\">
                </td>
                <td width=\"22\" height=\"23\">
				<INPUT TYPE=\"submit\" NAME=\"login\" value=$stringa[ok]>
				</td>
				</form>
              </tr>
               <tr> 
                <td colspan=\"3\"> 
                  <div align=\"center\"><span class=testopiccolo><a href=index.php?risorsa=chiedi_pwd>$stringa[dimenticato_pw]</a></span></div>
					<hr size=1>";
					if ($cod_area<>'kairos_area_corsi') {					
						echo"
					<div align=\"center\"><span class=testopiccolo>$stringa[avere_id] <a href=index.php?risorsa=registrazione><b>$stringa[registrarsi]</b></a>.</span></div>";
					};
					
                echo "
				</td>
              </tr>
            </table>
          </td>
        </tr>";
	
	echo "
</table>
 </td>
 <td valign=top width=1 bgcolor=#cccccc>
	<img src=\"img/pixel.gif\" width=\"1\" height=\"1\" alt=\"\" border=\"0\">
</td>
";
} else {
echo "
<td width=\"15%\" valign=\"top\"> 	
<table width=\"152\" border=\"1\" cellpadding=\"0\" cellspacing=\"0\" bgcolor=\"$colore_sfondo\" bordercolor=\"$colore_bordo\">
<tr> 
<td height=\"27\" valign=\"top\" align=center bgcolor=\"$colore_scuro\" >
<span class=testopiccolonegativo><b>";

if ($cod_area=='kairos_larimart') {
	echo "PROFILI";
} else { 
	echo $stringa[corsi];
};

echo "</b></span>
</td>
</tr>";
		
echo "<tr><td valign=\"top\">
<table border=0 cellpadding=5>
<tr><td valign=\"top\">";

$query="";
$eprof="1";

/*
if ($ruolo<>'staff' and $ruolo<>'admin' and $cod_area=='kairos_area_corsi') {
	$query_p="SELECT showme AS eprof FROM utenti WHERE id_utente='$id_utente'";
	$result_p=$mysqli->query($query_p);
	$riga=$result_p->fetch_array();
	$eprof=$riga["eprof"];
};
*/

if ($ruolo<>'staff' and $ruolo<>'admin' and (!$eprof or $cod_area<>'kairos_area_corsi')) {
$query="SELECT corso.descrizione,corso.id_corso,iscrizioni_corso.id_edizione,edizioni.descrizione as descr_edizione FROM corso,iscrizioni_corso,edizioni WHERE 
corso.id_corso=iscrizioni_corso.id_corso AND iscrizioni_corso.id_corso=edizioni.id_corso AND iscrizioni_corso.id_edizione=edizioni.id_edizione AND 
edizioni.stato='attiva' AND 
iscrizioni_corso.id_utente='$id_utente' ORDER BY corso.id_corso,iscrizioni_corso.id_edizione DESC";
};


if ($ruolo=='staff' or $ruolo=='admin') {
$query="SELECT corso.descrizione,corso.id_corso,edizioni.id_edizione,edizioni.descrizione as descr_edizione FROM corso,edizioni WHERE 
corso.id_corso=edizioni.id_corso AND 
edizioni.stato='attiva'  ORDER BY corso.id_corso,edizioni.id_edizione DESC";	
};


if ($query) {
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_corso=$riga["id_corso"];
		$descrizione=$riga["descrizione"];
		$id_edizione=$riga["id_edizione"];
		$descr_edizione=$riga["descr_edizione"];
		
		$id_corso_array[]=$id_corso;
		$descrizione_array[]=$descrizione;
		$id_edizione_array[]=$id_edizione;
		$descr_edizione_array[]=$descr_edizione;
	};
};


if ($ruolo<>'staff' and $ruolo<>'admin' and ($eprof and $cod_area=='kairos_area_corsi')) {
	$query="SELECT corso.descrizione,corso.id_corso,edizioni.id_edizione,edizioni.descrizione as descr_edizione FROM corso,edizioni WHERE 
corso.id_corso=edizioni.id_corso AND 
edizioni.stato='attiva'  ORDER BY corso.id_corso,edizioni.id_edizione DESC";	
	$result=$mysqli->query($query);
	
	$corso_att="";
	$ultima_ed="";
	while ($riga=$result->fetch_array()) {
		$id_corso=$riga["id_corso"];
		$descrizione=$riga["descrizione"];
		$id_edizione=$riga["id_edizione"];
		$descr_edizione=$riga["descr_edizione"];
		
		if ($corso_att<>$id_corso) {
			$ultima_ed=$id_edizione;
		};
		
		$query_i="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_utente='$id_utente'";
		$result_i=$mysqli->query($query_i);
		$iscritto_edizione=$result_i->num_rows;
		
		$query_i="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso'  AND id_utente='$id_utente'";
		$result_i=$mysqli->query($query_i);
		$iscritto_corso=$result_i->num_rows;
		
		$prendi=false;
		if ($iscritto_corso) $prendi=true;
		
		if ($ultima_ed==$id_edizione) {
			if ($iscritto_edizione) {
				$prendi=true;
			} else {
				$prendi=false; 	
			};
		};
		$corso_att=$id_corso;
		
		if ($prendi) {
			$id_corso_array[]=$id_corso;
			$descrizione_array[]=$descrizione;
			$id_edizione_array[]=$id_edizione;
			$descr_edizione_array[]=$descr_edizione;
		};
	};
	
};


$corso_att="";
for ($i=0;$i<count($id_corso_array);$i++) {
	$id_corso=$id_corso_array[$i];
	$descrizione=$descrizione_array[$i];
	$id_edizione=$id_edizione_array[$i];
	$descr_edizione=$descr_edizione_array[$i];
	
	$tag_icona="";
	if ($ruolo<>'staff' and $ruolo<>'admin' and $cod_area=='kairos_larimart') {
		$icona=verifica_corso($id_utente,$id_corso,$id_edizione);
		if ($icona) {
			$tag_icona="<img src=\"img/forum/$icona.gif\" width=15 height=15>";
		};
	};
	
	if ($cod_area<>'kairos_larimart') {
		if ($corso_att<>$id_corso) {
			if ($corso_att) echo "<hr size=1>";
			echo "
			<span class=testopiccolo>
			<b>$descrizione</b>
			</span>
			<br>";
		};
		echo "&nbsp;&nbsp;\n";
		$label=$descr_edizione;
		if (!$label) $label=$id_edizione;
		
		echo "<span class=testopiccolo><a href=set_corso.php?id_corso=$id_corso&id_edizione=$id_edizione>$label</a>";
		echo "$tag_icona";
		echo "</span>";
		echo "<br>";
		$corso_att=$id_corso;
	} else {
		echo "<span class=testopiccolo><a href=set_corso.php?id_corso=$id_corso&id_edizione=$id_edizione>$descrizione</a>";
		echo "$tag_icona";
		echo "</span><br>";
	};
};
echo "
</td></tr>
</table>
</td></tr>
</table>
</td>
<td valign=top width=1 bgcolor=#cccccc>
<img src=\"img/pixel.gif\" width=\"1\" height=\"1\" alt=\"\" border=\"0\">
</td>
";
};

?>
<!-- FINE BOX LOGIN -->

				
	<!-- SECONDA COLONNA -->
      
 		<?php 
	
		if (!isset($kairos_cookie[0])) { 
	 		echo "<td valign=\"TOP\" width=\"60%\" align=left>";
		} else {
			echo "<td valign=\"TOP\" width=\"60%\" align=left>";
		};		
		
		
		$link_nuova="";
		if ($ruolo=='admin' or ($ruolo=='staff' and $cod_area<>'kairos_fortic')) {
			$link_nuova="[<a href=index.php?risorsa=news_crea&tipo_news=0>$stringa[nuova_news]</a>]";
		};
		
		
			echo "
			<table border=0 bgcolor=$colore_scuro width=100%>
			<tr><td height=25>
			<span class=testopiccolonegativo><b>$stringa[news_direzione]</b> $link_nuova</span>
			</td></tr>
			</table>\n";
			
			if (!$kairos_cookie[0] and $cod_area=='kairos_area_corsi') {
				echo "
				<table border=0 width=100% cellspacing=3 cellpadding=3 bgcolor=$colore_sfondo>
				<tr><td>
				<span class=testo>Per accedere a quest'area devi essere registrato ad <a href=http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com target=_blank><b>Atlante</b></a> (usa quindi gli stessi <b>ID</b> e <b>PW</b>) ed essere iscritto ad un corso online ovvero averlo frequentato ed essere abbonato ad <b>E-Prof</b>.</span>
				</td></tr></table>";
			};
			
			if (!$id_corso_s) {						
			$query="SELECT id_news,url,url_label,testo,id_utente,date_format(data_news,\"%d/%m/%Y\") as data_n,posizione FROM hp_news WHERE tipo=0 AND (id_corso IS NULL OR id_corso='') AND (id_edizione IS NULL OR id_edizione='') ORDER BY posizione DESC,data_news DESC";
			$result=$mysqli->query($query);
			
			$news = 1;
			while (($item_news=$result->fetch_array()) and $news<=5) {
				$id_news = $item_news["id_news"];
				$titolo = $item_news["url_label"];
				$url = $item_news["url"];
				$testo = $item_news["testo"];
				$id_autore=$item_news["id_utente"];
				$data_news=$item_news["data_n"];
				$posizione=$item_news["posizione"];
				$testo = ereg_replace("\n","<br>",$testo);
				$testo = parse_link($testo);	
				
				echo "
				<table border=0 width=100% cellspacing=3 cellpadding=3 bgcolor=$colore_sfondo>
				<tr><td>
				<span class=testo>$data_news";
				if (($id_autore==$id_utente) or $ruolo=='admin' ) {
					echo " - [<a href=news_delete.php?id_news=$id_news>$stringa[cancella]</a>] [<a href=index.php?risorsa=news_mod&id_news=$id_news>$stringa[modifica]</a>]";
					if ($posizione) {
						echo " - [<a href=news_noprimopiano.php?id_news=$id_news>$stringa[no_primo_piano]</a>]</span><br>";				
					} else {
						echo "</span><br>";
					};		
				} else {
					echo "</span><br>";
				};
				
				if ($url) {
					if (!eregi("^http://",$url)) {
						$url = "http://".$url;
					};
					echo "
					<span class=testo><b><a href=$url>$titolo</a></b></span>";
				} else {
					echo "
					<span class=testo><b>$titolo</b></span>";	
				};
				
				echo "</tr></td><tr><td valign=top>";
											
				echo "
				<span class=testo>$testo</span><br>";

				echo "</td></tr>
				</table>";
				echo "";		
				$news++;
			};
			};
			
			if ($id_corso_s) {
			$query="SELECT id_news,url,url_label,testo,id_utente,date_format(data_news,\"%d/%m/%Y\") as data_n,posizione FROM hp_news WHERE tipo=0 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY posizione DESC,data_news DESC";
			$result=$mysqli->query($query);
			
			$news = 1;
			while (($item_news=$result->fetch_array()) and $news<=5) {
				$id_news = $item_news["id_news"];
				$titolo = $item_news["url_label"];
				$url = $item_news["url"];
				$testo = $item_news["testo"];
				$id_autore=$item_news["id_utente"];
				$data_news=$item_news["data_n"];
				$posizione=$item_news["posizione"];
				$testo = ereg_replace("\n","<br>",$testo);
				$testo = parse_link($testo);	
				
				echo "
				<table border=0 width=100% cellspacing=3 cellpadding=3 bgcolor=$colore_sfondo>
				<tr><td>
				<span class=testo>$data_news";
				if (($id_autore==$id_utente) or $ruolo=='admin' ) {
					echo " - [<a href=news_delete.php?id_news=$id_news>$stringa[cancella]</a>] [<a href=index.php?risorsa=news_mod&id_news=$id_news>$stringa[modifica]</a>]";
					if ($posizione) {
						echo " - [<a href=news_noprimopiano.php?id_news=$id_news>$stringa[no_primo_piano]</a>]</span><br>";				
					} else {
						echo "</span><br>";
					};		
				} else {
					echo "</span><br>";
				};
				
				if ($url) {
					if (!eregi("^http://",$url)) {
						$url = "http://".$url;
					};
					echo "
					<span class=testo><b><a href=$url>$titolo</a></b></span>";
				} else {
					echo "
					<span class=testo><b>$titolo</b></span>";	
				};
				
				echo "</tr></td><tr><td valign=top>";
											
				echo "
				<span class=testo>$testo</span><br>";


				echo "</td></tr>
				</table>";

				echo "";		
				$news++;
			};
			};
	
		?>      
		
	</td>
	<!-- FINE SECONDA COLONNA -->
	
	<td valign=top width=1 bgcolor=#cccccc >
	<img src="img/pixel.gif" width="1" height="1" alt="" border="0">
	</td>


	
		<?php 
			if (!isset($kairos_cookie[0])) { 
	 			echo "<td valign=\"TOP\" width=\"30%\" align=left>";
			} else {
				echo "<td valign=\"TOP\" width=\"30%\" align=left>";
			};
			
			echo "
			<table border=0 bgcolor=$colore_scuro width=100%>
			<tr><td  height=25>
			<span class=testopiccolonegativo><b>$stringa[news_iscritti]</b></span>
			</td></tr>
			</table>\n";
			
			$db = mysql_connect("localhost",$DBUSER,$DBPWD);
			mysql_select_db($DBASE,$db);	
			
			$query="SELECT id_news,url,url_label,testo,id_utente,date_format(data_news,\"%d/%m/%Y\") as data_n FROM hp_news where tipo=1 AND id_corso='' AND id_edizione='' ORDER BY data_news DESC";
			$result=$mysqli->query($query);
			
			$news = 1;
			while (($item_news=$result->fetch_array()) and $news<=5) {
				$id_news = $item_news["id_news"];
				$titolo = $item_news["url_label"];
				$url = $item_news["url"];
				$testo = $item_news["testo"];
				$id_autore=$item_news["id_utente"];
				$data_news=$item_news["data_n"];
			
				$testo = ereg_replace("\n","<br>",$testo);
				$testo = parse_link($testo);	
				
				echo "
				<table border=0 width=100% cellspacing=3 cellpadding=3 bgcolor=$colore_sfondo>
				<tr><td>
				<span class=testo>";
				
				echo "
				<b><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">($id_autore)</a></b>
				";				
				
				echo " - $data_news";
				if (($id_autore==$id_utente) or $ruolo=='admin' ) {
					echo " - [<a href=news_delete.php?id_news=$id_news>$stringa[cancella]</a>] [<a href=index.php?risorsa=news_mod&id_news=$id_news>$stringa[modifica]</a>]";				
				} else {
					echo "<br>";
				};
				
				if ($url) {
					if (!eregi("^http://",$url)) {
						$url = "http://".$url;
					};
					echo "
					<b><a href=$url target=_blank>$titolo</a></b>";
				} else {
					echo "
					<b>$titolo</b>";	
				};

				echo "
				<br>$testo<br>";

				echo "</span><br>";		
				echo "</td></tr>
				</table>";
				
				$news++;
			};		
			
			if ($id_corso_s) {
			$query="SELECT id_news,url,url_label,testo,id_utente,date_format(data_news,\"%d/%m/%Y\") as data_n FROM hp_news where tipo=1 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY data_news DESC";
			$result=$mysqli->query($query);
			
			$news = 1;
			while (($item_news=$result->fetch_array()) and $news<=5) {
				$id_news = $item_news["id_news"];
				$titolo = $item_news["url_label"];
				$url = $item_news["url"];
				$testo = $item_news["testo"];
				$id_autore=$item_news["id_utente"];
				$data_news=$item_news["data_n"];
			
				$testo = ereg_replace("\n","<br>",$testo);
				$testo = parse_link($testo);	
				
				echo "
				<table border=0 width=100% cellspacing=3 cellpadding=3 bgcolor=$colore_sfondo>
				<tr><td>
				<span class=testo>";
				
				echo "
				<b><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">($id_autore)</a></b>
				";				
				
				echo " - $data_news";
			if (($id_autore==$id_utente) or $ruolo=='admin' ) {
					echo " - [<a href=news_delete.php?id_news=$id_news>$stringa[cancella]</a>] [<a href=index.php?risorsa=news_mod&id_news=$id_news>$stringa[modifica]</a>]<br>";				
				} else {
					echo "<br>";
				};
				
				if ($url) {
					if (!eregi("^http://",$url)) {
						$url = "http://".$url;
					};
					echo "
					<b><a href=$url target=_blank>$titolo</a></b>";
				} else {
					echo "
					<b>$titolo</b>";	
				};

				echo "
				<br>$testo<br>";

				echo "</span><br>";		
				echo "</td></tr>
				</table>";

				
				$news++;
			};	
		};
			echo "		
		<br><br>
		<table border=0 cellspacing=0 cellpadding=5 bgcolor=$colore_sfondo>	
		<tr><td><span class=testo><a href=index.php?risorsa=news_crea&tipo_news=1><b>$stringa[modifica]</b></a> $stringa[modifica_sezione]</span></td></tr>
		</table>	
		";
		
		?>
	</td>
  </tr>
</table>

<!-- FINE CONTENUTO DELLA PAGINA -->

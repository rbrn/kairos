<?php

	echo "
	<table border=0 width=100% cellspacing=10 cellpadding=0>
	<tr>
	<td valign=top width=100% class=titolodot>".strtoupper($stringa[calendario_eventi])."</td>
	</tr>
	<tr><td>
	";
	
	echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

	
	$monthname = date('F', mktime(0,0,0,$month,1,$year));
	$monthname = $nomemese[$monthname];
	
	$lastseconds = mktime(0,0,0,$month,$day,$year)-(24*60*60);

        $lastday = date('j', $lastseconds);

        $lastmonth = date('m', $lastseconds);

        $lastyear = date('Y', $lastseconds);



        $nextseconds = mktime(0,0,0,$month,$day,$year)+(24*60*60);

        $nextday = date('j', $nextseconds);

        $nextmonth = date('m', $nextseconds);

        $nextyear = date('Y', $nextseconds);



		echo "<table align=\"center\"><tr>";
		
 		echo "<td>
<a href=\"index.php?risorsa=display&day=$lastday&month=$lastmonth&year=$lastyear\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back1','','img/ico_indietro_over.gif',1)\"><img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back1\"></a></td>";
	
	if ($ruolo=='staff' or $ruolo=='admin') {
    	echo "<td>
<a href=\"index.php?risorsa=operate&day=$day&month=$month&year=$year&action=NuovoEvento\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_new1','','img/ico_cal_nuovo_over.gif',1)\"><img border=\"0\" src=\"img/ico_cal_nuovo.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[nuovo_evento]\" name=\"img_new1\"></a></td>";
	} else {
		echo "<td></td>";
	};

	echo "<td>
<a href=\"index.php?risorsa=display&day=$nextday&month=$nextmonth&year=$nextyear\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_fw1','','img/ico_avanti_over.gif',1)\"><img border=\"0\" src=\"img/ico_avanti.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[avanti]\" name=\"img_fw1\"></a></td>";

		echo "</tr></table><br>";

	echo "
	<table width=80% cellpadding=1 cellspacing=0 border=0 bgcolor=\"$colore_scuro\"  align=\"center\">
	<tr><td>
	
	<table width=100% cellpadding=5 cellspacing=2 border=0 bgcolor=\"white\">
	<tr>";
	if ($ruolo=='staff' or $ruolo=='admin') {
		$colspan=4;
	} else {
		$colspan=2;
	};
	
	echo "
	<td colspan=$colspan bgcolor=\"$colore_scuro\" align=\"center\">
	<span class=testo><b><center>$day $monthname $year</b></span>
	</td>
	</tr>";
	
	echo "
	<tr bgcolor=\"$colore_sfondo_neutro\">
	<td width=20><span class=testopiccolo><b>$stringa[tempo]</b></span></td>
	<td><span class=testopiccolo><b>$stringa[oggetto]</b></span></td>
	</tr>";
			
	if ($id_corso_s) {
		$query = $mysqli->query("SELECT * FROM calendario WHERE data >= \"$year-$month-$day 00:00:00\" AND data <= \"$year-$month-$day 23:59:59\" AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY data");
	} else {
		$query = $mysqli->query("SELECT * FROM calendario WHERE data >= \"$year-$month-$day 00:00:00\" AND data <= \"$year-$month-$day 23:59:59\" AND id_corso='' AND id_edizione='' ORDER BY data");
	};



	while ($row = $query->fetch_array())

	{

		ereg("([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})",$row[data],$data);

		$giorno = $data[3];
		$mese = $data[2];
		$anno = $data[1];
		$ora = $data[4];
		$minuti = $data[5];
		$id=$row[id_cal];
		
		echo "
			<tr bgcolor=\"$colore_sfondo_neutro\">
			<td width=20><span class=testopiccolo>$ora:$minuti</b></span></td>
			<td><span class=testopiccolo><b>".stripslashes($row[oggetto])."</b><br>".stripslashes($row[descrizione])."</span></td>";
			
		if ($ruolo=='staff' or $ruolo=='admin') {
			echo "<td width=20><a href=index.php?risorsa=operate&day=$day&month=$month&year=$year&action=".$stringa[modifica]."&id=".$row[id_cal]." onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id\"></a></td>";

			echo "<td width=20><a href=index.php?risorsa=operate&day=$day&month=$month&year=$year&action=".$stringa[cancella]."&id=".$row[id_cal]." onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id\"></a></td>\n";
			
		
		};
		echo "</tr>";
	}

	echo "</td></tr></table>";
	echo "</td></tr></table>";
	
	echo "</td></tr></table>";
	echo "<br>";
?>

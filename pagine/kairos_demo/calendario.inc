<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";
	$num_ev=2;
	$currentday = date("j", time());
	$currentmonth = date("m", time());
	$currentyear = date("Y", time());

	$data_oggi=$currentyear."-".$currentmonth."-".$currentday." 23:59:59";
	
	$lastday = 1;
	if (!$month)
	{
		$month = date("m", time());
		$year = date("Y", time());
	}


	echo "
	<table border=0 width=100% cellspacing=10 cellpadding=0>
	<tr>
	<td valign=top width=100% class=titolodot>".strtoupper($stringa[calendario_eventi])."</td>
	</tr>
	<tr><td>
	";
	
	echo "<table border=0 width=100%>";
	echo "<tr>";
	
	echo "<td valign=top width=300>";
	if ($id_corso_s) {
	echo "
	<table border=0 width=100% cellspacing=0 cellpadding=5  bgcolor=$colore_sfondo>
	
	";
	$query2 = "SELECT oggetto,data FROM calendario WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY data";
	$result2=$mysqli->query($query2);

	while ($riga=$result2->fetch_array()) {
		$colore=$colore_sfondo;
		$data=$riga["data"];
		if ($data<$data_oggi) $colore=$colore_sfondo_neutro;
		ereg("^(.+)-(.+)-(.+) (.+)$",$data,$parti);
		$data=$parti[3]."/".$parti[2]."/".$parti[1];
		$oggetto=stripslashes($riga["oggetto"]);
		echo "<tr bgcolor=$colore>
		<td valign=top><span class=testopiccolo>$data</span></td>
		<td valign=top><span class=testopiccolo>$oggetto</span></td>
		</tr>";
	};
	echo "</table>";
	};
	echo "</td>";
	
	echo "<td valign=top>";	
	echo "<center><p><span class=testo><b>";
	$monthname = date('F', mktime(0,0,0,$month,1,$year));
	$monthname = $nomemese[$monthname];	
	echo $monthname;
	echo " $year</b></span><p>";
	
	$firstday = date( 'w', mktime(0,0,0,$month,1,$year));
	while (checkdate($month,$lastday,$year))
	{
	        $lastday++;
	}      


	$nextmonth = $month+1;
	$nextyear = $year;
	if ($nextmonth == 13)
	{
		$nextmonth = 1;
		$nextyear = $year + 1;
	}

	$lastmonth = $month-1;
	$lastyear = $year;

	if ($lastmonth == 0)
	{
		$lastmonth = 12;
		$lastyear = $year-1;
	}

	echo "<table><tr>";

	echo "<td>
<a href=\"index.php?risorsa=calendario&month=$lastmonth&year=$lastyear\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back1','','img/ico_indietro_over.gif',1)\"><img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back1\"></a></td>";
	
	if ($ruolo=='staff' or $ruolo=='admin') {
    	echo "<td>
<a href=\"index.php?risorsa=operate&month=$month&year=$year&action=NuovoEvento\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_new1','','img/ico_cal_nuovo_over.gif',1)\"><img border=\"0\" src=\"img/ico_cal_nuovo.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[nuovo_evento]\" name=\"img_new1\"></a></td>";
	} else {
		echo "<td></td>";
	};

	echo "<td>
<a href=\"index.php?risorsa=calendario&month=$nextmonth&year=$nextyear\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_fw1','','img/ico_avanti_over.gif',1)\"><img border=\"0\" src=\"img/ico_avanti.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[avanti]\" name=\"img_fw1\"></a></td>";

	
	echo "</tr></table>";


	echo "
	<table width=80% cellpadding=1 cellspacing=0 border=0 bgcolor=\"$colore_scuro\">
	<tr><td>
	
	<table width=100% cellpadding=5 cellspacing=2 border=0 bgcolor=\"white\">";
	echo "<tr>
	<td width=14% bgcolor=\"$colore_scuro\" align=\"center\"><span class=testonegativo><b>$stringa[domenica]</b></span></td>
	<td width=14% bgcolor=\"$colore_scuro\" align=\"center\"><span class=testonegativo><b>$stringa[lunedi]</b></span></td>
	<td width=14% bgcolor=\"$colore_scuro\" align=\"center\"><span class=testonegativo><b>$stringa[martedi]</b></span></td>
	<td width=14% bgcolor=\"$colore_scuro\" align=\"center\"><span class=testonegativo><b>$stringa[mercoledi]</b></span></td>
	<td width=14% bgcolor=\"$colore_scuro\" align=\"center\"><span class=testonegativo><b>$stringa[giovedi]</b></span></td>
	<td width=16% bgcolor=\"$colore_scuro\" align=\"center\"><span class=testonegativo><b>$stringa[venerdi]</b></span></td>
	<td width=14% bgcolor=\"$colore_scuro\" align=\"center\"><span class=testonegativo><b>$stringa[sabato]</b></span></td>
	";
	echo "</tr>";



	for ($i=0; $i<7; $i++)

	{
		if ($i < $firstday)
		{
			echo "<td></td>";
		}
		else
		{
			$thisday = ($i+1)-$firstday;
			if ($currentyear > $year)
			{
				echo "<td valign=top bgcolor=\"$colore_sfondo_neutro\" align=\"center\">";
			}
			else if ($currentmonth > $month && $currentyear == $year)
			{
				echo "<td valign=top bgcolor=\"$colore_sfondo_neutro\" align=\"center\">";
			}
			else if ($currentmonth == $month && $currentday > $thisday && $currentyear == $year)
			{
				echo "<td valign=top bgcolor=\"$colore_sfondo_neutro\" align=\"center\">";
			}
			else
			{
				if ($nextday==$currentday and $month==$currentmonth) {
					echo "<td valign=top bgcolor=\"$colore_sfondo\" align=\"center\">";		
				} else {
						echo "<td valign=top bgcolor=\"$colore_sfondo_neutro\" align=\"center\">";
				}
			}

			echo "<span class=sottotitolopagina><a href=index.php?risorsa=display&day=$thisday&month=$month&year=$year>$thisday</a></span>";

			if ($ruolo=='staff' or $ruolo=='admin') {
			echo "<br><br><a href=\"index.php?risorsa=operate&day=$thisday&month=$month&year=$year&action=NuovoEvento\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_new_$thisday','','img/ico_cal_nuovo_p_over.gif',1)\"><img border=\"0\" src=\"img/ico_cal_nuovo_p.gif\" width=\"13\" height=\"10\" align=\"middle\" alt=\"$stringa[nuovo_evento]\" name=\"img_new_$thisday\"></a>";

			};

			echo "<br><br>";

			
			if ($id_corso_s) {
				$query2 = $mysqli->query("SELECT oggetto FROM calendario WHERE data >= \"$year-$month-$thisday 00:00:00\" and data <= \"$year-$month-$thisday 23:59:59\" AND  id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY data");
			} else {
				$query2 = $mysqli->query("SELECT oggetto FROM calendario WHERE data >= \"$year-$month-$thisday 00:00:00\" and data <= \"$year-$month-$thisday 23:59:59\" AND id_corso='' AND id_edizione='' ORDER BY data");
			};

			for ($j = 0; $j<$query2->num_rows; $j++)
			{
				$results = $query2->fetch_array();
				if ($results["oggetto"])
				{
					echo "<span class=testopiccolo>".stripslashes($results[oggetto])."</span><br>";
				}
			}

			if ($query2->num_rows < $num_ev)
			{
				for ($j=0; $j<($num_ev-$query2->num_rows); $j++)
					echo "<br>";
			}
			echo "</td>";
		}
	}

	echo "</tr>\n";
	$nextday = ($i+1)-$firstday;

	for ($j = 0; $j<5; $j++)
	{
		echo "<tr>";
		for ($k = 0; $k<7; $k++)
		{
			if ($nextday < $lastday)
			{
				if ($currentyear > $year)
	            {       
					echo "<td valign=top bgcolor=\"$colore_sfondo_neutro\" align=\"center\">";

                }
				else if ($currentmonth > $month && $currentyear == $year)
					{       
						echo "<td valign=top bgcolor=\"$colore_sfondo_neutro\" align=\"center\">";
					}               

                    else if ($currentmonth == $month && $currentday > $nextday && $currentyear == $year)
					{
						echo "<td valign=top bgcolor=\"$colore_sfondo_neutro\" align=\"center\">";

                    }
					else    
					{
						if ($nextday==$currentday and $month==$currentmonth) {
							echo "<td valign=top bgcolor=\"$colore_sfondo\" align=\"center\">";		} else {
							echo "<td valign=top bgcolor=\"$colore_sfondo_neutro\" align=\"center\">";
						}
				}

				echo "<span class=sottotitolopagina><a href=index.php?risorsa=display&day=$nextday&month=$month&year=$year>$nextday</a></span>";

			if ($ruolo=='staff' or $ruolo=='admin') {

				echo "<br><br><a href=\"index.php?risorsa=operate&day=$nextday&month=$month&year=$year&action=NuovoEvento\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_new_$nextday','','img/ico_cal_nuovo_p_over.gif',1)\"><img border=\"0\" src=\"img/ico_cal_nuovo_p.gif\" width=\"13\" height=\"10\" align=\"middle\" alt=\"$stringa[nuovo_evento]\" name=\"img_new_$nextday\"></a>";

			};

			echo "<br><br>";
			
			if ($id_corso_s) {
				$query3 = $mysqli->query("SELECT oggetto FROM calendario WHERE data >= \"$year-$month-$nextday 00:00:00\" AND data <= \"$year-$month-$nextday 23:59:59\"   AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY data");
			} else {
				$query3 = $mysqli->query("SELECT oggetto FROM calendario WHERE data >= \"$year-$month-$nextday 00:00:00\" AND data <= \"$year-$month-$nextday 23:59:59\"  AND id_corso='' AND id_edizione='' ORDER BY data");
			}

			for ($i = 0; $i<$query3->num_rows+$num_ev; $i++)

			{
				$results2 = $query3->fetch_array();
				if ($results2["oggetto"])
				{
					echo "<span class=testopiccolo>".stripslashes($results2[oggetto])."</span><br>";
				}
				else if ($i < $num_ev)
				{
					echo "<br>";
				}

				}
				echo "</td>";
				$nextday++;
			}
		}
		echo "</tr>\n";
	}

	echo "</table>";
	
	echo "</td></tr></table>";





	echo "<table><tr>";

	echo "<td>
<a href=\"index.php?risorsa=calendario&month=$lastmonth&year=$lastyear\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back2','','img/ico_indietro_over.gif',1)\"><img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back2\"></a></td>";
	
	if ($ruolo=='staff' or $ruolo=='admin') {
    	echo "<td>
<a href=\"index.php?risorsa=operate&month=$month&year=$year&action=NuovoEvento\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_new2','','img/ico_cal_nuovo_over.gif',1)\"><img border=\"0\" src=\"img/ico_cal_nuovo.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[nuovo_evento]\" name=\"img_new2\"></a></td>";
	} else {
		echo "<td></td>";
	};

	echo "<td>
<a href=\"index.php?risorsa=calendario&month=$nextmonth&year=$nextyear\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_fw2','','img/ico_avanti_over.gif',1)\"><img border=\"0\" src=\"img/ico_avanti.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[avanti]\" name=\"img_fw2\"></a></td>";
	
	echo "</tr></table>";

	echo "</td>";
	
	echo "</tr>";
	echo "</table>";
	
	echo "</td></tr></table><br>";
echo "                </div>
            </div>
        </div>
    </div>
</div>";

?>

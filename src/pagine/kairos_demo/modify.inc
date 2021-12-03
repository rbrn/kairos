<?php
	echo "
	<p><span class=titolopagina>$stringa[calendario_eventi]</span></p>";
	$tablename = date('Fy', mktime(0,0,0,$month,1,$year));
	$monthname = date('F', mktime(0,0,0,$month,1,$year));
	$monthname = $nomemese[$monthname];

	echo "<p><span class=testo><b><center>$day $monthname $year</center></b></span></p>";

	echo "<font size=3>";




	
	if ($id_corso_s) {
		$query = $mysqli->query("SELECT * FROM calendario WHERE data >= \"$year-$month-$day 00:00:00\" AND data <= \"$year-$month-$day 23:59:59\" AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY data");
	} else {
		$query = $mysqli->query("SELECT * FROM calendario WHERE data >= \"$year-$month-$day 00:00:00\" AND data <= \"$year-$month-$day 23:59:59\" AND id_corso='' AND id_edizione='' ORDER BY data");
	};



	echo "<form method=post action=index.php>

		<input type=hidden name=risorsa value='operate'>

		<table cellpadding=5 cellspacing=5 border=1 width=80%>

		<tr><td><span class=testo><b>$stringa[seleziona]</b></span></td><td><span class=testo><b>$stringa[tempo]</b></span></td><td><span class=testo><b>$stringa[oggetto]</b></span></td>

		<td><span class=testo><b>$stringa[descrizione]</b></span></td></tr>";

	while ($row = $query->fetch_array())

	{

		$i++;

		ereg("([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})",$row[data],$data);

		$giorno = $data[3];

		$mese = $data[2];

		$anno = $data[1];

		$ora = $data[4];

		$minuti = $data[5];		

		echo "<tr><td><input type=radio name=id value=$row[id_cal]></td>

			<td><span class=testo>$ora:$minuti</span></td>

			<td><span class=testo>$row[oggetto]</span></td><td><span class=testo>$row[descrizione]</span></td></tr>";

	}

	echo "</table><p>

		<input type=hidden name=day value=$day>

		<input type=hidden name=month value=$month>

		<input type=hidden name=year value=$year>

		<input type=submit name=action value=\"$stringa[cancella]\">

		<input type=submit name=action value=\"$stringa[modifica]\">

		</form>

		<span class=testo><a href=index.php?risorsa=display&day=$day&month=$month&year=$year>[".$stringa[indietro]."]</a></span>";

?>

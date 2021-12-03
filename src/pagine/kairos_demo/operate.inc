<?php
	echo "
	<table border=0 width=100% cellspacing=10 cellpadding=0>
	<tr>
	<td valign=top width=100% class=titolodot>".strtoupper($stringa[calendario_eventi])."</td>
	</tr>
	<tr><td>
	";
	
	/*
	echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
";
*/

	$lastday = 1;
	while (checkdate($month,$lastday,$year))
	{
		$lastday++;
	}


	switch ($action)
	{
		case $stringa[cancella]:
			if (!$id)
			{
				echo "<p><span class=testo>$stringa[no_selezione]</span></p>";
				break;

			}


			$mysqli->query("DELETE FROM calendario WHERE id_cal = '$id'");

			echo "<p><span class=testo>$stringa[evento_cancellato]</span></p>";

			break;



		case $stringa[modifica]:

			if (!$id)
			{
				echo "<p><span class=testo>$stringa[no_modifica]</span></p>";
				break;
			}

			$query = $mysqli->query("SELECT *, RIGHT(data, 8) AS thetime, SUBSTRING(data FROM 9 FOR 2) AS theday FROM calendario WHERE id_cal = '$id'");
			$row = $query->fetch_array();
			$row[descrizione] = str_replace("<br>", "", $row[descrizione]);
			$row[descrizione] = htmlentities(stripslashes($row[descrizione]));
			$row[oggetto] = htmlentities(stripslashes($row[oggetto]));
			
			echo "<form method=post action=index.php>
				<input type=hidden name=risorsa value='operate'>
				<input type=hidden name=id value='$row[id_cal]'>
				
				<span class=testo><b>$stringa[nuovo_evento]</b></span>
				<br><br>
				<table>

				<tr>

					<td align=right><span class=testo><b>$stringa[giorno]</b></span></td>

					<td><select name=day size=1>";



			for ($i=1; $i<$lastday; $i++)
			{
				if ($i == $row[theday])
					echo "<option value=$i selected>$i</option>";
				else
					echo "<option value=$i>$i</option>";
			}
			echo "</select><select size=1 name=month>";
			for ($i=1; $i<13; $i++)
			{
				$nm = date("F", mktime(0,0,0,$i,1,$year));
				$nm = $nomemese[$nm];
				
				if ($i == $month)
					echo "<option value=$i selected>$nm</option>";
				else
					echo "<option value=$i>$nm</option>";
			}
			echo "</select><select size=1 name=year>";
			for ($i=$year-2; $i<$year+5; $i++)
			{
				if ($i == $year)
					echo "<option value=$i selected>$i</option>";
				else
					echo "<option value=$i>$i</option>";
			}

			echo "</select></tr>
				<tr><td align=right><span class=testo><b>$stringa[tempo] (hh:mm:ss)</b></span></td>
				<td><input type=text name=time value='$row[thetime]'></td></tr>

				<tr><td align=right><span class=testo><b>$stringa[oggetto]</b></td>
				<td><input type=text name=subject size=40 value=\"$row[oggetto]\"></td></tr>

				<tr><td align=right valign=top><span class=testo><b>$stringa[descrizione]</b></span></td>

				<td><textarea wrap=virtual rows=5 cols=50 name=description>$row[descrizione]</textarea></td></tr>

				</table>
				<input type=hidden name=action value=Addsucker>
				<input type=hidden name=modify value=Modify>
				<input type=submit value=\"$stringa[ok]\">
				</form>";    
			break;



		case "NuovoEvento":
			$query = $mysqli->query("SELECT max(id_cal) as id FROM calendario");
			if ($query)
			{
				$result = $query->fetch_array();
				$result["id_cal"]++;
			}
			else
			{
				$result["id_cal"] = 0;
			}
			echo "<form method=post action=index.php>
				<input type=hidden name=risorsa value='operate'>
				<input type=hidden name=id value=$result[id_cal]>
				
				<span class=testo><b>$stringa[nuovo_evento]</b></span>
				<br><br>
				<table>

			<tr><td align=right><span class=testo><b>$stringa[giorno]</b></span></td>

					<td><select name=day size=1>";

			for ($i=1; $i<$lastday; $i++)

			{

				if ($i == $day)

					echo "<option value=$i selected>$i</option>";

				else    

					echo "<option value=$i>$i</option>";

			}

			echo "</select><select size=1 name=month>";

			for ($i=1; $i<13; $i++)

			{

				$nm = date("F", mktime(0,0,0,$i,1,$year));

				$nm = $nomemese[$nm];

				

				if ($i == $month)

					echo "<option value=$i selected>$nm</option>";

				else

					echo "<option value=$i>$nm</option>";

			}

			echo "</select><select size=1 name=year>";

			for ($i=$year-2; $i<$year+5; $i++)

			{

				if ($i == $year)

					echo "<option value=$i selected>$i</option>";

				else

					echo "<option value=$i>$i</option>";

			}

			echo "</select></td></tr>

					<tr><td align=right><span class=testo><b>$stringa[tempo] (hh:mm:ss)</b></span></td>

					<td><input type=text name=time></td></tr>

					<tr><td align=right><span class=testo><b>$stringa[oggetto]</b></span></td>

					<td><input type=text size=40 name=subject></td></tr>

					<tr><td align=right valign=top><span class=testo><b>$stringa[descrizione]</b></td>

					<td><textarea wrap=virtual rows=5 cols=50 name=description></textarea></td></tr>
					
					<tr><td><input type=hidden name=action value=Addsucker>

				<input type=submit value=\"$stringa[ok]\"></td></tr>
				</table>

				

				</form>";

			break;



		case "Addsucker":

			if ($modify)
			{
                $mysqli->query("DELETE FROM calendario WHERE id_cal='$id'");
				str_replace("<br>", "", $description);
			}
			
			$description=str_replace("\n", "<br>",$description);
			$description = addslashes($description);
			$subject = addslashes($subject);

			$temp = $mysqli->query("INSERT INTO calendario (data, oggetto, descrizione,id_corso,id_edizione,id_gruppo) VALUES ('$year-$month-$day $time', '$subject', '$description','$id_corso_s','$id_edizione_s','$id_gruppo_s')");

			if ($temp != 0)

				echo "<p><span class=testo>$stringa[evento_confermato]</span></p>";

			else

			{

				echo mysql_error();

			}



			break;

	}



	echo "<p><form method=get action=index.php><input type=submit value='$stringa[torna_mese]'>
<input type=hidden name=month value=$month>
<input type=hidden name=year value=$year>
<input type=hidden name=risorsa value='calendario'>
</form></p>";

	echo "</td></tr></table>";
?>

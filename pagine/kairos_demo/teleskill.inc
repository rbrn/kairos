<?php
require "./teleskill/teleskill.php";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr>";
echo "
<td valign=top width=67% class=titolodot>VIDEOCONFERENZA</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=30%>&nbsp;</td>";
echo "</tr>";

echo "<tr><td valign=top width=67%>";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

echo "	
<p>
<span class=testopiccolo>Stanze di videoconferenza attive</span>";

if ($ruolo=="admin" or $ruolo=="staff") {
	echo " <span class=testopiccolo>[<a href=index.php?risorsa=teleskill_nuova>Crea nuova stanza</a>]</span>";
}

echo "
</p>
";

echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr>
<td valign=top>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
<tr><td>
";

$id_utente=$kairos_cookie[0];
//$ruolo=ruolo_utente($id_utente);

$ts=new Teleskill();
$ts->deleteOldRoom();

$res=$ts->RoomList($id_corso_s,$id_edizione_s);
if ($res) {
	echo "<table border=0 cellpadding=5 width=100%>";
	echo "<tr>
	<td><span class=testopiccolo><b>Titolo</b></span></td>
	<td><span class=testopiccolo><b>Intervallo di apertura</b></td><td>&nbsp;</td></tr>";
	while ($riga=$ts->nextRow($res)) {
		$roomid=$riga['roomid'];
		$accedi=false;
		$level=1;
		if ($riga['userid']==$kairos_cookie[0]) $level=2;
		if ($ts->isRoomActive($roomid)) {
			$res_login=$ts->loginIntoRoom($roomid,$level,$id_utente,$id_utente,"");
			$accedi=true;
		};
		
		ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$riga['start_date'],$parti0);
		ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$riga['end_date'],$parti1);
		
		$data=$parti0[4].":".$parti0[5]." - ".$parti1[4].":".$parti1[5]." (".$parti1[3]."/".$parti1[2]."/".$parti1[1].")";
		echo "<tr>";
		echo "<td><span class=testopiccolo>".$riga['title']."</span></td>";
		echo "<td><span class=testopiccolo>".$data."</span></td>";
		if ($accedi and !$res_login[errorcode])  {
			$url=$res_login['url'];
			echo "<td><span class=testopiccolo>[<a href=\"#\" 
								onclick=\"window.open('$url', 'TeleSkill', 'width=1000,height=700,toolbar=no,menubar=no,directories=no,resizable=yes,scrollbar=yes'); return false;\">Accedi</a>]</span></td>";
		} else {
			echo "<td>&nbsp;</td>";
		}	
		
		echo "</tr>";
			
	}
	echo "</table>";

}	
echo "
</td></tr>
</table>
</td></tr>
</table>";

echo "
</td></tr>
</table>";

echo "</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=30%>";


echo "</td></tr></table>";



echo "
</td></tr>
</table>";

echo "
</td></tr>
</table>";
?>

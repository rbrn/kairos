<?php
$query="SELECT corso.id_corso,corso.descrizione,edizioni.id_edizione FROM corso,edizioni WHERE 
corso.id_corso=edizioni.id_corso AND edizioni.stato='attiva' AND edizioni.autoiscrizione='on' ORDER BY id_corso";
$result=$mysqli->query($query);
if ($result->num_rows) {
echo "
</table>
<table border=0 width=100%>
<TR>
<TD align=left colspan=2 valign=top> 
<hr size=1>
</td>
</tr>
<TR>
<TD align=left colspan=2 valign=top> 
<span class=testopiccolo><b>$stringa[iscriviti_corsi]</b></span>
</td>
</tr>
<TR>
<TD align=left colspan=2 valign=top> 
<hr size=1>
</td>
</tr>
";

while ($riga=$result->fetch_array()) {
	$id_corso = $riga["id_corso"];
	$descrizione = $riga["descrizione"];
	$id_edizione=$riga["id_edizione"];
	
	$query_g="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' ORDER BY id_gruppo";
	$result_g=$mysqli->query($query_g);
	$elenco_gruppi="";
	while ($riga_g=$result_g->fetch_array()) {
		$id_gruppo=$riga_g["id_gruppo"];
		$descrizione_g=$riga_g["descrizione"];
		$elenco_gruppi .= "<option value=\"$id_corso $id_edizione $id_gruppo\">$descrizione_g</option>";
	};
	
	echo "
	<tr>
	<td valign=top align=right><input type=checkbox name=id_c[] value=\"$id_corso $id_edizione\" checked> <span class=testopiccolo>$descrizione ($id_edizione)</span></td>
	<td valign=top><span class=testopiccolo>$stringa[gruppo]:</span><select name=id_g[]>$elenco_gruppi</select></td>
	</tr>";
};
echo "
<TR>
<TD align=left colspan=2 valign=top> 
<hr size=1>
</td>
</tr>";
	
};
?>

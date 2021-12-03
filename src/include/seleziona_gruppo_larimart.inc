<?php

$id_corso="larimart";
$id_edizione="2003";

$query_g="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' ORDER BY id_gruppo";
$result_g=$mysqli->query($query_g);
$elenco_gruppi="";
while ($riga_g=$result_g->fetch_array()) {
	$id_gruppo=$riga_g["id_gruppo"];
	$descrizione_g=$riga_g["descrizione"];
	$elenco_gruppi .= "<option value=\"$id_gruppo\">$descrizione_g</option>";
};
	
echo "
<tr>
<td valign=top align=right><span class=testopiccolo><b>Gruppo:</b></span></td>
<td valign=top><select name=id_gruppo_reg>$elenco_gruppi</select></td>
</tr>";

?>

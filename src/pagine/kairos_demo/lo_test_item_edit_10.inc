<?php

$query="SELECT * FROM lo_test_item_cruciverba WHERE id_item='$id_item'";
$result=$mysqli->query($query);
if (!$result->num_rows) {
	$query="INSERT INTO lo_test_item_cruciverba SET id_item='$id_item',larghezza=0,altezza=0";
	$result=$mysqli->query($query);
	$num_orz=0;
	$num_ver=0;
} else {
	$riga=$result->fetch_array();
	$num_orz=$riga["larghezza"];
	$num_ver=$riga["altezza"];
};
echo "
<form action=lo_test_item_cruciverba_op.php method=post>
<input type=\"hidden\" name=\"id_item\" value=\"$id_item\">
<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">
<table border=0>
<tr><td align=right><span class=testopiccolo><b>$stringa[num_caselle_orz]</b>: </span></td><td><input type=\"text\" name=\"larghezza\" size=\"05\" value=\"$num_orz\"></td></tr>
<tr><td align=right><span class=testopiccolo><b>$stringa[num_caselle_ver]</b>: </span></td><td><input type=\"text\" name=\"altezza\" size=\"05\" value=\"$num_ver\"> <input type=\"submit\" value=\"Ok\"></td></tr>
</table>
</form>
";

echo "<table border=1 cellspacing=0 cellpadding=0>";
echo "<tr bgcolor=\"#ffffcc\">";
echo "<td width=\"19\" height=\"21\" align=\"middle\">&nbsp;</td>";
for ($j=0;$j<$num_orz;$j++) {
	$j1=$j+1;
	echo "<td width=\"19\" height=\"21\" align=\"center\"><span class=\"testopiccolo\">$j1</span></td>";
};
echo "</tr>";
	
for ($i=0;$i<$num_ver;$i++) {
	echo "<tr>";
	$i1=$i+1;
	echo "<td width=\"19\" height=\"21\" align=\"center\" bgcolor=\"#ffffcc\"><span class=\"testopiccolo\">$i1</span></td>";
	for ($j=0;$j<$num_orz;$j++) {
		$pos=$i*$num_orz+$j+1;
		$query="SELECT * FROM lo_test_item_opzioni_cruciverba WHERE id_item='$id_item' AND posizione='$pos'";
		$result=$mysqli->query($query);
		if ($result->num_rows) {
			$riga=$result->fetch_array();
			$etichetta=$riga["etichetta"];
			if ($etichetta=="-1") {
				echo "<td width=\"19\" height=\"21\" bgcolor=\"black\">&nbsp;</td>";
			} else {
				echo "<td width=\"19\" height=\"21\"><span class=\"testopiccolo\">$etichetta</span></td>";
			};
		
		} else {
			echo "<td width=\"19\" height=\"21\">&nbsp;</td>";
		};
	};
	echo "</tr>";
};
echo "</table>";


if ($ruolo=='admin' or $id_utente==$id_editor) {	
echo "<p><span class=testopiccolo><a href=\"index.php?risorsa=lo_test_item_opzione_cruciverba_add&id_item=$id_item&risorsa_padre=$risorsa_padre\"
>$stringa[nuova_definizione]</a>&nbsp;&nbsp;<a href=\"index.php?risorsa=lo_test_item_opzione_cruciverba_add&id_item=$id_item&risorsa_padre=$risorsa_padre&ope=2\">caselle nere</a></span></p>";
};


echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";


echo "<tr>
<td width=400 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[definizioni]</b></span></td>";

echo "
<td width=50 bgcolor=\"$colore_scuro\"></td>
<td width=50 bgcolor=\"$colore_scuro\"></td>
</tr>
\n";

$colore=$colore_sfondo;
$query="SELECT * FROM lo_test_item_opzioni_cruciverba WHERE id_item='$id_item' ORDER BY etichetta,verso,posizione";
$result=$mysqli->query($query);

while ($opzione = $result->fetch_array()) {
	$id_item_opzione=$opzione[id_item_opzione];
	$posizione=$opzione[posizione];
	$etichetta=$opzione[etichetta];
	$verso="(".$opzione[verso].")";
	$definizione=htmlentities($opzione[definizione]);
	$riga_casella=floor($posizione/$num_orz)+1;
	$col_casella=($posizione % $num_orz);
	if ($col_casella==0) {
		$col_casella=$num_orz;
		$riga_casella--;
	}; 
	if ($etichetta=="-1") {
		$etichetta="";
		$definizione="casella nera";
		$verso="";
	};
	
	echo "<tr bgcolor=\"$colore\">";
	
	echo "<td valign=top><span class=testo>($riga_casella,$col_casella) $etichetta $verso $definizione</span></td>\n";
	
	if ($ruolo=='admin' or $id_utente==$id_editor) {
		echo "
		<td valign=middle align=center>
		<a href=index.php?risorsa=lo_test_item_opzione_cruciverba_mod&id_item_opzione=$id_item_opzione&id_item=$id_item&risorsa_padre=$risorsa_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_item','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[edit]\" border=\"0\" name=\"img_mod_$id_item\"></a></td>";
	} else {
		echo "<td>&nbsp;</td>";
	};
	
	if ($ruolo=='admin' or $id_utente==$id_editor) {
		echo "
		<td valign=middle align=center>
		<a href=index.php?risorsa=msg&msg=conf_canc&pagina=lo_test_item_opzione_cruciverba_elimina.php&id_item_opzione=$id_item_opzione&id_item=$id_item&risorsa_padre=$risorsa_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_item','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_item\"></a>
		</td>
		";
	} else {
		echo "<td>&nbsp;</td>";
	};
	
	
	echo "</tr>";
	
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
}; 
echo "</table>\n";

echo "		
</td></tr>
</table>";


echo "</td></tr>
</table>";

?>

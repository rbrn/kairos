<?php
//if ($cod_area=="kairos_master" or $cod_area=="kairos_masterunitus") require "./include/master_pw.inc";

$id_utente=$kairos_cookie[0];

$query="SELECT * FROM iscrizioni_corso WHERE id_utente='$id_utente' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$livello=$riga["livello"];
$note = $riga["note"];
$superato=$riga["superato"];

$query="SELECT id_gruppo FROM iscrizioni_gruppo_pw WHERE id_utente='$id_utente' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {
	$id_gruppo=$riga["id_gruppo"];
	$query2="SELECT descrizione,livello,note FROM gruppo_utenti WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'"; 
	$result2=$mysqli->query($query2);
	$riga2=$result2->fetch_array();
	
	$descrizione_gruppo[]=$riga2["descrizione"];
	$livello_gruppo[]=$riga2["livello"];
	$note_gruppo[]=$riga2["note"];
	
};



echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>


<tr>
<td valign=top width=100%><span class=testo><b>VALUTAZIONI FINALI</b></span>
</td></tr>


<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=materiali\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=materiali\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";
$colore=$colore_sfondo;

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

echo "
<tr bgcolor=\"$colore_scuro\">
<td>
<span class=testonegativo>
<b>Valutazione Individuale</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>$stringa[livello_competenze]</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>Superato</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>$stringa[note]</b>
</span>
</td>";

echo "</tr>";

	echo "
		<tr  bgcolor=\"$colore\">
		<td valign=top>
		</td>";

		echo "<td align=left valign=top><span class=testopiccolo>";
		
		if ($livello==5) {
			echo "4/4 con Lode";
		} else {
			echo $livello."/4";
		};
		
		echo "</span></td>";
		
		echo "<td align=left valign=top><span class=testopiccolo>";
		if ($superato) {
			echo "OK";
		} else {
			echo "no OK (vedi note)";
		};
		
		echo "</span></td>";
		
		echo "
		<td align=left valign=top>
		<textarea class=testopiccolo rows=10 cols=70 readonly>$note</textarea>
		</td>";
		
		
		echo "</tr>
		";

		echo "</table>";
		echo "</td></tr></table>";


echo "
<br><br>
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

echo "
<tr bgcolor=\"$colore_scuro\">
<td>
<span class=testonegativo>
<b>Valutazione Project Work</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>$stringa[gruppo]</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>$stringa[livello_competenze]</b>
</span>
</td>
<td>
<span class=testonegativo>
<b>$stringa[note]</b>
</span>
</td>";

echo "</tr>";

$righe=1;
$continua = true;
$colore=$colore_sfondo;

for ($i=0;$i<count($livello_gruppo);$i++) {

	$descr_gruppo = $descrizione_gruppo[$i];
	$livello = $livello_gruppo[$i];
	$note = $note_gruppo[$i];
	$superato=$riga["superato"];
	
		
	echo "
		<tr  bgcolor=\"$colore\">
		<td></td>
		<td valign=top>
		<span class=testopiccolo>$descr_gruppo</span>
		</td>";
		
		echo "<td align=left valign=top><span class=testopiccolo>";
		
		if ($livello==5) {
			echo "4/4 con Lode";
		} else {
			echo $livello."/4";
		};
		
		echo "</span></td>";
		
		echo "
		<td align=left valign=top>
		<textarea class=testopiccolo rows=8 cols=60 readonly>$note</textarea>
		</td>";
		
		
		echo "</tr>
		";
	

	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};

};
echo "
</table>
</td></tr></table>
<br>

";

?>
</td></tr></table>
<br>

<?php

	
$query="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_utente";
$result=$mysqli->query($query);

if (!$pag_size) $pag_size=20;
if (!$pagina) $pagina=1;

$tot_righe=$result->num_rows;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$num =$tot_righe;
echo "<br><span class=titolopagina>$stringa[lavori_corsisti]</span>";

echo "<hr size=1><span class=testo>$stringa[utenti_trovati]: <b>$num</b></span><hr size=1>";


echo "
<table border=0>
<tr>
<td>
<span class=testopiccolo>
<b>$stringa[corsista]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[sito]</b>
</span>
</td>
</tr>";

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;

$righe=1;
while ($riga=$result->fetch_array()) {
	$id_utente1 = $riga["id_utente"];

	echo "
		<tr>
		<td>
		<span class=testopiccolo>
		<b>$progr</b> - 
		<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a></span>
		</td>";

		$url_utente=$PATH_ROOT."utenti/$cod_area/$id_utente1";
			
	echo "
		<td>
		<span class=testopiccolo>
		<a href=\"$url_utente\" target=_blank>$url_utente</a>
		</span>
		</td>
		</tr>
		";
	$righe++;
	$progr++;
	

};
echo "
</table>
<br>";

echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?risorsa=lavori&pagina=$i&pag_size=$pag_size>$i</a>]
		";
	};
	$i++;
};
echo "</span>
<br>
<br>";	

?>

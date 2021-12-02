<?php
require "./include/funzioni_stats.inc";
$da_aa=$_REQUEST["da_aa"];
$da_mm=$_REQUEST["da_mm"];
$da_gg=$_REQUEST["da_gg"];

$a_aa=$_REQUEST["a_aa"];
$a_mm=$_REQUEST["a_mm"];
$a_gg=$_REQUEST["a_gg"];

$dossier=$_REQUEST["dossier"];
$id_gruppo_stat=$_REQUEST["id_gruppo_stat"];
$da_data=$da_aa."-".$da_mm."-".$da_gg." 00:00:00";
$a_data=$a_aa."-".$a_mm."-".$a_gg." 23:59:59";

$da_data1=$da_aa."-".$da_mm."-".$da_gg;
$a_data1=$a_aa."-".$a_mm."-".$a_gg;

$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];

echo "
<p><span class=titolopagina>$stringa[statistiche_corso]</span><br>
<span class=sottotitolopagina>$stringa[dal]: $da_gg/$da_mm/$da_aa $stringa[al]: $a_gg/$a_mm/$a_aa</span></p>

<table border=1 cellspacing=0 cellpadding=4>
<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td colspan=3 align=center>
<span class=testopiccolo>
<b>$stringa[sessioni]</b>
</span>
</td>
<td colspan=2 align=center>
<span class=testopiccolo>
<b>$stringa[interventi_forum]</b>
</span>
</td>
<td colspan=4>&nbsp;</td>
</tr>

<tr>
<td>
<span class=testopiccolo>
<b>$stringa[utente]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[gruppo]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[num]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[durata_media]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[durata_totale]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[scritti]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[letti]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[righe_chat]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[materiali]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[test]</b>
</span>
</td>
<td>
<span class=testopiccolo>
<b>$stringa[risorse_piattaforma]</b>
</span>
</td>
</tr>";

if ($id_gruppo_stat) {
	$and_gruppo=" AND id_gruppo='$id_gruppo_stat'";
};

if (!$dossier) {	
	$query="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' $and_gruppo ORDER BY id_gruppo,id_utente";
} else {
	$query="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_utente='$id_utente' $and_gruppo ORDER BY id_gruppo,id_utente";
};

$result=$mysqli->query($query);


if (!$pag_size) $pag_size=20;
if (!$pagina) $pagina=1;

$tot_righe=$result->num_rows;
$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

//scorro fino alla pagina
$progr=0;
$num_pag=1;
$righe=0;
$continua=true;
$riga = $result->fetch_array();
while ($num_pag<>$pagina and $continua) {
	if ($riga) {
		$righe++;
		$progr++;
	} else {
		$continua=false;
	};
	if ($righe>$pag_size) {
		$num_pag++;
		$righe=1;
	};
	if ($num_pag<>$pagina) {
		$riga = $result->fetch_array();
	};
};

if (!$progr) $progr=1;

$righe=1;
$continua = true;
while ($riga and  $continua) {

	$id_utente1 = $riga["id_utente"];
	$id_gruppo1 = $riga["id_gruppo"];
	echo "
		<tr>
		<td>
		<span class=testopiccolo>
		<b>$progr</b> - 
		<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a></span>
		</td>
		<td>
		<span class=testopiccolo>$id_gruppo1</span>
		</td>
		";

	$stat_utente=get_stats($id_utente1,$da_data,$a_data);	
			
	echo "
		<td align=right>
		<span class=testopiccolo>";
		if ($stat_utente[0]) {
			echo "<a href=index.php?risorsa=stats_dettaglio&dettaglio=sessioni&id_utente1=$id_utente1&da_data=$da_data1"."&a_data=$a_data1>$stat_utente[0]</a>";
		} else {
			echo "$stat_utente[0]";
		};
		
		$durata_media=h_m_s($stat_utente[1]);
		$tot_durata=h_m_s($stat_utente[2]);
		echo "
		</span>
		</td>
		<td align=right>
		<span class=testopiccolo>
		$durata_media
		</span>
		</td>
		<td align=right>
		<span class=testopiccolo>
		$tot_durata
		</span>
		</td>
		<td align=right>
		<span class=testopiccolo>";
		
		if ($stat_utente[3]) {
			echo "<a href=index.php?risorsa=stats_dettaglio&dettaglio=forum_scritti&id_utente1=$id_utente1&da_data=$da_data1"."&a_data=$a_data1>$stat_utente[3]</a>";
		} else {
			echo "$stat_utente[3]";
		};
		echo "
		</span>
		</td>
		<td align=right>
		<span class=testopiccolo>";
		
		if ($stat_utente[4]) {
			echo "<a href=index.php?risorsa=stats_dettaglio&dettaglio=forum_letti&id_utente1=$id_utente1&da_data=$da_data1"."&a_data=$a_data1>$stat_utente[4]</a>";
		} else {
			echo "$stat_utente[4]";
		};
		
		echo "
		</span>
		</td>
		<td align=right>
		<span class=testopiccolo>
		$stat_utente[5]
		</span>
		</td>
		<td align=right>
		<span class=testopiccolo>";
		
		if ($stat_utente[6]) {
			echo "<a href=index.php?risorsa=stats_dettaglio&dettaglio=materiali&id_utente1=$id_utente1&da_data=$da_data1"."&a_data=$a_data1>$stat_utente[6]</a>";
		} else {
			echo "$stat_utente[6]";
		};
		
		echo "
		</span>
		</td>
		<td align=right>
		<span class=testopiccolo>";
		
		if ($stat_utente[7]) {
			echo "<a href=index.php?risorsa=stats_dettaglio&dettaglio=test&id_utente1=$id_utente1&da_data=$da_data1"."&a_data=$a_data1>$stat_utente[7]</a>";
		} else {
			echo "$stat_utente[7]";
		};
		
		echo "
		</span>
		</td>
		<td align=right>
		<span class=testopiccolo>";
		
		if ($stat_utente[8]) {
			echo "<a href=index.php?risorsa=stats_dettaglio&dettaglio=risorse&id_utente1=$id_utente1&da_data=$da_data1"."&a_data=$a_data1>$stat_utente[8]</a>";
		} else {
			echo "$stat_utente[8]";
		};
		
		echo "
		</span>
		</td>
		</tr>
		";
	
	$righe++;
	$progr++;
	$riga = $result->fetch_array();
	if ($righe > $pag_size) {
		$continua = false;
	};

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
		[<a href=index.php?risorsa=stats_corso&pagina=$i&pag_size=$pag_size&dossier=$dossier&da_gg=$da_gg&da_mm=$da_mm&da_aa=$da_aa&a_gg=$a_gg&a_mm=$a_mm&a_aa=$a_aa&id_gruppo_stat=$id_gruppo_stat>$i</a>]
		";
	};
	$i++;
};
echo "</span><br>";	
?>
<br>

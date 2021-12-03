<?php
require "./include/funzioni_stats.inc";

$id_utente1=$_REQUEST["id_utente1"];
$dettaglio=$_REQUEST["dettaglio"];

$da_data1=$_REQUEST["da_data"];
$a_data1=$_REQUEST["a_data"];

$da_data=$da_data1." 00:00:00";
$a_data=$a_data1." 23:59:59";

$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];

if ($id_utente<>$id_utente1 AND $ruolo<>'admin' AND $ruolo<>'staff') {
	echo "<p><span class=testo>$stringa[no_privilegi]</span></p>";
	exit();
};

echo "
<p><span class=titolopagina>$stringa[dettaglio_statistiche]</span><br>
<span class=sottotitolopagina>$stringa[utente]: 
<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a> - $stringa[dal]: $da_data1 $stringa[al]: $a_data1</span></p>
<hr size=1>
<span class=testo>[<a href=javascript:history.back()>$stringa[indietro]</a>]</span>
<hr size=1>
";

switch ($dettaglio) {
	case "sessioni":
	
	echo "
	<table border=1 cellspacing=0 cellpadding=4>
	<tr>
	<td colspan=2 align=center>
	<span class=testopiccolo>
	<b>$stringa[sessioni]</b>
	</span>
	</td>
	</tr>
	<tr>
	<td>
	<span class=testopiccolo>
	<b>$stringa[data]</b>
	</span>
	</td>
	<td>
	<span class=testopiccolo>
	<b>$stringa[durata]</b>
	</span>
	</td>
	</tr>";

	
	$stat_utente=get_stats_sessioni($id_utente1,$da_data,$a_data);
	
	for ($j=0;$j<count($stat_utente);$j++) {
		list ($durata,$inizio_sessione)=split("\t",$stat_utente[$j]);	
		ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$inizio_sessione,$parti);
		$da_gg=$parti[3];
		$da_mm=$parti[2];
		$da_aa=$parti[1];
		$da_hh=$parti[4];
		$da_m=$parti[5];
		$da_ss=$parti[6];
		
		$durata=h_m_s($durata);			
		echo "
		<tr>
		<td align=right>
		<span class=testopiccolo>
		$da_gg/$da_mm/$da_aa $da_hh:$da_m:$da_ss
		</span>
		</td>
		<td align=right>
		<span class=testopiccolo>
		$durata
		</span>
		</td>
		
		</tr>
		";
	};
	
	echo "
	</table>
	<br>";
	break;
	
	
	case "forum_scritti":
	
	echo "
	<table border=1 cellspacing=0 cellpadding=4>
	<tr>
	<td align=center>
	<span class=testopiccolo>
	<b>$stringa[interventi_scritti]</b>
	</span>
	</td>
	</tr>";

	
	$stat_utente=get_stats_forum_scritti($id_utente1,$da_data,$a_data);
	
	for ($j=0;$j<count($stat_utente);$j++) {
		list ($oggetto,$id_forum,$id_post,$data_post)=split("\t",$stat_utente[$j]);	
		ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_post,$parti);
		$da_gg=$parti[3];
		$da_mm=$parti[2];
		$da_aa=$parti[1];
		$da_hh=$parti[4];
		$da_m=$parti[5];
		$da_ss=$parti[6];

		echo "
		<tr>
		<td align=left>
		<span class=testopiccolo>
		<a href=index.php?risorsa=forum_mostra_post&id_post=$id_post&id_forum=$id_forum>$oggetto</a> ($da_gg/$da_mm/$da_aa $da_hh:$da_m:$da_ss)
		</span>
		</td>
		</tr>
		";
	};
	
	echo "
	</table>
	<br>";
	break;
	
	case "forum_letti":
	
	echo "
	<table border=1 cellspacing=0 cellpadding=4>
	<tr>
	<td align=center>
	<span class=testopiccolo>
	<b>$stringa[interventi_letti]</b>
	</span>
	</td>
	</tr>";

	
	$stat_utente=get_stats_forum_letti($id_utente1,$da_data,$a_data);
	
	for ($j=0;$j<count($stat_utente);$j++) {
		list ($id_autore,$oggetto,$id_forum,$id_post,$data_post,$data_read)=split("\t",$stat_utente[$j]);	
		ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_post,$parti);
		$da_gg=$parti[3];
		$da_mm=$parti[2];
		$da_aa=$parti[1];
		$da_hh=$parti[4];
		$da_m=$parti[5];
		$da_ss=$parti[6];

		ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_read,$parti);
		$read_gg=$parti[3];
		$read_mm=$parti[2];
		$read_aa=$parti[1];
		$read_hh=$parti[4];
		$read_m=$parti[5];
		$read_ss=$parti[6];
		echo "
		<tr>
		<td align=left>
		<span class=testopiccolo>
		<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_autore</a> - <a href=index.php?risorsa=forum_mostra_post&id_post=$id_post&id_forum=$id_forum>$oggetto</a> ($da_gg/$da_mm/$da_aa $da_hh:$da_m:$da_ss) $stringa[letto]: $read_gg/$read_mm/$read_aa $read_hh:$read_m:$read_ss
		</span>
		</td>
		</tr>
		";
	};
	
	echo "
	</table>
	<br>";
	break;

	case "materiali":
	
	echo "
	<table border=1 cellspacing=0 cellpadding=4>
	<tr>
	<td align=center>
	<span class=testopiccolo>
	<b>$stringa[materiali]</b>
	</span>
	</td>
	</tr>";

	
	$stat_utente=get_stats_materiali($id_utente1,$da_data,$a_data);
	
	for ($j=0;$j<count($stat_utente);$j++) {
		list ($id_risorsa,$titolo,$data_log)=split("\t",$stat_utente[$j]);	
		ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_log,$parti);
		$da_gg=$parti[3];
		$da_mm=$parti[2];
		$da_aa=$parti[1];
		$da_hh=$parti[4];
		$da_m=$parti[5];
		$da_ss=$parti[6];

		echo "
		<tr>
		<td align=left>
		<span class=testopiccolo>
		<a href=materiali_browse.php?risorsa=$id_risorsa>$titolo</a> ($da_gg/$da_mm/$da_aa $da_hh:$da_m:$da_ss)
		</span>
		</td>
		</tr>
		";
	};
	
	echo "
	</table>
	<br>";
	break;

	case "risorse":
	
	echo "
	<table border=1 cellspacing=0 cellpadding=4>
	<tr>
	<td align=center>
	<span class=testopiccolo>
	<b>$stringa[risorse_piattaforma]</b>
	</span>
	</td>
	</tr>";

	
	$stat_utente=get_stats_risorse($id_utente1,$da_data,$a_data);
	
	for ($j=0;$j<count($stat_utente);$j++) {
		list ($id_risorsa,$titolo,$data_log)=split("\t",$stat_utente[$j]);	
		ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_log,$parti);
		$da_gg=$parti[3];
		$da_mm=$parti[2];
		$da_aa=$parti[1];
		$da_hh=$parti[4];
		$da_m=$parti[5];
		$da_ss=$parti[6];

		echo "
		<tr>
		<td align=left>
		<span class=testopiccolo>
		$titolo ($da_gg/$da_mm/$da_aa $da_hh:$da_m:$da_ss)
		</span>
		</td>
		</tr>
		";
	};
	
	echo "
	</table>
	<br>";
	break;
	
	case "test":
	
	echo "
	<table border=1 cellspacing=0 cellpadding=4>
	<tr>
	<td align=center>
	<span class=testopiccolo>
	<b>$stringa[test]</b>
	</span>
	</td>
	</tr>";

	
	$stat_utente=get_stats_test($id_utente1,$da_data,$a_data);
	
	for ($j=0;$j<count($stat_utente);$j++) {
		list ($titolo_test,$id_test_compilato,$punteggio,$data_compilazione)=split("\t",$stat_utente[$j]);	
		ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_compilazione,$parti);
		$da_gg=$parti[3];
		$da_mm=$parti[2];
		$da_aa=$parti[1];
		$da_hh=$parti[4];
		$da_m=$parti[5];
		$da_ss=$parti[6];

		echo "
		<tr>
		<td align=left>
		<span class=testopiccolo>
		<a href=index.php?risorsa=test_compilato&id_test_compilato=$id_test_compilato>$titolo_test</a>";
		if ($punteggio<>"") {
			echo "&nbsp;$stringa[punteggio]: $punteggio";
		};
		echo "&nbsp;($da_gg/$da_mm/$da_aa $da_hh:$da_m:$da_ss)
		</span>
		</td>
		</tr>
		";
	};
	
	echo "
	</table>
	<br>";
	break;
};
?>

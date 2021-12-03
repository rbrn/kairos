<?php
if (!ereg('MSIE',$_SERVER["HTTP_USER_AGENT"]) or !ereg('Windows',$_SERVER["HTTP_USER_AGENT"])) {
	$win_ie=false;
} else {	
	$win_ie=true;
};

if (ereg('Opera',$_SERVER["HTTP_USER_AGENT"])) {
	$win_ie=false;
};

if (isset($cod_area)) {
	$kairos_cookie[4]=$cod_area;
	setcookie("kairos_cookie[4]",$kairos_cookie[4],0,"/",$dominio);
};

require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$risorsa=$_REQUEST[id_risorsa];

$id_corso=id_corso($risorsa);
		
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

		$query="SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_corso'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$titolo=$riga["titolo"];
		
		$query="SELECT tipo,id_autore,id_gruppo,risorsa_padre FROM risorse_materiali WHERE id_risorsa='$risorsa'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$tipo=$riga["tipo"];
		$id_autore=$riga["id_autore"];
		$id_gruppo=$riga["id_gruppo"];
		$risorsa_superiore=$riga["risorsa_padre"];
		
		if ($tipo==4) {
			$query="SELECT id_autore FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
			$result=$mysqli->query($query);
			$riga=$result->fetch_array();
			$id_autore=$riga["id_autore"];
		};
			
		
		$pag_succ=materiali_pag_succ($risorsa,$risorsa_superiore);
		$pag_prec=materiali_pag_prec($risorsa,$risorsa_superiore);
		
		
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");

$target="target=_top";
$id_utente=$kairos_cookie[0];
$ruolo=ruolo_utente($id_utente);
$id_corso_ed_s=$kairos_cookie[2];
list($id_corso_s,$id_edizione_s,$id_gruppo_s,$id_tutor_s)=split(" ",$id_corso_ed_s);

require "./include/testata.inc";

		echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[materiali])."</td></tr>
<tr><td>";


		echo "
		<table border=0 bgcolor=\"white\" width=100%>
		<tr>
		<td width=50%><span class=sottotitolopagina>$titolo</span><!--<br><span class=testo><b>$titolo_pagina</b></span>--></td>";
		
		if ($id_autore) {
			$query="SELECT nome,cognome FROM utenti WHERE id_utente='$id_autore'";
			$result=$mysqli->query($query);
			$riga=$result->fetch_array();
			$nome_autore=$riga[nome]." ".$riga[cognome];
			
			echo "
			<td align=right>
			<span class=testopiccolo>$stringa[autore]:
			<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$nome_autore</a></span></td>
			";
		};	
		
		echo "
		<td align=right>
		<a href=\"javascript:history.back()\" target=\"_top\" 
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back1','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back1\"></a>
		";
		if ($pag_prec) {
			echo "
			<a href=\"materiali_browse.php?risorsa=$pag_prec\" target=\"_top\" 
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_indietro1','','img/ico_indietro_over.gif',1)\"><img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_indietro1\"></a>
			";
		} else {
			echo "<img border=\"0\" src=\"img/ico_indietro.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_indietro1\">";
		};
		if ($pag_succ) {
			echo "
			<a href=\"materiali_browse.php?risorsa=$pag_succ\" target=\"_top\" 
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_fw1','','img/ico_avanti_over.gif',1)\"><img border=\"0\" src=\"img/ico_avanti.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[avanti]\" name=\"img_fw1\"></a>";
		} else {
			echo "<img border=\"0\" src=\"img/ico_avanti.gif\" width=\"17\" height=\"15\" align=\"middle\" alt=\"$stringa[avanti]\" name=\"img_fw1\">";
		};
		echo "</td></tr></table>";
echo "</td></tr></table>";
		
echo "</body></html>";
?>



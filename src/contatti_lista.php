<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_utente_cerca=$_REQUEST["id_utente_cerca"];
$cod_mecc_cerca=$_REQUEST["cod_mecc_cerca"];

$ruolo=ruolo_utente($kairos_cookie[0]);

/*
if ($ruolo<>"admin" and !$id_utente_cerca) {
	$id_utente_cerca=$kairos_cookie[0];
};
*/
$where="";

if ($id_utente_cerca) {
	if ($where) $where.="AND ";
	$where.= "id_utente = '$id_utente_cerca'";
};

if ($cod_mecc_cerca) {
	if ($where) $where.="AND ";
	$where.= "cod_mecc = '$cod_mecc_cerca'";
};

if ($risp_voce_3_1) {
	if ($where) $where.="AND ";
	$where.= "risp_voce_3_1 = 'x'";
};

if ($risp_voce_3_2) {
	if ($where) $where.="AND ";
	$where.= "risp_voce_3_2 = 'x'";
};

if ($risp_voce_3_3) {
	if ($where) $where.="AND ";
	$where.= "risp_voce_3_3 = 'x'";
};

if ($risp_voce_3_4) {
	if ($where) $where.="AND ";
	$where.= "risp_voce_3_4 = 'x'";
};

if ($risp_voce_3_5) {
	if ($where) $where.="AND ";
	$where.= "risp_voce_3_5 = 'x'";
};

if ($risp_voce_3_6) {
	if ($where) $where.="AND ";
	$where.= "risp_voce_3_6 = 'x'";
};

if ($risp_voce_3_7) {
	if ($where) $where.="AND ";
	$where.= "risp_voce_3_7 = 'x'";
};

if ($risp_voce_3_8) {
	if ($where) $where.="AND ";
	$where.= "risp_voce_3_8 = 'x'";
};

if ($risp_voce_3_9) {
	if ($where) $where.="AND ";
	$where.= "risp_voce_3_9 = 'x'";
};

if ($where) $where=" WHERE ".$where;
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>Consulenti: segnalazione contatto</title>
	<SCRIPT language=JavaScript src="script/funzioni.js"></SCRIPT>
<LINK href="stili/kairos_demo/stile_sito.css" rel=stylesheet>
</head>

<body>
<TABLE cellSpacing=10 cellPadding=0 width="100%" border=0>
        <TBODY>
  
     
        <TR>
          <TD><SPAN class=testo><b>Consulente</b></SPAN></TD>
		 <td><span class=testo><b>Data notifica</b></span></td>
		 <td>&nbsp;</td>
		</TR>
		<?php 
		$query="SELECT * FROM contatti $where ORDER BY data_compilazione DESC";
        $result = $mysqli->query($query);

		while ($riga=$resul->fetch_array()) {
			$id_u=$riga[id_utente];
			$data_compilazione=$riga[data_compilazione];
			$id_contatto=$riga[id_contatto];
			
			echo "
			<tr>
			 <TD><SPAN class=testo><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_u',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_u</a></SPAN></TD>
		 <td><span class=testo>$data_compilazione</span></td>
		 <td><span class=testo>[<a href=contatti_view.php?id_contatto=$id_contatto>Scheda</a>]</span></td>
		 </tr>";
		};
		?>
		
			</TBODY>
			</TABLE>


</body>
</html>

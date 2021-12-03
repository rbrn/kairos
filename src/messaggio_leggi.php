<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente1=strtolower($kairos_cookie[0]);
$id_messaggio=$_REQUEST["id_messaggio"];

if (!$id_utente1) {
	echo "
	<html>
	<head><title>Errore</title>
	<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
	<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
	</HEAD>
	<BODY bgcolor=$colore_sfondo>
	<span class=testo>$stringa[errore_no_login]</span>
	</body>
	</html>";
	exit();
};
?>
<?php
	$db = mysql_connect("localhost",$DBUSER,$DBPWD);
	mysql_select_db($DBASE,$db);	
	$query = "SELECT * FROM messaggi WHERE id_messaggio=$id_messaggio";
	$result=$mysqli->query($query);
	$messaggio=$result->fetch_array();
	$data_invio=$messaggio["data_invio"];

	ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_invio,$arg);
	$data_invio=$arg[3]."/".$arg[2]."/".$arg[1]." ".$arg[4].":".$arg[5].":".$arg[6];


	$oggetto=htmlentities($messaggio["oggetto"]);
	$data_lettura=$messaggio["data_lettura"];
	ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_lettura,$arg);
	$data_lettura=$arg[3]."/".$arg[2]."/".$arg[1]." ".$arg[4].":".$arg[5].":".$arg[6];

	$id_mittente=$messaggio["id_mittente"];
	$id_destinatario=strtolower($messaggio["id_destinatario"]);
	$testo=htmlentities($messaggio["testo"]);

	if ($id_utente1==$id_destinatario) {
		$query="UPDATE messaggi SET data_lettura=NOW() WHERE data_lettura='0000-00-00 00:00:00' AND id_messaggio=$id_messaggio";
		$result=$mysqli->query($query);
	};
?>

<?php
echo "
<html>
<head>
<title>$stringa[messaggio]</title>
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>
<script language="JavaScript" src="script/funzioni.js"></script>
</head>
<BODY bgcolor=<?php echo($colore_sfondo_neutro);?> topmargin="0" leftmargin="0">
<table border=0 width=100% cellpadding=5 bgcolor=<?php echo($colore_scuro_neutro);?>>
<tr><td>
<span class=testo><b><?php echo($stringa[messaggio]);?></b></span>
</tr>
</table>

<form action="messaggio_scrivi.php" method="post">
<table border="0">
<tr>
<td align="right" valign=top>
<span class=testo><b><?php echo($stringa[da]);?>:</b></span>
</td>
<td valign=top>
<?php 
echo "
<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_mittente',                   'myRemote1',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindow1');\"><span class=testo>$id_mittente</a> ($data_invio)</span>";
?>
</td>
</tr>
<tr>
<td align="right" valign=top>
<span class=testo><b><?php echo($stringa[a]);?>:</b></span>
</td>
<td valign=top>
<?php 
echo "
<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_destinatario',                   'myRemote1',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindow1');\"><span class=testo>$id_destinatario</a>";
if ($messaggio["data_lettura"]<>"0000-00-00 00:00:00") {
	echo " ($stringa[letto] $data_lettura)";
};
echo "</span>";
?>
</td>
</tr>
<tr>
<td align="right" valign=top>
<p><span class=testo><b><?php echo($stringa[oggetto]);?>:</b></span></p>
</td>
<td valign=top>
<span class=testo><?php echo($oggetto);?></span>
</td>
</tr>
 <tr>
 <td align="right" valign=top>
 <span class=testo><b><?php echo($stringa[messaggio]);?>:</b></span>
 </td>
<?php
echo " 
  <td valign=top>
<textarea name=testo rows=15 cols=40 readonly>$testo</textarea>
 </td>";
 ?>
 </tr>
<tr><td colspan=2></td></tr>
<tr><td colspan=2 align=right>
<span class=testo>[<a href="form_messaggio_scrivi.php?id_messaggio=<?php echo($id_messaggio);?>"><?php echo($stringa[replica]);?></a>] [<a href="javascript:self.close()"><?php echo($stringa[chiudi]);?></a>]</span>
</td>
</tr>
</table>
</form>
<!-- FINE CONTENUTO DELLA PAGINA -->
</body>
</html>

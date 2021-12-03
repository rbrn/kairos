<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";
$messaggi=$_REQUEST["messaggi"];
if (!$messaggi) {
	$messaggi="ricevuti";
};

if ($messaggi=="ricevuti") {
	$altri_messaggi="inviati";
	$da=$stringa[da];
} else {
	$altri_messaggi="ricevuti";
	$da=$stringa[a];
};


$query = "SELECT count(*) AS n_ricevuti FROM messaggi WHERE id_destinatario='$id_utente' AND stato<>2";

$result=$mysqli->query($query);
$riga=$result->fetch_array();
$n_ricevuti=$riga[n_ricevuti];

$query = "SELECT count(*) AS n_spediti FROM messaggi WHERE id_mittente='$id_utente' AND stato<>1";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$n_spediti=$riga[n_spediti];

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";


echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr>";

echo "
<td valign=top width=77% class=titolodot>".strtoupper($stringa[messaggi])." ".strtoupper($stringa[$messaggi])."</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=20%>&nbsp;</td>";
echo "</tr>";

echo "<tr><td valign=top width=77%>";

echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr><td>";

echo "
<form action=cancella_messaggi.php method=post name=modulo id=modulo>
<input type=hidden name=messaggi value=\"$messaggi\">";

echo "<table border=0>";
echo "<tr>
<td valign=middle><a class=miolink href=\"javascript:;\" title=\"$stringa[nuovo_messaggio_alt]\" onclick=\"javascript:apri_scheda('form_messaggio_scrivi.php',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mail_nuovo','','img/ico_mail_nuovo_over.gif',1)\"><img src=\"img/ico_mail_nuovo.gif\" width=\"25\" height=\"25\" alt=\"$stringa[nuovo_messaggio_alt]\" border=\"0\" name=\"img_mail_nuovo\"></a></td>
<td valign=middle><span class=testopiccolo><a class=miolink href=\"javascript:;\" title=\"$stringa[nuovo_messaggio_alt]\" onclick=\"javascript:apri_scheda('form_messaggio_scrivi.php',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mail_nuovo','','img/ico_mail_nuovo_over.gif',1)\">$stringa[nuovo_messaggio]</a></td>";

echo "<td width=10>&nbsp;</td>";

echo "
<td valign=middle><a class=miolink href=\"javascript:document.modulo.submit()\" title=\"$stringa[cancella_elementi]\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mail_elimina','','img/ico_mail_elimina_over.gif',1)\"><img src=\"img/ico_mail_elimina.gif\" width=\"25\" height=\"25\" alt=\"$stringa[cancella_elementi]\" border=\"0\" name=\"img_mail_elimina\"></a></td>

<td valign=middle>
<span class=testopiccolo>
<a class=miolink href=\"javascript:document.modulo.submit()\" title=\"$stringa[cancella_elementi]\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mail_elimina','','img/ico_mail_elimina_over.gif',1)\">$stringa[cancella_elementi]</a></span></td>";

echo "</tr>
</table>";


echo "
<br>
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=0 cellspacing=0 bgcolor=\"white\" >
<tr><td>";

echo "
<table border=0 cellpadding=5 cellspacing=1>
<tr bgcolor=\"$colore_scuro\">
<td>&nbsp;</td>
<td>&nbsp;</td>
<td><span class=testopiccolonegativo><b>$da</b></span></td>
<td><span class=testopiccolonegativo><b>$stringa[oggetto]</b></span></td>
<td><span class=testopiccolonegativo><b>$stringa[spedito]</b></span></td>
<td><span class=testopiccolonegativo><b>$stringa[letto]</b></span></td>
<!--<td>&nbsp;</td>-->
</tr>

";

if ($messaggi=='ricevuti') {
	$query = "SELECT * FROM messaggi WHERE id_destinatario='$id_utente' AND stato<>2  ORDER BY data_invio DESC";
} else {
	$query = "SELECT * FROM messaggi WHERE id_mittente='$id_utente' AND stato<>1 ORDER BY data_invio DESC";
};

$result=$mysqli->query($query);

$colore=$colore_sfondo;

while ($messaggio = $result->fetch_array()) {
	$id_messaggio=$messaggio["id_messaggio"];
	$id_mittente=$messaggio["id_mittente"];
	$id_destinatario=$messaggio["id_destinatario"];
	
	if ($messaggi=='ricevuti') {
		$id_utente_msg=$id_mittente;
	} else {
		$id_utente_msg=$id_destinatario;
	};
	
	$oggetto=$messaggio["oggetto"];
	
	$testo=ereg_replace("\n","<br>",$messaggio["testo"]);
	$data_invio=$messaggio["data_invio"];
	$data_lettura=$messaggio["data_lettura"];
	$enfasi="";
	$enfasi_stop="";
	if ($data_lettura=="0000-00-00 00:00:00") {
		$data_lettura="";
		$enfasi="<b>";
		$enfasi_stop="</b>";
	};
	
	ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_invio,$arg);
	
	$data_invio=$arg[3]."/".$arg[2]."/".$arg[1]." ".$arg[4].":".$arg[5].":".$arg[6];
	
	if ($data_lettura) {
		$img_ico_mail="ico_mail_letta.gif";
	} else {
		$img_ico_mail="ico_mail_nuova.gif";
	};
	
	if ($data_lettura) {
		ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_lettura,$arg);
	
		$data_lettura=$arg[3]."/".$arg[2]."/".$arg[1]." ".$arg[4].":".$arg[5].":".$arg[6];
	};
	
	echo "<tr bgcolor=$colore>";
	echo "
<td width=21><img src=\"img/$img_ico_mail\" width=\"21\" height=\"19\" alt=\"\" border=\"0\"></td>
<td width=05><input type=checkbox name=\"$id_messaggio\" value=\"$id_messaggio\"></td>

<td><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente_msg',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\"><span class=testopiccolo>$id_utente_msg</a></span></td>

<td><a class=miolink href=\"javascript:;\" title=\"$stringa[leggi_messaggio_alt]\" onclick=\"javascript:apri_scheda('messaggio_leggi.php?id_messaggio=$id_messaggio',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\"><span class=testopiccolo>$enfasi $oggetto $enfasi_stop</span></a></td>

<td><span class=testopiccolo>$data_invio</span></td>
<td><span class=testopiccolo>$data_lettura</span></td>

</tr>
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

</td></tr></table>";



echo "
<br>
<table border=0>";
echo "<tr>
<td valign=middle><a class=miolink href=\"javascript:;\" title=\"$stringa[nuovo_messaggio_alt]\" onclick=\"javascript:apri_scheda('form_messaggio_scrivi.php',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mail_nuovo2','','img/ico_mail_nuovo_over.gif',1)\"><img src=\"img/ico_mail_nuovo.gif\" width=\"25\" height=\"25\" alt=\"$stringa[nuovo_messaggio_alt]\" border=\"0\" name=\"img_mail_nuovo2\"></a></td>
<td valign=middle><span class=testopiccolo><a class=miolink href=\"javascript:;\" title=\"$stringa[nuovo_messaggio_alt]\" onclick=\"javascript:apri_scheda('form_messaggio_scrivi.php',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mail_nuovo2','','img/ico_mail_nuovo_over.gif',1)\">$stringa[nuovo_messaggio]</a></td>";

echo "<td width=10>&nbsp;</td>";

echo "
<td valign=middle><a class=miolink href=\"javascript:document.modulo.submit()\" title=\"$stringa[cancella_elementi]\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mail_elimina2','','img/ico_mail_elimina_over.gif',1)\"><img src=\"img/ico_mail_elimina.gif\" width=\"25\" height=\"25\" alt=\"$stringa[cancella_elementi]\" border=\"0\" name=\"img_mail_elimina2\"></a></td>

<td valign=middle>
<span class=testopiccolo>
<a class=miolink href=\"javascript:document.modulo.submit()\" title=\"$stringa[cancella_elementi]\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mail_elimina2','','img/ico_mail_elimina_over.gif',1)\">$stringa[cancella_elementi]</a></span></td>";

echo "</tr>
</table>";

echo "</form>";

echo "</td></tr></table>";

echo "</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=20%>";

echo "		
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr> 
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\"> 
<span class=titolo><b>$stringa[cartelle]</b></span>
</td>
</tr>

<tr><td>";

echo "
<table border=0 cellpadding=2 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">
<tr><td valign=middle>
<a href=index.php?risorsa=messaggi&messaggi=ricevuti  onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mailfold_arr','','img/ico_mailfold_arr_over.gif',1)\"><img src=\"img/ico_mailfold_arr.gif\" width=\"35\" height=\"24\" alt=\"$stringa[messaggi] $stringa[ricevuti]\" border=\"0\" name=\"img_mailfold_arr\"></a></td>
<td valign=middle>
<span class=\"testopiccolo\"><a href=index.php?risorsa=messaggi&messaggi=ricevuti  onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mailfold_arr','','img/ico_mailfold_arr_over.gif',1)\">".strtoupper("$stringa[messaggi] $stringa[ricevuti]")."</a> ($n_ricevuti)
</span>
</td></tr>
<tr>
<td valign=middle>
<a href=index.php?risorsa=messaggi&messaggi=ricevuti  onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mailfold_inv','','img/ico_mailfold_inv_over.gif',1)\"><img src=\"img/ico_mailfold_inv.gif\" width=\"35\" height=\"24\" alt=\"$stringa[messaggi] $stringa[inviati]\" border=\"0\" name=\"img_mailfold_inv\"></a></td>
<td valign=middle>
<span class=\"testopiccolo\"><a href=index.php?risorsa=messaggi&messaggi=inviati onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mailfold_inv','','img/ico_mailfold_inv_over.gif',1)\">".strtoupper("$stringa[messaggi] $stringa[inviati]")."</a> ($n_spediti)
</span>
</td></tr>
</table>";

echo "</td></tr></table>";

echo "</td></tr></table>";

echo "</td></tr></table>";
echo "                </div>
            </div>
        </div>
    </div>
</div>";
?>




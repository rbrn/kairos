<?php
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];


$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione_s;

$query="SELECT * FROM corso WHERE id_corso='$id_corso_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$descr_corso=$riga["descrizione"];

$direttore=0;

$query="SELECT DISTINCT * FROM ruolo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_utente='$kairos_cookie[0]'";
$result=$mysqli->query($query);
if ($result->num_rows) $direttore=1;
		
if ($ruolo=='admin' or $kairos_cookie[0]=='11lu' or $direttore) {
	$elenco_gruppi="<option value=\"\" selected>$stringa[qualunque]</option>";
	$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_gruppo";
} else {
	$elenco_gruppi="";
	$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_tutor='$id_utente' ORDER BY id_gruppo";
};
$result=$mysqli->query($query);

while ($riga=$result->fetch_array()) {
	$id_gruppo=$riga["id_gruppo"];
	$descr_gruppo=$riga["descrizione"];
	$tipo_gruppo=$riga["tipo_gruppo"];
	$elenco_gruppi .= "<option value=\"$id_gruppo-$tipo_gruppo\">$descr_gruppo</option>";
};

if (!$elenco_gruppi) {
	echo "<p><span class=testo>$stringa[errore_no_tutor]</span></p>";
	exit();
};	

$id_utente=$kairos_cookie[0];
$query = "SELECT nome,cognome FROM utenti WHERE id_utente='$id_utente'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$nome_mittente=$riga["nome"];
$cognome_mittente=$riga["cognome"];

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_index><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso_s><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s><span class=testo><b>$stringa[corso]:</b> $descr_corso: $descr_edizione</span></a>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[invio_newsletter])."</b></span>
</td></tr>



<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
";

?>
<!-- CONTENUTO DELLA PAGINA -->
<TR>
<TD>
<span class=testo><b><?php echo($stringa[invio_newsletter_label]);?></b>
</TD>
</tr>

<TR><TD>		
<form action=index.php method=post>
<input type=hidden name=risorsa value="newsletter">
<input type=hidden name=id_corso value="<?php echo($id_corso_s);?>">
<input type=hidden name=id_edizione value="<?php echo($id_edizione_s);?>">
<?php
echo "
<p>
<span class=testo><b>$stringa[gruppo]:</b></span>
<select name=id_gruppo_news>
$elenco_gruppi
</select>
</p>
";
?>

<p>
<span class=testo>
<b><?php echo($stringa[oggetto]);?>:</b>
</span>
<input type=text name=oggetto size=40 value="<?php echo($id_corso_s);?>: ">
</p>

<span class=testo>
<b><?php echo($stringa[contenuto]);?>:</b><br>
</span>
<textarea name=messaggio cols=40 rows=10>
<?php 
echo "

$nome_mittente $cognome_mittente ($id_utente)
$descr_corso
http://$server";
?>
</textarea>

<p>
<input type=checkbox name=invia_staff>
<span class=testo>
<b><?php echo($stringa[invia_staff]);?></b>
</span>
</p>

<input type=submit value="<?php echo($stringa[ok]);?>">
</form>
</TD></TR>

</TABLE>
<br>
<!-- FINE CONTENUTO DELLA PAGINA -->

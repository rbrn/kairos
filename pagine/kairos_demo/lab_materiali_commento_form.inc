<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[database_lavori])."</td></tr>
<tr><td>";
echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";
?>


<?php
$id_risorsa=$_REQUEST["id_risorsa"];
$id_utente=$kairos_cookie[0];

mysql_select_db($DBASE,$db);	

$query = "SELECT * FROM lab_materiali where id_risorsa=$id_risorsa";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$tipo=$riga["tipo"];
$risorsa_padre=$riga["risorsa_padre"];	
$titolo=htmlentities($riga["titolo"]);		
$descrizione=htmlentities($riga["descrizione"]);
$descrizione=str_replace("\n","<br>",$descrizione);
$parole_chiave=htmlentities($riga["parole_chiave"]);
$url=$riga["url"];		
$file_size=$riga["file_size"];

$query = "SELECT titolo FROM lab_materiali where id_risorsa=$risorsa_padre";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$nome_cartella=$riga[titolo];

?>

    <TABLE border=0 width=461>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
      <TR>
         <TD align=right><span class=testo><strong><?php echo($stringa[cartella]);?>:</strong></span></TD>
                <TD><span class=testo><?php echo "<a href=index.php?risorsa=lab_materiali_index&id_cartella=$risorsa_padre>$nome_cartella</a>";?></span></TD>
		</TR>
		
	  <?php 
	  if ($tipo==0) {
	  	$query="INSERT INTO log_lab_materiali SET
id_utente='$id_utente',
data_log=now(),
id_risorsa='$id_risorsa',
id_corso='$id_corso_s',
id_edizione='$id_edizione_s',
id_gruppo='$id_gruppo_s'";
$mysqli->query($query);
	  ?>
		<TR>
         <TD align=right><span class=testo><strong><?php echo($stringa[indirizzo]);?>:</strong></span></TD>
                <TD><span class=testo><?php echo "<a href=$url target=_blank title=\"$titolo\">$titolo ($url)</a>";?></span></TD>
		</TR>
 	<?php }; ?>
	
	  <?php 
	  if ($tipo==1) {			
	  ?>
		<TR>
         <TD align=right><span class=testo><strong><?php echo($stringa[file]);?>:</strong></span></TD>
                <TD><span class=testo><?php echo "<a href=lab_scarica.php?id_risorsa=$id_risorsa>$titolo</a> (".stringa_filesize($file_size).")";?></span></TD>
		</TR>
 	<?php }; ?>
	
      <TR> 
        <TD align=right valign=top><span class=testo><STRONG><?php echo($stringa[descrizione]);?>:</STRONG></span></TD>
        <TD><span class=testopiccolo><?php echo($descrizione);?></span></TD>
      </TR>  	
 	  
    </TABLE>
    <BR>
<hr size=1>
<?php 

if ($tipo==1) {
	$chi=$stringa[chi_scaricato];
} else {
	$chi=$stringa[chi_visto];
};

echo "
<span class=testo>
[<a href=\"javascript:;\" title=\"$chi\" onclick=\"javascript:apri_scheda('lab_materiali_chi.php?id_risorsa=$id_risorsa&tipo=$tipo','myRemoteLetto','height=500,width=300,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLetto');\">$chi</a>]
</span>
";

echo "<br><br>
<span class=testo><b>$stringa[commenti_aggiungi]:</b></span>
";

echo "<table border=0 width=400 cellpadding=5>
<form action=lab_materiali_commento_op.php method=post>
<input type=hidden name=id_risorsa value=\"$id_risorsa\">
<tr><td>
<textarea name=commento rows=5 cols=50>$stringa[scrivi_commento]</textarea>
</td></tr>
<tr><td>
<input type=submit value=\"$stringa[ok]\">
";
echo "</table>";
echo "</form>";
echo "<br>
</td></tr>
</table>
<br>";
?>

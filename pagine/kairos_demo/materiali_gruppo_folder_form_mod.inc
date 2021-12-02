<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[lavori_gruppo])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper("$stringa[modifica] $stringa[cartella]")."</b></span>
</td></tr>

";

echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>";
?>


<?php
$id_risorsa=$_REQUEST["id_risorsa"];
mysql_select_db($DBASE,$db);	
$query = "SELECT * FROM materiali_gruppo where id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$risorsa_padre=$riga["risorsa_padre"];		
$titolo_risorsa=htmlentities($riga["titolo"]);
$id_autore=$riga["id_autore"];		
$id_gruppo_risorsa=$riga["id_gruppo"];		

if ($risorsa_padre=="root") {
if ($ruolo<>"staff" and $ruolo<>"admin") {
	$query="SELECT gruppo_utenti.id_gruppo,gruppo_utenti.descrizione FROM iscrizioni_gruppo_pw,gruppo_utenti WHERE iscrizioni_gruppo_pw.id_gruppo=gruppo_utenti.id_gruppo AND gruppo_utenti.id_corso='$id_corso_s' AND gruppo_utenti.id_edizione='$id_edizione_s' AND iscrizioni_gruppo_pw.id_utente='$kairos_cookie[0]' ORDER BY gruppo_utenti.id_gruppo";
} else {
	$query="SELECT id_gruppo,descrizione FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo_gruppo='1'";
};

$result=$mysqli->query($query);
$elenco_gruppi="";
while ($riga=$result->fetch_array()) {
	$id_gruppo=$riga["id_gruppo"];
	$descr_gruppo=$riga["descrizione"];
	$sel="";
	if ($id_gruppo_risorsa==$id_gruppo) $sel="selected";
	$elenco_gruppi .= "<option value=\"$id_gruppo\" $sel>$descr_gruppo";
};
};

?>

<form action=materiali_gruppo_folder_mod_ok.php method=post name=modulo id=modulo>
<input type=hidden name=risorsa_padre value=<?php echo($risorsa_padre);?>>
<input type=hidden name=id_risorsa value=<?php echo($id_risorsa);?>>
    <TABLE border=0 width=461>

<?php if ($risorsa_padre=="root") { ?>	
<tr>
<td align=right valign=top>
<p><span class=testo><b><?php echo($stringa[gruppo]);?></b></span></p>
</td>
<td valign=top>
<select name=id_gruppo>
<?php echo($elenco_gruppi);?>
</select>
</td>
</tr>
<?php }; ?>
	  
      <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[descrizione]);?>:</STRONG></span></TD>
        <TD> 
			<INPUT type="text" maxLength=200 name=titolo 
            size=50 value="<?php echo($titolo_risorsa);?>">			
	    </TD>
      </TR>	  
	  
	   <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[autore]);?>:</STRONG></span></TD>
        <TD>
          <INPUT type="text" name=id_autore size=20 value="<?php echo($id_autore);?>">
          
		  <?php 
			echo "
<span class=\"testopiccolo\">
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup.php?ruolo=tutti&campo=id_autore','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup_op.php?ruolo=tutti&campo=id_autore','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["tutti"]."</a>]
</span>";
?>
		  </TD>
      </TR> 
	  	  
    </TABLE>
    <BR>
    <P align=center> 
      <INPUT type=submit value="<?php echo($stringa[modifica]);?>">
    </P>
  </FORM>
  
</td></tr></table>
<br>		

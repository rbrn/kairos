<?php
$padre=$_REQUEST["padre"];

mysql_select_db($DBASE,$db);	

$id_editor_gruppo="";

if ($padre<>"root") {
	$query="SELECT id_editor_gruppo FROM risorse_materiali WHERE id_risorsa='$padre' ";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$id_editor_gruppo=$riga["id_editor_gruppo"];
};
	
if ($ruolo=='admin') {
$query="SELECT id_risorsa,titolo FROM risorse_materiali WHERE tipo='2' ORDER BY id_risorsa ";
} else {
$query="SELECT id_risorsa,titolo FROM risorse_materiali WHERE tipo='2' AND (id_editor='$id_utente' or id_autore='$id_utente' or id_editor_gruppo='$id_editor_gruppo') ORDER BY id_risorsa ";
};

$result=$mysqli->query($query);

if ($padre=='root') {
	$elenco_cartelle = "<OPTION VALUE=\"root\" selected>root</OPTION>\n";
} else {
	$elenco_cartelle = "<OPTION VALUE=\"root\">root</OPTION>\n";	
};

while ($riga=$result->fetch_array()) {
	$cartella = $riga["id_risorsa"];
	$titolo = $riga["titolo"];
	
	if ($padre==$cartella) {
		$elenco_cartelle .= "<OPTION VALUE=\"$cartella\" selected>$titolo</OPTION>\n";
	} else {
		$elenco_cartelle .= "<OPTION VALUE=\"$cartella\">$titolo</OPTION>\n";	
	};
};
 

?>
<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_contenuti])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[nuovo_file])."</b></span>
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


<FORM action=materiali_file_add.php encType=multipart/form-data method=post name=modulo id=modulo>
<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>
 <input type=hidden name=tipo value=1>
    <TABLE border=0 width=461>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
      <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[cartella]);?>:</STRONG></span></TD>
        <TD>
			<SELECT NAME="risorsa_padre">
			<?php echo($elenco_cartelle);?>
			</SELECT> 
          </TD>
      </TR>	  	
	
	  <!--  
      <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[id_file]);?>:</STRONG></span></TD>
        <TD> 
			<INPUT type="text" maxLength=200 name=id_risorsa 
            size=20>
        </TD>
      </TR>
	-->
	
	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[file_caricare]);?>:</STRONG></span></TD>
        <TD>
          <INPUT type="file" name=titolo>
          </TD>
      </TR>
	  
	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[autore]);?>:</STRONG></span></TD>
        <TD>
          <INPUT type="text"  name=id_autore size=20  value="<?php echo($id_utente);?>">
          
		  
		  <?php 
			echo "
<span class=\"testopiccolo\">
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup.php?ruolo=tutti&campo=id_autore','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup_op.php?ruolo=tutti&campo=id_autore','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["tutti"]."</a>]
</span>";
?>

		  </TD>
      </TR>

      <TR> 
        <TD align=right valign=top><span class=testo><STRONG><?php echo($stringa[descrizione]);?>:</STRONG></span></TD>
        <TD><textarea name=descrizione rows=05 cols=70></textarea>
          </TD>
      </TR>  	

      <TR> 
        <TD align=right valign=top><span class=testo><STRONG><?php echo($stringa[parole_chiave]);?>:</STRONG></span></TD>
        <TD><textarea name=parole_chiave rows=05 cols=70></textarea>
          </TD>
      </TR>  		
	  	   
	  	  
    </TABLE>
    <BR>
    <P align=center> 
      <INPUT type=submit value="<?php echo($stringa[carica]);?>">
    </P>
  </FORM>
</td></tr></table>
<br>

<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[lavori_gruppo])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[modifica_file])."</b></span>
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
$descrizione_risorsa=htmlentities($riga["descrizione"]);
$file_size=$riga["file_size"];	
$id_autore=$riga["id_autore"];



?>

<form action=materiali_gruppo_file_mod_ok.php encType=multipart/form-data method=post name=modulo id=modulo>
<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>
<input type=hidden name=id_risorsa value="<?php echo($id_risorsa);?>">
<input type=hidden name=ex_titolo value="<?php echo($titolo_risorsa);?>">
<input type=hidden name=ex_file_size value="<?php echo($file_size);?>">
<input type=hidden name=risorsa_padre value="<?php echo($risorsa_padre);?>">
    <TABLE border=0 width=461>
    	  
	  	  
	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[file_caricare]);?>:</STRONG></span></TD>
        <TD><span class=testo><?php echo($titolo_risorsa);?></span> 
          <INPUT type="file" name=titolo>
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
	  
      <TR> 
        <TD align=right valign=top><span class=testo><STRONG><?php echo($stringa[descrizione]);?>:</STRONG></span></TD>
        <TD><textarea name=descrizione rows=05 cols=70><?php echo($descrizione_risorsa);?></textarea>
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

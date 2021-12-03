<?php
$padre=$_REQUEST["padre"];
mysql_select_db($DBASE,$db);	
?>

<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[lavori_gruppo])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[nuova_pagina_web])."</b></span>
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

  <FORM action=materiali_gruppo_web_add.php method=post name=modulo id=modulo>
  <INPUT name=MAX_FILE_SIZE type=hidden value=5097150>  
  <input type=hidden name=risorsa_padre value="<?php echo($padre);?>">
  
    <TABLE border=0 width=500>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
    
      <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[tipo]);?>:</STRONG></span></TD>
        <TD> 
			<INPUT type="radio" name="tipo" value="0" checked><span class=testo><?php echo($stringa[normale]);?></span> <INPUT type="radio" name="tipo" value="3"><span class=testo><?php echo($stringa[nota]);?></span>
        </TD>
      </TR>
	  	  
	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[titolo]);?>:</STRONG></span></TD>
        <TD>
          <INPUT type="text"  name=titolo size=50>
          </TD>
      </TR>
	  
	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[autore]);?>:</STRONG></span></TD>
        <TD>
          <INPUT type="text"  name=id_autore value="<?php echo($id_utente);?>" size=20>
          
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
        <TD align=right valign=top><span class=testo><STRONG><?php echo($stringa[url]);?>:</STRONG></span></TD>
        <TD><INPUT type="text"  name=url size=50>
          </TD>
      </TR> 
	  
	  	
<?php

echo"
<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[contenuto]:</b></span></td>
</tr>
<tr>
<td colspan=2 valign=top>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<TEXTAREA id=\"testo\" cols=80 name=\"testo\" rows=30>".$testo."</TEXTAREA>
</td></tr>
</table>
</td>
</tr>";

?>  	     
	  	  
    </TABLE>
    <BR>
<?php
echo "<input type=\"submit\" name=\"ok\" value=\"$stringa[ok]\" />";
?>
  </FORM>
</td></tr></table>
<br>

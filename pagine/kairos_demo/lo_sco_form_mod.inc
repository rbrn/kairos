<?php
$padre=$_REQUEST["padre"];

mysql_select_db($DBASE,$db);	

$id_editor_gruppo="";

$query="SELECT * FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);

$riga=$result->fetch_array();

$id_autore=htmlentities($riga["id_autore"]);
$titolo=htmlentities($riga["titolo"]);

$query="SELECT * FROM lo WHERE id_lo='$id_risorsa'";
$result=$mysqli->query($query);

$riga=$result->fetch_array();
$width=htmlentities($riga["width"]);
$height=htmlentities($riga["height"]);
	


?>
<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_repository])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper("$stringa[modifica] $stringa[lo]")."</b></span>
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


<FORM action="lo_sco_mod_op.php" method=post name=modulo id=modulo>
<input type=hidden name="id_risorsa" value="<?php echo $id_risorsa ?>">
    <TABLE border=0 width=461>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
	   
	
  
	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[autore]);?>:</STRONG></span></TD>
        <TD>
          <INPUT type="text"  name=id_autore size=20  value="<?php echo($id_autore);?>">
          
		  
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
        <TD align=right><span class=testo><STRONG><?php echo($stringa[titolo]);?>:</STRONG></span></TD>
        <TD> 
			<INPUT type="text" maxLength=200 name=titolo 
            size=50 value="<?php echo $titolo ?>">
        </TD>
      </TR>
	  
	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[larghezza_finestra]);?>:</STRONG></span></TD>
        <TD> 
			<INPUT type="text" maxLength=200 name=width 
            size=10 value="<?php echo $width ?>">
        </TD>
      </TR>
	  
	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[altezza_finestra]);?>:</STRONG></span></TD>
        <TD> 
			<INPUT type="text" maxLength=200 name=height 
            size=10 value="<?php echo $height ?>">
        </TD>
      </TR> 
	  
    </TABLE>
    <BR>
    <P align=center> 
      <INPUT type=submit value="<?php echo($stringa[ok]);?>">
    </P>
  </FORM>
</td></tr></table>
<br>

<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[lavori_gruppo])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper("$stringa[modifica] $stringa[pagina_web]")."</b></span>
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
$tipo=$riga["tipo"];
$id_autore=$riga["id_autore"];
$url=$riga["url"];
$tipo0="";
$tipo3="";


$file_codice=$PATH_ROOT_FILE."materiali/$cod_area/gruppo/$id_risorsa.inc";
if (file_exists($file_codice)) {
	$fd = fopen ($file_codice, "r");
	$testo = fread ($fd, filesize ($file_codice));
	fclose ($fd);
} else {
	$testo="";
};
     


switch ($tipo) {
	case 0:
		$tipo0="checked";
		break;
		
	case 3:
		$tipo3="checked";
		break;
};	

?>

<form action=materiali_gruppo_web_mod_ok.php method=post name=modulo id=modulo>
<input type=hidden name=id_risorsa value="<?php echo($id_risorsa);?>">
<input type=hidden name=risorsa_padre value="<?php echo($risorsa_padre);?>">
    <TABLE border=0 width=461>
      
	  
	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[tipo]);?>:</STRONG></span></TD>
        <TD> 
			<INPUT type="radio" name="tipo" value="0" <?php echo($tipo0);?>><span class=testo><?php echo($stringa[normale]);?></span> <INPUT type="radio" name="tipo" value="3" <?php echo($tipo3);?>><span class=testo><?php echo($stringa[nota]);?></span>
        </TD>
      </TR>

 	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[titolo]);?>:</STRONG></span></TD>
        <TD>
          <INPUT type="text" maxLength=150 name=titolo 
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

	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[url]);?>:</STRONG></span></TD>
        <TD><FONT face=verdana size=-1> 
          <INPUT type="text" maxLength=150 name=url size=50 value="<?php echo($url);?>">
          </TD>
      </TR>
	  
<?php
if (!$win_ie) {
echo"
<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[codice_contenuto]:</b></span></td>
</tr>
<tr>
<td colspan=2 valign=top>
<TEXTAREA cols=70 name=testo rows=10 wrap=virtual>".$testo."</TEXTAREA>
</td>
</tr>";
} else {
	echo "<input type=\"hidden\" name=\"testo\" id=\"testo\">\n
	<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[contenuto]:</b></span></td>
</tr>
	<tr>
	<td colspan=2 valign=top>
	";
	$modifica_testo=true;
	require "./include/editor_materiali.inc";
	echo "
	</td>
	</tr>
	";
};
?>  	     
	  	  
    </TABLE>
    <BR>
<?php
if (!$win_ie) {
echo "
<input type=submit value=$stringa[ok]>";
} else {
echo "<input type=submit value=$stringa[ok] onclick=\"inoltra();return true\">";
};	
?>
  </FORM>
</td></tr></table>
<br>

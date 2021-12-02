<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_contenuti])."</b></span>
</td></tr>

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
$query = "SELECT * FROM risorse_materiali where id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$risorsa_padre=$riga["risorsa_padre"];		
$titolo_risorsa=htmlentities($riga["titolo"]);		
$descrizione_risorsa=htmlentities($riga["descrizione"]);
$parole_chiave=htmlentities($riga["parole_chiave"]);	
$file_size=$riga["file_size"];	
$livello=$riga["livello"];
$id_gruppo=$riga["id_gruppo"];
$id_autore=$riga["id_autore"];

$livello01="";
$livello02="";
$livello03="";
$livello04="";
$livello05="";

$id_editor_gruppo="";
if ($risorsa_padre<>"root") {
$query_p = "SELECT id_editor_gruppo FROM risorse_materiali where id_risorsa='$risorsa_padre'";
$result_p=$mysqli->query($query_p);
$riga_p=$result_p->fetch_array();
$id_editor_gruppo=$riga_p["id_editor_gruppo"];	
};
     
if ($ruolo=='admin') {
$query="SELECT id_risorsa,titolo FROM risorse_materiali WHERE tipo='2' ORDER BY id_risorsa ";
} else {
$query="SELECT id_risorsa,titolo FROM risorse_materiali WHERE tipo='2' AND (id_editor='$id_utente' or id_autore='$id_utente' or id_editor_gruppo='$id_editor_gruppo') ORDER BY id_risorsa ";
};


$result=$mysqli->query($query);

if ($risorsa_padre=='root') {
	$elenco_cartelle = "<OPTION VALUE=\"root\" selected>root</OPTION>\n";
} else {
	$elenco_cartelle = "<OPTION VALUE=\"root\">root</OPTION>\n";	
};

while ($riga=$result->fetch_array()) {
	$cartella = $riga["id_risorsa"];
	$titolo = $riga["titolo"];

	if ($risorsa_padre==$cartella) {
		$elenco_cartelle .= "<OPTION VALUE=\"$cartella\" selected>$titolo</OPTION>\n";
	} else {
		$elenco_cartelle .= "<OPTION VALUE=\"$cartella\">$titolo</OPTION>\n";	
	};
}; 


switch ($livello) {
	case 1:
		$livello01="selected";
		break;
		
	case 2:
		$livello02="selected";
		break;

	case 3:
		$livello03="selected";
		break;

	case 4:
		$livello04="selected";
		break;
	
	case 5:
		$livello05="selected";
		break;
		
};		

?>

<form action=materiali_file_mod_ok.php encType=multipart/form-data method=post name=modulo id=modulo>
<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>
<input type=hidden name=id_risorsa value="<?php echo($id_risorsa);?>">
			<input type=hidden name=ex_titolo value="<?php echo($titolo_risorsa);?>">
			<input type=hidden name=ex_file_size value="<?php echo($file_size);?>">
    <TABLE border=0 width=461>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
	  <!--
      <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[id_file]);?>:</STRONG></span></TD>
        <TD> 
			
			<span class=testo><?php echo($id_risorsa);?></span>
        </TD>
      </TR>
	-->
      <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[cartella]);?>:</STRONG></span></TD>
        <TD>
			<SELECT NAME="risorsa_padre">
			<?php echo($elenco_cartelle);?>
			</SELECT> 
         </TD>
      </TR>	 		  
	  	  
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

      <TR> 
        <TD align=right valign=top><span class=testo><STRONG><?php echo($stringa[parole_chiave]);?>:</STRONG></span></TD>
        <TD><textarea name=parole_chiave rows=05 cols=70><?php echo($parole_chiave);?></textarea>
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

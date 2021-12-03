<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

$risorsa_padre=$_REQUEST["padre"];

$template_elenco="";
$template_elenco.="<OPTION VALUE=\"1\" selected>$stringa[solo_testo]</OPTION>";
$template_elenco.="<OPTION VALUE=\"12\" >$stringa[testo_immagine]</OPTION>";
$template_elenco.="<OPTION VALUE=\"13\" >$stringa[testo_video]</OPTION>";
$template_elenco.="<OPTION VALUE=\"14\" >$stringa[testo_flash]</OPTION>";
$template_elenco.="<OPTION VALUE=\"15\" >$stringa[testo_geogebra]</OPTION>";
$template_elenco.="<OPTION VALUE=\"2\" >$stringa[solo_immagine]</OPTION>";
$template_elenco.="<OPTION VALUE=\"3\" >$stringa[solo_video]</OPTION>";
$template_elenco.="<OPTION VALUE=\"4\" >$stringa[solo_flash]</OPTION>";
$template_elenco.="<OPTION VALUE=\"5\" >$stringa[commento]</OPTION>";



echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_repository])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[nuova_pagina_web])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=repository_index&id_cartella=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=repository_index&id_cartella=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";


?>
<TABLE BORDER=0 width=100%>
<tr>
<td>
 
<?php


echo "<form action=lo_pagina_add_op.php method=post name=modulo id=modulo>";
echo "<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">";
echo "<input type=\"hidden\" name=\"link_tutoriale\">";
echo "<input type=\"hidden\" name=\"link_tutoriale_post\">";
echo "<TABLE border=0 width=550>";

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[titolo]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo\" size=\"80\"></TD>
      </TR>";

	  
echo "<TR> 
        <TD align=right valign=top><input type=checkbox name=\"approfondimento\"></TD>
  		<TD><span class=testopiccolo><b>$stringa[approfondimento]</b></span></TD>
      </TR>";	 

echo "<TR> 
        <TD align=right valign=top><input type=checkbox name=\"glossario\"></TD>
  		<TD><span class=testopiccolo><b>$stringa[pag_glossario]</b></span></TD>
      </TR>";	
	    
echo "<TR> 
        <TD align=right valign=top><input type=checkbox name=\"riepilogo\"></TD>
  		<TD><span class=testopiccolo><b>$stringa[riepilogo]</b></span></TD>
      </TR>";		   
?>

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

<?php	  	  
echo "<TR>
		<TD align=\"right\" valign=\"top\"><span class=testo><b>$stringa[template]:</b></span></TD>
		<TD valign=\"top\"><SELECT name=\"tipo_pagina\" size=\"1\">$template_elenco</SELECT></TD>
		</TR>";

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[link_tutoriale_alternativo]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo_pagina\" size=\"50\" readonly>  <span class=testo>[<a href=\"javascript:;\" onclick=\"apri_scheda('index.php?risorsa=repository_cartella&id_cartella=$risorsa_padre&tipo_browse=link_tutoriale','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]</span></TD></TR>";	


echo "
<tr>
<td colspan=2 valign=top align=\"center\"><input type=\"submit\" name=\"ok\" value=\"$stringa[ok]\" /></td>
</tr>
";

echo "</TABLE>";


echo "</FORM>";
?>
		
</td></tr>
</table>

</td></tr>
</table>
<br>

<?php

echo "                </div>
            </div>
        </div>
    </div>
</div>"

?>

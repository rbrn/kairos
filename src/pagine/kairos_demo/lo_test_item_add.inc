<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";
$risorsa_padre=$_REQUEST["padre"];

$tipo_elenco="";
$tipo_elenco.="<OPTION VALUE=\"1\" selected>$stringa[sm_rs]</OPTION>";
$tipo_elenco.="<OPTION VALUE=\"2\" >$stringa[sm_rm]</OPTION>";
$tipo_elenco.="<OPTION VALUE=\"3\" >$stringa[vero_falso]</OPTION>";
$tipo_elenco.="<OPTION VALUE=\"4\" >$stringa[inserimento]</OPTION>";
$tipo_elenco.="<OPTION VALUE=\"5\" >$stringa[associazione]</OPTION>";
$tipo_elenco.="<OPTION VALUE=\"6\" >$stringa[aperta]</OPTION>";
$tipo_elenco.="<OPTION VALUE=\"7\" >$stringa[dragdrop]</OPTION>";
$tipo_elenco.="<OPTION VALUE=\"8\" >$stringa[cacciaerrore]</OPTION>";
$tipo_elenco.="<OPTION VALUE=\"9\" >$stringa[ascoltaescrivi]</OPTION>";
$tipo_elenco.="<OPTION VALUE=\"10\" >$stringa[cruciverba]</OPTION>";

$tipo_item="1";

echo "
<div style=\"height: 50px;\"></div>
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_repository])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[nuovo_quiz])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=repository_index&id_cartella=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=repository_index&id_cartella=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";


?>
<TABLE BORDER=0 width=100%;>
<tr>
<td>
 
<?php


echo "<form action=lo_test_item_add_op.php method=post name=modulo id=modulo>";
echo "<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">";
echo "<input type=\"hidden\" name=\"link_tutoriale\">";
echo "<input type=\"hidden\" name=\"link_tutoriale_post\">";
echo "<input type=\"hidden\" name=\"link_tutoriale_ref\">";
echo "<input type=\"hidden\" name=\"id_alternativo\">";
echo "<TABLE border=0 width=550>";

echo "<TR> 
        <TD align=right valign=top width=30%><span class=testo><b>$stringa[titolo]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo\" size=\"80\"><input type=checkbox name=\"mostra_titolo\" checked>&nbsp;<span class=testopiccolo>mostra</span></TD>
      </TR>";

echo "<TR> 
        <TD align=right valign=top width=30%><span class=testo><b>$stringa[consegna]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"consegna\" size=\"80\"></TD>
      </TR>";
	  	  
echo "<TR>
		<TD align=\"right\" valign=\"top\"><span class=testo><b>$stringa[tipo]:</b></span></TD>
		<TD valign=\"top\">	
		<SELECT name=\"tipo_item\" onchange=\"imposta_immagine_test()\" size=\"1\">$tipo_elenco</SELECT></TD>
		</TR>";

echo "<TR>
		<TD align=\"right\" valign=\"top\"><span class=testo><b>$stringa[esempio]:</b></span></TD>
		<TD valign=\"top\"><img name=\"img_test\" width=\"303\" height=\"143\" src=\"img/test_".$tipo_item.".gif\" align=\"top\"></TD>
		</TR>";

echo "<TR> 
        <TD align=right valign=top><input type=checkbox name=\"alternativo\"></TD>
  		<TD><span class=testopiccolo><b>$stringa[alternativo]</b></span></TD>
      </TR>";	 				

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[punteggio]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"peso\" size=\"10\"></TD>
     	</TR>";

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[msg_ok]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"msg_ok\" size=\"60\" value=\"".$stringa[msg_ok_content]."\"></TD>
     	</TR>";

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[msg_ko]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"msg_ko\" size=\"60\" value=\"".$stringa[msg_ko_content]."\"></TD>
     	</TR>";

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[link_tutoriale]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo_pagina\" size=\"50\" readonly>  <span class=testo>[<a href=\"javascript:;\" onclick=\"apri_scheda('index.php?risorsa=repository_cartella&id_cartella=$risorsa_padre&tipo_browse=link_tutoriale','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]</span></TD></TR>";				

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[link_tutoriale_post]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo_pagina_post\" size=\"50\" readonly>  <span class=testo>[<a href=\"javascript:;\" onclick=\"apri_scheda('index.php?risorsa=repository_cartella&id_cartella=$risorsa_padre&tipo_browse=link_tutoriale_post','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]</span></TD></TR>";	

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[link_tutoriale_ref]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo_pagina_ref\" size=\"50\" readonly>  <span class=testo>[<a href=\"javascript:;\" onclick=\"apri_scheda('index.php?risorsa=repository_cartella&id_cartella=$risorsa_padre&tipo_browse=link_tutoriale_ref','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]</span></TD></TR>";	

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[id_alternativo]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo_test\" size=\"50\" readonly>  <span class=testo>[<a href=\"javascript:;\" onclick=\"apri_scheda('index.php?risorsa=repository_cartella&id_cartella=$risorsa_padre&tipo_browse=link_test','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]</span></TD></TR>";	
					  
if ($tipo_test=="3") {
	echo "<TR>
		<TD align=\"right\" valign=\"top\"></TD>
		<TD valign=\"top\"><input type=\"checkbox\" name=\"altro\"><span class=testo><b>$stringa[chiedi_altro]</b></span></TD>
		</TR>";
};

echo"
<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[testo_domanda_esteso]:</b></span></td>
</tr>
<tr>
<td colspan=2 valign=top width=500>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<TEXTAREA id=\"testo\" cols=80 name=\"testo\" rows=30>".$testo."</TEXTAREA>
</td></tr>
</table>
</td>
</tr>";

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

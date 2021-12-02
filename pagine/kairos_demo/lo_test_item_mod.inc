<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";
$risorsa_padre=$_REQUEST["padre"];

$id_risorsa=$_REQUEST["id_risorsa"];
$query = "SELECT * FROM risorse_materiali where id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$risorsa_padre=$riga["risorsa_padre"];	
$id_item=$riga["id_gruppo"];

$query = "SELECT * FROM lo_test_item WHERE id_item='$id_item'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$titolo=htmlentities(($riga[titolo]));
$consegna=htmlentities(($riga[legend]));
$testo=htmlentities(($riga[domanda]));
$tipo_item=$riga[tipo_item];
$alternativo=$riga[alternativo];
$id_alternativo=$riga[id_alternativo];
$link_tutoriale=$riga[link_tutoriale];
$link_tutoriale_post=$riga[link_tutoriale_post];
$link_tutoriale_ref=$riga[link_tutoriale_ref];
$msg_ok=htmlentities(stripslashes($riga[msg_ok]));
$msg_ko=htmlentities(stripslashes($riga[msg_ko]));
$peso=htmlentities(stripslashes($riga[peso]));

if ($link_tutoriale) {
	$query_p="SELECT * FROM risorse_materiali WHERE id_risorsa='$link_tutoriale'";
	$result_p=$mysqli->query($query_p);
	$riga_p=$result_p->fetch_array();
	$titolo_pagina=htmlentities($riga_p[titolo]);
};			

if ($link_tutoriale_post) {
	$query_p="SELECT * FROM risorse_materiali WHERE id_risorsa='$link_tutoriale_post'";
	$result_p=$mysqli->query($query_p);
	$riga_p=$result_p->fetch_array();
	$titolo_pagina_post=htmlentities($riga_p[titolo]);
};		

if ($link_tutoriale_ref) {
	$query_p="SELECT * FROM risorse_materiali WHERE id_risorsa='$link_tutoriale_ref'";
	$result_p=$mysqli->query($query_p);
	$riga_p=$result_p->fetch_array();
	$titolo_pagina_ref=htmlentities($riga_p[titolo]);
};		

if ($id_alternativo) {
	$query_p="SELECT * FROM risorse_materiali WHERE id_risorsa='$id_alternativo'";
	$result_p=$mysqli->query($query_p);
	$riga_p=$result_p->fetch_array();
	$titolo_test=htmlentities($riga_p[titolo]);
};

$altro=$riga[altro];
$ex_tipo_item=$tipo_item;
$mostra_titolo=htmlentities($riga[mostra_titolo]);

$checked_titolo="";

if ($mostra_titolo) $checked_titolo="checked";

$checked_alternativo="";

if ($alternativo) $checked_alternativo="checked";

$tipi=array("sm_rs","sm_rm","vero_falso","inserimento","associazione","aperta","dragdrop","cacciaerrore","ascoltaescrivi","cruciverba");

//$tipi=array("sm_rs","sm_rm","vero_falso","inserimento","associazione","aperta");

$tipo_elenco="";
for ($i=0;$i<count($tipi);$i++) {
	$j=$i+1;
	$sel="";
	if ($tipo_item==$j) $sel="selected";
	$i_str=$tipi[$i];
	$tipo_elenco.="<OPTION VALUE=\"$j\" $sel>$stringa[$i_str]</OPTION>";
	
};

if ($ruolo=='admin') {
$query="SELECT id_risorsa,titolo FROM risorse_materiali WHERE tipo='20' AND url is NULL ORDER BY id_risorsa ";
} else {
$query="SELECT id_risorsa,titolo FROM risorse_materiali WHERE tipo='20' AND url is NULL AND (id_editor='$id_utente' or id_autore='$id_utente') ORDER BY id_risorsa ";
};

$result=$mysqli->query($query);

$elenco_cartelle = "";

while ($riga=$result->fetch_array()) {
	$cartella = $riga["id_risorsa"];
	$titolo_folder = $riga["titolo"];
	
	if ($cartella<>$id_risorsa) {
	if ($risorsa_padre==$cartella) {
		$elenco_cartelle .= "<OPTION VALUE=\"$cartella\" selected>$titolo_folder</OPTION>\n";
	} else {
		$elenco_cartelle .= "<OPTION VALUE=\"$cartella\">$titolo_folder</OPTION>\n";	
	};
	};
};  

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_repository])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[modifica_domanda_test])."</b></span>
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


echo "<form action=lo_test_item_mod_op.php method=post name=modulo id=modulo>";
echo "<input type=\"hidden\" name=\"id_item\" value=\"$id_item\">";
echo "<input type=\"hidden\" name=\"id_risorsa\" value=\"$id_risorsa\">";
echo "<input type=\"hidden\" name=\"ex_tipo_item\" value=\"$ex_tipo_item\">";
echo "<input type=\"hidden\" name=\"link_tutoriale\" value=\"$link_tutoriale\">";
echo "<input type=\"hidden\" name=\"link_tutoriale_post\" value=\"$link_tutoriale_post\">";
echo "<input type=\"hidden\" name=\"link_tutoriale_ref\" value=\"$link_tutoriale_ref\">";
echo "<input type=\"hidden\" name=\"id_alternativo\" value=\"$id_alternativo\">";
echo "<TABLE border=0 width=550>";
echo "
  <TR> 
        <TD align=right width=30%><span class=testo><STRONG>$stringa[cartella_sup]:</STRONG></span></TD>
        <TD>
			<SELECT NAME=\"risorsa_padre\">
			$elenco_cartelle
			</SELECT> 
          </TD>
      </TR>	
	  
 <TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[titolo]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo\" size=\"80\" value=\"$titolo\"><input type=checkbox name=\"mostra_titolo\" $checked_titolo>&nbsp;<span class=testopiccolo>mostra</span></TD>
      </TR>
	  
	   <TR> 
        <TD align=right valign=top><span class=testo><b>Consegna:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"consegna\" size=\"80\" value=\"$consegna\"></TD>
      </TR>
	  
<TR>
<TD align=\"right\" valign=\"top\"><span class=testo><b>$stringa[tipo]:</b></span></TD>";

	echo "<TD valign=\"top\"><SELECT name=\"tipo_item\" onchange=\"imposta_immagine_test()\" size=\"1\">$tipo_elenco</SELECT></TD>";

echo "</TR>";

echo "<TR>
		<TD align=\"right\" valign=\"top\"><span class=testo><b>$stringa[esempio]:</b></span></TD>
		<TD valign=\"top\"><img name=\"img_test\" width=\"303\" height=\"143\" src=\"img/test_".$tipo_item.".gif\" align=\"top\"></TD>
		</TR>";

echo "<TR> 
        <TD align=right valign=top><input type=checkbox name=\"alternativo\" $checked_alternativo></TD>
  		<TD><span class=testopiccolo><b>$stringa[alternativo]</b></span></TD>
      </TR>";	

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[punteggio]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"peso\" size=\"10\" value=\"$peso\"></TD>
     	</TR>";

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[msg_ok]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"msg_ok\" size=\"60\" value=\"$msg_ok\"></TD>
     	</TR>";

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[msg_ko]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"msg_ko\" size=\"60\" value=\"$msg_ko\"></TD>
     	</TR>";

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[link_tutoriale]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo_pagina\" size=\"50\" value=\"$titolo_pagina\" readonly>  <span class=testo>[<a href=\"javascript:;\" onclick=\"apri_scheda('index.php?risorsa=repository_cartella&id_cartella=$risorsa_padre&tipo_browse=link_tutoriale','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]</span>";

if (trim($link_tutoriale)) {
	echo "<br><input type=\"checkbox\" name=\"cancella_link_tutoriale\"><span class=testo>Rimuovi il link</span>";
};

echo"</TD></TR>";				

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[link_tutoriale_post]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo_pagina_post\" size=\"50\" value=\"$titolo_pagina_post\" readonly>  <span class=testo>[<a href=\"javascript:;\" onclick=\"apri_scheda('index.php?risorsa=repository_cartella&id_cartella=$risorsa_padre&tipo_browse=link_tutoriale_post','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]</span>";

if (trim($link_tutoriale_post)) {
	echo "<br><input type=\"checkbox\" name=\"cancella_link_tutoriale_post\"><span class=testo>Rimuovi il link</span>";
};

echo"</TD></TR>";	

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[link_tutoriale_ref]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo_pagina_ref\" size=\"50\" value=\"$titolo_pagina_ref\" readonly>  <span class=testo>[<a href=\"javascript:;\" onclick=\"apri_scheda('index.php?risorsa=repository_cartella&id_cartella=$risorsa_padre&tipo_browse=link_tutoriale_ref','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]</span>";

if (trim($link_tutoriale_ref)) {
	echo "<br><input type=\"checkbox\" name=\"cancella_link_tutoriale_ref\"><span class=testo>Rimuovi il link</span>";
};

echo"</TD></TR>";	

echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[id_alternativo]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo_test\" size=\"50\"  value=\"$titolo_test\" readonly>  <span class=testo>[<a href=\"javascript:;\" onclick=\"apri_scheda('index.php?risorsa=repository_cartella&id_cartella=$risorsa_padre&tipo_browse=link_test','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]</span>";

if (trim($id_alternativo)) {
	echo "<br><input type=\"checkbox\" name=\"cancella_id_alternativo\"><span class=testo>Rimuovi il link</span>";
};

echo"</TD></TR>";		
	  		
if ($tipo_test=="3") {
	$altro_chk="";
	if ($altro=="on") $altro_chk="checked";
	echo "<TR>
		<TD align=\"right\" valign=\"top\"></TD>
		<TD valign=\"top\"><input type=\"checkbox\" name=\"altro\" $altro_chk><span class=testo><b>$stringa[chiedi_altro]</b></span></TD>
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
</div>";
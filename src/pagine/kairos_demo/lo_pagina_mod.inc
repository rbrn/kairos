<?php
$risorsa_padre=$_REQUEST["padre"];

$id_risorsa=$_REQUEST["id_risorsa"];
$query = "SELECT * FROM risorse_materiali where id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$risorsa_padre=$riga["risorsa_padre"];	
$id_pagina=$riga["id_gruppo"];
$id_autore=$riga["id_autore"];

$query = "SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$titolo=htmlentities($riga[titolo]);
$tipo_pagina=$riga[tipo_pagina];
$approfondimento=$riga[approfondimento];
$riepilogo=$riga[riepilogo];
$glossario=$riga[glossario];
$ex_tipo_pagina=$tipo_pagina;
$link_tutoriale=$riga[id_alternativo];


if ($link_tutoriale) {
	$query_p="SELECT * FROM risorse_materiali WHERE id_risorsa='$link_tutoriale'";
	$result_p=$mysqli->query($query_p);
	$riga_p=$result_p->fetch_array();
	$titolo_pagina=htmlentities($riga_p[titolo]);
};			



$checked_appr="";
if ($approfondimento) $checked_appr="checked";

$checked_riep="";
if ($riepilogo) $checked_riep="checked";

$checked_glos="";
if ($glossario) $checked_glos="checked";

$tipi=array("solo_testo,1","testo_immagine,12","testo_video,13","testo_flash,14","testo_geogebra,15","solo_immagine,2","solo_video,3","solo_flash,4","commento,5");

$template_elenco="";
for ($i=0;$i<count($tipi);$i++) {
	$i_str=$tipi[$i];
	list($str_tipo,$indice)=split(",",$i_str);
	$sel="";
	if ($tipo_pagina==$indice) $sel="selected";
	
	$template_elenco.="<OPTION VALUE=\"$indice\" $sel>$stringa[$str_tipo]</OPTION>";
	
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
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[modifica_pagina_web])."</b></span>
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


echo "<form action=lo_pagina_mod_op.php method=post name=modulo id=modulo>";
echo "<input type=\"hidden\" name=\"id_pagina\" value=\"$id_pagina\">";
echo "<input type=\"hidden\" name=\"id_risorsa\" value=\"$id_risorsa\">";
echo "<input type=\"hidden\" name=\"ex_tipo_pagina\" value=\"$ex_tipo_pagina\">";
echo "<input type=\"hidden\" name=\"link_tutoriale\" value=\"$link_tutoriale\">";
echo "<input type=\"hidden\" name=\"link_tutoriale_post\" value=\"$link_tutoriale_post\">";
echo "<TABLE border=0 width=550>";
echo "
  <TR> 
        <TD align=right><span class=testo><STRONG>$stringa[cartella_sup]:</STRONG></span></TD>
        <TD>
			<SELECT NAME=\"risorsa_padre\">
			$elenco_cartelle
			</SELECT> 
          </TD>
      </TR>";	
	  
 echo "<TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[titolo]:</b></span></TD>
  		<TD><INPUT type=\"text\" name=\"titolo\" size=\"80\" value=\"$titolo\"></TD>
      </TR>";

	  
echo "<TR> 
        <TD align=right valign=top><input type=checkbox name=\"approfondimento\" $checked_appr></TD>
  		<TD><span class=testopiccolo><b>$stringa[approfondimento]</b></span></TD>
      </TR>";	  

echo "<TR> 
        <TD align=right valign=top><input type=checkbox name=\"glossario\" $checked_glos></TD>
  		<TD><span class=testopiccolo><b>$stringa[pag_glossario]</b></span></TD>
      </TR>";	
	  
echo "<TR> 
        <TD align=right valign=top><input type=checkbox name=\"riepilogo\" $checked_riep></TD>
  		<TD><span class=testopiccolo><b>$stringa[riepilogo]</b></span></TD>
      </TR>";	
?>

<TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[autore]);?>:</STRONG></span></TD>
        <TD>
          <INPUT type="text"  name=id_autore value="<?php echo($id_autore);?>" size=20>
          
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
  		<TD><INPUT type=\"text\" name=\"titolo_pagina\" size=\"50\" readonly value=\"$titolo_pagina\">  <span class=testo>[<a href=\"javascript:;\" onclick=\"apri_scheda('index.php?risorsa=repository_cartella&id_cartella=$risorsa_padre&tipo_browse=link_tutoriale','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]</span>";

if (trim($link_tutoriale)) {
	echo "<br><input type=\"checkbox\" name=\"link_cancella\"><span class=testo>Rimuovi il link a questo tutoriale</span>";
};
echo"</TD></TR>";	


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


<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

$id_pagina=$_REQUEST["id_pagina"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$azione=$_REQUEST["azione"];

$query = "SELECT * FROM lo_pagina WHERE id_pagina='$id_pagina'";
$result = $mysqli->query($query);
$riga=$result->fetch_array();

$titolo=htmlentities($riga[titolo]);
$approfondimento=$riga[approfondimento];
$tipo_pagina=$riga[tipo_pagina];
$id_editor=$riga[id_editor];

switch ($tipo_pagina) {
	case 1:
		$tipo_pag_stringa=$stringa[solo_testo];
		break;
		
	case 2:
		$tipo_pag_stringa=$stringa[solo_immagine];
		break;
		
	case 3:
		$tipo_pag_stringa=$stringa[solo_video];
		break;	
	
	case 4:
		$tipo_pag_stringa=$stringa[solo_flash];
		break;	
	
	case 12:
		$tipo_pag_stringa=$stringa[testo_immagine];
		break;	
	
	case 13:
		$tipo_pag_stringa=$stringa[testo_video];
		break;	
	
	case 14:
		$tipo_pag_stringa=$stringa[testo_flash];
		break;	
	
	case 15:
		$tipo_pag_stringa=$stringa[testo_geogebra];
		break;	
};		

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_repository])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper("$stringa[modifica] $stringa[pagina_web]")."</b></span>
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
echo "<TABLE border=0 width=550>";

echo "

 <TR>
        <TD align=right valign=top><span class=testo><b>$stringa[titolo]:</b></span></TD>
  		<TD><span class=testo>$titolo<span></TD>
      </TR>

<TR>
<TD align=\"right\" valign=\"top\"><span class=testo><b>$stringa[tipo]:</b></span></TD>";

	echo "
	<TD valign=\"top\">
	<span class=testo>$tipo_pag_stringa</span>
	";
	echo "</TD>";

echo "</TR>";

echo "</TABLE>";


require "./pagine/kairos_demo/lo_pagina_asset_edit_".$tipo_pagina.".inc";

?>

<?php

echo "
<form action=lo_pagina_asset_op.php method=post name=\"modulo\" id=\"modulo\">
<input type=\"hidden\" name=\"id_pagina\" value=\"$id_pagina\">
<input type=\"hidden\" name=\"tipo_pagina\" value=\"$tipo_pagina\">
<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

if ($tipo_pagina=="12" or $tipo_pagina=="13" or $tipo_pagina=="14" or $tipo_pagina=="15") {

	if (!$posizione and $tipo_pagina=="12") $posizione=1;
	if (!$posizione and ($tipo_pagina=="13" or $tipo_pagina=="14" or $tipo_pagina=="15")) $posizione=3;
	
	$posizioni[1]=$stringa[colonna_destra_multiplo];
	$posizioni[2]=$stringa[colonna_sinistra_multiplo];
	$posizioni[3]=$stringa[testo_destra];
	$posizioni[4]=$stringa[testo_sinistra];
	$posizioni[5]=$stringa[colonna_destra];
	$posizioni[6]=$stringa[colonna_sinistra];
	$posizioni[7]=$stringa[colonna_grande_destra];
	$posizioni[8]=$stringa[colonna_grande_sinistra];
	$posizioni[9]=$stringa[sopra]="Oggetto in alto";
	$posizioni[10]=$stringa[sotto]="Oggetto in basso";

	$i0=3;
	if ($tipo_pagina=="12") $i0=1;
	$elenco_posizioni="";
	$n0=count($posizioni);
	if ($tipo_pagina=="13" or $tipo_pagina=="14" or $tipo_pagina=="15" ) $n0=4;
	for ($i=$i0;$i<=$n0;$i++) {
		$sel="";
		if ($posizione==$i) $sel="selected";
		$elenco_posizioni.="<option value=\"$i\" $sel>$posizioni[$i]</option>";
	};
	$k=9;
	if ($tipo_pagina=="14") {
		$sel="";
		if ($posizione==$k) $sel="selected";
		$elenco_posizioni.="<option value=\"$k\" $sel>$posizioni[$k]</option>"; 
	}	
	echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>$stringa[posizione_relativa]:</b></span></td>
<td valign=top><select name=\"posizione\" onchange=\"imposta_immagine_layout()\">$elenco_posizioni</select> <img name=\"img_layout\" width=\"70\" height=\"50\" src=\"img/layout".$posizione.".gif\" align=\"top\"></td>
</tr>";

	};

if ($tipo_pagina=="1" or $tipo_pagina=="12" or $tipo_pagina=="13" or $tipo_pagina=="14" or $tipo_pagina=="15") {
echo "
<tr  bgcolor=\"$colore_sfondo\">
<td colspan=2 valign=top>
<span class=testo><b>$stringa[testo]:</b></span><br>
<table width=\"500\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<TEXTAREA id=\"testo\" cols=80 name=\"testo\" rows=30>".$testo."</TEXTAREA>
</td></tr>
</table>
</td>
</tr>";
};


if ($tipo_pagina=="2" or $tipo_pagina=="3" or $tipo_pagina=="4" or $tipo_pagina=="12" or $tipo_pagina=="13" or $tipo_pagina=="14" or $tipo_pagina=="15") {

	switch ($tipo_pagina) {
	case "12":
		$tipo_media="img";
		$nome_campo="file_immagine";
		$valore=$file_immagine;
		$label=$stringa[elenco_img];
		break;
		
	case "13":
		$tipo_media="video";
		$nome_campo="file_video";
		$valore=$file_video;
		$label=$stringa[elenco_video];
		break;
		
	case "14":
		$tipo_media="flash";
		$nome_campo="file_flash";
		$valore=$file_flash;
		$label=$stringa[elenco_flash];
		break;
	
	case "15":
		$tipo_media="ggb";
		$nome_campo="file_geogebra";
		$valore=$file_geogebra;
		$label=$stringa[elenco_geogebra];
		break;
		
	case "2":
		$tipo_media="img";
		$nome_campo="file_immagine";
		$valore=$file_immagine;
		$label=$stringa[elenco_img];
		break;
		
	case "3":
		$tipo_media="video";
		$nome_campo="file_video";
		$valore=$file_video;
		$label=$stringa[elenco_video];
		break;
		
	case "4":
		$tipo_media="flash";
		$nome_campo="file_flash";
		$valore=$file_flash;
		$label=$stringa[elenco_flash];
		break;
	};
	
	$label_posizione="";
        if ($tipo_pagina=="12" and ($posizione=="1" or $posizione=="2")) {
		echo "<tr bgcolor=\"$colore_sfondo\">
<td align=left valign=top colspan=2><span class=testo>[<a href=lo_pagina_asset_add_img.php?id_pagina=$id_pagina&posizione=$posizione&risorsa_padre=$risorsa_padre>$stringa[aggiungi_immagine]</span>]</span></td>
</tr>";
		$label_posizione="&nbsp;".$posizione_int;
	};

	echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>$stringa[$tipo_media]".$label_posizione.":</b></span></td>
<td><input type=\"text\" name=\"$nome_campo\" id=\"$nome_campo\" readonly value=\"$valore\" size=\"60\"><br>
<a href=\"javascript:;\" onclick=\"return lo_seleziona_media('gruppo','$tipo_media','$nome_campo');\"><span class=testopiccolo>$label</span></a></td>
</tr>";

	if ($tipo_media=="flash" and false) {
	echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>$stringa[larghezza]:</b></span></td>
<td><input type=\"text\" name=\"f_w\" id=\"f_w\" value=\"$f_w\" size=\"05\"></td>
</tr>";

	echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>$stringa[altezza]:</b></span></td>
<td><input type=\"text\" name=\"f_h\" id=\"f_h\" value=\"$f_h\" size=\"05\"></td>
</tr>";
	};


	echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>$stringa[alt_text]:</b></span></td>
<td><textarea name=\"alt_text\" id=\"$alt_text\"  rows=\"05\" cols=\"60\">$alt_text</textarea></td>
</tr>";

	if ($tipo_pagina=="13" or $tipo_pagina=="14" or $tipo_pagina=="15" or $tipo_pagina=="3" or $tipo_pagina=="4") {
	echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>$stringa[alt_img]:</b></span></td>
<td><input type=\"text\" name=\"alt_img\" id=\"alt_img\" readonly value=\"$alt_img\" size=\"60\"><br>
<a href=\"javascript:;\" onclick=\"return lo_seleziona_media('gruppo','img','alt_img');\"><span class=testopiccolo>$stringa[elenco_img]</span></a></td>
</tr>";
	};

	if ($tipo_pagina=="12" and ($posizione=="1" or $posizione=="2")) {
		$query_img="SELECT * FROM lo_pagina_asset WHERE id_pagina='$id_pagina' AND posizione_int>1 ORDER BY posizione_int";
		$result_img= $mysqli->query($query_img);
		while ($riga_img=$result_img->fetch_array()) {
			$id_pagina_asset_img=$riga_img["id_pagina_asset"];
			$tipo_media="img";
			$file_immagine=$riga_img["file_asset"];
			$valore=$file_immagine;
			$label=$stringa[elenco_img];
			$alt_text=$riga_img["alt_text"];
			$posizione_int=$riga_img["posizione_int"];
			$nome_campo="img_".$id_pagina_asset_img;
			
			echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>$stringa[$tipo_media] $posizione_int:</b></span></td>
<td><input type=\"text\" name=\"$nome_campo\" id=\"$nome_campo\" readonly value=\"$valore\" size=\"60\"><span class=testopiccolo>[<a href=lo_pagina_asset_del_img.php?id_pagina=$id_pagina&posizione_int=$posizione_int&risorsa_padre=$risorsa_padre>$stringa[elimina_immagine]</span>]<br>
<a href=\"javascript:;\" onclick=\"return lo_seleziona_media('gruppo','$tipo_media','$nome_campo');\"><span class=testopiccolo>$label</span></a></td>
</tr>";

			echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>$stringa[alt_text]:</b></span></td>
<td><textarea name=\"alt_text_".$id_pagina_asset_img."\" id=\"$alt_text_".$id_pagina_asset_img."\"  rows=\"05\" cols=\"60\">$alt_text</textarea></td>
</tr>";

		};
	};

	

	

};


if ($approfondimento<>"on" and ($tipo_pagina=="1" or $tipo_pagina=="12" or $tipo_pagina=="2")) {
$query="SELECT * FROM lo_pagina_asset WHERE tipo_asset='5' AND id_pagina='$id_pagina'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$file_audio="";
if ($riga) {
	$file_audio=$riga["file_asset"];
};
echo "
<tr>
<td colspan=2><hr size=1></td>
</tr>
<tr>
<td align=right valign=top><span class=testo><b>$stringa[audio_opzionale]:</b></span></td>
<td><input type=\"text\" name=\"file_audio\" id=\"file_audio\" readonly value=\"$file_audio\" size=\"60\"><br>
<a href=\"javascript:;\" onclick=\"return lo_seleziona_media('gruppo','audio','file_audio');\"><span class=testopiccolo>$stringa[elenco_suoni]</span></a>";

if ($file_audio) {
	echo "<br><input type=\"checkbox\" name=\"audio_cancella\"><span class=testo>Rimuovi il link a questo file audio</span>";
};
echo "</td>
</tr>";
};

echo "</table>\n";
echo "
</td></tr>
</table>";

if ($ruolo=='admin' or $id_utente==$id_editor) {
echo "
<input type=\"submit\" value=\"$stringa[ok]\">";
};

echo "</form>";

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
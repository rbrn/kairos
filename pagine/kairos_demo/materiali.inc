<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

if ($cod_area<>'kairos_larimart') {
	$stringa_mat=$stringa[materiali];
} else {
	$stringa_mat=$stringa[materiali_test];
};

if ($cod_area<>"kairos_elombardia" or !$id_corso_s) {

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr>
<td valign=top width=77% class=titolodot>";
echo strtoupper($stringa_mat)."</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=20%>&nbsp;</td>";
echo "</tr>";

echo "<tr><td valign=top width=77%>";

echo "
<br>
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr><td>";

echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
<tr><td>";

if ($cod_area=='kairos_larimart') {
   echo "<br><br><span class=testo>Per raggiungere la competenza del profilo che hai selezionato in home page, ? necessario superare i test qui elencati. I test superati saranno marcati dalla icona <img src=img/forum/approvo.gif width=15 height=15>. Quando tutti i test saranno stati superati, apparir? la stessa icona anche in <b>Home Page</b> accanto al profilo corrispondente.
</span>
<br>";

};

if ($id_corso_s) {
	$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='' OR id_gruppo IS NULL) AND tipo_risorsa='20' ORDER BY ordine";
$result=$mysqli->query($query);
	if ($result->num_rows) {
		echo "<p class=\"sottotitolopagina\">$stringa[lo_corso]</p>";
		require "./include/materiali_indice.inc";
	};

	$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='' OR id_gruppo IS NULL) AND tipo_risorsa<>'3' and tipo_risorsa<>'20' ORDER BY ordine";
$result=$mysqli->query($query);
	if ($result->num_rows) {
		echo "<p class=\"sottotitolopagina\">$stringa[materiali_corso]</p>";
		require "./include/materiali_indice.inc";
	};

	$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='' OR id_gruppo IS NULL) AND tipo_risorsa='3' ORDER BY ordine";
$result=$mysqli->query($query);
	if ($result->num_rows) {
		echo "<hr size=1>";
		echo "<p class=\"sottotitolopagina\">$stringa[questionari_corso]</p>";
		require "./include/materiali_indice.inc";
	};

	/* MATERIALI DI GRUPPO */
	$query_g="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
	$result_g=$mysqli->query($query_g);

	while ($riga_g=$result_g->fetch_array()) {
		$tit_gruppo=$riga_g["descrizione"];
		$id_gr=$riga_g["id_gruppo"];
		$id_tutor=$riga_g["id_tutor"];
		$istutor="";
		$mostra=0;
		if ($ruolo=="admin" or $ruolo=="staff") {
			if ($kairos_cookie[0]==$id_tutor) $istutor="(<b>sei tutor</b>)";
			$mostra=1;
		} else {
			$query3="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_utente='$kairos_cookie[0]' AND id_gruppo='$id_gr' LIMIT 1";
			$result3=$mysqli->query($query3);
			if ($result3->num_rows) $mostra=1;
			if (!$mostra) {
				$query3="SELECT * FROM iscrizioni_gruppo_pw WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_utente='$kairos_cookie[0]' AND id_gruppo='$id_gr' LIMIT 1";
				$result3=$mysqli->query($query3);
				if ($result3->num_rows) $mostra=1;
			}
		}

		if ($mostra) {
			$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='$id_gr') AND tipo_risorsa<>'20' ORDER BY ordine";
			$result=$mysqli->query($query);
			if ($result->num_rows) {
				echo "<hr size=1>";
				echo "<p class=\"sottotitolopagina\">Materiali del gruppo: $tit_gruppo $istutor</p>";
				require "./include/materiali_indice.inc";
			};

			$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='$id_gr') AND tipo_risorsa='20' ORDER BY ordine";
$result=$mysqli->query($query);
			if ($result->num_rows) {
				echo "<p class=\"sottotitolopagina\">Learning Object del gruppo: $tit_gruppo $istutor</p>";
				require "./include/materiali_indice.inc";
			};

		};
	};


};

$query = "SELECT * FROM materiali_sequenza WHERE id_corso='' and tipo_risorsa<>'20' ORDER BY ordine";
$result=$mysqli->query($query);
if ($result->num_rows) {
	echo "<hr size=1>";
	echo "<p class=\"sottotitolopagina\">$stringa[materiali_comuni]</p>";
	require "./include/materiali_indice.inc";

};

echo "</td></tr></table>";
echo "</td></tr></table>";

echo "</td></tr></table>";
echo "</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=20%>";

if ($cod_area=="kairos_amicosole") {
echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr>
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\">
<img src=\"img/ico_materiali_int.gif\" width=\"15\" height=\"16\" alt=\"\" border=\"0\"><span class=titolo>&nbsp;<b>Progetti Amico Sole</b></span>
</td>
</tr>

<tr><td>";

echo "
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">
<tr><td align=center>
<a href=\"index.php?risorsa=progetti_file_form_add\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_1','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_1\" align=\"middle\"></a>&nbsp;<a href=index.php?risorsa=progetti_file_form_add onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_1','','img/ico_apri_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[apri])."</span></a>
</td></tr>
</table>";

echo "</td></tr></table><br>";

};

echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr>
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\">
<img src=\"img/ico_materiali_int.gif\" width=\"15\" height=\"16\" alt=\"\" border=\"0\"><span class=titolo>&nbsp;<b>$stringa[database_lavori]</b></span>
</td>
</tr>

<tr><td>";

echo "
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">
<tr><td align=center>
<a href=\"index.php?risorsa=lab_materiali_index&id_cartella=0\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_2','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_2\" align=\"middle\"></a>&nbsp;<a href=index.php?risorsa=lab_materiali_index&id_cartella=0 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_2','','img/ico_apri_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[apri])."</span></a>
</td></tr>
</table>";

echo "</td></tr></table>";

echo "
<br>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr>
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\">
<img src=\"img/ico_materiali_int.gif\" width=\"15\" height=\"16\" alt=\"\" border=\"0\"><span class=titolo>&nbsp;<b>$stringa[cartelle_condivise]</b></span>
</td>
</tr>

<tr><td>";

echo "
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">
<tr><td align=center>
<a href=\"ftp_comune/\" target=\"_blank\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_3','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_3\" align=\"middle\"></a>&nbsp;<a href=\"ftp_comune/\" target=\"_blank\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_3','','img/ico_apri_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[apri])."</span></a>
</td></tr>
</table>";

echo "</td></tr></table>";


$lavori_g=true;
if ($ruolo<>"admin" and $ruolo<>"staff") {
	$query_g="SELECT * FROM iscrizioni_gruppo_pw WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_utente='$kairos_cookie[0]'";
	$result_g=$mysqli->query($query_g);
	if (!$result_g->num_rows) $lavori_g=false;
} else {
	$query_g="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo_gruppo='1'";
	$result_g=$mysqli->query($query_g);
	if (!$result_g->num_rows) $lavori_g=false;
};


if ($lavori_g) {

echo "
<br>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr>
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\">
<img src=\"img/ico_materiali_int.gif\" width=\"15\" height=\"16\" alt=\"\" border=\"0\"><span class=titolo>&nbsp;<b>$stringa[lavori_gruppo]</b></span>
</td>
</tr>
<tr><td>";
echo "
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">
<tr><td align=center>
<a href=\"index.php?risorsa=materiali_gruppo_index\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_4','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_4\" align=\"middle\"></a>&nbsp;<a href=\"index.php?risorsa=materiali_gruppo_index\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_4','','img/ico_apri_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[apri])."</span></a>
</td></tr>
</table>";

echo "</td></tr></table>";
};

if ($editor_lo and ($cod_area=="kairos_itc_scuola" or $cod_area=="kairos_eprof" or $cod_area=="kairos_concorsocontenuti07")) {
echo "
<br>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr>
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\">
<img src=\"img/ico_materiali_int.gif\" width=\"15\" height=\"16\" alt=\"\" border=\"0\"><span class=titolo>&nbsp;<b>$stringa[gestione_repository]</b></span>
</td>
</tr>
<tr><td>";
echo "
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">
<tr><td align=center>
<a href=\"index.php?risorsa=repository_index\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_4','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_5\" align=\"middle\"></a>&nbsp;<a href=\"index.php?risorsa=repository_index\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_5','','img/ico_apri_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[apri])."</span></a>
</td></tr>
</table>";
};

echo "</td></tr></table>";


echo "</td></tr></table>";

echo "</td></tr></table>";

} else {

	$img1="materiali_img/kairos_elombardia/materiali/".$id_corso_s."1.gif";
	$size=getimagesize($img1);
	$tag_img1=$size[3];

	$img2="materiali_img/kairos_elombardia/materiali/".$id_corso_s."2.gif";
	$size=getimagesize($img2);
	$tag_img2=$size[3];

?>

<table width="100%" border="0" cellspacing="0" cellpadding="0" bgcolor="d6f0ef">
  <tr>
    <td width="24%"><img src="<?php echo($img1);?>" <?php echo($tag_img1);?>></td>
    <td width="76%">
	<span class=titolopagina><?php echo($stringa_mat);?></span>
	</td>
  </tr>
</table>
<table width="100%" border="0" cellspacing="0" cellpadding="0" bgcolor="d6f0ef">
  <tr> 
    <td width="1" height="138" valign="top"><img src="<?php echo($img2);?>" <?php echo($tag_img2);?>></td>
    <td width="100%" height="138" valign="top"> 
      <table width="95%" border="0" cellspacing="0" cellpadding="0" align="left" bgcolor="#FFFFFF">
        <tr> 
          <td width="1"><img src="materiali_img/kairos_elombardia/materiali//corner-susx.gif" width="12" height="18"></td>
          <td width="100%">&nbsp;</td>
          <td width="1"> 
            <div align="right"><img src="materiali_img/kairos_elombardia/materiali//corner-sudx.gif" width="12" height="18"></div>
          </td>
        </tr>
        <tr> 
          <td width="1">&nbsp;</td>
          <td width="100%"> 
            <?php
$query = "SELECT * FROM materiali_sequenza WHERE id_corso='' ORDER BY ordine";
$result=$mysqli->query($query);
if ($result->num_rows) {
	require "./include/materiali_indice.inc";
	echo "<hr size=1>";
};

if ($id_corso_s) {
	$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY ordine";
$result=$mysqli->query($query);
	require "./include/materiali_indice.inc";
};

?>
              <p>&nbsp;</p>
            
          </td>
          <td width="1">&nbsp;</td>
        </tr>
        <tr> 
          <td width="1"><img src="materiali_img/kairos_elombardia/materiali//corner-giusx.gif" width="12" height="18"></td>
          <td width="100%">&nbsp;</td>
          <td width="1"> 
            <div align="right"><img src="materiali_img/kairos_elombardia/materiali//corner-giudx.gif" width="12" height="18"></div>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr> 
    <td colspan="2" height="10" valign="top">&nbsp;</td>
  </tr>
</table>

<?php 
};

echo "                </div>
            </div>
        </div>
    </div>
</div>";

?>

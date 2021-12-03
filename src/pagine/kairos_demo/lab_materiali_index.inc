<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";


require "./include/funzioni_lab_materiali.inc";
$id_cartella=$_REQUEST["id_cartella"];
$id_gruppo_lab=$_REQUEST["id_gruppo_lab"];
$id_utente=$kairos_cookie[0];

if (!isset($id_cartella)) {
	$query="select id_risorsa FROM lab_materiali WHERE titolo='$id_utente' and tipo=2 and id_corso='$id_corso_s' and id_edizione='$id_edizione_s'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$id_cartella=$riga[id_risorsa];
	if (!$id_cartella) {
		$query = "INSERT INTO lab_materiali (id_risorsa,tipo,risorsa_padre,titolo,descrizione,parole_chiave,id_autore,data_crea,id_corso,id_edizione,id_gruppo) VALUES (NULL,'2','0','$id_utente','','','$id_utente',NOW(),'$id_corso_s','$id_edizione_s','$id_gruppo_s')";
		$result=$mysqli->query($query);
		$id_cartella=$mysqli->insert_id;
	};
};
$ruolo=ruolo_utente($id_utente);

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[database_lavori])."</td></tr>
<tr><td>";
?>

<TABLE BORDER=0 width=100%>

<tr><td>
<?php

mysql_select_db($DBASE,$db);	

if ($id_cartella) {
	$query="select titolo,risorsa_padre,id_gruppo,id_autore FROM lab_materiali WHERE id_risorsa=$id_cartella";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$titolo=$riga[titolo];
	$id_gruppo_lab_s=$riga[id_gruppo];
	$id_cartella_sup=$riga["risorsa_padre"];
	$id_autore=$riga["id_autore"];
	$path_cartella=path_cartella_materiali($id_cartella_sup)."/".$titolo;
} else {
	$titolo="";
	$path_cartella=$titolo;
};

if ($id_cartella) {
	echo "<span class=testo><b>$stringa[contenuto_cartella]: $path_cartella</b></a><br><br></span>";
	echo "<a href=index.php?risorsa=lab_materiali_index&id_cartella=$id_cartella_sup&id_gruppo_lab=$id_gruppo_lab_s onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_cart_sup','','img/ico_cart_sup_over.gif',1)\"><img src=\"img/ico_cart_sup.gif\" width=\"20\" height=\"20\" alt=\"$stringa[dir_superiore]\" border=\"0\" name=\"img_cart_sup\" align=\"middle\"></a>&nbsp;<a href=index.php?risorsa=lab_materiali_index&id_cartella=$id_cartella_sup&id_gruppo_lab=$id_gruppo_lab_s onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_cart_sup','','img/ico_cart_sup_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[dir_superiore])."</span></a>&nbsp;&nbsp;";
};

if ($id_cartella<>0 and ($id_autore==$id_utente or $ruolo=='admin' or $ruolo=='staff')) { 
	echo "<a href=lab_materiali_form_add.php?padre=$id_cartella&tipo=0 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_web','','img/ico_nuovo_web_over.gif',1)\"><img src=\"img/ico_nuovo_web.gif\" width=\"20\" height=\"20\" alt=\"$stringa[nuovo_sito_web]\" border=\"0\" name=\"img_nuovo_web\" align=\"middle\"></a>&nbsp;<a href=lab_materiali_form_add.php?padre=$id_cartella&tipo=0 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_web','','img/ico_nuovo_web_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[nuovo_sito_web])."</span></a>&nbsp;&nbsp;";

	echo "<a href=lab_materiali_form_add.php?padre=$id_cartella&tipo=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_file','','img/ico_nuovo_file_over.gif',1)\"><img src=\"img/ico_nuovo_file.gif\" width=\"20\" height=\"20\" alt=\"$stringa[nuovo_file]\" border=\"0\" name=\"img_nuovo_file\" align=\"middle\"></a>&nbsp;<a href=lab_materiali_form_add.php?padre=$id_cartella&tipo=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_file','','img/ico_nuovo_file_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[nuovo_file])."</span></a>&nbsp;&nbsp;";

	echo "<a href=lab_materiali_form_add.php?padre=$id_cartella&tipo=2 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_cart','','img/ico_nuovo_cart_over.gif',1)\"><img src=\"img/ico_nuovo_cart.gif\" width=\"20\" height=\"20\" alt=\"$stringa[nuova_cartella]\" border=\"0\" name=\"img_nuovo_cart\" align=\"middle\"></a>&nbsp;<a href=lab_materiali_form_add.php?padre=$id_cartella&tipo=2 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_cart','','img/ico_nuovo_cart_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[nuova_cartella])."</span></a>&nbsp;&nbsp;";
};

if ($id_cartella<>0) {
echo "<span class=testopiccolo>".strtoupper($stringa[spazio_web_pers]).":&nbsp;</span>";
};

if ($id_cartella<>0 and ($id_autore==$id_utente or $ruolo=='admin' or $ruolo=='staff')) { 
	echo "<a href=\"ftp/index.php?altro_utente=$id_autore\" target=\"_blank\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_1','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_1\"></a>";
};

if ($id_cartella<>0) {
	$url_utente="";
	$file_utente_htm=$PATH_ROOT_FILE."utenti/$cod_area/$id_autore/index.htm";
	$file_utente_php=$PATH_ROOT_FILE."utenti/$cod_area/$id_autore/index.php";
			
	if (file_exists($file_utente_htm) or file_exists($file_utente_php)) {
		$url_utente=$PATH_ROOT."utenti/$cod_area/$id_autore";
	};
			
	if ($url_utente) {
		echo "&nbsp;&nbsp;<a href=\"$url_utente\" target=\"_blank\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_$id_autore','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_$id_autore\"></a>";
	};
};

?>

</td></tr>

<?php 
if (!$id_cartella and !$id_gruppo_lab) {
	$query="SELECT id_gruppo,descrizione FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo_gruppo=0";
	$result=$mysqli->query($query);
	$elenco_gruppi="<option value=\"qualunque\">$stringa[qualunque]</option>";
	while ($riga=$result->fetch_array()) {
		$id_gr=$riga[id_gruppo];
		$descr_gr=$riga[descrizione];
		$elenco_gruppi .= "<option value=\"$id_gr\">$descr_gr</option>";
	};
?>
<tr>
<form action=index.php method=post>
<input type=hidden name=risorsa value="lab_materiali_index">
<input type=hidden name=id_cartella value="0">
<span class=testo><?php echo($stringa[gruppo]);?></span>
<select name="id_gruppo_lab">
<?php echo($elenco_gruppi);?>
</select>
<input type=submit value="ok">
</form>
</td>
</tr>
<?php 
} else {
?>

<tr><td>
<!-- elenco risorse -->
<?php

echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
<tr><td>
";


thread_lab_cartella($id_cartella);
echo "</td></tr></table>";
echo "</td></tr></table>";
?>
<!-- fine elenco risorse -->
</td></tr>

<?php 
};
?>

</table>
</td></tr></table>
<br>

<?php
echo "                </div>
            </div>
        </div>
    </div>
</div>"
?>

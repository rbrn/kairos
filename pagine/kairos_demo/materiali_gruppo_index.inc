<?php
require "./include/funzioni_materiali_gruppo.inc";
$id_cartella=$_REQUEST["id_cartella"];

if (!isset($id_cartella)) {
	$id_cartella="root";
};

$query="SELECT * FROM contesto_cartella_gruppo WHERE id_utente='$id_utente' AND id_cartella='$id_cartella'";
$result=$mysqli->query($query);
$presente=$result->num_rows;
$riga=$result->fetch_array();

if (!$pagina) $pagina=$riga[pagina];

if (!$pagina) $pagina=1;

if ($presente) {
	$query="UPDATE contesto_cartella_gruppo SET pagina=$pagina WHERE id_utente='$id_utente' AND id_cartella='$id_cartella'";
} else {
	$query="INSERT INTO contesto_cartella_gruppo SET id_utente='$id_utente', id_cartella='$id_cartella',pagina=$pagina";
};
$mysqli->query($query);
		
$ruolo=ruolo_utente($kairos_cookie[0]);
$editabile=true;

if ($id_cartella<>"root") {
	mysql_select_db($DBASE);
	$query="select * FROM materiali_gruppo WHERE id_risorsa='$id_cartella'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$titolo=$riga[titolo];
	$id_cartella_sup=$riga["risorsa_padre"];
	
	if ($ruolo<>"admin" and $ruolo<>"staff") {
		$id_gruppo=gruppo_nodo($id_cartella);
		$query_g="SELECT * FROM iscrizioni_gruppo_pw WHERE id_utente='$kairos_cookie[0]' AND id_gruppo='$id_gruppo' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
		$result_g=$mysqli->query($query_g);
		$in_gruppo=$result_g->num_rows;
		if ($in_gruppo) {
			$editabile=true;
		} else {
			$editabile=false;
		};
	};
	
	$path_cartella=path_cartella($id_cartella_sup)."/".$titolo;
} else {
	$titolo="";
	$id_cartella_sup="";
	$path_cartella=$titolo;
};


?>

<?php 
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[lavori_gruppo])."</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=materiali\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=materiali\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
";


echo "<tr><td>";

mysql_select_db($DBASE,$db);	


if ($id_cartella_sup) {
	echo "<a href=index.php?risorsa=materiali_gruppo_index&id_cartella=$id_cartella_sup onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_cart_sup','','img/ico_cart_sup_over.gif',1)\"><img src=\"img/ico_cart_sup.gif\" width=\"20\" height=\"20\" alt=\"$stringa[dir_superiore]\" border=\"0\" name=\"img_cart_sup\" align=\"middle\"></a>&nbsp;<a href=index.php?risorsa=materiali_gruppo_index&id_cartella=$id_cartella_sup onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_cart_sup','','img/ico_cart_sup_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[dir_superiore])."</span></a>&nbsp;&nbsp;&nbsp;";
};


if ($editabile and $id_cartella<>"root") {
	if ($cod_area<>"kairos_eprof" or $id_cartella_sup<>"root") {
	echo "<a href=materiali_risorsa_gruppo_form_add.php?padre=$id_cartella&tipo=0 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_web','','img/ico_nuovo_web_over.gif',1)\"><img src=\"img/ico_nuovo_web.gif\" width=\"20\" height=\"20\" alt=\"$stringa[nuova_pagina_web]\" border=\"0\" name=\"img_nuovo_web\" align=\"middle\"></a>&nbsp;<a href=materiali_risorsa_gruppo_form_add.php?padre=$id_cartella&tipo=0 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_web','','img/ico_nuovo_web_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[nuova_pagina_web])."</span></a>&nbsp;&nbsp;&nbsp;";

	echo "<a href=materiali_risorsa_gruppo_form_add.php?padre=$id_cartella&tipo=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_file','','img/ico_nuovo_file_over.gif',1)\"><img src=\"img/ico_nuovo_file.gif\" width=\"20\" height=\"20\" alt=\"$stringa[nuovo_file]\" border=\"0\" name=\"img_nuovo_file\" align=\"middle\"></a>&nbsp;<a href=materiali_risorsa_gruppo_form_add.php?padre=$id_cartella&tipo=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_file','','img/ico_nuovo_file_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[nuovo_file])."</span></a>&nbsp;&nbsp;&nbsp;";
	};
};

if ($editabile) {
	if ($cod_area<>"kairos_eprof" or $ruolo=="admin" or $ruolo=="staff" or ($id_cartella<>"root")) {
	echo "<a href=materiali_risorsa_gruppo_form_add.php?padre=$id_cartella&tipo=2 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_cart','','img/ico_nuovo_cart_over.gif',1)\"><img src=\"img/ico_nuovo_cart.gif\" width=\"20\" height=\"20\" alt=\"$stringa[nuova_cartella]\" border=\"0\" name=\"img_nuovo_cart\" align=\"middle\"></a>&nbsp;<a href=materiali_risorsa_gruppo_form_add.php?padre=$id_cartella&tipo=2 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_nuovo_cart','','img/ico_nuovo_cart_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[nuova_cartella])."</span></a>&nbsp;";
	};
};

if ($id_cartella_sup) {
	$id_gruppo_cartella=gruppo_nodo($id_cartella);
	if ($id_gruppo_cartella) {
		$query_g="SELECT descrizione FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_cartella'";
		$result_g=$mysqli->query($query_g);
		$riga_g=$result_g->fetch_array();
		$descr_gruppo=$riga_g[descrizione];
		echo "<br><br><span class=testo><b>$stringa[gruppo]:</b> <a class=miolink href=\"javascript:;\" title=\"$stringa[componenti_gruppo]\" onclick=\"javascript:apri_scheda('gruppo_pw_iscritti.php?id_gruppo=$id_gruppo_cartella',                   'myRemoteGruppo',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowGruppo');\">$descr_gruppo</a></span>";

		

	};
	echo "<br><br><span class=testo><b>$stringa[contenuto_cartella]: $path_cartella</b></a></span>";
};

echo "</td></tr>";

echo "
<tr><td>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
";




?>


<tr><td>
<!-- elenco risorse -->
<?php
thread_risorse($id_cartella,$pagina);
?>
<!-- fine elenco risorse -->
</td></tr></table>

</td></tr></table>

</td></tr></table>
<br>

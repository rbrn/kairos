<?php
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];

$direttore=0;

$query="SELECT DISTINCT * FROM ruolo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_utente='$kairos_cookie[0]'";
$result=$mysqli->query($query);
if ($result->num_rows) $direttore=1;

if ($id_corso_s) {
$query = "SELECT * FROM edizioni WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$descr_edizione=$riga["descrizione"];

if (!$descr_edizione) $descr_edizione=$id_edizione_s;

$query="SELECT * FROM corso WHERE id_corso='$id_corso_s'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$descr_corso=$riga["descrizione"];
};

$query="";
$tutor=false;
if ($id_corso_s) {
	if ($ruolo=='staff') {
		$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_tutor='$id_utente'";
		$result=$mysqli->query($query);
		if ($result->num_rows) $tutor=true;
	};
};

if ($id_corso_s) {
	if ($ruolo=='admin' or $direttore) {
		$query="SELECT * FROM forum WHERE (id_corso='$id_corso_s' AND id_edizione='$id_edizione_s') ORDER BY tipo,id_corso,id_edizione,id_gruppo,ordine";
	} else {
		if ($tutor) $query="SELECT forum.id_forum,forum.descrizione,forum.tipo,forum.ordine,forum.id_gruppo,gruppo_utenti.descrizione as descr_gruppo FROM forum,gruppo_utenti WHERE forum.id_corso='$id_corso_s' AND forum.id_edizione='$id_edizione_s' AND gruppo_utenti.id_tutor='$id_utente' AND (gruppo_utenti.id_gruppo=forum.id_gruppo) AND forum.id_corso=gruppo_utenti.id_corso AND forum.id_edizione=gruppo_utenti.id_edizione ORDER BY forum.tipo,forum.id_corso,forum.id_edizione,forum.id_gruppo,ordine";
	}
} else {
	if ($ruolo=='admin') {
		$query="SELECT * FROM forum WHERE (tipo=0 or tipo=4) ORDER BY tipo,id_corso,id_edizione,id_gruppo,ordine";
	};
};

if($query)$result=$mysqli->query($query);

$tipo_forum = array("0"=>$stringa[generale], "1"=>$stringa[corso],"3"=>$stringa[laboratorio],"4"=>$stringa[staff]);

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>";

if ($id_corso_s) {
echo "
<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_index><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span></a>
</td></tr>

<tr>
<td valign=top width=100%><a href=index.php?risorsa=corsi_edizioni_index&id_corso=$id_corso_s><span class=testo><b>".strtoupper($stringa[gestione_edizioni])."</b></span></a>
</td></tr>
";

echo "
<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_forum])."</b></span>
</td></tr>";
} else {
echo "

<tr>
<td valign=top width=100%><span class=testo><b>".$stringa[utility]."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_forum_comuni])."</b></span>
</td></tr>";
};

if ($id_corso_s) {
echo "
<tr>
<td valign=top width=100%><span class=testo><b>$stringa[corso]:</b> $descr_corso: $descr_edizione</span>
</td></tr>";
};

if ($id_corso_s) {
	$indietro="index.php?risorsa=corsi_edizioni_tool&id_corso=$id_corso_s&id_edizione=$id_edizione_s";
} else {
	$indietro="index.php?risorsa=utility_index";
};

echo "
<tr>
<td valign=top width=100%>
<a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

if ($ruolo=='admin' or $tutor or $direttore) {
echo "
<a href=\"index.php?risorsa=creaforum&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_forumnuovo','','img/ico_forumnuovo_over.gif',1)\"><img border=\"0\" src=\"img/ico_forumnuovo.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[nuovo_forum]\" name=\"img_forumnuovo\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=creaforum&id_corso=$id_corso_s&id_edizione=$id_edizione_s\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_forumnuovo','','img/ico_forumnuovo_over.gif',1)\">".strtoupper($stringa[nuovo_forum])."</a></span>";
};

echo "
<br>
<br>
\n";

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";

echo "
<tr bgcolor=\"$colore_scuro\">
<td><span class=testonegativo><b>$stringa[pos]</b></span></td>
<td><span class=testonegativo><b>$stringa[descrizione]</b></td>
<td><span class=testonegativo><b>$stringa[tipo]</b></span></td>
<td><span class=testonegativo><b>$stringa[gruppo]</b></span></td>
<td><span class=testonegativo><b>$stringa[num_int]</b></span></td>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>
\n";


if ($query) {
$colore=$colore_sfondo;
while ($riga=$result->fetch_array()) {
	$id_forum = $riga["id_forum"];

	echo "<tr bgcolor=\"$colore\">\n";
	printf ("<td><span class=testo>%s</span></td>\n",$riga["ordine"]);
	printf ("<td><span class=testo>%s</span></td>\n",$riga["descrizione"]);
	printf ("<td><span class=testo>%s</span></td>\n",$tipo_forum[$riga["tipo"]]);
	$descr_gruppo=$riga["id_gruppo"];
	if ($riga["descr_gruppo"]) $descr_gruppo=$riga["descr_gruppo"];
	printf ("<td><span class=testo>%s</span></td>\n",$descr_gruppo);	

	$query_t = "SELECT * FROM forum_posts WHERE id_forum='$id_forum'";
	$result_t=$mysqli->query($query_t);
	$n_posts = $result_t->num_rows;
	echo "<td align=right><p><span class=testo>$n_posts</p></td>";
	echo "<td><a href=\"index.php?risorsa=editforum&id_forum=$riga[id_forum]&id_corso=$id_corso_s&id_edizione=$id_edizione_s\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$riga[id_forum]','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[edit]\" border=\"0\" name=\"img_mod_$riga[id_forum]\"></a></td>";	

	if (!$n_posts) {	
		echo "<td><a href=\"index.php?risorsa=msg&msg=conf_canc&pagina=delforum.php&id_forum=$riga[id_forum]&id_corso=$id_corso_s&id_edizione=$id_edizione_s\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$riga[id_forum]','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$riga[id_forum]\"></a></td>";
	} else {
		echo "<td>&nbsp;</td>";
	};
	echo "</tr>\n";
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
};
};

$query="";
if ($tutor) {
 $query="SELECT forum.id_forum,forum.descrizione,forum.tipo,forum.ordine,forum.id_gruppo FROM forum WHERE forum.id_corso='$id_corso_s' AND forum.id_edizione='$id_edizione_s' AND (forum.id_gruppo='') ORDER BY forum.tipo,forum.id_corso,forum.id_edizione,forum.id_gruppo,ordine";
};

if ($query and $tutor) {
$result=$mysqli->query($query);
$colore=$colore_sfondo;
while ($riga=$result->fetch_array()) {
	$id_forum = $riga["id_forum"];

	echo "<tr  bgcolor=\"$colore\">\n";
	printf ("<td><span class=testo>%s</span></td>\n",$riga["ordine"]);
	printf ("<td><span class=testo>%s</span></td>\n",$riga["descrizione"]);
	printf ("<td><span class=testo>%s</span></td>\n",$tipo_forum[$riga["tipo"]]);
	$descr_gruppo="";
	printf ("<td><span class=testo>%s</span></td>\n",$descr_gruppo);	

	$query_t = "SELECT * FROM forum_posts WHERE id_forum='$id_forum'";
	$result_t=$mysqli->query($query_t);
	$n_posts = mysql_numrows($result_t);
	echo "<td align=right><span class=testo>$n_posts</td>";

	echo "<td><a href=\"index.php?risorsa=editforum&id_forum=$riga[id_forum]&id_corso=$id_corso_s&id_edizione=$id_edizione_s\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$riga[id_forum]','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[edit]\" border=\"0\" name=\"img_mod_$riga[id_forum]\"></a></td>";	

	if (!$n_posts) {	
		echo "<td><a href=\"index.php?risorsa=msg&msg=conf_canc&pagina=delforum.php&id_forum=$riga[id_forum]&id_corso=$id_corso_s&id_edizione=$id_edizione_s\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$riga[id_forum]','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$riga[id_forum]\"></a></td>";
	} else {
		echo "<td>&nbsp;</td>";
	};
	echo "</tr>\n";
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
};
};

echo "</table>";

echo "</td></tr></table>";
echo "</td></tr></table><br>";
?>

<?php
$query2 = "SELECT * FROM forum WHERE id_forum='$id_forum'";
$result2=$mysqli->query($query2);
$dati_forum=$result2->fetch_array();
$tipo_forum=$dati_forum["tipo"];
$id_gruppo_forum=strtolower($dati_forum[id_gruppo]);
$id_gruppo_s=strtolower($id_gruppo_s);

$descr_gr_forum="";
if ($id_gruppo_forum) {
$query_gr="select * from gruppo_utenti where id_gruppo='$id_gruppo_forum' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
$result_r=$mysqli->query($query_gr);
$riga_gr=$result_r->fetch_array();
$tipo_gruppo_gr=$riga_gr["tipo_gruppo"];
$descr_gr=$riga_gr["descrizione"];

if ($tipo_gruppo_gr==0) {
	$pagina_g="gruppo_iscritti.php";
} else {
	$pagina_g="gruppo_pw_iscritti.php";
};

$descr_gr_forum=" ($stringa[gruppo]: <a class=miolink href=\"javascript:;\" title=\"$stringa[componenti_gruppo]\" onclick=\"javascript:apri_scheda('$pagina_g?id_gruppo=$id_gruppo_forum',                   'myRemoteGruppo',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowGruppo');\">$descr_gr</a>)";
};
		
$edit_forum=true;

if ($ruolo<>"staff" and $ruolo<>"admin") {
	if ($id_gruppo_forum AND !$tipo_gruppo_gr AND $id_gruppo_forum<>$id_gruppo_s) {
		$edit_forum=false;
	} else {
		if ($id_gruppo_forum AND $tipo_gruppo_gr) {
			$query_f="SELECT id_utente FROM iscrizioni_gruppo_pw WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_forum' AND id_utente='$kairos_cookie[0]'";
			$result_f=$mysqli->query($query_f);
			if (!$result_f->num_rows) $edit_forum=false;
		};
	};
};

//if ($kairos_cookie[0]=="ospite" and $cod_area=="kairos_eprof") $edit_forum=false;

$descr_forum = $dati_forum["descrizione"];
if (!$vista) {
	$vista = 'thread';
	$modo = 'esteso';
};

if ($vista=='thread' and !$modo) {
	$modo = 'esteso';
};	

if (!$pagina) $pagina=1;

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr>
<td valign=top width=77% class=titolodot>";
echo strtoupper($stringa[web_forum])."</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=20%>&nbsp;</td>";
echo "</tr>";

echo "<tr><td valign=top width=77%>";

echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr><td>";

echo "	
<p>
<span class=testo><b>$descr_forum</b> $descr_gr_forum</span>";

	echo "<a href=\"./materiali/$cod_area/$id_forum".".xml\"><img src=\"img/rss.gif\" width=\"19\" height=\"11\" alt=\"copia con il destro questo indirizzo e incollalo in un feedreader\" border=\"0\"></a>";

echo"
</p>
";

echo "

<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"2\" bgcolor=\"$colore_sfondo\">
<tr><td>
<table border=0 cellpadding=2>";

echo "<tr>";


echo "<td width=5>&nbsp;</td>";

echo "
<td valign=middle>
<span class=testo><b>$stringa[visualizzazione]:</b></span></td>";

echo "<td width=5>&nbsp;</td>";

if ($vista == 'thread') {
if ($cod_area<>"kairos_masterunitus" or 1) {
	/*
	if ($modo == 'esteso') {
 		echo "
		<td valign=middle>
		<a  href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=thread&modo=sintetico&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_sintetico','','img/ico_forum_view_sintetico_over.gif',1)\"><img src=\"img/ico_forum_view_sintetico.gif\" width=\"20\" height=\"20\" alt=\"$stringa[comprimi_struttura]\" border=\"0\" name=\"img_sintetico\"></a>
		</td>
		<td valign=middle>
		<span class=testopiccolo><a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=thread&modo=sintetico&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_sintetico','','img/ico_forum_view_sintetico_over.gif',1)\">$stringa[comprimi_struttura]</a></span>
		</td>";
	} else	{
		echo "
		<td valign=middle>
		<a  href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=thread&modo=esteso&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_esteso','','img/ico_forum_estesa_over.gif',1)\"><img src=\"img/ico_forum_estesa.gif\" width=\"20\" height=\"20\" alt=\"$stringa[espandi_struttura]\" border=\"0\" name=\"img_esteso\"></a>
		</td>
		<td valign=middle>
		<span class=testopiccolo><a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=thread&modo=esteso&pagina=$pagina onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_esteso','','img/ico_forum_estesa_over.gif',1)\">$stringa[espandi_struttura]</a></span>
		</td>";
	};
	*/
};
	
} else {
	echo "
		<td valign=middle>
		<a  href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=thread&modo=esteso&pagina=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_struttura','','img/ico_forum_estesa_over.gif',1)\"><img src=\"img/ico_forum_estesa.gif\" width=\"20\" height=\"20\" alt=\"$stringa[vista_struttura]\" border=\"0\" name=\"img_struttura\"></a>
		</td>";
	echo "<td valign=middle>";
	echo "<span class=testopiccolo><a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=thread&modo=esteso&pagina=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_struttura','','img/ico_forum_estesa_over.gif',1)\">$stringa[vista_struttura]</a></span>";	
	echo "</td>";
};



if ($vista <> "data") {
	echo "<td width=5>&nbsp;</td>";
	echo "
		<td valign=middle>
		<a  href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=data&modo=esteso&pagina=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_crono','','img/ico_forum_view_crono_over.gif',1)\"><img src=\"img/ico_forum_view_crono.gif\" width=\"20\" height=\"20\" alt=\"$stringa[vista_cronologica]\" border=\"0\" name=\"img_crono\"></a>
		</td>";
	echo "<td valign=middle>";
	echo "<span class=testopiccolo><a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=data&modo=esteso&pagina=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_crono','','img/ico_forum_view_crono_over.gif',1)\">$stringa[vista_cronologica]</a></span>";
	echo "</td>";
};

if ($vista <> "mark") {
	echo "<td width=5>&nbsp;</td>";
	echo "
		<td valign=middle>
		<a  href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=mark&modo=esteso&pagina=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_interes','','img/ico_forum_view_interes_over.gif',1)\"><img src=\"img/ico_forum_view_interes.gif\" width=\"20\" height=\"20\" alt=\"$stringa[interessanti]\" border=\"0\" name=\"img_interes\"></a>
		</td>";
	echo "<td valign=middle>";
	echo "<span class=testopiccolo><a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=mark&modo=esteso&pagina=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_interes','','img/ico_forum_view_interes_over.gif',1)\">$stringa[interessanti]</a></span>";		
	echo "</td>";
};



if ($vista <> "focus") {
	echo "<td width=5>&nbsp;</td>";
	echo "
		<td valign=middle>
		<a  href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=focus&modo=esteso&pagina=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_attinente','','img/attinente_2.gif',1)\"><img src=\"img/attinente_1.gif\" width=\"20\" height=\"20\" alt=\"attinenti\" border=\"0\" name=\"img_attinente\"></a>
		</td>";
	echo "<td valign=middle>";
	echo "<span class=testopiccolo><a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=focus&modo=esteso&pagina=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_attinente','','img/attinente_2.gif',1)\">ATTINENTI</a></span>";		
	echo "</td>";
};



if ($vista <> "read") {
	echo "<td width=5>&nbsp;</td>";
	echo "
		<td valign=middle>
		<a  href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=read&modo=esteso&pagina=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_read','','img/ico_forum_daleggere_over.gif',1)\"><img src=\"img/ico_forum_daleggere.gif\" width=\"20\" height=\"20\" alt=\"da leggere\" border=\"0\" name=\"img_read\"></a>
		</td>";
	echo "<td valign=middle>";
	echo "<span class=testopiccolo><a href=index.php?risorsa=forum_indice&id_forum=$id_forum&vista=read&modo=esteso&pagina=1 onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_read','','img/ico_forum_daleggere_over.gif',1)\">DA LEGGERE</a></span>";		
	echo "</td>";
};

echo "</tr></table>";

echo "
</td></tr>
</table>

</td></tr>
";

echo "
<tr><td>
<table border=0 cellpadding=10 cellspacing=0 bgcolor=\"$colore_sfondo\" width=\"100%\">
<tr>
<td>";

if ($vista=='thread') {
	$pag_size=10;
} else {
	$pag_size=20;
};


switch($vista) {
	case "data":
		$query="SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' ORDER BY data_last_mod DESC";
		$result=$mysqli->query($query);
		$tot_righe=$result->num_rows;

		$tot_pag=floor($tot_righe/$pag_size);
		if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;
		bydate();	
		break;

	case "thread":
		$query="SELECT id_post FROM forum_posts WHERE id_post_padre=0 AND id_forum='$id_forum' ORDER BY data_last_mod DESC";
		$result=$mysqli->query($query);
		$tot_righe=$result->num_rows;
		$tot_pag=floor($tot_righe/$pag_size);
		if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;
		
		if ($cod_area<>"kairos_masterunitus" or 1) {
			thread('0',$modo,'true');		
		} else {
			thread0('0',$modo,'true');	
		};
		break;

	case "mark":
		$query = "SELECT forum_posts.id_post FROM forum_mark,forum_posts WHERE forum_mark.id_utente='$id_utente' and forum_mark.id_post=forum_posts.id_post and forum_mark.id_forum='$id_forum' ORDER BY data_last_mod DESC ";
		$result=$mysqli->query($query);
		$tot_righe=$result->num_rows;
		$tot_pag=floor($tot_righe/$pag_size);
		if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;
		bymark();	
		break;	
		
	
	case "focus":
		$query = "SELECT id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post FROM forum_posts WHERE id_forum='$id_forum' AND (attinenza>2 and n_attinenze>2) ORDER BY id_post DESC ";
		$result=$mysqli->query($query);
		$tot_righe=$result->num_rows;
		$tot_pag=floor($tot_righe/$pag_size);
		if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;
		byfocus();	
		break;	
		
	case "read":
		$post_non_letti=array();
		$query = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' ORDER BY id_post DESC ";
		$result=$mysqli->query($query);
		while ($intervento=$result->fetch_array()) {
			$id_post = $intervento["id_post"];
			$query1 = "SELECT * FROM forum_read WHERE id_post = '$id_post' AND id_utente='$id_utente' LIMIT 1";
			$result1=$mysqli->query($query1);
			$letto = $result1->num_rows;
	
			if (!$letto) $post_non_letti[]=$id_post;

		};
		$tot_righe=count($post_non_letti);
		$tot_pag=floor($tot_righe/$pag_size);
		if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;
		byread();	
		break;
			
};

echo "</td></tr></table>";

echo "</td></tr></table>";
echo "<br>";

if ($pagina>1) {
	$id_prec=$pagina-1;
	echo "
	<span class=testopiccolo>
	[<a href=index.php?risorsa=forum_indice&id_forum=$id_forum&pagina=$id_prec&modo=$modo&vista=$vista><<</a>]
	</span> ";
};

if ($pagina<$tot_pag) {
	$id_succ=$pagina+1;
	echo " 
	<span class=testopiccolo>
	[<a href=index.php?risorsa=forum_indice&id_forum=$id_forum&pagina=$id_succ&modo=$modo&vista=$vista>>></a>]
	</span> ";
};	


echo "<span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?risorsa=forum_indice&id_forum=$id_forum&pagina=$i&modo=$modo&vista=$vista>$i</a>]
		";
	};
	$i++;
};
echo "</span>";


echo "</td></tr></table>";

echo "</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=20%>";

echo "		
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr> 
<td width=\"100%\" align=\"center\" valign=\"middle\"> 
<img src=\"img/ico_forum_utils.gif\" width=\"20\" height=\"20\" alt=\"\" border=\"0\" align=\"middle\"><span class=testo>&nbsp;<b>$stringa[utilities]</b></span>
</td>
</tr>

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">
\n";

if ($edit_forum) {
echo "
<tr><td>

<table border=0 cellspacing=5 cellpadding=0>
<tr>
<td valign=middle>
<a href=index.php?risorsa=forum_post&id_forum=$id_forum&op=nuovo&vista=$vista&modo=$modo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_forum_nuovo_post','','img/ico_forum_nuovo_post_over.gif',1)\"><img src=\"img/ico_forum_nuovo_post.gif\" width=\"20\" height=\"20\" alt=\"nuovo intervento\" border=\"0\" name=\"img_forum_nuovo_post\"></a>
</td>
<td valign=middle>
<span class=testopiccolo>
<a href=index.php?risorsa=forum_post&id_forum=$id_forum&op=nuovo&vista=$vista&modo=$modo onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_forum_nuovo_post','','img/ico_forum_nuovo_post_over.gif',1)\">$stringa[nuovo_intervento]</a></span></td>
</tr></table>

</td></tr>";

echo "
<tr> 
<td bgcolor=\"$colore_scuro_neutro\" height=\"1\"></td>
</tr>";

};


$query="SELECT * FROM forum_mail WHERE id_utente='$kairos_cookie[0]' AND id_forum='$id_forum'";
$result=$mysqli->query($query);
$op="on";
$ico_op_over="img/forum_inoltra2.gif";
$ico_op="img/forum_inoltra1.gif";
if ($result->num_rows) {
	$op="off";
	$ico_op_over="img/forum_no_inoltra2.gif";
	$ico_op="img/forum_no_inoltra1.gif";
};

$fm="forum_mail_".$op;
echo "
<tr><td>

<table border=0 cellspacing=5 cellpadding=0>
<tr><td width=20 valign=top><a href=forum_mail.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&op=$op onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_forum_notifica','','$ico_op_over',1)\"><img src=\"$ico_op\" width=\"21\" height=\"19\" alt=\"\" border=\"0\" name=\"img_forum_notifica\"></a></td><td colspan=$colspan>
<a href=forum_mail.php?id_forum=$id_forum&vista=$vista&modo=$modo&pagina=$pagina&op=$op onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_forum_notifica','','$ico_op_over',1)\"><span class=testopiccolo>".($stringa[$fm])."</span></a>
</td></tr>
</table>

</td></tr>";

echo "
<tr> 
<td bgcolor=\"$colore_scuro_neutro\" height=\"1\"></td>
</tr>";


if ($ruolo=="staff" or $ruolo=="admin") {
echo "
<tr><td>

<table border=0 cellspacing=5 cellpadding=0>
<tr><td width=20 valign=top><a href=\"javascript:;\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_forum_report','','img/ico_forumreport2.gif',1)\" onclick=\"javascript:apri_scheda('forum_report.php?id_forum=$id_forum',  'myRemoteLetto',        'height=500,width=300,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLetto');\"><img src=\"img/ico_forumreport1.gif\" width=\"21\" height=\"19\" alt=\"report interventi forum\" border=\"0\" name=\"img_forum_report\"></a></td>
<td colspan=$colspan><span class=testopiccolo><a class=miolink href=\"javascript:;\" title=\"report interventi forum\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_forum_report','','img/ico_forumreport2.gif',1)\" onclick=\"javascript:apri_scheda('forum_report.php?id_forum=$id_forum',  'myRemoteLetto',        'height=500,width=300,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLetto');\"><b>Report</b> interventi Forum</a></span>
</td></tr>
</table>

</td></tr>";


echo "
<tr> 
<td bgcolor=\"$colore_scuro_neutro\" height=\"1\"></td>
</tr>";

};

echo "<tr><td>";
echo "<table border=0 cellspacing=5 cellpadding=0>";

echo "<tr><td width=20 valign=top><img src=\"img/ico_forum_tutti_letti.gif\" width=\"20\" height=\"20\" alt=\"$stringa[segna_come_letti]\" border=\"0\" name=\"img_forum_tutti_letti\"></td>";

echo "<td valign=top>";
echo "
<form action=\"forum_letti.php\" method=\"post\">
<input type=\"hidden\" name=\"vista\" value=\"$vista\"><input type=\"hidden\" name=\"modo\" value=\"$modo\"><input type=\"hidden\" name=\"pagina\" value=\"$pagina\"><input type=\"hidden\" name=\"id_forum\" value=\"$id_forum\">
<span class=testopiccolo><b>Segna come letti</b> gli interventi:</span>";
echo "<table border=0 cellspacing=0 cellpadding=0>";

echo "<tr><td colspan=2><hr size=1></td></tr>";
echo "<tr><td valign=top><input type=\"radio\" name=\"filtro\" value=\"tutti\"></td><td><span class=testopiccolo><i>tutti</i></span></td></tr>";

echo "<tr><td colspan=2><hr size=1></td></tr>";
echo "<tr><td valign=top><input type=\"radio\" name=\"filtro\" value=\"vecchi\"></td><td><span class=testopiccolo><i>piÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ vecchi di giorni</i></span></td>
<tr><td></td><td><input type=\"text\" name=\"parametro\" size=\"5\" class=\"testopiccolo\"></td></tr>";

echo "<tr><td colspan=2><hr size=1></td></tr>";
echo "<tr><td valign=top><input type=\"radio\" name=\"filtro\" value=\"2\"></td><td><span class=testopiccolo><i>con attinenza inferiore a <b>2</b></i></span></td></tr>";

echo "<tr><td colspan=2><hr size=1></td></tr>";
echo "<tr><td valign=top><input type=\"radio\" name=\"filtro\" value=\"3\"></td><td><span class=testopiccolo><i>con attinenza inferiore a <b>3</b></i></span></td></tr>";

echo "<tr><td colspan=2><hr size=1></td></tr>";
echo "<tr><td valign=top><input type=\"radio\" name=\"filtro\" value=\"4\"></td><td><span class=testopiccolo><i>con attinenza inferiore a <b>4</b></i></span></td></tr>";

echo "<tr><td colspan=2><hr size=1></td></tr>";
echo "<tr><td valign=top></td><td><input type=\"submit\" value=\"ok\" class=\"testopiccolo\">
</td></tr>";

echo "</table>";

echo "</form>";

echo "</td></tr>";

echo "</table>";
echo "</td></tr>";


echo "</table>";

echo "</td></tr></table>";

echo "</td>";
echo "
</tr></table><br>";

echo "</td></tr></table>";

?>




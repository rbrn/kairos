<?php
if (file_exists($PATH_ROOT."pagine/$cod_area/colori.inc")) 
require $PATH_ROOT."pagine/$cod_area/colori.inc";

$codice .=  "
<html>
<head>
<title>$titolo</title>
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>";

$codice .= "
<link rel=\"stylesheet\" href=\"stili/stile_sito.css\">
</head>
";

$codice .= "
<body topmargin=\"0\" leftmargin=\"15\" bgcolor=\"#FFFFFF\" link=\"#535190\">";

$size=getimagesize($PATH_MODULO.$id_modulo."/img/testata.gif");
$tag_img=$size[3];

$codice .= "
<table width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=\"center\">
<tr><td>
<!-- TESTATA -->";

$table=0;
if (file_exists($PATH_ROOT."img/$cod_area/up-bg.gif")) { 
$codice .= "
<table border=0 cellpadding=\"0\" cellspacing=\"0\" width=100% background=\"img/up-bg.gif\" bgcolor=\"$colore_sfondo_testata\">";
$table=1;
};

if (file_exists($PATH_ROOT."img/$cod_area/up-bg.jpg")) { 
$codice .=  "
<table border=0 cellpadding=\"0\" cellspacing=\"0\" width=100% background=\"img/up-bg.jpg\" bgcolor=\"$colore_sfondo_testata\">";
$table=1;
};

if (!$table) {
$codice .=  "
<table border=0 cellpadding=\"0\" cellspacing=\"0\" width=100% bgcolor=\"$colore_sfondo_testata\">";
};

$codice .="<tr>";
if (file_exists($PATH_ROOT."img/$cod_area/testata.gif")) {
$codice .=  "
<td >
<div align=\"left\"><img src=\"img/testata.gif\" $tag_img border=0 alt=\"$cod_area\"></div></td>";
};

if (file_exists($PATH_ROOT."img/$cod_area/testata.jpg")) {
$codice .=  "
<td >
<div align=\"left\"><img src=\"img/testata.jpg\" $tag_img border=0 alt=\"$cod_area\"></div></td>";
};

$codice .= "
</tr>
</table>
<!-- FINE TESTATA -->
";


mysql_select_db($DBASE,$db);
if ($gruppo) {
	$query="SELECT titolo FROM materiali_gruppo WHERE id_risorsa='$id_modulo'";
} else {
	$query="SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_modulo'";
};
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$titolo=$riga["titolo"];

if ($gruppo) {
	$query="SELECT tipo,id_autore,url,id_gruppo,risorsa_padre FROM materiali_gruppo WHERE id_risorsa='$id_risorsa'";
} else {
	$query="SELECT tipo,id_autore,url,id_gruppo,risorsa_padre FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
};

$result=$mysqli->query($query);
$riga=$result->fetch_array();
$tipo=$riga["tipo"];
$id_autore=$riga["id_autore"];
$id_gruppo=$riga["id_gruppo"];
$risorsa_superiore=$riga["risorsa_padre"];
$url=$riga["url"];	

		if ($tipo==4) {
			if ($gruppo) {
				$query="SELECT id_autore FROM materiali_gruppo WHERE id_risorsa='$id_gruppo'";
			} else {
				$query="SELECT id_autore FROM risorse_materiali WHERE id_risorsa='$id_gruppo'";
			};
			$result=$mysqli->query($query);
			$riga=$result->fetch_array();
			$id_autore=$riga["id_autore"];
		};
			
		
		$pag_succ=materiali_pag_succ($id_risorsa,$risorsa_superiore);
		$pag_prec=materiali_pag_prec($id_risorsa,$risorsa_superiore);
		
		
		
		$codice.= "
		<table border=0 bgcolor=$colore_sfondo width=100%>
		<tr>
		<td><span class=sottotitolopagina>$titolo</span></td>
		<td align=right>";
		
		if ($id_corso_esporta) {
			$codice .= "<span class=testopiccolo><b>[<a href=\"../$id_corso_esporta".".htm\">Indice</a>]</b></span>";
		};
		$codice .="<span class=testopiccolo><b>[<a href=javascript:history.back()>Indietro</a>]</b></span>
		";
		if ($pag_prec) {
			$codice.= "<span class=testopiccolo><b>[<a href=$pag_prec><<</a>]</b></span>";
		} else {
			$codice.= "<span class=testopiccolo><b>[<<]</b></span>";
		};
		if ($pag_succ) {
			$codice.= "<span class=testopiccolo><b>[<a href=$pag_succ>>></a>]</b></span>";
		} else {
			$codice.= "<span class=testopiccolo><b>[>>]</b></span>";
		};
		$codice.= "</td></tr></table>";
		
		$codice.= "<table border=0 cellpadding=5 width=100%>
		<tr>
		<td valign=top bgcolor=$colore_sfondo width=180>";
		
		$codice .= capitolo($id_modulo,$id_risorsa);
		
		if ($id_autore) {
			$query="SELECT nome,cognome FROM utenti WHERE id_utente='$id_autore'";
			$result=$mysqli->query($query);
			$riga=$result->fetch_array();
			$nome_autore=$riga[nome]." ".$riga[cognome];
			
			$codice.= "
			<hr size=1>
			<ul style=\"list-style-type:none\">\n
			<li><span class=testopiccolo>Autore:<br>
			$nome_autore</span>

			</li>
			</ul>";
		};	
		
		$codice.= "</td>";
		
		$codice.= "<td valign=top>";
		
		$codice.= "<span class=testo>";
		
		if ($gruppo) {
			if (file_exists($PATH_ROOT."materiali/$cod_area/gruppo/$id_pagina.inc")) {
				$pagina=join('',file($PATH_ROOT."materiali/$cod_area/gruppo/$id_pagina.inc"));
			
				require "./copia_oggetti.php";
			
				$codice .= $pagina;
			} else {
				$codice .= "<a href=\"$url\" target=\"_blank\">$url</a>";
			};
		} else {
			if (file_exists($PATH_ROOT."materiali/$cod_area/$id_pagina.inc")) {
				$pagina=join('',file($PATH_ROOT."materiali/$cod_area/$id_pagina.inc"));
			
				require "./copia_oggetti.php";
			
				$codice .= $pagina;
			} else {
				$codice .= "<a href=\"$url\" target=\"_blank\">$url</a>";
			};
		};
		$codice .= "</span>";
		
		if ($gruppo) {
			$query_f="SELECT * FROM materiali_gruppo WHERE risorsa_padre='$risorsa_superiore' AND tipo=1 ORDER BY posizione,id_risorsa";
		} else {
			$query_f="SELECT * FROM risorse_materiali WHERE risorsa_padre='$risorsa_superiore' AND tipo=1 ORDER BY posizione,id_risorsa";
		};
		$result_f=$mysqli->query($query_f);
		
		if ($result_f->num_rows) {
			$codice .= "
			<hr size=1>
			<span class=testo><b>Download:</b></span><br>
			";
			while ($riga_f=$result_f->fetch_array()) {
				$id_file=$riga_f["id_risorsa"];
				$file_size=$riga_f["file_size"];
				$titolo_f=$riga_f["titolo"];
				$descrizione_f=$riga_f["descrizione"];
				$codice .= "
				<span class=testopiccolo><a href=\"risorse/$titolo_f\"  alt=\"$descrizione_f\">$titolo_f</a>&nbsp;".stringa_filesize($file_size)."<br>$descrizione_f</span>
				<br><br>";
			};
		};
		$codice .= "<hr size=1>";
		
		


		
		$codice .= "
		</td></tr>
		</table>";
		
		$codice .= "
		<table border=0 bgcolor=$colore_sfondo width=100%>
		<tr>
		<td><span class=sottotitolopagina>$titolo</span></td>
		<td align=right>";
		
		if ($id_corso_esporta) {
			$codice .= "<span class=testopiccolo><b>[<a href=\"../$id_corso_esporta".".htm\">Indice</a>]</b></span>";
		};
		$codice .="<span class=testopiccolo><b>[<a href=javascript:history.back()>Indietro</a>]</b></span>
		";
		if ($pag_prec) {
			$codice .= "<span class=testopiccolo><b>[<a href=$pag_prec><<</a>]</b></span>";
		} else {
			$codice .= "<span class=testopiccolo><b>[<<]</b></span>";
		};
		if ($pag_succ) {
			$codice .= "<span class=testopiccolo><b>[<a href=$pag_succ>>></a>]</b></span>";
		} else {
			$codice .= "<span class=testopiccolo><b>[>>]</b></span>";
		};
		$codice .= "</td></tr></table><br>";
		
		$codice .= "</body></html>";
?>

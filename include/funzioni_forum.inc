<?php
function byread() {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT,$stringa,
			$id_forum,$id_utente,$tipo_forum,$id_corso_s,$id_edizione_s,$ruolo,
			$pagina,$pag_size,$DBHOST;
	
	global $post_non_letti;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
// seleziono gli interventi del forum e li visualizzo
/*
$query = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' ORDER BY id_post DESC ";
$result=$mysqli->query($query);

	$post_non_letti=array();
	
while ($intervento=$result->fetch_array()) {
	$id_post = $intervento["id_post"];
	$query1 = "SELECT * FROM forum_read WHERE id_post = '$id_post' AND id_utente='$id_utente' LIMIT 1";
	$result1=$mysqli->query($query1);
	$letto = $result1->num_rows;
	
	if (!$letto) $post_non_letti[]=$id_post;

};
*/

$inizio=$pag_size*($pagina-1);

$progr=$inizio;

$righe=1;
while ($righe<=$pag_size and $progr<count($post_non_letti) ) {
	//vedo se l'utente ha letto l'intervento in questione
	$id_post = $post_non_letti[$progr];
	
	$query = "SELECT id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post,attinenza,n_attinenze FROM forum_posts WHERE id_post='$id_post'";
$result=$mysqli->query($query);
	$result=$mysqli->query($query);
	$intervento=$result->fetch_array();
	
	$id_post = $intervento["id_post"];
	
	$letto=false;
	
	if ($letto) {
		$flag = "";
	} else {
		$flag = " <i><b>$stringa[nuovo]</b></i>";
	};
	
	$id_autore=$intervento["id_autore"];
	$icona_post = $intervento["icona_post"];

	if (!$icona_post) {
		$icona_post = "messaggio";
	};

	
	$query_mark = "SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post' LIMIT 1";
	$result_mark=$mysqli->query($query_mark);
	$riga_mark = $result_mark->fetch_array();	
	if ($riga_mark) {
		echo "<img src=\"img/forum/spunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	} else {
		echo "<img src=\"img/forum/nospunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	}
	
	
	
	
	echo "<a href=\"javascript:;\" onclick=\"showPost('".$id_forum."','".$intervento[id_post]."','read','".$pagina."')\"><img src=\"img/ico_forum_daleggere.gif\" id=\"preview".$intervento[id_post]."\" width=\"20\" height=\"20\" border=\"0\" alt=\"clicca per vedere in anteprima l'intervento\"></a> ";
	
	if ($intervento[n_attinenze]>2) {
		$n_attinenze=$intervento[n_attinenze];
		$attinenza=$intervento[attinenza];
		echo "<span class=testopiccolo>"; for ($at=0;$at<$attinenza;$at++) { echo "<img src=\"img/piuma.gif\" width=\"15\" height=\"15\" border=\"0\" alt=\"\" >"; }; echo "<sup>$n_attinenze</sup></span>&nbsp;";
	};
	
	if ($intervento["nome_file"]) {
		echo "<img src=img/forum/allegato.gif width=16 height=16 border=0>";
	};
	
	printf("<img src=img/forum/%s.gif alt=%s> <span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post&id_forum=%s&id_post=%s&vista=read&modo=esteso&pagina=%s>%s</a></span>",$icona_post,$icona_post,$id_forum,$intervento["id_post"],$pagina,$intervento["oggetto"]);
	
	$ruolo_str="";
	if ($tipo_forum=='1' or $tipo_forum=='2' or $tipo_forum=='3') {
		$query_s="SELECT ruolo FROM ruolo_utenti WHERE id_utente='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_".$riga_s["ruolo"];
		if ($riga_s["ruolo"])  $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
		
		$query_s="SELECT id_tutor FROM gruppo_utenti WHERE id_tutor='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_tutor";
		if (!$ruolo_str and $riga_s["id_tutor"])  $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
	};
	
	echo "<span class=testopiccolo> <i><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_autore</a></i>$ruolo_str
</span>";

		
	printf("<span class=testopiccolo><i> - %s)</i></span>\n",$intervento["data_p"]);
	
	
	echo "<span class=\"testopiccolo\" id=\"post_".$intervento["id_post"]."\">$flag</span><br>";	
	
	$righe++;
	$progr++;
};


};


function bydate() {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT,$stringa,
			$id_forum,$id_utente,$tipo_forum,$id_corso_s,$id_edizione_s,$ruolo,
			$pagina,$pag_size,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
// seleziono gli interventi del forum e li visualizzo
$query = "SELECT id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post,attinenza,n_attinenze FROM forum_posts WHERE id_forum='$id_forum' ORDER BY id_post DESC ";
//$result=$mysqli->query($query);

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;

$righe=1;
$continua = true;
while ($intervento=$result->fetch_array()) {
	//vedo se l'utente ha letto l'intervento in questione
	
	$letto=true;
	
	if ($DBASE<>"kairos_masterunitus" or 1) {
	$id_post = $intervento["id_post"];
	$query1 = "SELECT * FROM forum_read WHERE id_post = '$id_post' AND id_utente='$id_utente' LIMIT 1";
	$result1=$mysqli->query($query1);
	$letto = $result1->num_rows;
	};
	
	if ($letto) {
		$flag = "";
	} else {
		$flag = " <i><b>$stringa[nuovo]</b></i>";
	};
	
	$id_autore=$intervento["id_autore"];
	$icona_post = $intervento["icona_post"];

	if (!$icona_post) {
		$icona_post = "messaggio";
	};


	$query_mark = "SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post'  LIMIT 1";
	$result_mark=$mysqli->query($query_mark);
	$riga_mark = $result_mark->fetch_array();	
	if ($riga_mark) {
		echo "<img src=\"img/forum/spunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	} else {
		echo "<img src=\"img/forum/nospunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	}
		
	
	
	echo "<a href=\"javascript:;\" onclick=\"showPost('".$id_forum."','".$intervento[id_post]."','data','".$pagina."')\"><img src=\"img/ico_forum_daleggere.gif\" id=\"preview".$intervento[id_post]."\" width=\"20\" height=\"20\" border=\"0\" alt=\"clicca per vedere in anteprima l'intervento\"></a> ";
	
	if ($intervento[n_attinenze]>2) {
		$n_attinenze=$intervento[n_attinenze];
		$attinenza=$intervento[attinenza];
		echo "<span class=testopiccolo>"; for ($at=0;$at<$attinenza;$at++) { echo "<img src=\"img/piuma.gif\" width=\"15\" height=\"15\" border=\"0\" alt=\"\" >"; }; echo "<sup>$n_attinenze</sup></span>&nbsp;";
	};
	
	if ($intervento["nome_file"]) {
		echo "<img src=img/forum/allegato.gif width=16 height=16 border=0>";
	};
	
	printf("<img src=img/forum/%s.gif alt=%s> <span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post&id_forum=%s&id_post=%s&vista=data&modo=esteso&pagina=%s>%s</a></span>",$icona_post,$icona_post,$id_forum,$intervento["id_post"],$pagina,$intervento["oggetto"]);
	
	$ruolo_str="";
	if ($tipo_forum=='1' or $tipo_forum=='2' or $tipo_forum=='3') {
		$query_s="SELECT ruolo FROM ruolo_utenti WHERE id_utente='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'  LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_".$riga_s["ruolo"];
		if ($riga_s["ruolo"])  $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
		
		$query_s="SELECT id_tutor FROM gruppo_utenti WHERE id_tutor='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'  LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_tutor";
		if (!$ruolo_str and $riga_s["id_tutor"]) $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
	};
	
	echo "<span class=testopiccolo> (<i><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_autore</a></i>$ruolo_str
</span>";

		
	printf("<span class=testopiccolo><i> - %s)</i></span>\n",$intervento["data_p"]);

	
	
	echo "<span class=\"testopiccolo\" id=\"post_".$intervento["id_post"]."\">$flag</span><br>";	
	
	$righe++;
};

	
};

function thread($id_padre,$modo,$margine="false") {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT,$HTTP_COOKIE_VARS,$stringa,
			$id_forum,$id_utente,$win_ie,$tipo_forum,$id_corso_s,$id_edizione_s,$ruolo,
			$pagina,$pag_size,$DBHOST;
	global $opera;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
// seleziono gli interventi del forum e li visualizzo
if ($id_padre) {
	$query = "SELECT id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post,attinenza,n_attinenze FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre='$id_padre'  ORDER BY data_last_mod DESC";
} else {
	$query = "SELECT id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post,attinenza,n_attinenze FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre=0 ORDER BY data_last_mod DESC";
	$inizio=$pag_size*($pagina-1);
	$query .= " LIMIT $inizio,$pag_size";
};

$result=$mysqli->query($query);

$intervento = $result->fetch_array();
	
if ($margine=="true") {	
	echo "<ul style=\"list-style-type:none;margin-left:5px\">\n";
} else {
	echo "<ul style=\"list-style-type:none\">\n";
};

$righe=1;
$continua = true;
while ($intervento and  $continua) {
	//vedo se l'utente ha letto l'intervento in questione
	$id_post = $intervento["id_post"];
	$query0 = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre='$id_post'";
	$result0=$mysqli->query($query0);
	$nrep = $result0->num_rows;
	
	
	if (!$icona_post) {
		$icona_post = "messaggio";
	};	
	
	$letto=true;
	
	if ($DBASE<>"kairos_masterunitus" or 1) {
	$query1 = "SELECT * FROM forum_read WHERE id_post = '$id_post' AND id_utente='$id_utente' LIMIT 1";
	$result1=$mysqli->query($query1);
	$letto = $result1->num_rows;
	};
	
	if ($letto) {
		$flag = "";
	} else {
		$flag = " <i><b>$stringa[nuovo]</b></i>";
	};
	
	$id_autore=$intervento["id_autore"];
	$icona_post = $intervento["icona_post"];

	if (!$icona_post) {
		$icona_post = "messaggio";
	};	
			
	echo "<li>\n";

	
	$query_mark = "SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post'  LIMIT 1";
	$result_mark=$mysqli->query($query_mark);
	$riga_mark = $result_mark->fetch_array();	
	if ($riga_mark) {
		echo "<img src=\"img/forum/spunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	} else {
		echo "<img src=\"img/forum/nospunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	}
	
	
	
	echo "<a href=\"javascript:;\" onclick=\"showPost('".$id_forum."','".$intervento[id_post]."','thread','".$pagina."')\"><img src=\"img/ico_forum_daleggere.gif\" id=\"preview".$intervento[id_post]."\" width=\"20\" height=\"20\" border=\"0\" alt=\"clicca per vedere in anteprima l'intervento\"></a> ";
	
	if ($id_padre==0) {
		echo "<a href=\"forum_pdf.php?id_thread=".$intervento[id_post]."\" target=\"_blank\"><img src=\"img/pdf_button.png\" width=\"16\" height=\"16\" alt=\"versione stampabile in pdf del thread\" border=\"0\"></a> ";
	};
	
	if ($intervento[n_attinenze]>2) {
		$n_attinenze=$intervento[n_attinenze];
		$attinenza=$intervento[attinenza];
		echo "<span class=testopiccolo>"; for ($at=0;$at<$attinenza;$at++) { echo "<img src=\"img/piuma.gif\" width=\"15\" height=\"15\" border=\"0\" alt=\"\" >"; }; echo "<sup>$n_attinenze</sup></span>&nbsp;";
	};
	
	if ($intervento["nome_file"]) {
		echo "<img src=img/forum/allegato.gif width=16 height=16 border=0>";
	};
	
	printf("<img src=img/forum/%s.gif alt=%s> <span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post&id_forum=%s&id_post=%s&vista=thread&modo=%s&pagina=%s >%s</a></span>",$icona_post,$icona_post,$id_forum,$intervento["id_post"],$modo,$pagina,$intervento["oggetto"]);
	
	$ruolo_str="";
	if ($tipo_forum=='1' or $tipo_forum=='2' or $tipo_forum=='3') {
		$query_s="SELECT ruolo FROM ruolo_utenti WHERE id_utente='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'  LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_".$riga_s["ruolo"];
		if ($riga_s["ruolo"]) $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
		
		$query_s="SELECT id_tutor FROM gruppo_utenti WHERE id_tutor='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'  LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_tutor";
		if (!$ruolo_str and $riga_s["id_tutor"]) $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
	};
	if ($id_autore=="fleo1") $id_autore="enza62";
	if ($id_autore=="fleo2") $id_autore="AntonioTul";
	
	echo "<span class=testopiccolo> (<i><a href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');$cancelBubble_stm\">$id_autore</a></i>$ruolo_str
</span>";
		
	printf("<span class=testopiccolo><i> - %s)</i></span>\n",$intervento["data_p"]);
	

	echo "<span class=\"testopiccolo\" id=\"post_".$intervento["id_post"]."\">$flag</span><br>";	
		
	if ($nrep) {
	 	thread($id_post,$modo); 
	} 
	
	echo "</li>";
	
	$righe++;
	$intervento = $result->fetch_array();
	if ($id_padre == 0) {
		if ($righe > $pag_size) {
			$continua = false;
		};
	};
		
	
};
	
echo "</ul>";

};

function thread0($id_padre,$modo,$margine="false") {
	global 	$DBASE,$DBUSER,$DBPWD,$DBHOST,$PATH_ROOT,$HTTP_COOKIE_VARS,$stringa,
			$id_forum,$id_utente,$win_ie,$tipo_forum,$id_corso_s,$id_edizione_s,
			$pagina,$pag_size;
	global $opera;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

// seleziono gli interventi del forum e li visualizzo
if ($id_padre) {
	$query = "SELECT id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post,attinenza,n_attinenze FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre='$id_padre'  ORDER BY data_last_mod DESC";
} else {
	$query = "SELECT id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post,attinenza,n_attinenze FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre=0 ORDER BY data_last_mod DESC";
	$inizio=$pag_size*($pagina-1);
	$query .= " LIMIT $inizio,$pag_size";
};

$result=$mysqli->query($query);

$intervento = $result->fetch_array();

/*
if ($margine=="true") {	
	echo "<ul style=\"list-style-type:none;margin-left:5px\">\n";
} else {
	echo "<ul style=\"list-style-type:none\">\n";
};
*/

echo "<table border=0 width=100%>";

forceFlush();
$righe=1;
$continua = true;
while ($intervento and  $continua) {
	//vedo se l'utente ha letto l'intervento in questione
	$id_post = $intervento["id_post"];
	
	$query0 = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre='$id_post'";
	$result0=$mysqli->query($query0);
	$nrep = $result0->num_rows;
	
	$iconapiu="";
	if ($nrep) {
		$iconapiu="<img  src=\"img/forum/piu.gif\" width=\"11\" height=\"11\" alt=\"\" border=\"0\">";
	};
	if (!$icona_post) {
		$icona_post = "messaggio";
	};	
	
	$letto=true;
	
	if ($DBASE<>"kairos_masterunitus" or 1) {
	$query1 = "SELECT * FROM forum_read WHERE id_post = '$id_post' AND id_utente='$id_utente'  LIMIT 1";
	$result1=$mysqli->query($query1);
	$letto = $result1->num_rows;
	};
	
	if ($letto) {
		$flag = "";
	} else {
		$flag = " <i><b>$stringa[nuovo]</b></i>";
	};
	
	$novita_interno="";
	
		
	if ($DBASE<>"kairos_masterunitus" or 1) {
	if ($nrep and !$flag) {
		$novita_interno= novita_thread($id_post);
		if ($novita_interno) {
			$flag = " <i><b>$stringa[nuovo_interno]</b></i>";	
		};
	};
	};
	
	$id_autore=$intervento["id_autore"];
	$icona_post = $intervento["icona_post"];

	if (!$icona_post) {
		$icona_post = "messaggio";
	};	
			
	//echo "<li>\n";
	
	echo "<tr>";
	echo "<td align=right>";
	echo "<span class=testopiccolo>$flag</span>&nbsp;";
	if ($nrep) {
		$id_p=$intervento["id_post"];
		if ($novita_interno) $id_p=$novita_interno;
		echo "<a href=index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_p&vista=thread&modo=$modo&pagina=$pagina><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_$id_edizione\" align=\"middle\"></a>";
	};
	
	echo "</td>";
	
	echo "<td>";
	$query_mark = "SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post' LIMIT 1";
	$result_mark=$mysqli->query($query_mark);
	$riga_mark = $result_mark->fetch_array();	
	
	if ($riga_mark) {
		echo "<img src=\"img/forum/spunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	} else {
		echo "<img src=\"img/forum/nospunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	}
	
	echo "<a href=\"javascript:;\" onclick=\"showPost('".$id_forum."','".$intervento[id_post]."','data','".$pagina."')\"><img src=\"img/ico_forum_daleggere.gif\" id=\"preview".$intervento[id_post]."\" width=\"20\" height=\"20\" border=\"0\" alt=\"clicca per vedere in anteprima l'intervento\"></a> ";

	if ($intervento[n_attinenze]>2) {
		$n_attinenze=$intervento[n_attinenze];
		$attinenza=$intervento[attinenza];
		echo "<span class=testopiccolo>"; for ($at=0;$at<$attinenza;$at++) { echo "<img src=\"img/piuma.gif\" width=\"15\" height=\"15\" border=\"0\" alt=\"\" >"; }; echo "<sup>$n_attinenze</sup></span>&nbsp;";
	};
		
	if ($intervento["nome_file"]) {
		echo "<img src=img/forum/allegato.gif width=16 height=16 border=0>";
	};
	
	printf("<img src=img/forum/%s.gif alt=%s> <span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post&id_forum=%s&id_post=%s&vista=thread&modo=%s&pagina=%s>%s</a></span>",$icona_post,$icona_post,$id_forum,$intervento["id_post"],$modo,$pagina,$intervento["oggetto"]);
	
	$ruolo_str="";
	if ($tipo_forum=='1' or $tipo_forum=='2' or $tipo_forum=='3') {
		$query_s="SELECT ruolo FROM ruolo_utenti WHERE id_utente='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_".$riga_s["ruolo"];
		if ($riga_s["ruolo"]) $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
		
		$query_s="SELECT id_tutor FROM gruppo_utenti WHERE id_tutor='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_tutor";
		if (!$ruolo_str and $riga_s["id_tutor"]) $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
	};
	if ($id_autore=="fleo1") $id_autore="enza62";
	if ($id_autore=="fleo2") $id_autore="AntonioTul";
	
	echo "<span class=testopiccolo> (<i><a href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');$cancelBubble_stm\">$id_autore</a></i>$ruolo_str
</span>";
		
	printf("<span class=testopiccolo><i> - %s)</i></span>\n",$intervento["data_p"]);
	
	
	echo "</td>";
	
	echo "</tr>";
	//echo "</li>";
	

	forceFlush();
	
	$righe++;
	$intervento = $result->fetch_array();
	if ($id_padre == 0) {
		if ($righe > $pag_size) {
			$continua = false;
		};
	};
		
	
};
	
//echo "</ul>";
echo "</table>";
};

function novita_thread($id_post) {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT,$id_utente,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
	$query = "SELECT id_post FROM forum_posts WHERE id_post_padre='$id_post'";
	$result=$mysqli->query($query);
	$novita="";
	while ($riga = $result->fetch_array() and !$novita) {
		$id_post0=$riga["id_post"];
		$query1 = "SELECT * FROM forum_read WHERE id_post = '$id_post0' AND id_utente='$id_utente' LIMIT 1";
		$result1=$mysqli->query($query1);
		$letto = $result1->num_rows;		
		if (!$letto) {
			$novita=$id_post0;
		} else {
			//$query0 = "SELECT id_post FROM forum_posts WHERE id_post_padre='$id_post' LIMIT 1";
			//$result0=mysql_query($query0,$db);
			//$nrep=mysql_num_rows($result0);
			//if ($nrep) {
				$novita=novita_thread($id_post0);
			//};
		};
	};
	return $novita;
}; 


function ascendente($id_post) {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$id_post_padre=0;
	
	if ($id_post) {
	//cerco il padre dei padri di questo intervento
	$query = "SELECT id_post_padre FROM forum_posts WHERE id_post='$id_post' LIMIT 1";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	$id_post_padre = $riga["id_post_padre"];
	};
	
	if ($id_post_padre == '0') {
		return $id_post;
	} else {
		return ascendente($id_post_padre);
	};

}; 

function cambia_forum($id_post,$id_forum,$nuovo_forum) {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
	//cambio forum a lui
	$query = "update forum_posts set id_forum='$nuovo_forum' where id_post='$id_post' and id_forum='$id_forum'";
	$result=$mysqli->query($query);
	
	$query = "update forum_read set id_forum='$nuovo_forum' where id_post='$id_post' and id_forum='$id_forum'";
	$result=$mysqli->query($query);
	
	//cerco i figli di questo intervento e li cambio di forum
	$query = "SELECT id_post FROM forum_posts WHERE id_post_padre='$id_post' and id_forum='$id_forum'";
	$result=$mysqli->query($query);
	
	while ($riga = $result->fetch_array()) {
		$id_post = $riga["id_post"];
	
		if (!$id_post) {
			return 'ok';
		} else {
			cambia_forum($id_post,$id_forum,$nuovo_forum);
		};
	};

}; 
		


function bymark() {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT,$stringa,
			$id_forum,$id_utente,$tipo_forum,$id_corso_s,$id_edizione_s,$ruolo,
			$pagina,$pag_size,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
// seleziono gli interventi del forum e li visualizzo
$query = "SELECT forum_posts.id_post,forum_posts.oggetto,forum_posts.id_autore,forum_posts.nome_file,DATE_FORMAT(forum_posts.data_post,'%d/%m/%Y %H:%i') as data_p,forum_posts.icona_post,attinenza,n_attinenze FROM forum_mark,forum_posts WHERE forum_mark.id_utente='$id_utente' and forum_mark.id_post=forum_posts.id_post and forum_mark.id_forum='$id_forum' ORDER BY forum_posts.id_post DESC ";
//$result=$mysqli->query($query);

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;


$righe=1;
while ($intervento=$result->fetch_array()) {
	//vedo se l'utente ha letto l'intervento in questione
	$id_post = $intervento["id_post"];
	
	$letto=true;
	
	if ($DBASE<>"kairos_masterunitus" or 1) {
	$query1 = "SELECT * FROM forum_read WHERE id_post = '$id_post' AND id_utente='$id_utente' LIMIT 1";
	$result1=$mysqli->query($query1);
	$letto = $result1->num_rows;
	};
	
	if ($letto) {
		$flag = "";
	} else {
		$flag = " <i><b>$stringa[nuovo]</b></i>";
	};
	
	$id_autore=$intervento["id_autore"];
	$icona_post = $intervento["icona_post"];

	if (!$icona_post) {
		$icona_post = "messaggio";
	};

	
	$query_mark = "SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post' LIMIT 1";
	$result_mark=$mysqli->query($query_mark);
	$riga_mark = $result_mark->fetch_array();	
	if ($riga_mark) {
		echo "<img src=\"img/forum/spunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	} else {
		echo "<img src=\"img/forum/nospunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	}
	
	
	
	
	echo "<a href=\"javascript:;\" onclick=\"showPost('".$id_forum."','".$intervento[id_post]."','mark','".$pagina."')\"><img src=\"img/ico_forum_daleggere.gif\" id=\"preview".$intervento[id_post]."\" width=\"20\" height=\"20\" border=\"0\" alt=\"clicca per vedere in anteprima l'intervento\"></a> ";
	
	if ($intervento[n_attinenze]>2) {
		$n_attinenze=$intervento[n_attinenze];
		$attinenza=$intervento[attinenza];
		echo "<span class=testopiccolo>"; for ($at=0;$at<$attinenza;$at++) { echo "<img src=\"img/piuma.gif\" width=\"15\" height=\"15\" border=\"0\" alt=\"\" >"; }; echo "<sup>$n_attinenze</sup></span>&nbsp;";
	};
	
	if ($intervento["nome_file"]) {
		echo "<img src=img/forum/allegato.gif width=16 height=16 border=0>";
	};
	
	printf("<img src=img/forum/%s.gif alt=%s> <span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post&id_forum=%s&id_post=%s&vista=mark&modo=esteso&pagina=%s>%s</a></span>",$icona_post,$icona_post,$id_forum,$intervento["id_post"],$pagina,$intervento["oggetto"]);
	
	$ruolo_str="";
	if ($tipo_forum=='1' or $tipo_forum=='2' or $tipo_forum=='3') {
		$query_s="SELECT ruolo FROM ruolo_utenti WHERE id_utente='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_".$riga_s["ruolo"];
		if ($riga_s["ruolo"])  $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
		
		$query_s="SELECT id_tutor FROM gruppo_utenti WHERE id_tutor='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_tutor";
		if (!$ruolo_str and $riga_s["id_tutor"])  $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
	};
	
	echo "<span class=testopiccolo> <i><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_autore</a></i>$ruolo_str
</span>";

		
	printf("<span class=testopiccolo><i> - %s)</i></span>\n",$intervento["data_p"]);
	
	
	echo "<span class=\"testopiccolo\" id=\"post_".$intervento["id_post"]."\">$flag</span><br>";	
	
	$righe++;

};


};

function thread_padre($id_post) {
	global 	$DBASE,$DBUSER,$DBPWD,$DBHOST;
	global  $id_forum;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

	$query="SELECT id_post,id_post_padre FROM forum_posts WHERE id_post='$id_post' AND id_forum='$id_forum' LIMIT 1";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	
	$id_post_padre=$riga[id_post_padre];
	
	if ($id_post_padre==0) {
		return $id_post;
	} else {
		return thread_padre($id_post_padre);
	};
};


function thread_sintetico($id_padre) {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT,$HTTP_COOKIE_VARS,$stringa,
			$id_forum,$id_utente,$win_ie,$tipo_forum,$id_corso_s,$id_edizione_s,
			$pagina,$pag_size,$id_post_view,$vista,$modo,$kairos_cookie,$ruolo,
			$colore_sfondo,$colore_sfondo_neutro,$DBHOST;
	
	global $opera;
	
	//$modo="esteso";

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

	$query = "SELECT id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre='$id_padre' ORDER BY data_last_mod DESC";


	$result=$mysqli->query($query);


	$intervento = $result->fetch_array();

	
echo "<ul style=\"list-style-type:none;\">\n";
$righe=1;
$continua = true;
while ($intervento and  $continua) {
	//vedo se l'utente ha letto l'intervento in questione
	$id_post = $intervento["id_post"];
	$query0 = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre='$id_post'";
	$result0=$mysqli->query($query0);
	$nrep = $result0->num_rows;
	
	
	if (!$icona_post) {
		$icona_post = "messaggio";
	};	
	
	$letto=true;
	

	$query1 = "SELECT * FROM forum_read WHERE id_post = '$id_post' AND id_utente='$id_utente' LIMIT 1";
	$result1=$mysqli->query($query1);
	$letto = $result1->num_rows;
	
	
	if ($letto) {
		$flag = "";
	} else {
		$flag = " <i><b>$stringa[nuovo]</b></i>";
	};
	
	$id_autore=$intervento["id_autore"];
	$icona_post = $intervento["icona_post"];

	if (!$icona_post) {
		$icona_post = "messaggio";
	};	
	
	if ($intervento[id_post]==$id_post_view) {
		$bgcolor=$colore_sfondo;
	} else {
		$bgcolor=$colore_sfondo_neutro;
	};		
	echo "<li>\n";


	
	if ($nrep) {
		echo "
	<p style=\"background-color:$bgcolor;margin-bottom=5pt;margin-top=5pt\">";
	} else {
		echo "
		<p style=\"background-color:$bgcolor;margin-bottom=5pt;margin-top=5pt\">
		";
	};
	
	
	$query_mark = "SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post' LIMIT 1";
	$result_mark=$mysqli->query($query_mark);
	$riga_mark = $result_mark->fetch_array();	
	if ($riga_mark) {
		echo "<img src=\"img/forum/spunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	} else {
		echo "<img src=\"img/forum/nospunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	}
		
	if ($intervento["nome_file"]) {
		echo "<img src=img/forum/allegato.gif width=16 height=16 border=0>";
	};


	echo "<a href=\"javascript:;\" onclick=\"showPost('".$id_forum."','".$intervento[id_post]."','".$vista."','".$pagina."')\"><img src=\"img/ico_forum_daleggere.gif\" id=\"preview".$intervento[id_post]."\" width=\"20\" height=\"20\" border=\"0\" alt=\"clicca per vedere in anteprima l'intervento\"></a> ";
	
	echo "<img src=img/forum/$icona_post".".gif alt=$icona_post> <span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$intervento[id_post]&vista=$vista&modo=$modo&pagina=$pagina  $cancelBubble title=\"$intervento[data_p]\">$intervento[oggetto]</a></span>";
	
	
	
	echo "<span class=testopiccolo> (<i><a href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');$cancelBubble_stm\">$id_autore</a></i>)</span>";
		
		
	echo "<span class=\"testopiccolo\" id=\"post_".$intervento["id_post"]."\">$flag</span></p>";
	
	if ($nrep) {
	 	thread_sintetico($intervento["id_post"]); 
	} 
	
	echo "</li>";
	
	$righe++;
	$intervento = $result->fetch_array();
	if ($id_padre == 0) {
		if ($righe > $pag_size) {
			$continua = false;
		};
	};
		
	
};
	
echo "</ul>";

};

function thread_view($id_padre) {
	global 	$DBASE,$DBUSER,$DBPWD,$DBHOST,$PATH_ROOT,$HTTP_COOKIE_VARS,$stringa,
			$id_forum,$id_utente,$win_ie,$tipo_forum,$id_corso_s,$id_edizione_s,
			$pagina,$pag_size,$id_post_view,$vista,$modo,$kairos_cookie,$ruolo,
			$colore_sfondo,$colore_sfondo_neutro;
	
	global $opera;
	
	//$modo="esteso";

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

	$query = "SELECT id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post='$id_padre' ORDER BY data_last_mod DESC";


	$result=$mysqli->query($query);


	$intervento = $result->fetch_array();

	
echo "<ul style=\"list-style-type:none;margin-left:5px\">\n";
$righe=1;
$continua = true;
while ($intervento and  $continua) {
	//vedo se l'utente ha letto l'intervento in questione
	$id_post = $intervento["id_post"];
	$query0 = "SELECT id_post FROM forum_posts WHERE id_forum='$id_forum' AND id_post_padre='$id_post'";
	$result0=$mysqli->query($query0);
	$nrep = $result0->num_rows;
	
	
	if (!$icona_post) {
		$icona_post = "messaggio";
	};	
	
	$letto=true;
	
	if ($DBASE<>"kairos_masterunitus" or 1) {
	$query1 = "SELECT * FROM forum_read WHERE id_post = '$id_post' AND id_utente='$id_utente' LIMIT 1";
	$result1=$mysqli->query($query1);
	$letto = $result1->num_rows;
	};
	
	if ($letto) {
		$flag = "";
	} else {
		$flag = " <i><b>$stringa[nuovo]</b></i>";
	};
	
	$id_autore=$intervento["id_autore"];
	$icona_post = $intervento["icona_post"];

	if (!$icona_post) {
		$icona_post = "messaggio";
	};	
	
	if ($intervento[id_post]==$id_post_view) {
		$bgcolor=$colore_sfondo;
	} else {
		$bgcolor=$colore_sfondo_neutro;
	};		
	echo "<li>\n";

	
	if ($nrep) {
		echo "
	<p style=\"background-color:$bgcolor;margin-bottom=5pt;margin-top=5pt\">\n";
	} else {
		echo "
		<p style=\"background-color:$bgcolor;margin-bottom=5pt;margin-top=5pt\">
		";
	};
	
	$query_mark = "SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post' LIMIT 1";
	$result_mark=$mysqli->query($query_mark);
	$riga_mark = $result_mark->fetch_array();	
	if ($riga_mark) {
		echo "<img src=\"img/forum/spunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	} else {
		echo "<img src=\"img/forum/nospunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	}
		
	if ($intervento["nome_file"]) {
		echo "<img src=img/forum/allegato.gif width=16 height=16 border=0>";
	};
	

	$ruolo_str="";
	if ($tipo_forum=='1' or $tipo_forum=='2' or $tipo_forum=='3') {
		$query_s="SELECT ruolo FROM ruolo_utenti WHERE id_utente='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'  LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_".$riga_s["ruolo"];
		if ($riga_s["ruolo"]) $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
		
		$query_s="SELECT id_tutor FROM gruppo_utenti WHERE id_tutor='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'  LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_tutor";
		if (!$ruolo_str and $riga_s["id_tutor"]) $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
	};
	
	if ($ruolo=="staff" or $ruolo=="admin" or 1) 
	echo "<a href=\"javascript:;\" onclick=\"showPost('".$id_forum."','".$intervento[id_post]."','".$vista."','".$pagina."')\"><img src=\"img/ico_forum_daleggere.gif\" id=\"preview".$intervento[id_post]."\" width=\"20\" height=\"20\" border=\"0\" alt=\"clicca per vedere in anteprima l'intervento\"></a> ";
	
	echo "<img src=img/forum/$icona_post".".gif alt=$icona_post> <span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$intervento[id_post]&vista=$vista&modo=$modo&pagina=$pagina  title=\"$intervento[data_p]\">$intervento[oggetto]</a></span>";
	
	
	
	echo "<span class=testopiccolo> (<i><a href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');$cancelBubble_stm\">$id_autore</a></i>&nbsp;$ruolo_str)</span>";
		
	echo "<span class=\"testopiccolo\" id=\"post_".$intervento["id_post"]."\">$flag</span></p>";
	
	if ($nrep) {
	 	thread_sintetico($intervento["id_post"]); 
	} 
	
	echo "</li>";
	
	$righe++;
	$intervento = $result->fetch_array();
	if ($id_padre == 0) {
		if ($righe > $pag_size) {
			$continua = false;
		};
	};
		
	
};
	
echo "</ul>";

};


function byfocus() {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT,$stringa,
			$id_forum,$id_utente,$tipo_forum,$id_corso_s,$id_edizione_s,$ruolo,
			$pagina,$pag_size,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	
// seleziono gli interventi del forum e li visualizzo
$query = "SELECT id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post,attinenza,n_attinenze FROM forum_posts WHERE id_forum='$id_forum' AND (attinenza>2 and n_attinenze>2) ORDER BY id_post DESC ";
//$result=$mysqli->query($query);

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;


$righe=1;
while ($intervento=$result->fetch_array()) {
	//vedo se l'utente ha letto l'intervento in questione
	$id_post = $intervento["id_post"];
	
	$letto=true;
	
	if ($DBASE<>"kairos_masterunitus" or 1) {
	$query1 = "SELECT * FROM forum_read WHERE id_post = '$id_post' AND id_utente='$id_utente' LIMIT 1";
	$result1=$mysqli->query($query1);
	$letto = $result1->num_rows;
	};
	
	if ($letto) {
		$flag = "";
	} else {
		$flag = " <i><b>$stringa[nuovo]</b></i>";
	};
	
	$id_autore=$intervento["id_autore"];
	$icona_post = $intervento["icona_post"];

	if (!$icona_post) {
		$icona_post = "messaggio";
	};

	
	$query_mark = "SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post' LIMIT 1";
	$result_mark=$mysqli->query($query_mark);
	$riga_mark = $result_mark->fetch_array();	
	if ($riga_mark) {
		echo "<img src=\"img/forum/spunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	} else {
		echo "<img src=\"img/forum/nospunta.gif\" id=\"rigamark_$id_post\"  border=\"0\">";
	}	
	
	
	
	echo "<a href=\"javascript:;\" onclick=\"showPost('".$id_forum."','".$intervento[id_post]."','focus','".$pagina."')\"><img src=\"img/ico_forum_daleggere.gif\" id=\"preview".$intervento[id_post]."\" width=\"20\" height=\"20\" border=\"0\" alt=\"clicca per vedere in anteprima l'intervento\"></a> ";
	
	if ($intervento[n_attinenze]>2) {
		$n_attinenze=$intervento[n_attinenze];
		$attinenza=$intervento[attinenza];
		echo "<span class=testopiccolo>"; for ($at=0;$at<$attinenza;$at++) { echo "<img src=\"img/piuma.gif\" width=\"15\" height=\"15\" border=\"0\" alt=\"\" >"; }; echo "<sup>$n_attinenze</sup></span>&nbsp;";
	};
	
	if ($intervento["nome_file"]) {
		echo "<img src=img/forum/allegato.gif width=16 height=16 border=0>";
	};
	
	printf("<img src=img/forum/%s.gif alt=%s> <span class=testopiccolo><a href=index.php?risorsa=forum_mostra_post&id_forum=%s&id_post=%s&vista=mark&modo=esteso&pagina=%s>%s</a></span>",$icona_post,$icona_post,$id_forum,$intervento["id_post"],$pagina,$intervento["oggetto"]);
	
	$ruolo_str="";
	if ($tipo_forum=='1' or $tipo_forum=='2' or $tipo_forum=='3') {
		$query_s="SELECT ruolo FROM ruolo_utenti WHERE id_utente='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_".$riga_s["ruolo"];
		if ($riga_s["ruolo"])  $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
		
		$query_s="SELECT id_tutor FROM gruppo_utenti WHERE id_tutor='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_tutor";
		if (!$ruolo_str and $riga_s["id_tutor"])  $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
	};
	
	echo "<span class=testopiccolo> <i><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_autore</a></i>$ruolo_str
</span>";

		
	printf("<span class=testopiccolo><i> - %s)</i></span>\n",$intervento["data_p"]);
	
	
	echo "<span class=\"testopiccolo\" id=\"post_".$intervento["id_post"]."\">$flag</span><br>";
	
	
	$righe++;

};


};

function dummyErrorHandler ($errno, $errstr, $errfile, $errline) { 
}; 

function forceFlush() {   
   session_write_close(); 
   ob_start(); 
   ob_end_clean(); 
   flush(); 
   set_error_handler("dummyErrorHandler"); 
   ob_end_flush(); 
   restore_error_handler(); 
}; 

function parse_quote($contenuto) {
	$contenuto_originale=$contenuto;
	
	$pattern="\[citazione";
	$position0 = multi_strpos($pattern, $contenuto_originale);
	
	if ($position0) {
		while (list($index, $pos0) = each($position0)) {
			$comando="[citazione";
			$autore="";
			$i=0;
			$char=substr($contenuto_originale,$pos0+10+$i,1);
			while ($char<>"]" and $i<(strlen($contenuto_originale)-10)) {
				$autore.=$char;
				$comando.=$char;
				$i++;
				$char=substr($contenuto_originale,$pos0+10+$i,1);
			}
			$comando.=$char;
						
			$autore=trim($autore);
			
			$autoredice="";
			if ($autore) $autoredice="<strong>$autore dice:</strong><br><br>";
			
			$contenuto=str_replace($comando,"<div class=\"citazione\">$autoredice",$contenuto);
		
		}
		
		$contenuto=str_replace("[/citazione]","</div>",$contenuto);
	}
	
	
	return $contenuto;
};

function getThread($id_padre) {
	global 	$DBASE,$DBUSER,$DBPWD,$PATH_ROOT,$HTTP_COOKIE_VARS,$stringa,
			$id_forum,$id_utente,$win_ie,$tipo_forum,$id_corso_s,$id_edizione_s,$ruolo,
			$pagina,$pag_size, $DBHOST;
	global $opera;
	global $thread_html;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);



	$query = "SELECT id_post,oggetto,testo,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post,attinenza,n_attinenze FROM forum_posts WHERE id_post_padre='$id_padre' ORDER BY data_post";
	
	$result=$mysqli->query($query);

	
	while ($intervento = $result->fetch_array()) {
	

		$id_post = $intervento["id_post"];
		$query0 = "SELECT id_post FROM forum_posts WHERE id_post_padre='$id_post'";
		$result0=$mysqli->query($query0);
		$nrep = $result0->num_rows;
	

		$id_autore=$intervento["id_autore"];
		$icona_post = $intervento["icona_post"];

		if (!$icona_post) {
			$icona_post = "messaggio";
		};	
			
		$thread_html.="<hr size=1>\n";

		$thread_html.="<img src=img/forum/$icona_post.gif> <span class=testopiccolo>".$intervento["oggetto"]."</span>";
		
		$thread_html.= "<span class=testopiccolo> (<i>$id_autore</i></span>";
		
		$thread_html.="<span class=testopiccolo><i> - ".$intervento["data_p"].")</i></span>";
		$testo = $intervento["testo"];
		$testo = parse_href($testo);
		$testo = parse_quote($testo);

		$thread_html.= "
<table border=0 width=90% cellspacing=10 cellpadding=2>
<tr>
<td><span class=testo>$testo</span></td>
</tr></table>";
		
	
		if ($nrep) {
	 		getThread($id_post); 
		} 
	
	
	};
	
	
};
	
?>

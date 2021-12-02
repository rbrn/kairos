<?php
include_once 'common_functions.php'; 
echo "
<table border=0 cellspacing=0 cellpadding=0 width=100% height=20>
<tr><td valign=middle align=left>

<span class=titololink>";

echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";

if ($risorsa<>'index') {
	echo "<span class=menu><a href=\"index.php?risorsa=index\" $target>$stringa[home]</a></span>";
} else {
	echo "<span class=menu_on>$stringa[home]</span>";
};		  

echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";


echo "<span class=menu><a href=javascript:whosonline()>$stringa[chi_e_in_linea]</a></span>";

echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";

if ($risorsa<>'forum_elenco') {
	echo "<span class=menu><a href=\"index.php?risorsa=forum_elenco\" $target>$stringa[forum]</a></span>";
} else {
	echo "<span class=menu_on>$stringa[forum]</span>";
};

echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";

if ($risorsa<>'chat') {
	echo "<span class=menu><a href=\"index.php?risorsa=chat\" $target>$stringa[chat]</a></span>";
} else {
	echo "<span class=menu_on>$stringa[chat]</span>";
};

echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";

if ($win_ie and 0) {
	if ($risorsa<>'bacheca' and $id_corso_s) {
		echo "<span class=menu><a href=\"index.php?risorsa=bacheca\">$stringa[bacheca]</a></span>";
	} else {
		echo "<span class=menu_on>$stringa[bacheca]</span>";
	};
	echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";
};


if (($wimba_lc and $kairos_cookie[0] and $id_corso_s) or ($cod_area=="kairos_area_corsi" and $id_corso_s=="corso_inglese")) {
	require_once("./wimba/wimba_lc_api.php");
	echo "<span class=menu>$liveclassroom</span>";
	echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";	
};

$teleskill=0;



$teleskill = get_teleskill_enabled($cod_area);

if ($cod_area=="kairos_ebookditesto") $teleskill=1;
if ($cod_area=="itc_scuola") $teleskill=1;
if ($cod_area=="kairos_curriculumdigitale") $teleskill=1;
if ($cod_area=="kairos_ripetizionionline") $teleskill=1;
if ($cod_area=="kairos_insegnanti") $teleskill=1;
if ($cod_area=="kairos_masterunitus") $teleskill=1;
if ($cod_area=="kairos_stage2007") $teleskill=1;
if ($cod_area=="kairos_comitato") $teleskill=1;
if ($cod_area=="kairos_recuperonline") $teleskill=1;
if ($cod_area=="kairos_edmont") $teleskill=1;
if ($cod_area=="kairos_itc_scuola") $teleskill=1;
if ($cod_area=="kairos_lascuolafuori") $teleskill=1;
if ($cod_area=="kairos_innovazioneascuola")  $teleskill=1;
if ($cod_area=="kairos_learningobject" and ($ruolo=="staff" or $ruolo=="admin")) $teleskill=1;
if ($cod_area=="kairos_innovazioneascuola") $teleskill=1;
if ($cod_area=="kairos_innovascuola") $teleskill=1;
if ($cod_area=="kairos_classi2") $teleskill=1;
if ($cod_area=="kairos_winscuola") $teleskill=1;



if (($id_corso_s and $teleskill==1) || $enable) {
	echo "<span class=menu><a href=\"index.php?risorsa=teleskill\">Aula Virtuale</a></span>";
	echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";	
}

/*
echo "<span class=menu><a href=javascript:whosonline()>$stringa[chi_e_in_linea]</a></span>";


echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";		 
		 
if ($risorsa<>'messaggi') {
	echo "<span class=menu><a href=\"index.php?risorsa=messaggi\" $target>$stringa[posta_interna]</a></span>";
} else {
	echo "<span class=menu_on>$stringa[posta_interna]</span>";
};

	
echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";
*/
		
if ($risorsa<>'calendario') {
	if (!$id_corso_s) {
		echo "<span class=menu_on>$stringa[eventi]</span>";
	} else {
		echo "<span class=menu><a href=\"index.php?risorsa=calendario\" $target>$stringa[eventi]</a></span>";
	};
} else {
	echo "<span class=menu_on>$stringa[eventi]</span>";
};

echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";

if ($cod_area<>'kairos_larimart') {
	$stringa_mat=$stringa[materiali];
} else {
	$stringa_mat=$stringa[materiali];
};

if ($risorsa<>'materiali') {
	echo "<span class=menu><a href=\"index.php?risorsa=materiali\" $target>$stringa_mat</a></span>";
} else {
	echo "<span class=menu_on>$stringa_mat</span>";
};

echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";

if ($cod_area=="kairos_curriculumdigitale") {
	echo "<span class=menu><a href=\"index.php?risorsa=lo_repository\" $target>Repository</a></span>";
	echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";
};

if ($risorsa<>'cerca') {
	echo "<span class=menu><a href=\"index.php?risorsa=cerca\" $target>$stringa[cerca]</a></span>";
} else {
	echo "<span class=menu_on>$stringa[cerca]</span>";
};

echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";


if ($cod_area<>"kairos_librinrete" and $cod_area<>"kairos_area_corsi" and $cod_area<>"kairos_master" and $cod_area<>"kairos_masterunitus" and $cod_area<>"kairos_eprof") {
if ($risorsa<>'catalogo') {
	echo "<span class=menu><a href=\"index.php?risorsa=catalogo\" $target>$stringa[catalogo_corsi]</a></span>";
} else {
	echo "<span class=menu_on>$stringa[catalogo_corsi]</span>";
};
echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";
};

if ($risorsa<>'info') {
	echo "<span class=menu><a href=\"index.php?risorsa=info\" $target>$stringa[info]</a></span>";
} else {
	echo "<span class=menu_on>$stringa[info]</span>";
};

echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";

if ($id_utente) {
	if ($ruolo=='staff' or $ruolo=='admin')  {
		if ($risorsa<>'admin_index') {
			echo "<span class=menu><a href=\"index.php?risorsa=admin_index\" $target>$stringa[admin]</a></span>";
		} else {
		 	echo "<span class=menu_on>$stringa[admin]</span>";
		};
		echo "<img src=\"img/separatore.gif\" width=\"16\" height=\"16\" align=\"absmiddle\" hspace=\"1\">";
	};
};


echo "</span></td></tr></table>";

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="shortcut icon" href="../../assets/ico/favicon.png">

    <title>Sticky Footer Navbar Template for Bootstrap</title>

    <!-- Bootstrap core CSS -->
    <link href="../../dist/css/bootstrap.css" rel="stylesheet">

    <!-- Custom styles for this template -->
    <link href="sticky-footer-navbar.css" rel="stylesheet">

    <!-- HTML5 shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
    <script src="../../assets/js/html5shiv.js"></script>
    <script src="../../assets/js/respond.min.js"></script>
    <![endif]-->


<body>


<?php
/*echo "
<html>
<head>
<title>Atlante Area Corsi: $titolo</title>
<meta name=\"keywords\" content=\"$parole_chiave\">
<meta name=\"description\" content=\"$descrizione\">
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>";*/

if ($risorsa_padre=='cartella_materiali') {
	echo "
	<script language=\"JavaScript\" src=\"script/script_materiali.js\"></script>";
};

echo "
<link rel=\"stylesheet\" href=\"./config/kairos_stile_css.php\">
</head>
";
?>
</head>

<?php

if ($risorsa_padre=='cartella_materiali') {
	echo "
<body topmargin=\"0\" leftmargin=\"15\" class=\"pagina\" onLoad=\"if (document.all) beforeLoad()\">";
} else {
	echo "
<body topmargin=\"0\" leftmargin=\"15\" class=\"pagina\">";
};	

echo "
<table width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=\"center\">
<tr><td>
<!-- TESTATA -->
<table border=0 cellpadding=\"0\" cellspacing=\"0\" width=100% background=\"img/up-bg.gif\">
<tr>
<td >
<div align=\"left\"><img src=\"img/testatina.gif\" width=\"428\" height=\"78\" border=0 alt=\"Corso On Line\"></div>
</td>
<td  > 
<div align=\"right\"><a href=http://www.garamond.it><img src=\"img/atlante2.gif\" width=\"131\" height=\"78\" border=0 alt=\"Home Page Atlante Garamond\"></a></div>
</td>
</tr>
</table>
<!-- FINE TESTATA -->";

echo "
<table class=\"menu\" width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" height=\"20\">
<tr> 
<td align=center> 
		  |&nbsp;";

if ($risorsa<>'index') {
	echo "<a href=\"index.php?risorsa=index\">Home</a>&nbsp;|&nbsp;";
} else {
	echo "<span class=menu_on>Home</span>&nbsp;|&nbsp;";
};		  

if ($risorsa<>'corsi_info') {
	echo "<a href=\"index.php?risorsa=segreteria\">Segreteria</a>&nbsp;|&nbsp;";
} else {
	echo "<span class=menu_on>Segreteria</span>&nbsp;|&nbsp;";
};

if ($risorsa<>'staff') {
	echo "<a href=\"index.php?risorsa=staff\">Staff</a>&nbsp;|&nbsp;";
} else {
	echo "<span class=menu_on>Staff</span>&nbsp;|&nbsp;";
};


echo "<a href=javascript:whosonline()>Chi ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ in linea</a>&nbsp;|&nbsp;";


if ($risorsa<>'forum_elenco') {
	echo "<a href=\"index.php?risorsa=forum_elenco\">Forum</a>&nbsp;|&nbsp;";
} else {
	echo "<span class=menu_on>Forum</span>&nbsp;|&nbsp;";
};

echo "<a href=\"chat/\">Chat</a>&nbsp;|&nbsp;";
		 
if ($risorsa<>'messaggi') {
	echo "<a href=\"index.php?risorsa=messaggi\">Posta interna</a>&nbsp;|&nbsp;";
} else {
	echo "<span class=menu_on>Posta interna</span>&nbsp;|&nbsp;";
};
		  
if ($risorsa<>'materiali') {
	echo "<a href=\"index.php?risorsa=materiali\">Materiali</a>&nbsp;|&nbsp;";
} else {
	echo "<span class=menu_on>Materiali</span>&nbsp;|&nbsp;";
};

if ($risorsa<>'laboratori') {
	echo "<a href=\"index.php?risorsa=laboratori\">Laboratori</a>&nbsp;|&nbsp;";
} else {
	echo "<span class=menu_on>Laboratori</span>&nbsp;|&nbsp;";
};


if ($risorsa<>'mediateca') {
	echo "<a href=\"index.php?risorsa=mediateca\">Mediateca</a>&nbsp;";
} else {
	echo "<span class=menu_on>Mediateca</span>&nbsp;";
};


if ($id_utente) {
	echo "|&nbsp;<a href=\"logout.php\" title=\"Logout\">[X]</a> $id_utente &nbsp;";
};

echo "|";
echo "
</td>

</tr>
";
echo "
</table>";
?>

<?php
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");
require "./include/init_sito.inc";
echo "
<html>
<head>
	<title>$stringa[anteprima_chat_collab]</title>
<?php

<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>
<script language="JavaScript">
window.setTimeout("ricarica()", 10000);

function ricarica() {
	var valore_scroll=document.body.scrollTop;
	setCookie("CookieScroll",valore_scroll);
	window.location='anteprima.php';
}

function getCookie(nome_cookie) {
	var nome_cookie = nome_cookie + "="
	if (document.cookie.length > 0) { 
		inizio = document.cookie.indexOf(nome_cookie) 
		if (inizio != -1) { 
			inizio += nome_cookie.length 
			fine = document.cookie.indexOf(";", inizio) 
			if (fine == -1) {
				fine = document.cookie.length
			}
			return unescape(document.cookie.substring(inizio, fine))
		} else {
			return null;
		}
	} else {
		return null;
	};	
}

function setCookie(nome_cookie,valore_cookie) {
	document.cookie=nome_cookie + '=' + valore_cookie;
}

function imposta_scroll() {
	var valore_scroll = getCookie("CookieScroll");
	document.body.scrollTop=valore_scroll;
}
</script>
</head>

<body bgcolor=white onload=imposta_scroll()>

<?php
$contenuto=$PATH_ROOT_FILE.$cod_area."_".$id_corso_s."_laboratorio.txt";

if (file_exists($contenuto)) {
	include "./".$cod_area."_".$id_corso_s."_laboratorio.txt";
};
?>
<hr size=1>
</body>
</html>

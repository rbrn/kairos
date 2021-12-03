<?php
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");
require "./include/init_sito.inc";
?>
<html>
<head>
	<title><?php echo($stringa[editor]);?></title>
	
	<?php
	if ($usanuovoeditor) {
		echo "
	<script type=\"text/javascript\" src=\"script/html_editor_conf.js.php\"></script>
	<script type=\"text/javascript\" src=\"html_editor/htmlarea.js.php\"></script>
	<script language=\"JavaScript\" src=\"script/html_editor.js.php?contesto=chat\"></script>
	<link rel=\"stylesheet\" href=\"stili/stile_html_editor.css\">
	";
	
	} else {
		echo "
	<script language=\"JavaScript\" src=\"script/script_editor.js\"></script>
	<link rel=\"stylesheet\" href=\"stili/stile_editor.css\">
	";
	}
	
	?>
	<?php
	echo "
	<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
	";
	?>
<script language="JavaScript">
function popup(url,x,y) {
 dimensione="toolbar=no,menubar=no,directories=no,status=no,resizable=no,scrollbars=yes,width="+x+",height="+y
 window.open(url,"f",dimensione);
}
</script>
</head>
<?php 
if (!$usanuovoeditor) {
	echo "<body onload=\"assegna_testo();\">";
} else {
	echo "<body onload=\"initEditor();\">";
};
?>

<table border=0 width=500>
<tr><td valign=top>

<form action=aggiorna_contenuto_chat.php method=post name=modulo id=modulo>


<?php
$kairos_cookie=$_REQUEST["kairos_cookie"];
$cod_area=$kairos_cookie[4];
$cartella=$kairos_cookie[5];
$semaforo=$PATH_ROOT_FILE.$cod_area."_".$id_corso_s."_semaforo.txt";
$id_utente=$kairos_cookie[0];
$fd=fopen($semaforo,"w");
fwrite($fd,$id_utente);
fclose($fd);

$contenuto=$PATH_ROOT_FILE.$cod_area."_".$id_corso_s."_laboratorio.txt";
if (file_exists($contenuto)) {
	$testo_array=file($contenuto);
	$testo=join('',$testo_array);
	$testo=htmlentities($testo);
	/*
	$testo=addslashes($testo);
	$testo = nl2br($testo);
	$testo = str_replace(chr(10)," ",$testo);
	$testo = str_replace(chr(13)," ",$testo);
	*/
} else {
	$testo="";
};


if ($usanuovoeditor) {
	echo "
	<p>
	<b>Editing contenuto</b><br>
	<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<TEXTAREA id=\"testo\" cols=80 name=\"testo\" rows=30>".$testo."</TEXTAREA>
</td></tr>
</table>
	</p>
	";
} else {
if (!$win_ie) {
echo"
	<p>
	<b>Editing contenuto</b><br>
<TEXTAREA cols=70 name=testo rows=30 wrap=virtual>".$testo."</TEXTAREA>
</p>";
} else {
	echo "<input type=\"hidden\" name=\"testo\" id=\"testo\">\n
	<p>
	<b>Editing contenuto</b><br>
	";
	require "./include/editor.inc";
};
}

?>
<?php
echo "<input type=\"submit\" name=\"ok\" value=\"$stringa[invia]\" />";
?>

</form>
<span class=testo>[<a href="lascia_editor.php"><?php echo($stringa[lascia]);?></a>]</span>
<span class=testo>[<a href="atlante_editor.php"><?php echo($stringa[riprendi]);?></a>]</span>
<span class=testo>[<a href="nuovo_editor.php"><?php echo($stringa[nuovo_e]);?></a>]</span>
<span class=testo>[<a href="ftp_comune/salva.php?cartella=<?php echo($cartella);?>"><?php echo($stringa[salva]);?></a>]</span>
<span class=testo>[<a href="ftp_comune/apri.php?cartella=<?php echo($cartella);?>"><?php echo($stringa[apri]);?></a>]</span>

</td></tr>
</table>

</body>
</html>


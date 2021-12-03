<?php
require "./init_sito.inc";
require "./function_admin.inc";
$cartella=$_REQUEST["cartella"];
$ruolo=ruolo_utente($kairos_cookie[0]);

if ($ruolo<>'admin' and $ruolo<>'staff' and $cod_area=='kairos_eprof' and $eprof<>"valido") {
	$msg="Il tuo abbonamento ad E-Prof scaduto e non puoi piu accedere a questa funzione o area.";
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:../index.php?risorsa=msg&msg=$msg");
	exit();
};

?>
<HTML>
<HEAD><TITLE><?php echo($stringa[cartelle_condivise]);?></TITLE>
<script language="JavaScript">

function nota(url,x,y) {
  dimensione="toolbar=no,menubar=no,directories=no,status=no,resizable=no,scrollbars=yes,width="+x+",height="+y
 window.open(url,"f",dimensione);

}
</script>

</HEAD>
<BODY bgColor=white>

  <P><FONT face=verdana><B><br>
    <?php echo($stringa[cartelle_condivise]);?>: <?php echo($id_utente);?></B></FONT> </P>

<?php
echo "
<form action=cancella_file.php method=post>
<input type=hidden name=cartella value=\"$cartella\">
<a href=nuova_cartella.php?cartella=$cartella><img src=img/new_folder.gif width=25 height=24 alt=\"$stringa[nuova_cartella]\" border=0></a><a href=nuovo_file.php?cartella=$cartella><img src=img/new_file.gif width=25 height=24 alt=\"$stringa[nuovo_file]\" border=0></a><a href=zip_form.php?cartella=$cartella><img src=img/new_file_zip.gif width=25 height=24 alt=\"$stringa[archivio_zip]\" border=0></a>&nbsp;&nbsp;&nbsp;";

if ($ruolo=='staff' or $ruolo=='admin') {
	echo "<input type=submit value=\"$stringa[cancella_elementi]\">";
};

?>  
<TABLE border=0 width=461>
<tr></td>
<?php
$indice="index";
$dir_path=$PATH_ROOT_FILE.$cartella;
if (is_dir($dir_path)) {
	browse_folder($cartella);
} else {
	echo "<br><span class=testo>La cartella non e' raggiungibile forse a causa di uno spazio nel suo nome. <br>I nomi di file e cartelle <b>non devono contenere spazi</b>.</span>";
};
?>
</td></tr>
	  	  
</TABLE>
</form>
    <BR>
  <HR>
</BODY>
</HTML>

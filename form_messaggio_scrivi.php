<?php

require "./include/init_sito.inc";

require "./include/funzioni_sito.inc";

/*

echo "<a href=\"javascript:;\" onclick=\"opener.location='form_messaggio_scrivi.php?id_utente=$id_utente'\" title=\"manda un messaggio in posta interna!\"><img src=img/envelope.gif width=14 height=10 border=0></a>";

*/



$id_utente1=$kairos_cookie[0];

$id_messaggio=$_REQUEST["id_messaggio"];

$id_utente=$_REQUEST["id_utente"];

if (!$id_utente1) {

	echo "

	<html>

	<head><title>$stringa[errore]</title>

	<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">

	<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>

	</HEAD>

	<BODY bgcolor=$colore_sfondo>

	<span class=testo>$stringa[errore_no_login]</span>

	</body>

	</html>";

	exit();

};

?>



<?php

if ($id_messaggio) {
	$query = "SELECT * FROM messaggi WHERE id_messaggio=$id_messaggio";

    $result = $mysqli->query($query);
    $messaggio = $result->fetch_array();

	$data_invio=$messaggio["data_invio"];

	ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data_invio,$arg);

	$data_invio=$arg[3]."/".$arg[2]."/".$arg[1]." ".$arg[4].":".$arg[5].":".$arg[6];

	

	$oggetto=htmlentities("Re:".$messaggio["oggetto"]);

	$data_lettura==$messaggio["data_lettura"];

	$id_utente=$messaggio["id_mittente"];

	$testo=htmlentities("$id_utente $stringa[ha_scritto] $data_invio:\n-------------\n".$messaggio["testo"]."\n-------------\n");

};

?>



<html>

<head>

<title><?php echo($stringa[nuovo_messaggio]);?></title>

<?php
echo "
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
";
?>

</head>

<BODY bgcolor=<?php echo($colore_sfondo_neutro);?> topmargin="0" leftmargin="0">
<table border=0 width=100% cellpadding=5 bgcolor=<?php echo($colore_scuro_neutro);?>>
<tr><td>
<span class=testo><b><?php echo($stringa[nuovo_messaggio]);?></b></span></td>
</tr>
</table>

<form action="messaggio_scrivi.php" method="post" name="modulo" id="modulo">



<table border="0">

<tr>

<td align="right" valign=top>

<p><span class=testo><?php echo($stringa[id_utente]);?>:</span></p>

</td>

<td valign=top>

<input type="text" size="20" maxlength=100 name=id_utente value="<?php echo($id_utente);?>">
<?php 
			echo "
<span class=\"testopiccolo\">
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup.php?ruolo=tutti&campo=id_utente','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]
</span>";
?>
</td>

</tr>



<tr>

<td align="right" valign=top>

<p><span class=testo><?php echo($stringa[oggetto]);?>:</span></p>

</td>

<td valign=top>

<input type="text" size="40" maxlength=100 name=oggetto value="<?php echo($oggetto);?>">

</td>

</tr>



 <tr>

 <td align="right" valign=top>

 <p><span class=testo><?php echo($stringa[messaggio]);?>:</span></p>

 </td>

<?php

echo " 

  <td valign=top>

<textarea name=testo rows=15 cols=40>$testo</textarea>

 </td>";

 ?>

 </tr>

 

<tr><td colspan=2></td></tr>



<tr><td colspan=2>

<p align="right">

<input type="submit" value="<?php echo($stringa[invia]);?>">

</p>

</td>

</tr>



</table>

</form>





<!-- FINE CONTENUTO DELLA PAGINA -->

</body>

</html>

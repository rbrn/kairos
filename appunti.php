<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente1=$kairos_cookie[0];

if (!$id_utente1) {
	echo "
	<html>
	<head><title>Errore</title>
	<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
	<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
	</HEAD>
	<BODY bgcolor=$colore_sfondo>
	<span class=testo>$stringa[errore_no_login]</span>
	</body>
	</html>";
	exit();
};

$query = "SELECT * FROM appunti WHERE id_utente='$id_utente1'";
$result = $mysqli->query($query);
$riga=$result->fetch_array();
$testo=htmlentities($riga["testo"]);
?>


<?php
echo "
<html>
<head>
<title>$stringa[appunti]</title>
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>
<script language="JavaScript" src="script/funzioni.js"></script>
</head>
<BODY bgcolor=<?php echo($colore_sfondo_neutro);?> topmargin="0" leftmargin="0">
<table border=0 width=100% cellpadding=5 bgcolor=<?php echo($colore_scuro_neutro);?>>
<tr><td>
<span class=testo><b><?php echo($stringa[appunti]);?></b></span></td>
</tr>
</table>

<form action="appunti_op.php" method="post">
<table border="0" cellpadding=10>


<?php
echo " 
<tr><td valign=top>
<textarea name=testo rows=15 cols=40>$testo</textarea>
</td></tr>";
?>

<tr><td align=center><input type=submit value="<?php echo($stringa[salva]);?>">
<span class=testo>[<a href="javascript:self.close()"><?php echo($stringa[chiudi]);?></a>]</span>
</td></tr>
</table>
</form>
<!-- FINE CONTENUTO DELLA PAGINA -->
</body>
</html>

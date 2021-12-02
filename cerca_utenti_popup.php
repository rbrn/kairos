<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente1=$kairos_cookie[0];

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

$ruolo=$_REQUEST["ruolo"];
$campo=$_REQUEST["campo"];

?>


<html>
<head>
<title><?php echo($stringa[cerca]);?></title>
<?php 
echo "
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">";
?>
</head>
<BODY bgcolor=<?php echo($colore_sfondo_neutro);?> topmargin="0" leftmargin="0">
<table border=0 width=100% cellpadding=5 bgcolor=<?php echo($colore_scuro_neutro);?>>
<tr><td>
<span class=testo><b><?php echo($stringa[cerca]);?></b></span></td>
</tr>
</table>

<form action="cerca_utenti_popup_op.php" method="get">
<input type="hidden" name="ruolo" value="<?php echo($ruolo);?>">
<input type="hidden" name="campo" value="<?php echo($campo);?>">
<input type="hidden" name="pagina" value="1">
<input type="hidden" name="pag_size" value="20">
<table border="0">

<?php

		echo "
		<tr>
		<td align=\"right\" valign=top>
		<span class=testo>$stringa[identificativo]</span>
		</td>
		<td valign=top>
		<input type=\"text\" size=\"10\" name=\"id_utente_cerca\">
		</td>
		</tr>

		 <tr>
 		<td align=\"right\" valign=top>
		<span class=testo>$stringa[nome]</span>
 		</td>
  		<td valign=top>	
		 <input type=\"text\" size=\"35\"  name=\"nome\">
		 </td>
 		</tr>
 
 		<tr>
 		<td align=\"right\" valign=top><span class=testo>$stringa[cognome]</span></td>
 		<td valign=top><input type=\"text\" size=\"35\"  name=\"cognome\">
 		</td>
 		</tr>";
 
?> 
 
<tr><td colspan=2></td></tr>

<tr><td colspan=2>
<p align="center">
<input type="submit"  value="<?php echo($stringa[cerca]);?>">
</p>
	
</td>
</tr>

</table>
</form>

</body>
</html>

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

$campo=$_REQUEST["campo"];
$dir=$_REQUEST[dir];

?>


<html>
<head>
<title><?php echo($stringa[cerca_materiali]);?></title>
<?php 
echo "
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">";
?>
</head>
<BODY bgcolor=<?php echo($colore_sfondo);?>>
<!-- CONTENUTO DELLA PAGINA -->
<p>
<span class=titolopagina><?php echo($stringa[cerca_materiali]);?></span>
</p>
<hr size=1>
<form action="cerca_pagina_popup_op.php" method="get">
<input type="hidden" name="campo" value="<?php echo($campo);?>">
<input type="hidden" name="dir" value="<?php echo($dir);?>">
<input type="hidden" name="pagina" value="1">
<input type="hidden" name="pag_size" value="20">
<table border="0">

<?php
		if (!$dir) {
		echo "
		<tr>
		<td align=\"right\" valign=top>
		<span class=testo>$stringa[identificativo]</span>
		</td>
		<td valign=top>
		<input type=\"text\" size=\"10\" name=\"id_risorsa_cerca\">
		</td>
		</tr>";
		};
		
		echo "
		 <tr>
 		<td align=\"right\" valign=top>
		<span class=testo>$stringa[titolo]</span>
 		</td>
  		<td valign=top>	
		 <input type=\"text\" size=\"35\"  name=\"titolo\">
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

<?php
$id_pagina=1000+$id_item;

$query="SELECT * FROM lo_pagina_asset WHERE id_pagina='$id_pagina'";
$result=$mysqli->query($query);

$riga=$result->fetch_array();
$id_pagina_asset=0;
$file_flash="";
if ($riga) {
	$id_pagina_asset=$riga["id_pagina_asset"];
	$file_flash=$riga["file_asset"];
	$f_w=$riga[width];
	$f_h=$riga[height];
	$alt_text=htmlentities($riga["alt_text"]);
	$alt_img=$riga["alt_img"];
	$soluzione=htmlentities($riga["soluzione"]);
};

$tipo_media="flash";
$nome_campo="file_flash";
$valore=$file_flash;
$label=$stringa[elenco_flash];
echo "<form action=lo_test_asset_op.php method=post name=\"modulo\" id=\"modulo\">
<input type=\"hidden\" name=\"id_pagina\" value=\"$id_pagina\">
<input type=\"hidden\" name=\"id_item\" value=\"$id_item\">
<input type=\"hidden\" name=\"risorsa_padre\" value=\"$risorsa_padre\">
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >";

echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>$stringa[$tipo_media]".":</b></span></td>
<td><input type=\"text\" name=\"$nome_campo\" id=\"$nome_campo\" readonly value=\"$valore\" size=\"60\"><br>
<a href=\"javascript:;\" onclick=\"return lo_seleziona_media('gruppo','$tipo_media','$nome_campo');\"><span class=testopiccolo>$label</span></a></td>
</tr>";		

echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>$stringa[alt_img]:</b></span></td>
<td><input type=\"text\" name=\"alt_img\" id=\"alt_img\" readonly value=\"$alt_img\" size=\"60\"><br>
<a href=\"javascript:;\" onclick=\"return lo_seleziona_media('gruppo','img','alt_img');\"><span class=testopiccolo>$stringa[elenco_img]</span></a></td>
</tr>";

echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>$stringa[alt_text]:</b></span></td>
<td><textarea name=\"alt_text\" id=\"$alt_text\"  rows=\"05\" cols=\"60\">$alt_text</textarea></td>
</tr>";

echo "<tr bgcolor=\"$colore_sfondo\">
<td align=right valign=top><span class=testo><b>Soluzione:</b></span></td>
<td><textarea name=\"soluzione\" id=\"$soluzione\"  rows=\"05\" cols=\"60\">$soluzione</textarea></td>
</tr>";

echo "</table>\n";
echo "		
</td></tr>
</table>";

if ($ruolo=='admin' or $id_utente==$id_editor) {	
echo "
<input type=\"submit\" value=\"$stringa[ok]\">";
};

echo "</form>";

?>

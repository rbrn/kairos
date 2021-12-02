<?php
$file_testata = "img/$cod_area/testata.gif";
if (!file_exists($file_testata)) $file_testata = "img/$cod_area/testata.jpg";

if (!file_exists($file_testata)) $file_testata = "";

$file_testatabg = "img/$cod_area/up-bg.gif";
if (!file_exists($file_testatabg)) $file_testatabg = "img/$cod_area/up-bg.jpg";

$tag_testatabg = "";

if (file_exists($file_testatabg)) $tag_testatabg = "background=\"$file_testatabg\"";

$size = getimagesize($file_testata);
$tag_img = $size[3];


echo "
<table width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=\"center\">
<tr><td>
<!-- TESTATA -->
<table border=0 cellpadding=\"0\" cellspacing=\"0\" width=100% $tag_testatabg bgcolor=\"$colore_sfondo_testata\">
<tr>
<td >
<div align=\"left\"><img src=\"$file_testata\" $tag_img border=0 alt=\"$cod_area\"></div></td>";

if ($cod_area == 'kairos_demo') {
    echo "
	<td  align=\"right\">
<div align=\"right\"><img src=\"img/$cod_area/testata2.gif\" width=\"230\" height=\"72\" alt=\"\" border=\"0\"> </div>
</td>";
}
;


echo "
</tr>
</table>
<!-- FINE TESTATA -->
";

?>

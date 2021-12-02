<P><span class=titolopagina><?php echo($stringa[cartella_file]);?></span></p>

<?php
require "./include/funzioni_materiali.inc";
$cartella=$_REQUEST["cartella"];
$tipo_file=$_REQUEST["tipo"];
$dir=$_REQUEST["dir"];
$contesto=$_REQUEST["contesto"];
$nome_campo=$_REQUEST["nome_campo"];
/*
echo "
<form action=materiali_cancella_file.php method=post>
<input type=hidden name=cartella value=\"$cartella\">
<input type=hidden name=tipo value=\"$tipo_file\">
<input type=hidden name=dir value=\"$dir\">
<input type=hidden name=contesto value=\"$contesto\">
<input type=hidden name=nome_campo value=\"$nome_campo\">";
*/

echo "
<a href=index.php?risorsa=materiali_nuova_cartella&tipo=$tipo_file&cartella=$cartella&dir=$dir&contesto=$contesto&nome_campo=$nome_campo><img src=img/new_folder.gif width=25 height=24 alt=\"$stringa[nuova_cartella]\" border=0></a><a href=index.php?risorsa=materiali_nuovo_file&tipo=$tipo_file&cartella=$cartella&dir=$dir&contesto=$contesto&nome_campo=$nome_campo><img src=img/new_file.gif width=25 height=24 alt=\"$stringa[nuovo_file]\" border=0></a>&nbsp;&nbsp;&nbsp;  <!--<input type=submit value=\"$stringa[cancella_elementi]\"> -->";
?>  
<TABLE border=0 width=461>
<tr></td>
<?php
if ($contesto=="lo") {
	browse_folder($cartella,$tipo_file,$contesto,$nome_campo);
} else {
	browse_folder($cartella,$tipo_file);
};
?>
</td></tr>
	  	  
</TABLE>
<!--</form>--> <BR>
<HR>

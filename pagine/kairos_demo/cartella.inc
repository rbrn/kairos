<P><span class=titolopagina><?php echo($stringa[gestione_cartella_img]);?></span></p>

<span class=testo>[<a href=index.php?risorsa=admin_index><?php echo($stringa[admin]);?></a>]</<span><br>



<?php

require "./include/function_admin.inc";

$cartella=$_REQUEST["cartella"];



echo "

<form action=cancella_file.php method=post>

<input type=hidden name=cartella value=\"$cartella\">

<a href=index.php?risorsa=nuova_cartella&cartella=$cartella><img src=img/new_folder.gif width=25 height=24 alt=\"$stringa[nuova_cartella]\" border=0></a><a href=index.php?risorsa=nuovo_file&cartella=$cartella><img src=img/new_file.gif width=25 height=24 alt=\"$stringa[nuovo_file]\" border=0></a>&nbsp;&nbsp;&nbsp;  <input type=submit value=\"$stringa[cancella_elementi]\">";

?>  

<TABLE border=0 width=461>

<tr></td>

<?php

browse_folder($cartella);

?>

</td></tr>

	  	  

</TABLE>

</form> <BR>

<HR>

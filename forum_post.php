<?php



$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	



$query2 = "SELECT * FROM forum WHERE id_forum='$id_forum'";

$result2=$mysqli->query($query2);

$dati_forum=$result2->fetch_array();


?>







<br><br>

<table border=0 width=80%>

<tr><td>



<?php

$descr_forum = $dati_forum["descrizione"];



if ($op=='replica') {

	// prelevo i dati dell'intervento padre

	$query = "SELECT * FROM forum_posts WHERE id_forum='$id_forum' AND id_post='$id_post_padre'";

	$result=$mysqli->query($query);

	$intervento_padre = $result->fetch_array();

	$id_autore=$intervento_padre["id_autore"];

	mysql_select_db($DBASE_UTENTI,$db);

	$query_u="SELECT * FROM utenti WHERE id_utente='$id_autore'";

	$result_u=$mysqli->query($query_u);

	$dati_autore = $result_u->fetch_array();

	mysql_select_db($DBASE,$db);

	$nome_autore=$dati_autore["nome"]." ".$dati_autore["cognome"];

	$email_autore=$dati_autore["email"];	

	$titolo = "Replica Intervento";

	$oggetto = "Re: ".$intervento_padre["oggetto"];

	$testo = "\n\n\n---- ".

	"($id_autore) $nome_autore"." ha scritto:\n".

	$intervento_padre["testo"].

	"\n--------------------------------\n";

} else {

	$titolo = "Nuovo Intervento";

	$oggetto = "";

	$testo = "";

	$id_post_padre="0";

};



mysql_select_db($DBASE_UTENTI,$db);

$query_u="SELECT * FROM utenti WHERE id_utente='$id_utente'";

$result_u=$mysqli->query($query_u);

$dati_autore = $result_u->fetch_array();

mysql_select_db($DBASE,$db);

$id_autore=$id_utente;

$nome_autore=$dati_autore["nome"]." ".$dati_autore["cognome"];

$email_autore=$dati_autore["email"];	



echo "

<p>

<span class=testo><b>$titolo</b></span>

</p>

<p align=left>

<span class=testo><b>$descr_forum</b></span>

</p>

<hr size=1>

<span class=testopiccolo>[<a href=javascript:history.back()>Indietro</a>]</span>

<br>

<hr size=1>";



if ($dati_forum["file_allegati"]=='1') {

	echo "

	<FORM action=forum_store_post.php encType=multipart/form-data method=post>\n

	<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>\n";

} else {

	echo "<form action=forum_store_post.php method=post>\n";

};







echo "

<input type=hidden name=id_forum value=".$id_forum.">

<input type=hidden name=id_post_padre value=".$id_post_padre.">

<input type=hidden name=vista value=".$vista.">

<input type=hidden name=modo value=".$modo.">";

echo "

<table border=0>";

echo "

<tr>

<td align=right valign=top><span class=testopiccolo><b>Autore</b>:</span></td>

<td valign=top><span class=testopiccolo>$id_utente</span></td>

</tr>

";



printf('

<tr>

<td align=right valign=top><span class=testopiccolo><b>Oggetto</b>:</span></td>

<td valign=top><input type=text name=oggetto maxlength=150 size=60 value="%s"></td>

</tr>',$oggetto);







if (!ereg('MSIE',$_SERVER["HTTP_USER_AGENT"]) {

echo"

<tr>

<td colspan=2 valign=top><span class=testopiccolo><b>Intervento:</b></span></td>

</tr>

<tr>

<td colspan=2 valign=top>

<TEXTAREA cols=70 name=testo rows=10 wrap=virtual>".$testo."</TEXTAREA>

</td>

</tr>";

} else {

	echo "<input type=\"hidden\" name=\"testo\" id=\"testo\">\n";

	require "./include/editor.inc";

};



if ($dati_forum["file_allegati"]=='1') {

echo "

<tr>

<td align=right valign=top><span class=testopiccolo><b>File allegato (max. 5MB)</b>:</span></td>

<td valign=top><INPUT name=nome_file type=file></td>

</tr>

";

};



echo "

<tr>

<td valign=top align=right>

<span class=testopiccolo><b>Icona intervento:</b></span>

</td>

<td><input type=radio checked name=icona_post value=messaggio> <img src=img/forum/messaggio.gif alt=generica> <input type=radio name=icona_post value=domanda> <img src=img/forum/domanda.gif alt=domanda> <input type=radio name=icona_post value=idea> <img src=img/forum/idea.gif alt=idea> <input type=radio name=icona_post value=approvo> <img src=img/forum/approvo.gif alt=approvo> <input type=radio name=icona_post value=disapprovo> <img src=img/forum/disapprovo.gif alt=disapprovo> <input type=radio name=icona_post value=importante> <img src=img/forum/importante.gif alt=importante>

<br> 

<input type=radio name=icona_post value=confuso> <img src=img/forum/confuso.gif alt=confuso> <input type=radio name=icona_post value=contento> <img src=img/forum/contento.gif alt=contento> <input type=radio name=icona_post value=triste> <img src=img/forum/triste.gif alt=triste> <input type=radio name=icona_post value=scherzo> <img src=img/forum/scherzo.gif alt=scherzo> 

<input type=radio name=icona_post value=arrabbiato> <img src=img/forum/arrabbiato.gif alt=arrabbiato> <input type=radio name=icona_post value=moltoarrabbiato> <img src=img/forum/moltoarrabbiato.gif alt=moltoarrabbiato> 

<br>

<input type=radio name=icona_post value=fico> <img src=img/forum/fico.gif alt=fico>

</td>

</tr>

\n";

     

echo "

<tr>

<td>&nbsp;</td>

<td align=left valign=top>

<input type=checkbox name=repemail> <span class=testopiccolo>Invia anche al mio email eventuali repliche</span>

</td></tr>

</table>";



if (!ereg('MSIE',$_SERVER["HTTP_USER_AGENT"]) { 

echo "

<input type=submit value=Invia>";

} else {

echo "<input type=submit value=Invia onclick=\"inoltra();return true\">

};







echo "

</form>

";

?>

</td></tr>

</table>







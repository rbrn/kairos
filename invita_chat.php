<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	
$id_utente=$kairos_cookie[0];
$id_utente_invitare=$_REQUEST["id_utente_invitare"];
$stanza=$_REQUEST["stanza"];
?>
<HTML>
<HEAD><TITLE><?php echo($stringa[utente_invitato]);?></TITLE>
<?php
echo "
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>
<script language="JavaScript" src="script/funzioni.js"></script>
<SCRIPT LANGUAGE="JAVASCRIPT" TYPE="TEXT/JAVASCRIPT">
var StayAlive = 5;
function KillMe(){
setTimeout("self.close()",StayAlive * 1000);
}
</SCRIPT>
</HEAD>
<BODY bgcolor=<?php echo($colore_sfondo);?> onload="KillMe();self.focus()">
<table border=0 width=100%>
<tr>
<td width=5>&nbsp;</td>
<td bgcolor=white>
<p>
&nbsp;
</p>
<!-- CONTENUTO DELLA PAGINA -->
<TABLE BORDER=0 ALIGN=CENTER width=90%>
<tr>
<td>
<?php
// parametro di richiamo: id_utente_invitare,stanza
$query = "INSERT INTO invito_chat (id_utente,id_invitato,stanza) VALUES ('$id_utente','$id_utente_invitare','$stanza')";
$result=$mysqli->query($query);

echo "<span class=testo><b>$id_utente_invitare</b>: $stringa[utente_invitato_msg]</span><br><br>";

echo "<span class=testopiccolo><i>$stringa[chiude_da_sola]</i></span>";
?>
</td>
</tr>
</table>	
<!-- FINE CONTENUTO DELLA PAGINA -->
</td>
</tr>
</table>
</body>
</html>

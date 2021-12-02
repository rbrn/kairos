<?php
require "./include/init_sito.inc";
$data_invito=$_REQUEST["data_invito"];
$stanza=$_REQUEST["stanza"];
$id_host=$_REQUEST["id_host"];
$nome_stanza=$stanza;
if ($stanza=="Generale") $nome_stanza=$stringa[$stanza];
echo "
	<html>
	<head>
	<title>$stringa[invito_chat]</title>
	<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
	<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
	<script language=javascript>
	var mainWin = window.dialogArguments;
	</script>
	</head>
	<body bgcolor=$colore_sfondo>
	<table width=100% cellpadding=5>
	<tr><td align=center>
	<span class=testopiccolo>
	<b>$data_invito</b><br>
	<p>
	$stringa[ricevuto_invito_chat]: <b>$nome_stanza</b><br>$stringa[da_p]: <b>$id_host</b>
</p>
<p>
[<a style=\"cursor:hand;text-decoration:underline\" onclick=\"mainWin.location='chat_entra.php?stanza=$stanza'; self.close();\">$stringa[accetto]</a>] [<a style=\"cursor:hand;text-decoration:underline\"  onclick=\"javascript:self.close();\">$stringa[declino]</a>]
<OBJECT classid=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\"
 codebase=\"http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0\"
 WIDTH=\"1\" HEIGHT=\"1\" id=\"invito_chat\" ALIGN=\"\">
 <PARAM NAME=movie VALUE=\"img/invito_chat.swf\"> <PARAM NAME=quality VALUE=high> <PARAM NAME=bgcolor VALUE=#FFFFFF> <EMBED src=\"img/invito_chat.swf\" quality=high bgcolor=#FFFFFF  WIDTH=\"1\" HEIGHT=\"1\" NAME=\"invito_chat\" ALIGN=\"\"
 TYPE=\"application/x-shockwave-flash\" PLUGINSPAGE=\"http://www.macromedia.com/go/getflashplayer\"></EMBED>
</OBJECT>
</p>
</span>	
</td> 
</td></tr>
</table>
<br>
</body>
</html>
";

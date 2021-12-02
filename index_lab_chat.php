<?php
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");
require "./include/init_sito.inc";
$chat_stanza=$_REQUEST["chat_stanza"];
?>
<html>
<head>
	<title>Chat</title>
</head>
<FRAMESET ROWS="103,*" BORDER="0" name="radice" id="radice">
	<FRAME SRC="testata_chat.php" NAME="testata" MARGINWIDTH=0 MARGINHEIGHT=0 SCROLLING="NO" NORESIZE>
		<FRAMESET ROWS="200,*,50" BORDER=0 name="frame11" id="frame11">
			<frame name="finestra_pagina" src="pagina_chat.php" marginwidth="3" marginheight="3" scrolling="auto" frameborder="0" noresize>
			<frame name="finestra_chat" src="audio_lab_chat.php" marginwidth="3" marginheight="3" scrolling="auto" frameborder="0" noresize>

		</FRAMESET>

</FRAMESET>
</html>


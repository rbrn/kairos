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

	<FRAMESET COLS="*,130" BORDER="0" name="frame1" id="frame1">
<?php
if ($chat_stanza=='lab_'.$id_corso_s) {
?>
		<FRAMESET ROWS="200,*,50" BORDER=0 name="frame11" id="frame11">
			<frame name="finestra_pagina" src="pagina_chat.php" marginwidth="3" marginheight="3" scrolling="auto" frameborder="0" noresize>
<?php } else { ?>
		<FRAMESET ROWS="*,50" BORDER=0 name="frame11" id="frame11">
<?php }; ?>

<?php
if ($win_ie) {
	$msg_chat="pmessaggi_chat.php";
} else {
	$msg_chat="messaggi_chat.php";
};
?>
			<frame name="finestra_chat" src="<?php echo($msg_chat);?>" marginwidth="3" marginheight="3" scrolling="auto" frameborder="0" noresize>

			<frame name="finestra_input" src="input_chat.php" marginwidth="0" marginheight="0" scrolling="no" frameborder="0" noresize>
		</FRAMESET>
		<frameset rows="*,0">
			<frame name="finestra_utenti" src="utenti_chat.php" marginwidth="0" marginheight="0" scrolling="auto" frameborder="0" noresize>
			
			<FRAME SRC="chat_loader.php" NAME="loader" FRAMEBORDER="0" BORDER="0" FRAMESPACING="0" MARGINHEIGHT="0" MARGINWIDTH="0" SCROLLING="NO">
		</frameset>
	</FRAMESET>
</FRAMESET>
</html>


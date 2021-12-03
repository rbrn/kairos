<?php
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");

require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect(C_DB_HOST,C_DB_USER,C_DB_PASS);
mysql_select_db(C_DB_NAME,$db);


$id_utente=$kairos_cookie[0];
$chat_stanza=$_REQUEST["chat_stanza"];

$stanza=$chat_stanza;
$Charset1 = (isset($FontName) && $FontName != "") ? $FontName : $Charset;
?>
<HTML>
<head>

<script language="JavaScript">
function imposta_scroll() {
	document.body.scrollTop=65000;
}
</script>
<LINK REL="stylesheet" HREF="./stili/<?php echo($cod_area);?>/style.css" TYPE="text/css">
</head>

<body class="mainframe" onload=imposta_scroll()>

<?php

$tempo=time() - 2 * 60 * 60;
$query="DELETE FROM ".C_MSG_TBL." WHERE m_time < $tempo";
$result=$mysqli->query($query);

$tempo=time() - 4 * 60;
$query="DELETE FROM ".C_USR_TBL." WHERE u_time < $tempo";
$result=$mysqli->query($query);


$query="SELECT * FROM ".C_MSG_TBL." WHERE room='$stanza' ORDER BY m_time DESC LIMIT 20";

$result=$mysqli->query($query);



$MessagesString = "";
$last_time=0;
$righe_chat=0;

while ($riga=$result->fetch_array()) {

	
	
	$username=$riga["username"];

	$time=$riga["m_time"];

	$message=$riga["message"];



	$NewMsg = "<P CLASS=msg>";

	$NewMsg .= "<SPAN CLASS=time>".date("H:i:s", $time +  C_TMZ_OFFSET*60*60)."</SPAN> ";

			

	if (ereg("^/(enter|exit)[[:space:]](.+)$",$message,$Regs))

	{
		if ($Regs[1] == "enter") {
			$message = $Regs[2]." ".$stringa[entra_stanza];
		} else {
			$message = $Regs[2]." ".$stringa[esce_stanza];
		};

		$NewMsg .= " <SPAN CLASS=notify>$message</SPAN>";

	} else {

			

		if (substr($message,22,1) == '+') {

			$verbo = "";

			$message2 = substr($message,0,22).substr($message,23);

			$message = $message2;

		} else {

			$verbo = $stringa[dice];

		};

			

		if ($verbo==$stringa[dice]) {

			$NewMsg .= "<B>$username $verbo</B> $message</P>";

		} else {

			$NewMsg .= "<i><B>$username</B> $message</i></P>";		

		};

	

	};

	$MessagesString = $NewMsg.$MessagesString;

	//$MessagesString = $MessagesString.$NewMsg;
	if ($last_time==0) $last_time=$time;
	$righe_chat++;
};

echo($MessagesString);



echo("\n<SCRIPT TYPE=\"text/javascript\" LANGUAGE=\"javascript\">\n<!--\nwindow.scrollBy(0, 65000);\n// -->\n</SCRIPT>\n");

flush();

echo("<SCRIPT TYPE=\"text/javascript\" LANGUAGE=\"javascript\">\n<!--\nwindow.scrollBy(0, 65000);\n// -->\n</SCRIPT>\n");

flush();

?>

</BODY>

</html>




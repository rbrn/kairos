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
<!-- faccio in modo che questa pagina venga aggiornata ogni 4 secondi -->
<script language="JavaScript">
window.setTimeout("{window.location='chat_loader.php';}", 4000);
</script>

<LINK REL="stylesheet" HREF="./stili/<?php echo($cod_area);?>/style.css" TYPE="text/css">

</head>

<BODY CLASS=frame>
<?php

$tempo=time() - 2 * 60 * 60;
$query="DELETE FROM ".C_MSG_TBL." WHERE m_time < $tempo";
$result=$mysqli->query($query);

$tempo=time() - 2 * 60 * 60;
$query="DELETE FROM ".C_USR_TBL." WHERE u_time < $tempo";
$result=$mysqli->query($query);

$tempo=time() - 2 * 60 * 60;
$query="DELETE FROM c_moderazione WHERE time_out < $tempo and id_stanza='$stanza'";
$result=$mysqli->query($query);

$query="SELECT * FROM ".C_MSG_TBL." WHERE room='$stanza' ORDER BY m_time DESC LIMIT 80";

$result=$mysqli->query($query);



$MessagesString = "";
$last_time=0;
$righe_chat=0;
$suono=false;
$nome_suono="";
while ($riga=$result->fetch_array()) {
	
	$username=$riga["username"];
	$time=$riga["m_time"];
	$message=$riga["message"];

	$mostra=true;	
	$NewMsg="";
	for ($i=0;$i<count($suoni_chat);$i++) {
		$pat=$suoni_chat[$i]."_ascolta";
		if (ereg("\*$pat\*",$message)) {
			if ($username==$kairos_cookie[0]) {
				$query2="DELETE FROM ".C_MSG_TBL." WHERE room='$stanza' AND username='$username' AND message='*$pat*'";
				$suono=true;
				$nome_suono=$suoni_chat[$i];
				$mysqli->query($query2);
				echo mysql_error();
			};
			$mostra=false;
		};
	};
	
	if ($mostra) {
	$NewMsg = "<P CLASS=msg>";

	$NewMsg .= "<SPAN CLASS=time>".date("H:i:s", $time +  C_TMZ_OFFSET*60*60)."</SPAN> ";

			

	if (ereg("^/(enter|exit|moderazione)[[:space:]](.+)$",$message,$Regs))

	{
		if ($Regs[1] == "enter") {
			$message = $Regs[2]." ".$stringa[entra_stanza];
		} else {
			if ($Regs[1] == "exit") {
				$message = $Regs[2]." ".$stringa[esce_stanza];
			} else {
				$message=$Regs[2];
			};
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

	};
	
	$NewMsg = ereg_replace("([^<]+)[\]","\\1\\\\",$NewMsg);
	
	$NewMsg = str_replace("\"","\\\"",$NewMsg);
	$NewMsg = str_replace("\'","\\\'",$NewMsg);
	
	$MessagesString = $NewMsg.$MessagesString;
	
	
	if ($last_time==0) $last_time=$time;
	$righe_chat++;
};

$corpo=$MessagesString;
//echo $corpo;

if ($suono) {
echo "<OBJECT classid=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\"
 codebase=\"http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0\"
 WIDTH=\"1\" HEIGHT=\"1\" id=\"suono_chat\" ALIGN=\"\">
 <PARAM NAME=movie VALUE=\"img/$nome_suono.swf\"> <PARAM NAME=quality VALUE=high> <PARAM NAME=bgcolor VALUE=#FFFFFF> <EMBED src=\"img/$nome_suono.swf\" quality=high bgcolor=#FFFFFF  WIDTH=\"1\" HEIGHT=\"1\" NAME=\"suono_chat\" ALIGN=\"\"
 TYPE=\"application/x-shockwave-flash\" PLUGINSPAGE=\"http://www.macromedia.com/go/getflashplayer\"></EMBED>
</OBJECT>";
};

$suona_brano=false;
$query="SELECT * FROM musica_chat WHERE stanza='$stanza'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
if ($riga) {
	$brano=$riga["brano"];
	$query2="SELECT * FROM musica_chat_stato WHERE stanza='$stanza' and id_utente='$kairos_cookie[0]'";
	$result2=$mysqli->query($query2);
	if ($result2->num_rows) {
		$riga2=$result2->fetch_array();
		if ($brano!=$riga2["brano"]) {
			$query2="DELETE FROM musica_chat_stato WHERE stanza='$stanza' and id_utente='$kairos_cookie[0]'";
			$mysqli->query($query2);
			$query2="INSERT INTO musica_chat_stato SET stanza='$stanza',brano='$brano',id_utente='$kairos_cookie[0]'";
			$mysqli->query($query2);
			$brano="juke_box/".$riga["brano"].".mp3";
			$suona_brano=true;
		}
	} else {
		$query2="INSERT INTO musica_chat_stato SET stanza='$stanza',brano='$brano',id_utente='$kairos_cookie[0]'";
		$mysqli->query($query2);
		$brano="juke_box/".$riga["brano"].".mp3";
		$suona_brano=true;
		
	}
}

?>

<script language="javascript">
if (window.parent.frames['finestra_chat'].window.document.body) {
window.parent.frames['finestra_chat'].window.document.body.innerHTML="<?php echo($corpo);?>";
window.parent.frames['finestra_chat'].window.document.body.scrollTop=65000;
<?php if ($suona_brano) { ?>
window.parent.frames['finestra_musica'].window.document.body.innerHTML="<object classid=\"clsid:d27cdb6e-ae6d-11cf-96b8-444553540000\" codebase=\"http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,0,0\" width=\"56\" height=\"28\" id=\"mp3player_med\" align=\"middle\"><param name=\"allowScriptAccess\" value=\"sameDomain\" /><param name=\"movie\" value=\"juke_box/mp3player_med.swf?filemp3=<?php echo($brano);?>\" /><param name=\"quality\" value=\"high\" /><param name=\"bgcolor\" value=\"#ffffff\" /><embed src=\"juke_box/mp3player_med.swf?filemp3=<?php echo($brano);?>\" quality=\"high\" bgcolor=\"#ffffff\" width=\"56\" height=\"28\" name=\"mp3player_med\" align=\"middle\" allowScriptAccess=\"sameDomain\" type=\"application/x-shockwave-flash\" pluginspage=\"http://www.macromedia.com/go/getflashplayer\" /></object><br>[<a href=\"#\" onclick=\"goLights();\">Luci</a>] [<a href=\"#\" onclick=\"stopLights();\">stop Luci</a>]";
<?php }; ?>
}
</script>
</BODY>

</html>




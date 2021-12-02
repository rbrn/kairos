<?php
$C=$_REQUEST["C"];
if (isset($_REQUEST["CookieColor"])) $CookieColor = $_REQUEST["CookieColor"];
if(!isset($C))
{
	if(!isset($CookieColor))
	{
		
		$C = "#000000";
	}
	else
	{
		$C = $CookieColor;
	}
};
setcookie("CookieColor", $C, time() + 60*60*24*365);   
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
require "./include/mysql.class.inc";

$id_utente=$kairos_cookie[0];
refresh_utente($id_utente);
$chat_stanza=$_REQUEST["chat_stanza"];
$U=$id_utente;
$R=$chat_stanza;

$DbLink = new DB;


$DbLink->query("SELECT status,room FROM ".C_USR_TBL." WHERE username = '$U' LIMIT 1");
if ($DbLink->num_rows() != 0)
{
	list($status,$room) = $DbLink->next_record();
	$DbLink->clean_results();
	$kicked = 0;
	if ($room != stripslashes($R))	
	{
		$DbLink->query("INSERT INTO ".C_MSG_TBL." VALUES ('$T', '$R', '', '', ".time().", '', '/exit $U')");
		$kicked = 3;
	}
	elseif ($status == "k")			
	{
		$DbLink->query("INSERT INTO ".C_MSG_TBL." VALUES ('$T', '$R', '', '', ".time().", '', '/exit $U')");
		$kicked = 1;
	}
	elseif ($status == "d")			
	{
		$kicked = 2;
	}
	if ($kicked > 0)
	{
		
		?>
		<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript">
		<!--
		parent.location = '<?php echo("$From?L=$L&U=".urlencode(stripslashes($U))."&E=".urlencode(stripslashes($R))."&KICKED=${kicked}"); ?>';
		// -->
		</SCRIPT>
		<?php
		$DbLink->close();
		exit;
	}
}
else
{
	$DbLink->clean_results();
}


unset($TextColors);
$TextColors = array(
	"#FF0000","#FF0099","#FF00FF","#CC00FF","#9900FF","#6600FF","#000099","#0000FF","#0066FF",		"#00CCFF","#00FFFF","#00FF66","#009900","#006600","#999900","#99CC00","#FFFF00","#FF9900",
		"#FF6600","#996633","#990000","#660000","#000000","#666666","#999999");
	
$Charset1 = (isset($FontName) && $FontName != "") ? $FontName : $Charset;
?>

<HTML>
<HEAD>


<LINK REL="stylesheet" HREF="./stili/<?php echo($cod_area);?>/style.css" TYPE="text/css">



<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript">

function apri_scheda(newURL, newName, newFeatures, orgName) {
  var remote = open(newURL, newName, newFeatures);
  if (remote.opener == null)
    remote.opener = window;
  remote.opener.name = orgName;
  return remote;
}

function help_popup()
{
	if (parent.is_help_popup && !parent.is_help_popup.closed)
	{
		parent.is_help_popup.focus();
	}
	else
	{
		parent.is_help_popup = window.open("help_popup.php","help_popup","width=600,height=350,scrollbars=yes,resizable=yes");
		if (parent.ver4) parent.is_help_popup.moveTo(parent.mouseX-10,parent.mouseY-400);
	};
}


function get_focus()
{
	window.focus();
	document.Form.riga_chat.focus();
}


image1 = new Image(4,20);
image1.src = "images/unselColor.gif";
image2 = new Image(4,20);
image2.src = "images/selColor.gif";
var SelColor = null;

function ChangeColor(ColorVal,ColorRank)
{
	if (SelColor != ColorRank)
	{
		if (document.all)
		{
			obj1 = document.all[SelColor];
			obj2 = document.all[ColorRank];
		}
		else if (document.images)
		{
			obj1 = document.images[SelColor];
			obj2 = document.images[ColorRank];
		}
		else return;

		if (SelColor != null)
		{
			obj1.src = image1.src;
		}
		SelColor = ColorRank;
		document.Form.C.value = ColorVal;
		obj2.src = image2.src;
	}
	document.Form.riga_chat.focus();
}


function callColorDlg(sInitColor){

if (sInitColor == null) 
	
	var sColor = dlgHelper.ChooseColorDlg();
else
	var sColor = dlgHelper.ChooseColorDlg(sInitColor);
	
	sColor = sColor.toString(16);
	
if (sColor.length < 6) {
  var sTempString = "000000".substring(0,6-sColor.length);
  sColor = sTempString.concat(sColor);
}

	document.Form.C.value = sColor;
	sInitColor = sColor;
}
</SCRIPT>
</HEAD>

<body class=frame onload="get_focus()">

<?php
$refresh=$_REQUEST["refresh"];

if ($refresh) {

	echo "

	<SCRIPT  LANGUAGE=\"JavaScript\">

		parent.loader.location = 'chat_loader.php';

	</SCRIPT>

	";

};

?>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
<td valign=top><form name="Form" action=input_op.php method=post>
<INPUT TYPE="hidden" NAME="C" VALUE="<?php echo($C); ?>">
<input type=text name=riga_chat size=50><input type=submit value="<?php echo($stringa[invia]);?>"></form> 
</td>
<td>&nbsp;&nbsp;</td>
<td valign=top><TABLE BORDER=0 CELLPADDING=0 CELLSPACING=0>
<TR HEIGHT=20>
			<?php
			while(list($key, $ColorCode) = each($TextColors))
			{
				$i = $key + 1;
				if ($ColorCode == $C)
				{
					$wichImage = "selColor.gif";
					$wichSelected = $i;
				}
				else
				{
					$wichImage = "unselColor.gif";
				}
				?>
				<TD BGCOLOR="<?php echo($ColorCode); ?>"><A HREF="javascript:ChangeColor('<?php echo($ColorCode); ?>','<?php echo("C${i}"); ?>');"><IMG SRC="images/<?php echo($wichImage); ?>" ALT="<?php echo($ColorCode); ?>" NAME="<?php echo("C${i}"); ?>" BORDER=0 WIDTH=4 HEIGHT=20></A></TD>
				<?php
			}
			?>
			
</TR>
</TABLE>
</td>
<td valign=top>
<?php 
if ($win_ie) {
		echo "
		&nbsp;<a href=\"#\" onclick=\"callColorDlg('$C')\">$stringa[scegli_colore]</a>";
};
?>
		<!--&nbsp;&nbsp;<a href="#" title="Elenco suoni che si possono richiamare in chat" onclick="javascript:apri_scheda('../suoni.php',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');">Suoni</a>-->&nbsp;&nbsp;<a href="#" title="<?php echo($stringa[elenco_immagini_chat]);?>" onclick="javascript:apri_scheda('img.php',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');"><?php echo($stringa[immagini_chat]);?></a>&nbsp;&nbsp;<A HREF="#>" onClick="help_popup(); return false" TARGET="_blank"><?php echo($stringa[istruzioni_chat]);?></A>

<?php 
if ($win_ie) {
?>
 <OBJECT id=dlgHelper CLASSID="clsid:3050f819-98b5-11cf-bb82-00aa00bdce0b" width="0px" height="0px"></OBJECT>
<?php 
};
?>

<?php 
if ($cod_area=="kairos_masterunitus" or $cod_area=="kairos_fleo") {
?>
&nbsp;&nbsp;<a href="#" title="brani in playlist" onclick="javascript:apri_scheda('juke_box.php', 'myRemotejuke_box',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowjuke_box');">Juke Box</a>
<?php 
};
?>
</td>
</tr>
</table>
</body>

</html>




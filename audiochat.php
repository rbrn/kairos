<?php 

$canale=$_GET["canale"];
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>AudioChat</title>
</head>

<body>
<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=8,0,0,0" width="220" height="165" id="walkietalkie" align="middle">
<param name="allowScriptAccess" value="always" />
<param name="swLiveConnect" value="true" />
<param name="movie" value="http://www.yackpack.net/yackpack/walkietalkie.swf" />
<param name="quality" value="high" />
<param name="FlashVars" value="globalchaturl=<?php echo($canale);?>" />
<param name="wmode" value="transparent" />
<embed src="http://www.yackpack.net/yackpack/walkietalkie.swf" quality="high" wmode="transparent" width="220" height="165" name="walkietalkie" align="middle" allowScriptAccess="always" swLiveConnect="true" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" FlashVars="globalchaturl=<?php echo($canale);?>"  />
</object>


</body>
</html>

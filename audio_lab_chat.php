<?php
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");
require "./include/init_sito.inc";
?>
<html>
<head>
	<title></title>
<?php
echo "
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>
</head>

<body>
<?php 
$rid="1-1074682169766";
if ($cod_area=="kairos_master") $rid="175-1108377738159";
?>
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td class=titolodot>
Audio Chat
</td></tr>
<tr><td>
<SCRIPT type="text/javascript" SRC="http://cgi3.garamond.it:8080/wimba/voicedirect/voicedirect.js"></SCRIPT>
<SCRIPT type="text/javascript">
  var w_p = new Object();
  w_p.view_archives_url="/wimba/board?action=display";
  w_p.view_archives_target = "wimba_archives";
  
  w_p.rid="<?php echo($rid);?>";
 
  if (window.w_voicedirect_tag) w_voicedirect_tag(w_p);
  else document.write("Problemi con il server audio");
</SCRIPT>
</td></tr>
</table>
</body>
</html>

<?php
$excludeTemplate = true;
$id_risorsa=$_REQUEST["id_risorsa"];
$tipo=$_REQUEST["tipo"];
$url=$_REQUEST["url"];
$launch_data=$_REQUEST['launch_data'];
$kairos=$_REQUEST['kairos'];
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">

<html>
<head>
	<title>SCO Viewer</title>
</head>


<!-- frames -->
<frameset  rows="0,*">
    <frame name="API" src="scorm/scorm_api.php?tipo=<?php echo($tipo);?>&url=<?php echo($url);?>&id_risorsa=<?php echo($id_risorsa);?>&launch_data=<?php echo $launch_data?>&kairos=<?php echo $kairos?>" tipo="10" marginheight="10" scrolling="no" frameborder="0">
<!--
	<frame name="API_1484_11" src="scorm/scorm_api.php?id_lo=<?php echo($id_risorsa);?>" marginwidth="10" marginheight="10" scrolling="no" frameborder="0">
-->
	<frame name="contenuto" src="attesa.htm" marginwidth="10" marginheight="10" scrolling="auto" frameborder="0">
</frameset>
<body>
</body>
</html>


<?php
$excludeTemplate = true;
require "../include/init_sito.inc";

$id_risorsa=$_REQUEST["id_risorsa"];
$tipo=$_REQUEST["tipo"];
$url=$_REQUEST["url"];
$launch_data=$_REQUEST['launch_data'];
$kairos=$_REQUEST['kairos'];

if ($tipo=="lo") {
	$query_lo="SELECT * FROM lo WHERE id_lo='$id_risorsa'";
	$result_lo=$mysqli->query($query_lo);
	$riga_lo=$result_lo->fetch_array();
	$tipo_shell=$riga_lo["lo_shell"];
	switch  ($tipo_shell) {
		case 0:
			$lo_viewer_script="lo_viewer.php";
			break;
		case 1:
			$lo_viewer_script="lo_viewer_new.php";
			break;
		
	}	
	$contenuto=$PATH_ROOT."$lo_viewer_script?risorsa=$id_risorsa&kairos=$kairos";
} else {
	$contenuto=$url;
};

$scoid=$_REQUEST[id_risorsa];
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
	
	<title>API</title>
<script language="JavaScript" type="text/javascript" src="request.js"></script>	
<script language="JavaScript" type="text/javascript" src="datamodels/scorm1_2.js.php?scoid=<?php echo $scoid?>&launch_data=<?php echo $launch_data?>"></script>	
<script language="JavaScript">
function carica_sco() {
	parent.contenuto.document.location='<?php echo $contenuto ?>';
}
</script>
</head>

<body onLoad="carica_sco()">
API (lascia stare, non ti preoccupare di questa roba, non e' cosa per te)
</body>
</html>

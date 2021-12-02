<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>LOM Editor:msg</title>

	<link rel="stylesheet" href="stile_lom.css.php">
	
</head>

<body>
<?php
$msg=$_REQUEST[msg];
$id_lo=$_REQUEST[id_lo];
echo "
<p align=\"center\">
<table border=0>
<tr><td>$msg</td></tr>
</table>
<br>
[<a href=index.php?id_lo=$id_lo>Indietro</a>]
</p>
";
?>
</body>
</html>

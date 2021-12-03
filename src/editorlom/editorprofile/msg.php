<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>LOM Application Profile Editor:msg</title>

	<link rel="stylesheet" href="../stile_lom.css.php">
	
</head>

<body>
<?php
$msg=$_REQUEST[msg];
echo "
<p align=\"center\">
<table border=0>
<tr><td>$msg</td></tr>
</table>
<br>
[<a href=\"javascript:history.back()\">Indietro</a>]
</p>
";
?>
</body>
</html>

<?php
require "./config_xml_lom.php";
$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);

$id_lom=$_REQUEST[id_lom];
$id_profile=$_REQUEST[id_profile];

$query="SELECT * FROM lo_schema WHERE id_lom='$id_lom' AND id_profile='$id_profile' ORDER BY id_lom";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$id_lom=$riga[id_lom];
$nome=$riga[nome];
$commento=nl2br($riga[commento]);
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>LOM Editor: Guida</title>

	<link rel="stylesheet" href="stile_lom.css.php">
	
</head>

<body>
<?php
echo "
<div class=\"title\">$id_lom.$nome</div>";
echo "
<table border=0 cellpadding=05>
<tr><td>$commento</td></tr>
</table>
";
?>
</body>
</html>

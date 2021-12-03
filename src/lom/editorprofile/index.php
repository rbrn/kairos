<?php
require "./config.php";

$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>LOM Application Profile Editor</title>
	<link rel="stylesheet" href="stile_lom.css.php">

</head>

<body>
<TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
<tr>
<td class=testonegativo height=30 valign=center bgcolor=<?php echo($colore_scuro);?>>
<img src="../ico_lom.gif" width="20" height="20" alt="" align=absMiddle>&nbsp;<b>LOM Application Profile Editor</b></td></tr>
<tr><td valign=top>

<TABLE cellSpacing=1 cellPadding=1 width="100%" bgColor=#ffffff border=0>
<?php
$query="SELECT * FROM profile ORDER BY id_profile";
$result=$mysqli->query($query);

echo "<table border=\"0\" cellpadding=5>";
while ($riga=$result->fetch_array()) {
	$descrizione=$riga[descrizione];
	$id_profile=$riga[id_profile];
	
	echo "
	<tr>
	<td>$descrizione</td>
	<td>[<a href=profile_index.php?id_profile=$id_profile>Apri</a>]</td>
	<td>[<a href=profile_form.php?id_profile=$id_profile>Modifica</a>]</td>";
};
echo "</table>";

?>
</td></tr>
</table>
<br clear="all" />
<hr size=1>
<p align=center>
LOM Editor & Metadata Generator - &copy;2005 - <a href="http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com" target="_blank">Garamond</a>
</p>
</body>
</html>

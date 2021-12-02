<?php
require "./config.php";

$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);

$id_profile=$_REQUEST[id_profile];

$azione="nuovo";
$descrizione="";
if ($id_profile) {
	$query="SELECT * FROM profile WHERE id_profile='$id_profile'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$descrizione=htmlentities($riga[descrizione]);
	$azione="modifica";
};

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>LOM Application Profile Editor: <?php echo $azione ?></title>
	<link rel="stylesheet" href="stile_lom.css.php">

</head>

<body>
<div class="title">LOM Application Profile Editor: <?php echo $azione ?></div>
<table border=0 cellpadding=10 width=100%>
<tr><td valign=top>
[<a href=index.php>Indietro</a>]
<hr size=1>
<?php
echo "
<form action=\"profile_op.php\" method=\"post\">
<input type=hidden name=\"azione\" value=\"$azione\">

<table border=\"0\">
<tr>
<td><span class=label>Identificativo:</span></td>";

if ($azione=="nuovo") {
	echo "<td><input type=\"text\" name=\"id_profile\" size=\"20\"></td>";
} else {
	echo "<td>$id_profile<input type=hidden name=\"id_profile\" value=\"$id_profile\"></td>";
};
echo "</tr>";
echo "
<tr>
<td><span class=label>Descrizione:</span></td>
<td><input type=\"text\" name=\"descrizione\" size=\"70\" value=\"$descrizione\"></td></tr>";

echo "
<tr>
<td valign=\"top\"></td>
<td valign=\"top\" align=\"center\"><input type=\"submit\" value=\"ok\"></td>
</tr>";

echo "</table>";

echo "</form>";
?>
</td></tr></table>
<br clear="all" />
<hr size=1>
<p align=center>
LOM Editor & Metadata Generator - &copy;2005 - <a href="http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com" target="_blank">Garamond</a>
</p>
</body>
</html>

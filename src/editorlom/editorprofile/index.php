<?php
require "../config.php";

$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>LOM Application Profile Editor</title>
	<link rel="stylesheet" href="../stile_lom.css.php">

</head>

<body>
<div class="title">LOM Application Profile Editor</div>

[<a href=profile_form.php>Nuovo</a>] [<a href="../index.php">LOM Editor</a>]
<hr size=1>
<?php
$query="SELECT * FROM profile ORDER BY id_profile";
$result=$mysqli->query($query);

echo "<table border=\"0\">";
while ($riga=$result->fetch_array()) {
	$descrizione=$riga[descrizione];
	$id_profile=$riga[id_profile];
	
	echo "
	<tr>
	<td>$descrizione</td>
	<td>[<a href=profile_index.php?id_profile=$id_profile>Apri</a>]</td>
	<td>[<a href=profile_form.php?id_profile=$id_profile>Modifica</a>]</td>";
	
	if ($id_profile<>"default" and $id_profile<>"lom" and $id_profile<>"lom_garamond") { 
		echo "<td>[<a href=profile_del.php?id_profile=$id_profile>Cancella</a>]</td>";
	} else {
		echo "<td></td>";
	};
};
echo "</table>";

?>

<br clear="all" />
<hr size=1>
LOM Editor & Metadata Generator - &copy;2005 - <a href="http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com/kairos" target="_blank">Garamond</a>
</body>
</html>

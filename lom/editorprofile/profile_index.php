<?php
require "./config.php";

function mostra_lom($id_lom,$id_profile) {
	global $db;
	global $colore_sfondo_neutro,$colore_sfondo;
	
	$query="SELECT * FROM lo_schema WHERE id_lom_sup='$id_lom' AND id_profile='$id_profile' ORDER BY id_lom";
	$result=$mysqli->query($query);
	
	$colore="$colore_sfondo";
		while ($riga=$result->fetch_array()) {
		$id_lom_r=$riga[id_lom];
		$nome=$riga[nome];
		$tipocampo=$riga[tipocampo];
		$obbligatorio=$riga[obbligatorio];
		if ($obbligatorio) $nome="<b>".$nome."</b>";
		echo "
		<tr bgcolor=$colore>
		<td width=60%>$id_lom_r.$nome</td>";
		if (!$tipocampo) {
			echo "<td align=center>[<a href=profile_index.php?id_lom=$id_lom_r&id_profile=$id_profile>Apri</a>]</td>";
			echo "<td align=center>[<a href=profile_metadato_form.php?id_lom=$id_lom_r&id_profile=$id_profile&tipo_md=gruppo>Modifica</a>]</td>";
			echo "<td align=center>[<a href=profile_metadato_del.php?id_lom=$id_lom_r&id_profile=$id_profile&id_lom_sup=$id_lom>Cancella</a>]</td>";
		} else {
			echo "<td align=center></td>";
			echo "<td align=center>[<a href=profile_metadato_form.php?id_lom=$id_lom_r&id_profile=$id_profile&tipo_md=metadato>Modifica</a>]</td>";
			echo "<td align=center>[<a href=profile_metadato_del.php?id_lom=$id_lom_r&id_profile=$id_profile&id_lom_sup=$id_lom>Cancella</a>]</td>";
		};
		echo "</tr>";
		if ($colore=="$colore_sfondo") {
			$colore="$colore_sfondo_neutro";
		} else {
			$colore="$colore_sfondo";
		};	
	};

};

$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);

$id_profile=$_REQUEST[id_profile];
$id_lom=$_REQUEST[id_lom];

if (!$id_lom) $id_lom=0;

$query="SELECT * FROM profile WHERE id_profile='$id_profile'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$descrizione=htmlentities($riga[descrizione]);

$id_lom_sup=0;
if ($id_lom) {
	$query="SELECT * FROM lo_schema WHERE id_lom='$id_lom' AND id_profile='$id_profile'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$id_lom_sup=$riga[id_lom_sup];
	$nome=$riga[nome];
	$tipocampo=$riga[tipocampo];
	$obbligatorio=$riga[obbligatorio];
	if ($obbligatorio) $nome="<b>".$nome."</b>";
};

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>LOM Application Profile Editor: <?php echo $descrizione ?></title>
	<link rel="stylesheet" href="stile_lom.css.php">

</head>

<body>
<TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
<tr>
<td class=testonegativo height=30 valign=center bgcolor=<?php echo($colore_scuro);?>>
<img src="../ico_lom.gif" width="20" height="20" alt="" align=absMiddle>&nbsp;<b>LOM Application Profile Editor: <?php echo $descrizione ?></b></td></tr>
<tr><td valign=top>

<table border=0 cellpadding=10 width=100%>
<tr><td valign=top>

[<a href=index.php>Indietro</a>]
<hr size=1>
<?php
if ($id_lom) {
	echo "<div class=\"title\">$id_lom.$nome</div>";
	echo "[<a href=profile_index.php?id_lom=$id_lom_sup&id_profile=$id_profile>Su</a>]";
	echo "[<a href=profile_metadato_form.php?id_lom_sup=$id_lom&id_profile=$id_profile&tipo_md=metadato>Nuovo metadato</a>]";
}

echo "[<a href=profile_metadato_form.php?id_lom_sup=$id_lom&id_profile=$id_profile&tipo_md=gruppo>Nuovo gruppo</a>]";

echo "<hr size=1>";

echo "<TABLE cellSpacing=1 cellPadding=5 width=\"100%\" bgColor=#ffffff border=0>";
mostra_lom($id_lom,$id_profile);
echo "</table>";
?>

</td></tr></table>
</td></tr></table>
<br clear="all" />
<hr size=1>
<p align=center>
LOM Editor & Metadata Generator - &copy;2005 - <a href="http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com" target="_blank">Garamond</a>
</p>
</body>
</html>

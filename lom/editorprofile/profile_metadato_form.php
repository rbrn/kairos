<?php
require "./config.php";

$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);

$id_lom=$_REQUEST[id_lom];
$id_lom_sup=$_REQUEST[id_lom_sup];
$id_profile=$_REQUEST[id_profile];

$tipo_md=$_REQUEST[tipo_md];
$azione="nuovo";
$check_obbligatorio="";
$check_langstring="";

if ($id_lom) {
	$query="SELECT * FROM lo_schema WHERE id_profile='$id_profile' AND id_lom='$id_lom'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();

	$id_lom_sup=htmlentities($riga[id_lom_sup]);
	$nome=htmlentities($riga[nome]);
	$size=htmlentities($riga[size]);
	$valuespace=htmlentities($riga[valuespace]);
	$langstring=htmlentities($riga[langstring]);
	$tipocampo=htmlentities($riga[tipocampo]);
	$datetype=htmlentities($riga[datetype]);
	$val_default=htmlentities($riga[val_default]);
	$obbligatorio=htmlentities($riga[obbligatorio]);
	$commento=htmlentities($riga[commento]);
	$source=htmlentities($riga[source]);
	
	if ($obbligatorio) $check_obbligatorio="checked";
	if ($langstring) $check_langstring="checked";
	
	$azione="modifica";
};

$tipocampi=array("stringa","testo","selettore");
$tipocampi_i=array("text","textarea","select");

$elenco_tipocampo="";
for ($i=0;$i<count($tipocampi);$i++) {
	$sel="";
	if ($tipocampo==$tipocampi_i[$i]) $sel="selected";
	$elenco_tipocampo.="<option value=\"$tipocampi_i[$i]\" $sel>$tipocampi[$i]</option>";
};
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>LOM Application Profile Editor: Modifica  <?php echo $azione ?> metadato</title>
	<link rel="stylesheet" href="stile_lom.css.php">

</head>

<body>
<div class="title">LOM Application Profile Editor:  <?php echo $azione ?> metadato</div>
<table border=0 cellpadding=10 width=100%>
<tr><td valign=top>

[<a href=profile_index.php?id_lom=<?php echo $id_lom_sup ?>&id_profile=<?php echo $id_profile ?>>Indietro</a>]
<hr size=1>

<?php
echo "
<form action=\"profile_metadato_op.php\" method=\"post\">
<input type=hidden name=\"azione\" value=\"$azione\">
<input type=hidden name=\"ex_id_lom\" value=\"$id_lom\">
<input type=hidden name=\"id_lom_sup\" value=\"$id_lom_sup\">
<input type=hidden name=\"id_profile\" value=\"$id_profile\">
<input type=hidden name=\"tipo_md\" value=\"$tipo_md\">

<table border=\"0\">";

echo "
<tr>
<td valign=\"top\"><span class=label>ID LOM:</td>
<td valign=\"top\"><input type=\"text\" name=\"id_lom\" size=\"20\" value=\"$id_lom\"></td>
</tr>";


echo "
<tr>
<td valign=\"top\"><span class=label>Denominazione:</span></td>
<td valign=\"top\"><input type=\"text\" name=\"nome\" size=\"70\" value=\"$nome\"></td>
</tr>";

echo "
<tr>
<td valign=\"top\"><span class=label>Size:</span></td>
<td valign=\"top\"><input type=\"text\" name=\"size\" size=\"10\" value=\"$size\"></td>
</tr>";

echo "
<tr>
<td valign=\"top\"><span class=label>Obbligatorio:</span></td>
<td valign=\"top\"><input type=\"checkbox\" name=\"obbligatorio\" $check_obbligatorio></td>
</tr>";

if ($tipo_md=="metadato") {
echo "
<tr>
<td valign=\"top\"><span class=label>ValueSpace:</span></td>
<td valign=\"top\"><textarea name=\"valuespace\" rows=\"8\" cols=\"40\">$valuespace</textarea></td>
</tr>";

echo "
<tr>
<td valign=\"top\"><span class=label>Valore multilingue:</span></td>
<td valign=\"top\"><input type=\"checkbox\" name=\"langstring\" $check_langstring></td>
</tr>";

echo "
<tr>
<td valign=\"top\"><span class=label>Tipo campo:</span></td>
<td valign=\"top\"><select name=\"tipocampo\">$elenco_tipocampo</td>
</tr>";

echo "
<tr>
<td valign=\"top\"><span class=label>Source:</span></td>
<td valign=\"top\"><input type=\"text\" name=\"source\" size=\"30\" value=\"$source\"></td>
</tr>";

};

echo "
<tr>
<td valign=\"top\"><span class=label>Commento:</span></td>
<td valign=\"top\"><textarea name=\"commento\" rows=\"8\" cols=\"40\">$commento</textarea></td>
</tr>";

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

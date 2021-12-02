<?php
$indietro="index.php?risorsa=lo_repository";

$kairos=$_REQUEST["kairos"];
$elenco_lo=$_REQUEST["elenco_lo"];

  
for ($i=0;$i<count($elenco_lo);$i++) {
	$id_lo=$elenco_lo[$i];
	mysql_select_db($kairos);
	$query="SELECT * FROM lo WHERE id_lo='$id_lo'";
	$result=$mysqli->query($query);

	$riga=$result->fetch_array();
		
	$query2="SELECT * FROM risorse_materiali WHERE id_risorsa='$id_lo'";
	$result2=$mysqli->query($query2);
	
	$riga2=$result2->fetch_array();
	if (mysql_error()) echo $query."<br>".mysql_error()."<br>";	
	
	$lo_tipo=$riga["lo_tipo"];
	$lo_tipo_lom=$riga["lo_tipo_lom"];
	$lo_url=$riga["lo_url"];
	$lo_skin=$riga["lo_skin"];
	$width=$riga["width"];
	$height=$riga["height"];
	$scorm_version=$riga["scorm_version"];
	$titolo=addslashes($riga2["titolo"]);
	$materia=addslashes($riga["materia"]);
	$fruitore=addslashes($riga["fruitore"]);
	$obiettivi=addslashes($riga["obiettivi"]);
	$argomenti=addslashes($riga["argomenti"]);
	$profilo_ingresso=addslashes($riga["profilo_ingresso"]);
	
	mysql_select_db($DBASE);
	
	$query="DELETE FROM lo_repository WHERE id_lo='$id_lo'";
	@$mysqli->query($query);
	
	$query="INSERT INTO lo_repository SET"
." id_lo='$id_lo',"
." lo_tipo='1',"
." lo_tipo_lom='$lo_tipo_lom',"
." lo_url='$lo_url',"
." lo_skin='$lo_skin',"
." kairos='$kairos',"
." titolo='$titolo',"
." materia='$materia',"
." fruitore='$fruitore',"
." obiettivi='$obiettivi',"
." argomenti='$argomenti',"
." profilo_ingresso='$profilo_ingresso'";
	@$mysqli->query($query);
	
	if (mysql_error()) echo $query."<br>".mysql_error()."<br>";
};
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>Importa da Repository</td></tr>
";

echo "
<tr>
<td valign=top width=100%>
<a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>";

echo "<span class=\"testo\">Gli LO sono stati importati</span>";
  
?>  
  
</td></tr></table>
<br>

<?php
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");
require "./include/init_sito.inc";

$id_risorsa=$_REQUEST[id_risorsa];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	
	
$query="SELECT * FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$titolo=$riga["titolo"];
$url=$riga["url"];
$id_risorsa0=$riga["risorsa_padre"];

echo "
<html>
<head>
	<title>$titolo</title>
</head>";
?>

<FRAMESET ROWS="220,*" BORDER="0" name="radice" id="radice">
	<FRAME SRC="materiali_testata.php?id_risorsa=<?php echo($id_risorsa);?>" NAME="testata" MARGINWIDTH=0 MARGINHEIGHT=0 SCROLLING="NO" NORESIZE>

	<FRAMESET COLS="*,200" BORDER="0" name="frame1" id="frame1">
		<frame name="contenuto" src="<?php echo($url);?>" marginwidth="0" marginheight="0" scrolling="auto" frameborder="0" noresize>

		<frame name="menu_sezioni" src="materiali_indice.php?id_risorsa=<?php echo($id_risorsa);?>" marginwidth="0" marginheight="0" scrolling="auto" frameborder="0" noresize>
		
		
	</FRAMESET>

</FRAMESET>
</html>


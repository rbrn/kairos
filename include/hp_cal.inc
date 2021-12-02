<?php

$query = "SELECT * FROM calendario WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND DATE_ADD(data,interval 10 day)>=curdate() AND DATE_SUB(data,interval 10 day)<=curdate() ORDER BY data ";
$result=$mysqli->query($query);
//echo mysql_error()." $query <br>";
$eventi=array();
while ($riga=$result->fetch_array()) {
	$data0=$riga[data];
	ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data0,$parti);
	$data=$parti[3]."/".$parti[2]."/".$parti[1];
	$oggetto=$riga[oggetto];
	$data_oggi0 = getdate();
	$data_oggi=substr("0".$data_oggi0["mday"],-2)."/".substr("0".$data_oggi0["mon"],-2)."/".$data_oggi0["year"];
	
	if ($data_oggi==$data) {
		$eventi[]="<b>$data: $oggetto</b>";
	} else {
		$eventi[]="$data: $oggetto";
	};
};



if (count($eventi)) {
	echo "
	<table border=0 width=100% cellspacing=3 cellpadding=3>
	<tr><td valign=\"top\" class=titolodot><img src=\"img/ico_home_cal.gif\" width=\"25\" height=\"20\" alt=\"\" border=\"0\" align=\"bottom\">$stringa[news_eventi]</td></tr>";

	for ($i=0;$i<count($eventi);$i++) {
		echo "<tr><td><span class=\"testopiccolo\">".stripslashes($eventi[$i])."</span></td></tr>";
	};

	echo "</table>";
};


?>

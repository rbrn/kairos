<?php

if (($ruolo=='staff' or $ruolo=='admin' or $cod_area=="kairos_masterunitus") and $id_corso_s) {
	if ($gruppi) {
		$cond_gruppo=$gruppi;
	} else {
		$cond_gruppo=1;
	};
	if ($cod_area=="kairos_masterunitus") $cond_gruppo=1;
} else {
	$cond_gruppo="id_gruppo='$id_gruppo_s'";
};

$query = "SELECT * FROM lab_materiali WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo<>2 AND ($cond_gruppo) AND DATE_ADD(data_crea,interval 11 day)>=curdate() ORDER BY data_crea DESC ";


$result=$mysqli->query($query);
//echo mysql_error()." $query <br>";
$materiali=array();
$id_utente=$kairos_cookie[0];
while ($riga=$result->fetch_array()) {
	$data0=$riga[data_crea];
	ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$data0,$parti);
	$data=$parti[3]."/".$parti[2]."/".$parti[1];
	$utente=$riga[id_autore];
	$titolo=$riga[titolo];
	$id_risorsa=$riga[id_risorsa];
	$query2="SELECT * FROM log_lab_materiali WHERE id_risorsa='$id_risorsa' AND id_utente='$id_utente' LIMIT 1";
	$result2=$mysqli->query($query2);
	
	if ($result2->num_rows) {
		$flag="";
	} else {
		$flag="<i><b>$stringa[nuovo]</b></i>";
	};
	
	$materiali[]="
	<a style=\"cursor:hand;text-decoration:underline\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$utente',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$utente</a>:&nbsp;<a href=index.php?risorsa=lab_materiali_view&id_risorsa=$id_risorsa>$titolo</a> ($data)&nbsp;$flag";
};



if (count($materiali)) {
	echo "
	<table border=0 width=100% cellspacing=3 cellpadding=3>
	<tr><td valign=\"top\" class=titolodot><img src=\"img/ico_home_materiali.gif\" width=\"25\" height=\"20\" alt=\"\" border=\"0\" align=\"bottom\">$stringa[news_portfolio]</td></tr>";

	for ($i=0;$i<count($materiali);$i++) {
		echo "<tr><td><span class=\"testopiccolo\">$materiali[$i]</span></td></tr>";
	};
	
	echo "</table>";
};


?>

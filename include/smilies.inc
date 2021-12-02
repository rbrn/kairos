<?php
$M = ereg_replace(":\)", " <IMG SRC=\"images/smilies/smile1.gif\" WIDTH=15 HEIGHT=15 ALT=\":)\"> ", $M);
$M = ereg_replace(":D", " <IMG SRC=\"images/smilies/smile2.gif\" WIDTH=15 HEIGHT=15 ALT=\":D\"> ", $M);
$M = ereg_replace(":o", " <IMG SRC=\"images/smilies/smile3.gif\" WIDTH=15 HEIGHT=15 ALT=\":o\"> ", $M);
$M = ereg_replace(":\(", " <IMG SRC=\"images/smilies/smile4.gif\" WIDTH=15 HEIGHT=15 ALT=\":(\"> ", $M);
$M = ereg_replace(";\)", " <IMG SRC=\"images/smilies/smile5.gif\" WIDTH=15 HEIGHT=15 ALT=\";)\"> ", $M);
$M = ereg_replace(":p", " <IMG SRC=\"images/smilies/smile6.gif\" WIDTH=15 HEIGHT=15 ALT=\":p\"> ", $M);
$M = ereg_replace("8\)", " <IMG SRC=\"images/smilies/smile7.gif\" WIDTH=15 HEIGHT=15 ALT=\"8)\"> ", $M);
$M = ereg_replace(":\[", " <IMG SRC=\"images/smilies/smile8.gif\" WIDTH=15 HEIGHT=15 ALT=\":[\"> ", $M);
$M = ereg_replace(":kill:", "<IMG SRC=\"images/smilies/smile9.gif\" WIDTH=50 HEIGHT=15 ALT=\":kill:\">", $M);


//vedo se ci sono immagini...
$dir_path=$PATH_ROOT_FILE."/images/$cod_area";
$d = dir($dir_path);
$i=0;
while ($nomefile=$d->read()) {
	if (($nomefile != '.') && ($nomefile != '..')) { 
		$file_img[$i] = strtolower($nomefile);
		$i++;
	};
}

$d->close();
if (count($file_img)) {
	while (list($key, $val) = each($file_img)) {
		if (ereg("^(.+)\.(.+)$",$val,$parte)) {
		
			$M = ereg_replace("\*$parte[1]\*", "<img src=\"images/$cod_area/$val\" alt=\"$parte[1]\">", $M);
		};
	};
};

//vedo se ci sono squadre di calcio...
$squadre = array ("genoa","inter","juve","lazio","bari","roma","milan","napoli");
$colori["genoa"][0]="#ff0000";
$colori["genoa"][1]="#0000ff";

$colori["inter"][0]="#000000";
$colori["inter"][1]="#0000ff";

$colori["juve"][0]="#ffffff";
$colori["juve"][1]="#000000";

$colori["lazio"][0]="#ffffff";
$colori["lazio"][1]="#99ffff";

$colori["napoli"][0]="#99ffff";
$colori["napoli"][1]="#99ffff";

$colori["bari"][0]="#ffffff";
$colori["bari"][1]="#ff0000";

$colori["roma"][0]="#ffff00";
$colori["roma"][1]="#ff0000";

$colori["milan"][0]="#ff0000";
$colori["milan"][1]="#000000";

$trovato=false;
$trovato=false;
while ( list($key, $sq) = each($squadre) and !$trovato) {

	$squadra="*".$sq."*";
	$i = strpos($M,$squadra);

	if ($i) {
		$trovato = true;
		
		$inizio = substr($M,0,$i);
		$fine = substr($M,-(strlen($M)-$i-strlen($squadra)));

		$testo="";
		$j=0;
		$icol = 0;
		$continua=true;
		while ($j<strlen($fine) and $continua) {
			$car = substr($fine,$j,1);
			if ($car=='<') {
				$testo .= $car;
				while ($car!='>' and $j<strlen($fine)) {
					$j++;
					$car = substr($fine,$j,1);
					$testo .= $car;
				};
		
				if ($j>=strlen($fine)) {
					$continua=false;
				} else {
					//$testo .= $car;
					$j++;
					if ($j<strlen($fine)) {
						$car = substr($fine,$j,1);
					} else {
						$continua=false;
					};
				};
			};

			if ($continua) {
				if ($car != '<') {
					$col = $colori[$sq][$icol];
					$testo .= "<font color=$col>$car</font>";
					if ($icol==0) {
						$icol=1;
					} else {
						$icol=0;
					};
					$j++;
				};
			};	

		};
	};
};

if ($trovato) {
	$M = $inizio.$testo;
};	


?>

<?php
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$risorsa=$_REQUEST[id_risorsa];

$dati_nodo=dati_nodo($risorsa);
		
$id_corso_s=$dati_nodo[id_corso];
$id_edizione_s=$dati_nodo[id_edizione];
$descr_gruppo=$dati_nodo[descr_gruppo];
$titolo=$dati_nodo[titolo];

$id_modulo=$dati_nodo[id_modulo];

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query="SELECT tipo,id_autore,risorsa_padre FROM materiali_gruppo WHERE id_risorsa='$risorsa'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$tipo=$riga["tipo"];
$id_autore=$riga["id_autore"];
$risorsa_superiore=$riga["risorsa_padre"];

echo "
<html>
<head>
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>";


echo "
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
</head>
";

echo "
<body topmargin=\"0\" leftmargin=\"15\" bgcolor=\"#FFFFFF\" link=\"$colore_link\" vlink=\"$colore_link\" >";

		
		echo "<table border=0 bgcolor=\"white\" width=100%>";
		echo "<tr><td valign=top bgcolor=$colore_sfondo_neutro width=200 cellpadding=3>";
		
		$target=" target=\"_top\" ";
		capitolo_gruppo($id_modulo,$risorsa,"true",$target);
		
		$query_f="SELECT * FROM materiali_gruppo WHERE risorsa_padre='$risorsa_superiore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo=1 ORDER BY posizione,id_risorsa";
		$result_f=$mysqli->query($query_f);
		
		if ($result_f->num_rows) {
			echo "
			<hr size=1>
			<ul style=\"list-style-type:none\">
			<li><span class=testopiccolo><b>$stringa[download]:</b></span><br>
			";
			while ($riga_f=$result_f->fetch_array()) {
				$id_file=$riga_f["id_risorsa"];
				$file_size=$riga_f["file_size"];
				$titolo_f=$riga_f["titolo"];
				$descrizione_f=$riga_f["descrizione"];
				echo "
				<span class=testopiccolo><a href=\"materiali_gruppo_browse.php?risorsa=$id_file\"  alt=\"$descrizione_f\">$titolo_f</a><br>(".stringa_filesize($file_size).")<br>$descrizione_f</span>
				<br><br>";
			};
			echo "</li></ul>";
		};
		
		
		echo "</td>";
		
		echo "</tr>
		</table>";
		
echo "</body>";
echo "</html>";

?>


<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);			

$materiali_attesa=$_REQUEST["materiali_attesa"];
$materiali_pubblicati=$_REQUEST["materiali_pubblicati"];
$aggiungi=$_REQUEST["aggiungi"];
$rimuovi=$_REQUEST["rimuovi"];	
$comuni=$_REQUEST["comuni"];	
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];
$titolo_cerca=mysql_real_escape_string($_REQUEST["titolo_cerca"]);
$id_autore_cerca=mysql_real_escape_string($_REQUEST["id_autore_cerca"]);
$id_gruppo_cerca=mysql_real_escape_string($_REQUEST["id_gruppo_cerca"]);

if ($comuni=="1") {
	$id_corso_s='';
	$id_edizione_s='';
	$id_gruppo_s='';
	$query = "SELECT * FROM materiali_sequenza WHERE id_corso='' ORDER BY ordine";
} else {
	$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_cerca' ORDER BY ordine";
};

$result=$mysqli->query($query);

$materiali_pubblicati_db=array();
$n=count($materiali_pubblicati);
while ($risorsa = $result->fetch_array() ) {
	$id_risorsa=$risorsa["id_risorsa"];
	$cancella=false;
	for ($i=0;$i<$n;$i++) {
		$risorsa0=$materiali_pubblicati[$i];
		ereg("^(.+)-(.+)$",$risorsa0,$parte);
		$id_risorsa0=$parte[2];
		
		if ($id_risorsa==$id_risorsa0) {
			$cancella=true;
			break;
		};
	};
	$materiali_pubblicati_db[$id_risorsa] = $cancella;
};

if ($aggiungi) {
	$n = count($materiali_attesa);
	$ordine = count($materiali_pubblicati_db);
	for ($i=0;$i<$n;$i++) {
		$ordine=$ordine+$i;
		$risorsa=$materiali_attesa[$i];
		ereg("^(.+)-(.+)$",$risorsa,$parte);
		$tiporisorsa=$parte[1];
		$id_risorsa=$parte[2];
		switch ($tiporisorsa) {
			case "web":
				$tipo_risorsa=0;
				break;
			case "link":
				$tipo_risorsa=4;
				break;	
			case "file":
				$tipo_risorsa=1;
				break;
			case "cartella":
				$tipo_risorsa=2;
				break;
			case "test":
				$tipo_risorsa=3;
				break;
		};
		$query="INSERT INTO materiali_sequenza (id_risorsa,tipo_risorsa,ordine,id_corso,id_edizione,id_gruppo) VALUES ('$id_risorsa','$tipo_risorsa','$ordine','$id_corso_s','$id_edizione_s','$id_gruppo_cerca')";
		
		$result=$mysqli->query($query);
		
	};
	
} else {
	/*
	reset($materiali_pubblicati_db);
	while (list($key,$value)=each($materiali_pubblicati_db)) {
		echo "$key : $value <br>";
	};
	echo "<hr size=1>";
	reset($materiali_pubblicati);
	while (list($key,$value)=each($materiali_pubblicati)) {
		echo "$key : $value <br>";
	};
	*/
	if ($comuni=='1') {
		$query = "SELECT * FROM materiali_sequenza WHERE id_corso='' ORDER BY ordine";
	} else {
		$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_cerca' ORDER BY ordine";
	};
	$result=$mysqli->query($query);
	$ordine=0;
	while ($riga=$result->fetch_array()) {
		$id_risorsa=$riga["id_risorsa"];
		$cancella=$materiali_pubblicati_db[$id_risorsa];
		
		if ($cancella) {
			if ($comuni=='1') {
				$query2="DELETE FROM materiali_sequenza WHERE id_risorsa='$id_risorsa' AND id_corso=''";
			} else {
				$query2="DELETE FROM materiali_sequenza WHERE id_risorsa='$id_risorsa' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_cerca'";
			};
		} else {
			if ($comuni=='1') {
				$query2="UPDATE materiali_sequenza SET ordine='$ordine' WHERE id_risorsa='$id_risorsa' AND id_corso=''";
			} else {
				$query2="UPDATE materiali_sequenza SET ordine='$ordine' WHERE id_risorsa='$id_risorsa' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_cerca'";
			};
			$ordine++;
		};
		$result2=$mysqli->query($query2);
	};
	
};		

header("Location:index.php?risorsa=materiali_sequenza_edit&comuni=$comuni&id_corso=$id_corso_s&id_edizione=$id_edizione_s&titolo_cerca=$titolo_cerca&id_autore_cerca=$id_autore_cerca&id_gruppo_cerca=$id_gruppo_cerca");
?>

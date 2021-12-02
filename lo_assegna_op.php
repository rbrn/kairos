<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);			

$materiali_attesa=$_REQUEST["materiali_attesa"];
$materiali_pubblicati=$_REQUEST["materiali_pubblicati"];
$aggiungi=$_REQUEST["aggiungi"];
$rimuovi=$_REQUEST["rimuovi"];	
$id_corso_s=$_REQUEST["id_corso"];
$id_edizione_s=$_REQUEST["id_edizione"];
$titolo_cerca=trim($_REQUEST["titolo_cerca"]);
$id_autore_cerca=trim($_REQUEST["id_autore_cerca"]);
$lo_tipo_lom_cerca=trim($_REQUEST["lo_tipo_lom_cerca"]);
$materia_cerca=trim($_REQUEST["materia_cerca"]);
$id_gruppo_cerca=$_REQUEST["id_gruppo_cerca"];

$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_cerca' AND tipo_risorsa='20' ORDER BY ordine";


if(!$result = $mysqli->query($query)) die($mysqli->error);

$materiali_pubblicati_db=array();
$n=count($materiali_pubblicati);
while ($risorsa = $result->fetch_array()) {
	$id_risorsa=$risorsa["id_risorsa"];
	$cancella=false;
	for ($i=0;$i<$n;$i++) {
		$id_risorsa0=$materiali_pubblicati[$i];
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
		$id_risorsa=$materiali_attesa[$i];
		$query="INSERT INTO materiali_sequenza (id_risorsa,tipo_risorsa,ordine,id_corso,id_edizione,id_gruppo) VALUES ('$id_risorsa','20','$ordine','$id_corso_s','$id_edizione_s','$id_gruppo_cerca')";

        if(!$result = $mysqli->query($query)) die($mysqli->error);
		
	};
	
} else {
	$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_cerca' AND tipo_risorsa='20' ORDER BY ordine";

    if(!$result = $mysqli->query($query)) die($mysqli->error);
	$ordine=0;
	while ($riga=$result->fetch_array()) {
		$id_risorsa=$riga["id_risorsa"];
		$cancella=$materiali_pubblicati_db[$id_risorsa];
		
		if ($cancella) {
			$query2="DELETE FROM materiali_sequenza WHERE id_risorsa='$id_risorsa'";
		} else {
			$query2="UPDATE materiali_sequenza SET ordine='$ordine' WHERE id_risorsa='$id_risorsa'";
			$ordine++;
		};

       $mysqli->query($query2);
	};
	
};		

header("Location:index.php?risorsa=lo_assegna&id_corso=$id_corso_s&id_edizione=$id_edizione_s&titolo_cerca=$titolo_cerca&id_autore_cerca=$id_autore_cerca&lo_tipo_lom_cerca=$lo_tipo_lom_cerca&materia_cerca=$materia_cerca&id_gruppo_cerca=$id_gruppo_cerca");
?>

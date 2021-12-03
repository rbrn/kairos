<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_pagina=trim($_REQUEST["id_pagina"]);
$posizione_int=$_REQUEST["posizione_int"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

$query="DELETE FROM lo_pagina_asset WHERE id_pagina='$id_pagina' AND tipo_asset='2' AND posizione_int='$posizione_int'";
$mysqli->query($query);

$query="SELECT * FROM lo_pagina_asset WHERE id_pagina='$id_pagina' AND tipo_asset='2' ORDER BY posizione_int";
$result=$mysqli->query($query);
$posizione_int=1;
while ($riga=$result->fetch_array()) {
	$id_pagina_asset=$riga["id_pagina_asset"];
		
	$query="UPDATE lo_pagina_asset SET ".
			" posizione_int='$posizione_int'".
			" WHERE id_pagina_asset='$id_pagina_asset'";
			
	$mysqli->query($query);
	$posizione_int++;
};		

Header("Location:index.php?risorsa=lo_pagina_asset_edit&id_pagina=$id_pagina&id_cartella=$risorsa_padre");		
?>

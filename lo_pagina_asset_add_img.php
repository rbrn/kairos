<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_pagina=trim($_REQUEST["id_pagina"]);
$posizione=$_REQUEST["posizione"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

$query="SELECT max(posizione_int) AS  max_pos FROM lo_pagina_asset WHERE id_pagina='$id_pagina' AND tipo_asset='2'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$posizione_int=$riga["max_pos"]+1;

$query="INSERT INTO lo_pagina_asset SET ".
			" id_pagina='$id_pagina',".
			" tipo_asset='2',".
			" file_asset='',".
			" alt_text='',".
			" posizione='$posizione',".
			" posizione_int='$posizione_int',".
			" id_editor='$kairos_cookie[0]'";
$mysqli->query($query);
			
		

Header("Location:index.php?risorsa=lo_pagina_asset_edit&id_pagina=$id_pagina&risorsa_padre=$risorsa_padre");		
?>

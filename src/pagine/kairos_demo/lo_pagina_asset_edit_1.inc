<?php

$query="SELECT * FROM lo_pagina_asset WHERE tipo_asset='1' AND id_pagina='$id_pagina'";
$result=$mysqli->query($query);

$riga=$result->fetch_array();
$id_pagina_asset=0;
if ($riga) {
	$id_pagina_asset=$riga["id_pagina_asset"];
};

$file_asset=$PATH_ROOT_FILE."materiali/$cod_area/asset_".$id_pagina."_".$id_pagina_asset.".inc";
if (file_exists($file_asset)) {
    $testo = file_get_contents($file_asset);
	$testo=htmlentities($testo);

} else {
	$testo="";
};

?>
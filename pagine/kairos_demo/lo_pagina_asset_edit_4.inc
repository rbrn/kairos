<?php

$query="SELECT * FROM lo_pagina_asset WHERE tipo_asset='4' AND id_pagina='$id_pagina'";
$result=$mysqli->query($query);

$riga=$result->fetch_array();
$id_pagina_asset=0;
$file_flash="";
if ($riga) {
	$id_pagina_asset=$riga["id_pagina_asset"];
	$file_flash=$riga["file_asset"];
	$f_w=$riga[width];
	$f_h=$riga[height];
	$alt_text=htmlentities($riga["alt_text"]);
	$alt_img=$riga["alt_img"];
};

?>

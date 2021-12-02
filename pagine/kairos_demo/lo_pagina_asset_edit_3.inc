<?php

$query="SELECT * FROM lo_pagina_asset WHERE tipo_asset='3' AND id_pagina='$id_pagina'";
$result=$mysqli->query($query);

$riga=$result->fetch_array();
$id_pagina_asset=0;
$file_video="";
if ($riga) {
	$id_pagina_asset=$riga["id_pagina_asset"];
	$file_video=$riga["file_asset"];
	$alt_text=htmlentities($riga["alt_text"]);
	$alt_img=$riga["alt_img"];
};

?>

<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_pagina=trim($_REQUEST["id_pagina"]);
$id_item=trim($_REQUEST["id_item"]);
$risorsa_padre=trim($_REQUEST["risorsa_padre"]);
$file_asset=trim($_REQUEST["file_flash"]);
$alt_text=trim($_REQUEST["alt_text"]);
$alt_img=trim($_REQUEST["alt_img"]);
$soluzione=trim($_REQUEST["soluzione"]);
$soluzione=str_replace("\n","",$soluzione);
$soluzione=str_replace("\r","",$soluzione);

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_utente = $kairos_cookie["0"];

$query="SELECT * FROM lo_pagina_asset WHERE id_pagina='$id_pagina'";
$result=$mysqli->query($query);

if (!$result->num_rows) {
	$query="INSERT INTO lo_pagina_asset SET ".
	" id_pagina='$id_pagina',".
	" file_asset='$file_asset',".
	" alt_text='$alt_text',".
	" alt_img='$alt_img',".
	" soluzione='$soluzione',".
	" id_editor='$id_utente'";
	$mysqli->query($query);
} else {
	$riga=$result->fetch_array();
	$id_pagina_asset=$riga["id_pagina_asset"];
	$query="UPDATE lo_pagina_asset SET ".
	" alt_text='$alt_text',".
	" alt_img='$alt_img',".
	" soluzione='$soluzione',".
	" file_asset='$file_asset'".
	" WHERE id_pagina_asset='$id_pagina_asset'";
	$mysqli->query($query);
};


Header("Location:index.php?risorsa=repository_index&id_cartella=$risorsa_padre");		
?>

<?php
$id_risorsa=$_REQUEST["id_risorsa"];
$tipo=$_REQUEST["tipo"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

switch($tipo) {
	case 0:
		$prompt=$stringa[conf_cancella_pagina];
		break;

	case 1:
		$prompt=$stringa[conf_cancella_file];
		break;		
		
	case 2:
		$prompt=$stringa[conf_cancella_cartella];
		break;		
};
echo "
<p>
<span class=testo>$id_risorsa: $prompt [<a href=risorsa_del_ok.php?id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$risorsa_padre>$stringa[si]</a>] [<a href=index.php?risorsa=admin_index&id_cartella=$risorsa_padre>$stringa[no]</a>]</span>
</p>
<br>";
?>

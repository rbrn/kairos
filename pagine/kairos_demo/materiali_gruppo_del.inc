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
	
	case 3:
		$prompt=$stringa[conf_cancella_nota];
		break;
			
	case 4:
		$prompt=$stringa[conf_cancella_link];
		break;	
};
echo "
<table border=0 cellpadding=5 cellspacing=5>
<tr><td>
<p>
<span class=testo>$prompt [<a href=materiali_gruppo_del_ok.php?id_risorsa=$id_risorsa&tipo=$tipo&risorsa_padre=$risorsa_padre>$stringa[si]</a>] [<a href=index.php?risorsa=materiali_gruppo_index&id_cartella=$risorsa_padre>$stringa[no]</a>]</span>
</p>
</td></tr>
</table>
<br>";
?>

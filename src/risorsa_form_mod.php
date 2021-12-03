<?php 
$id_risorsa=$_REQUEST["id_risorsa"];
$tipo=$_REQUEST["tipo"];

switch ($tipo) {
	case 0:
		Header("Location:index.php?risorsa=web_form_mod&id_risorsa=$id_risorsa");
		break;

	case 1:
		Header("Location:index.php?risorsa=file_form_mod&id_risorsa=$id_risorsa");
		break;
	case 2:		
		Header("Location:index.php?risorsa=folder_form_mod&id_risorsa=$id_risorsa");
		break;
};
?>

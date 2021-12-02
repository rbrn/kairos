<?php 
$id_risorsa=$_REQUEST["id_risorsa"];
$tipo=$_REQUEST["tipo"];
$padre=$_REQUEST["padre"];
switch ($tipo) {
	case 20:		
		Header("Location:index.php?risorsa=lo_folder_form_mod&id_risorsa=$id_risorsa");
		break;
	
	case 22:		
		Header("Location:index.php?risorsa=lo_sco_form_mod&id_risorsa=$id_risorsa");
		break;
		
	case 200:		
		Header("Location:index.php?risorsa=lo_pagina_mod&id_risorsa=$id_risorsa");
		break;
	
	case 201:		
		Header("Location:index.php?risorsa=lo_test_item_mod&id_risorsa=$id_risorsa&risorsa_padre=$padre");
		break;
};
?>

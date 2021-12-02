<?php 
$padre=$_REQUEST["padre"];
$tipo=$_REQUEST["tipo"];

switch ($tipo) {
	case 20:		
		Header("Location:index.php?risorsa=lo_folder_form_add&padre=$padre");
		break;
		
	case 200:
		Header("Location:index.php?risorsa=lo_pagina_add&padre=$padre");
		break;			

	case 201:		
		Header("Location:index.php?risorsa=lo_test_item_add&padre=$padre&risorsa_padre=$padre");
		break;
};
?>

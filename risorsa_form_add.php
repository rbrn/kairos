<?php 
$padre=$_REQUEST["padre"];
$tipo=$_REQUEST["tipo"];

switch ($tipo) {
	case 0:
		Header("Location:index.php?risorsa=web_form_add&padre=$padre");
		break;			
	case 1:
		Header("Location:index.php?risorsa=file_form_add&padre=$padre");
		break;
	case 2:		
		Header("Location:index.php?risorsa=folder_form_add&padre=$padre");
		break;
};
?>

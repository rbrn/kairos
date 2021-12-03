<?php 
$padre=$_REQUEST["padre"];
$tipo=$_REQUEST["tipo"];

switch ($tipo) {
	case 0:
		Header("Location:index.php?risorsa=lab_materiali_web_form_add&padre=$padre");
		break;			
	case 1:
		Header("Location:index.php?risorsa=lab_materiali_file_form_add&padre=$padre");
		break;
	case 2:		
		Header("Location:index.php?risorsa=lab_materiali_folder_form_add&padre=$padre");
		break;
};
?>

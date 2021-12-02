<?php

$nome=trim($_GET["nome"]);

$im = imagecreatefrompng("fondino.png");

$fontsize=11;
$fontangle=90;


$text_nome=$nome;

//$font = "FreeSerifBoldItalic.ttf";
$font = "./TSCu_Comic.ttf";

$imgcoord=imagettfbbox ( $fontsize, $fontangle, $font, $text_nome );
$dimX=abs($imgcoord[4]-$imgcoord[2]);
$dimY=abs($imgcoord[7]-$imgcoord[5]);
$partdaX=15+$dimX+intval((20.5-$dimX)/2);
$partdaY=$dimY+intval((238-$dimY)/2);

$text_lic = "LEARNING OBJECT DI";
$imgcoord_lic=imagettfbbox ($fontsize, $fontangle, $font, $text_lic );
$dim_lic_X=abs($imgcoord_lic[4]-$imgcoord_lic[2]);
$dim_lic_Y=abs($imgcoord_lic[7]-$imgcoord_lic[5]);
$partda_lic_X=$dim_lic_X+intval((20.5-$dim_lic_X)/2);
$partda_lic_Y=$dim_lic_Y+intval((238-$dim_lic_Y)/2);

$black = imagecolorallocate($im, 0, 0, 0);

imagettftext($im, $fontsize, $fontangle, $partda_lic_X, $partda_lic_Y, $black, $font, $text_lic);
imagettftext($im, $fontsize, $fontangle, $partdaX, $partdaY, $black, $font, $text_nome);

header("Content-type: image/png");
imagepng($im);

imagedestroy($im);

?> 

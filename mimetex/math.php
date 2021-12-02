<?php
function genera_formula($formula) {

$texvc="/var/www/html/prototipo/kairos/formule/texvc";
$tmpDir="/var/www/html/prototipo/kairos/formule/tmp";
$imgDir="/var/www/html/prototipo/kairos/formule";

$tex="\"$formula\"";

$cmd = 	$texvc.' '.
		$tmpDir.' '.
		$imgDir.' '.
		$tex.' iso-8859-1';
			
$contents = shell_exec($cmd);

if (strlen($contents) == 0) {
	die("errore in conversione formula");
};
			
$retval = substr ($contents, 0, 1);
if (($retval == 'C') || ($retval == 'M') || ($retval == 'L')) {
	if ($retval == 'C')
		$conservativeness = 2;
	else if ($retval == 'M')
		$conservativeness = 1;
	else
		$conservativeness = 0;

	$outdata = substr ($contents, 33);
		
	$i = strpos($outdata, "\000");
		
	$html = substr($outdata, 0, $i);
	$mathml = substr($outdata, $i+1);
} else if (($retval == 'c') || ($retval == 'm') || ($retval == 'l'))  {
	$html = substr ($contents, 33);

	if ($retval == 'c')
		$conservativeness = 2;
	else if ($retval == 'm')
		$conservativeness = 1;
	else
		$conservativeness = 0;

	$mathml = NULL;

} else if ($retval == 'X') {
	$html = NULL;
	$mathml = substr ($contents, 33);
	$conservativeness = 0;

} else if ($retval == '+') {
	$html = NULL;
	$mathml = NULL;
	$conservativeness = 0;

} else {
	$errbit = htmlspecialchars( substr($contents, 1) );

	switch( $retval ) {
			case 'E': die( 'math_lexing_error'. $errbit );
			case 'S': die( 'math_syntax_error'. $errbit );
			case 'F': die( 'math_unknown_function'. $errbit );
			default:  die( 'math_unknown_error'.$errbit );
	}
}


$hash = substr ($contents, 1, 32);

if (!preg_match("/^[a-f0-9]{32}$/", $hash)) {
	die( 'math_unknown_error' );
}
		
if ( !file_exists( "$imgDir/{$hash}.png" )) {
	die ('math_image_error' );
};

return ($hash);
};

$formula=$_REQUEST["formula"];
$immagine=genera_formula($formula);
echo "<img src=\"../formule/{$immagine}.png\">";		

?>

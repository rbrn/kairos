<?php
require "./init_sito.inc";
$cartella=$_REQUEST["cartella"];

reset($HTTP_POST_VARS);

list($key, $cartella) = each($HTTP_POST_VARS);
list($key, $val) = each($HTTP_POST_VARS);

if ($cartella) {
	$path_file=$PATH_ROOT_FILE.$cartella."/".$val;
} else {
	$path_file=$PATH_ROOT_FILE.$val;
};
	

if (is_dir($path_file))	{
	Header("Location:apri.php?cartella=$cartella");
	exit();
} else {
	if (file_exists($path_file)) {
		$est = substr($val,-3);
		$nome=substr($val,0,strlen($val)-4);
		//echo "$val - $est - $nome <br>";
		if ($est=="htm") {
			$nome=substr($val,0,strlen($val)-4);
			$file_htm=join('',file($path_file));
			//$file_htm=join('',file("./istruzioni.htm"));
			//eregi("^.*<TITLE>(.*)</TITLE>(.*)<BODY([^>]*)>(.*)</BODY>.*$",$file_htm,$parti);
			$titolo=$parti[1];
			$contenuto=$parti[4];		
			$cod_area=$kairos_cookie[4];
			if (!$contenuto) {
				$titolo="senza titolo";
				$contenuto=$file_htm;
			};
			/*
			echo "
			$path_file <br>
			<hr size=1>".
			htmlentities($file_htm)
			."<br>nome: $nome <br>
			titolo: $titolo <br>
			<hr size=1>
			contenuto: ".
			htmlentities($contenuto);
			*/	$file_contenuto="/var/www/html/prototipo/kairos/".$cod_area."_".$id_corso_s."_laboratorio.txt";
			$fd=fopen ($file_contenuto,"w");
			fwrite($fd,$contenuto);
			fclose($fd);
			setcookie("kairos_cookie[5]",$cartella,0,"/",$dominio);
			setcookie("kairos_cookie[6]",$nome,0,"/",$dominio);
			setcookie("kairos_cookie[7]",$titolo,0,"/",$dominio);
			Header("Location:../atlante_editor.php");
			exit();
		};
	};
};
Header("Location:apri.php?cartella=$cartella");
?>




<?php
require "./include/init_sito.inc";
reset($HTTP_POST_VARS);

list($key, $cartella) = each($HTTP_POST_VARS);
list($key, $tipo_file) = each($HTTP_POST_VARS);
list($key, $dir) = each($HTTP_POST_VARS);

while (list($key, $val) = each($HTTP_POST_VARS)) {
	$path_file=$PATH_ROOT_FILE."materiali_img/$cod_area/$dir/".$cartella."/".$key;
	if (is_dir($path_file))	{
		$i=0;
		$d = dir($path_file);
		while ($filename=$d->read()) {
			if (($filename != '.') && ($filename != '..')) { 
				$i++;
			};

		};
		$d->close();
		if (!$i) {
			rmdir($path_file);
		};
	} else {
		if (substr($path_file,-4,1)=="_") {
			$path_file=substr($path_file,0,strlen($path_file)-4).".".substr($path_file,-3,3);
		};
		unlink($path_file);
	};
	
	
};
Header("Location:index.php?risorsa=materiali_cartella&tipo=$tipo_file&cartella=$cartella&dir=$dir");	
?>

<?php
require "./init_sito.inc";
$cartella=$_REQUEST["cartella"];

reset($HTTP_POST_VARS);

list($key, $cartella) = each($HTTP_POST_VARS);
while (list($key, $val) = each($HTTP_POST_VARS)) {
	if ($cartella) {
		$path_file=$PATH_ROOT_FILE.$cartella."/".$val;
	} else {
		$path_file=$PATH_ROOT_FILE.$val;
	};
	

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
		if (file_exists($path_file)) {		
			unlink($path_file);
		};
	};

	
};
Header("Location:index.php?cartella=$cartella");
?>

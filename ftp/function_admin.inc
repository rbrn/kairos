<?php
function stringa_filesize($filesize) {
	$type = Array ('Bytes', 'KB', 'MB', 'GB');

    for ($i = 0; $filesize > 1024; $i++)
        $filesize /= 1024;

    return round ($filesize, 2)." $type[$i]"; 
};

function browse_folder($cartella) {
	global $PATH_ROOT,$PATH_ROOT_FILE,$stringa;
	
	$dir_path=$PATH_ROOT_FILE.$cartella;

	if ($cartella) {
		$padre=dirname($cartella);
		echo "
		[<a href=index.php?cartella=$padre>$stringa[dir_superiore]</a>]<br><hr>";
	};

	echo "<h1>".$cartella."</h1>";
	$i=0;
	$d = dir($dir_path);
	while ($filename=$d->read()) {
		if (($filename != '.') && ($filename != '..')) { 
			$entry[$i]=$filename;
			$i++;
		};

	};
	$d->close();
	if ($i) {
		sort($entry);
	};
	for ($j=0;$j<$i;$j++){ 
		$filename=$entry[$j];
		$path_file=$PATH_ROOT_FILE.$cartella."/".$filename;
		$index=$j+1;
		echo "
		<input type=checkbox name=\"$filename\" value=\"$filename\"> ";
		$date=date("d/m/y H:m:s", filemtime($path_file));
		if (is_dir($path_file)) {
			echo "<font face=verdana size=-1>
				<img src=img/folder.gif width=18 height=16 border=0> <a href=index.php?cartella=$cartella"."/".$filename.">$filename</a> ($date)</font><br>";
		} else {
			$size=stringa_filesize(filesize($path_file));
			echo "<font face=verdana size=-1>
			<a href=".$PATH_ROOT.$cartella."/"."$filename>$filename</a> ($size - $date)</font><br>\n";
		};
	
	};
};
?>

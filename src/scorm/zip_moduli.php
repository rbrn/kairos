<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>Untitled</title>
</head>

<body>

<?php

$cur_dir=getcwd();
chdir("/var/www/html/prototipo/kairos");
			
$comando="/usr/bin/zip -r moduli.zip moduli";
exec($comando);

chdir($cur_dir);
			
?>

</body>
</html>

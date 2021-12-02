<?php
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");
require "./include/init_sito.inc";
$semaforo=$PATH_ROOT_FILE.$cod_area."_".$id_corso_s."_semaforo.txt";
if (file_exists($semaforo)) unlink($semaforo);
echo "
<html>
<head>
<title>$stringa[editor_collaborativo]</title>
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
</head>
<body bgcolor=white>
<span class=testo>$stringa[editor_finito]</span>
<p align=center>
<span class=testo>[<a href=\"#\" onclick=\"self.close()\">$stringa[chiudi]</a>]</span>
</p>
</body>
</html>
";
?>

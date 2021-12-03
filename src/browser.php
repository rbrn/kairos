<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>Browser rilevato</title>
</head>

<body>
<?php
echo $_SERVER['HTTP_USER_AGENT'] . "<hr />\n";

$browser = get_browser()

foreach ($browser as $name => $value) {
   echo "<b>$name</b> $value <br />\n";


?> 


</body>
</html>

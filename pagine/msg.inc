<span class=testo>
<p>
<?php 
ereg_replace("%20"," ",$msg);
$msg=stripslashes($msg);
echo($msg);?>
</p>

<p>
<?php
if ($url) {
	$url=$PATH_ROOT.$url;
	echo "
	<a href=$url>[".$stringa[indietro]."]</a>
	";
} else { 
	echo "
	<a href=javascript:history.back()>[".$stringa[indietro]."]</a>";
};
?>
</p>
</span>

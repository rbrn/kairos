<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_faq=$_REQUEST["id_faq"];
$pagina=$_REQUEST["pagina_r"];

$query="DELETE FROM faq WHERE id_faq='$id_faq'";
$result = $mysqli->query($query);

if ($pagina=="info") {
	Header("Location:index.php?risorsa=info");
} else {
	Header("Location:index.php?risorsa=faq");
};

?>


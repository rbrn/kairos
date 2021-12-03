<?php
$id_risorsa=$_REQUEST["id_risorsa"];
$id_cartella=$_REQUEST["id_cartella"];
?>
<html>
<head>
	<title>KairÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½s</title>
</head>

<!-- frames -->
<frameset  rows="95%,*">

    <frame name="main" src="index.php?risorsa=<?php echo($id_risorsa);?>" marginwidth="0" marginheight="0" scrolling="auto" frameborder="1">

    <frame name="ritorno" src="ritorno.php?id_cartella=<?php echo($id_cartella);?>" marginwidth="0" marginheight="0" scrolling="auto" frameborder="1">

</frameset>



</html>


<?php
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");
?>
<HTML>
<head>
<!-- faccio in modo che questa pagina venga aggiornata ogni 2 secondi -->
<script language="JavaScript">
window.setTimeout("{window.location='chat_loader.php';}", 2000);
</script>
</head>

<BODY>
</BODY>

</html>




<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente1=$kairos_cookie[0];
$id_faq=$_REQUEST["id_faq"];

if (!$id_utente1) {
	echo "
	<html>
	<head><title>$stringa[errore]</title>
	<link rel=\"stylesheet\" href=\"stili/stile_sito.css\">
	<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
	</HEAD>
	<BODY bgcolor=$colore_sfondo>
	<span class=testo>$stringa[errore_no_login]</span>
	</body>
	</html>";
	exit();
};

$query = "SELECT * FROM faq WHERE id_faq='$id_faq'";
$result = $mysqli->query($query);
$faq = $result->fetch_array();
$domanda=str_replace("\n","<br>",$faq["domanda"]);
$risposta = $faq["risposta"];

?>
<html>
<head>
<title><?php echo($stringa[faq]);?>: <?php echo($id_utente);?></title>
<link rel="stylesheet" href="stili/stile_sito.css">
<script language="JavaScript" src="script/funzioni.js"></script>
</head>
<BODY bgcolor=<?php echo($colore_sfondo_neutro);?>>
<TABLE border=0 width=100%>
<TR>
<TD>
<span class=testo><b><?php echo($stringa[domanda_f]);?>:</b></span><br>
<span class=testo><?php echo($domanda);?></span>
</td>
</tr>

<TR>
<TD>
<span class=testo><b><?php echo($stringa[risposta_f]);?>:</b></span><br>
<span class=testo><?php echo($risposta);?></span>
</td>
</tr>

</TABLE>
</body>
</html>

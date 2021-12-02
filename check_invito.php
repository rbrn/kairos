<?php
require "./include/init_sito.inc";
echo "
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>
<html>
<head>
<meta HTTP-EQUIV="refresh" CONTENT="30">

</head>

<body bgcolor=white>
<?php





//vedo se ci sono inviti per questo utente

$db = mysql_connect("localhost",$DBUSER,$DBPWD);

mysql_select_db($DBASE,$db);	

$id_utente=$kairos_cookie[0];



$query = "SELECT id_utente,stanza,date_format(data_invito,\"%d/%m/%Y %H:%i:%s\") as data_inv FROM invito_chat WHERE id_invitato='$id_utente' ORDER BY data_invito DESC";

$result=$mysqli->query($query);

$invito = $result->fetch_array();



$query = "DELETE FROM invito_chat WHERE id_invitato='$id_utente'";

$result=$mysqli->query($query);



if ($invito) {

	$stanza=$invito["stanza"];

	$id_host=$invito["id_utente"];

	$data_invito=$invito["data_inv"];

	echo "

	<script language=javascript>

	var sUrl = 'invito_chat.php?data_invito=$data_invito&stanza=$stanza&id_host=$id_host&id_utente=$id_utente';

	window.showModalDialog(sUrl,window.parent,'dialogHeight:200px;dialogWidth:400px;center:yes;scroll:no;help:no;resizable:no;status:no');

	</script>";

	

	

};

?>

</body>

</html>

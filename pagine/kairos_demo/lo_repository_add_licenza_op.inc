<?php
$indietro="index.php?risorsa=lo_repository";

$codice=$_REQUEST["codice"];

$query="SELECT * FROM lo_ordine_codici WHERE codice='$codice' LIMIT 1";
$result=$mysqli->query($query);

$errore=0;
$msg="";
if (!$result->num_rows) {
	$msg="Non esiste il codice: <strong>$codice</strong>";
	$errore=1;
};

if (!$errore) {
	$riga=$result->fetch_array();
	$id_u=$riga["id_utente"];
	if ($id_u and $id_u<>$kairos_cookie[0]) {
		$msg="Il codice: <strong>$codice</strong> risulta essere in uso da un altro utente";
		$errore=1;
	};
	
	if ($id_u==$kairos_cookie[0]) {
		$msg="Hai gi&agrave; inserito il codice: <strong>$codice</strong>";
		$errore=1;
	};
};

if (!$errore) {
	$query="UPDATE lo_ordine_codici SET"
." id_utente='$kairos_cookie[0]'"
." WHERE codice='$codice'";
	@$mysqli->query($query);
	$msg="E' stato accreditato l'accesso ai Learning Object identificati dal codice inserito";
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>Carica Ordine</td></tr>
";

echo "
<tr>
<td valign=top width=100%>
<a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"$indietro\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>";

echo "<span class=\"testo\">$msg</span><br><br><span class=\"testo\">[<a href=\"$indietro\">OK</a>]</span>";

  
?>  
  
</td></tr></table>
<br>

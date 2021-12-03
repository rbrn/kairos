<?php
$indietro="index.php?risorsa=lo_repository";

$rif_ordine=$_REQUEST["rif_ordine"];
$num_utenti=$_REQUEST["num_utenti"];
$elenco_lo=$_REQUEST["elenco_lo"];

$query="INSERT INTO lo_ordine SET rif_ordine='$rif_ordine',num_utenti='$num_utenti'";
@$mysqli->query($query);

$id_ordine=$mysqli->insert_id;

for ($i=0;$i<count($elenco_lo);$i++) {
	$id_lo=$elenco_lo[$i];
	$query="INSERT INTO lo_ordine_lo SET"
." id_lo='$id_lo',"
." id_ordine='$id_ordine'";
	@$mysqli->query($query);
};

$codici="";
$codici_mail="";
for ($i=0;$i<$num_utenti;$i++) {
	$codice=uniqid('lo');
	$query="INSERT INTO lo_ordine_codici SET"
." codice='$codice',"
." id_utente='',"
." id_ordine='$id_ordine'";
	@$mysqli->query($query);
	$codici.=$codice."<br>";
	$codici_mail.=$codice."\n";
};

$msg = "Codici generati per ordine: $rif_ordine

$codici_mail";

$msg=stripslashes($msg);

$id_package=uniqid("");	
mail_job($id_package,"ordini@garamond.it","Ordine Learning Object","$msg","ordini@garamond.it","ordini@garamond.it","");

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

echo "<span class=\"testo\">L'ordine &egrave; stato caricato con i seguenti codici:</span><br><br><span class=\"testo\">$codici</span>";


  
?>  
  
</td></tr></table>
<br>

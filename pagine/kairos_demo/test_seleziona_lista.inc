<?php
$id_test=$_REQUEST["id_test"];
$query = "SELECT * FROM test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$test = $result->fetch_array();

if ($kairos_cookie[9]) $DBASE_UTENTI="atlante";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>SELEZIONA RISPOSTE TEST</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<span class=testo><b>".$test["titolo"]." ($id_test)</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=test_seleziona&id_test=$id_test\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=test_seleziona&id_test=$id_test\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

?>


  	
<?php

$query = "SELECT * FROM test_compilato WHERE (id_test='$id_test') ";
$result=$mysqli->query($query);

echo "<table border=1 cellpadding=3>";
echo "
<tr>
<td><span class=testopiccolo><b>N.</b></span></td>
<td><span class=testopiccolo><b>IdUtente</b></span></td>
<td><span class=testopiccolo><b>Cognome</b></span></td>
<td><span class=testopiccolo><b>Nome</b></span></td>
<td><span class=testopiccolo><b>Indirizzo</b></span></td>
<td><span class=testopiccolo><b>CittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½</b></span></td>
<td><span class=testopiccolo><b>CAP</b></span></td>
<td><span class=testopiccolo><b>Prov.</b></span></td>
<td><span class=testopiccolo><b>E-Mail</b></span></td>
<td><span class=testopiccolo><b>Tel.</b></span></td>
<td></td>
</tr>";

$i=1;
while ($riga = $result->fetch_array()) {
	$id_test_compilato=$riga["id_test_compilato"];
	$id_autore=$riga["id_utente"];
	
	$query3 = "SELECT * FROM item_test_compilato WHERE id_test_compilato='$id_test_compilato'  ";
	$result3=$mysqli->query($query3);

	$prendi=true;
	while ($item = $result3->fetch_array() and $prendi) {
		$id_item_test="d".$item["id_item_test"];
		$risp_chiusa = $item["risp_chiusa"];
		$risp_altro = $item["risp_altro"];
		
		
		$query4 = "SELECT * FROM item_test WHERE id_item_test='".$item["id_item_test"]."'";
		$result4=$mysqli->query($query4);
		$item_test = $result4->fetch_array();
		
		$tipo_item = $item_test["tipo_item"];
		
		switch ($tipo_item) {
			case "1":
			if (isset(${$id_item_test}) and ${$id_item_test}<>"*") {
				$prendi=false;
				if (${$id_item_test}=="altro" and $risp_altro) {
					$prendi=true;
				} else {
					if (${$id_item_test}==$risp_chiusa) $prendi=true;
				};
			};
			break;
		
			case "3":
			if (isset(${$id_item_test}) and ${$id_item_test}<>"*") {
				$prendi=false;
				$j=${$id_item_test};
				$campo="risp_box".$j;
				$risp_item=$item[$campo];
				if ($risp_item=="1") $prendi=true;
			};
			break;
			
		};
	};

	if ($prendi) {		
		echo "<tr><td><span class=testopiccolo>$i</td><td><span class=testopiccolo>
	<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_autore</a>
</span></td>";
		mysql_select_db($DBASE_UTENTI);
		$query2="SELECT * FROM utenti WHERE id_utente='$id_autore'";
		$result2=$mysqli->query($query2);
		$riga2=$result2->fetch_array();
		mysql_select_db($DBASE);
		printf ("<td><span class=testopiccolo>%s</span></td>",$riga2["cognome"]);
		printf ("<td><span class=testopiccolo>%s</span></td>",$riga2["nome"]);
		printf ("<td><span class=testopiccolo>%s</span></td>",$riga2["indirizzo"]);
		printf ("<td><span class=testopiccolo>%s</span></td>",$riga2["citta"]);
		printf ("<td><span class=testopiccolo>%s</span></td>",$riga2["cap"]);
		printf ("<td><span class=testopiccolo>%s</span></td>",$riga2["prov"]);
		printf ("<td><span class=testopiccolo>%s</span></td>",$riga2["email"]);
		printf ("<td><span class=testopiccolo>%s</span></td>",$riga2["telefono"]);
		printf("<td><span class=testopiccolo><a href=index.php?risorsa=test_compilato&id_test_compilato=%s>%s</a></span></td></tr>",$id_test_compilato,$stringa[questionario_compilato]);
		$i++;
	};

};
echo "</table>";

?>
		
</td></tr>
    </table>


<br>

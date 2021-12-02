<?php


$tipo_elemento=$_REQUEST["tipo_elemento"];
$id_item=$_REQUEST["id_item"];
$id_lo=$_REQUEST["id_lo"];
$risorsa_padre=$_REQUEST["risorsa_padre"];

if ($id_item) {
$query = "SELECT * FROM lo_test_item WHERE id_item='$id_item'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$titolo=htmlentities($riga[titolo]);
$testo_domanda=$riga[domanda];
$tipo_item=$riga[tipo_item];

switch ($tipo_item) {
	case 1:
		$tipo_item_stringa=$stringa[sm_rs];
		break;
		
	case 2:
		$tipo_item_stringa=$stringa[sm_rm];
		break;
		
	case 3:
		$tipo_item_stringa=$stringa[vero_falso];
		break;	
	
	case 4:
		$tipo_item_stringa=$stringa[inserimento];
		break;	
	
	case 5:
		$tipo_item_stringa=$stringa[associazione];
		break;	
	
	case 6:
		$tipo_item_stringa=$stringa[aperta];
		break;	
	
	case 7:
		$tipo_item_stringa=$stringa[dragdrop];
		break;		
};		
};


switch ($tipo_elemento) {
	case "id_item":
		$label=$stringa[commento_item];
		$campo=$tipo_elemento;
		$val_campo=$id_item;
		break;
};

$indietro="repository_index";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_repository])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($label)."</b></span>
</td></tr>


<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=$indietro&id_cartella=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=$indietro&id_cartella=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

?>

<TABLE BORDER=0 width=100%>
<tr>
<td>
 
<?php

if ($tipo_elemento=="id_item") {

echo "<TABLE border=0 width=550>";

echo "

 <TR> 
        <TD align=right valign=top><span class=testo><b>$stringa[testo_domanda]:</b></span></TD>
  		<TD><span class=testo>$titolo<span></TD>
      </TR>
	  
<TR>
<TD align=\"right\" valign=\"top\"><span class=testo><b>$stringa[tipo]:</b></span></TD>";

	echo "
	<TD valign=\"top\">
	<span class=testo>$tipo_item_stringa</span>
	";
	echo "</TD>";

echo "</TR>";

if ($tipo_item=="4") {
	$nspazio=0;
	for ($i=0;$i<strlen($testo_domanda);$i++) {
		$char=substr($testo_domanda,$i,1);
		if ($char=="[" and substr($testo_domanda,$i+1,1)=="*" and substr($testo_domanda,$i+2,1)=="]") {
			$nspazio++;
			$testo_domanda1.="[*".$nspazio."]";
			$i=$i+2;
		} else {
			$testo_domanda1.=$char;
		};
	};
};

if (trim($testo_domanda) or trim($testo_domanda1)) {
echo "
<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[testo_domanda_esteso]:</b></span></td>
</tr>
<tr>
<td colspan=2 valign=top width=500>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table width=\"100%\" border=\"0\" cellspacing=\"10\" cellpadding=\"1\" bgcolor=\"#ffffff\">
<tr><td>
<span class=testo>";
if ($tipo_item=="4") {
	echo "$testo_domanda1";
} else {
	echo "$testo_domanda";
};
echo "</span>
</td></tr>
</table>
</td></tr>
</table>
</td>
</tr>";
};

echo "</TABLE>";

};

echo "<p><span class=testopiccolo><a href=\"index.php?risorsa=lo_test_commento_add&tipo_elemento=$tipo_elemento&id_item=$id_item&id_test=$id_test&id_sezione=$id_sezione&risorsa_padre=$risorsa_padre\"
>$stringa[aggiungi_commento]</a></span></p>";

echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" >
";



echo "<tr>
<td width=400 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[commento]</b></span></td>";

echo "
<td width=50 bgcolor=\"$colore_scuro\"><span class=testonegativo><b>$stringa[range]</b></span></td>";

echo "
<td width=50 bgcolor=\"$colore_scuro\"></td>
<td width=50 bgcolor=\"$colore_scuro\"></td>
</tr>
\n";

$colore=$colore_sfondo;


$query="SELECT * FROM lo_test_commento WHERE $campo='$val_campo' AND tipo_elemento='$tipo_elemento' ORDER BY lim_inf,lim_sup";
$result=$mysqli->query($query);

while ($commento = $result->fetch_array()) {
	$id_commento=$commento[id_commento];
	$id_editor=$commento[id_editor];
	$commento_testo=$commento[commento];
	$lim_inf=$commento[lim_inf];
	$lim_sup=$commento[lim_sup];

	echo "<tr bgcolor=\"$colore\">";
		
	
	echo "<td valign=top><span class=testo>$commento_testo</span></td>\n";
	echo "<td valign=top align=right><span class=testo>$lim_inf - $lim_sup</span></td>\n";
	
	
	if ($ruolo=='admin' or $id_utente==$id_editor) {
		echo "
		<td valign=middle align=center>
		<a href=index.php?risorsa=lo_test_commento_mod&id_commento=$id_commento&tipo_elemento=$tipo_elemento&id_item=$id_item&risorsa_padre=$risorsa_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_commento','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[edit]\" border=\"0\" name=\"img_mod_$id_commento\"></a></td>";
	} else {
		echo "<td>&nbsp;</td>";
	};
	
	if ($ruolo=='admin' or $id_utente==$id_editor) {
		echo "
		<td valign=middle align=center>
		<a href=index.php?risorsa=msg&msg=conf_canc&pagina=lo_test_commento_elimina.php&id_commento=$id_commento&tipo_elemento=$tipo_elemento&id_item=$id_item&risorsa_padre=$risorsa_padre onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_commento','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_commento\"></a>
		</td>
		";
	} else {
		echo "<td>&nbsp;</td>";
	};
	
	
	echo "</tr>";
	
	if ($colore==$colore_sfondo) {
		$colore=$colore_sfondo_neutro;
	} else {
		$colore=$colore_sfondo;
	};
}; 
echo "</table>\n";

echo "		
</td></tr>
</table>";

?>
		
</td></tr>
</table>

</td></tr>
</table>
<br>

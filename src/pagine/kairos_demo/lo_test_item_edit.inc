<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

$id_item=$_REQUEST["id_item"];
$risorsa_padre=$_REQUEST["risorsa_padre"];
$azione=$_REQUEST["azione"];

$query = "SELECT * FROM lo_test_item WHERE id_item='$id_item'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$titolo=htmlentities($riga[titolo]);
$testo_domanda=$riga[domanda];
$tipo_item=$riga[tipo_item];
$max_risposte=$riga[max_risposte];
$altro=$riga[altro];
$id_editor=$riga[id_editor];

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
		
	case 8:
		$tipo_item_stringa=$stringa[cacciaerrore];
		break;	
		
	case 9:
		$tipo_item_stringa=$stringa[ascoltaescrivi];
		break;	
		
	case 10:
		$tipo_item_stringa=$stringa[cruciverba];
		break;	
		
};		

echo "
<div style=\"height: 50px;\"></div>
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_repository])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[modifica_domanda_test])."</b></span>
</td></tr>


<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=repository_index&id_cartella=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=repository_index&id_cartella=$risorsa_padre\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";


?>

<TABLE BORDER=0 width=100%>
<tr>
<td>
 
<?php
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

if ($tipo_item=="8") {
	$nerrore=0;
	for ($i=0;$i<strlen($testo_domanda);$i++) {
		$char=substr($testo_domanda,$i,1);
		if ($char=="[" and substr($testo_domanda,$i+1,1)=="*" and substr($testo_domanda,$i+2,1)=="]") {
			$nerrore++;
			$testo_domanda1.="[*".$nerrore."]";
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
<tr>";

$tag_g="";

echo "
<td colspan=2 valign=top width=\"600\" >
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<table width=\"600\" border=\"0\" cellspacing=\"10\" cellpadding=\"1\" bgcolor=\"#ffffff\">
<tr><td>
<span class=testo>";
if ($tipo_item=="4" or $tipo_item=="8") {
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

$item_gest=$tipo_item;
if ($tipo_item=="1" or $tipo_item=="2" or $tipo_item=="3") $item_gest=1;
require "./pagine/kairos_demo/lo_test_item_edit_".$item_gest.".inc";

?>
		
</td></tr>
</table>

</td></tr>
</table>
<br>

<?php

echo "                </div>
            </div>
        </div>
    </div>
</div>"

?>

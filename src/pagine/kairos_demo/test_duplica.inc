<?php
$id_test_padre=$_REQUEST[id_test];

$query = "SELECT * FROM test WHERE id_test='$id_test_padre'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$tipo_test=$riga[tipo_test];
$num_domande=$riga[num_domande];
$titolo=$riga[titolo];
$punteggio_soglia=$riga[punteggio_soglia];

if ($tipo_test==0) {
	$tipo_stringa=$stringa[verifica];
} else {
	$tipo_stringa=$stringa[sondaggio];
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[duplica_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<span class=testo><b>".$riga["titolo"]." ($id_test)</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=test_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=test_index\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";
?>

<form action=test_duplica_op.php  method=post>
<input type=hidden name=id_test_padre value="<?php echo($id_test_padre);?>">
<input type=hidden name=tipo_test value="<?php echo($tipo_test);?>">
    <TABLE border=0 width=461>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
      <TR> 
        <TD align=right><span class=testo><b><?php echo($stringa[id_test]);?>:</b></span></TD>
        <TD> 
			<INPUT type="text"  name=id_test size=20>
        </TD>
      </TR>
	  <TR> 
        <TD align=right><span class=testo><b><?php echo($stringa[titolo]);?>:</b></span></TD>
        <TD>
          <INPUT type="text" name=titolo size=50 value="<?php echo($titolo);?>">
          </TD>
      </TR>

	   <TR> 
        <TD align=right><span class=testo><b><?php echo($stringa[tipo]);?>:</b></span></TD>
        <TD>
          <span class=testo><?php echo($tipo_stringa);?></span>
          </TD>
      </TR>
	  
	  <TR> 
        <TD align=right><span class=testo><b><?php echo($stringa[num_domande_random]);?>:</b></span></TD>
        <TD valign=bottom>
          <INPUT type="text" name=num_domande size=10 value="<?php echo($num_domande);?>">
          </TD>
      </TR>
	  
	  <TR> 
        <TD align=right><span class=testo><b><?php echo($stringa[punteggio_soglia]);?>:</b></span></TD>
        <TD valign=bottom>
          <INPUT type="text" name=punteggio_soglia size=10 value="<?php echo($punteggio_soglia);?>">
          </TD>
      </TR>
	  
    </TABLE>
    <BR>
    <P align=center> 
      <INPUT type=submit value="<?php echo($stringa[ok]);?>">
    </P>
 </FORM>
</td></tr></table><br>

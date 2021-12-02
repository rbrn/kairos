<?php
$id_test=$_REQUEST["id_test"];

$query = "SELECT * FROM test WHERE id_test='$id_test'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
$tipo_test=$riga[tipo_test];
$num_domande=$riga[num_domande];
$testo=$riga[titolo];
$punteggio_soglia=$riga[punteggio_soglia];

$tipo_0="";
$tipo_1="";

if ($tipo_test==0) {
	$tipo_0="selected";
} else {
	$tipo_1="selected";
};


echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_test])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[test_modifica])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

?>

<form action=test_modifica_op.php  method=post name=modulo id=modulo>
<input type=hidden name=id_test value="<?php echo($id_test);?>">
    <TABLE border=0 width=461>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
	  <!--
      <TR> 
        <TD align=right><span class=testo><b><?php echo($stringa[id_test]);?>:</b></span></TD>
        <TD> 
			<span class=testo><?php echo($id_test);?></span>
        </TD>
      </TR>
	  -->
	  <TR> 
        <TD align=right valign=top><span class=testo><b><?php echo($stringa[titolo]);?>:</b></span></TD>
        
<?php
if (!$win_ie or $cod_area<>'kairos_patente') {
	echo "
  <TD>
  <INPUT type=\"text\" name=testo size=50 value=\"$testo\">
  </TD>";
} else {
	echo "
	<input type=\"hidden\" name=\"testo\" id=\"testo\">\n
	<td valign=top>
	";
	$modifica_testo=true;
	require "./include/editor_materiali.inc";

	echo "	
	</td>
	";
};
?>		
		
      </TR>

	   <TR> 
        <TD align=right><span class=testo><b><?php echo($stringa[tipo]);?>:</b></span></TD>
        <TD>
          <select name=tipo_test>
		  <option value=0 <?php echo($tipo_0);?>><?php echo($stringa[verifica]);?></option>
		  <option value=1 <?php echo($tipo_1);?>><?php echo($stringa[sondaggio]);?></option>
		  </select>
          </TD>
      </TR>
	  
	  <TR> 
        <TD align=right><span class=testo><b><?php echo($stringa[num_domande_random]);?>:</b></span></TD>
        <TD valign=bottom>
          <INPUT type="text"  name=num_domande size=10 value="<?php echo($num_domande);?>">
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
      <?php
      	if (!$win_ie or $cod_area<>'kairos_patente') {
			echo "
			<input type=submit value=$stringa[ok]>";
		} else {
			echo "<input type=submit value=$stringa[ok] onclick=\"inoltra();return true\">";
		};
		?>
    </P>
 </FORM>
</td></tr></table>
<br>

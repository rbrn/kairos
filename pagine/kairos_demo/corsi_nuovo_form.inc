<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[area_admin])."</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[gestione_corsi])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper($stringa[nuovo_corso])."</b></span>
</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";

echo "
<table border=0 width=500>
<tr>
<td>
<form action=corsi_nuovo_op.php method=post name=modulo id=modulo>
<table border=0 wodth=100% cellspacing=2 cellpadding=2>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[id_corso]</b>:</span></p>
</td>
<td valign=top>
<input type=text size=20 name=id_corso>
</td>
</tr>

<tr>
<td align=right valign=top>
<p><span class=testo><b>$stringa[titolo]</b>:</span></p>
</td>
<td valign=top>
<input type=text size=70 name=descrizione>
</td>
</tr>";


echo"
<tr>
<td colspan=2 valign=top><span class=testo><b>$stringa[descrizione]</b>:</span></td>
</tr>
<tr>
<td colspan=2 valign=top>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
<tr><td>
<TEXTAREA id=\"testo\" cols=80 name=\"testo\" rows=30>".$testo."</TEXTAREA>
</td></tr>
</table>
</td>
</tr>";

echo "
<!--
<tr>
<td align=right valign=top>
<p><span class=testo><b>Colore della fascetta del corso</b></span></p>
</td>
<td valign=top>

<table width=\"80%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\">
  <tr> 
    <td height=\"20\" bgcolor=\"#000066\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td height=\"20\" bgcolor=\"#0033CC\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td height=\"20\" bgcolor=\"#0066FF\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td height=\"20\" bgcolor=\"#006666\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td height=\"20\" bgcolor=\"#006633\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td height=\"20\" bgcolor=\"#669933\"> 
      <div align=\"center\"><font color=\"#003366\" face=\"Arial, Helvetica, sans-serif\" size=\"2\"><b>scritta 
        blu</b></font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td height=\"20\" bgcolor=\"#FFCC00\"> 
      <div align=\"center\"><font color=\"#003366\" face=\"Arial, Helvetica, sans-serif\" size=\"2\"><b>scritta 
        blu</b></font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td height=\"20\" bgcolor=\"#CC6600\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td height=\"20\" bgcolor=\"#FF0000\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td height=\"20\" bgcolor=\"#663366\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td bgcolor=\"#CC0066\" height=\"20\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td bgcolor=\"#9966FF\" height=\"20\"> 
      <div align=\"center\"><font color=\"#003366\" face=\"Arial, Helvetica, sans-serif\" size=\"2\"><b>scritta 
        blu</b></font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td bgcolor=\"#FF9966\" height=\"20\"> 
      <div align=\"center\"><font color=\"#003366\" face=\"Arial, Helvetica, sans-serif\" size=\"2\"><b>scritta 
        blu</b></font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td bgcolor=\"#6699FF\" height=\"20\"> 
      <div align=\"center\"><font color=\"#003366\" face=\"Arial, Helvetica, sans-serif\" size=\"2\"><b>scritta 
        blu</b></font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td bgcolor=\"#666666\" height=\"20\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td bgcolor=\"#333333\" height=\"20\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td bgcolor=\"#996633\" height=\"20\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td bgcolor=\"#660000\" height=\"20\"> 
      <div align=\"center\"><font color=\"#FFFFFF\" face=\"Arial, Helvetica, sans-serif\" size=\"2\">scritta 
        bianca</font></div>
    </td>
  </tr>
  <tr> 
    <td height=\"20\">&nbsp;</td>
  </tr>
  <tr> 
    <td bgcolor=\"#66FF00\" height=\"20\"> 
      <div align=\"center\"><font color=\"#003366\" face=\"Arial, Helvetica, sans-serif\" size=\"2\"><b>scritta 
        blu</b></font></div>
    </td>
  </tr>
</table>

</td>
</tr>
-->

<tr><td colspan=2>&nbsp;</td></tr>
<tr><td colspan=2 align=right>";

echo "<input type=\"submit\" name=\"ok\" value=\"$stringa[ok]\" />";


echo "
</td></tr>
</table>

</form>


</td>
</tr>
</table>
</td>
</tr>
</table>
<br><br>";

?>

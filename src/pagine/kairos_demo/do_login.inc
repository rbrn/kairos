<?php
if (!isset($url)) {
	if ($dir=='materiali') {
		$url="materiali_browse.php?".$kairos_cookie[3];
	} else {
		$url="index.php?".$kairos_cookie[3];
	};
} else {

	$url=$url."?".$kairos_cookie[3];

};

if (!in_array($cod_area,$kairos_pubblici)) {
	echo "
	<table width=100% border=0 cellspacing=2 cellpadding=0>
    <tr><td align=left>
	<p>&nbsp;</p>
<table width=\"152\" border=\"1\" cellpadding=\"0\" cellspacing=\"0\" bgcolor=\"$colore_sfondo\" bordercolor=\"$colore_bordo\">
        <tr> 
          <td height=\"27\" valign=\"top\" align=center bgcolor=$colore_scuro >
		  <span class=testopiccolonegativo><b>$stringa[login]</b></span>
		  </td>
        </tr>
        <tr> 
          <td valign=\"top\">
		  <form action=login.php method=post>
		  	<input type=hidden name=url value=\"$url\">
            <table width=\"144\" border=\"0\" align=\"center\" bgcolor=\"$colore_sfondo\">
              <tr> 
                <td width=\"23\"> 
                 <div align=\"center\"><span class=testopiccolo><b>$stringa[id]</b></div>
                </td>
               <td width=\"83\"> 
                  <input type=\"text\" name=\"id_utente_form\" size=\"12\">
                </td>
                <td width=\"22\"> </td>
              </tr>
              <tr> 
                <td width=\"23\" height=\"23\"> 
                  <div align=\"center\"><span class=testopiccolo><b>$stringa[pw]</b></div>
                </td>
                <td width=\"83\" height=\"23\"> 
                  <input type=\"password\" name=\"pwd_utente_form\" size=\"12\">
                </td>
                <td width=\"22\" height=\"23\">
				<INPUT TYPE=\"submit\" NAME=\"login\" value=$stringa[ok]>
				</td>
				</form>
              </tr>
              <tr> 
                <td colspan=\"3\"> 
                  <div align=\"center\"><span class=testopiccolo><a href=index.php?risorsa=chiedi_pwd>$stringa[dimenticato_pw]</span></div>
<hr size=1>
					<div align=\"center\"><span class=testopiccolo>$stringa[registration_required0]<a href=index.php?risorsa=registrazione><b>$stringa[registration_required1]</b></a>.</span></div>
                </td>
              </tr>
            </table>
          </td>
        </tr>
</table>
<p>&nbsp;</p>
</td></tr>
</table>
";
} else {
	echo "
 <table width=\"170\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
              <tr> 
                <td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\"> 
		  <span class=testonegativo><b>$stringa[login]</b></span>
		  		</td>

        </tr>";
		
		echo "
		<tr><td valign=\"top\" align=\"center\">";
		
		echo "
        <table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
		<tr> 
          <td valign=\"top\">";
		  
		echo "<span class=testopiccolo>Per accedere a quest'area &egrave; necessario essere utenti registrati di <a href=\"\">Garamond</a> e fare Login dalla relativa Home Page</span>";
		echo "</td></tr></table>";
		
		echo "</td></tr>";
		
	
	echo "</table>";
};
?>

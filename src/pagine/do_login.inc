<?php

if (!isset($url)) {

	$url="index.php?".$kairos_cookie[3];

} else {

	$url=$url."?".$kairos_cookie[3];

};
	echo "

	<table width=100% border=0 cellspacing=2 cellpadding=0>

    <tr><td align=left>

	<p>&nbsp;</p>

<table width=\"152\" border=\"1\" cellpadding=\"0\" cellspacing=\"0\" bgcolor=\"$colore_sfondo\" bordercolor=\"$colore_bordo\">

        <tr> 

          <td height=\"27\" valign=\"top\" align=center bgcolor=$colore_scuro >

		  <span class=testopiccolonegativo><b>LOGIN</b></span>

		  </td>

        </tr>

        <tr> 

          <td valign=\"top\">

		  <form action=login.php method=post>

		  	<input type=hidden name=url value=\"$url\">

			

            <table width=\"144\" border=\"0\" align=\"center\" bgcolor=\"$colore_sfondo\">

              <tr> 

                <td width=\"23\"> 

                  <div align=\"center\"><span class=testopiccolo><b>ID</b></div>

                </td>

               <td width=\"83\"> 

                  <input type=\"text\" name=\"id_utente_form\" size=\"12\">

                </td>

                <td width=\"22\"> </td>

              </tr>

              <tr> 

                <td width=\"23\" height=\"23\"> 

                  <div align=\"center\"><span class=testopiccolo><b>PW</b></div>

                </td>

                <td width=\"83\" height=\"23\"> 

                  <input type=\"password\" name=\"pwd_utente_form\" size=\"12\">

                </td>

                <td width=\"22\" height=\"23\">

				<INPUT TYPE=\"image\" NAME=\"login\" SRC=\"img/vai.gif\">

				</td>

				</form>

              </tr>

              <tr> 

                <td colspan=\"3\"> 

                  <div align=\"center\"><span class=testopiccolo><a href=index.php?risorsa=chiedi_pwd>Ho dimenticato la PW!</span></div>
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


?>

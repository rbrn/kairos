<?php 
require "./include/init_sito.inc";
?>
<html>

<head>

	<title><?php echo($stringa[inserisci_tabella]);?></title>

	<script language="JavaScript">

		

 function capture (color) 

 {

 document.all.extrait.style.background=color;

 document.all.valhexa.value=color;

 }

 

 function click_select (color) 

 {

 document.all.selezione.style.background=color;

 document.all.rit_colore.value=color;

 }

 

 function hex(q) 

 {

 hexa="0123456789abcdef";

 return  hexa.charAt(q >> 4 &  0xf)  +  hexa.charAt(q & 0xf);

 }

                  

 

 function affiche () {

 

 var q;

 var compteur=1;

 

 var cons="<table cellpadding='0' cellspacing='0'><tr>"; 

                 

 for (var k=0; k<256; k+=51){

 for (var i=0; i<256; i+=51){

 for (var j=0; j<256; j+=51){

 

 if (compteur==36) {

 

   cons+="</tr><tr>";

   compteur=0;

   

                   }

                   

 else 

                   

                   

       cons+="<td bgcolor='#"+ hex (k)+""+hex (i)+""+hex (j)+"' onMouseOver='capture(this.bgColor)'  onClick='click_select(this.bgColor)'><a href='#' style='text-decoration:none; cursor:crosshair '>&nbsp;</a></td>";

       compteur=compteur+1;

       

      

                            }

                            }

                            }

 

 

                            

      cons+="</tr></table>";

      

      return cons;

 }

	

</script>





</head>



<body><font face="Verdana, Arial, Helvetica, sans-serif" size="2">

<B><?php echo($stringa[inserisci_tabella]);?></B></font><BR>

<FORM NAME="form1">

  <TABLE width="303" height="361">

    <TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[righe]);?>:</font></TD>

      <TD> 

        <INPUT TYPE="text" NAME="rows" VALUE="2" MAXLENGTH="3" SIZE="3">

      </TD>

    </TR>

    <TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[colonne]);?>:</font></TD>

      <TD> 

        <INPUT TYPE="text" NAME="columns" VALUE="2" MAXLENGTH="3" SIZE="3">

      </TD>

    </TR>

    <TR> 

      <TD COLSPAN="2"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"></font></TD>

    </TR>

    <TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[margine_interno]);?>:</font></TD>

      <TD> 

        <INPUT TYPE="text" NAME="cellpadding" VALUE="0" MAXLENGTH="3" SIZE="3">

      </TD>

    </TR>

    <TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[spazio_celle]);?>:</font></TD>

      <TD> 

        <INPUT TYPE="text" NAME="cellspacing" VALUE="0" MAXLENGTH="3" SIZE="3">

      </TD>

    </TR>

    <TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[larghezza_cella]);?>:</font></TD>

      <TD> 

        <INPUT TYPE="text" NAME="cellwidth" VALUE="" MAXLENGTH="3" SIZE="3">

      </TD>

    </TR>

    <TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[altezza_cella]);?>:</font></TD>

      <TD> 

        <INPUT TYPE="text" NAME="cellheight" VALUE="" MAXLENGTH="3" SIZE="3">

      </TD>

    </TR>

    <TR> 

      <TD COLSPAN="2" height="4"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"></font></TD>

    </TR>

    <TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[bordo]);?>:</font></TD>

      <TD> 

        <INPUT TYPE="text" NAME="borderwidth" VALUE="1" MAXLENGTH="3" SIZE="3">

      </TD>

    </TR>

    <TR> 

      <TD ALIGN="RIGHT" height="86"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[colore_sfondo]);?>:</font></TD>

      <TD height="86"> 

        <input type="button" id="extrait" class="extrait" value="     ">

        <input type="text" size="7" name="valhexa" value="" height="50">

        <table border="1">

          <tr> 

            <td> 

              <script>

           document.write(affiche());

           </script>

            </td>

          </tr>

        </table>

        &nbsp; <font size="1" face="Verdana, Arial, Helvetica, sans-serif"><?php echo($stringa[selezionato]);?></font> 

        <input type="button" id="selezione" class="extrait" value="           " name="button">

        <input type="hidden"  name="rit_colore" value="">

      </TD>

    </TR>

  </TABLE>



<BR>

<CENTER>

<INPUT TYPE="submit" NAME="submit" VALUE="<?php echo($stringa[inserisci_tabella]);?>" 

	onclick="window.opener.InsertTable(form1.rows.value, form1.columns.value, form1.cellpadding.value, form1.cellspacing.value, form1.borderwidth.value, form1.cellwidth.value, form1.cellheight.value, form1.rit_colore.value); window.close();  window.opener.idContent.focus(); ">

<INPUT TYPE="button" NAME="cancel" VALUE="<?php echo($stringa[annulla]);?>" onclick="window.close()">

</center></FORM>





</body>

</html>


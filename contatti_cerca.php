<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$ruolo=ruolo_utente($kairos_cookie[0]);

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>Consulenti: segnalazione contatto</title>
	<SCRIPT language=JavaScript src="script/funzioni.js"></SCRIPT>
<LINK href="stili/kairos_demo/stile_sito.css" rel=stylesheet>
</head>

<body>
<TABLE cellSpacing=10 cellPadding=0 width="100%" border=0>
        <TBODY>

    
        <TR>
          <TD>
            <FORM action=contatti_lista.php method=post>
            <table border=0>
			
			 <?php 
  if ($ruolo=="admin" or 1) {
  echo "<tr><td align=right><SPAN class=testo><B>ID utente:</B></span></td><td><input name=id_utente_cerca size=20 value=\"$kairos_cookie[0]\"></td></tr>";
  };
  ?>
			
			<tr><td align=right><SPAN class=testo><B>Codice meccanografico:</B></span></td><td><input name=cod_mecc_cerca size=40></td></tr>


			<tr><td align=right valign=top><SPAN class=testo><B>Tipologia di acquisto:</B></SPAN></td>
			
            <td valign=top>
			<INPUT type=checkbox value="x" name=risp_voce_3_1><SPAN 
            class=testopiccolo>Acquisto software</SPAN><BR>
			
			<INPUT type=checkbox value="x" 
             name=risp_voce_3_2><SPAN class=testopiccolo>Noleggio 
            piattaforma</SPAN><BR>
			
			<INPUT type=checkbox value="x"  
            name=risp_voce_3_3><SPAN class=testopiccolo>Abbonamento E-Prof per 
            gruppo docenti</SPAN><BR>
			
			<INPUT type=checkbox value="x" 
            name=risp_voce_3_4><SPAN class=testopiccolo>Iscrizione corsi online 
            per gruppo docenti</SPAN><BR>
			
			<INPUT type=checkbox value="x"  
            name=risp_voce_3_5><SPAN class=testopiccolo>Iscrizione Master per 
            gruppo docenti</SPAN><BR>
			
			<INPUT type=checkbox value="x"  
            name=risp_voce_3_6><SPAN class=testopiccolo>Acquisto 
            Libri</SPAN><BR>
			
			<INPUT type=checkbox value="x" name=risp_voce_3_7><SPAN 
            class=testopiccolo>Acquisto Learning Object</SPAN><BR>
			
			<INPUT type=checkbox value="x" name=risp_voce_3_8><SPAN 
            class=testopiccolo>Teatro dei Suoni</SPAN><BR>
			
			<INPUT type=checkbox value="x" name=risp_voce_3_9><SPAN class=testopiccolo>Altro</SPAN>
			</td>
			</tr>
			</table>
            
            <BR>
            <P 
      align=center><INPUT type=submit value=OK></P></FORM></TD></TR></TBODY></TABLE>


</body>
</html>

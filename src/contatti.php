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

  <?php 
  
  echo "<tr><td><span class=testo>[<a href=contatti_cerca.php>Cerca contatti archiviati</a>]</span></td></tr>";
  
  ?>
     
        <TR>
          <TD>
            <FORM action=contatti_op.php method=post>
            <P><SPAN class=testo><B>1. Indica la Scuola o l'Ente che hai 
            contattato.</B></SPAN></P><TEXTAREA name=risposta_aperta_1 rows=8 cols=60></TEXTAREA> 
            
			<P><SPAN class=testo><B>Codice meccanografico:</B> <input name=cod_mecc size=40></SPAN></P>
			
            <P><SPAN class=testo><B>2. Indica la persona e il ruolo con cui hai 
            avuto un contatto. </B></SPAN></P><TEXTAREA name=risposta_aperta_2 rows=8 cols=60></TEXTAREA> 
            
            <P><SPAN class=testo><B>3. Quale tipologia di acquisto potrebbe scaturire da questo 
            contatto?</P></B></SPAN>
            <P></P><INPUT type=checkbox value="x" name=risp_voce_3_1><SPAN 
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
			
			<INPUT 
            type=checkbox value="x"  name=risp_voce_3_9><SPAN class=testopiccolo>Altro, 
            specificare:<INPUT size=50 
            name=risposta_altro_voce_3_9></SPAN>
			
            <P><SPAN class=testo><B>4. Aggiungi liberamente i tuoi commenti. 
            Grazie!</B></SPAN></P><TEXTAREA name=risposta_aperta_4 rows=8 cols=60></TEXTAREA> 
            <BR>
            <P 
      align=center><INPUT type=submit value=OK></P></FORM></TD></TR></TBODY></TABLE>


</body>
</html>

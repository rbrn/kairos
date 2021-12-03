<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente=$kairos_cookie[0];

$risposta_aperta_1     =$_REQUEST[risposta_aperta_1];
$cod_mecc    			 =$_REQUEST[cod_mecc];
$risposta_aperta_2     =$_REQUEST[risposta_aperta_2];
$risp_voce_3_1		  =$_REQUEST[risp_voce_3_1];
$risp_voce_3_2		  =$_REQUEST[risp_voce_3_2];
$risp_voce_3_3		  =$_REQUEST[risp_voce_3_3];
$risp_voce_3_4		  =$_REQUEST[risp_voce_3_4];
$risp_voce_3_5		  =$_REQUEST[risp_voce_3_5];
$risp_voce_3_6		  =$_REQUEST[risp_voce_3_6];
$risp_voce_3_7		  =$_REQUEST[risp_voce_3_7];
$risp_voce_3_8		  =$_REQUEST[risp_voce_3_8];
$risp_voce_3_9		  =$_REQUEST[risp_voce_3_9];
$risposta_altro_voce_3_9 =$_REQUEST[risposta_altro_voce_3_9];

$risposta_aperta_4     =$_REQUEST[risposta_aperta_4];

$query="INSERT INTO contatti SET
id_utente='$id_utente',
data_compilazione=now(),
risposta_aperta_1     ='$risposta_aperta_1',
cod_mecc			  ='$cod_mecc',
risposta_aperta_2     ='$risposta_aperta_2',
risp_voce_3_1		  ='$risp_voce_3_1',
risp_voce_3_2		  ='$risp_voce_3_2',
risp_voce_3_3		  ='$risp_voce_3_3',
risp_voce_3_4		  ='$risp_voce_3_4',
risp_voce_3_5		  ='$risp_voce_3_5',
risp_voce_3_6		  ='$risp_voce_3_6',
risp_voce_3_7		  ='$risp_voce_3_7',
risp_voce_3_8		  ='$risp_voce_3_8',
risp_voce_3_9		  ='$risp_voce_3_9',
risposta_altro_voce_3_9 ='$risposta_altro_voce_3_9',

risposta_aperta_4     ='$risposta_aperta_4'
";
$result = $mysqli->query($query);

$msg = "
Scheda contatto:
	
Consulente: $id_utente
	
1. Indica la Scuola o l'Ente che hai contattato.
	
$risposta_aperta_1

Codice meccanografico: $cod_mecc
------------------------------------------------------------------------
2. Indica la persona e il ruolo con cui hai avuto un contatto.

$risposta_aperta_2
-------------------------------------------------------------------------
3. Quale tipologia di acquisto potrebbe scaturire da questo contatto?

($risp_voce_3_1) Acquisto software
($risp_voce_3_2) Noleggio piattaforma
($risp_voce_3_3) Abbonamento E-Prof per gruppo docenti
($risp_voce_3_4) Iscrizione corsi online per gruppo docenti
($risp_voce_3_5) Iscrizione Master per gruppo docenti
($risp_voce_3_6) Acquisto Libri
($risp_voce_3_7) Acquisto Learning Object
($risp_voce_3_7) Teatro dei suoni
($risp_voce_3_9) Altro, specificare: $risposta_altro_voce_3_9
-------------------------------------------------------------------------
4. Aggiungi liberamente i tuoi commenti. Grazie!

$risposta_aperta_4
-------------------------------------------------------------------------

"; 

	$msg=stripslashes($msg);
	
	$id_package=uniqid("");	
	mail_job($id_package,"comunicazione@garamond.it,consulenti@garamond.it","[Consulenti] Segnalazione contatto","$msg","fleo@garamond.it","fleo@garamond.it","");	

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
            <P><SPAN class=testo><B>La scheda contatti ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ stata archiviata, grazie!</B></SPAN></P></TD></TR></TBODY></TABLE>


</body>
</html>

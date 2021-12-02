<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$ruolo=ruolo_utente($kairos_cookie[0]);

$id_contatto=$_REQUEST[id_contatto];
$query="SELECT * FROM contatti WHERE id_contatto='$id_contatto'";

$result = $mysqli->query($query);
$riga=$result->fetch_array();

$id_utente=$riga[id_utente];

$risposta_aperta_1     =htmlentities($riga[risposta_aperta_1]);
$cod_mecc		 	   =$riga[cod_mecc];
$risposta_aperta_2     =htmlentities($riga[risposta_aperta_2]);
$risp_voce_3_1		  =$riga[risp_voce_3_1];
$risp_voce_3_2		  =$riga[risp_voce_3_2];
$risp_voce_3_3		  =$riga[risp_voce_3_3];
$risp_voce_3_4		  =$riga[risp_voce_3_4];
$risp_voce_3_5		  =$riga[risp_voce_3_5];
$risp_voce_3_6		  =$riga[risp_voce_3_6];
$risp_voce_3_7		  =$riga[risp_voce_3_7];
$risp_voce_3_8		  =$riga[risp_voce_3_8];
$risp_voce_3_9		  =$riga[risp_voce_3_9];
$risposta_altro_voce_3_9 =$riga[risposta_altro_voce_3_9];

$risposta_aperta_4     =htmlentities($riga[risposta_aperta_4]);

$c3_1="";
$c3_2="";
$c3_3="";
$c3_4="";
$c3_5="";
$c3_6="";
$c3_7="";
$c3_8="";
$c3_9="";


for ($i=1;$i<=9;$i++) {
	$r="risp_voce_3_".$i;
	if (${$r}) {
		$c="c3_".$i;
		${$c}="checked";
	};
};


?><!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>Consulenti: segnalazione contatto</title>
	<SCRIPT language=JavaScript src="script/funzioni.js"></SCRIPT>
<LINK href="stili/kairos_demo/stile_sito.css" rel=stylesheet>
</head>

<body>

<TABLE cellSpacing=10 cellPadding=0 width="100%" border=0>
        <TBODY>

  <tr><td><p><span class=testo>[<a href=javascript:history.back()>Indietro</a>]</span></p></td></tr>
     
        <TR>
          <TD>
			<FORM action=contatti_modifica.php method=post>
			<INPUT type=hidden name=id_contatto value="<?php echo $id_contatto ?>"> 
            <P><SPAN class=testo><B>1. Indica la Scuola o l'Ente che hai 
            contattato.</B></SPAN></P><TEXTAREA name=risposta_aperta_1 rows=8 cols=60 ><?php echo($risposta_aperta_1);?></TEXTAREA> 
            
			<P><SPAN class=testo><B>Codice meccanografico:</B> <input name=cod_mecc size=40 value="<?php echo($cod_mecc);?>"></SPAN></P>
			
            <P><SPAN class=testo><B>2. Indica la persona e il ruolo con cui hai 
            avuto un contatto. </B></SPAN></P><TEXTAREA name=risposta_aperta_2 rows=8 cols=60 ><?php echo($risposta_aperta_2);?></TEXTAREA> 
            
            
            <P><SPAN class=testo><B>3. Quale tipologia di acquisto potrebbe scaturire da questo 
            contatto?</P></B></SPAN>
            <P></P><INPUT type=checkbox  <?php echo($c3_1);?> value="x" name=risp_voce_3_1><SPAN 
            class=testopiccolo>Acquisto software</SPAN><BR><INPUT type=checkbox  <?php echo($c3_2);?>  value="x" 
             name=risp_voce_3_2><SPAN class=testopiccolo>Noleggio 
            piattaforma</SPAN><BR><INPUT type=checkbox    <?php echo($c3_3);?> value="x"  
            name=risp_voce_3_3><SPAN class=testopiccolo>Abbonamento E-Prof per 
            gruppo docenti</SPAN><BR><INPUT type=checkbox    <?php echo($c3_4);?> value="x" 
            name=risp_voce_3_4><SPAN class=testopiccolo>Iscrizione corsi online 
            per gruppo docenti</SPAN><BR><INPUT type=checkbox    <?php echo($c3_5);?> value="x"  
            name=risp_voce_3_5><SPAN class=testopiccolo>Iscrizione Master per 
            gruppo docenti</SPAN><BR><INPUT type=checkbox    <?php echo($c3_6);?> value="x"  
            name=risp_voce_3_6><SPAN class=testopiccolo>Acquisto 
            Libri</SPAN><BR><INPUT type=checkbox    <?php echo($c3_7);?> value="x" name=risp_voce_3_7><SPAN 
            class=testopiccolo>Acquisto Learning Object</SPAN><BR>
			<INPUT type=checkbox    <?php echo($c3_8);?> value="x" name=risp_voce_3_8><SPAN 
            class=testopiccolo>Teatro dei Suoni</SPAN><BR>
			
			<INPUT 
            type=checkbox   <?php echo($c3_9);?> value="x"  name=risp_voce_3_9><SPAN class=testopiccolo>Altro, 
            specificare:<INPUT   size=50 
            name=risposta_altro_voce_3_9 value="<?php echo($risposta_altro_voce_3_9);?>"></SPAN>
			
            <P><SPAN class=testo><B>4. Aggiungi liberamente i tuoi commenti. 
            Grazie!</B></SPAN></P><TEXTAREA name=risposta_aperta_4 rows=8 cols=60 ><?php echo($risposta_aperta_4);?></TEXTAREA> 
            <BR>
            <P 
      align=center><?php if ($ruolo=="admin" or $id_utente==$kairos_cookie[0]) {?><INPUT type="submit" value="Modifica"> <span class=testo>[<a href=contatti_cancella.php?id_contatto=<?php echo $id_contatto ?>>Elimina scheda</a>]</span><?php }; ?></P></FORM></TD></TR></TBODY></TABLE>


</body>
</html>

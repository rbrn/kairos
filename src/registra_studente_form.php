<?php

require "./include/init_sito.inc";

require "./include/funzioni_sito.inc";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);

	



$id_utente=$kairos_cookie[0];

$pwd_utente=$kairos_cookie[1];



if (!$id_utente or !authenticateUser($id_utente,$pwd_utente)) {

	echo "I tuoi parametri di accesso non sono corretti!";

	exit();

};





if ($atlante_cookie[4]<>'1' and ruolo_utente($id_utente)<>'admin' and ruolo_utente($id_utente)<>'staff' ) {

	echo "I tuoi parametri di accesso non sono corretti!";

	exit();

};



mysql_select_db($DBASE_UTENTI,$db);

$query="SELECT count(*) as num_studenti FROM ragazzi_eprof WHERE id_eprof='$id_utente'";

$result=$mysqli->query($query);

$riga=$result->fetch_array();



$num_studenti=$riga["num_studenti"];



if ($num_studenti>=30) {

	echo "Hai giÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ registrato il massimo di 30 studenti consentito per ogni <b>E-Prof</b>.";

	exit();

};

?>

<HTML>

<HEAD><TITLE>Atlante Ragazzi: Registrazione Alunno</TITLE>

<link rel="stylesheet" href="../stili/stile_sito.css">

</HEAD>

<BODY bgcolor=$colore_sfondo>

<TABLE border=0 width=100%>

<TR>

<TD>

<span class=testo><b>Registrazione nuovo alunno ad ATLANTE RAGAZZI</b></span>

</TD>

</tr>



<TR>

<TD>

<FORM action=registra_studente.php method=post>

<span class=testopiccolo>

I campi in <b>grassetto</b> sono obbligatori.<br>

</span> 

<br><br>



            <TABLE border=0>

              <TR>

                <TD colSpan=2></TD></TR>

              <TR>

                <TD align=right><span class=testopiccolo><b>Identificativo</b></span></TD>

                <TD><INPUT maxLength=100 name=id_studente size=10><span class=testopiccolo> <i>(usare solo lettere e/o numeri senza spazi)</i></span>

			</TD></TR>

              

			  <TR>

                <TD align=right><span class=testopiccolo><b>Password</b></span></TD>

                <TD><INPUT maxLength=100 name=pwd_studente size=10><span class=testopiccolo> <i>(usare solo lettere e/o numeri senza spazi)</i></span>

			</TD></TR>

			

			  <TR>

                <TD colSpan=2>

                  <HR>

                </TD></TR>

              <TR>



				  

              <TR>

                <TD colSpan=2></TD></TR>

              <TR>

                <TD align=right><span class=testopiccolo><b>Nome</b></span></TD>

                <TD>

				<INPUT maxLength=100 name=nome size=35></TD></TR>

              <TR>

                <TD align=right><span class=testopiccolo><b>Cognome</b></span></TD>

                <TD><INPUT maxLength=100 name=cognome size=35></TD></TR>

              

              <TR>

                <TD align=right><span class=testopiccolo>E-Mail</span></TD>

                <TD><INPUT maxLength=100 name=email size=40></span></TD></TR>

              <TR>

              

			   <TR>			  

                <TD align=right><span class=testopiccolo><b>Sesso</b></span></TD>

                <TD><INPUT name=sesso type=radio value="M" checked><span class=testopiccolo>M</span><INPUT name=sesso type=radio value="F"><span class=testopiccolo>F</span></TD></TR>

	             <TR>

                <TD align=right><span class=testopiccolo><b>Fascia di etÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½</b></span></TD>

                <TD><SELECT name=eta size=1>

					 <OPTION selected value="meno 14">meno 14</OPTION>

					 <OPTION value="14-19">14-19</OPTION>

					 <OPTION value="20-26">20-26</OPTION>

					 <OPTION value="27-35">27-35</OPTION>

					 <OPTION value="36-45">36-45</OPTION>

					 <OPTION value="46-60">46-60</OPTION>

					 <OPTION value="oltre 60">oltre 60</OPTION>

					</SELECT>

				</TD>

				</TR>		



			<TR>

            <TD align=CENTER colspan=2 valign=top> 

			<INPUT type=submit value="REGISTRA">

			</TD>

			</TR>

		</TABLE>

		<BR>

        </FORM>    

</TD></TR>

		

<TR>

<TD>

<hr size=1>

</TD></TR>



<TR>

<TD>

<span class=testopiccolo><b>ATTENZIONE:</b> con la registrazione si ritengono contestualmente accettate le seguenti clausole:<br><br>

L'utente E-Prof identificato come <b><?php echo($id_utente);?></b>  che registra questo alunno ne ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ responsabile. <br>

Garamond declina ogni responsabilitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ da eventuali comportamenti illegali, lesivi od offensivi che tale alunno potrebbe condurre nella comunitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ in rete.<br>

Garamond si riserva comunque di annullare la registrazione dell'alunno nei casi in cui lo ritiene opportuno, senza preavviso e insidacabilmente.

</span>

</TD>

</TR>



  <TR>

    <TD>

      <HR size=1>

      <span class=testopiccolo>Copyright ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ 2001, <A   href="mailto:comunicazione@garamond.it">Garamond srl</A> - Piazza 

      Sallustio, 3 - 00187 ROMA - 06.4882110 </span>

</TD></TR>

  



</TABLE>

</BODY></HTML>

<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

?>
<table border=0 cellpadding=10>
<tr><td>
<p><span class=titolopagina><?php echo($stringa[registrazione]);?></span></p>
<TABLE border=0 width=500>
<TR>
<TD>
<FORM action=registra.php method=post name=modulo id=modulo>
<span class=testopiccolo>
<?php echo($stringa[modifica_intro]);?>
</span> 
            <TABLE border=0>
               <TR>
                <TD colSpan=2></TD></TR>
				 <TR>
                <TD colSpan=2></TD></TR>				
              <TR>
                <TD colSpan=2></TD></TR>

<?php 
if ($cod_area=="kairos_atlanteragazzi") {
echo "<tr> <TD align=right><span class=testopiccolo><b>ID Insegnante E-Prof di cui sei alunno/a:</b></span></TD>
<td><input type=text size=40 name=id_eproffaro>";
echo "</td></tr>";
};


?>				
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[identificativo]);?></b></span></TD>
                <TD><INPUT  name=id_utente size=10><br><span class=testopiccolo> <i><?php echo($stringa[id_guida]);?></i></span></TD></TR>

				<TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[password]);?></b></span></TD>
                <TD><INPUT  name=pwd_utente size=10></TD>
				</TR>

              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[nome]);?></b></span></TD>
                <TD>
				<INPUT  name=nome size=35></TD></TR>
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[cognome]);?></b></span></TD>
                <TD><INPUT  name=cognome size=35></TD></TR>
				
			<TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[email]);?></b></span></TD>
                <TD><INPUT  name=email size=35></TD></TR>


<?php
if ($cod_area=='kairos_larimart') {
	echo "
	 <TR>
                <TD align=right><span class=testopiccolo><b>Numero di
serie del cd-rom:</b></span></TD>
                <TD>
				<INPUT  name=codice_cd size=20></TD></TR>
	";
	require "./include/seleziona_gruppo_larimart.inc";
};

?>
				
<?php 
if ($cod_area<>"kairos_larimart") {
?>					
					  
			  
              <TR>
                <TD align=right vAlign=top><span class=testopiccolo><b><?php echo($stringa[indirizzo]);?></b></span></TD>
                <TD><INPUT name=indirizzo size=35></TD></TR>
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[cap]);?></b></span></TD>
                <TD><INPUT maxLength=5 name=cap size=5></span></TD></TR>
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[citta]);?></b></span></TD>
                <TD><INPUT  name=citta size=35></TD></TR>
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[prov]);?></b></span></TD>
                <TD><INPUT maxLength=2 name=prov size=2></TD></TR>
              
			
			 <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[scuola]);?></b></span></TD>
                <TD><INPUT  name=scuola size=35></TD></TR>
              
			  <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[telefono]);?></b></span></TD>
                <TD><INPUT  name=telefono size=35></TD></TR>
              
              <TR>
              <TR>
                <TD align=right><span class=testopiccolo><?php echo($stringa[sitoweb]);?></span></TD>
                <TD><INPUT  name=sitoweb size=35 value="http://"></span></TD></TR>
              <TR>			  
                <TD align=right><span class=testopiccolo><?php echo($stringa[sesso]);?></span></TD>
                <TD><INPUT name=sesso type=radio value="M"><span class=testopiccolo><?php echo($stringa[m]);?></span><INPUT name=sesso type=radio value="F"><span class=testopiccolo><?php echo($stringa[f]);?></span></TD></TR>
	             <TR>
                <TD align=right><span class=testopiccolo><?php echo($stringa[eta]);?></span></TD>
                <TD><INPUT  name=eta size=10>
				</TD>
				</TR>			  
								
			  <TR>
                <TD align=right><span class=testopiccolo><?php echo($stringa[interessi]);?></span></TD>
                <TD><INPUT  name=interesse size=35></TD></TR>
				
				
				<?php
				if ($cod_area<>"kairos_librinrete" and $cod_area<>"kairos_atlanteragazzi") {
				echo "
				<TR>
                <TD align=right><span class=testopiccolo><b>$stringa[ruolo_scuola]</b></span></TD>
                <TD>";
				
				if ($cod_area<>"kairos_amicosole" and $cod_area<>"kairos_oppla" and $cod_area<>"kairos_bandaingamba") {
					echo "
					<SELECT name=ruolo_scuola size=1> 
					<OPTION value=\"Dirigente\">$stringa[dirigente]</OPTION>
					<OPTION selected value=\"Insegnante\">$stringa[insegnante]</OPTION> 
					<OPTION value=\"Studente\">$stringa[studente]</OPTION>
					<OPTION value=\"Altro\">$stringa[altro]</OPTION>
					<OPTION value=\"Nessuno\">$stringa[nessun_ruolo]</OPTION>
					</SELECT>";
					
				} else {
					echo "
					<SELECT name=ruolo_scuola size=1> 
					<OPTION value=\"Dirigente\">$stringa[dirigente]</OPTION>
					<OPTION selected value=\"Insegnante\">$stringa[insegnante]</OPTION> 
					<OPTION value=\"Studente\">Alunno</OPTION>
					<OPTION value=\"Studente\">Genitore</OPTION>
					<OPTION value=\"Altro\">$stringa[altro]</OPTION>
					<OPTION value=\"Nessuno\">$stringa[nessun_ruolo]</OPTION>
					</SELECT>";
				};
			  echo "
			  </TD>
			  </TR>";
			  
			  if ($cod_area<>"kairos_amicosole" and $cod_area<>"kairos_oppla"  and $cod_area<>"kairos_bandaingamba") {
			  echo "
			  <TR>
               <TD align=right valign=top> 
                   <span class=testopiccolo>$stringa[materia_insegnata]</span>
				</TD>	
                <TD><INPUT name=materia size=50>
				<br><span class=testopiccolo>($stringa[guida_materia_insegnata])</span></TD>
				</TR>
			  ";
			  };
			  };
			  ?>
			
			<?php
				if ($cod_area=="kairos_librinrete") {
				echo "
			  <TR>
               <TD align=right valign=top> 
                   <span class=testopiccolo><b>Codice Libro in Rete:</b></span>
				</TD>	
                <TD><INPUT name=codice_libro size=60>
				<br><span class=testopiccolo><i>(Il codice, necessario per la registrazione, e' quello fornito dall'<a target=_blank>Agenzia Editoriale RCS</a> che ti ha invitato a partecipare alle attivitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ in rete del testo che hai in adozione.)</i></span><br><br></TD>
				</TR>
			  ";
			  };
			  ?>
			  	
			
			 <?php 
			if ($cod_area=='kairos_fortic') {?>	
			 <TR>
                <TD align=right><INPUT type=checkbox name=tutor_fortic></TD>
                <TD><span class=testopiccolo><b>Sono tutor di un corso ForTIC</b> presso:</span><input type=text name=scuola_fortic size=20></TD></TR>
			<?php }; ?> 

<?php
};
?>          

<?php
if ($cod_area<>'kairos_larimart' and $cod_area<>'kairos_librinrete') require "./include/seleziona_corso.inc";
?>

<?php
if ($cod_area=="kairos_amicosole" or $cod_area=="kairos_oppla"  or $cod_area=="kairos_bandaingamba") {
	echo "
	<tr><TD align=left colspan=2 valign=top> 
<br>
	<span class=testopiccolo>
	<b>Informativa ai sensi dell'articolo 13 D.L.vo 30 giugno 2003, 196</b>
	<br> 
I dati che Lei ci fornirÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ permetteranno a RCS MediaGroup di farLa partecipare alle nostre iniziative. Il conferimento dei dati ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ facoltativo tuttavia senza i Suoi dati non potremmo fornirLe i servizi indicati. I dati verranno custoditi su supporti informatici e trattati nel pieno rispetto delle misure di sicurezza a tutela della Sua riservatezza. Inoltre i Suoi dati potranno essere comunicati a tutte le SocietÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ del gruppo RCS MediaGroup, nonchÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ alle SocietÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ partecipate. Questi dati potranno essere utilizzati dai soggetti indicati nel suddetto elenco per permetterLe di ricevere informazioni scientifiche e commerciali, campioni gratuiti, buoni sconto, analisi statistiche ed essere contattato per sondaggi di opinione. Titolare e responsabile del trattamento dei dati ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ RCS Libri S.p.A., Via Mecenate, 91, 20138, Milano. In ogni momento potrÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ esercitare i suoi diritti nei confronti del titolare del trattamento, ai sensi dell'articolo 7 del D.L.vo n. 196/2003. <br><br>

<b>Consenso al trattamento dei dati</b>: Vi autorizzo al trattamento dei dati per le finalitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ e con le modalitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ indicate nell'impegno di riservatezza e dichiaro di essere maggiorenne. 
<br><br>
<input type=\"radio\" name=\"autorizzo_privacy\" value=\"1\">Accetto <input type=\"radio\" name=\"autorizzo_privacy\" value=\"0\">Non accetto 
	</span>
	<hr size=1>
	</td></tr>";

};
?>   
			<TR>
            <TD align=left colspan=2 valign=top> 
			<span class=testopiccolo>
<?php 
if ($cod_area=='kairos_larimart') {
	echo "La tua richiesta di registrazione verrÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ inoltrata al <b>responsabile dell'area</b> che provvederÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ ad autorizzarla entro le prossime <b>24 ore</b> lavorative. Se inserisci un <b>numero di
serie del cd-rom</b> valido, la tua registrazione sarÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ invece immediatamente ed automaticamente attivata.";
} else { 
	if ($cod_area<>"kairos_librinrete" and $cod_area<>"kairos_oppla"  and $cod_area<>"kairos_bandaingamba") {
		echo($stringa[registrazione_guida]);
	} else {
		if ($cod_area=="kairos_librinrete") {
		echo "
		Verrai automaticamente accreditato all'accesso al <b>Libro in Rete</b> corrispondente al codice libro che hai indicato. 
		";
		};
		
	};
};
?>
</span> 
			</TD>
			</TR>
			<TR>
            <TD align=center colspan=2 valign=top> 
			<INPUT type=submit value="<?php echo($stringa[ok]);?>">
			</TD>
			</TR>
		</TABLE>
		<BR>
        </FORM>    

</TD></TR>
</TABLE>
</td></tr>
</table>
<br>


<?php

echo "</div>
</div>
</div>
</div>
</div>";

?>
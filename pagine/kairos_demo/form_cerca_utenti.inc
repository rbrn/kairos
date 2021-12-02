<!-- CONTENUTO DELLA PAGINA -->



<h1>Cerca Utenti</h1>

<hr size=1>

<p>

<b>

Imposta il tuo criterio di ricerca compilando uno o piÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ campi della scheda qui presentata.

</b>

</p>

<p>I campi vegono uniti dall'operatore <b>AND</b>. Se ad esempio scrivi in corrispondenza di <i>materia insegnata</i> "italiano" e <i>provincia</i> "BA", verranno cercati tutti i corsisti che insegnano italiano e vivono nella provincia di Bari. 

</p>

<p>Dall'elenco selezionato vengono esclusi coloro che hanno dichiarato nel proprio profilo di non voler rendere noti i dati personali (qualora si cercasse usando criteri diversi da identificativo, nome o cognome, che sono dati obbligatoriamente visibili a tutti).

</p>



<TABLE BORDER=0 ALIGN=LEFT width=450>



<tr>

<td>

<form action="cerca_utenti_result.php" method="post">



<table border="0">



<tr>

<td align="right" valign=top>

<p>Identificativo</p>

</td>

<td valign=top>

<input type="text" size="10" maxlength=10 name="id_utente">

</td>

</tr>





 <tr>

 <td align="right" valign=top>

 <p>Nome</p>

 </td>

  <td valign=top>

 <input type="text" size="35" maxlength=35 name="nome">

 </td>

 </tr>

 

 <tr>

 <td align="right" valign=top><p>Cognome</p></td>

 <td valign=top><input type="text" size="35" maxlength=35 name="cognome"></p>

 </td>

 </tr>

 	

<tr>

<td align="right" valign=top><p>CittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½</p></td>

<td valign=top><input type="text" size="35" maxlength=35 name="citta"></td>

</tr>		



<tr>

<td align="right" valign=top><p>Prov.</p></td>

<td valign=top><input type="text" size="02" maxlength=02 name="prov"></td>

</tr>		

 

<tr>

<td align="right" valign=top><p>Tipo Scuola/Istituto in cui opera:</p></td>

<td valign=top><SELECT name=ordinescuola size=1> 

					<OPTION value="Scuola d'Infanzia">Scuola d'Infanzia</OPTION>

					<OPTION value="Scuola Elementare">Scuola Elementare</OPTION> 

					<OPTION value="Scuola Media Inferiore">Scuola Media Inferiore</OPTION>

					<OPTION  value="Scuola Media Superiore">Scuola Media Superiore</OPTION>

					<OPTION value="UniversitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½">UniversitÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½</OPTION>

					<OPTION value="Enti/Istituti di ricerca">Enti/Istituti di ricerca</OPTION>

					<OPTION selected value="all">qualunque</OPTION>

</SELECT>

</td>

</tr>

		

<tr>

<td align="right" valign=top><p>Materia Insegnata</p></td>

<td valign=top><input type="text" size="50" maxlength=50 name="materia"></td>

</tr>



<tr><td colspan=2></td></tr>



<tr><td colspan=2>

<p align="center">

<input type="submit"  value="CERCA">

</p>

	

</td>

</tr>



</table>

</form>



<!-- FINE CONTENUTO DELLA PAGINA -->



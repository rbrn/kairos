<table width="94%" align="center">

  <tr> 

    <td height="14" width="22%"> 

      <div align="center"></div>

    </td>

    <td height="14" width="78%"> 

      <span class="titolopagina">Elenco Iscritti</span>

	  <br><br>

	  <span class="sottotitolopagina">

	  Atlante Ragazzi</span>

	  <br><br>



    </td>

  </tr>

  <tr> 

    <td width="22%"  valign="top"> 

     <ul>

        <li> 

          <span class="titololink"> 

		  <a href="index.php?risorsa=calendario">Calendario</a>

		  </span>

		  <br><br>

        </li>

		<li> 

          <span class="titolosezionecorrente"> 

		  Elenco iscritti

		  </span>

		  <br><br>

        </li>		

      </ul>

    </td>

    <td width="78%" valign="top"> 

	<!-- contenuto pagina -->

	<table border=1 cellpadding=5>

	<tr>

	<td>

	<span class=testopiccolo>

	<b>Iscritto</b>

	</span>

	</td>

	<td>

	<span class=testopiccolo>

	<b>Ordine</b>

	</span>

	</td>

	<td>

	<span class=testopiccolo>

	<b>CittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½</b>

	</span>

	</td>

	<td>

	<span class=testopiccolo>

	<b>E-Prof</b>

	</span>

	</td>	

	</tr>

	

    <?php



	mysql_select_db($DBASE_UTENTI,$db);

	

	$query="SELECT utenti.id_utente,ragazzi_eprof.id_eprof,utenti.nome,utenti.cognome,utenti.ordinescuola,utenti.cittascuola,utenti.provscuola FROM ragazzi_eprof,utenti WHERE ragazzi_eprof.id_utente=utenti.id_utente";

	$result=$mysqli->query($query);



	$i=1;

	

	while ($riga=$result->fetch_array()) {

		$id_utente1 = $riga["id_utente"];

		$id_eprof= $riga["id_eprof"];

		$nome = $riga["nome"];

		$cognome = $riga["cognome"];

		$ordinescuola = stripslashes($riga["ordinescuola"]);

		$cittascuola = stripslashes($riga["cittascuola"]);

		$provscuola=$riga["provscuola"];

		

		echo "

		<tr>

		<td>

		<span class=testopiccolo>

		<b>$i</b> - 

		$nome $cognome (<a class=miolink href=\"javascript:;\" title=\"Clicca per sapere chi ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½...\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a>)</span>

		</td>

		<td>

		<span class=testopiccolo>

		$ordinescuola 

		</span>

		</td>

		<td>

		<span class=testopiccolo>

		$cittascuola ($provscuola) 

		</span>

		</td>

		<td>

		<span class=testopiccolo>

		<a class=miolink href=\"javascript:;\" title=\"Clicca per sapere chi ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½...\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_eprof',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_eprof</a>

		</span>

		</td>

		

		</tr>

			";

			

		$i++;

	};

	

	?>

	</table>

	<!-- fine contenuto pagina -->

<p>&nbsp;</p>

      </td>

  </tr>

</table>

<br>

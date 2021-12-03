<?php

require("./cerca/config/config.php");

require "./include/init_sito.inc";

require "./include/funzioni_sito.inc";

$risorsa="";

require "./include/testata.inc";

?>

<!-- CONTENUTO DELLA PAGINA -->

	

		<p span class=titolopagina>Cerca nei Forum</p>

	

	<TABLE WIDTH="100%" CELLSPACING="0" CELLPADDING="0" BORDER="0">

		<TR>

			<TD ALIGN="center">

				<FORM METHOD="get" ACTION="forum_cerca_op.php">

					<TABLE CELLSPACING="0" CELLPADDING="0" BORDER="0">

						<TR>

							<TD><INPUT TYPE="text" NAME="q" SIZE="25" TABINDEX="1">&nbsp;</TD>

							<TD><INPUT TYPE="submit" VALUE="Cerca" TABINDEX="3">&nbsp;</TD>

							<TD>

								<SELECT NAME="r" TABINDEX="2">

									<OPTION VALUE="0">Mostra tutti i risultati in una pagina</OPTION>

									<OPTION VALUE="5">5 risultati per pagina</OPTION>

									<OPTION SELECTED VALUE="10">10 risultati per pagina</OPTION>

									<OPTION VALUE="20">20 risultati per pagina</OPTION>

									<OPTION VALUE="30">30 risultati per pagina</OPTION>

									<OPTION VALUE="50">50 risultati per pagina</OPTION>

								</SELECT>

							</TD>

						</TR>

						<TR>

							<TD>

						

							</TD>

							<TD COLSPAN="2">&nbsp;</TD>

						</TR>

					</TABLE>

				</FORM>

			</TD>

		</TR>

	</TABLE>



<!-- FINE CONTENUTO DELLA PAGINA -->

</td>

</tr>





<?php

require "./include/piede.inc";

?>



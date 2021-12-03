<?php
$padre=$_REQUEST["padre"];
$query="SELECT DISTINCT id_risorsa FROM risorse WHERE tipo='2' ORDER BY id_risorsa ";

$result=$mysqli->query($query);



if ($padre=='root') {

	$elenco_cartelle = "<OPTION VALUE=\"root\" selected>root</OPTION>\n";

} else {

	$elenco_cartelle = "<OPTION VALUE=\"root\">root</OPTION>\n";	

};



while ($riga=$result->fetch_array()) {

	$cartella = $riga["id_risorsa"];

	

	if (($cartella=='admin' or risorsa_admin($cartella)) and $ruolo<>'admin') {

		$prendi=false;

	} else {

		$prendi=true;

	};

	

	if ($prendi) {

		if ($padre==$cartella) {

			$elenco_cartelle .= "<OPTION VALUE=\"$cartella\" selected>$cartella</OPTION>\n";

		} else {

			$elenco_cartelle .= "<OPTION VALUE=\"$cartella\">$cartella</OPTION>\n";	

		};

	};

};


?>



 <P><FONT face=verdana><B><br>

    <?php echo($stringa[nuova_pagina_web]);?></B></FONT> </P>

 <FONT face=verdana size=-1>[<a href=index.php?risorsa=admin_index&id_cartella=<?php echo($padre);?>><?php echo($stringa[indietro]);?></a>]</font><br>

  <P> 

  <FORM action=web_add.php encType=multipart/form-data method=post>

  <INPUT name=MAX_FILE_SIZE type=hidden value=5097150>  

  

  <input type=hidden name=tipo value=0>

   

    <TABLE border=0 width=461>

      <TR> 

        <TD colSpan=2></TD>

      </TR>

      <TR> 

        <TD align=right><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[cartella]);?>:</STRONG></FONT></TD>

        <TD><FONT face=verdana size=-1> 

			<SELECT NAME="risorsa_padre">

			<?php echo($elenco_cartelle);?>

			</SELECT> 

          </FONT></TD>

      </TR>	  	  

      <TR> 

        <TD align=right><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[id_pagina_web]);?>:</STRONG></FONT></TD>

        <TD> 

			<INPUT type="text" maxLength=200 name=id_risorsa 

            size=20>

        </TD>

      </TR>



      	  

	  <TR> 

        <TD align=right><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[titolo]);?>:</STRONG></FONT></TD>

        <TD><FONT face=verdana size=-1> 

          <INPUT type="text" maxLength=150 name=titolo 

            size=50>

          </FONT></TD>

      </TR>



      <TR> 

        <TD align=right><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[livello]);?>:</STRONG></FONT></TD>

        <TD><FONT face=verdana size=-1> 

			<SELECT NAME="livello">

				<OPTION VALUE="1" selected><?php echo($stringa[pubblico]);?></option>

				<OPTION VALUE="2" ><?php echo($stringa[registrati]);?></option>

				<OPTION VALUE="4" ><?php echo($stringa[staff]);?></option>

				<OPTION VALUE="5" ><?php echo($stringa[admin]);?>in</option>

			</SELECT> 

          </FONT></TD>

      </TR>	  

 

	 

      <TR> 

        <TD align=right valign=top><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[descrizione]);?>:</STRONG></FONT></TD>

        <TD><textarea name=descrizione rows=05 cols=70></textarea>

          </FONT></TD>

      </TR>  	



      <TR> 

        <TD align=right valign=top><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[parole_chiave]);?>:</STRONG></FONT></TD>

        <TD><textarea name=parole_chiave rows=05 cols=70></textarea>

          </FONT></TD>

      </TR>  		



  	   

      <TR> 

        <TD align=right valign=top><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[contenuto]);?>:</STRONG></FONT></TD>

        <TD><INPUT type="file" name="pagina"></TD>

      </TR>  	  

	  	  

    </TABLE>

    <BR>

    <P align=center> 

      <INPUT type=submit value="<?php echo($stringa[ok]);?>">

    </P>

  </FORM>

  <HR>

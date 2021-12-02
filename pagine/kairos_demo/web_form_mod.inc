<b><font face="verdana" size="-1"><?php echo($stringa[modifica_pagina_web]);?></font></b>



<?php

$id_risorsa=$_REQUEST["id_risorsa"];



$query = "SELECT * FROM risorse where id_risorsa='$id_risorsa'";

$result=$mysqli->query($query);

$riga=$result->fetch_array();



$risorsa_padre=$riga["risorsa_padre"];	



$titolo=htmlentities($riga["titolo"]);		

$livello=$riga["livello"];

$descrizione=$riga["descrizione"];

$parole_chiave=$riga["parole_chiave"];

$id_gruppo=$riga["id_gruppo"];

$tipo=$riga["tipo"];

$livello01="";

$livello02="";

$livello03="";

$livello04="";

$livello05="";
   

$query="SELECT DISTINCT id_risorsa FROM risorse WHERE tipo='2' ORDER BY id_risorsa ";

$result=$mysqli->query($query);



if ($risorsa_padre=='root') {

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

		if ($risorsa_padre==$cartella) {

			$elenco_cartelle .= "<OPTION VALUE=\"$cartella\" selected>$cartella</OPTION>\n";

		} else {

			$elenco_cartelle .= "<OPTION VALUE=\"$cartella\">$cartella</OPTION>\n";	

		};

	};

};  



switch ($livello) {

	case 1:

		$livello01="selected";

		break;

		

	case 2:

		$livello02="selected";

		break;



	case 3:

		$livello03="selected";

		break;

	

	case 4:

		$livello04="selected";

		break;

	

	case 5:

		$livello05="selected";

		break;

};		




?>



<form action=web_mod_ok.php encType=multipart/form-data method=post>

  <INPUT name=MAX_FILE_SIZE type=hidden value=5097150> 

    <TABLE border=0 width=461>

      <TR> 

        <TD colSpan=2></TD>

      </TR>

      <TR> 

        <TD align=right><STRONG><?php echo($stringa[id_pagina_web]);?>:</STRONG></FONT></TD>

        <TD> 

			<input type=hidden name=id_risorsa value="<?php echo($id_risorsa);?>">

			<FONT face=verdana size=-1><?php echo($id_risorsa);?></font>

	    </TD>

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

            size=-1><STRONG><?php echo($stringa[titolo]);?>:</STRONG></FONT></TD>

        <TD><FONT face=verdana size=-1> 

          <INPUT type="text" maxLength=150 name=titolo 

            size=50 value="<?php echo($titolo);?>">

          </FONT></TD>

      </TR>



      <TR> 

        <TD align=right><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[livello]);?>:</STRONG></FONT></TD>

        <TD><FONT face=verdana size=-1> 

			<SELECT NAME="livello">

				<OPTION VALUE="1" <?php echo($livello01);?>><?php echo($stringa[pubblico]);?></option>

				<OPTION VALUE="2" <?php echo($livello02);?>><?php echo($stringa[registrati]);?></option>

				<OPTION VALUE="4" <?php echo($livello04);?>><?php echo($stringa[staff]);?></option>

				<OPTION VALUE="5" <?php echo($livello05);?>><?php echo($stringa[admin]);?></option>

			</SELECT> 

          </FONT></TD>

      </TR>	  


      <TR> 

        <TD align=right valign=top><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[descrizione]);?>:</STRONG></FONT></TD>

        <TD><textarea name=descrizione rows=05 cols=70><?php echo($descrizione);?></textarea>

          </FONT></TD>

      </TR>  	



      <TR> 

        <TD align=right valign=top><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[parole_chiave]);?>:</STRONG></FONT></TD>

        <TD><textarea name=parole_chiave rows=05 cols=70><?php echo($parole_chiave);?></textarea>

          </FONT></TD>

      </TR> 

  

      <TR> 

        <TD align=right valign=top><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[codice_contenuto]);?>:</STRONG></FONT></TD>

        <TD><INPUT type="file" name="pagina"></TD>

      </TR>  	  



	  <TR> 

        <TD align=right valign=top><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[contenuto]);?>:</STRONG></FONT></TD>

        <TD><a href=scarica_codice.php?id_risorsa=<?php echo($id_risorsa);?>><?php echo($id_risorsa);?>.htm</a></TD>

      </TR> 

	  	  

    </TABLE>

    <BR>

    <P align=center> 

      <INPUT type=submit value="<?php echo($stringa[ok]);?>">

    </P>

  </FORM>

  <HR>

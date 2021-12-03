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

    <?php echo($stringa[nuova_cartella]);?></B></FONT> </P>

 <FONT face=verdana size=-1>[<a href=index.php?risorsa=admin_index&id_cartella=<?php echo($padre);?>><?php echo($stringa[admin]);?></a>]</font><br>

  <P> 

  <form action=folder_add.php method=post>

  <input type=hidden name=tipo value=2>

    <TABLE border=0 width=461>

      <TR> 

        <TD colSpan=2></TD>

      </TR>

      <TR> 

        <TD align=right><FONT face=verdana 

            size=-1><STRONG> <?php echo($stringa[cartella]);?>:</STRONG></FONT></TD>

        <TD><FONT face=verdana size=-1> 

			<SELECT NAME="risorsa_padre">

			<?php echo($elenco_cartelle);?>

			</SELECT> 

          </FONT></TD>

      </TR>	  	  

      <TR> 

        <TD align=right><FONT face=verdana 

            size=-1><STRONG> <?php echo($stringa[id_cartella]);?>:</STRONG></FONT></TD>

        <TD> 

			<INPUT type="text" maxLength=200 name=id_risorsa 

            size=20>

        </TD>

      </TR>

      <TR> 

        <TD align=right><FONT face=verdana 

            size=-1><STRONG> <?php echo($stringa[descrizione]);?>:</STRONG></FONT></TD>

        <TD> 

			<INPUT type="text" maxLength=200 name=titolo 

            size=20>

        </TD>

      </TR>



      

	  	  

    </TABLE>

    <BR>

    <P align=center> 

      <INPUT type=submit value="<?php echo($stringa[inserisci]);?>">

    </P>

  </FORM>

  <HR>

<b><font face="verdana" size="-1"><?php echo($stringa[modifica]." ".$stringa[cartella]);?></font></b>

<p>

<?php

$id_risorsa=$_REQUEST["id_risorsa"];

$query = "SELECT * FROM risorse where id_risorsa='$id_risorsa'";

$result=$mysqli->query($query);

$riga=$result->fetch_array();



$risorsa_padre=$riga["risorsa_padre"];		

$titolo=$riga["titolo"];

     

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





?>



<form action=folder_mod_ok.php method=post>

<input type=hidden name=ex_id_risorsa value=<?php echo($id_risorsa);?>>

<input type=hidden name=ex_risorsa_padre value=<?php echo($risorsa_padre);?>>

    <TABLE border=0 width=461>

     <TR> 

        <TD align=right><FONT face=verdana size=-1><STRONG><?php echo($stringa[cartella]);?>:</STRONG></FONT></TD>

        <TD><FONT face=verdana size=-1> 

			<SELECT NAME="risorsa_padre">

			<?php echo($elenco_cartelle);?>

			</SELECT> 

          </FONT></TD>

      </TR>	 

	

      <TR> 

        <TD colSpan=2></TD>

      </TR>

      <TR> 

        <TD align=right><STRONG><?php echo($stringa[id_cartella]);?>:</STRONG></FONT></TD>

        <TD> 

			<INPUT type="text" maxLength=200 name=id_risorsa 

            size=20 value="<?php echo($id_risorsa);?>">			

	    </TD>

      </TR>



      <TR> 

        <TD align=right><STRONG><?php echo($stringa[descrizione]);?>:</STRONG></FONT></TD>

        <TD> 

			<INPUT type="text" maxLength=200 name=titolo 

            size=20 value="<?php echo($titolo);?>">			

	    </TD>

      </TR>	  

	   

	  	  

    </TABLE>

    <BR>

    <P align=center> 

      <INPUT type=submit value="<?php echo($stringa[modifica]);?>">

    </P>

  </FORM>

<br>		

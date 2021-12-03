<?php
$cartella=$_REQUEST["cartella"];
?>
<P><FONT face=verdana><B><br>
    <?php echo($stringa[nuova_cartella]);?></B></FONT> </P>

 <FONT face=verdana size=-1>[<a href=index.php?risorsa=admin_index><?php echo($stringa[indietro]);?></a>]</font><br>

  <P> 

  <form action=cartella_add.php method=post>

  <input type=hidden name=cartella value="<?php echo($cartella);?>">

    <TABLE border=0 width=461>

      <TR> 

        <TD colSpan=2></TD>

      </TR>

  

      <TR> 

        <TD align=right><FONT face=verdana 

            size=-1><STRONG><?php echo($stringa[cartella]);?>:</STRONG></FONT></TD>

        <TD> 

			<INPUT type="text" maxLength=200 name=id_cartella size=20>

        </TD>

      </TR>

      

	  	  

    </TABLE>

    <BR>

    <P align=center> 

      <INPUT type=submit value="<?php echo($stringa[ok]);?>">

    </P>

  </FORM>

  <HR>

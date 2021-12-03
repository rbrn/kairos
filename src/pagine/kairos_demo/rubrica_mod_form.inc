<?php

$id_rubrica=$_REQUEST["id_rubrica"];

$query = "SELECT * FROM rubrica WHERE id_rubrica='$id_rubrica'";

$result=$mysqli->query($query);

$riga = $result->fetch_array();

$titolo=$riga["titolo"];

$posizione=$riga["posizione"];

?>

<p><span class=titolopagina>Modifica rubrica</span></p>

<span class=testo>[<a href=index.php?risorsa=gestione_rubriche>Gestione rubriche</a>]</span><br>

  <P> 

  <form action=rubrica_mod.php method=post>

  <input type="hidden" name="id_rubrica" value="<?php echo($id_rubrica);?>">

    <TABLE border=0 width=600>

      <TR> 

        <TD colSpan=2></TD>

      </TR>

      <TR> 

      <TR> 

        <TD align=right valign=top><span class=testo><b>ID Rubrica:</b></span></TD>

        <TD> 

			<span class=testo><?php echo($id_rubrica);?></span>

        </TD>

      </TR>

      <TR> 

        <TD align=right><span class=testo><b>Denominazione rubrica:</b></span></TD>

        <TD> 

			<INPUT type="text" maxLength=200 name=titolo size=20 value="<?php echo($titolo);?>">

        </TD>

      </TR>



	    <TR> 

        <TD align=right><span class=testo><b>Posizione nell'elenco:</b></span></TD>

        <TD> 

			<INPUT type="text" maxLength=200 name=posizione size=20 value="<?php echo($posizione);?>">

        </TD>

      </TR>

      

	  	  

    </TABLE>

    <BR>

    <P align=center> 

      <INPUT type=submit value="MODIFICA">

    </P>

  </FORM>

  <HR>
